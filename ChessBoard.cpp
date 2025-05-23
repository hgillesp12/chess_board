#include <iostream>
#include "ChessBoard.h"
#include "ChessPiece.h"
using namespace std;

ChessBoard::ChessBoard() {
	clear_board();
}

ChessBoard::~ChessBoard() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != nullptr) {
				delete board[i][j];
			}
		}
	}
}

void ChessBoard::clear_board() {
        for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                        board[i][j] = nullptr;
                }
        }
}


void ChessBoard::loadState(const char *fen_positions) {
	
	clear_board();

	int rank = 8;
	char file = 'A';

	int i = 0;
	while (fen_positions[i] != ' ') {
		if (fen_positions[i] == '/') {
			rank--;
			file = 'A';
		} else if (isdigit(fen_positions[i])) {
			file += fen_positions[i];
		} else {	
			char piece_id = fen_positions[i];
			int row = rank - 1;
			int col = file - 'A';
			cout << row << ", " << col << " ";
			char color;
			if (islower(piece_id)) {
				color = 'b';
			} else {
				color = 'w';
			}
			switch (tolower(piece_id)) {
				case 'k': board[row][col] = new King(color); break;
				case 'q': board[row][col] = new Queen(color); break;
				case 'r': board[row][col] = new Rook(color); break;
				case 'b': board[row][col] = new Bishop(color); break;
				case 'n': board[row][col] = new Knight(color); break;
				case 'p': board[row][col] = new Pawn(color); break;
			}
			cout << row << col << rank << file << piece_id << endl;
			file++;
		}
		i++;
	}

	turn = fen_positions[++i];
	cout << "it is " << turn << " turn." << endl;

	cout << "A new board state is loaded!" << endl;

}

bool ChessBoard::in_bounds(const int row, const int col) {
	if (row > 7 || row < 0) {
		return false;
	}
	if (col > 7 || col < 0) {
		return false;
	}
	return true;
}


int ChessBoard::get_row(const char *position) {
	char rank = position[1];
	int row = rank - '0' - 1;
	return row;
}

int ChessBoard::get_col(const char *position) {
	int file = position[0];
	int col = file - 'A';
	return col;
}


void ChessBoard::submitMove(const char *original_position, const char *intended_position) {
	// check original position is in bounds
	int original_row = get_row(original_position);
	int original_col = get_col(original_position);
	cout << original_row  << " " << original_col << endl;
	if (!in_bounds(original_row, original_col)) {
		cerr << "Error: " << original_position << " is not in bounds.";
		return;
	}
	
	// check intended position is in bounds
	int intended_row = get_row(intended_position);
	int intended_col = get_col(intended_position);
	cout << intended_row  << " " << intended_col << endl;
	if (!in_bounds(intended_row, intended_col)) {
		cerr << "Error: " << intended_position << " is not in bounds.";
		return;
	}


	// ensure there is actually a piece there (not nullptr)
	if (board[original_row][original_col] == nullptr) {
		cerr << "There is no piece at position " << original_position << "!" << endl;
		return;
	}
	
	// now retrieve the piece at the spot since it exists
	ChessPiece *piece = board[original_row][original_col];

	// now check it is actually that team's turn
	if (piece->get_team() != turn) {
		cerr << "It is not " << piece->get_team() << "'s turn to move!" << endl;
		return;
	}

	// check the move is valid for the given piece
	if (!piece->move_is_valid(*this, original_row, original_col, intended_row, intended_col)) {
		cerr << piece->get_team() << "'s " << piece->get_name() << " cannot move to " << intended_position << "!" << endl;
		return;
	}

	// move is valid so make it
	ChessPiece *taken_piece = board[intended_row][intended_col];
	cout << piece->get_team() << "'s " << piece->get_name() << " moves from " << original_position << " to " << intended_position;
	(taken_piece == nullptr ? cout << endl : cout << " taking " << taken_piece->get_team() << "'s " << taken_piece->get_name() << endl);
	delete taken_piece;

	// switch the place of the piece
	board[intended_row][intended_col] = piece;
	board[original_row][original_col] = nullptr;
	
	// switch whose turn it is
	(piece->get_team() == 'w' ? turn = 'b' : turn = 'w');

	// check if anyone is now in check
	// TODO //
	// TODO: Need to check before any move is valid that the king is not in check 
	return;
}


