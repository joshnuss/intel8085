OPTS := -g 

default:
	g++ $(OPTS) token.cpp lexer.cpp main.cpp -o iasm

clean:
	rm iasm
