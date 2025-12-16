#include "../include/raylib.h"
#include<iostream>

bool turn = true;
class Beads{
    public:
    Vector2 position;
    float radius = 10;
    int type;
    Beads(Vector2 pos, int t){
        position = pos;
        type = t;
    }
};

const int TILE_W = 10;
const int TILE_H = TILE_W;
const int TILE_SIZE = 32;
const int SCREEN_SIZE = 2;
int tileset[TILE_H][TILE_W] = {
                            {1,0,1,0,1,0,1,0,1,0},
                            {0,1,0,1,0,1,0,1,0,1},
                            {1,0,1,0,1,0,1,0,1,0},
                            {0,1,0,1,0,1,0,1,0,1},
                            {1,0,1,0,1,0,1,0,1,0},
                            {0,1,0,1,0,1,0,1,0,1},
                            {1,0,1,0,1,0,1,0,1,0},
                            {0,1,0,1,0,1,0,1,0,1},
                            {1,0,1,0,1,0,1,0,1,0},
                            {0,1,0,1,0,1,0,1,0,1},
};
int beads [TILE_H][TILE_W]= {{1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {2,2,2,2,2,2,2,2,2,2},
                            {2,2,2,2,2,2,2,2,2,2},
                            {2,2,2,2,2,2,2,2,2,2},

};
void draw_beads(){
    for(int y = 0 ; y<TILE_H; y++){
        for (int x = 0; x<TILE_W; x++){
            if (beads[y][x] != 0){
                Color c;
                switch (beads[y][x]){
                    case 1:
                        c = RED;
                        break;
                    case 2:
                        c = BLUE;
                        break;
                    case 3:
                        c = GREEN;
                        break;
                    default:
                        c = BLACK;
                        break;
                }
                DrawCircle(x*TILE_SIZE*SCREEN_SIZE + TILE_SIZE*SCREEN_SIZE/2, y*TILE_SIZE*SCREEN_SIZE + TILE_SIZE*SCREEN_SIZE/2, 10*SCREEN_SIZE, c);
            }
        }
    }
}
int main(){

    SetTargetFPS(60);

    InitWindow(TILE_W*TILE_SIZE*SCREEN_SIZE,TILE_H*TILE_SIZE*SCREEN_SIZE,"12 Beats");
    while (! WindowShouldClose())
    {
        //Updating
        Vector2 mouse_position = GetMousePosition();
        
        
        //Event Updating
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            int tile_x = mouse_position.x / (TILE_SIZE*SCREEN_SIZE);
            int tile_y = mouse_position.y / (TILE_SIZE*SCREEN_SIZE);
            if (tile_x >=0 && tile_x < TILE_W && tile_y >=0 && tile_y < TILE_H){
                beads[tile_y][tile_x] +=1;
                if (beads[tile_y][tile_x]>3){
                    beads[tile_y][tile_x] =0;
                }
            }
        }
        if (turn){
            //Player 1 turn logic
        } else {
            //Player 2 turn logic
        }
        
        //Drawing
        BeginDrawing();
        for(int y = 0 ; y<TILE_H; y++){
            for (int x = 0; x<TILE_W; x++){
                Color c = tileset[y][x] == 1 ? DARKGRAY:RAYWHITE;
                DrawRectangle(x*TILE_SIZE*SCREEN_SIZE,y*TILE_SIZE*SCREEN_SIZE,TILE_SIZE*SCREEN_SIZE,TILE_SIZE*SCREEN_SIZE,c);
            }
        }
        draw_beads();
        DrawFPS(10,10);
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    
}