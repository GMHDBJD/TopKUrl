CC = g++
CFLAGS = -std=c++11 -O -I$(IDIR) -g

IDIR = ./include/
SRCDIR = ./src/
GENDIR = ./gen_data/

SOURCES = $(SRCDIR)*.cpp\

all: generate_data.out hash_heap.out count_min_sketch.out space_saving.out

generate_data.out : $(SOURCES)
	$(CC) $(GENDIR)generate_data.cpp $(CFLAGS) -O -o $@

hash_heap.out : $(SOURCES)
	$(CC) $(SRCDIR)hash_heap.cpp $(CFLAGS) -O -o $@

count_min_sketch.out : $(SOURCES)
	$(CC) $(SRCDIR)count_min_sketch.cpp $(CFLAGS) -O -o $@

space_saving.out : $(SOURCES)
	$(CC) $(SRCDIR)space_saving.cpp $(CFLAGS) -O -o $@

clean:
	rm -rf *.out data hash_heap count_min_sketch space_saving