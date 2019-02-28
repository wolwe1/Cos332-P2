main: 	*.o
	g++ -static -g  main.cpp Handler.o User.o -o main

*.o: *.h *.cpp
	g++ -c -g -Wall *.cpp

run:
	./main

clean:
	rm main *.o