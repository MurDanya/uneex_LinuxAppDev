all: install

build:
	src/build.sh

install:
	src/install.sh

uninstall:
	src/uninstall.sh

test:	build
	src/test.sh

man:	build
	man docs/man/man3/guess.3

http:	build
	python3 -m http.server --directory docs/html

clean:
	rm -rf build Testing docs po/ru/LC_MESSAGES
	rm -f guess