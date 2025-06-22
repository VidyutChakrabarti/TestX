# examples/graph/test/Makefile

INC= -I ../ -I ../../../testgenerators/
LIB= -L ../ -L ../../../testgenerators/
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

test: test.o user_function.o ../graphmutator.o
	g++ $(INC) $(LIB) -g -o test test.o ../graphtg.o ../graph.o ../graphmutator.o user_function.o -ltg -ljsoncpp -lgcov $(GCOV_FLAGS)

test.o: test.cpp
	g++ $(INC) -g -c test.cpp

user_function.o: ../user_function.cpp ../user_function.h ../graph.h
	g++ $(INC) -g -c ../user_function.cpp -o user_function.o $(GCOV_FLAGS)

clean:
	rm -f *.o test *.gcda *.gcno *.gcov
