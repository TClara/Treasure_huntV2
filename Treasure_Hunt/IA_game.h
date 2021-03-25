#ifndef IA_GAME_H
#define IA_GAME_H
#include <iostream>
#include <string>
#include <vector>
#include <duels/treasure_hunt/msg.h>
#include <duels/local.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Boat_game.h"

using namespace std;
using duels::Player;
using namespace duels::treasure_hunt;


class IA_player{
public:
    int level;
    int mem_distance;
    MsgSonar mem_sonar;
    bool on_the_right_way;
    IA_player(){};
    IA_player(int lvl){
        level = lvl;
        mem_distance = 100;
        on_the_right_way = false;
    };
    void Add_sonar(MsgSonar New_msg);
};




#endif
