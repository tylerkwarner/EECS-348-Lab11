CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

OBJS = main.o Matrix.o

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS)

main.o: main.cpp Matrix.h
Matrix.o: Matrix.cpp Matrix.h

clean:
	rm -f *.o main
