# examples/graph/Makefile



INC=../../testgenerators/

LIB=../../testgenerators/

GCOV_FLAGS=-fprofile-arcs -ftest-coverage



# Compile normally (without instrumentation)

COMPILE_BASE=g++ -g -c -I $(INC)

# Compile with gcov instrumentation (only for files we want measured)

COMPILE_GCOV=g++ -g -c -I $(INC) $(GCOV_FLAGS)



graphtg: main.o graphtg.o $(INC)/libtg.a graph.o user_function.o

	g++ -I $(INC) -L $(LIB) graph.o graphtg.o user_function.o main.o -ljsoncpp -ltg -lgcov -o graphtg $(GCOV_FLAGS)



$(INC)/libtg.a:

	make -C $(INC) libtg.a



graphtg.o: graphtg.cpp graphtg.h

	$(COMPILE_BASE) graphtg.cpp



graph.o: graph.cpp graph.h

	$(COMPILE_BASE) graph.cpp



user_function.o: user_function.cpp user_function.h graph.h

	$(COMPILE_BASE) user_function.cpp

clean:

	rm -f *.o graphtg *.gcda *.gcno *.gcov

