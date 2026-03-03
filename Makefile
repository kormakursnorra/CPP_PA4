CXX := g++ 
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -g

SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := obj

TARGET := game 
TARGET_BIN := $(BIN_DIR)/$(TARGET)

TARGET_SOURCES := src/game.cpp

TARGET_OBJECTS := $(TARGET_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(TARGET_BIN)
	@echo " Game executable built"

$(TARGET_BIN): $(TARGET_OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@chmod +x $@
	@echo "Build of game complete: $@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
    @mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I $(SRC_DIR) -c $< -o $@
 
$(BIN_DIR):
    mkdir -p $(BIN_DIR)
 
$(OBJ_DIR):
    mkdir -p $(OBJ_DIR)

clean: 
	rmd -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Clean complete"

rebuild: 
	clean all

.PHONY: all test clean rebuild list