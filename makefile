CXX := g++
GTKMMFLAGS := `pkg-config --libs --cflags gtkmm-3.0`

BUILD_DIR := build
BIN_DIR := bin
SRC_DIR := src

$(BIN_DIR)/main: $(BUILD_DIR)/manager.o 
	$(CXX)  -o $(BIN_DIR)/main $(SRC_DIR)/main.cc $(BUILD_DIR)/manager.o  $(GTKMMFLAGS)

$(BUILD_DIR)/manager.o: $(SRC_DIR)/manager.cc $(SRC_DIR)/manager.h
	$(CXX) -c $(SRC_DIR)/manager.cc  $(GTKMMFLAGS) -o $(BUILD_DIR)/manager.o

clean:
	rm -rf $(BUILD_DIR)/*.o $(BIN_DIR)/main

run:
	./bin/main

.PHONY: all clean print-working-dir
