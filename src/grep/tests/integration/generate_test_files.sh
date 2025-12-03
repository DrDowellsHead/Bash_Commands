#!/bin/bash
set -e

TEST_FILES_DIR="../test_files"

mkdir -p "$TEST_FILES_DIR"

# simple.txt - базовый файл
cat > "$TEST_FILES_DIR/simple.txt" << EOF
Hello world
hello everyone
HELLO UNIVERSE
This is a test line
Another hello here
Goodbye world
EOF

# mixed_case.txt - для флага -i
cat > "$TEST_FILES_DIR/mixed_case.txt" << EOF
Case Sensitive
case sensitive
CASE SENSITIVE
CaSe SeNsItIvE
this is a CASE test
EOF

# numbers.txt - для тестов с цифрами
cat > "$TEST_FILES_DIR/numbers.txt" << EOF
12345
67890
123 and 456
789 only
no numbers here
1234567890 all together
EOF

# empty.txt - пустой файл
touch "$TEST_FILES_DIR/empty.txt"

# binary.bin - бинарный файл
echo -e "\x48\x65\x6c\x6c\x6f\x00\x57\x6f\x72\x6c\x64" > "$TEST_FILES_DIR/binary.bin"

# big_file.txt - большой файл
seq 1 1000 | while read i; do
  if [ $((i % 3)) -eq 0 ]; then
    echo "match line $i"
  else
    echo "regular line $i"
  fi
done > "$TEST_FILES_DIR/big_file.txt"

# patterns.txt - файл с паттернами для -f
cat > "$TEST_FILES_DIR/patterns.txt" << EOF
hello
world
universe
EOF

# special_chars.txt - специальные символы
cat > "$TEST_FILES_DIR/special_chars.txt" << EOF
Hello.world
Hello-world
Hello_world
Hello@world
email@example.com
phone: 123-456-7890
path/to/file.txt
C:\\Windows\\System32
EOF

echo "✅ Тестовые файлы успешно сгенерированы"