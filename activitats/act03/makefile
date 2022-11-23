CC=GCC
CFLAGS = -c -Wall
SOURCES= shell.c helpers.c
EXECS = ohsh

OBJECTS=$(SOURCES:.c=.o)

$(EXECS): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECS)

execute: $(EXECS)
	./$(EXECS)