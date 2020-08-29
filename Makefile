all:
	clang main.c -o octowine

install: all
	sudo mv octowine /usr/bin/
