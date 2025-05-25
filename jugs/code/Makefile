COMPILE = g++ -g
jugs : main.o jugs.o
	$(COMPILE) -o jugs main.o jugs.o

main.o : main.cpp jugs.h
	$(COMPILE) -o main.o -c main.cpp

test_jugs : test_jugs.o tester.o jugs_instrumented.o
	$(COMPILE) -o test_jugs test_jugs.o tester.o jugs_instrumented.o

jugs.o : jugs.h jugs.cpp
	$(COMPILE) -o jugs.o -c jugs.cpp

jugs_instrumented.o : jugs.h jugs_instrumented.cpp
	$(COMPILE) -o jugs_instrumented.o -c jugs_instrumented.cpp

tester.o : tester.h tester.cpp
	$(COMPILE) -o tester.o -c tester.cpp

test_jugs.o : test_jugs.cpp tester.h jugs.h
	$(COMPILE) -o test_jugs.o -c test_jugs.cpp

testgen : jugs_instrumented.o tester.o testgenerator.o testgen_main.o
	$(COMPILE) -o testgen jugs_instrumented.o tester.o testgenerator.o testgen_main.o

testgenerator.o : tester.h testgenerator.h testgenerator.cpp
	$(COMPILE) -c testgenerator.cpp

testgen_main.o : jugs.h testgenerator.h tester.h testgen_main.h testgen_main.cpp
	$(COMPILE) -c testgen_main.cpp

gtest_jugs : jugs.o gtest_jugs.o
	$(COMPILE) -Wall -Wextra -Werror -O3 -std=c++17 -pthread \
		jugs.o \
		gtest_jugs.o \
		-lgtest -lgtest_main -o gtest_jugs

gtest_jugs.o : gtest_jugs.cpp
	$(COMPILE) -Wall -Wextra -Werror -O3 -std=c++17 -pthread \
		-c gtest_jugs.cpp -o gtest_jugs.o

gtest_jugs_cov : jugs_instrumented.o tester.o gtest_jugs.o
	$(COMPILE) -Wall -Wextra -Werror -O3 -std=c++17 -pthread \
		tester.o \
		jugs_instrumented.o \
		gtest_jugs.o \
		-lgtest -lgtest_main -o gtest_jugs_cov

clean :
	rm *.o;
	rm test_jugs
	rm jugs
