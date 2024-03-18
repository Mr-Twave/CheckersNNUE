#include <vector>

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
