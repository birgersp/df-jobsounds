# Default variables
PROJECT_NAME ?= unnamed
BUILD_DIR ?= build
BINARIES_DIR ?= bin
LIB_DIR ?= lib
SOURCES_DIR ?= src
TEST_SOURCES_DIR ?= test
INCLUDE_DIR ?= include
INCLUDES += -I$(INCLUDE_DIR)

# Print variables
$(info PROJECT_NAME: $(PROJECT_NAME))
$(info BUILD_DIR: $(BUILD_DIR))
$(info BINARIES_DIR: $(BINARIES_DIR))
$(info LIB_DIR: $(LIB_DIR))
$(info SOURCES_DIR: $(SOURCES_DIR))
$(info TEST_SOURCES_DIR: $(TEST_SOURCES_DIR))
$(info INCLUDE_DIR: $(INCLUDE_DIR))
$(info INCLUDES: $(INCLUDES))

# Compiler flags
CC_FLAGS += $(INCLUDES) -c -std=c++11 -Werror

# Linker flags
LD_FLAGS += $(LIBRARIES)

# Compiler call
CC = g++

# Archiver call
AR = ar rcsv

# Find all .cpp files in source directory
SOURCES := $(shell (find $(SOURCES_DIR) -name '*.cpp'))

# Set test source files (use sources, remove main.cpp, add test sources directory)
TEST_SOURCES := $(SOURCES)
TEST_SOURCES := $(TEST_SOURCES:$(SOURCES_DIR)/main.cpp=)
TEST_SOURCES += $(shell (find $(TEST_SOURCES_DIR) -name '*.cpp'))

# Generate .o file name for each source file
OBJECTS := $(addprefix $(BUILD_DIR)/,$(SOURCES))
OBJECTS := $(OBJECTS:.cpp=.o)

# Generate .o file names for each test source file
TEST_OBJECTS := $(addprefix $(BUILD_DIR)/,$(TEST_SOURCES))
TEST_OBJECTS := $(TEST_OBJECTS:.cpp=.o)

# Create executable
$(BINARIES_DIR)/$(PROJECT_NAME): $(OBJECTS)
	mkdir -p $(shell dirname $@)
	$(CC) -o $@ $^ $(LD_FLAGS)

# Create test executable
$(BINARIES_DIR)/$(PROJECT_NAME)-test: $(TEST_OBJECTS)
	mkdir -p $(shell dirname $@)
	$(CC) -o $@ $^ $(LD_FLAGS)

# Build object files
$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(shell dirname $@)
	$(CC) $(CC_FLAGS) -o $@ $<

# Create static library
$(LIB_DIR)/lib$(PROJECT_NAME).a: $(OBJECTS)
	mkdir -p $(shell dirname $@)
	$(AR) $@ $^

# Executable target
executable: $(BINARIES_DIR)/$(PROJECT_NAME)

# Executable test target
test: $(BINARIES_DIR)/$(PROJECT_NAME)-test

# Static library target
lib: $(LIB_DIR)/lib$(PROJECT_NAME).a

# Clean (wipe build directory)
clean:
	rm -rf $(BUILD_DIR)/*
	rm $(BINARIES_DIR)/$(PROJECT_NAME)-test*
	rm $(BINARIES_DIR)/$(PROJECT_NAME)*

.PHONY: all clean
