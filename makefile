all: project2.out

project2.out: main.cpp 
	g++ -std=c++11 $^ -o $@

clean:
	rm -f *.out

