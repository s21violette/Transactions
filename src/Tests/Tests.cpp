#include <gtest/gtest.h>

// #include "../ConsoleEngine/ConsoleEngine.h"
#include "../Databases/HashTable/HashTable.h"

char GenerateRandomLetter() { return 'a' + rand() % ('z' - 'a'); }

TEST(HashTable, test) {
    s21::HashTable hash_table;
    for (int i = 0; i < 50; ++i) {
        Values values;
        values.key_ = "key" + std::to_string(i);
        for (int j = 0; j < 2; ++j) {
            values.last_name_ += GenerateRandomLetter();
            values.first_name_ += GenerateRandomLetter();
        }
        values.year_of_birth_ = 1950 + i;
        values.city_ = i % 3 == 0 ? "Казань" : i % 3 == 1 ? "Москва" : "НабережныеЧелны";
        values.number_of_coins_ = i * i * i * i;
        hash_table.Set(values);
    }
    EXPECT_EQ(hash_table.ShowAll().size(), 50);
    for (int i = 0; i < 50; ++i) {
        std::string key = "key" + std::to_string(i);
        Values values = hash_table.Get(key);
        EXPECT_EQ(values.year_of_birth_, 1950 + i);
        EXPECT_EQ(values.number_of_coins_, i * i * i * i);
        EXPECT_TRUE(hash_table.Exists(key));
    }
    for (int i = 0; i < 10; ++i) {
        std::string key;
        for (int j = 0; j < 5; ++j) {
            key += GenerateRandomLetter();
        }
        EXPECT_EQ(hash_table.Get(key).first_name_, "");
        EXPECT_EQ(hash_table.Get(key).city_, "");
        EXPECT_EQ(hash_table.Get(key).number_of_coins_, -1);
        EXPECT_FALSE(hash_table.Exists(key));
    }
    EXPECT_EQ(hash_table.Keys().size(), 50);
    for (int i = 0; i < 20; ++i) {
        std::string key = "key" + std::to_string(i);
        hash_table.Del(key);
        EXPECT_FALSE(hash_table.Exists(key));
    }
    EXPECT_EQ(hash_table.Keys().size(), 30);
    EXPECT_EQ(hash_table.ShowAll().size(), 30);
    for (int i = 20; i < 50; ++i) {
        std::string key = "key" + std::to_string(i);
        Values values = hash_table.Get(key);
        EXPECT_EQ(values.year_of_birth_, 1950 + i);
        EXPECT_EQ(values.number_of_coins_, i * i * i * i);
        EXPECT_TRUE(hash_table.Exists(key));
    }
    for (int i = 20; i < 30; ++i) {
        std::string key = "key" + std::to_string(i);
        Values values;
        values.key_ = key;
        values.last_name_ = values.first_name_ = values.first_name_ = "-";
        values.city_ = "ГГГГГГГ";
        values.year_of_birth_ = -1;
        values.number_of_coins_ = 10000;
        EXPECT_TRUE(hash_table.Update(values));
    }
    for (int i = 20; i < 30; ++i) {
        std::string key = "key" + std::to_string(i);
        Values values = hash_table.Get(key);
        EXPECT_NE(values.last_name_, "-");
        EXPECT_EQ(values.city_, "ГГГГГГГ");
        EXPECT_EQ(values.number_of_coins_, 10000);
        EXPECT_TRUE(values.year_of_birth_ > 0);
    }
    for (int i = 20; i < 30; ++i) {
        std::string key = "key" + std::to_string(i);
        Values values = hash_table.Get(key);
        EXPECT_NE(values.last_name_, "-");
        EXPECT_EQ(values.city_, "ГГГГГГГ");
        EXPECT_EQ(values.number_of_coins_, 10000);
        EXPECT_TRUE(values.year_of_birth_ > 0);
    }
    for (int i = 20; i < 30; ++i) {
        std::string key = "key" + std::to_string(i);
        Values values = hash_table.Get(key);
        EXPECT_EQ(hash_table.Find(values).size(), 1);
        EXPECT_EQ(hash_table.Find(values)[0], values.key_);
    }
    Values values;
    values.key_ = "test";
    values.last_name_ = "aboba";
    values.first_name_ = "aboba";
    values.year_of_birth_ = 2007;
    values.city_ = "Челяба";
    values.ex_ = 4;
    hash_table.Set(values);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    EXPECT_TRUE(hash_table.TTL("test") < 4);
    EXPECT_TRUE(hash_table.TTL("test") > 0);
    EXPECT_TRUE(hash_table.Exists("test"));
    std::this_thread::sleep_for(std::chrono::seconds(3));
    EXPECT_FALSE(hash_table.Exists("test"));
}

TEST(HashTable, UploadExport) {
    s21::HashTable hash_table;
    std::fstream fs1("TextFiles/data.txt"), fs2("TextFiles/data2.txt");
    EXPECT_EQ(hash_table.Upload(fs1), 50);
    EXPECT_EQ(hash_table.Keys().size(), 50);
    EXPECT_EQ(hash_table.ShowAll().size(), 50);
    EXPECT_EQ(hash_table.ShowAll().size(), 50);
    EXPECT_EQ(hash_table.Export(fs2), 50);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}