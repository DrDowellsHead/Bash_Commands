#!/bin/bash

# Цвета для вывода
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Пути к программам
S21_GREP="./s21_grep"
GREP="grep"
TEST_DIR="test_files"
LOG_FILE="test_results.log"

# Создаем тестовую директорию
mkdir -p $TEST_DIR

# Создаем тестовые файлы
echo "Тест 1: простой текст" > $TEST_DIR/file1.txt
echo "ТЕСТ 2: В ВЕРХНЕМ РЕГИСТРЕ" >> $TEST_DIR/file1.txt
echo "test 3: в нижнем регистре" >> $TEST_DIR/file1.txt
echo "еще один тест для проверки" >> $TEST_DIR/file1.txt
echo "строка без совпадений" >> $TEST_DIR/file1.txt
echo "test with multiple test words test" >> $TEST_DIR/file1.txt

echo "второй файл с тестами" > $TEST_DIR/file2.txt
echo "ТЕСТ во втором файле" >> $TEST_DIR/file2.txt
echo "test lowercase in second file" >> $TEST_DIR/file2.txt
echo "последняя строка" >> $TEST_DIR/file2.txt

# Файл с паттернами для флага -f
echo "test" > $TEST_DIR/patterns.txt
echo "ТЕСТ" >> $TEST_DIR/patterns.txt
echo "тест" >> $TEST_DIR/patterns.txt

# Функция для запуска теста
run_test() {
    local name="$1"
    local s21_cmd="$2"
    local grep_cmd="$3"
    
    echo "Test: $name" | tee -a $LOG_FILE
    echo "Command: $s21_cmd" >> $LOG_FILE
    
    # Запускаем s21_grep
    eval "$S21_GREP $s21_cmd" > s21_output.txt 2>&1
    local s21_exit=$?
    
    # Запускаем оригинальный grep
    eval "$GREP $grep_cmd" > grep_output.txt 2>&1
    local grep_exit=$?
    
    # Нормализуем вывод (убираем лишние пробелы, приводим к одному формату)
    sed -i 's/[[:space:]]*$//' s21_output.txt
    sed -i 's/[[:space:]]*$//' grep_output.txt
    
    # Удалим возможные лишние двоеточия (для приведения к одному формату)
    sed -i 's/::/:/g' s21_output.txt
    sed -i 's/::/:/g' grep_output.txt
    
    # Сравниваем выходные данные
    if diff -q s21_output.txt grep_output.txt > /dev/null; then
        # Сравниваем коды возврата
        if [ $s21_exit -eq $grep_exit ]; then
            echo -e "${GREEN}PASS${NC}: $name" | tee -a $LOG_FILE
            echo "Exit codes match: $s21_exit" >> $LOG_FILE
            return 0
        else
            echo -e "${YELLOW}WARN${NC}: $name - exit codes differ (s21: $s21_exit, grep: $grep_exit)" | tee -a $LOG_FILE
            echo "s21_grep exit code: $s21_exit" >> $LOG_FILE
            echo "grep exit code: $grep_exit" >> $LOG_FILE
            return 1
        fi
    else
        echo -e "${RED}FAIL${NC}: $name" | tee -a $LOG_FILE
        echo "--- Output diff ---" >> $LOG_FILE
        diff s21_output.txt grep_output.txt >> $LOG_FILE
        echo "s21_grep exit code: $s21_exit" >> $LOG_FILE
        echo "grep exit code: $grep_exit" >> $LOG_FILE
        echo "-------------------" >> $LOG_FILE
        return 2
    fi
}

# Очищаем лог файл
echo "Тестовый прогон: $(date)" > $LOG_FILE
echo "=========================" >> $LOG_FILE

total_tests=0
passed_tests=0
warn_tests=0
failed_tests=0

echo "=== Запуск тестов s21_grep ==="

# Базовые тесты
echo "=== Базовые тесты ==="
run_test "Простой поиск" "test $TEST_DIR/file1.txt" "test $TEST_DIR/file1.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

run_test "Поиск нескольких файлов" "test $TEST_DIR/file1.txt $TEST_DIR/file2.txt" "test $TEST_DIR/file1.txt $TEST_DIR/file2.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

# Тесты с флагами
echo "=== Тесты с флагами ==="

run_test "Флаг -i (игнорировать регистр)" "-i TEST $TEST_DIR/file1.txt" "-i TEST $TEST_DIR/file1.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

run_test "Флаг -v (инвертировать)" "-v test $TEST_DIR/file1.txt" "-v test $TEST_DIR/file1.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

run_test "Флаг -c (количество)" "-c test $TEST_DIR/file1.txt" "-c test $TEST_DIR/file1.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

