// test_main.cpp

#include <gtest/gtest.h>

// Пример функции для тестирования
int add(int a, int b) {
    return a + b;
}

// Тест для функции add
TEST(AdditionTest, HandlesPositiveInput) {
    EXPECT_EQ(add(1, 2), 3);  // Проверка 1 + 2 = 3
    EXPECT_EQ(add(5, 3), 8);  // Проверка 5 + 3 = 8
}

TEST(AdditionTest, HandlesNegativeInput) {
    EXPECT_EQ(add(-1, -1), -2);  // Проверка -1 + (-1) = -2
    EXPECT_EQ(add(-5, 3), -2);   // Проверка -5 + 3 = -2
}

TEST(AdditionTest, HandlesZeroInput) {
    EXPECT_EQ(add(0, 0), 0);    // Проверка 0 + 0 = 0
    EXPECT_EQ(add(0, 5), 5);    // Проверка 0 + 5 = 5
}

// Основная функция для запуска тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);  // Инициализация Google Test
    return RUN_ALL_TESTS();  // Запуск всех тестов
}
