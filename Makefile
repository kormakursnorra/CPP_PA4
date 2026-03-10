CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -Isrc

BIN_DIR := bin
OBJ_DIR := obj
TARGET  := hobo_fighters

TARGET_BIN := $(BIN_DIR)/$(TARGET)

SRCS := src/game.cpp \
        src/battle.cpp \
        src/hobos/hobo.cpp \
        src/hobos/player_hobo.cpp \
        src/hobos/enemy_hobo.cpp \
		src/hobos/boss.cpp \
        src/creatures/creature.cpp \
        src/creatures/move.cpp \
        src/stash/zoo.cpp \
		src/stash/inventory.cpp \
        src/ui/battle_menu.cpp \
        src/ui/tui.cpp

OBJS := $(patsubst src/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET_BIN)
	@echo "Build complete: $@"

$(TARGET_BIN): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@chmod +x $@

$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

log:
	$(MAKE) all 2>&1 | tee build.log

run: $(TARGET_BIN)
	./$(TARGET_BIN) $(ARGS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Clean complete"

.PHONY: all clean run