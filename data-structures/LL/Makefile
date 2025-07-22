INC=../../testgenerators/
LIB=../../testgenerators/
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

COMPILE_BASE=g++ -g -c -I $(INC)
COMPILE_GCOV=g++ -g -c -I $(INC) $(GCOV_FLAGS)

lltg: main.o lltg.o llmutator.o linkedlist.o user_function.o $(INC)/libtg.a
	g++ -I $(INC) -L $(LIB) linkedlist.o lltg.o llmutator.o user_function.o main.o -ljsoncpp -ltg -lgcov -o lltg

$(INC)/libtg.a:
	make -C $(INC) libtg.a

lltg.o: lltg.cpp lltg.h
	$(COMPILE_BASE) lltg.cpp

llmutator.o: llmutator.cpp llmutator.h
	$(COMPILE_BASE) llmutator.cpp

linkedlist.o: linkedlist.cpp linkedlist.h
	$(COMPILE_BASE) linkedlist.cpp

user_function.o: Userfunctions/user_function.cpp Userfunctions/user_function.h linkedlist.h
	$(COMPILE_GCOV) Userfunctions/user_function.cpp -o user_function.o

main.o: main.cpp
	$(COMPILE_BASE) main.cpp

clean:
	del *.o lltg.exe *.gcda *.gcno *.gcov 2>nul || true
