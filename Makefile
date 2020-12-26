# Generic phony targets
all: debug_all release

clean:
	rm -rf build

gcc: gcc_debug gcc_release
clang: clang_debug clang_release

# Check + Run targets

check_run: build/debug/Makefile
check_run_release: build/release/Makefile
gcc_debug: build/gcc-debug/Makefile
gcc_release: build/gcc-release/Makefile
clang_debug: build/clang-debug/Makefile
clang_release: build/clang-release/Makefile

check_run check_run_release gcc_debug gcc_release clang_debug clang_release:
	${MAKE} -C $(abspath $(addsuffix /..,$<)) check run --no-print-directory

# Debug targets
debug: build/debug/Makefile
	${MAKE} -C build/debug puzzles --no-print-directory

debug_all: build/debug/Makefile
	${MAKE} -C build/debug all --no-print-directory

check: build/debug/Makefile
	${MAKE} -C build/debug check --no-print-directory

run: debug
	./build/debug/puzzles

# TODO Find a better name than "full"
run_full: debug
	./build/debug/puzzles full

# Release targets
release: build/release/Makefile
	${MAKE} -C build/release puzzles --no-print-directory

check_release: build/release/Makefile
	${MAKE} -C build/release check --no-print-directory

run_release: build/release/Makefile
	${MAKE} -C build/release run --no-print-directory

.PHONY: all clean gcc clang check_run check_run_release gcc_debug gcc_release clang_debug clang_release debug debug_all check run run_full release check_release run_release

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

build/gcc-debug/Makefile: CMakeLists.txt
	@mkdir -p build/gcc-debug
	cd build/gcc-debug && cmake ../.. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=/usr/bin/g++ -DCMAKE_C_COMPILER=/usr/bin/gcc

build/gcc-release/Makefile: CMakeLists.txt
	@mkdir -p build/gcc-release
	cd build/gcc-release && cmake ../.. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=/usr/bin/g++ -DCMAKE_C_COMPILER=/usr/bin/gcc

build/clang-debug/Makefile: CMakeLists.txt
	@mkdir -p build/clang-debug
	cd build/clang-debug && cmake ../.. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_C_COMPILER=/usr/bin/clang

build/clang-release/Makefile: CMakeLists.txt
	@mkdir -p build/clang-release
	cd build/clang-release && cmake ../.. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_C_COMPILER=/usr/bin/clang
