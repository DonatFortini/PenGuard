CXX := g++
GTKMMFLAGS := `pkg-config --libs --cflags gtkmm-3.0`
OPENSSLFLAGS := -lssl -lcrypto
MYSQLFLAGS := $(shell mysql_config --cflags --libs) -lmysqlcppconn

BUILD_DIR := build
BIN_DIR := bin
SRC_DIR := src
DB_DIR := db
COMP_DIR := src/components

# List of headers
HEADERS := $(SRC_DIR)/manager.h $(DB_DIR)/db.h $(COMP_DIR)/passwordBlock.h

$(BUILD_DIR)/$(BIN_DIR)/main: $(BUILD_DIR)/manager.o $(BUILD_DIR)/db.o $(BUILD_DIR)/client.o $(BUILD_DIR)/passwordBlock.o
	$(CXX) -o $@ $(SRC_DIR)/main.cc $^ $(GTKMMFLAGS) $(OPENSSLFLAGS) $(MYSQLFLAGS)

$(BUILD_DIR)/manager.o: $(SRC_DIR)/manager.cc $(HEADERS)
	$(CXX) -c $(SRC_DIR)/manager.cc $(GTKMMFLAGS) -o $(BUILD_DIR)/manager.o

$(BUILD_DIR)/client.o: $(SRC_DIR)/client.cc $(BUILD_DIR)/passwordBlock.o $(HEADERS) 
	$(CXX) -c $(SRC_DIR)/client.cc  $(GTKMMFLAGS) -o $(BUILD_DIR)/client.o 

$(BUILD_DIR)/passwordBlock.o:  $(COMP_DIR)/passwordBlock.cc $(HEADERS)
	$(CXX) -c $(COMP_DIR)/passwordBlock.cc $(GTKMMFLAGS) -o $(BUILD_DIR)/passwordBlock.o

$(BUILD_DIR)/db.o: $(DB_DIR)/db.cpp $(HEADERS)
	$(CXX) -c $(DB_DIR)/db.cpp $(GTKMMFLAGS) -o $(BUILD_DIR)/db.o

clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/$(BIN_DIR)/main

run:
	make clean
	make
	./build/bin/main

.PHONY: all clean run
