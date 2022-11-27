#include <gtest/gtest.h>
#include "timestamp_consumer_app.h"
#include "i_listener.h"
#include <vector>
#include <queue>

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
        m_received_messasge = std::move(m_messages_to_receive.front());
        m_messages_to_receive.pop();
        return {0, m_received_messasge.data(), m_received_messasge.size()};
    }

    void set_is_ready(bool value) { m_is_ready = value; }

    void push_message(std::vector<char> && data_to_push)
    {
        m_messages_to_receive.emplace(std::move(data_to_push));
    }

private:
    std::queue<std::vector<char>> m_messages_to_receive;
    std::vector<char> m_received_messasge;
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

    MockListener m_listener;
    TimestampConsumerApp m_consumer;
};

TEST_F(ConsumerTest, receive_single_message)
{
    std::vector<char> data;
    data.resize(Message::size());
    auto & msg = *new(data.data()) Message();
    msg.fill_verification_header();
    msg.set_timestamp(0);
    m_listener.push_message(std::move(data));

    m_consumer.work();
}

}
