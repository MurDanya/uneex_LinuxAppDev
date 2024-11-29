SUBDIRS = po src

@DX_RULES@
doxygen-doc/man/man1/guess.1:	doxygen-doc

man1_MANS = doxygen-doc/man/man1/guess.1

install-data-local:
		mkdir -p $(DESTDIR)/$(docdir)
		cp -a doxygen-doc/html $(DESTDIR)/$(docdir)

http:	doxygen-doc
		python3 -m http.server --directory $</html

clean:
		git clean -df
