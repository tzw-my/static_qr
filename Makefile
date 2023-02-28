
.PHONY: CFLAGS != pkg-config --cflags libsodium
.PHONY: LFLAGS != pkg-config --libs libsodium

CFLAGS = $(shell pkg-config --cflags libsodium	)
LFLAGS = $(shell pkg-config --libs libsodium	)

.PHONY: CC = zig cc
CC = zig cc

main.o: makefile src/**/*.c
	@ $(CC) $(CFLAGS) $(LFLAGS) src/main.c -o main.o

all: \
	dist/sodium.linux.aarch64 		\
	dist/sodium.linux.x64 			\
	dist/sodium.darwin.arm 			\
	dist/sodium.darwin.x86 			\
	dist/sodium.x86_64-windows.exe

dist/sodium.linux.aarch64: makefile src/**/*.c
	@ $(CC) -target aarch64-linux-musl $(CFLAGS) $(LFLAGS) src/main.c -o dist/sodium.linux.aarch64

dist/sodium.darwin.x86: makefile src/**/*.c
	@ $(CC) -target x86-64-macos $(CFLAGS) $(LFLAGS) src/main.c -o dist/sodium.darwin.x86

dist/sodium.darwin.arm: makefile src/**/*.c
	@ $(CC) -target aarch64-macos $(CFLAGS) $(LFLAGS) src/main.c -o dist/sodium.darwin.arm

dist/sodium.linux.x64: makefile src/**/*.c
	@ $(CC) -target x86_64-linux-musl $(CFLAGS) $(LFLAGS) src/main.c -o dist/sodium.linux.x64

dist/sodium.x86_64-windows.exe: makefile src/**/*.c
	@ $(CC) -target x86_64-windows $(CFLAGS) $(LFLAGS) src/main.c -o dist/sodium.x86_64-windows.exe

run: main.o
	@ ./main.o

clean:
	rm -rf main.o
