#include <array>

enum Piece { EMPTY = 0, RED, RED_KING, BLACK, BLACK_KING };

class GameState {
public:
    std::array<std::array<Piece, 8>, 8> board;

    GameState() {
        // Initialize the board with pieces in starting positions
        // Assuming RED is at the top and BLACK is at the bottom
        for(int y = 0; y < 8; ++y) {
            for(int x = (y + 1) % 2; x < 8; x += 2) {
                if(y < 3) board[y][x] = RED;
                else if(y > 4) board[y][x] = BLACK;
                else board[y][x] = EMPTY;
            }
        }
    }
};
