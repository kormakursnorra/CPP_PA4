CXX := g++ 
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -g

SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := obj
TARGET := game

TARGET_BIN := $(BIN_DIR)/$(TARGET)
TARGET_OBJECT := $(OBJ_DIR)/$(TARGET).o 

TARGET_GAME_SRC := src/game.cpp
ENTITY_SRC := src/entity.cpp
CHARACTER_SRC := src/character.cpp
ENEMY_SRC := src/enemy.cpp
MOVE_SRC := src/move.cpp

ALL_CLASS_SRCS := $(ENTITY_SRC) $(CHARACTER_SRC) $(ENEMY_SRC) $(MOVE_SRC)
ALL_GAME_SRCS := $(TARGET_GAME_SRC) $(ALL_CLASS_SRCS)

ALL_GAME_OBJECTS := $(ALL_GAME_SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(TARGET_BIN)
	@echo "Game executable built"

$(TARGET_BIN): $(ALL_GAME_OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@chmod +x $@
	@echo "All builds complete: $@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I $(SRC_DIR) -c $< -o $@
 
$(BIN_DIR):
	mkdir -p $(BIN_DIR)
 
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run-game: $(TARGET_BIN)
	@echo "Running PokeMen exe."
	./$(TARGET_BIN) $(ARGS)
	
clean: 
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Clean complete"

.PHONY: all clean run-game