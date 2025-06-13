CXX = g++
CXXFLAGS = -std=c++20 -MMD -ggdb -pedantic

SRC_DIR = src
BUILD_DIR = build
TARGET = UTrello
HOLIDAYS_FILE = holidays.csv
PORT_NUM = 5000

SRC = \
	$(wildcard $(SRC_DIR)/*.cpp) \
	utils/template_parser.cpp \
	utils/response.cpp \
	utils/request.cpp \
	utils/utilities.cpp \
	utils/strutils.cpp \
	server/server.cpp \
	server/route.cpp 

OBJ = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRC))
DEPS = $(OBJ:.o=.d)

ifeq ($(OS),Windows_NT)
	LDLIBS += -l Ws2_32
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET) $(PORT_NUM) $(HOLIDAYS_FILE)

-include $(DEPS)

.PHONY: all clean run
