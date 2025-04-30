#-------------------------------------------------------------------------------
# The MIT License (MIT)
# 
# Copyright (c) 2017 DigiDNA - www.digidna.net
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# makelib configuration
#-------------------------------------------------------------------------------

BUILD_LEGACY_ARCHS  := 0

include Submodules/makelib/Common.mk

PRODUCT             := ISOBMFF
PRODUCT_LIB         := libISOBMFF
PRODUCT_DYLIB       := libISOBMFF
PRODUCT_FRAMEWORK   := ISOBMFF
PREFIX_DYLIB        := /usr/local/lib/
PREFIX_FRAMEWORK    := /Library/Frameworks/
DIR_INC             := ISOBMFF/include/
DIR_SRC             := ISOBMFF/source/
DIR_RES             := ISOBMFF/
DIR_TESTS           := ISOBMFF-Tests/
EXT_C               := .c
EXT_CPP             := .cpp
EXT_M               := .m
EXT_MM              := .mm
EXT_H               := .hpp
CC                  := clang
FLAGS_OPTIM         := Os
FLAGS_WARN          := -Werror -Wall
FLAGS_STD_C         := c99
FLAGS_STD_CPP       := c++14
FLAGS_OTHER         := -fno-strict-aliasing
FLAGS_C             := 
FLAGS_CPP           := -x c++ -stdlib=libc++
FLAGS_M             := -fobjc-arc
FLAGS_MM            := -fobjc-arc
XCODE_PROJECT       := ISOBMFF.xcodeproj
XCODE_TEST_SCHEME   := ISOBMFF

FILES_C             := 
FILES_C_EXCLUDE     := 

FILES_CPP           := $(call GET_CPP_FILES, $(DIR_SRC))
FILES_CPP_EXCLUDE   := 

FILES_M             := 
FILES_M_EXCLUDE     := 

FILES_MM            := 
FILES_MM_EXCLUDE    := 

LIBS                := -lc++

FILES               := $(filter-out $(FILES_C_EXCLUDE),$(FILES_C))      \
                       $(filter-out $(FILES_CPP_EXCLUDE),$(FILES_CPP))  \
                       $(filter-out $(FILES_M_EXCLUDE),$(FILES_M))      \
                       $(filter-out $(FILES_MM_EXCLUDE),$(FILES_MM))
FILES_TESTS         := $(call GET_CPP_FILES, $(DIR_TESTS))

include Submodules/makelib/Targets.mk

# Directory for test executables
DIR_BUILD_TESTS     := Build/Tests/

# Custom target for unit tests
unittest: $(patsubst $(DIR_TESTS)%.cpp,$(DIR_BUILD_TESTS)%,$(FILES_TESTS))
	@echo "All unit tests built successfully."
	@echo "Run tests with: ./$(DIR_BUILD_TESTS)<test_name>"

# Rule to build each test file
$(DIR_BUILD_TESTS)%: $(DIR_TESTS)%.cpp
	@echo "Building unit test: $<"
	@mkdir -p $(DIR_BUILD_TESTS)
	@g++ -std=$(FLAGS_STD_CPP) -Wall -I$(DIR_INC) \
		$< \
		$(DIR_BUILD_PRODUCTS)x86_64/libISOBMFF.a \
		-L/usr/local/lib \
		-lgtest -lgtest_main -lpthread \
		-o $@
	@echo "Unit test built successfully: $@"

# Override the all target to include unittest
all: release debug unittest

.PHONY: unittest
