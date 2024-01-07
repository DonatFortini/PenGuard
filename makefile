CXX := g++
GTKMMFLAGS := `pkg-config --libs --cflags gtkmm-3.0`
MYSQLFLAGS := $(shell mysql_config --cflags --libs) -lmysqlcppconn
CRYPTOFLAGS := -I/usr/include/cryptopp -lcryptopp -std=c++17

BUILD_DIR := build
BIN_DIR := bin
SRC_DIR := src
DB_DIR := db
COMP_DIR := src/components

HEADERS := $(SRC_DIR)/utilsCache.h $(SRC_DIR)/manager.h $(SRC_DIR)/client.h $(DB_DIR)/db.h $(COMP_DIR)/passwordBlock.h $(COMP_DIR)/logGenDiag.h 


OBJECTS := $(filter-out $(BUILD_DIR)/main.o,$(patsubst $(SRC_DIR)/%.cc,$(BUILD_DIR)/%.o,$(wildcard $(SRC_DIR)/*.cc))) \
		   $(patsubst $(DB_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(wildcard $(DB_DIR)/*.cpp)) \
		   $(patsubst $(COMP_DIR)/%.cc,$(BUILD_DIR)/%.o,$(wildcard $(COMP_DIR)/*.cc))


$(BUILD_DIR)/$(BIN_DIR)/main: $(OBJECTS)
	$(CXX) -o $@ $(SRC_DIR)/main.cc $^ $(GTKMMFLAGS) $(MYSQLFLAGS) $(CRYPTOFLAGS)


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc $(HEADERS)
	$(CXX) -c $< $(GTKMMFLAGS) -o $@

$(BUILD_DIR)/%.o: $(DB_DIR)/%.cpp $(HEADERS)
	$(CXX) -c $< $(GTKMMFLAGS) -o $@ $(CRYPTOFLAGS)

$(BUILD_DIR)/%.o: $(COMP_DIR)/%.cc $(HEADERS)
	$(CXX) -c $< $(GTKMMFLAGS) -o $@


clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/$(BIN_DIR)/main

run:
	make clean
	make
	./$(BUILD_DIR)/$(BIN_DIR)/main

.PHONY: all clean run
