PARSER_SOURCES := $(shell find utils -name '*.c')
PARSER_HEADERS := $(shell find utils -name '*.h')
TO = compile
FROM=test.td

all: demo parser

parser: grammar/grammar.y grammar/definitions.l $(PARSER_SOURCES) $(PARSER_HEADERS)
	yacc -d grammar/grammar.y -Wno-other -Wno-yacc -Wno-conflicts-sr
	lex grammar/definitions.l
	gcc -o parser lex.yy.c y.tab.c $(PARSER_SOURCES) -g -Wno-implicit-int -Wno-incompatible-pointer-types   -ly

compile:
	./parser < $(FROM) > $(TO).c && $(CC) $(TO).c lib/figures.c lib/handlers.c -o $(TO) -w -lncurses -lm

clean:
	rm -rf demo lex.yy.c y.tab.c y.tab.h parser compile

.PHONY: compile