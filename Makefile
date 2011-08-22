default:
	g++ token.cpp lexer.cpp main.cpp -o iasm

clean:
	rm iasm
