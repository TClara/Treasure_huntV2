#include <iostream>
#include "Boat_game.h"
#include <vector>
#include <math.h>

using namespace std;


bool Is_free(int x, int y, int X[40], int Y[40]){
    int i;
    bool res=true;
    if (x>=30||y>=20||x<0||y<0){res=false;}
    else {
        for (i=0;i<40;i++){
            if ((X[i]==x)&&(Y[i]==y)){
                res=false;
            }
        }
    }
    return res;
};


bool Is_In(int x, int y, vector<int> X, vector<int> Y){
    bool res=false;
    for (int i=0; i<X.size(); i++){
        if ((x==X[i])&&(y==Y[i])){
                res=true;
        }
    }
    return res;
}



void Boat::Move(int Xo[40], int Yo[40]){
    int t=Boat::t;

    if ((t==0) /*&& Is_free(Boat::x+1, Boat::y, Xo, Yo)*/){
        Boat::x++;
    }
    if ((t==1) /*&& Is_free(Boat::x, Boat::y+1, Xo, Yo)*/){
        Boat::y--;
    }
    if ((t==2) /*&& Is_free(Boat::x-1, Boat::y, Xo, Yo)*/){
        Boat::x--;
    }
    if ((t==3) /*&& Is_free(Boat::x, Boat::y-1, Xo, Yo)*/){
        Boat::y++;
    }
};


void Boat::Turn_l(){
    if (Boat::t==3){Boat::t=0;}
    else {Boat::t=Boat::t+1;}
};

void Boat::Turn_r(){
    if (Boat::t==0){Boat::t=3;}
    else {Boat::t=Boat::t-1;}
};

void Boat::Get_Sonar(int Xo[40], int Yo[40]){
    Boat::Sonar_coordinates.xs.clear();
    Boat::Sonar_coordinates.ys.clear();
    Boat::Sonar_coordinates.obstacle.clear();
    float lower= -Boat::t*(3.14/2) - (3.14/3);
    float upper= -Boat::t*(3.14/2) + (3.14/3);
    float alpha=lower;
    for (int i = 0; i<100; i++){
        alpha=lower+i*(upper-lower)/100;
        float inc_a=cos(alpha);
        float inc_b=sin(alpha);

        float a = Boat::x + 0.5;
        float b = Boat::y + 0.5;
        while (Is_free(int(floor(a)), int(floor(b)), Xo, Yo)){
            if (!Is_In(int(a), int(b), Boat::Sonar_coordinates.xs, Boat::Sonar_coordinates.ys)){
                Boat::Sonar_coordinates.xs.push_back(int(floor(a)));
                Boat::Sonar_coordinates.ys.push_back(int(floor(b)));
                Boat::Sonar_coordinates.obstacle.push_back(false);

            }
            a = a+inc_a;
            b = b+inc_b;

        }
        if (!Is_In(int(a), int(b), Boat::Sonar_coordinates.xs, Boat::Sonar_coordinates.ys)){
            Boat::Sonar_coordinates.xs.push_back(int(a));
            Boat::Sonar_coordinates.ys.push_back(int(b));
            Boat::Sonar_coordinates.obstacle.push_back(true);
        }
    }
};




void Boat::Update_game(inputMsg input, int Xo[40], int Yo[40], int xt, int yt){
    string A=input.action;
    Sonar_coordinates.xs.clear();
    Sonar_coordinates.ys.clear();
    Sonar_coordinates.obstacle.clear();
    if (A=="move"){
        Boat::Move(Xo, Yo);
        if (Boat::On_treasure(xt, yt)){treasure_found=true;}
        if (!Is_free(x,y,Xo,Yo)){hit_obstacle=true;}
    }
    if (A=="turn_l"){Boat::Turn_l();}
    if (A=="turn_r"){Boat::Turn_r();}
    if (A=="sonar"){Boat::Get_Sonar(Xo, Yo);}
};

bool Boat::On_treasure(int xt, int yt){
    return ((Boat::x==xt)&&(Boat::y==yt));
}

void Grid::Create_Obstacles(){
    srand (time(NULL));
    for (int i=0; i<20; i++){
        Xo[i]=x_treasure;
        Yo[i]=y_treasure;
        while ((Xo[i]==x_treasure)&&(Yo[i]==y_treasure)){
            Xo[i]=rand()%(width-1);
            Yo[i]=rand()%height;
            Xo[39-i]=Xo[i]+1;
            Yo[39-i]=Yo[i];
        }
        if (i>0){
            for (int j=0;j<i;j++){
                while ((Xo[i]==Xo[j])&&(Yo[i]==Yo[j])){
                    Xo[i]=rand()%(width-1);
                    Yo[i]=rand()%height;
                    Xo[39-i]=Xo[i]+1;
                    Yo[39-i]=Yo[i];
                }
            }
        }
    }
    cout<<"obstacles created"<<endl;
};


void Grid::Create_Obstacle2(){
    for (int i=0;i<20;i++){
        Xo[i]=i+3;
        Xo[i+20]=i+4;
        Yo[i]=i;
        Yo[i+20]=i;
    }
    cout<<"obstacles created"<<endl;
};


feedbackMsg Grid::Create_feedback(Boat b){
    feedbackMsg fb;
    fb.x=b.x;
    fb.y=b.y;
    fb.t=b.t;
    fb.Xs=b.Sonar_coordinates.xs;
    fb.Ys=b.Sonar_coordinates.ys;
    fb.Os=b.Sonar_coordinates.obstacle;
    fb.dist=abs(Grid::x_treasure-b.x)+abs(Grid::y_treasure-b.y);
    return fb;
};
