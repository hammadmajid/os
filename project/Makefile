.PHONY: build run clean

build:
	clang++ -std=c++17 -Wall -Wextra -o main ./main.cpp

run: build
	./main

clean:
	rm -f main auth.csv
	rm -rf user_files/
