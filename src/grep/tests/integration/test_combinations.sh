#!/bin/bash
set -e

source ../utils/compare_results.sh

TEST_DIR="combination_tests_$(date +%s)"
mkdir -p "$TEST_DIR"

S21_GREP="../../s21_grep"
REAL_GREP="grep"

run_combination_test() {
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

# Тесты для комбинаций флагов
success=0
total=0

# Комбинация -i -n
run_combination_test "-i -n" "case" "../test_files/mixed_case.txt" "combo_i_n" && ((success++))
((total++))

# Комбинация -i -v
run_combination_test "-i -v" "hello" "../test_files/mixed_case.txt" "combo_i_v" && ((success++))
((total++))

# Комбинация -n -l
run_combination_test "-n -l" "hello" "../test_files/*.txt" "combo_n_l" && ((success++))
((total++))

# Комбинация -i -n -l
run_combination_test "-i -n -l" "case" "../test_files/*.txt" "combo_i_n_l" && ((success++))
((total++))

# Комбинация -v -c
run_combination_test "-v -c" "apple" "../test_files/simple.txt" "combo_v_c" && ((success++))
((total++))

# Комбинация -i -o
run_combination_test "-i -o" "hello" "../test_files/simple.txt" "combo_i_o" && ((success++))
((total++))

# Комбинация -e -i -n
run_combination_test "-e hello -e world -i -n" "" "../test_files/simple.txt" "combo_e_i_n" && ((success++))
((total++))

# Комбинация -f -i -l
run_combination_test "-f ../test_files/patterns.txt -i -l" "" "../test_files/*.txt" "combo_f_i_l" && ((success++))
((total++))

# Комбинация -i -v -n -h
run_combination_test "-i -v -n -h" "hello" "../test_files/simple.txt ../test_files/mixed_case.txt" "combo_i_v_n_h" && ((success++))
((total++))

# Комбинация -o -n
run_combination_test "-o -n" "[0-9]+" "../test_files/numbers.txt" "combo_o_n_numbers" && ((success++))
((total++))

echo ""
echo "📊 Отчет по тестам комбинаций:"
echo "Всего тестов: $total"
echo "Пройдено: $success"
echo "Провалено: $(($total - $success))"

if [ $success -eq $total ]; then
    echo "🎉 Все тесты комбинаций пройдены!"
    exit 0
else
    echo "💔 Некоторые тесты комбинаций провалены"
    exit 1
fi