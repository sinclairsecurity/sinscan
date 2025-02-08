#########
# Makefile for sinscan
# Author: sinclairsecurity
#########

CC = gcc
CFLAGS = -Wall -std=c99 -Wextra -pedantic -D_POSIX_C_SOURCE=200112L

SRC_DIR = src
INC_DIR = include

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:.c=.o)
TARGET = sinscan

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(TARGET)
