all: a.out

a.out: main.cpp MinMedianMaxSketch.cpp
	g++ -std=c++11 $^ -o $@

clean:
	rm -f *.out

