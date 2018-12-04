#include "../settings.hpp"
#include "gtest/gtest.h" 


namespace {
    
    TEST(SettingsTest, DefaultWidth) {
        Settings* set = Settings::getInstance();
        EXPECT_EQ(set->getWidth(), 800);
    }
    
    TEST(SettingsTest, DefaultHeight) {
        Settings* set = Settings::getInstance();
        EXPECT_EQ(set->getHeight(), 600);
    }
    
}

/* int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
} */
