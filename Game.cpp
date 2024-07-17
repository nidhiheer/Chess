#include <iostream>
#include <vector>

using namespace std;

enum Color { WHITE, BLACK };
enum PieceType { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };

class Piece {
protected:
    PieceType type;
    Color color;
public:
    Piece(PieceType type, Color color) : type(type), color(color) {}
    virtual bool isValidMove(vector<vector<Piece*>>& pieces, int startX, int startY, int endX, int endY) = 0;
    Color getColor() { return color; }
    PieceType getType() { return type; }
};

class King : public Piece {
public:
    King(Color color) : Piece(KING, color) {}
    bool isValidMove(vector<vector<Piece*>>& pieces, int startX, int startY, int endX, int endY) override {
        if (abs(endX - startX) <= 1 && abs(endY - startY) <= 1) {
            return true;
        }
        return false;
    }
};

class Queen : public Piece {
public:
    Queen(Color color) : Piece(QUEEN, color) {}
    bool isValidMove(vector<vector<Piece*>>& pieces, int startX, int startY, int endX, int endY) override {
        if (abs(endX - startX) == abs(endY - startY) || endX == startX || endY == startY) {
            return true;
        }
        return false;
    }
};

class Rook : public Piece {
public:
    Rook(Color color) : Piece(ROOK, color) {}
    bool isValidMove(vector<vector<Piece*>>& pieces, int startX, int startY, int endX, int endY) override {
        if (endX == startX || endY == startY) {
            return true;
        }
        return false;
    }
};

class Bishop : public Piece {
public:
    Bishop(Color color) : Piece(BISHOP, color) {}
    bool isValidMove(vector<vector<Piece*>>& pieces, int startX, int startY, int endX, int endY) override {
        if (abs(endX - startX) == abs(endY - startY)) {
            return true;
        }
        return false;
    }
};

class Knight : public Piece {
public:
    Knight(Color color) : Piece(KNIGHT, color) {}
    bool isValidMove(vector<vector<Piece*>>& pieces, int startX, int startY, int endX, int endY) override {
        if ((abs(endX - startX) == 2 && abs(endY - startY) == 1) || (abs(endX - startX) == 1 && abs(endY - startY) == 2)) {
            return true;
        }
        return false;
    }
};

class Pawn : public Piece {
public:
    Pawn(Color color) : Piece(PAWN, color) {}
    bool isValidMove(vector<vector<Piece*>>& pieces, int startX, int startY, int endX, int endY) override {
        if (color == WHITE) {
            if (startY == 1 && endY == 3 && startY == endY - 2 && startX == endX) {
                for (int i = startY; i < endY; i++) {
                    if (pieces[startX][i] != nullptr) {
                        return false;
                    }
                }
                return true;
            } else if (endY == startY + 1 && abs(endX - startX) <= 1) {
                if (endX == startX) {
                    if (pieces[endX][endY] == nullptr) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    if (pieces[endX][endY] != nullptr && pieces[endX][endY]->getColor() != color) {
                        return true;
                    } else {
                        return false;
                    }
                }
            } else {
                return false;
            }
        } else {
            if (startY == 6 && endY == 4 && startY == endY + 2 && startX == endX) {
                for (int i = startY; i > endY; i--) {
                    if (pieces[startX][i] != nullptr) {
                        return false;
                    }
                }
                return true;
            } else if (endY == startY - 1 && abs(endX - startX) <= 1) {
                if (endX == startX) {
                    if (pieces[endX][endY] == nullptr) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    if (pieces[endX][endY] != nullptr && pieces[endX][endY]->getColor() != color) {
                        return true;
                    } else {
                        return false;
                    }
                }
            } else {
                return false;
            }
        }
    }
    };
    class Board {
public:
    vector<vector<Piece*>> pieces;
    

    Board() {
        pieces.resize(8, vector<Piece*>(8, nullptr));
        for (int i = 0; i < 8; i++) {
            pieces[1][i] = new Pawn(WHITE);
            pieces[6][i] = new Pawn(BLACK);
        }
        pieces[0][0] = pieces[0][7] = new Rook(WHITE);
        pieces[0][1] = pieces[0][6] = new Knight(WHITE);
        pieces[0][2] = pieces[0][5] = new Bishop(WHITE);
        pieces[0][3] = new Queen(WHITE);
        pieces[0][4] = new King(WHITE);
        pieces[7][0] = pieces[7][7] = new Rook(BLACK);
        pieces[7][1] = pieces[7][6] = new Knight(BLACK);
        pieces[7][2] = pieces[7][5] = new Bishop(BLACK);
        pieces[7][3] = new Queen(BLACK);
        pieces[7][4] = new King(BLACK);
    }

   
    void makeMove( vector<vector<Piece*>> pieces, int startX, int startY, int endX, int endY) {
    Piece* piece = pieces[startX][startY];
    if (piece != nullptr && piece->isValidMove(pieces, startX, startY, endX, endY)) {
        pieces[endX][endY] = piece;
        pieces[startX][startY] = nullptr;
       
        pieces[startX][startY]=pieces[endX][endY];
       
    }
}

    bool isCheckmate(Color color) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (pieces[i][j] != nullptr && pieces[i][j]->getColor() == color) {
                    if (pieces[i][j]->getType() == KING) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};
void printBoard(Board board){
        cout << "  1  2  3  4  5  6  7  8" << endl;
        for (int i = 7; i >= 0; i--) {
            cout << i + 1 << " ";
            for (int j = 0; j < 8; j++) {
                if (board.pieces[i][j]!= nullptr) {
                    char pieceChar;
                    switch (board.pieces[i][j]->getType()) {
                        case KING:
                            pieceChar = 'K';
                            break;
                        case QUEEN:
                            pieceChar = 'Q';
                            break;
                        case ROOK:
                            pieceChar = 'R';
                            break;
                        case BISHOP:
                            pieceChar = 'B';
                            break;
                        case KNIGHT:
                            pieceChar = 'N';
                            break;
                        case PAWN:
                            pieceChar = 'P';
                            break;
                    }
                    if (board.pieces[i][j]->getColor() == WHITE) {
                        cout << pieceChar << "w ";
                    } else {
                        cout << pieceChar << "b ";
                    }
                } else {
                    cout << "-- ";
                      }
            }
            cout << endl;
        }
    }

int main() {
    Board board;
    
    printBoard(board);
    while (true) {
        int startX, startY, endX, endY;
        cout << "Enter start position (x y): ";
        cin >> startX >> startY;
        cout << "Enter end position (x y): ";
        cin >> endX >> endY;
        startX--; startY--; endX--; endY--; // convert to 0-based indexing
        board.makeMove(board.pieces,startX, startY, endX, endY);
        printBoard(board);
    }
    return 0;
}