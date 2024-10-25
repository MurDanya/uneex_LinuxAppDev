CC_DEFINES = -D_GNU_SOURCE

IN_FILE=infile.txt
OUT_FILE=outfile.txt

GENERATES=move *${IN_FILE} ${OUT_FILE} *.o *.so

all: move libremove.so test

move: move.c

libremove.so: remove.c
	${CC} ${CC_DEFINES} -shared $< -o $@

test: move libremove.so
	echo "ahhasdhvhsdvpfaibho82565 f dsv" > ${IN_FILE}
	strace -e fault=openat:when=1 -P ${IN_FILE} ./move ${IN_FILE} ${OUT_FILE} 2> /dev/null || test $$? -eq 2
	test -f ${IN_FILE}
	strace -e fault=openat:when=1 -P ${OUT_FILE} ./move ${IN_FILE} ${OUT_FILE} 2> /dev/null || test $$? -eq 3
	test -f ${IN_FILE}
	strace -e fault=read:when=1 -P ${IN_FILE} ./move ${IN_FILE} ${OUT_FILE} 2> /dev/null || test $$? -eq 4
	test -f ${IN_FILE}
	strace -e fault=unlink:when=1 -y -P ${IN_FILE} ./move ${IN_FILE} ${OUT_FILE} 2> /dev/null || test $$? -eq 6
	test -f ${IN_FILE}

	echo "ahahahahahahahahahahahaha" > PROTECT_${IN_FILE}
	LD_PRELOAD=./libremove.so ./move PROTECT_${IN_FILE} ${OUT_FILE} 2> /dev/null || test $$? -eq 6
	test -f PROTECT_${IN_FILE}

clean:
	rm -rf ${GENERATES}