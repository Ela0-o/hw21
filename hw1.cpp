#include <iostream>
#include <cmath>
#include <fstream>

/*
Считаем косинус угла между двумя векторами
*/
float cos_betw(std::pair<double, double> a, std::pair<double, double> b)
{
    if (a.first==0 and a.second==0){
        return 1;
    }else{
    return round(((a.first*b.first + a.second*b.second)/(sqrt((a.first*a.first + a.second*a.second)*(b.first*b.first + b.second*b.second)) * 100000.0) / 100000.0;
    }
}

int main(){
    std::ifstream file ("in.txt");
    double x = 0;
    double y = 0;
    file >> x >> y;
    double xn = 0;
    double yn = 0;
    double left_max_x = 0;
    double left_max_y = 0;
    double right_max_x = 0;
    double right_max_y = 0;
    double c = 0;
    while (file >> xn){
        file >> yn;
        c = cos_betw({xn, yn}, {x, y});
        if ((x*yn > xn*y) and c <= cos_betw({left_max_x, left_max_y}, {x,y})){
            left_max_x = xn;
            left_max_y = yn;
        }
        if ((x*yn <= xn*y) and c <= cos_betw({right_max_x, right_max_y}, {x,y})){
            right_max_x = xn;
            right_max_y = yn;
        }
    }
    file.close();
    
    std::cout << std::endl << "Leftmost: " << left_max_x << " " << left_max_y;
    std::cout << std::endl << "Rightmost: " << right_max_x << " " << right_max_y;
}
