#include "../src/utils.hpp"
#include "gtest/gtest.h" 


namespace {
    
    TEST(UtilsTest, CorrectIP) {
        Uint32 result = linbound::stringToIP("255.0.127.1");
        EXPECT_EQ(result, 0xff007f01);
    }
    
    TEST(UtilsTest, BadNumbersIP) {
        EXPECT_EQ(linbound::stringToIP("456.257.12.0"), 0);
        EXPECT_EQ(linbound::stringToIP("123.121.120.257"), 0);
    }
    
    TEST(UtilsTest, NotAnIP) {
        EXPECT_EQ(linbound::stringToIP("fgr.dz"), 0);
        EXPECT_EQ(linbound::stringToIP("..."), 0);
        EXPECT_EQ(linbound::stringToIP("123.124.125.126.127"), 0);
    }
    
    TEST(UtilsTest, EmptyIP) {
        EXPECT_EQ(linbound::stringToIP(""), 0);
    }
}
