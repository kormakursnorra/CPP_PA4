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
PLAYER_SRC := src/player.cpp
ENEMY_SRC := src/enemy.cpp
MOVE_SRC := src/move.cpp
CREATURE_SRC := src/creature.cpp
ZOO_SRC := src/zoo.cpp

ENTITIES_SRCS := $(ENTITY_SRC) $(PLAYER_SRC) $(ENEMY_SRC) $(CREATURE_SRC)

ALL_CLASS_SRCS := $(ENTITIES_SRCS) $(MOVE_SRC) $(ZOO_SRC)
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
	@echo "Running Game exe."
	./$(TARGET_BIN) $(ARGS)
	
clean: 
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Clean complete"

.PHONY: all clean run-game