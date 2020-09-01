#include <SDL2/SDL.h>
#include <string>
#include "../src/gamemap.hpp"
#include "gtest/gtest.h"

namespace {
    TEST(GameMapTest, Loading) {
        GameMap map{ "abyss" };
        EXPECT_EQ(map.getName(), "Abyss");
        EXPECT_FALSE(map.getPathToBack().find("background.jpg") == std::string::npos);
        EXPECT_FALSE(map.getPathToPreview().find("preview.jpg") == std::string::npos);
        EXPECT_FALSE(map.getPathToFrontA().find("foreground.png") == std::string::npos);
    }
}
