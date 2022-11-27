#include <gtest/gtest.h>
#include <queue>
#include <algorithm>
#include "i_sender.h"
#include "i_listener.h"
#include "timestamp_provider_app.h"
#include "timestamp_consumer_app.h"

namespace test {

class MockPhysicalChannel
{
public:
    std::queue<std::vector<char>> m_sent_messages;
};

class MockSenderWithChannel final : public ISender
{
public:
    MockSenderWithChannel(MockPhysicalChannel & channel)
        : m_channel(channel)
    {
    }
    ~MockSenderWithChannel() override = default;

    int send(const void * data, size_t size) override
    {
        if (m_is_ready) {
            std::vector<char> vec_to_push;
            size_t count = 0;
            std::generate_n(
                std::back_inserter(vec_to_push),
                size,
                [&]() -> char { return *(static_cast<const char *>(data) + count++); });
            m_channel.m_sent_messages.emplace(std::move(vec_to_push));
            return 0;
        }
        return -1;
    }

    bool is_ready() const override { return m_is_ready; }

private:
    bool m_is_ready = true;
    MockPhysicalChannel & m_channel;
};

class MockListenerWithChannel final : public IListener
{
public:
    MockListenerWithChannel(MockPhysicalChannel & channel)
        : m_channel(channel)
    {
        m_is_ready = true;
    }
    ~MockListenerWithChannel() = default;

    std::tuple<int, const void *, size_t> obtain_data() override
    {
        if (m_channel.m_sent_messages.empty()) {
            return {-1, nullptr, 0}; // simulating socket failure to stop consumer loop
        }
        m_received_message = std::move(m_channel.m_sent_messages.front());
        m_channel.m_sent_messages.pop();
        return {0, m_received_message.data(), m_received_message.size()};
    }

private:
    MockPhysicalChannel & m_channel;
    std::vector<char> m_received_message;
};

class EndToEndTest : public ::testing::Test
{
protected:
    static constexpr size_t amount_to_send = 10;

    EndToEndTest()
        : m_sender(m_channel)
        , m_provider(m_sender)
        , m_listener(m_channel)
        , m_consumer(m_listener)
    {
        m_provider.set_iterations_limit(amount_to_send);
        m_provider.m_do_printout = false;
        m_consumer.m_on_msg_received = [&](const Message &) { ++m_received_count; };
    }

    MockPhysicalChannel m_channel;

    MockSenderWithChannel m_sender;
    TimestampProviderApp m_provider;

    MockListenerWithChannel m_listener;
    TimestampConsumerApp m_consumer;

    size_t m_received_count = 0;
};

TEST_F(EndToEndTest, general_scenario)
{
    m_provider.work();
    m_consumer.work();
    EXPECT_EQ(amount_to_send, m_received_count);
}

}
