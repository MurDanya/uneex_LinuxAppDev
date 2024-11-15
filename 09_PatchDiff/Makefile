GENERATES = labgen_ver0 labgen_ver1 labgen_ver2 labgen_ver3 labgen_ver1.c labgen_ver2.c labgen_ver3.c

run: labgen_ver0 labgen_ver1 labgen_ver2 labgen_ver3
	./labgen_ver0
	./labgen_ver1 10
	./labgen_ver2 " #" 10
	./labgen_ver3 42 " +" 10
	./labgen_ver3 100500 " *" 10

labgen_ver1.c: labgen_ver0.c p1.patch
	patch -b $< p1.patch
	mv $< $@
	mv $<.orig $<

labgen_ver2.c: labgen_ver1.c p2.patch
	patch -b $< p2.patch
	mv $< $@
	mv $<.orig $<

labgen_ver3.c: labgen_ver2.c p3.patch
	patch -b $< p3.patch
	mv $< $@
	mv $<.orig $<

labgen_ver0: labgen_ver0.c

labgen_ver1: labgen_ver1.c

labgen_ver2: labgen_ver2.c

labgen_ver3: labgen_ver3.c

clean:
	rm -rf $(GENERATES)