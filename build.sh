#!/bin/bash
g++ -c main.cpp && g++ main.o -o simple_pong -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio && ./simple_pong
