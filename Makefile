CC = g++
CFLAGS =-pedantic -Wall -Wfatal-errors -std=c++11 -D_POSIX_SOURCE -g -O0
LFLAGS = 
LIBS = -ljansson
TESTDIR = test
BINDIR = bin
SRCDIR = src
LIBDIR = libs

.PHONY: all

all: peak clean


peak: $(SRCDIR)/*.cpp $(SRCDIR)/*.h
	$(CC) $(CFLAGS) $(LFLAGS) -o $(BINDIR)/peak $(SRCDIR)/peak.cpp  $(LIBS)

test: $(TESTDIR)/*.cpp *.cpp *.h

clean:
	rm -f $(SRCDIR)/*.o
	rm -f $(TESTDIR)/*.o
