main: 	*.o
	g++ -static -g -w server.cpp Handler.o User.o -o main

*.o: *.h *.cpp
	g++ -c -g -w *.cpp

run:
	./main

clean:
	rm main *.o
