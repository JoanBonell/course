CC=GCC
CFLAGS = -c -Wall
SOURCES= log.c ossh.c helpers.c
EXECS = ohsh

OBJECTS=$(SOURCES:.c=.o)

$(EXECS): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
