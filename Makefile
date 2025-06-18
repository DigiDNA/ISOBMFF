

all: none
	echo "use cmake to build"


format:
	clang-format -i -style=google ./include/*h
	clang-format -i -style=google ./src/*cpp
	clang-format -i -style=google ./tools/*cpp


.PHONY: build

build:
	\rm -rf build
	mkdir build
	cd build && CC=clang CXX=clang++ cmake -DCMAKE_BUILD_TYPE=DEBUG -DCMAKE_C_FLAGS_DEBUG="-g -O0 -Wall -Wextra -Wno-unused-parameter -Wshadow -Werror" -DCMAKE_CXX_FLAGS_DEBUG="-g -O0 -Wall -Wextra -Wno-unused-parameter -Wshadow -Werror" ..
	cd build && make -j 8
