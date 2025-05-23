#include <iostream>
#include "ChessPiece.h"
#include "ChessBoard.h"
using namespace std;


ChessPiece::ChessPiece(char color) : team(color) {
	move_count = 0;
	exists = true;

}

ChessPiece::~ChessPiece() {
	return;
}

const char ChessPiece::get_team() {
	return team;
}

const char *ChessPiece::get_name() {
	return name;
}

bool ChessPiece::check_diagonal(const ChessBoard &board, int row1, int col1, int row2, int col2) {
        // first make sure the diagonal is correct i.e. rank_distance should always equal file_distance
        int rank_distance = row2 - row1;
        int direction_rank = rank_distance / abs(rank_distance);
        int file_distance = col2 - col1;
        int direction_file = file_distance / abs(file_distance);

        if (abs(rank_distance) != abs(file_distance)) {
                cerr << "Error: " << team << "'s " << name << " is not moving along a diagonal." << endl;
                return false;
        }

        // now make sure every diagonal spot in between is unoccupied
        for (int i = 1; i < abs(rank_distance); i++) {
                ChessPiece *curr_piece = board.board[row1 + (i * direction_rank)][col1 + (i * direction_file)];
                if (curr_piece != nullptr) {
                        cerr << "Error: " << team << "'s " << name << " cannot jump over a piece." << endl;
                        return false;
                }
        }

        return true;


}

bool ChessPiece::check_straight(const ChessBoard &board, int row1, int col1, int row2, int col2) {

        // first make sure it is either moving all in one rank or all in one file
        int rank_distance = row2 - row1;
        int file_distance = col2 - col1;

        if ((abs(rank_distance) > 0 && file_distance != 0) ||
            (abs(file_distance) > 0 && rank_distance != 0)) {
                cerr << "Error: " << team << "'s " << name << " is not moving in a straight line." << endl;
                return false;
        }

        // make sure every spot in between is unoccupied
        // in the case we are moving up / down rows
        if (abs(rank_distance) > 0) {
                int direction_rank = rank_distance / abs(rank_distance);
                for (int i = 1; i < abs(rank_distance); i++) {
                        ChessPiece *curr_piece = board.board[row1 + (i * direction_rank)][col1];
                        if (curr_piece != nullptr) {
                                cerr << "Error: " << team << "'s " << name << " cannot jump over a piece." << endl;
                                return false;
                        }

                }
                return true;
        }

        // in the case we are moving along files (columns)
        // implied abs(file_distance) > 0
        int direction_file = file_distance / abs(file_distance);
        for (int i = 1; i < abs(file_distance); i++) {
                ChessPiece *curr_piece = board.board[row1][col1 + (i * direction_file)];
                if (curr_piece != nullptr) {
                        cerr << "Error: " << team << "'s " << name << " cannot jump over a piece." << endl;
                        return false;
                }
        }

        return true;


}


King::King(char color) : ChessPiece(color) {
	name = "King";
        cout << "Created " << team << name << endl;
}

bool King::move_is_valid(const ChessBoard &board, int row1, int col1, int row2, int col2) {
	
	int rank_distance = row2 - row1;
	int file_distance = col2 - col1;

	// both must be one or less
	if (abs(rank_distance) > 1 || abs(file_distance) > 1) {
		cerr << "Error: " << team << "'s " << name << " cannot move more than one spot." << endl;
		return false;
	}

	return true;
}


Queen::Queen(char color) : ChessPiece(color) {
	name = "Queen";
        cout << "Created " << team << name << endl;
}

bool Queen::move_is_valid(const ChessBoard &board, int row1, int col1, int row2, int col2) {

	if (!check_diagonal(board, row1, col1, row2, col2) && !check_straight(board, row1, col1, row2, col2)) {
		return false;
	}

	return true;
}


Rook::Rook(char color) : ChessPiece(color) {
	name = "Rook";
        cout << "Created " << team << name << endl;
}

bool Rook::move_is_valid(const ChessBoard &board, int row1, int col1, int row2, int col2) {
	/*
	// first make sure it is either moving all in one rank or all in one file
	int rank_distance = row2 - row1;
	int file_distance = col2 - col1;
	
	if ((abs(rank_distance) > 0 && file_distance != 0) ||
	    (abs(file_distance) > 0 && rank_distance != 0)) {
		cerr << "Error: " << team << "'s " << name << " is not moving in a straight line." << endl;
		return false;
	} 

	// make sure every spot in between is unoccupied
	// in the case we are moving up / down rows
	if (abs(rank_distance) > 0) {
		int direction_rank = rank_distance / abs(rank_distance);
		for (int i = 1; i < abs(rank_distance); i++) {
			ChessPiece *curr_piece = board.board[row1 + (i * direction_rank)][col1];
			if (curr_piece != nullptr) {
				cerr << "Error: " << team << "'s " << name << " cannot jump over a piece." << endl;
				return false;
			}
			
		}
		return true;
	}

	// in the case we are moving along files (columns) 
	// implied abs(file_distance) > 0
	int direction_file = file_distance / abs(file_distance);
	for (int i = 1; i < abs(file_distance); i++) {
		ChessPiece *curr_piece = board.board[row1][col1 + (i * direction_file)];
		if (curr_piece != nullptr) {
			cerr << "Error: " << team << "'s " << name << " cannot jump over a piece." << endl;
			return false;
		}
	}

	return true;
	*/
	return check_straight(board, row1, col1, row2, col2);

}

