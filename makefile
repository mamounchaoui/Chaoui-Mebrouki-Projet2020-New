.DEFAULT_GOAL := check

.PHONY: clean

clean:
	rm -rf build

build:
	mkdir -p build

build/employe.o: lib/employe.c | build
	gcc -Wall -pedantic -Werror -g -c lib/employe.c -I ./lib -o build/employe.o

build/chercheurdemploi.o: lib/chercheurdemploi.c | build
	gcc -Wall -pedantic -Werror -g -c lib/chercheurdemploi.c -I ./lib -o build/chercheurdemploi.o

build/entreprise.o: lib/entreprise.c | build
	gcc -Wall -pedantic -Werror -g -c lib/entreprise.c -I ./lib -o build/entreprise.o

build/test.o: test/main.c | build
	gcc -Wall -pedantic -Werror -g -c test/main.c -I ./lib -o build/test.o

build/libentreprise.a: build/entreprise.o build/employe.o build/chercheurdemploi.o | build
	ar crs build/libentreprise.a build/entreprise.o build/employe.o build/chercheurdemploi.o
	
build/test: build/test.o build/libentreprise.a | build
	gcc build/test.o -Lbuild/ -lentreprise -o build/test

# Lance le programme build/test.
check: build/test
	./build/test