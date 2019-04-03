# Generic phony targets
all: tests release

clean:
	rm -rf build

check: build/Makefile
	make -C build build_tests test

checkv: build/Makefile
	make -C build build_tests
	cd build && ctest -V

release: build/puzzles

run: build/puzzles
	./build/puzzles

tests: build/Makefile
	make -C build build_tests

.PHONY: all clean check checkv release run tests

# Specific file targets
build:
	mkdir build

build/Makefile: build
	cd build && cmake ..

build/puzzles: build/Makefile
	make -C build puzzles
