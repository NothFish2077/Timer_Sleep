# ==================================================
# Project Configuration
# ==================================================

TARGET      := sleepr

SRC_DIR     := src
INC_DIR     := include
BUILD_DIR   := build
OBJ_DIR     := $(BUILD_DIR)/obj

CC          := gcc

BUILD       ?= release

# ==================================================
# Compiler Flags
# ==================================================

WARNINGS    := -Wall -Wextra -Wpedantic -Wshadow \
               -Wconversion -Wformat=2

CSTD        := -std=c17

CFLAGS_COMMON := $(CSTD) $(WARNINGS) -I$(INC_DIR)

CFLAGS_DEBUG := -g3 -O0 -DDEBUG
CFLAGS_RELEASE := -O2 -DNDEBUG

ifeq ($(BUILD),debug)
    CFLAGS := $(CFLAGS_COMMON) $(CFLAGS_DEBUG)
else
    CFLAGS := $(CFLAGS_COMMON) $(CFLAGS_RELEASE)
endif

# ==================================================
# Source Discovery
# ==================================================

SRCS := $(shell find $(SRC_DIR) -name '*.c')

OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# ==================================================
# Targets
# ==================================================

.PHONY: all clean debug release run

all: $(BUILD_DIR)/$(TARGET)

debug:
	$(MAKE) BUILD=debug

release:
	$(MAKE) BUILD=release

run: all
	./$(BUILD_DIR)/$(TARGET)

.PHONY: all clean debug release run install uninstall

install: all
	install -Dm755 $(BUILD_DIR)/$(TARGET) /usr/local/bin/$(TARGET)

uninstall:
	rm -f /usr/local/bin/$(TARGET)

# ==================================================
# Linking
# ==================================================

$(BUILD_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $^ -o $@

# ==================================================
# Compilation
# ==================================================

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# ==================================================
# Cleanup
# ==================================================

clean:
	rm -rf $(BUILD_DIR)

# ==================================================
# Dependencies
# ==================================================

-include $(DEPS)
