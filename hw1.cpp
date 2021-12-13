#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <utility>
using namespace std;

#define PI 3.14159265


int sign(double x)
{if (x >= 0){return 1;}
 else{return -1;}}
 
 double sc_pr(pair<double, double> a, pair<double, double> b){
     return a.first * b.first + a.second * b.second;
 }
 
/*
Считаем косинус угла между двумя векторами
*/
float angle(pair<double, double> a, pair<double, double> b, double theta)
{
    return sign(cos(theta)*b.first - sin(theta)*b.second)*(a.first*b.first + a.second*b.second)/(pow((pow(a.first,2) + pow(a.second,2))*(pow(b.first,2) + pow(b.second,2)),0.5));
}

int main() {
    /*
    В этом блоке читаем данные из файла
    */
    ifstream file ("in.txt");
    double x = 0;
    double y = 0;
    file >> x >> y;
    vector<pair<double, double>> dots;
    double c1 = 0;
    double c2 = 0;
    while (file >> c1){
        file >> c2;
        dots.push_back({c1,c2});
    }
    file.close();
    
    /*
    В этом блоке считаем, на какой угол
    нужно повернуть против часовой стрелки
    вектор, чтобы он стал направлен вертикально вверх
    (удобно для деления точек на левые и правые)
    */
    double a = 0.0;
    if (x == 0){
        if (y >= 0){
            a = 0;
        }
    else{
        a = PI;
    }
    }
    if (y == 0){
        if (x > 0){
            a = PI/2;
        }
    else{
        a = 3*PI/2;
    }
    }
    if ((x>0) and (y>0)){
        a = atan(x/y);
    }
    if ((x>0) and (y<0)){
        a = PI/2 - atan(y/x);
    }
    if ((x<0) and (y<0)){
        a = PI + atan(x/y);
    }
    if ((x<0) and (y>0)){
        a = 3*PI/2 - atan(y/x);
    }
    
    pair<double,double> left={x,y};
    pair<double,double> right={x,y};
    pair<double,double> mid={x,y};
    for (int i=0; i<dots.size(); i++){
        if (abs(pow(sc_pr({x,y},dots[i]),2) - sc_pr(dots[i],dots[i])*sc_pr({x,y},{x,y})) < 0.000000000001){
            if (sc_pr({x,y}, dots[i]) < sc_pr({x,y}, mid)){
                mid = dots[i];
            }
        }else{
        if (angle({x,y},dots[i],a) > angle({x,y},right,a)){
            right = dots[i];
        }
        if (angle({x,y},dots[i],a) < angle({x,y},left,a)){
            left = dots[i];
        }}
    }
    if (mid.first==x and mid.second==y){
        cout << "Leftmost: " << left.first << " " << left.second << endl << "Rightmost: " << right.first << " " << right.second;
    }
    else{
        cout << "Leftmost: " << left.first << " " << left.second << endl << "Rightmost: " << mid.first << " " << mid.second;
    }
}
