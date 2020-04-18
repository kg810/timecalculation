CFLAGS := -std=c++14 -Wall -Werror

all: myMain

.cpp.o:
	g++ $(CFLAGS) -c -fPIC $<

myMain: main.cpp libhour.so libcost.so
	g++ $(CFLAGS) -L. -o myMain main.cpp -ldl -lhour -lcost

libhour.so: hour.o
	g++ $(CFLAGS) -shared hour.o -o libhour.so
	rm hour.o

slow.a: slow.o
	ar rcs slow.a slow.o
	rm slow.o

libcost.so: cost.o slow.a
	g++ $(CFLAGS) cost.o -shared -o libcost.so -Wl,--whole-archive slow.a -Wl,--no-whole-archive
	rm cost.o

clean:
	rm -f *.o *.a *.so myMain
