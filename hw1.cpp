#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <utility>
using namespace std;

/*
Считаем косинус угла между двумя векторами
*/
float cos_betw(pair<double, double> a, pair<double, double> b)
{
    return round(((a.first*b.first + a.second*b.second)/(pow((pow(a.first,2) + pow(a.second,2))*(pow(b.first,2) + pow(b.second,2)),0.5))) * 100000000000.0) / 100000000000.0;
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
        if (c1 != 0 or c2 !=0){
            dots.push_back({c1,c2});
        }
    }
    file.close();
  
    pair<double, double> left_max = {x, y};
    pair<double, double> right_max = {x, y};
    for (int i=0; i<dots.size(); i++){
        if ((x*dots[i].second > dots[i].first*y) and cos_betw(dots[i], {x, y}) < cos_betw(left_max, {x,y})){
            left_max = dots[i];
        }
        if ((x*dots[i].second <= dots[i].first*y) and cos_betw(dots[i], {x, y}) < cos_betw(right_max, {x,y})){
            right_max = dots[i];
        }
    }

    cout << endl << "Leftmost: " << left_max.first << " " << left_max.second;
    cout << endl << "Rightmost: " << right_max.first << " " << right_max.second;
}
