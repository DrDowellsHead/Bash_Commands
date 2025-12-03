CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
TARGET = s21_cat
SOURCES = main.c file_read.c compession_str.c numbering_non_empty.c numbering_all_str.c symbols_end_line.c view_tabs.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

rebuild: clean all

# Тестирование
test: $(TARGET)
	chmod +x test_cat.sh
	./test_cat.sh

.PHONY: all clean rebuild test