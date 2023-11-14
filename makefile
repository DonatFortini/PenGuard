CXX := g++
GTKMMFLAGS := `pkg-config --libs --cflags gtkmm-3.0`
OPENSSLFLAGS := -lssl -lcrypto
MYSQLFLAGS := $(shell mysql_config --cflags --libs) -lmysqlcppconn

BUILD_DIR := build
BIN_DIR := bin
SRC_DIR := src
DB_DIR := db

# List of headers
HEADERS := $(SRC_DIR)/manager.h $(DB_DIR)/db.h

$(BIN_DIR)/main: $(BUILD_DIR)/manager.o $(BUILD_DIR)/db.o
	$(CXX) -o $(BIN_DIR)/main $(SRC_DIR)/main.cc $(BUILD_DIR)/manager.o $(BUILD_DIR)/db.o $(GTKMMFLAGS) $(OPENSSLFLAGS) $(MYSQLFLAGS)

$(BUILD_DIR)/manager.o: $(SRC_DIR)/manager.cc $(HEADERS)
	$(CXX) -c $(SRC_DIR)/manager.cc $(GTKMMFLAGS) -o $(BUILD_DIR)/manager.o

$(BUILD_DIR)/db.o: $(DB_DIR)/db.cpp $(HEADERS)
	$(CXX) -c $(DB_DIR)/db.cpp $(GTKMMFLAGS) -o $(BUILD_DIR)/db.o

clean:
	rm -rf $(BUILD_DIR)/*.o $(BIN_DIR)/main

run:
	./bin/main

.PHONY: all clean run
