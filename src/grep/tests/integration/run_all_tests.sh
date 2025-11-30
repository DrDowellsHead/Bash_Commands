#!/bin/bash
set -e

# Установка прав на выполнение для всех скриптов
chmod +x generate_test_files.sh
chmod +x test_flags.sh
chmod +x test_combinations.sh
chmod +x test_edge_cases.sh
chmod +x ../utils/compare_results.sh

# Генерация тестовых файлов
echo "🔧 Генерация тестовых файлов..."
./generate_test_files.sh

# Запуск всех тестов
echo ""
echo "🚀 Запуск всех интеграционных тестов..."
echo "========================================"

# Переменные для статистики
total_tests=0
passed_tests=0
failed_tests=0

# Функция для запуска группы тестов
run_test_suite() {
    local script="$1"
    local name="$2"
    
    echo ""
    echo "🧪 $name"
    echo "────────────────────────────────────────"
    
    if bash "$script"; then
        echo "✅ $name: ВСЕ ТЕСТЫ ПРОЙДЕНЫ"
        return 0
    else
        echo "❌ $name: НЕКОТОРЫЕ ТЕСТЫ ПРОВАЛЕНЫ"
        return 1
    fi
}

# Запуск тестов флагов
if run_test_suite "test_flags.sh" "Тесты отдельных флагов"; then
    ((passed_tests+=10))
else
    ((failed_tests+=10))
fi
((total_tests+=10))

# Запуск тестов комбинаций
if run_test_suite "test_combinations.sh" "Тесты комбинаций флагов"; then
    ((passed_tests+=10))
else
    ((failed_tests+=10))
fi
((total_tests+=10))

# Запуск тестов крайних случаев
if run_test_suite "test_edge_cases.sh" "Тесты крайних случаев"; then
    ((passed_tests+=10))
else
    ((failed_tests+=10))
fi
((total_tests+=10))

echo ""
echo "🎯 ФИНАЛЬНЫЙ ОТЧЕТ"
echo "========================================"
echo "Всего тестов: $total_tests"
echo "Пройдено: $passed_tests"
echo "Провалено: $failed_tests"
echo ""

if [ $failed_tests -eq 0 ]; then
    echo "🎉🎉🎉 ПОЗДРАВЛЯЕМ! ВСЕ ИНТЕГРАЦИОННЫЕ ТЕСТЫ ПРОЙДЕНЫ! 🎉🎉🎉"
    echo "Ваша утилита s21_grep полностью соответствует поведению реального grep!"
    exit 0
else
    echo "💔 Некоторые тесты провалены. Пожалуйста, проверьте вывод выше для деталей."
    echo "Для отладки вы можете запустить отдельные тесты:"
    echo "  cd tests/integration"
    echo "  bash test_flags.sh"
    echo "  bash test_combinations.sh"
    echo "  bash test_edge_cases.sh"
    exit 1
fi