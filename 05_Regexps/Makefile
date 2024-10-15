GENERATES = esub tests

all: 	test

esub: 	esub.c

REGEXP_1 = r
SUBSTITUTUION_1 = ll
STRING_1 = hero

test_1: esub
	mkdir -p tests
	./$< '$(REGEXP_1)' '$(SUBSTITUTUION_1)' '$(STRING_1)' > tests/esub_1.txt
	echo '$(STRING_1)' | sed -E 's/$(REGEXP_1)/$(SUBSTITUTUION_1)/' > tests/sed_1.txt
	cmp tests/esub_1.txt tests/sed_1.txt

REGEXP_2 = (e.*w)
SUBSTITUTUION_2 = @\1@
STRING_2 = hello world!

test_2: esub
	mkdir -p tests
	./$< '$(REGEXP_2)' '$(SUBSTITUTUION_2)' '$(STRING_2)' > tests/esub_2.txt
	echo '$(STRING_2)' | sed -E 's/$(REGEXP_2)/$(SUBSTITUTUION_2)/' > tests/sed_2.txt
	cmp tests/esub_2.txt tests/sed_2.txt

REGEXP_3 = (e.*w)
SUBSTITUTUION_3 = @\\1\\@
STRING_3 = hello world!

test_3: esub
	mkdir -p tests
	./$< '$(REGEXP_3)' '$(SUBSTITUTUION_3)' '$(STRING_3)' > tests/esub_3.txt
	echo '$(STRING_3)' | sed -E 's/$(REGEXP_3)/$(SUBSTITUTUION_3)/' > tests/sed_3.txt
	cmp tests/esub_3.txt tests/sed_3.txt

REGEXP_4 = ([0-9][0-9]*)
SUBSTITUTUION_4 = <\1>
STRING_4 = Wed Oct 15 20:14:57 MSK 2024

test_4: esub
	mkdir -p tests
	./$< '$(REGEXP_4)' '$(SUBSTITUTUION_4)' '$(STRING_4)' > tests/esub_4.txt
	echo '$(STRING_4)' | sed -E 's/$(REGEXP_4)/$(SUBSTITUTUION_4)/' > tests/sed_4.txt
	cmp tests/esub_4.txt tests/sed_4.txt

REGEXP_5 = (([0-9]+).*)([0-9]+)
SUBSTITUTUION_5 = <1=\1><2=\2><3=\3>
STRING_5 = Wed Oct 15 20:14:57 MSK 2024

test_5: esub
	mkdir -p tests
	./$< '$(REGEXP_5)' '$(SUBSTITUTUION_5)' '$(STRING_5)' > tests/esub_5.txt
	echo '$(STRING_5)' | sed -E 's/$(REGEXP_5)/$(SUBSTITUTUION_5)/' > tests/sed_5.txt
	cmp tests/esub_5.txt tests/sed_5.txt

REGEXP_6 = 1([0-9]+):([0-9]+)7
SUBSTITUTUION_6 = 3\1:\29
STRING_6 = Wed Oct 15 20:14:57 MSK 2024

test_6: esub
	mkdir -p tests
	./$< '$(REGEXP_6)' '$(SUBSTITUTUION_6)' '$(STRING_6)' > tests/esub_6.txt
	echo '$(STRING_6)' | sed -E 's/$(REGEXP_6)/$(SUBSTITUTUION_6)/' > tests/sed_6.txt
	cmp tests/esub_6.txt tests/sed_6.txt

test: 	test_1 test_2 test_3 test_4 test_5 test_6

clean:
	rm -rf ${GENERATES}