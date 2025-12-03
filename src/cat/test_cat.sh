#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

total_tests=0
passed_tests=0

compare_output() {
    local test_name="$1"
    local flags="$2"
    shift 2
    local files="$@"
    
    ((total_tests++))
    
    # Используем массив для правильной передачи файлов
    ./s21_cat $flags $files > our_output.txt 2>&1
    cat $flags $files > std_output.txt 2>&1
    
    if diff -q our_output.txt std_output.txt > /dev/null; then
        echo -e "${GREEN}✓ PASS${NC}: $test_name"
        ((passed_tests++))
        return 0
    else
        echo -e "${RED}✗ FAIL${NC}: $test_name"
        echo "Flags: $flags"
        echo "Files: $files"
        return 1
    fi
}

echo "Создание тестовых файлов..."

# Различные тестовые файлы
echo -e "Line 1\nLine 2\nLine 3" > test_basic.txt
echo -e "First\n\nThird\n\n\nSixth" > test_empty.txt
echo -e "Text\twith\ttabs" > test_tabs.txt
echo -e "Line1\n\nLine2\nLine3\n\n\nLine4" > test_mixed.txt
echo -e "SINGLE" > test_single.txt
touch test_empty_file.txt
echo -n "No newline" > test_no_newline.txt

echo -e "${YELLOW}Расширенное тестирование...${NC}"

# Тестируем все флаги по отдельности
echo -e "\n${YELLOW}Тестирование отдельных флагов:${NC}"

flags=("-b" "-e" "-E" "-n" "-s" "-t" "-T")
for flag in "${flags[@]}"; do
    compare_output "Flag $flag (basic)" "$flag" "test_basic.txt"
    compare_output "Flag $flag (empty)" "$flag" "test_empty.txt"
    compare_output "Flag $flag (tabs)" "$flag" "test_tabs.txt"
done

# Тестируем все возможные парные комбинации
echo -e "\n${YELLOW}Тестирование парных комбинаций:${NC}"

combinations=("-b -e" "-b -n" "-b -s" "-b -t" "-e -n" "-e -s" "-e -t" "-n -s" "-n -t" "-s -t")
for combo in "${combinations[@]}"; do
    compare_output "Combo $combo" "$combo" "test_mixed.txt"
done

# Тестируем тройные комбинации
echo -e "\n${YELLOW}Тестирование тройных комбинаций:${NC}"

triples=("-b -e -n" "-b -e -s" "-b -n -s" "-e -n -s" "-b -e -t" "-e -n -t")
for triple in "${triples[@]}"; do
    compare_output "Triple $triple" "$triple" "test_mixed.txt"
done

# Тестируем несколько файлов - ИСПРАВЛЕНО!
echo -e "\n${YELLOW}Тестирование нескольких файлов:${NC}"

# Без кавычек вокруг нескольких файлов!
compare_output "Multiple files basic" "-n" test_basic.txt test_empty.txt
compare_output "Multiple files with flags" "-b -e" test_tabs.txt test_mixed.txt

# Специальные случаи
echo -e "\n${YELLOW}Специальные случаи:${NC}"

compare_output "Single line file" "-n" "test_single.txt"
compare_output "Empty file" "-n" "test_empty_file.txt"
compare_output "File without newline" "-n" "test_no_newline.txt"

# Тестируем stdin
echo -e "\n${YELLOW}Тестирование stdin:${NC}"

echo "test" | ./s21_cat -n > our_stdin.txt
echo "test" | cat -n > std_stdin.txt
if diff -q our_stdin.txt std_stdin.txt > /dev/null; then
    echo -e "${GREEN}✓ PASS${NC}: stdin with -n"
    ((passed_tests++))
else
    echo -e "${RED}✗ FAIL${NC}: stdin with -n"
fi
((total_tests++))

# Итоги
echo -e "\n${YELLOW}Результаты:${NC}"
echo -e "Пройдено: ${GREEN}$passed_tests${NC} из ${total_tests} тестов"

if [ $passed_tests -eq $total_tests ]; then
    echo -e "${GREEN}Все тесты пройдены!${NC}"
else
    echo -e "${RED}Некоторые тесты не пройдены${NC}"
    exit 1
fi

# Очистка
rm -f test_*.txt *_output.txt