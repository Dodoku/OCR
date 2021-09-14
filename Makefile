#
# Makefile of OCR
#
#	make: Build all project
#	make src/<module>: Build module
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
LDFLAGS = -export-dynamic $(shell sdl2-config --libs)

SRC = $(shell find $(SOURCE_DIR) -name "*.c" ! -name "*main.c")
OBJ = $(patsubst $(SOURCE_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

#
# Init
#

init:
	@echo "Initialization..."
	@mkdir -p $(BUILD_DIR) $(OBJ_DIR)

#
# Builds
#
ocr: $(OBJ)
	@$(MAKE) -s init
	@echo "Linking OCR..."
	@$(CC) -o $@ $^ $(LDFLAGS)

#
#Modules
#

.SECONDEXPANSION:
src/%: $$(patsubst $(SOURCE_DIR)/%.c, $(OBJ_DIR)/%.o, $$(shell find $$@ -name "*.c"))
	@$(MAKE) -s init
	@echo "$(shell echo $(shell echo $($^)))"
	@echo "Linking $@..."
	@$(CC) -o $(BUILD_DIR)/$(@F) $^ $(LDFLAGS)

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
