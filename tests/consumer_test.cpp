#include "i_listener.h"
#include "message.h"
#include "timestamp_consumer_app.h"
#include "timestamp_factory.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <queue>
#include <tuple>
#include <vector>

namespace test {

class MockPrinter final : public IPrinter
{
public:
    ~MockPrinter() = default;

    void print(uint64_t local, uint64_t received, int32_t diff) override
    {
        std::tie(m_local, m_received, m_diff) = std::make_tuple(local, received, diff);
    }

    uint64_t m_local = 0;
    uint64_t m_received = 0;
    int32_t m_diff = 0;
};

class MockListener final : public IListener
{
public:
    MockListener() = default;
    ~MockListener() override = default;

    std::tuple<int, const void *, size_t> obtain_data() override
    {
        if (m_messages_to_receive.empty()) {
            return {-1, nullptr, 0}; // simulating socket failure to stop consumer loop
        }
        m_received_message = std::move(m_messages_to_receive.front());
        m_messages_to_receive.pop();
        return {0, m_received_message.data(), m_received_message.size()};
    }

    void set_is_ready(bool value) { m_is_ready = value; }

    void push_message(std::vector<char> && data_to_push)
    {
        m_messages_to_receive.emplace(std::move(data_to_push));
    }

private:
    std::queue<std::vector<char>> m_messages_to_receive;
    std::vector<char> m_received_message;
};

class ConsumerTest : public ::testing::Test
{
protected:
    ConsumerTest()
        : m_consumer(m_listener)
    {
    }

    void SetUp() override
    {
        m_listener.set_is_ready(true);
    }

    void set_consumer_callback(std::function<void(const Message & msg)> && callback)
    {
        m_consumer.m_on_msg_received = callback;
    }

    std::unique_ptr<MockPrinter> extract_printer()
    {
        auto * base_p = m_consumer.m_printer.release();
        auto * der_p = dynamic_cast<MockPrinter *>(base_p);
        if (!der_p) {
            return nullptr;
        }
        return std::unique_ptr<MockPrinter>{der_p};
    }
    auto set_mock_printer()
    {
        m_consumer.m_printer = std::make_unique<MockPrinter>();
    }

    MockListener m_listener;
    TimestampConsumerApp m_consumer;
    size_t m_received_count = 0;
};

TEST_F(ConsumerTest, receive_single_message)
{
    std::vector<char> data;
    data.resize(Message::size());
    auto & msg = *new (data.data()) Message();
    msg.fill_verification_header();
    msg.set_timestamp(0);
    ASSERT_TRUE(msg.verify());
    m_listener.push_message(std::move(data));

    set_consumer_callback([&](const Message &) { ++m_received_count; });
    m_consumer.work();

    EXPECT_EQ(m_received_count, 1);
}

TEST_F(ConsumerTest, dont_receive_completely_invalid_message)
{
    std::vector<char> data;
    std::fill_n(std::back_inserter(data), Message::size(), 'A');

    m_listener.push_message(std::move(data));
    set_consumer_callback([&](const Message &) { ++m_received_count; });
    m_consumer.work();

    EXPECT_EQ(0, m_received_count);
}

TEST_F(ConsumerTest, dont_receive_old_version_message)
{
    std::vector<char> data;
    data.resize(Message::size());
    auto & msg = *new (data.data()) Message();
    msg.fill_verification_header();
    msg.set_timestamp(0);

    char * version = &data[Message::s_header.size() - 1];
    ASSERT_EQ(*version, '1');
    *version = '0';
    ASSERT_FALSE(msg.verify());

    m_listener.push_message(std::move(data));

    set_consumer_callback([&](const Message &) { ++m_received_count; });
    m_consumer.work();

    EXPECT_EQ(m_received_count, 0);
}

TEST_F(ConsumerTest, dont_receive_msg_with_greater_size)
{
    std::vector<char> data;
    constexpr size_t additional_size = 10;
    std::fill_n(std::back_inserter(data), Message::size() + additional_size, 'A');
    auto & msg = *new (data.data()) Message();
    msg.fill_verification_header();
    msg.set_timestamp(0);
    ASSERT_TRUE(msg.verify());
    m_listener.push_message(std::move(data));

    set_consumer_callback([&](const Message &) { ++m_received_count; });
    m_consumer.work();

    EXPECT_EQ(m_received_count, 0);
}

TEST_F(ConsumerTest, dont_receive_msg_with_smaller_size)
{
    std::vector<char> data;
    std::fill_n(std::back_inserter(data), Message::size(), 'A');
    auto & msg = *new (data.data()) Message();
    msg.fill_verification_header();
    msg.set_timestamp(0);
    ASSERT_TRUE(msg.verify());
    data.erase(data.end() - 1);
    m_listener.push_message(std::move(data));

    set_consumer_callback([&](const Message &) { ++m_received_count; });
    m_consumer.work();

    EXPECT_EQ(m_received_count, 0);
}

TEST_F(ConsumerTest, positive_diff)
{
    std::vector<char> data;
    data.resize(Message::size());
    auto & msg = *new (data.data()) Message();
    msg.fill_verification_header();

    constexpr int time_diff = 100;
    const auto current_ts = TimestampFactory::get_timestamp_ms();
    msg.set_timestamp(current_ts - time_diff);
    set_mock_printer();

    ASSERT_TRUE(msg.verify());
    m_listener.push_message(std::move(data));
    m_consumer.work();

    const auto printer = extract_printer();
    ASSERT_TRUE(printer);
    EXPECT_TRUE(printer->m_diff > 0);
    EXPECT_EQ(printer->m_received, current_ts - time_diff);
}

TEST_F(ConsumerTest, negative_diff)
{
    std::vector<char> data;
    data.resize(Message::size());
    auto & msg = *new (data.data()) Message();
    msg.fill_verification_header();

    constexpr int time_diff = 100;
    const auto current_ts = TimestampFactory::get_timestamp_ms();
    msg.set_timestamp(current_ts + time_diff);
    set_mock_printer();

    ASSERT_TRUE(msg.verify());
    m_listener.push_message(std::move(data));
    m_consumer.work();

    const auto printer = extract_printer();
    ASSERT_TRUE(printer);
    EXPECT_TRUE(printer->m_diff < 0);
    EXPECT_EQ(printer->m_received, current_ts + time_diff);
}

} // namespace test
