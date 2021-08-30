all:
	flex -o scanner.cpp scanner.l
	bison -o parser.cpp parser.y
	g++ -g main.cpp nfa.cpp scanner.cpp parser.cpp interpreter.cpp -o ComplementNFA

clean:
	rm -rf scanner.cpp
	rm -rf parser.cpp parser.hpp location.hh position.hh stack.hh
	rm -rf a.out ComplementNFA
