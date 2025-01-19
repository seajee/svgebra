all:
	g++ -Wall -Wextra -o libsvgebra main.cpp svgebra.cpp

clean:
	rm -rf libsvgebra
