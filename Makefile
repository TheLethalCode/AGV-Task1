CFLAGS = `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`
CC = g++
% : %.cpp
	$(CC) -g $(CFLAGS) -o $@ $< $(LIBS) 
