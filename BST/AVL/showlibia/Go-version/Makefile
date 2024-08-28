.PHONY:test correct clean all

all: 
	go run main.go avl.go common.go test.go correct.go

test:
	go run main.go avl.go common.go test.go correct.go -test

correct:
	go run main.go avl.go common.go test.go correct.go -correct && cp ../../../correctness/correct.sh ./ && sh correct.sh 

clean:
	rm correct.sh && rm -f correctness.csv