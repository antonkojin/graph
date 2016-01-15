CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=facebook.c graph.c list.c binary_search_tree.c user.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=facebook

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o facebook

