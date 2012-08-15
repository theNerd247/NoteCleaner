NoteCleaner: NoteCleaner.cpp
	g++ -g -o NoteCleaner NoteCleaner.cpp 
clean:
	rm NoteCleaner
run: NoteCleaner
	./NoteCleaner test

