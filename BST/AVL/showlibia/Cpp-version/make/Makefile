ROOT_DIR := $(shell cd .. && pwd)
cd_to_root := cd $(ROOT_DIR)

.PHONY: debug build configure run clean test correct debug_correct

build: configure
	$(cd_to_root) && cmake --build build -j 8	

configure:
	$(cd_to_root) && cmake -B build -DCMAKE_BUILD_TYPE=Release -S .

run: build
	$(cd_to_root) && ./build/avl

clean: 
	$(cd_to_root) && rm -rf build && rm -f avl.o && rm -f correct && rm -f correctness.csv

debug: 
	$(cd_to_root) && cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
	$(cd_to_root) && cmake --build build -j 8
	$(cd_to_root) && ./build/avl

correct:
	$(cd_to_root) && clang++ -c avl.cc && clang++ -o correct avl.o correct.cc && ./correct

debug_correct:
	$(cd_to_root) && clang++ -c avl.cc && clang++ -o correct avl.o correct.cc -g && gdb ./correct --tui

test:correct
	$(cd_to_root) && cp ../../../correctness/correct.sh ./ && sh correct.sh && rm correct.sh