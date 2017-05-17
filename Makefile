CFLAGS := -O3 -Wall
CPPFLAGS := -std=c++11

CC := clang
CPPC := clang++

DEP_DIR := dep
SRC_DIR := src

YAJL_DIR := $(DEP_DIR)/yajl-mod
YAJL_API_DIR := $(YAJL_DIR)/api
ARGPARSE_DIR := $(DEP_DIR)/argparse

BINARIES_DIR := bin
OBJECTS_DIR := $(BINARIES_DIR)/obj
DEP_OBJECTS_DIR := $(OBJECTS_DIR)/dep

DEP_SOURCES := $(wildcard $(YAJL_DIR)/*.c)
SRC_SOURCES:= $(wildcard $(SRC_DIR)/*.cpp)

DEP_OBJECTS := $(patsubst $(YAJL_DIR)/%.c,$(DEP_OBJECTS_DIR)/%.o,$(DEP_SOURCES))
SRC_OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJECTS_DIR)/%.o,$(SRC_SOURCES))

all: $(DEP_OBJECTS) $(SRC_OBJECTS)
	mkdir -p $(OBJECTS_DIR)
	$(CPPC) -o bin/jbcc-dump $(DEP_OBJECTS) $(SRC_OBJECTS)

$(DEP_OBJECTS): $(DEP_OBJECTS_DIR)/%.o:$(YAJL_DIR)/%.c
	mkdir -p $(DEP_OBJECTS_DIR)
	$(CC) -c -o $@ $< -I$(YAJL_API_DIR) $(CFLAGS)

$(SRC_OBJECTS): $(OBJECTS_DIR)/%.o:$(SRC_DIR)/%.cpp
	$(CPPC) -c -o $@ $< -I$(ARGPARSE_DIR) -I$(YAJL_API_DIR) $(CFLAGS) $(CPPFLAGS)

clean:
	rm -r $(BINARIES_DIR)