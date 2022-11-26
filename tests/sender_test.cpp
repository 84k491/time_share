#include <gtest/gtest.h>
#include "timestamp_provider_app.h" 

namespace test {

// TODO make final
class MockSender final : public ISender
{
public:
    ~MockSender() override {}
    int send(const Message & msg) override
    {
        if (m_is_ready) {
            m_sent_messages.emplace_back(msg);
            return 0;
        }
        return -1;
    }

    auto sent_count() const { return m_sent_messages.size(); }
    bool is_ready() const override { return m_is_ready; }
    void set_is_ready(bool value) { m_is_ready = value; }
    const auto & last_sent_message() const { return m_sent_messages.back(); }

private:
    bool m_is_ready = true;
    std::vector<Message> m_sent_messages;
};

class SenderTest : public ::testing::Test
{
protected:
    SenderTest()
        : m_provider(m_sender)
    {
    }

    void set_iterations(size_t v)
    {
        m_provider.set_iterations_limit(v);
    }

    MockSender m_sender;
    TimestampProviderApp m_provider;
};

TEST_F(SenderTest, send_some_messages__exact_amount_sent)
{
    constexpr size_t amount_to_send = 1;
    set_iterations(amount_to_send);
    const int rc = m_provider.work();
    EXPECT_EQ(amount_to_send, m_sender.sent_count());
    EXPECT_EQ(0, rc);
}

TEST_F(SenderTest, try_to_use_not_ready_sender__got_rc_fail)
{
    m_sender.set_is_ready(false);

    constexpr size_t amount_to_send = 1;
    set_iterations(amount_to_send);
    const auto rc = m_provider.work();
    EXPECT_NE(0, rc);
    EXPECT_EQ(0, m_sender.sent_count());
}

TEST_F(SenderTest, send_one_message__check_message_structure)
{
    constexpr size_t amount_to_send = 1;
    set_iterations(amount_to_send);
    const auto rc = m_provider.work();
    EXPECT_EQ(0, rc);
    EXPECT_EQ(1, m_sender.sent_count());
    const auto & msg = m_sender.last_sent_message();
    EXPECT_TRUE(msg.verify());
    EXPECT_GT(msg.timestamp(), 0);
}

}
