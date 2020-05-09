CC=gcc
CFLAGS=
BINARY=ducgol
DEST=/usr/bin/$(BINARY)
LDLINKS=-lncurses

build:
	$(CC) $(CFLAGS) $(LDLINKS) -o $(BINARY) main.c game.c

clean:
	rm $(BINARY)

install: build
	cp $(BINARY) $(DEST)
	chown root.root $(DEST)
	chmod 755 $(DEST)

uninstall:
	rm $(DEST)
