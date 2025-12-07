CC = gcc
CFLAGS = -std=c11 -D_POSIX_C_SOURCE=200809L -Wall -Wextra -Werror -pedantic
TARGET = s21_grep
SRC_DIR = .
OBJ_DIR = obj

SOURCES = main.c \
          file_read_grep.c \
          flag_count_only.c \
          flag_files_with_matches.c \
          flag_ignore_case.c \
          flag_invert_match.c \
          flag_line_number.c \
          flag_no_filename.c \
          flag_only_matching.c \
          flag_pattern_flag.c \
          flag_pattern_from_file.c \
          flag_quiet_mode.c \
          initialize_options.c \
          process_arguments.c \
          regex_utils.c

OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET) test_results.log

rebuild: clean all

# Автоматически дает права на выполнение тестовому скрипту и запускает его
test: $(TARGET)
	@chmod +x test_runner.sh 2>/dev/null || true
	@echo "Запуск тестов..."
	@./test_runner.sh

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET) "test" test_files/test1.txt 2>&1 | grep -E "ERROR SUMMARY|leak"

.PHONY: all clean rebuild test valgrind