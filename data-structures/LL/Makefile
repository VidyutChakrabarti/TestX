INC=../../testgenerators/
LIB="../../testgenerators/"
COMPILE=g++ -g -c -I $(INC)
lltg : main.o lltg.o $(INC)/libtg.a linkedlist_instrumented.o
	g++ -I $(INC) -L$(LIB) linkedlist_instrumented.o lltg.o main.o -ljsoncpp -ltg -o lltg

$(INC)/libtg.a :
	make -C $(INC) libtg.a;

lltg.o: lltg.cpp lltg.h
	$(COMPILE) lltg.cpp

linkedlist_instrumented.o : linkedlist_instrumented.cpp linkedlist.h
	$(COMPILE) linkedlist_instrumented.cpp

main.o : main.cpp
	$(COMPILE) main.cpp

clean:
	rm *.o
	rm lltg
