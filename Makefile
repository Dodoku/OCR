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
CFLAGS = -Wall -Wextra $(shell sdl2-config --cflags)
LDFLAGS = -export-dynamic $(shell sdl2-config --libs) -lm -lSDL2_image

ALLFILES = $(shell find . -name "*.[ch]")
SRC = $(shell find $(SOURCE_DIR) -name "*.c" ! -name "*main.c")
OBJ = $(patsubst $(SOURCE_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

TOOLS = $(OBJ_DIR)/tools/image.o

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
ocr: module/imageProcess module/imageSpliter module/neuralNetwork module/solver module/imageGenerator

#ocr: $(OBJ)
#	@echo "Linking OCR..."
#	@$(CC) -o $@ $^ $(LDFLAGS)
#	@echo "Build Finished"

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
