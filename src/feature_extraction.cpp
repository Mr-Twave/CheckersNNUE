#
#include <vector>
#include <cmath>

std::vector<float> extractFeatures(const GameState& state) {
    int redPieces = 0, blackPieces = 0, redKings = 0, blackKings = 0;
    for(const auto& row : state.board) {
        for(const auto& piece : row) {
            switch(piece) {
                case RED: ++redPieces; break;
                case BLACK: ++blackPieces; break;
                case RED_KING: ++redKings; break;
                case BLACK_KING: ++blackKings; break;
                default: break;
            }
        }
    }

    // Normalize features to be within a certain range, e.g., [0, 1]
    // This is important for neural network performance
    std::vector<float> features = {
        redPieces / 12.0f, blackPieces / 12.0f, 
        redKings / 12.0f, blackKings / 12.0f
    };

    return features;
}

std::vector<float> extractFeatures(const GameState& state) {
    int redPieces = 0, blackPieces = 0, redKings = 0, blackKings = 0;
    int piecesInKingRowRed = 0, piecesInKingRowBlack = 0;
    int piecesInCenter = 0; // Pieces in the 4 central squares

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            Piece piece = state.board[y][x];
            switch (piece) {
                case RED:
                    redPieces++;
                    if (y == 7) piecesInKingRowRed++;
                    break;
                case BLACK:
                    blackPieces++;
                    if (y == 0) piecesInKingRowBlack++;
                    break;
                case RED_KING:
                    redKings++;
                    break;
                case BLACK_KING:
                    blackKings++;
                    break;
                default:
                    break;
            }

            // Count pieces in the central 4x4 square
            if (y >= 2 && y <= 5 && x >= 2 && x <= 5) {
                if (piece != EMPTY) piecesInCenter++;
            }
        }
    }

    // Normalize features to range [0, 1]
    std::vector<float> features;
    features.push_back(redPieces / 12.0f);
    features.push_back(blackPieces / 12.0f);
    features.push_back(redKings / 12.0f);
    features.push_back(blackKings / 12.0f);
    features.push_back(piecesInKingRowRed / 4.0f);
    features.push_back(piecesInKingRowBlack / 4.0f);
    features.push_back(piecesInCenter / 16.0f);

    return features;
}
