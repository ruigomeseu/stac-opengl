
default: CGFexample
	echo

.PHONY: CGFlib CGFexample

CGFlib: 
	mkdir -p buildtemp
	+$(MAKE) -C CGFlib

CGFexample: CGFlib
	mkdir -p buildtemp
	mkdir -p CGFexample/lib
	mkdir -p CGFexample/include/CGF
	cp CGFlib/lib/libCGF.a CGFexample/lib
	cp CGFlib/include/CGF*.* CGFexample/include/CGF
	+$(MAKE) -C CGFexample

clean:
	+$(MAKE) -C CGFlib clean
	+$(MAKE) -C CGFexample clean

