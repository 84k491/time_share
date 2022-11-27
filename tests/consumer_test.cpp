#include <gtest/gtest.h>
#include "timestamp_consumer_app.h"
#include "i_listener.h"
#include "message.h"
#include <vector>
#include <queue>
#include <algorithm>

namespace test {

class MockListener final : public IListener
{
public:
    MockListener() = default;
    ~MockListener() = default;

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
        set_consumer_callback([&](const Message &) { ++m_received_count; });
    }

    void set_consumer_callback(std::function<void(const Message & msg)> && callback)
    {
        m_consumer.m_on_msg_received = callback;
    }

    MockListener m_listener;
    TimestampConsumerApp m_consumer;
    size_t m_received_count = 0;
};

TEST_F(ConsumerTest, receive_single_message)
{
    std::vector<char> data;
    data.resize(Message::size());
    auto & msg = *new(data.data()) Message();
    msg.fill_verification_header();
    msg.set_timestamp(0);
    ASSERT_TRUE(msg.verify());
    m_listener.push_message(std::move(data));

    m_consumer.work();

    EXPECT_EQ(m_received_count, 1);
}

TEST_F(ConsumerTest, dont_receive_completely_invalid_message)
{
    std::vector<char> data;
    std::fill_n(std::back_inserter(data), Message::size(), 'A');

    m_listener.push_message(std::move(data));
    m_consumer.work();
    
    EXPECT_EQ(0, m_received_count);
}

TEST_F(ConsumerTest, dont_receive_old_version_message)
{
    std::vector<char> data;
    data.resize(Message::size());
    auto & msg = *new(data.data()) Message();
    msg.fill_verification_header();
    msg.set_timestamp(0);

    char * version = &data[7];
    ASSERT_EQ(*version, '1');
    *version = '0';
    ASSERT_FALSE(msg.verify());

    m_listener.push_message(std::move(data));

    m_consumer.work();

    EXPECT_EQ(m_received_count, 0);
}

TEST_F(ConsumerTest, dont_receive_msg_with_greater_size)
{
    std::vector<char> data;
    constexpr size_t additional_size = 10;
    std::fill_n(std::back_inserter(data), Message::size() + additional_size, 'A');
    auto & msg = *new(data.data()) Message();
    msg.fill_verification_header();
    msg.set_timestamp(0);
    ASSERT_TRUE(msg.verify());
    m_listener.push_message(std::move(data));

    m_consumer.work();

    EXPECT_EQ(m_received_count, 0);
}

TEST_F(ConsumerTest, dont_receive_msg_with_smaller_size)
{
    std::vector<char> data;
    std::fill_n(std::back_inserter(data), Message::size(), 'A');
    auto & msg = *new(data.data()) Message();
    msg.fill_verification_header();
    msg.set_timestamp(0);
    ASSERT_TRUE(msg.verify());
    data.erase(data.end() - 1);
    m_listener.push_message(std::move(data));

    m_consumer.work();

    EXPECT_EQ(m_received_count, 0);
}

}
