# Compiler and flags
CC = gcc
CFLAGS = -Wall -O3

# Correctness file
CORRECTNESS_FILE = correctness.csv

# Target executable names
TARGET_MAIN = avl_main_test
TARGET_CORRECT = avl_correct_test

# Source files
SRCS_MAIN = main.c AVL.c
SRCS_CORRECT = correct.c AVL.c

# Object files (replace .c with .o)
OBJS_MAIN = $(SRCS_MAIN:.c=.o)
OBJS_CORRECT = $(SRCS_CORRECT:.c=.o)

# Header files
HDRS = AVL.h

# Default rule to build all targets
all: $(TARGET_MAIN) $(TARGET_CORRECT)

# Rule to build the main target executable
$(TARGET_MAIN): $(OBJS_MAIN)
	$(CC) $(CFLAGS) -o $(TARGET_MAIN) $(OBJS_MAIN)

# Rule to build the correct target executable
$(TARGET_CORRECT): $(OBJS_CORRECT)
	$(CC) $(CFLAGS) -o $(TARGET_CORRECT) $(OBJS_CORRECT)

# Rule to compile source files into object files
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean the build directory
clean:
	rm -f $(OBJS_MAIN) $(OBJS_CORRECT) $(TARGET_MAIN) $(TARGET_CORRECT) $(CORRECTNESS_FILE)

# Rule to run the main executable
run_main: $(TARGET_MAIN)
	./$(TARGET_MAIN)

# Rule to run the correct executable
run_correct: $(TARGET_CORRECT)
	./$(TARGET_CORRECT)