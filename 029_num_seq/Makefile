CFLAGS=-pedantic -std=gnu99 -Wall -Werror

step1: step1.c
	gcc -o $@ $(CFLAGS) $?
step2: step2.c
	gcc -o $@ $(CFLAGS) $?
step3: step3.c
	gcc -o $@ $(CFLAGS) $?

clean_e:
	rm -rf step1 step2 step3 *~

