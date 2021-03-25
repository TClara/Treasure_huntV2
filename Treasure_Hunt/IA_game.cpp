#include <iostream>
#include "IA_game.h"
#include "Boat_game.h"
#include <vector>
#include <math.h>

using namespace std;

void IA_player::Add_sonar(MsgSonar New_msg){
    for (int i=0;i<New_msg.obstacle.size();i++){
        if (!Is_In(New_msg.xs[i],New_msg.ys[i],mem_sonar.xs,mem_sonar.ys)){
            mem_sonar.xs.push_back(New_msg.xs[i]);
            mem_sonar.ys.push_back(New_msg.ys[i]);
            mem_sonar.obstacle.push_back(New_msg.obstacle[i]);

        }
    }
};
