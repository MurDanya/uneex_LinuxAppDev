GENERATES = range gdb1_out.txt gdb2_out.txt

range: range.c
	$(CC) -Wall -g -O0 range.c -o range

test: range
	gdb --batch --quiet -x gdb1 ./range | grep -P "^@@@" > gdb1_out.txt
	diff gdb1_etalon.txt gdb1_out.txt
	gdb --batch --quiet -x gdb2 ./range | grep -P "^@@@" > gdb2_out.txt
	diff gdb2_etalon.txt gdb2_out.txt

clean:
	rm -f $(GENERATES)