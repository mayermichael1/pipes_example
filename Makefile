#  use alias bake to generate compile_commands.json
CXX := clang++
CXXFLAGS := -Wall -Wextra -Werror
BUILD_DIR := ./build
LDFLAGS :=
LDLIBS := 
CPPFLAGS :=  -Iinclude/

# add objects here like this:
# OBJECTS += $(BUILD_DIR)/object.o

CXXFLAGS += -O0 -g
#CXXFLAGS += -O2

.PHONY: all
all: $(BUILD_DIR)/cap $(BUILD_DIR)/pipe

$(BUILD_DIR)/cap: $(BUILD_DIR)/cap.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(BUILD_DIR)/cap.o -o $(BUILD_DIR)/cap $(LDFLAGS) $(LDLIBS)

$(BUILD_DIR)/pipe: $(BUILD_DIR)/pipe.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(BUILD_DIR)/pipe.o -o $(BUILD_DIR)/pipe $(LDFLAGS) $(LDLIBS)

$(BUILD_DIR)/cap.o: cap.cpp 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c cap.cpp -o $(BUILD_DIR)/cap.o

$(BUILD_DIR)/pipe.o: pipe.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c pipe.cpp -o $(BUILD_DIR)/pipe.o

.PHONY: clean
clean: 
	rm -rf $(BUILD_DIR)/*
	rm ./compile_commands.json

