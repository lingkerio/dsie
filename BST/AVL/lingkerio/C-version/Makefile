# Compiler and flags
CC = gcc
CFLAGS = -Wall -O2

# Target executable name
TARGET = avl_test

# Source files
SRCS = main.c AVL.c

# Object files (replace .c with .o)
OBJS = $(SRCS:.c=.o)

# Header files
HDRS = AVL.h

# Default rule to build the target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean the build directory
clean:
	rm -f $(OBJS) $(TARGET)

# Rule to run the executable
run: $(TARGET)
	./$(TARGET)
