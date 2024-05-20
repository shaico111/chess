CC = gcc
CFLAGS = -Iinclude -g -Wall

# Define your source and object directories
SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = tests

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

# Executable for the main application
EXEC = chessSim

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# Rule to compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Test executable rule
test: $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $^ -o run_tests
	./run_tests

# Rule to compile test object files
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(OBJ_DIR)/*.o run_tests
