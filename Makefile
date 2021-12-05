#
# Makefile of OCR
#
#	make: Build all project
#	make module/<module>: Build module
#
#	make init: Creating build folders
#	make clean: Cleaning objects files
#	make cleanall: Cleaning all build files
#
SOURCE_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

CC = gcc

CFLAGS = -Wall -Wextra -pthread $(shell sdl2-config --cflags) `pkg-config --cflags gtk+-3.0`
LDFLAGS = -export-dynamic -pthread $(shell sdl2-config --libs) -lm -lSDL2_image `pkg-config --libs gtk+-3.0`

ALLFILES = $(shell find . -name "*.[ch]")
SRC = $(shell find $(SOURCE_DIR) -name "*.c" ! -name "*main.c")
OBJ = $(patsubst $(SOURCE_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

TOOLS = $(OBJ_DIR)/tools/image.o $(OBJ_DIR)/tools/hough.o

all: init ocr

#
# Init
#

init:
	@echo "Initialization..."
	@mkdir -p $(BUILD_DIR) $(OBJ_DIR)

#
# Format
#

format:
	@echo "Formating Files..."
	@clang-format --style=file -i ${ALLFILES}
#
# Builds
#

ocr: $(OBJ)
	@echo "Linking OCR..."
	@$(CC) -o $@ $^ $(LDFLAGS)
	@make module/neuralNetwork
	@make module/solver
	@make module/imageGenerator
	@echo "Build Finished"

#
#Modules
#

.SECONDEXPANSION:
src-dependencies = $(patsubst $(SOURCE_DIR)/%.c, $(OBJ_DIR)/%.o, $(shell find $(SOURCE_DIR)/$* -name "*.c"))
module/%: $${src-dependencies} ${TOOLS}
	@echo "Linking $@..."
	@$(CC) -o $(BUILD_DIR)/$(@F) $^ $(LDFLAGS)
	@echo "Build Finished"

#
# Templates
#
$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c
	@echo "Building $@..."
	@mkdir -p $(@D)
	@$(CC) -o $@ -c $< $(CFLAGS)

#
# Cleaning
#
clean:
	@echo "Cleaning..."
	@rm -f -r $(OBJ_DIR)
	@rmdir --ignore-fail-on-non-empty $(BUILD_DIR)

cleanall:
	@echo "Cleaning of all build files..."
	@rm -f -r $(BUILD_DIR)
	@rm -f ocr
