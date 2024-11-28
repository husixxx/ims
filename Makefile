all:
	g++ -std=gnu++11 -Wall -Wextra -pedantic main.cpp -o ims -lsimlib -lm
clean:
	rm -f ims