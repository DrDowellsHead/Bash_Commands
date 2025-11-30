#!/bin/bash

# Цвета для вывода
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Функция для сравнения вывода
compare_output() {
    local test_name="$1"
    local flags="$2"
    local file="$3"
    
    ./s21_cat $flags $file > our_output.txt 2>&1
    cat $flags $file > std_output.txt 2>&1
    
    if diff -q our_output.txt std_output.txt > /dev/null; then
        echo -e "${GREEN}✓ PASS${NC}: $test_name"
        return 0
    else
        echo -e "${RED}✗ FAIL${NC}: $test_name"
        echo "Flags: $flags"
        echo "File: $file"
        echo "--- Our output ---"
        cat our_output.txt
        echo "--- Standard output ---"
        cat std_output.txt
        return 1
    fi
}

# Создаем тестовые файлы
echo "Создание тестовых файлов..."

# Простой файл
echo -e "line 1\nline 2\nline 3" > test1.txt

# Файл с пустыми строками
echo -e "line 1\n\nline 2\n\n\nline 3" > test2.txt

# Файл с табуляциями
echo -e "line with\ttab\nanother\t\tline" > test3.txt

# Файл с разными символами
echo -e "line 1\nline 2\n\nline 4" > test4.txt

# Пустой файл
touch empty.txt

# Файл с одной строкой
echo "single line" > single.txt

echo -e "${YELLOW}Начало тестирования...${NC}"

# Тестируем отдельные флаги
echo -e "\n${YELLOW}Тестирование отдельных флагов:${NC}"

# Флаг -b
compare_output "Flag -b (simple)" "-b" "test1.txt"
compare_output "Flag -b (empty lines)" "-b" "test2.txt"
compare_output "Flag -b (empty file)" "-b" "empty.txt"

# Флаг -e
compare_output "Flag -e (simple)" "-e" "test1.txt"
compare_output "Flag -e (E flag)" "-E" "test1.txt"

# Флаг -n
compare_output "Flag -n (simple)" "-n" "test1.txt"
compare_output "Flag -n (empty lines)" "-n" "test2.txt"

# Флаг -s
compare_output "Flag -s (compression)" "-s" "test2.txt"

# Флаг -t
compare_output "Flag -t (tabs)" "-t" "test3.txt"
compare_output "Flag -t (T flag)" "-T" "test3.txt"

# Тестируем комбинации флагов
echo -e "\n${YELLOW}Тестирование комбинаций флагов:${NC}"

compare_output "Flags -b -e" "-b -e" "test1.txt"
compare_output "Flags -n -e" "-n -e" "test1.txt"
compare_output "Flags -b -n" "-b -n" "test1.txt"
compare_output "Flags -s -n" "-s -n" "test2.txt"
compare_output "Flags -t -e" "-t -e" "test3.txt"
compare_output "Flags -b -e -n" "-b -e -n" "test1.txt"
compare_output "Flags -s -e -t" "-s -e -t" "test4.txt"

# Тестируем несколько файлов
echo -e "\n${YELLOW}Тестирование нескольких файлов:${NC}"

compare_output "Multiple files" "-n" "test1.txt test2.txt"
compare_output "Multiple files with flags" "-b -e" "test1.txt test3.txt"

# Тестируем stdin
echo -e "\n${YELLOW}Тестирование stdin:${NC}"

echo "test input" | ./s21_cat -n > our_stdin.txt
echo "test input" | cat -n > std_stdin.txt

if diff -q our_stdin.txt std_stdin.txt > /dev/null; then
    echo -e "${GREEN}✓ PASS${NC}: stdin with -n"
else
    echo -e "${RED}✗ FAIL${NC}: stdin with -n"
fi

# Тестируем GNU флаги
echo -e "\n${YELLOW}Тестирование GNU-флагов:${NC}"

compare_output "GNU --number-nonblank" "--number-nonblank" "test2.txt"
compare_output "GNU --number" "--number" "test1.txt"
compare_output "GNU --squeeze-blank" "--squeeze-blank" "test2.txt"

# Тестируем крайние случаи
echo -e "\n${YELLOW}Тестирование крайних случаев:${NC}"

# Несуществующий файл
./s21_cat nonexistent.txt > our_error.txt 2>&1
cat nonexistent.txt > std_error.txt 2>&1

if [ $? -eq $? ]; then
    echo -e "${GREEN}✓ PASS${NC}: non-existent file handling"
else
    echo -e "${RED}✗ FAIL${NC}: non-existent file handling"
fi

# Файл без прав на чтение
touch no_read.txt
chmod 000 no_read.txt
./s21_cat no_read.txt > our_perm.txt 2>&1
cat no_read.txt > std_perm.txt 2>&1
chmod 644 no_read.txt

if [ $? -eq $? ]; then
    echo -e "${GREEN}✓ PASS${NC}: permission denied handling"
else
    echo -e "${RED}✗ FAIL${NC}: permission denied handling"
fi

# Очистка
echo -e "\n${YELLOW}Очистка тестовых файлов...${NC}"
rm -f test1.txt test2.txt test3.txt test4.txt empty.txt single.txt no_read.txt
rm -f our_output.txt std_output.txt our_stdin.txt std_stdin.txt our_error.txt std_error.txt our_perm.txt std_perm.txt

echo -e "${GREEN}Тестирование завершено!${NC}"