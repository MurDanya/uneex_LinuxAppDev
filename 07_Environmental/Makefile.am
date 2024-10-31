bin_PROGRAMS=rhasher
rhasher_SOURCES=rhasher.c
TESTS=test

test:
	echo "MD5 \"HelloWorld" | ./rhasher > out
	echo -n "HelloWorld" | md5sum | awk '{print $$1 }' > etalon
	cmp out etalon

	echo "SHA1 \"HelloWorld" | ./rhasher > out
	echo -n "HelloWorld" | sha1sum | awk '{print $$1 }' > etalon
	cmp out etalon

gitclean:
	git clean -df
