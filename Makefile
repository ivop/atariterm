
CFLAGS += -O3

atariterm: atariterm.c Makefile raw.h
	$(CC) $(CFLAGS) -o $@ $< libatari800.a -lm

atariterm-static: atariterm.c Makefile raw.h
	$(CC) $(CFLAGS) -o $@ $< libatari800.a -lm -static

clean:
	rm -f atariterm atariterm-static *~
