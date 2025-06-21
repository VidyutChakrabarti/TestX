INC=../../testgenerators/
LIB=../../testgenerators/
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

COMPILE_BASE=g++ -g -c -I $(INC)
COMPILE_GCOV=g++ -g -c -I $(INC) $(GCOV_FLAGS)

graphtg: main.o graphtg.o graphmutator.o graph.o user_function.o $(INC)/libtg.a
	g++ -I $(INC) -L $(LIB) graph.o graphtg.o graphmutator.o user_function.o main.o -ljsoncpp -ltg -lgcov -o graphtg

$(INC)/libtg.a:
	make -C $(INC) libtg.a

graphtg.o: graphtg.cpp graphtg.h
	$(COMPILE_BASE) graphtg.cpp

graphmutator.o: graphmutator.cpp graphmutator.h
	$(COMPILE_BASE) graphmutator.cpp

graph.o: graph.cpp graph.h
	$(COMPILE_BASE) graph.cpp

user_function.o: user_function.cpp user_function.h graph.h
	$(COMPILE_GCOV) user_function.cpp

main.o: main.cpp
	$(COMPILE_BASE) main.cpp

clean:
	rm -f *.o graphtg *.gcda *.gcno *.gcov
