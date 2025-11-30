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
    
    # Запуск s21_grep с обработкой ошибок сегментации
    if ! eval "$s21_cmd" > "$s21_stdout" 2> "$s21_stderr"; then
        echo $? > "$s21_exit"
    else
        echo $? > "$s21_exit"
    fi
    
    # Запуск реального grep
    eval "$real_cmd" > "$real_stdout" 2> "$real_stderr"
    echo $? > "$real_exit"
    
    # Сравнение результатов с учетом особенностей
    diff -q "$s21_stdout" "$real_stdout" >/dev/null 2>&1
    local stdout_diff=$?
    
    # Игнорируем некоторые различия в stderr
    cat "$s21_stderr" | grep -v "segmentation fault" | grep -v "error" > "$s21_stderr.filtered"
    cat "$real_stderr" | grep -v "segmentation fault" | grep -v "error" > "$real_stderr.filtered"
    
    diff -q "$s21_stderr.filtered" "$real_stderr.filtered" >/dev/null 2>&1
    local stderr_diff=$?
    rm -f "$s21_stderr.filtered" "$real_stderr.filtered"
    
    # Сравнение exit codes с учетом допустимых различий
    local s21_code=$(cat "$s21_exit")
    local real_code=$(cat "$real_exit")
    
    local exit_diff=0
    if [ $s21_code -eq 139 ]; then
        # Ошибка сегментации - всегда считаем провалом
        exit_diff=1
    elif [ $s21_code -eq 1 ] && [ $real_code -eq 1 ]; then
        # Оба вернули 1 - совпадение
        exit_diff=0
    elif [ $s21_code -ne $real_code ]; then
        exit_diff=1
    fi
    
    return $((stdout_diff + stderr_diff + exit_diff))
}