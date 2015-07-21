CC = gcc
CXX = clang

LINK.o = $(LINK.cc)

INCLUDES = 

CFLAGS = -g -Wall $(INCLUDES)
CXXFLAGS = -g -std=c++11 -Wall $(INCLUDES)

LDFLAGS = -g -Wall -lstdc++
LDLIBS = -lm 


tfidf: tfidf.o tf.o idf.o filereader.o

tfidf.o: tfidf.cpp tf.hpp idf.hpp

tf.o: tf.cpp tf.hpp filereader.hpp

idf.o: idf.cpp idf.hpp tf.hpp filereader.hpp

filereader.o: filereader.cpp filereader.hpp

.PHONY: clean
clean:
	rm -f *.o tfidf

.PHONY: all
all: clean tfidf
