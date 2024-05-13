#
# CS-556 Project 2
#

G++ := g++
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
  G++ := /bin/g++
endif

all: KeyGenerator asymmetrickey_encr asymmetrickey_decr

KeyGenerator: KeyGenerator.cpp crypto_utils.cpp crypto_utils.h
	$(G++) -std=c++11 -o KeyGenerator KeyGenerator.cpp crypto_utils.cpp -lgmp -lgmpxx

asymmetrickey_encr: asymmetrickey_encr.cpp crypto_utils.cpp crypto_utils.h
	$(G++) -std=c++11 -o asymmetrickey_encr asymmetrickey_encr.cpp crypto_utils.cpp -lgmp -lgmpxx

asymmetrickey_decr: asymmetrickey_decr.cpp crypto_utils.cpp crypto_utils.h
	$(G++) -std=c++11 -o asymmetrickey_decr asymmetrickey_decr.cpp crypto_utils.cpp -lgmp -lgmpxx

clean:
	rm -f asymmetrickey_encr
	rm -f asymmetrickey_decr
