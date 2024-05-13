G++ := g++
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    G++ := /bin/g++
endif

all: encrypt decrypt distance

encrypt: encrypt.o crypto_utils.o
	$(G++) -std=c++11 -o encrypt encrypt.o crypto_utils.o

decrypt: decrypt.o crypto_utils.o
	$(G++) -std=c++11 -o decrypt decrypt.o crypto_utils.o

distance: distance.o
	$(G++) -std=c++11 -o distance distance.o

%.o: %.cpp
	$(G++) -std=c++11 -c $< -o $@

clean:
	rm -f encrypt decrypt *.o
	rm -f encrypt
	rm -f decrypt
	rm -f distance *.o
