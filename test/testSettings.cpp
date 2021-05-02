#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include "../src/settings.hpp"
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

    TEST(SettingsTest, DefaultMusicVolume) {
        Settings* set = Settings::getInstance();
        EXPECT_EQ(set->getMusicVolume(), 64);
    }

    TEST(SettingsTest, DefaultFXVolume) {
        Settings* set = Settings::getInstance();
        EXPECT_EQ(set->getEffectsVolume(), 64);
    }

    TEST(SettingsTest, SetHeight) {
        Settings* set = Settings::getInstance();
        set->setHeight(742);
        EXPECT_EQ(set->getHeight(), 742);
    }

    TEST(SettingsTest, SetWidth) {
        Settings* set = Settings::getInstance();
        set->setWidth(742);
        EXPECT_EQ(set->getWidth(), 742);
    }
    
}

int main(int argc, char *argv[]) {
  SDL_SetMainReady();

  //Initializing SDL (with no audio because it will not work on Travis)
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      std::cout << "FATAL: Cannot init SDL: " << SDL_GetError();
      return -1;
  }

  ::testing::InitGoogleTest(&argc, argv);
  int result = RUN_ALL_TESTS();

  SDL_Quit();

  return result;
}
