# specify your own C compiler if you don't have gcc
# change from `gcc` to `cc` for FreeBSD
CC = gcc


# flags (may be gcc-specific)
FLAGS = -O3 -Wall


# debug flags (if you want a debuggable version)
DEBUG = -g -Wall


# asm flags (if you want to read the assembly output)
ASM = -S\
      -fverbose-asm\
      -masm=intel\
      -fno-asynchronous-unwind-tables\
      -Wall


# flags for gprof
PROF = -pg -Wall


# flags for linking SDL2
# change to `SDL2 = -D_REENTRANT -I/usr/local/include -L/usr/local/lib -lSDL2` for FreeBSD
SDL2 = -D_REENTRANT -I/usr/include/SDL2 -lSDL2


# name of the target
TARGET = test.x86


# required sourcefiles
SOURCE = src/mchar_t.c\
	 src/mchar_t.h\
	 src/test.c


# expected object files for main.c
OBJS = obj/mchar_t.o


$(TARGET): $(SOURCE)
	$(CC) $(FLAGS) -c src/mchar_t.c -o obj/mchar_t.o
	$(CC) $(FLAGS) $(OBJS) src/main.c -o $(TARGET) $(SDL2)

run: $(TARGET)
	./$(TARGET)

prof: $(SOURCE)
	$(CC) $(PROF) -c src/mchar_t.c -o obj/mchar_t.o
	$(CC) $(PROF) $(OBJS) src/main.c -o $(TARGET) $(SDL2)

asm: $(SOURCE)
	$(CC) $(ASM) -c src/mchar_t.c -o src/mchar_t.s
	$(CC) $(ASM) src/main.c -o src/main.s

debug: $(SOURCE)
	$(CC) $(DEBUG) -c src/mchar_t.c -o src/mchar_t.o
	$(CC) $(DEBUG) $(OBJS) src/main.c -o $(TARGET) $(SDL2)


clean: $(TARGET) $(OBJS)
	rm $(TARGET)
	rm $(OBJS)

clean-asm: src/mchar_t.s src/main.s
	rm src/mchar_t.s src/main.s

clean-prof: gmon.out $(TARGET)
	rm gmon.out $(TARGET)

