GENERATES = prog prog-a prog-so liboutput_static.a liboutput.so test_outputs
TRASH = *.o *~ o.*
CFLAGS = -Wall -fPIC

ARGS_TEST_1 =
ARGS_TEST_2 = haha
ARGS_TEST_3 = haha hehe hihi

.PHONY: 	clean distclean

all:	test

fun.o prog.o:  outlib.h

.SECONDARY:	liboutput_static.a(fun.o const.o)

liboutput_static.a:	liboutput_static.a(fun.o const.o)

liboutput.so:	fun.o const.o
	$(CC) $^ -o $@ -shared

prog:	prog.o fun.o const.o

prog-a:	prog.o liboutput_static.a
	$(CC) $< -L. -loutput_static -o prog-a

prog-so:	prog.o liboutput.so
	$(CC) $< -L. -l:liboutput.so -o prog-so

test_1: prog prog-a prog-so
	mkdir -p test_outputs
	./prog $(ARGS_TEST_1) > test_outputs/prog_1.txt 2> test_outputs/prog_1_err.txt
	./prog-a $(ARGS_TEST_1) > test_outputs/prog-a_1.txt 2> test_outputs/prog-a_1_err.txt
	LD_LIBRARY_PATH=`pwd` ./prog-so $(ARGS_TEST_1) > test_outputs/prog-so_1.txt 2> test_outputs/prog-so_1_err.txt
	cmp test_outputs/prog_1.txt test_outputs/prog-a_1.txt
	cmp test_outputs/prog_1.txt test_outputs/prog-so_1.txt
	sed 's/prog-a/prog/g' test_outputs/prog-a_1_err.txt | cmp test_outputs/prog_1_err.txt
	sed 's/prog-so/prog/g' test_outputs/prog-so_1_err.txt | cmp test_outputs/prog_1_err.txt

test_2: prog prog-a prog-so
	mkdir -p test_outputs
	./prog $(ARGS_TEST_2) > test_outputs/prog_2.txt
	./prog-a $(ARGS_TEST_2) > test_outputs/prog-a_2.txt
	LD_LIBRARY_PATH=`pwd` ./prog-so $(ARGS_TEST_2) > test_outputs/prog-so_2.txt
	cmp test_outputs/prog_2.txt test_outputs/prog-a_2.txt
	cmp test_outputs/prog_2.txt test_outputs/prog-so_2.txt

test_3: prog prog-a prog-so
	mkdir -p test_outputs
	./prog $(ARGS_TEST_3) > test_outputs/prog_3.txt
	./prog-a $(ARGS_TEST_3) > test_outputs/prog-a_3.txt
	LD_LIBRARY_PATH=`pwd` ./prog-so $(ARGS_TEST_3) > test_outputs/prog-so_3.txt
	cmp test_outputs/prog_3.txt test_outputs/prog-a_3.txt
	cmp test_outputs/prog_3.txt test_outputs/prog-so_3.txt

test: test_1 test_2 test_3

clean:
	rm -rf $(TRASH)

distclean:      clean
	rm -rf $(GENERATES)
