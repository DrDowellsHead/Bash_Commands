# Создай тестовые файлы
echo -e "Hello\nWorld\nHello again" > test1.txt
echo -e "Another\nHello\nTest" > test2.txt

# Запусти тест с разными комбинациями
echo "=== Тест 1: -o ==="
./s21_grep -o "Hello" test1.txt test2.txt
echo "Ожидается:"
grep -o "Hello" test1.txt test2.txt

echo -e "\n=== Тест 2: -o -n ==="
./s21_grep -o -n "Hello" test1.txt test2.txt
echo "Ожидается:"
grep -o -n "Hello" test1.txt test2.txt

echo -e "\n=== Тест 3: -o -n -h ==="
./s21_grep -o -n -h "Hello" test1.txt test2.txt
echo "Ожидается:"
grep -o -n -h "Hello" test1.txt test2.txt

# Очистка
rm test1.txt test2.txt