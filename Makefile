CXX      := g++
CXXFLAGS := -std=c++11
LDFLAGS  := -L/opt/local/lib -larmadillo
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
TARGET   := TECO++
INCLUDE  := -I/opt/local/include/
SRC      := $(wildcard ./src/*.cpp)

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -g -Wall
debug: all

release: CXX = icpc #comment this line to use g++
release: CXXFLAGS += -fast
release: INCLUDE += -I/opt/intel/mkl/include
release: LDFLAGS += -L/opt/intel/mkl/lib -Wl,-rpath,/opt/intel/mkl/lib -lmkl_intel_ilp64 -lmkl_sequential -lmkl_core -lpthread -ldl
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*