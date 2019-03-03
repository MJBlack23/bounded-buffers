FROM ubuntu:16.04

RUN apt-get update -y && \
    apt-get install -y gcc

ADD ./src/ /app/src/

WORKDIR /app

RUN gcc src/buffer.c src/output.c -o buff -lpthread
