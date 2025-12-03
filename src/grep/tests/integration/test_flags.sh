#!/bin/bash
set -e

source ../utils/compare_results.sh

TEST_DIR="flag_tests_$(date +%s)"
mkdir -p "$TEST_DIR"

S21_GREP="../../s21_grep"
REAL_GREP="grep"

run_flag_test() {
    local flag="$1"
    local pattern="$2"
    local files="$3"
    local test_name="$4"
    
    local s21_cmd="$S21_GREP $flag \"$pattern\" $files"
    local real_cmd="$REAL_GREP $flag \"$pattern\" $files"
    
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

# Тесты для каждого флага
success=0
total=0

# Флаг -i (игнорирование регистра)
run_flag_test "-i" "case" "../test_files/mixed_case.txt" "flag_i_case_sensitive" && ((success++))
((total++))

# Флаг -v (инверсия)
run_flag_test "-v" "apple" "../test_files/simple.txt" "flag_v_invert" && ((success++))
((total++))

# Флаг -c (счетчик)
run_flag_test "-c" "hello" "../test_files/simple.txt" "flag_c_count" && ((success++))
((total++))

# Флаг -l (имена файлов)
run_flag_test "-l" "hello" "../test_files/*.txt" "flag_l_filenames" && ((success++))
((total++))

# Флаг -n (номера строк)
run_flag_test "-n" "hello" "../test_files/simple.txt" "flag_n_line_numbers" && ((success++))
((total++))

# Флаг -h (без имен файлов)
run_flag_test "-h" "hello" "../test_files/simple.txt ../test_files/mixed_case.txt" "flag_h_no_filenames" && ((success++))
((total++))

# Флаг -s (тихий режим)
run_flag_test "-s" "pattern" "../test_files/non_existent.txt" "flag_s_silent" && ((success++))
((total++))

# Флаг -o (только совпадения)
run_flag_test "-o" "hello" "../test_files/simple.txt" "flag_o_only_matches" && ((success++))
((total++))

# Флаг -e (несколько шаблонов)
run_flag_test "-e hello -e world" "" "../test_files/simple.txt" "flag_e_multiple_patterns" && ((success++))
((total++))

# Флаг -f (шаблоны из файла)
run_flag_test "-f ../test_files/patterns.txt" "" "../test_files/simple.txt" "flag_f_file_patterns" && ((success++))
((total++))

echo ""
echo "📊 Отчет по тестам флагов:"
echo "Всего тестов: $total"
echo "Пройдено: $success"
echo "Провалено: $(($total - $success))"

if [ $success -eq $total ]; then
    echo "🎉 Все тесты флагов пройдены!"
    exit 0
else
    echo "💔 Некоторые тесты флагов провалены"
    exit 1
fi