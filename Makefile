# Compiler and Linking Variables
CC = gcc
CFLAGS = -Wall -fPIC
LIB_NAME = libmemory_manager.so

# Source and Object Files
SRC = memory_manager.c
OBJ = $(SRC:.c=.o)
LINKED_LIST_SRC = linked_list.c
LINKED_LIST_OBJ = $(LINKED_LIST_SRC:.c=.o)

# Default target
all: clean gitinfo build check

# Rule to create the dynamic library
$(LIB_NAME): $(OBJ)
	$(CC) -shared -o $@ $(OBJ)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

gitinfo:
	@echo "const char *git_date = \"$(shell date)\";" > gitdata.h
	@echo "const char *git_sha = \"$(shell git rev-parse HEAD)\";" >> gitdata.h
	@echo "Git information added."

# Build the memory manager
mmanager: $(LIB_NAME)

# Build the linked list
list: $(LINKED_LIST_OBJ)

# Build the test binaries
test_mmanager: $(LIB_NAME)
	$(CC) $(CFLAGS) -o executable_memory_manager test_memory_manager.c memory_manager.c

test_list: $(LIB_NAME) $(LINKED_LIST_OBJ)
	$(CC) $(CFLAGS) -o executable_linked_list test_linked_list.c $(LINKED_LIST_SRC) memory_manager.c

build: mmanager list test_mmanager test_list
	@echo "Build complete."

# Check for the existence of necessary files
check:
	@if [ ! -f executable_linked_list ]; then \
		echo " Missing; test_linked_list binary, can't continue."; \
		exit 1; \
	fi

# Run tests
run_tests: run_test_mmanager run_test_list

run_test_mmanager:
	./executable_memory_manager

run_test_list:
	./executable_linked_list

# Clean target to clean up build files
clean:
	rm -f $(OBJ) $(LINKED_LIST_OBJ) $(LIB_NAME) executable_memory_manager executable_linked_list
	@echo "Cleaned up all build files."
