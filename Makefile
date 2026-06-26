# Compiler settings
CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -std=c11 -MMD -MP -g
CFLAGS += -D_POSIX_C_SOURCE=200809L

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# Executable name
TARGET := $(BIN_DIR)/cfind

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) -o $@

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories if needed
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Include generated dependency files
-include $(DEPS)

.PHONY: all clean
