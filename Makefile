CC = gcc

LDLIBS = -lglut -lGLU -lGL

# デフォルトターゲット
all: main

# 個別のターゲット
src1: main.c
	$(CC) main.c $(LDLIBS) -o main

# クリーンアップルール
clean:
	rm -f main