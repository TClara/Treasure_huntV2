#ifndef BOAT_GAME_H
#define BOAT_GAME_H
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <duels/treasure_hunt/msg.h>
#include <duels/local.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
using duels::Player;
using namespace duels::treasure_hunt;


struct MsgSonar
{
    vector<int> xs;
    vector<int> ys;
    vector<bool> obstacle;
};


class Boat{
public:
    int x;
    int y;
    int t;
    bool treasure_found=false;
    bool hit_obstacle=false;
    MsgSonar Sonar_coordinates;
    Boat(){};
    Boat(int xt, int yt, int d){
        srand (time(NULL));
        t=rand()%4;
        int aleax=rand()%d;
        if (t==0){
            x=xt+aleax;
            y=yt+(d-aleax);}
        if (t==1){
            x=xt-aleax;
            y=yt+(d-aleax);}
        if (t==2){
            x=xt+aleax;
            y=yt-(d-aleax);}
        if (t==3){
            x=xt-aleax;
            y=yt-(d-aleax);}
        Sonar_coordinates.xs.push_back(-5);
        Sonar_coordinates.ys.push_back(-5);
        Sonar_coordinates.obstacle.push_back(false);
    };

    void Update_game(inputMsg input, int Xo[40], int Yo[40], int xt, int yt);
    void Move(int Xo[40], int Yo[40]);
    void Turn_l();
    void Turn_r();
    void Get_Sonar(int Xo[40], int Yo[40]);
    bool On_treasure(int xt, int yt);

};

bool Is_free(int x,int y, int X[40], int Y[40]);
bool Is_In(int x, int y, vector<int> X, vector<int> Y);

class Grid
{
public:
    int height, width;
    int x_treasure, y_treasure;
    int dist_init;
    int Xo[40];
    int Yo[40];
    Boat b1;
    Boat b2;


    Grid(){
        srand (time(NULL));
        height=20;
        width=30;
        x_treasure=rand()%width;
        y_treasure=rand()%height;
        dist_init=((30-x_treasure)+(20-y_treasure))-10;
        Create_Obstacle2();
        b1=Boat(x_treasure,y_treasure,dist_init);
        while (Is_free(b1.x, b1.y, Xo, Yo)==false){
            b1=Boat(x_treasure,y_treasure,dist_init);
        }
        b2=Boat(x_treasure,y_treasure,dist_init);
        while ((!Is_free(b2.x, b2.y, Xo, Yo))||((b1.x==b2.x)&&(b1.y==b2.y))){
            b2=Boat(x_treasure,y_treasure,dist_init);
        }
    };
    void Create_Obstacles();
    void Create_Obstacle2();
    feedbackMsg Create_feedback(Boat b);
};



#endif
