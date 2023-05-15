#include "Board.h"

void Board::setStartBoard() {
    for (auto& row : piecesOnBoard) {
        for (auto& p : row) {
            p = nullptr;
        }
    }

    int index = 0;
    for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 8; x++) {
            piecesOnBoard[x][y] = allPieces[index++];
        }
    }
    for (int y = 6; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            piecesOnBoard[x][y] = allPieces[index++];
        }
    }

    bKing = piecesOnBoard[4][0];
    wKing = piecesOnBoard[4][7];

    for (auto& p : allPieces) {
        (p->color == Color::White) ? p->setKing(wKing) : p->setKing(bKing);
        p->updateTableMove(piecesOnBoard);
    }
}

Board::Board() {
    allPieces.push_back(new Rook(0, 0, Color::Black));
    allPieces.push_back(new Knight(1, 0, Color::Black));
    allPieces.push_back(new Bishop(2, 0, Color::Black));
    allPieces.push_back(new Queen(3, 0, Color::Black));
    allPieces.push_back(new King(4, 0, Color::Black));
    allPieces.push_back(new Bishop(5, 0, Color::Black));
    allPieces.push_back(new Knight(6, 0, Color::Black));
    allPieces.push_back(new Rook(7, 0, Color::Black));
    for (int i = 0; i < 8; i++) {
        allPieces.push_back(new Pawn(i, 1, Color::Black));
    }

    for (int i = 0; i < 8; i++) {
        allPieces.push_back(new Pawn(i, 6, Color::White));
    }
    allPieces.push_back(new Rook(0, 7, Color::White));
    allPieces.push_back(new Knight(1, 7, Color::White));
    allPieces.push_back(new Bishop(2, 7, Color::White));
    allPieces.push_back(new Queen(3, 7, Color::White));
    allPieces.push_back(new King(4, 7, Color::White));
    allPieces.push_back(new Bishop(5, 7, Color::White));
    allPieces.push_back(new Knight(6, 7, Color::White));
    allPieces.push_back(new Rook(7, 7, Color::White));
    
    piecesOnBoard.resize(8);
    for (auto& row : piecesOnBoard) {
        row.resize(8);
    }
    setStartBoard();
}

Board::~Board() {
    for (auto& row : piecesOnBoard) {
        for (auto& piece : row) {
            if (piece) delete piece;
        }
    }
}

bool Board::movePiece(Piece* piece, int newX, int newY) {
    
    if (!piece->move(piecesOnBoard, newX, newY)) return false;
    
    // If pawn -> check promotion

    for (auto& p : allPieces) {
        p->updateTableMove(piecesOnBoard);
    }

    // UPdate table move for 2 kings (cuz king must know enemies' attack range before moving)
    if (bKing->isBeingAttacked(piecesOnBoard, bKing->color)) {
            cout << "BLACK in CHECK!" << endl;
    }
    bKing->updateTableMove(piecesOnBoard);

    if (wKing->isBeingAttacked(piecesOnBoard, wKing->color)) {
        cout << "BLACK in CHECK!" << endl;
    }
    wKing->updateTableMove(piecesOnBoard);
    

    return true;
}

void Board::undo() {
}

void Board::redo() {
}