run_test "Флаг -l (только имена файлов)" "-l test $TEST_DIR/file1.txt $TEST_DIR/file2.txt" "-l test $TEST_DIR/file1.txt $TEST_DIR/file2.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

run_test "Флаг -n (номера строк)" "-n test $TEST_DIR/file1.txt" "-n test $TEST_DIR/file1.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

run_test "Флаг -h (без имен файлов)" "-h test $TEST_DIR/file1.txt $TEST_DIR/file2.txt" "-h test $TEST_DIR/file1.txt $TEST_DIR/file2.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

run_test "Флаг -s (тихий режим)" "-s pattern $TEST_DIR/nonexistent.txt" "-s pattern $TEST_DIR/nonexistent.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

run_test "Флаг -e (шаблон)" "-e test $TEST_DIR/file1.txt" "-e test $TEST_DIR/file1.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

run_test "Флаг -f (шаблоны из файла)" "-f $TEST_DIR/patterns.txt $TEST_DIR/file1.txt" "-f $TEST_DIR/patterns.txt $TEST_DIR/file1.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

run_test "Флаг -o (только совпадения)" "-o test $TEST_DIR/file1.txt" "-o test $TEST_DIR/file1.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

# Тесты с комбинациями флагов
echo "=== Тесты с комбинациями флагов ==="

run_test "Флаги -i и -v" "-iv TEST $TEST_DIR/file1.txt" "-iv TEST $TEST_DIR/file1.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

run_test "Флаги -n и -i" "-ni test $TEST_DIR/file1.txt" "-ni test $TEST_DIR/file1.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

run_test "Флаги -c и -v" "-cv test $TEST_DIR/file1.txt" "-cv test $TEST_DIR/file1.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

run_test "Флаги -l и -c" "-cl test $TEST_DIR/file1.txt $TEST_DIR/file2.txt" "-cl test $TEST_DIR/file1.txt $TEST_DIR/file2.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

run_test "Флаги -n и -o" "-no test $TEST_DIR/file1.txt" "-no test $TEST_DIR/file1.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

run_test "Флаги -h и -n" "-hn test $TEST_DIR/file1.txt $TEST_DIR/file2.txt" "-hn test $TEST_DIR/file1.txt $TEST_DIR/file2.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

# Тесты с регулярными выражениями
echo "=== Тесты с регулярными выражениями ==="

run_test "Регулярное выражение ." "'t.st' $TEST_DIR/file1.txt" "'t.st' $TEST_DIR/file1.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

run_test "Регулярное выражение с ^" "'^test' $TEST_DIR/file1.txt" "'^test' $TEST_DIR/file1.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

run_test "Регулярное выражение с []" "'[ТT]est' $TEST_DIR/file1.txt" "'[ТT]est' $TEST_DIR/file1.txt"
case $? in
    0) ((passed_tests++));;
    1) ((warn_tests++));;
    2) ((failed_tests++));;
esac
((total_tests++))

# Тесты со stdin
echo "=== Тесты со stdin ==="
echo -e "line1 test\nline2\nline3 test" | $S21_GREP test > s21_output.txt
echo -e "line1 test\nline2\nline3 test" | $GREP test > grep_output.txt

if diff -q s21_output.txt grep_output.txt > /dev/null; then
    echo -e "${GREEN}PASS${NC}: Чтение из stdin"
    ((passed_tests++))
else
    echo -e "${RED}FAIL${NC}: Чтение из stdin"
    ((failed_tests++))
fi
((total_tests++))

# Очистка временных файлов
rm -f s21_output.txt grep_output.txt
rm -rf $TEST_DIR

# Итоги
echo "================================"
echo "Итоги тестирования:"
echo "Всего тестов: $total_tests"
echo -e "${GREEN}Пройдено: $passed_tests${NC}"
if [ $warn_tests -gt 0 ]; then
    echo -e "${YELLOW}Предупреждений: $warn_tests${NC}"
fi
if [ $failed_tests -gt 0 ]; then
    echo -e "${RED}Провалено: $failed_tests${NC}"
fi

if [ $failed_tests -eq 0 ] && [ $warn_tests -eq 0 ]; then
    echo -e "${GREEN}✓ Все тесты пройдены успешно!${NC}"
    exit 0
elif [ $failed_tests -eq 0 ]; then
    echo -e "${YELLOW}⚠ Есть предупреждения. Проверьте $LOG_FILE для деталей${NC}"
    exit 0
else
    echo -e "${RED}✗ Есть проваленные тесты. Проверьте $LOG_FILE для деталей${NC}"
    exit 1
fi