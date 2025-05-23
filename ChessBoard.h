/* ChessBoard.h - header file for the class ChessBoard */

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include "ChessPiece.h"

/****************** Chess Board Class *****************/

class ChessPiece;

class ChessBoard {
	private:
		char turn;
		bool in_bounds(const int row, const int col);
		void clear_board();
	
	public:
		ChessPiece *board[8][8];
		
		/* Initialize the board to 8x8 nullptrs */
		ChessBoard();
		~ChessBoard();

		/* loadState takes in an FEN string describing
		 * the state of a chess board and then 
		 * instantiates pieces to set up the board in
		 * the given configuration
		 *
		 * @param: fen_positions A character array with 
		 * the given chess piece configuration
		 */
		void loadState(const char *fen_positions);

		/* submitMove takes in two board positions and
		 * checks if the chess piece at the first location
		 * may move to the second location
		 *
		 * @param: 
		 */
		void submitMove(const char *original_position, const char *intended_position);

		int get_row(const char *position);
	       	int get_col(const char *position);	
};

#endif
