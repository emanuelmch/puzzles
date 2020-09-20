# Generic phony targets
all: debug_all release

clean:
	rm -rf build

fullcheck: check_run run_release

# Debug targets
debug: build/debug/Makefile
	cmake --build build/debug --target puzzles -- --no-print-directory

debug_all: build/debug/Makefile
	cmake --build build/debug -- --no-print-directory

check: build/debug/Makefile
	cmake --build build/debug --target check -- --no-print-directory

run: debug
	./build/debug/puzzles

check_run: build/debug/Makefile
	${MAKE} -C build/debug check run --no-print-directory

# TODO Find a better name than "full"
run_full: debug
	./build/debug/puzzles full

# Release targets
release: build/release/Makefile
	cmake --build build/release --target puzzles -- --no-print-directory

run_release: build/release/Makefile
	${MAKE} -C build/release run --no-print-directory

.PHONY: all clean fullcheck debug debug_all check run check_run run_full release run_release

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
