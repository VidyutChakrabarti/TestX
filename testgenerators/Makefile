INC=.
LIB=.
COMPILE=g++ -g -c -I $(INC)

libtg.a : testgenerator.o valuegenerators.o
	ar rcs libtg.a testgenerator.o valuegenerators.o

test : test_valuegenerators.o
	g++ -o test test_valuegenerators.o

test_valuegenerators.o : test_valuegenerators.cpp valuegenerators.h
	$(COMPILE) test_valuegenerators.cpp

testgenerator.o : testgenerator.cpp testgenerator.h mutator.h
	$(COMPILE) testgenerator.cpp

valuegenerators.o : valuegenerators.cpp valuegenerators.h
	$(COMPILE) valuegenerators.cpp

clean:
	rm -f *.o
	rm -f libtg.a
	rm -f test
