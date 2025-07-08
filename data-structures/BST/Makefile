CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

SRCS = main.cpp bst.cpp bst_instrumented.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = bst

all: $(TARGET)

$(TARGET): main.o bst.o
	$(CXX) $(CXXFLAGS) -o $@ main.o bst.o

bst_instrumented.o: bst_instrumented.cpp bst.h
	$(CXX) $(CXXFLAGS) -c bst_instrumented.cpp

main.o: main.cpp bst.h
	$(CXX) $(CXXFLAGS) -c main.cpp

bst.o: bst.cpp bst.h
	$(CXX) $(CXXFLAGS) -c bst.cpp

clean:
	del /Q *.o *.exe 2>nul || rm -f *.o *.exe
