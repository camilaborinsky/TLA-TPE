demo: demo.c lib/figures.c lib/figures.h
	gcc demo.c lib/figures.c lib/handlers.c -o demo  -Wall -fsanitize=address -pedantic -lncurses -lm

run_demo:
	./demo