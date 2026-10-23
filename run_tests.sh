#!/usr/bin/env bash

# Останавливать выполнение скрипта, если какая-то команда завершилась ошибкой
set -e

echo "=== Запуск успешных тестов ==="
./build/bin/just_simple_test_ok
./build/bin/test_using_simple_test_ok
./build/bin/test_using_gtest_ok

# Если тесты с "failures" ДОЛЖНЫ падать, и это часть проверки:
echo "=== Проверка падающих тестов (ожидаем ошибку) ==="
if ./build/bin/just_simple_test_failures 2>/dev/null; then
    echo "Ошибка: тест just_simple_test_failures успешно выполнился, а должен был упасть!"
    exit 1
else
    echo "Тест just_simple_test_failures упал, как и ожидалось."
fi

if ./build/bin/test_using_simple_test_failures 2>/dev/null; then
    echo "Ошибка: тест test_using_simple_test_failures успешно выполнился, а должен был упасть!"
    exit 1
else
    echo "Тест test_using_simple_test_failures упал, как и ожидалось."
fi

if ./build/bin/test_using_gtest_failures 2>/dev/null; then
    echo "Ошибка: тест test_using_gtest_failures успешно выполнился, а должен был упасть!"
    exit 1
else
    echo "Тест test_using_gtest_failures упал, как и ожидалось."
fi

echo "=== Все тесты успешно прошли проверку! ==="
