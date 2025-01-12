CC = g++
CFLAGS = -O2 -Wall
LDFLAGS =

TARGET = lagswitch

SRC = $(shell find . -name '*.c' -o -name '*.cpp')

OBJ = $(SRC:.c=.o)
OBJ := $(OBJ:.cpp=.o)

INCLUDE_DIRS = $(shell find . -type d ! -path '*/.git*' -printf '-I%p ')

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

gdb: $(TARGET)
	gdb ./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean run gdb
