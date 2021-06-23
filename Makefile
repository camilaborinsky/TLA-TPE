demo: demo.c figures.c figures.h
	gcc demo.c figures.c -o demo -lncurses -lm

run_demo:
	./demo