struct Move {
    int startX, startY, endX, endY;
    bool isCapture() const {
        return std::abs(startX - endX) == 2;
    }
};

bool GameState::makeMove(const Move& move) {
    Piece& startPiece = board[move.startY][move.startX];
    Piece& endPiece = board[move.endY][move.endX];

    // Basic validation of the move
    if (startPiece == EMPTY || endPiece != EMPTY) return false; // Invalid move

    // Calculate direction of the move
    int dirY = (move.endY - move.startY) > 0 ? 1 : -1;
    int playerDirection = currentPlayer == PLAYER_RED ? 1 : -1; // RED moves down, BLACK moves up

    // Check if move is forward for non-kings
    if (dirY != playerDirection && startPiece != RED_KING && startPiece != BLACK_KING) return false; // Move backward by non-king

    // Perform the move
    std::swap(startPiece, endPiece);

    // Check for captures
    if (move.isCapture()) {
        int midX = (move.startX + move.endX) / 2;
        int midY = (move.startY + move.endY) / 2;
        board[midY][midX] = EMPTY; // Remove the captured piece
    }

    // King conversion
    if (move.endY == 0 && currentPlayer == PLAYER_BLACK) {
        endPiece = BLACK_KING;
    } else if (move.endY == 7 && currentPlayer == PLAYER_RED) {
        endPiece = RED_KING;
    }

    // Change the player
    currentPlayer = (currentPlayer == PLAYER_RED) ? PLAYER_BLACK : PLAYER_RED;

    return true; // Move was successful
}
