#include "message.h"

#include <gtest/gtest.h>

#include <algorithm>

TEST(MessageTest, timestamp_set_and_get)
{
    const uint64_t original_ts = 45172985;
    Message msg;
    msg.set_timestamp(original_ts);
    EXPECT_EQ(original_ts, msg.timestamp());
}

TEST(MessageTest, verification_header_check)
{
    std::array<char, Message::size()> mem;
    std::fill(mem.begin(), mem.end(), 'A');

    auto * ptr = new (mem.data()) Message();
    ASSERT_TRUE(ptr);
    auto & msg = *ptr;

    EXPECT_FALSE(msg.verify());

    msg.fill_verification_header();
    EXPECT_TRUE(msg.verify());
}
