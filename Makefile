all: demo parser

parser: grammar/grammar.y grammar/definitions.l
	yacc -d grammar/grammar.y -Wno-other -Wno-yacc -Wno-conflicts-sr
	lex grammar/definitions.l
	gcc -o parser lex.yy.c y.tab.c  -Wno-implicit-int   -ly

demo: demo.c lib/figures.c lib/figures.h
	$(CC) demo.c lib/figures.c lib/handlers.c -o demo  -Wall -fsanitize=address -pedantic -lncurses -lm

run_demo:
	./demo

clean:
	rm -rf demo lex.yy.c y.tab.c y.tab.h parser