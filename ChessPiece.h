/* ChessPiece.h - header file for the class ChessPiece */

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <iostream>
#include "ChessBoard.h"

/********************** Chess Piece Class **************/

const int MAX_NAME_LENGTH = 10;

class ChessBoard;

class ChessPiece {
	protected:
		int move_count;
		char team;
		bool exists;
		const char *name;
		bool check_diagonal(const ChessBoard &board, int row1, int col1, int row2, int col2);
		bool check_straight(const ChessBoard &board, int row1, int col1, int row2, int col2);
		
		//char *location;
	public:
		ChessPiece(char color);
		virtual ~ChessPiece();

		const char get_team();
		const char *get_name();

		virtual bool move_is_valid(const ChessBoard &board, int row1, int col1, int row2, int col2) = 0;

};

class King : public ChessPiece {
	private:
		bool in_check();
	public:
		King(char color);
		bool move_is_valid(const ChessBoard &board, int row1, int col1, int row2, int col2) override;
};

class Queen : public ChessPiece {
	private:
			
	public:
		Queen(char color);
		bool move_is_valid(const ChessBoard &board, int row1, int col1, int row2, int col2) override;

};

class Rook : public ChessPiece {
	private:
	
	public:
		Rook(char color);
		bool move_is_valid(const ChessBoard &board, int row1, int col1, int row2, int col2) override;
};

class Bishop : public ChessPiece {
	private:

	public:
		Bishop(char color);
		bool move_is_valid(const ChessBoard &board, int row1, int col1, int row2, int col2) override;
};

class Knight : public ChessPiece {
	private:
	public:
		Knight(char color);
		bool move_is_valid(const ChessBoard &board, int row1, int col1, int row2, int col2) override;
};

class Pawn : public ChessPiece {
	private:

	public:
		Pawn(char color);
		bool move_is_valid(const ChessBoard &board, int row1, int col1, int row2, int col2) override;
};

#endif
