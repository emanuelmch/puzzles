# Generic phony targets
all: debug release tests

clean:
	rm -rf build

check: tests
	cd build/debug && ctest -E all_tests

checkv: tests
	cd build/debug && ctest -E all_tests -V

debug: build/debug/Makefile
	cmake --build build/debug --target puzzles

release: build/release/Makefile
	cmake --build build/release --target puzzles

run: debug
	./build/debug/puzzles

tests: build/debug/Makefile
	cmake --build build/debug --target build_tests

.PHONY: all clean check checkv debug release run tests

# Specific file targets
build/debug/Makefile: CMakeLists.txt
	@#The -B parameter was only introduced in cmake 3.13
	@#cmake . -DCMAKE_BUILD_TYPE=Debug -B build/debug
	@mkdir -p build/debug
	cd build/debug && cmake ../.. -DCMAKE_BUILD_TYPE=Debug

build/release/Makefile: CMakeLists.txt
	@#The -B parameter was only introduced in cmake 3.13
	@#cmake . -DCMAKE_BUILD_TYPE=Release -B build/release
	@mkdir -p build/release
	cd build/release && cmake ../.. -DCMAKE_BUILD_TYPE=Release
