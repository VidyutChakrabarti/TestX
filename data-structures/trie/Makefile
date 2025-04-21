INC=../../testgenerators/
LIB="../../testgenerators/"

trie.o : trie.cpp trie.h
	$(COMPILE) trie.cpp

trie_instrumented.o : trie_instrumented.cpp trie.h
	$(COMPILE) trie_instrumented.cpp

main.o : main.cpp
	$(COMPILE) main.cpp

clean:
	rm *.o
	rm trietg
