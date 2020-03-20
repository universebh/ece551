CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
test-bsearch: test.cpp function.h search.cpp
	g++ -o $@  $(CCFLAGS) $?
clean:
	rm -f test-bsearch *~
