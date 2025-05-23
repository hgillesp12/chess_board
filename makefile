chess: ChessMain.o ChessPiece.o ChessBoard.o
	g++ -g ChessMain.o ChessPiece.o ChessBoard.o -o chess

ChessBoard.o: ChessBoard.cpp ChessBoard.h ChessPiece.h
	g++ -Wall -g -c ChessBoard.cpp

ChessPiece.o: ChessPiece.cpp ChessPiece.h ChessBoard.h
	g++ -Wall -g -c ChessPiece.cpp

ChessMain.o: ChessMain.cpp ChessBoard.h
	g++ -Wall -g -c ChessMain.cpp
clean:
	rm -rf *.o
