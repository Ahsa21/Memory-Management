# Compiler and Linking Variables
CC = gcc
CFLAGS = -Wall -fPIC
LIB_NAME = libmemory_manager.so

# Source and Object Files
SRC = memory_manager.c
OBJ = $(SRC:.c=.o)
LINKED_LIST_OBJ = linked_list.o

# Default target
all: $(LIB_NAME) executable_memory_manager executable_linked_list

# Rule to create the dynamic library
$(LIB_NAME): $(OBJ)
	$(CC) -shared -o $@ $(OBJ)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Test executable for the memory manager
executable_memory_manager: test_memory_manager.c $(LIB_NAME)
	$(CC) -o $@ test_memory_manager.c memory_manager.c $(CFLAGS)

# Test executable for the linked list
executable_linked_list: test_linked_list.c linked_list.c memory_manager.c $(LIB_NAME)
	$(CC) -o $@ test_linked_list.c linked_list.c memory_manager.c $(CFLAGS)

# Run all tests
run_tests: run_test_memory_manager run_test_linked_list

# Run the memory manager test
run_test_memory_manager: executable_memory_manager
	./executable_memory_manager

# Run the linked list test
run_test_linked_list: executable_linked_list
	./executable_linked_list

# Clean target to clean up build files
clean:
	rm -f $(OBJ) $(LIB_NAME) $(LINKED_LIST_OBJ) executable_memory_manager executable_linked_list
