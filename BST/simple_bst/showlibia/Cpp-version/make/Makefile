ROOT_DIR := $(shell cd .. && pwd)
cd_to_root := cd $(ROOT_DIR)

.PHONY: debug build configure run clean test correct debug_correct

build: configure
	$(cd_to_root) && cmake --build build -j 8	

configure:
	$(cd_to_root) && cmake -B build -DCMAKE_BUILD_TYPE=Release -S .

run: build
	$(cd_to_root) && ./build/bst

clean: 
	$(cd_to_root) && rm -rf build && rm -f bst.o && rm -f correct

debug: 
	$(cd_to_root) && cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
	$(cd_to_root) && cmake --build build -j 8
	$(cd_to_root) && gdb ./build/bst

correct:
	$(cd_to_root) && clang++ -c bst.cc && clang++ -o correct bst.o correct.cc && ./correct

debug_correct:
	$(cd_to_root) && clang++ -c bst.cc && clang++ -o correct bst.o correct.cc -g && gdb ./correct --tui

test:correct
	$(cd_to_root) && cp ../../../correctness/correct.sh ./ && sh correct.sh && rm correct.sh
	make clean