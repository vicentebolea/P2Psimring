
all:
	-make -C minini
	-make -C unittest++
	-cp minini/minIni.o .
	-cp unittest++/libUnitTest++.a .

clean:
	-make -C minini clean
	-make -C unittest++ clean
	-rm *.o *.a

