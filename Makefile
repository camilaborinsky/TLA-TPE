PARSER_SOURCES =utils/ast.c utils/symbol_table.c utils/code_generator.c
PARSER_HEADERS = utils/types.h utils/symbol_table.h utils/code_generator.h

all: demo parser

parser: grammar/grammar.y grammar/definitions.l $(PARSER_SOURCES) $(PARSER_HEADERS)
	yacc -d grammar/grammar.y -Wno-other -Wno-yacc -Wno-conflicts-sr
	lex grammar/definitions.l
	gcc -o parser lex.yy.c y.tab.c $(PARSER_SOURCES) -Wno-implicit-int -Wno-incompatible-pointer-types   -ly

demo: demo.c lib/figures.c lib/figures.h
	$(CC) demo.c lib/figures.c lib/handlers.c -o demo  -Wall -fsanitize=address -pedantic -lncurses -lm

run_demo:
	./demo

clean:
	rm -rf demo lex.yy.c y.tab.c y.tab.h parser