#!/bin/bash
set -e

source ../utils/compare_results.sh

TEST_DIR="edge_case_tests_$(date +%s)"
mkdir -p "$TEST_DIR"

S21_GREP="../../s21_grep"
REAL_GREP="grep"

run_edge_case_test() {
    local flags="$1"
    local pattern="$2"
    local files="$3"
    local test_name="$4"
    
    local s21_cmd="$S21_GREP $flags \"$pattern\" $files"
    local real_cmd="$REAL_GREP $flags \"$pattern\" $files"
    
    echo "🧪 Тест: $test_name"
    echo "   Команда: $s21_cmd"
    
    if compare_results "$s21_cmd" "$real_cmd" "$test_name" "$TEST_DIR"; then
        echo "✅ $test_name: PASSED"
        return 0
    else
        echo "❌ $test_name: FAILED"
        print_diff "$test_name" "$TEST_DIR"
        return 1
    fi
}

# Тесты для крайних случаев
success=0
total=0

# Пустой файл
run_edge_case_test "" "hello" "../test_files/empty.txt" "edge_empty_file" && ((success++))
((total++))

# Больной файл
run_edge_case_test "-c" "match" "../test_files/big_file.txt" "edge_big_file" && ((success++))
((total++))

# Бинарный файл
run_edge_case_test "-i" "Hello" "../test_files/binary.bin" "edge_binary_file" && ((success++))
((total++))

# Несуществующий файл
run_edge_case_test "-s" "pattern" "../test_files/non_existent.txt" "edge_non_existent_file" && ((success++))
((total++))

# Пустой шаблон
run_edge_case_test "" "" "../test_files/simple.txt" "edge_empty_pattern" && ((success++))
((total++))

# Специальные символы
run_edge_case_test "-o" "[0-9]{3}-[0-9]{3}-[0-9]{4}" "../test_files/special_chars.txt" "edge_special_chars" && ((success++))
((total++))

# Чтение из stdin
run_edge_case_test "-n" "hello" "" "edge_stdin" && ((success++))
((total++))

# Много файлов
run_edge_case_test "-l" "hello" "../test_files/*.txt" "edge_many_files" && ((success++))
((total++))

# Длинная строка
echo "This is a very long line with hello in the middle and more text after hello and even more text to make it really long" > "$TEST_DIR/long_line.txt"
run_edge_case_test "-o" "hello" "$TEST_DIR/long_line.txt" "edge_long_line" && ((success++))
((total++))

# Нулевой байт в файле
echo -e "Hello\x00World" > "$TEST_DIR/null_byte.txt"
run_edge_case_test "-i" "hello" "$TEST_DIR/null_byte.txt" "edge_null_byte" && ((success++))
((total++))

echo ""
echo "📊 Отчет по тестам крайних случаев:"
echo "Всего тестов: $total"
echo "Пройдено: $success"
echo "Провалено: $(($total - $success))"

if [ $success -eq $total ]; then
    echo "🎉 Все тесты крайних случаев пройдены!"
    exit 0
else
    echo "💔 Некоторые тесты крайних случаев провалены"
    exit 1
fi