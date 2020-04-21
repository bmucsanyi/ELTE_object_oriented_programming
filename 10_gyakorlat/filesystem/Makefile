CXX = g++
CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra
HEADERS = directory.h entry.h file.h filesystem.h
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))

.PHONY: all clean

all: main.out

%.o: %.c $(HEADERS)
	$(CXX) $(CXXFLAGS) $< -c -o $@

main.out: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf *.out
