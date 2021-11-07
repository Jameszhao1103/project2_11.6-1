EXE	= project1b

all: project1b

project1b: main.cpp dictionary.cpp hash24.cpp
	g++ -std=c++11 $^ -o $@

clean:
	rm -rf ${EXE}