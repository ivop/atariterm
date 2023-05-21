
CFLAGS += -O3

atariterm: atariterm.c Makefile raw.h
	$(CC) $(CFLAGS) -o $@ $< libatari800.a -lm

clean:
	rm -f atariterm *~
