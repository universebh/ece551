CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
test-bstmap: test.cpp bstmap.h map.h
	g++ -o $@ $(CCFLAGS) $?
clean:
	rm -f test-bstmap *~

