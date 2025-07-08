CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

SRCS = test.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = testbst

all: $(TARGET)

$(TARGET): test.o ../bst.o
	$(CXX) $(CXXFLAGS) -o $@ test.o ../bst.o

test.o: test.cpp ../../bst/bst.h
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	del /Q *.o *.exe 2>nul || rm -f *.o *.exe
