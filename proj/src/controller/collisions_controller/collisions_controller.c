#include <lcom/lcf.h>

#include "collisions-controller.h"
#include "../../model/pacman_model/pacman.h"
#include "../../view/initialize_pixmaps.h"

extern Ghost ghosts[4];
extern BigCoin big_coins[5];
extern SmallCoin small_coins[329];
extern uint8_t* maze_pixmap;
extern Pacman pacman;

bool (pacman_ghost_collision)(Position ghost_pos) {
    if((ghost_pos.top_y >= pacman.pos.top_y && ghost_pos.top_y <= pacman.pos.bottom_y) 
        || (ghost_pos.bottom_y <= pacman.pos.bottom_y && ghost_pos.bottom_y >= pacman.pos.top_y)){

            if((ghost_pos.left_x <= pacman.pos.left_x && ghost_pos.right_x >= pacman.pos.left_x)
            || (ghost_pos.right_x >= pacman.pos.right_x && ghost_pos.left_x <= pacman.pos.right_x)){
                return true;
            }
        }  
    return false;
}

bool (maze_collision)(Position position) {
    position.left_x -= 148;
    position.right_x -= 148;
    position.top_y -= 20;
    position.bottom_y -= 20;

    int index=0;
    for(int y = 0; y < 728; y++) {
        for(int x = 0; x < 728; x++) {
            if(y >= position.top_y && y <= position.bottom_y 
                && x >= position.left_x && x <= position.right_x 
                && *(maze_pixmap + index) == 1) {
                return true;
            }
            index++;
        }
    }
    return false;
}

bool (pacman_small_coin_collision)() {
    for(int i = 0; i < 323; i++) {
        if ( (small_coins[i].pos.top_y >= pacman.pos.top_y && small_coins[i].pos.top_y <= pacman.pos.bottom_y) 
            || (small_coins[i].pos.bottom_y <= pacman.pos.right_x && small_coins[i].pos.left_x <= small_coins[i].pos.right_x) ) {

            if((small_coins[i].pos.left_x <= pacman.pos.left_x && small_coins[i].pos.right_x >= pacman.pos.left_x)
            || (small_coins[i].pos.right_x >= pacman.pos.right_x && small_coins[i].pos.left_x <= pacman.pos.right_x)){
                return true;
            }
        }
    }
    return false;
}

bool (pacman_big_coin_collision)(Position pacman_pos) {
    for(int i = 0; i < 5; i++) {
        if ( (big_coins[i].pos.top_y >= pacman.pos.top_y && big_coins[i].pos.top_y <= pacman.pos.bottom_y) 
            || (big_coins[i].pos.bottom_y <= pacman.pos.right_x && big_coins[i].pos.left_x <= big_coins[i].pos.right_x) ) {

                if((big_coins[i].pos.left_x <= pacman.pos.left_x && big_coins[i].pos.right_x >= pacman.pos.left_x)
                    || (big_coins[i].pos.right_x >= pacman.pos.right_x && big_coins[i].pos.left_x <= pacman.pos.right_x)){
                return true;
            }
        }
    }
    return false;
}

bool (ghosts_collision)() {
    for (int i=0; i < 4; i++) {
        for (int j=0; j < 4; j++) {
            if (j == i)
                continue;
            
            if ( (ghosts[i].pos.top_y >= ghosts[j].pos.top_y && ghosts[i].pos.top_y <= ghosts[j].pos.bottom_y) 
            || (ghosts[i].pos.bottom_y <= ghosts[j].pos.right_x && ghosts[i].pos.left_x <= ghosts[j].pos.right_x) ) {

                if((ghosts[i].pos.left_x <= ghosts[j].pos.left_x && ghosts[i].pos.right_x >= ghosts[j].pos.left_x)
                    || (ghosts[i].pos.right_x >= ghosts[j].pos.right_x && ghosts[i].pos.left_x <= ghosts[j].pos.right_x)){
                    return true;
                }
            }
        }
    }
    return false;
}
