# Compilers and flags
CC ?= cc
AR = ar
CFLAGS ?= -std=c99
CFLAGS += -Wall -Wextra -Wpedantic -fPIC

# Sources, objects and libraries
INCLUDES = -Iinclude
SRCS = $(wildcard src/*c)
OBJS = $(SRCS:src/%.c=build/%.o)

STATIC_LIB = build/libcds.a
SHARED_LIB = build/libcds.so

# Default target
all: $(STATIC_LIB) $(SHARED_LIB)

# Build object files
build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build static library
$(STATIC_LIB): $(OBJS)
	$(AR) rcs $@ $(OBJS)

# Build shared library
$(SHARED_LIB): $(OBJS)
	$(CC) -shared -o $@ $(OBJS)

# Clean repo
clean:
	rm -rf build

# Add debug flag
debug: CFLAGS += -g -O0
debug: all

.PHONY: all clean debug
