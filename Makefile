OPTS := 

default:
	g++ -c $(OPTS) instruction.cpp parser.cpp token.cpp lexer.cpp main.cpp 
	g++ -l:libboost_program_options.so.1.42.0 *.o -o iasm

clean:
	rm *.o
	rm iasm
