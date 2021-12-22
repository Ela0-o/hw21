#include <iostream>
#include <cmath>
#include <fstream>


// Считаем косинус угла между двумя векторами
// Косинус равен склярному произведению, делённому на произведение длин

float cos_betw(std::pair<double, double> a, std::pair<double, double> b)
{
    if (a.first==0 and a.second==0){
        return 1;
    }else{
        return round(((a.first*b.first + a.second*b.second)/(sqrt((a.first*a.first + a.second*a.second)*(b.first*b.first + b.second*b.second))))*100000.0)/100000.0;
    }
}

int main(){
    std::ifstream file ("in.txt");
    double x = 0; \\ x и y -- координаты заданного вектора
    double y = 0;
    file >> x >> y;
    double xn = 0; \\ xn и yn -- координаты для считывания точек
    double yn = 0;
    std::pair<double,double> left_max = {0, 0}; \\ эти векторы -- точки, которые мы в данный момент считаем самыми левыми и самыми правыми
    std::pair<double,double> right_max = {0, 0};
    double c = 0;
    while (file >> xn){ \\ считываем точки, пока входной поток не кончится
        file >> yn;
        c = cos_betw({xn, yn}, {x, y}); \\ сосчитали косинус угла между точкой и заданным вектором
        if ((x*yn > xn*y) and c <= cos_betw(left_max, {x,y})){ \\ если точка слева, и косинус меньше предыдущего минимального, то записываем новую точку
            left_max = {xn, yn};
        }
        if ((x*yn <= xn*y) and c <= cos_betw(right_max, {x,y})){ \\ аналогично, но справа
            right_max = {xn, yn};
        }
    }
    file.close();
    
    std::cout << std::endl << "Leftmost: " << left_max.first << " " << left_max.second; \\ выводим самую левую и самую правую
    std::cout << std::endl << "Rightmost: " << right_max.first << " " << right_max.second;
}
