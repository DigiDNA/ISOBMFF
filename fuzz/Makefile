# Copyright (c) Meta Platforms, Inc. and its affiliates.

# Include the main project's Makefile configuration
include ../Submodules/makelib/Common.mk

# Fuzzing specific configuration
DIR_SRC := ../ISOBMFF/source/
DIR_INC := ../ISOBMFF/include/
DIR_BUILD_PRODUCTS := ../Build/Release/Products/
DIR_BUILD_FUZZ := ../Build/fuzz/

# Compiler and flags
CC := clang
CXX := clang++
CXXFLAGS := -std=c++14 -I$(DIR_INC) -I$(DIR_SRC) -fsanitize=address,fuzzer,undefined -g -O1
LDFLAGS := -fsanitize=address,fuzzer,undefined $(DIR_BUILD_PRODUCTS)x86_64/libISOBMFF.a -lstdc++ -lpthread

# Fuzzer targets
FUZZERS := Parser_fuzzer META_fuzzer
FUZZ_TARGETS := $(patsubst %,$(DIR_BUILD_FUZZ)%,$(FUZZERS))

# Default target
all: $(FUZZ_TARGETS)

# Create build directory
$(DIR_BUILD_FUZZ):
	@mkdir -p $(DIR_BUILD_FUZZ)

# Rule to build fuzzers
$(DIR_BUILD_FUZZ)%_fuzzer: %_fuzzer.cpp | $(DIR_BUILD_FUZZ)
	@echo "Building fuzzer: $<"
	$(CXX) $(CXXFLAGS) $< $(LDFLAGS) -o $@
	@echo "Fuzzer built successfully: $@"

# Rule to run fuzzers
RUNS?=100
fuzz: $(FUZZ_TARGETS)
	@echo "Running fuzzers..."
	@for fuzzer in $(FUZZERS); do \
		mkdir -p $(DIR_BUILD_FUZZ)corpus/$$fuzzer; \
		$(DIR_BUILD_FUZZ)$$fuzzer -artifact_prefix=corpus/$$fuzzer/ corpus/$$fuzzer -runs=$(RUNS); \
	done

.PHONY: all fuzz
