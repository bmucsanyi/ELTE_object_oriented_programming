CXX = g++
CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra
HEADERS = garden.h gardener.h parcel.h plant.h
OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

.PHONY: all clean

all: main.out

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $< -c -o $@

main.out: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf *.out
