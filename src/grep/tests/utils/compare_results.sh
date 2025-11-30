#!/bin/bash
# compare_results.sh - утилита для сравнения результатов

compare_results() {
    local s21_cmd="$1"
    local real_cmd="$2"
    local test_name="$3"
    local test_dir="$4"
    
    local s21_stdout="$test_dir/${test_name}_s21_stdout.txt"
    local s21_stderr="$test_dir/${test_name}_s21_stderr.txt"
    local s21_exit="$test_dir/${test_name}_s21_exit.txt"
    
    local real_stdout="$test_dir/${test_name}_real_stdout.txt"
    local real_stderr="$test_dir/${test_name}_real_stderr.txt"
    local real_exit="$test_dir/${test_name}_real_exit.txt"
    
    # Запуск s21_grep
    eval "$s21_cmd" > "$s21_stdout" 2> "$s21_stderr"
    echo $? > "$s21_exit"
    
    # Запуск реального grep
    eval "$real_cmd" > "$real_stdout" 2> "$real_stderr"
    echo $? > "$real_exit"
    
    # Сравнение результатов
    local stdout_diff=0
    local stderr_diff=0
    local exit_diff=0
    
    # Сравнение stdout с учетом нормализации
    normalize_output "$s21_stdout" > "$s21_stdout.norm"
    normalize_output "$real_stdout" > "$real_stdout.norm"
    
    if ! cmp -s "$s21_stdout.norm" "$real_stdout.norm"; then
        stdout_diff=1
    fi
    
    # Сравнение stderr (игнорируем некоторые сообщения об ошибках)
    normalize_errors "$s21_stderr" > "$s21_stderr.norm"
    normalize_errors "$real_stderr" > "$real_stderr.norm"
    
    if ! cmp -s "$s21_stderr.norm" "$real_stderr.norm"; then
        stderr_diff=1
    fi
    
    # Сравнение exit codes
    if [ "$(cat "$s21_exit")" -ne "$(cat "$real_exit")" ]; then
        # Разрешаем exit code 1 для отсутствующих файлов
        if ! echo "$s21_cmd" | grep -q "non_existent.txt"; then
            exit_diff=1
        fi
    fi
    
    # Очистка временных файлов
    rm -f "$s21_stdout.norm" "$real_stdout.norm"
    rm -f "$s21_stderr.norm" "$real_stderr.norm"
    
    return $((stdout_diff + stderr_diff + exit_diff))
}

normalize_output() {
    local file="$1"
    # Удаляем лишние пробелы в конце строк и пустые строки в конце
    sed -e 's/[[:space:]]*$//' -e :a -e '/^\n*$/{$d;N;ba' -e '}' "$file"
}

normalize_errors() {
    local file="$1"
    # Фильтруем сообщения об ошибках, которые могут отличаться
    grep -v "Permission denied" "$file" 2>/dev/null || true
    grep -v "No such file" "$file" 2>/dev/null || true
    grep -v "binary file" "$file" 2>/dev/null || true
}

print_diff() {
    local test_name="$1"
    local test_dir="$2"
    
    echo "🔍 Различия в тесте: $test_name"
    echo ""
    
    # Сравнение stdout
    if [ -f "$test_dir/${test_name}_s21_stdout.txt" ] && [ -f "$test_dir/${test_name}_real_stdout.txt" ]; then
        echo "📋 STDOUT различия:"
        diff -u "$test_dir/${test_name}_s21_stdout.txt" "$test_dir/${test_name}_real_stdout.txt" || true
        echo ""
    fi
    
    # Сравнение stderr
    if [ -f "$test_dir/${test_name}_s21_stderr.txt" ] && [ -f "$test_dir/${test_name}_real_stderr.txt" ]; then
        echo "⚠️ STDERR различия:"
        diff -u "$test_dir/${test_name}_s21_stderr.txt" "$test_dir/${test_name}_real_stderr.txt" || true
        echo ""
    fi
    
    # Сравнение exit codes
    if [ -f "$test_dir/${test_name}_s21_exit.txt" ] && [ -f "$test_dir/${test_name}_real_exit.txt" ]; then
        echo "🔢 Exit code различия:"
        echo "Ваша утилита: $(cat "$test_dir/${test_name}_s21_exit.txt")"
        echo "Реальный grep: $(cat "$test_dir/${test_name}_real_exit.txt")"
        echo ""
    fi
}