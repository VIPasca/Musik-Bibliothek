# Makefile wurde mit hilfe von Ai erstellt
DEBUG ?= 1
ENABLE_WARNINGS ?= 1
WARNINGS_AS_ERRORS ?= 0

CXX = g++
CXX_STANDARD = c++17

INCLUDE_DIR = include
SOURCE_DIR = src
TEST_DIR = tests
CATCH_DIR = $(TEST_DIR)/include
BUILD_DIR = build
TEST_BUILD_DIR = $(BUILD_DIR)/tests

ifeq ($(ENABLE_WARNINGS), 1)
    CXX_WARNINGS = -Wall -Wextra -Wpedantic
else
    CXX_WARNINGS =
endif

ifeq ($(WARNINGS_AS_ERRORS), 1)
    CXX_WARNINGS += -Werror
endif

CXXFLAGS = $(CXX_WARNINGS) -std=$(CXX_STANDARD)
CPPFLAGS = -I$(INCLUDE_DIR) -I$(CATCH_DIR)
LDFLAGS += -mconsole -static-libgcc -static-libstdc++

ifeq ($(DEBUG), 1)
    CXXFLAGS += -g -O0
    EXECUTABLE_NAME = mainDebug
    TEST_EXECUTABLE_NAME = testDebug
else
    CXXFLAGS += -O3
    EXECUTABLE_NAME = mainRelease
    TEST_EXECUTABLE_NAME = testRelease
endif

CXX_COMPILER_CALL = $(CXX) $(CXXFLAGS) $(CPPFLAGS)

CXX_SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)
CXX_OBJECTS = $(patsubst $(SOURCE_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CXX_SOURCES))

TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.cpp, $(TEST_BUILD_DIR)/%.o, $(TEST_SOURCES))

MAIN_CPP = main.cpp
MAIN_OBJECT = $(BUILD_DIR)/main.o

all: create build

create:
	@mkdir -p $(BUILD_DIR) $(TEST_BUILD_DIR)

build: $(MAIN_OBJECT) $(CXX_OBJECTS)
	$(CXX_COMPILER_CALL) $(MAIN_OBJECT) $(CXX_OBJECTS) $(LDFLAGS) -o $(BUILD_DIR)/$(EXECUTABLE_NAME)

execute:
	./$(BUILD_DIR)/$(EXECUTABLE_NAME)

clean:
	rm -f $(BUILD_DIR)/*.o
	rm -f $(BUILD_DIR)/$(EXECUTABLE_NAME)
	rm -f $(TEST_BUILD_DIR)/*.o
	rm -f $(TEST_BUILD_DIR)/$(TEST_EXECUTABLE_NAME)

test: create $(TEST_OBJECTS) $(CXX_OBJECTS)
	$(CXX_COMPILER_CALL) $(TEST_OBJECTS) $(CXX_OBJECTS) $(LDFLAGS) -o $(TEST_BUILD_DIR)/$(TEST_EXECUTABLE_NAME)

run_tests: test
	./$(TEST_BUILD_DIR)/$(TEST_EXECUTABLE_NAME)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CXX_COMPILER_CALL) -c $< -o $@

$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX_COMPILER_CALL) -c $< -o $@

$(MAIN_OBJECT): $(MAIN_CPP)
	$(CXX_COMPILER_CALL) -c $< -o $@

.PHONY: create build execute clean test run_tests
