OPTS := -g 

default:
	g++ $(OPTS) instruction.cpp parser.cpp token.cpp lexer.cpp main.cpp -o iasm

clean:
	rm iasm
