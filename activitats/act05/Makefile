CC=GCC
CFLAGS = -c -Wall
SOURCES= jugador.c EscapeRoom.c
EXECS = EscapeRoom

OBJECTS=$(SOURCES:.c=.o)

$(EXECS): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECS)

execute: $(EXECS)
	./$(EXECS)

test1: $(EXECS)
	./$(EXECS) aaaa

test2: $(EXECS)
	./$(EXECS) abab

test3: $(EXECS)
	./$(EXECS) abba