Bishop::Bishop(char color) : ChessPiece(color) {
	name = "Bishop";
        cout << "Created " << team << name << endl;
}

bool Bishop::move_is_valid(const ChessBoard &board, int row1, int col1, int row2, int col2) {
	/*
	// first make sure the diagonal is correct i.e. rank_distance should always equal file_distance
	int rank_distance = row2 - row1;
	int direction_rank = rank_distance / abs(rank_distance);
	int file_distance = col2 - col1;
	int direction_file = file_distance / abs(file_distance);

	if (abs(rank_distance) != abs(file_distance)) {
		cerr << "Error: " << team << "'s " << name << " is not moving along a diagonal." << endl;
		return false;
	}
	
	// now make sure every diagonal spot in between is unoccupied
	for (int i = 1; i < abs(rank_distance); i++) {
		ChessPiece *curr_piece = board.board[row1 + (i * direction_rank)][col1 + (i * direction_file)];
		if (curr_piece != nullptr) {
			cerr << "Error: " << team << "'s " << name << " cannot jump over a piece." << endl;
			return false;
		}
	}

	return true;
	*/
	return check_diagonal(board, row1, col1, row2, col2);
}

Knight::Knight(char color) : ChessPiece(color) {
        name = "Knight";
        cout << "Created " << team << name << endl;
}

bool Knight::move_is_valid(const ChessBoard &board, int row1, int col1, int row2, int col2) {
	int rank_distance = row2 - row1;
	int file_distance = col2 - col1;

	if ((abs(rank_distance) == 1 && abs(file_distance) != 2) ||
	    (abs(rank_distance) == 2 && abs(file_distance) != 1)) {
		cerr << "Error: " << team << "'s " << name << " move is trying to move " << rank_distance << " vertically and " << file_distance << " horizontally." << endl;
		return false;
	} 

	return true;
}

Pawn::Pawn(char color) : ChessPiece(color) {
        name = "Pawn";
        cout << "Created " << team << name << endl;
}

bool Pawn::move_is_valid(const ChessBoard &board, int row1, int col1, int row2, int col2) {

	cout << team << endl;

	// get the right direction of motion
	int direction;
	(team == 'w' ? direction = 1 : direction = -1);

	// get the distance to move
	int distance = row2 - row1;
	int file_movement = col2 - col1;
	ChessPiece *piece_at_destination = board.board[row2][col2];

	// make sure if it is two it is the first move
	if (move_count != 0 && abs(distance) == 2) {
		cerr << "Error: " << team << "'s " << name << " cannot move two spots since it is on turn number: " << move_count << endl;
		return false;
	}

	// make sure it is in right range
	if (abs(distance) > 2 || distance == 0) {
		cerr << "Error: " << team << "'s " << name << " cannot move " << distance << " spaces." << endl;
		return false;
	}

	cout << "Distance: " << distance << " Direction: " << direction << endl;

	// make sure the piece is moving in the right direction
	if (distance != direction && distance != direction * 2) {
		cerr << "Error: " << team << "'s " << name << " tried to move in wrong direction!" << endl;
		return false;
	}

	// make sure not trying to move two forward and file
	if (abs(distance) == 2 && abs(file_movement) > 0) {
		cerr << "Error: " << team << "'s " << name << " cannot move two by rank and one by file." << endl;
		return false;
	}

	// process a single forward (non-jumping movement) 
	if (abs(distance) == 1 && abs(file_movement) == 0) {
		if (piece_at_destination != nullptr) {
			cerr << team << "'s " << name << " cannot move to new position << replace >> " << endl;
			return false;
		}
		return true;
	}

	// process a double forward (non-jumping movement)
	if (abs(distance) == 2 && abs(file_movement) == 0) {
		if (piece_at_destination != nullptr || board.board[row2][col2 - (1* direction)] != nullptr) {
			cerr << team << "'s " << name << " cannot move to new position because both spots are not unoccupied!" << endl;
			return false;
		}
		return true;
	}

	// make sure the file movement is reasonable
	if (abs(file_movement) > 1) {
		cerr << "Error: " << team << "'s " << name << " cannot move more than one spot by file." << endl;
		return false;
	}

	// process a jumping movement
	if (abs(distance) != 1 && abs(file_movement) != 1) {
		cerr << "Error: " << team << "'s " << name << " has a mixup." << endl;
		return false;
	}
	// make sure the spot is occupied 
	if (piece_at_destination == nullptr) {
		cerr << team << "'s " << name << " cannot jump an unoccupied position." << endl;
		return false;
	}

	return true;
	
}

