CC = gcc

LDLIBS = -lglut -lGLU -lGL

# 引数をTARGETとして扱うための設定
TARGET = $(firstword $(MAKECMDGOALS))

# デフォルトターゲット
all: $(TARGET)

# ターゲットを指定するためのルール
$(TARGET): $(TARGET).c
	$(CC) $(TARGET).c $(LDLIBS) -o $(TARGET)

# クリーンアップルール
clean:
	rm -f $(TARGET)

# Makefile の使い方のヒント
help:
	@echo "Usage: make <filename_without_extension>"
