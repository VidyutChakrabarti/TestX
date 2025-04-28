INC= -I ../ -I ../../../testgenerators/
LIB= -L ../ -L ../../../testgenerators/

test : test.o
	g++ $(INC) $(LIB) test.o ../lltg.o ../linkedlist.o -ltg -ljsoncpp -o test
	
test.o : test.cpp
	g++ $(INC) -c test.cpp
	
clean:
	rm *.o
	rm test
