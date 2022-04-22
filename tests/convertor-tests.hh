#pragma once

#include <gtest/gtest.h>
#include <string>

#include "../src/convertor.hh"

TEST(convertor, easy_parsing)
{
    std::string path =
        "/home/aminou/Perso/Command-Note-Pad/test-ressources/.cpad_easy";
    auto map = Convertor::instance().read(path);

    ASSERT_EQ(map.size(), 1);
    ASSERT_TRUE(map.find(".") != map.end());

    ASSERT_EQ(map["."].get_elements().size(), 4);

    ASSERT_TRUE(map["."].get_elements()[0].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[0].get_name(), "git commands");

    ASSERT_TRUE(map["."].get_elements()[1].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[1].get_name(), "test");

    ASSERT_FALSE(map["."].get_elements()[2].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[2].get_name(), "ls -a");

    ASSERT_FALSE(map["."].get_elements()[3].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[3].get_name(), "ls");
}

TEST(convertor, medium)
{
    std::string path =
        "/home/aminou/Perso/Command-Note-Pad/test-ressources/.cpad_medium";
    auto map = Convertor::instance().read(path);

    ASSERT_EQ(map.size(), 2);

    ASSERT_TRUE(map.find(".") != map.end());
    ASSERT_EQ(map["."].get_elements().size(), 4);

    ASSERT_TRUE(map["."].get_elements()[0].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[0].get_name(), "git commands");

    ASSERT_TRUE(map["."].get_elements()[1].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[1].get_name(), "test");

    ASSERT_FALSE(map["."].get_elements()[2].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[2].get_name(), "ls -a");

    ASSERT_FALSE(map["."].get_elements()[3].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[3].get_name(), "ls");

    ASSERT_TRUE(map.find("git commands") != map.end());
    ASSERT_EQ(map["git commands"].get_elements().size(), 1);

    ASSERT_FALSE(map["git commands"].get_elements()[0].get_is_folder());
    ASSERT_EQ(map["git commands"].get_elements()[0].get_name(), "git add *");
}