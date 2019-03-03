FROM ubuntu:16.04

RUN apt-get update -y && \
    apt-get install -y gcc

COPY main.c /app/main.c
ADD ./src/ /app/src/

WORKDIR /app

RUN gcc -o prod_con main.c \
    src/buffer.c \
    src/helpers.c \
    src/input.c \
    src/output.c \
    -lpthread
