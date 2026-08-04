ifeq ($(OS),Windows_NT)
	EXEC = main.exe
	RM = del /Q
else
	EXEC = main
	RM = rm -f
endif

$(EXEC) : main.o game.o historique.o view.o mask.o board.o 
	g++ main.o game.o historique.o view.o mask.o board.o -o $(EXEC)

main.o : main.cpp
	g++ -c main.cpp

game.o : game.cpp
	g++ -c game.cpp

historique.o : historique.cpp
	g++ -c historique.cpp

view.o : view.cpp
	g++ -c view.cpp

mask.o : mask.cpp
	g++ -c mask.cpp

board.o : board.cpp
	g++ -c board.cpp

clean:
	$(RM) *.o $(EXEC)