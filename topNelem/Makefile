CC    = g++
CFLAGS= -I.
OBJ   = topN.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

topN: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY:
	run clean

run:
	./topN

clean:
	rm -f topN topN.o output_file
