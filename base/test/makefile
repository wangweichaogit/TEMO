#! /bin/bash

src = $(wildcard *.cc)
des = $(patsubst %.cc,%,$(src))
CC = g++
opt = -std=c++11
lib = -lpthread
end:$(des)
%:%.cc
	$(CC) $< -o $@ $(opt) $(lib)
clean:
	@echo romving...
	-rm -rf  $(des)
.PHONY:clean
