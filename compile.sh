#!/bin/bash

gcc -o prod_con main.c \
    src/buffer.c \
    src/helpers.c \
    src/input.c \
    src/output.c \
    -lpthread