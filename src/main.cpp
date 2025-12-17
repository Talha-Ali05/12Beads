#include <raylib.h>
#include <cmath>
#include <cstring>

// copy .vscode folder from the template to compile the project with C++14 standard

// ================= CONFIG =================
constexpr int TILE_SIZE  = 32;
constexpr int SCALE      = 2;
constexpr int BOARD_SIZE = 10;

// ================= TYPES =================
enum class BeadType {
    None = 0,
    Red,
    Blue
};

Color BeadColor(BeadType type) {
    switch (type) {
        case BeadType::Red:  return RED;
        case BeadType::Blue: return BLUE;
        default:             return BLANK;
    }
}

// ================= BOARD =================
class Board {
public:
    int tiles[BOARD_SIZE][BOARD_SIZE];
    BeadType beads[BOARD_SIZE][BOARD_SIZE];

    Board() {
        int tileInit[BOARD_SIZE][BOARD_SIZE] = {
            {1,0,1,0,1,0,1,0,1,0},
            {0,1,0,1,0,1,0,1,0,1},
            {1,0,1,0,1,0,1,0,1,0},
            {0,1,0,1,0,1,0,1,0,1},
            {1,0,1,0,1,0,1,0,1,0},
            {0,1,0,1,0,1,0,1,0,1},
            {1,0,1,0,1,0,1,0,1,0},
            {0,1,0,1,0,1,0,1,0,1},
            {1,0,1,0,1,0,1,0,1,0},
            {0,1,0,1,0,1,0,1,0,1}
        };

        memcpy(tiles, tileInit, sizeof(tiles));

        for (int y = 0; y < BOARD_SIZE; y++) {
            for (int x = 0; x < BOARD_SIZE; x++) {
                if (y < 3)
                    beads[y][x] = BeadType::Red;
                else if (y > 6)
                    beads[y][x] = BeadType::Blue;
                else
                    beads[y][x] = BeadType::None;
            }
        }
    }

    bool IsInside(int x, int y) const {
        return x >= 0 && x < BOARD_SIZE &&
               y >= 0 && y < BOARD_SIZE;
    }

    bool IsDarkTile(int x, int y) const {
        return tiles[y][x] == 1;
    }
};

// ================= RENDERER =================
class BoardRenderer {
public:
    static void Draw(const Board& board, Vector2 selected) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            for (int x = 0; x < BOARD_SIZE; x++) {

                Color tileColor =
                    board.tiles[y][x] ? DARKGRAY : RAYWHITE;

                DrawRectangle(
                    x * TILE_SIZE * SCALE,
                    y * TILE_SIZE * SCALE,
                    TILE_SIZE * SCALE,
                    TILE_SIZE * SCALE,
                    tileColor
                );

                if ((int)selected.x == x && (int)selected.y == y) {
                    DrawRectangleLinesEx(
                        {
                            (float)x * TILE_SIZE * SCALE,
                            (float)y * TILE_SIZE * SCALE,
                            (float)TILE_SIZE * SCALE,
                            (float)TILE_SIZE * SCALE
                        },
                        3,
                        YELLOW
                    );
                }

                BeadType bead = board.beads[y][x];
                if (bead != BeadType::None) {
                    DrawCircle(
                        x * TILE_SIZE * SCALE + TILE_SIZE * SCALE / 2,
                        y * TILE_SIZE * SCALE + TILE_SIZE * SCALE / 2,
                        10 * SCALE,
                        BeadColor(bead)
                    );
                }
            }
        }
    }
};

// ================= GAME =================
class Game {
public:
    Board board;
    bool redTurn = true;
    Vector2 selected = {-1, -1};

    void HandleClick(Vector2 mouse) {
        int x = mouse.x / (TILE_SIZE * SCALE);
        int y = mouse.y / (TILE_SIZE * SCALE);

        if (!board.IsInside(x, y)) return;

        // No selection yet → try selecting a bead
        if (selected.x < 0) {
            BeadType bead = board.beads[y][x];
            if ((redTurn && bead == BeadType::Red) ||
                (!redTurn && bead == BeadType::Blue)) {
                selected = {(float)x, (float)y};
            }
            return;
        }

        // Attempt move
        TryMove((int)selected.x, (int)selected.y, x, y);
        selected = {-1, -1};
    }

    void TryMove(int sx, int sy, int dx, int dy) {
        // if (!board.IsDarkTile(dx, dy)) return;
        if (board.beads[dy][dx] != BeadType::None) return;

        int dir = redTurn ? 1 : -1;
        if (dy - sy == dir && std::abs(dx - sx) == 1) {
            board.beads[dy][dx] = board.beads[sy][sx];
            board.beads[sy][sx] = BeadType::None;
            redTurn = !redTurn;
        }
    }

    void DrawUI() const {
        DrawText(
            redTurn ? "RED TURN" : "BLUE TURN",
            10,
            BOARD_SIZE * TILE_SIZE * SCALE + 10,
            20,
            redTurn ? RED : BLUE
        );
    }
};

// ================= MAIN =================
int main() {
    const int screenWidth  = BOARD_SIZE * TILE_SIZE * SCALE;
    const int screenHeight = screenWidth + 50;

    InitWindow(screenWidth, screenHeight, "12 Beads - Movement");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            game.HandleClick(GetMousePosition());
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BoardRenderer::Draw(game.board, game.selected);
        game.DrawUI();
        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
