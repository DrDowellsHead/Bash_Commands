CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g -D_POSIX_C_SOURCE=200809L
LDFLAGS = 
INCLUDES = -I.
SOURCES = main.c initialize_options.c process_arguments.c file_read_grep.c \
          flag_pattern_flag.c flag_ignore_case.c flag_invert_match.c \
          flag_count_only.c flag_files_with_matches.c flag_line_number.c \
          flag_no_filename.c flag_quiet_mode.c flag_pattern_from_file.c \
          flag_only_matching.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = s21_grep

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

set_permissions:
	chmod +x tests/integration/*.sh
	chmod +x tests/utils/*.sh

test: $(EXECUTABLE)
	@echo "🧪 Запуск интеграционных тестов..."
	@cd tests/integration && bash run_all_tests.sh

.PHONY: all clean