# Makefile for ACM SIMD Workshop

# ** DO NOT CHANGE ANYTHING ON THIS FILE **

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -march=native -lm

# Source files
SCALAR_SRC = main-program-scalar.c
SIMD_SRC = main-program-simd.c

# Output binaries
SCALAR_EXEC = scalar_program
SIMD_EXEC = simd_program

# Default target
all: check_scalar check_simd

# Check and build scalar version
check_scalar:
	@if [ -f $(SCALAR_SRC) ]; then \
       	        $(MAKE) scalar; \
       	else \
       	        echo "Scalar source file $(SCALAR_SRC) not found. Skipping scalar build."; \
       	fi

# Compile scalar version
scalar: $(SCALAR_SRC)
	$(CC) $(SCALAR_SRC) -o $(SCALAR_EXEC) $(CFLAGS)

# Check and build SIMD version
check_simd:
	@if [ -f $(SIMD_SRC) ]; then \
	        $(MAKE) simd; \
	else \
              echo "SIMD source file $(SIMD_SRC) not found. Skipping SIMD build."; \
        fi

# Compile SIMD version
simd: $(SIMD_SRC)
	$(CC) $(SIMD_SRC) -o $(SIMD_EXEC) $(CFLAGS)

# Clean up compiled binaries
clean:
	rm -f $(SCALAR_EXEC) $(SIMD_EXEC)

# Phony targets
.PHONY: all clean check_scalar check_simd scalar simd
