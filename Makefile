# Generic phony targets
all: debug_all release

clean:
	rm -rf build

check: build/debug/Makefile
	cmake --build build/debug --target check -- --no-print-directory

# Debug targets
debug: build/debug/Makefile
	cmake --build build/debug --target puzzles -- --no-print-directory

debug_all: build/debug/Makefile
	cmake --build build/debug -- --no-print-directory

run: debug
	./build/debug/puzzles

# TODO Find a better name than "full"
run_full: debug
	./build/debug/puzzles full

# Release targets
release: build/release/Makefile
	cmake --build build/release --target puzzles -- --no-print-directory

run_release: release
	./build/release/puzzles

.PHONY: all clean check debug debug_all run run_full release run_release

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
