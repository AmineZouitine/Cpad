#pragma once

#include <gtest/gtest.h>
#include <string>

#include "../src/convertor.hh"
#include "../src/utils.hh"

TEST(convertor, easy_parsing)
{
    std::string path = "./test-ressources/.cpad_easy";
    bool emoji = true;
    auto map = Convertor::instance().read(path, emoji);

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

TEST(convertor, easy_combo)
{
    std::string path = "./test-ressources/.cpad_combo";

    bool emoji = true;
    auto map = Convertor::instance().read(path, emoji);

    ASSERT_EQ(map.size(), 1);
    ASSERT_TRUE(map.find(".") != map.end());

    ASSERT_EQ(map["."].get_elements().size(), 5);

    ASSERT_TRUE(map["."].get_elements()[0].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[0].get_name(), "git commands");

    ASSERT_TRUE(map["."].get_elements()[1].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[1].get_name(), "test");

    ASSERT_FALSE(map["."].get_elements()[2].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[2].get_name(), "ls -a");

    ASSERT_FALSE(map["."].get_elements()[3].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[3].get_name(), "ls");

    ASSERT_TRUE(map["."].get_elements()[4].get_is_combo());
    ASSERT_EQ(map["."].get_elements()[4].get_name(), "");
    ASSERT_EQ(map["."].get_elements()[4].get_combo_elements_().size(), 2);

    ASSERT_FALSE(
        map["."].get_elements()[4].get_combo_elements_()[0].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[4].get_combo_elements_()[0].get_name(),
              "ls -a");

    ASSERT_FALSE(
        map["."].get_elements()[4].get_combo_elements_()[1].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[4].get_combo_elements_()[1].get_name(),
              "echo OUI");
}

TEST(convertor, easy_combo_name)
{
    std::string path = "./test-ressources/.cpad_combo_name";
    bool emoji = true;
    auto map = Convertor::instance().read(path, emoji);

    ASSERT_EQ(map.size(), 1);
    ASSERT_TRUE(map.find(".") != map.end());

    ASSERT_EQ(map["."].get_elements().size(), 5);

    ASSERT_TRUE(map["."].get_elements()[0].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[0].get_name(), "git commands");

    ASSERT_TRUE(map["."].get_elements()[1].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[1].get_name(), "test");

    ASSERT_FALSE(map["."].get_elements()[2].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[2].get_name(), "ls -a");

    ASSERT_FALSE(map["."].get_elements()[3].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[3].get_name(), "ls");

    ASSERT_TRUE(map["."].get_elements()[4].get_is_combo());
    ASSERT_EQ(map["."].get_elements()[4].get_name(), "LE SAINT COMBO");
    ASSERT_EQ(map["."].get_elements()[4].get_combo_elements_().size(), 2);

    ASSERT_FALSE(
        map["."].get_elements()[4].get_combo_elements_()[0].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[4].get_combo_elements_()[0].get_name(),
              "ls -a");

    ASSERT_FALSE(
        map["."].get_elements()[4].get_combo_elements_()[1].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[4].get_combo_elements_()[1].get_name(),
              "echo OUI");
}

TEST(convertor, medium)
{
    std::string path = "./test-ressources/.cpad_medium";
    bool emoji = true;
    auto map = Convertor::instance().read(path, emoji);

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

TEST(convertor, write_easy)
{
    std::string path1 = "./test-ressources/.cpad_easy";
    std::string path = "./test-ressources/.cpad_easy_test1";
    bool emoji = true;
    auto map_init = Convertor::instance().read(path1, emoji);
    Convertor::instance().write(map_init, path, false);
    auto map = Convertor::instance().read(path, emoji);

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

TEST(convertor, write_medium)
{
    std::string path1 = "./test-ressources/.cpad_medium";
    std::string path = "./test-ressources/.cpad_medium_test1";
    bool emoji = true;
    auto map_init = Convertor::instance().read(path1, emoji);
    Convertor::instance().write(map_init, path, false);
    auto map = Convertor::instance().read(path, emoji);

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

TEST(convertor, write_add_command)
{
    std::string path1 = "./test-ressources/.cpad_medium";
    std::string path = "./test-ressources/.cpad_medium_test1";

    bool emoji = true;
    auto map = Convertor::instance().read(path1, emoji);

    std::string parent_folder = ".";
    std::string command_name = "echo new command";
    Convertor::instance().add_command(map, parent_folder, command_name);

    Convertor::instance().write(map, path, false);

    ASSERT_EQ(map.size(), 2);

    ASSERT_TRUE(map.find(".") != map.end());
    ASSERT_EQ(map["."].get_elements().size(), 5);

    ASSERT_TRUE(map["."].get_elements()[0].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[0].get_name(), "git commands");

    ASSERT_TRUE(map["."].get_elements()[1].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[1].get_name(), "test");

    ASSERT_FALSE(map["."].get_elements()[2].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[2].get_name(), "ls -a");

    ASSERT_FALSE(map["."].get_elements()[3].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[3].get_name(), "ls");

    ASSERT_FALSE(map["."].get_elements()[4].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[4].get_name(), "echo new command");

    ASSERT_TRUE(map.find("git commands") != map.end());
    ASSERT_EQ(map["git commands"].get_elements().size(), 1);

    ASSERT_FALSE(map["git commands"].get_elements()[0].get_is_folder());
    ASSERT_EQ(map["git commands"].get_elements()[0].get_name(), "git add *");
}

TEST(convertor, write_remove_command)
{
    std::string path1 = "./test-ressources/.cpad_medium";
    std::string path = "./test-ressources/.cpad_medium_test1";

    bool emoji = true;
    auto map = Convertor::instance().read(path1, emoji);

    std::string parent_folder = ".";
    Convertor::instance().remove_command(map, parent_folder, 4);

    Convertor::instance().write(map, path, false);

    ASSERT_EQ(map.size(), 2);

    ASSERT_TRUE(map.find(".") != map.end());
    ASSERT_EQ(map["."].get_elements().size(), 3);

    ASSERT_TRUE(map["."].get_elements()[0].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[0].get_name(), "git commands");

    ASSERT_TRUE(map["."].get_elements()[1].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[1].get_name(), "test");

    ASSERT_FALSE(map["."].get_elements()[2].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[2].get_name(), "ls -a");

    ASSERT_TRUE(map.find("git commands") != map.end());
    ASSERT_EQ(map["git commands"].get_elements().size(), 1);

    ASSERT_FALSE(map["git commands"].get_elements()[0].get_is_folder());
    ASSERT_EQ(map["git commands"].get_elements()[0].get_name(), "git add *");
}

TEST(convertor, write_add_folder)
{
    std::string path1 = "./test-ressources/.cpad_medium";
    std::string path = "./test-ressources/.cpad_medium_test1";

    bool emoji = true;
    auto map = Convertor::instance().read(path1, emoji);

    std::string parent_folder = ".";
    std::string folder_name = "New folder";
    Convertor::instance().add_folder(map, parent_folder, folder_name);
    Convertor::instance().write(map, path, false);

    ASSERT_EQ(map.size(), 3);

    ASSERT_TRUE(map.find(".") != map.end());
    ASSERT_EQ(map["."].get_elements().size(), 5);

    ASSERT_TRUE(map["."].get_elements()[0].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[0].get_name(), "git commands");

    ASSERT_TRUE(map["."].get_elements()[1].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[1].get_name(), "test");

    ASSERT_FALSE(map["."].get_elements()[2].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[2].get_name(), "ls -a");

    ASSERT_FALSE(map["."].get_elements()[3].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[3].get_name(), "ls");

    ASSERT_TRUE(map["."].get_elements()[4].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[4].get_name(), "New folder");

    ASSERT_TRUE(map.find("git commands") != map.end());
    ASSERT_EQ(map["git commands"].get_elements().size(), 1);

    ASSERT_FALSE(map["git commands"].get_elements()[0].get_is_folder());
    ASSERT_EQ(map["git commands"].get_elements()[0].get_name(), "git add *");

    ASSERT_TRUE(map.find("New folder") != map.end());
    ASSERT_EQ(map["New folder"].get_elements().size(), 0);
}

TEST(convertor, write_remove_folder)
{
    std::string path1 = "./test-ressources/.cpad_medium";
    std::string path = "./test-ressources/.cpad_medium_test1";

    bool emoji = true;
    auto map = Convertor::instance().read(path1, emoji);

    std::string parent_folder = ".";
    std::string folder_name = "New folder";
    Convertor::instance().add_folder(map, parent_folder, folder_name);
    Convertor::instance().remove_folder(map, parent_folder, folder_name);
    Convertor::instance().write(map, path, false);

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

TEST(convertor, write_reset_folder)
{
    std::string path1 = "./test-ressources/.cpad_medium";
    std::string path = "./test-ressources/.cpad_medium_test1";

    bool emoji = true;
    auto map = Convertor::instance().read(path1, emoji);

    std::string parent_folder = ".";
    Convertor::instance().reset_folder(map, parent_folder);
    Convertor::instance().write(map, path, false);

    ASSERT_EQ(map.size(), 1);

    ASSERT_TRUE(map.find(".") != map.end());
    ASSERT_EQ(map["."].get_elements().size(), 0);
}

TEST(convertor, write_reset_all)
{
    std::string path1 = "./test-ressources/.cpad_medium";
    std::string path = "./test-ressources/.cpad_medium_test1";

    bool emoji = true;
    auto map = Convertor::instance().read(path1, emoji);

    std::string parent_folder = ".";
    Convertor::instance().reset_all(map);
    Convertor::instance().write(map, path, false);

    ASSERT_EQ(map.size(), 1);

    ASSERT_TRUE(map.find(".") != map.end());
    ASSERT_EQ(map["."].get_elements().size(), 0);
}

TEST(convertor, write_easy_combo)
{
    std::string path1 = "./test-ressources/.cpad_combo";
    std::string path = "./test-ressources/.cpad_easy_test1";

    bool emoji = true;
    auto map_init = Convertor::instance().read(path1, emoji);
    Convertor::instance().write(map_init, path, false);
    auto map = Convertor::instance().read(path, emoji);

    ASSERT_EQ(map.size(), 1);
    ASSERT_TRUE(map.find(".") != map.end());

    ASSERT_TRUE(map["."].get_elements()[0].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[0].get_name(), "git commands");

    ASSERT_TRUE(map["."].get_elements()[1].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[1].get_name(), "test");

    ASSERT_FALSE(map["."].get_elements()[2].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[2].get_name(), "ls -a");

    ASSERT_FALSE(map["."].get_elements()[3].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[3].get_name(), "ls");

    ASSERT_TRUE(map["."].get_elements()[4].get_is_combo());
    ASSERT_EQ(map["."].get_elements()[4].get_name(), "");
    ASSERT_EQ(map["."].get_elements()[4].get_combo_elements_().size(), 2);
}

TEST(convertor, write_name_combo)
{
    std::string path1 = "./test-ressources/.cpad_combo_name";
    std::string path = "./test-ressources/.cpad_easy_test1";

    bool emoji = true;
    auto map_init = Convertor::instance().read(path1, emoji);
    Convertor::instance().write(map_init, path, false);
    auto map = Convertor::instance().read(path, emoji);

    ASSERT_EQ(map.size(), 1);
    ASSERT_TRUE(map.find(".") != map.end());

    ASSERT_TRUE(map["."].get_elements()[0].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[0].get_name(), "git commands");

    ASSERT_TRUE(map["."].get_elements()[1].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[1].get_name(), "test");

    ASSERT_FALSE(map["."].get_elements()[2].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[2].get_name(), "ls -a");

    ASSERT_FALSE(map["."].get_elements()[3].get_is_folder());
    ASSERT_EQ(map["."].get_elements()[3].get_name(), "ls");

    ASSERT_TRUE(map["."].get_elements()[4].get_is_combo());
    ASSERT_EQ(map["."].get_elements()[4].get_name(), "LE SAINT COMBO");
    ASSERT_EQ(map["."].get_elements()[4].get_combo_elements_().size(), 2);
}
