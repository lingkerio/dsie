ROOT_DIR := $(shell cd .. && pwd)
cd_to_root := cd $(ROOT_DIR)

.PHONY: debug build configure run clean

build: configure
	$(cd_to_root) && cmake --build build -j 8	

configure:
	$(cd_to_root) && cmake -B build -DCMAKE_BUILD_TYPE=Release -S .

run: 
	$(cd_to_root) && ./build/bst

clean: 
	$(cd_to_root) && rm -rf build

debug: 
	$(cd_to_root) && cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
	$(cd_to_root) && cmake --build build -j 8
	$(cd_to_root) && gdb ./build/bst
