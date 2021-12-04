#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <utility>
using namespace std;

#define PI 3.14159265

/*
Считаем косинус угла между двумя векторами
*/
float cos_betw(pair<double, double> a, pair<double, double> b)
{
  return (a.first*b.first + a.second*b.second)/(pow((pow(a.first,2) + pow(a.second,2))*(pow(b.first,2) + pow(b.second,2)),0.5));
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
  вектор-точку, чтобы он стал направлен вертикально вверх
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
    a = 3*PI/2 - atan(x/y);
  }

  /*
  В этом блоке точки делятся на левые и правые
  Величина, которую сравниваем с нулём - это
  x-координата вектора-точки после умножения
  на матрицу поворота
  */
  vector<pair<double, double>> left, right;
  for (int i = 0; i < dots().size; ++i){
    if ((cos(a)*dots[i].first - sin(a)*dots[i].second) < 0){
      left.push_back(dots[i]);
    }
    else{
      right.push_back(dots[i]);
    }
  }

  
  /*
  Отдельно для левых и отдельно для правых точек выясняем,
  какая из точек соответствует наибольшему углу
  (или наименьшему косинусу этого угла)
  */
  pair<double, double> l_max = left[0];
  pair<double, double> r_max = left[0];
  double c = 0;
  for (int i = 0; i < left().size; ++i){
    c = cos_betw(left[i],{x,y});
    if (cos_betw(l_max,{x,y}) > c){
      l_max = left[i];
    }
  }
  for (int i = 0; i < right().size; ++i){
    c = cos_betw(right[i],{x,y});
    if (cos_betw(r_max,{x,y}) > c){
      r_max = right[i];
    }
  }


  cout << endl << "Leftmost: " << l_max.first << " " << l_max.second;
  cout << endl << "Rightmost: " << r_max.first << " " << r_max.second;
}
