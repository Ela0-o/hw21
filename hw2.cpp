#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

#define g 9.81

double h0;
double vx;
double vy;

// Функция, описывающая траекторию
double y(double x){
  return (-(g/(2*pow(vx,2)))*pow(x,2) + (vy/vx)*x + h0);}

// Функция, которая сравнивает все зоны с запрещёнными и находит ответ
int ans(int n, set<int> s){
  for (int i = 0; i < n; i++){
    if (s.count(i) == 0){
      return i;
    }
  }
  return 0;}

// Здесь содержится решение
int solve(vector<vector<double>> bars){
  int zones = bars.size()+1;
  set <int> forbid; // множество запрещённых зон: если тело врезалось в стенку, то за ней все зоны запрещены
  int i = 0;
  bool right = true; // индикатор того, куда летит тело (есть небольшая разница)
  while (i < bars.size()){ // перебираем барьеры
      
    if (y(bars[i][0]) <= bars[i][1]){ // условие того, что тело врезалось в стенку
    
      // Добавляем зоны в множество запрещённых
      if (right){
        for (int j=i; j < bars.size(); j++){
          forbid.insert(int(bars[j][2]));}
      }else{
        forbid.insert(0);
        for (int j=i+1; j < bars.size(); j++){
          forbid.insert(int(bars[j][2]));}
      }
      
      right = !right; // Переключили направление полёта
      if (zones - forbid.size() == 1){ // смотрим, когда запрещёнными стали все зоны, кроме одной
        return ans(zones, forbid);} // находим её и даём ответ
        
      // этот блок разворачивает все барьеры (чтобы рассматривать после отскока ту же траекторию, а не отражённую)
      vector<vector<double>> bars1 = bars;
      for (int j=0; j < bars.size(); j++){
        bars1[j][0] = 2*bars[i][0] - bars[j][0];}
      reverse( bars1.begin(), bars1.end() );
      bars = bars1;
      i = bars.size()-i-1;
    }
    i += 1;
  }
  
  //  это случается, если мы прошли барьеры до конца и не врезались
  if (!right){ // движение было вправо
    return int(0); // ответ - самая правая зона
  }else{ // движение было влево
    return bars.size(); // ответ - нулевая зона
  }
  return 0;
}


int main(int argc, char** argv) {
  if(argc == 2){
      // есть один агрумент
      // в argv[1] содержится строка с первым агрументом (имя файла)
    std::cout << "1st argument: "<< argv[1] << std::endl;
  }else{
      // аргументов нет или их больше чем мы ожидаем
  }
  
  // этот блок считывает из файла
  ifstream file (argv[1]);
  file >> h0;
  file >> vx >> vy;
  vector<vector<double>> bars;
  double x = 0;
  double h = 0;
  double n = 1; // будем добавлять к информации о точке её номер, который не будет нигде меняться
                // это нужно, чтобы при всех отражениях мы всё ещё могли знать номера зон
  while (file >> x){
    file >> h;
    bars.push_back({x,h,n});
    n++;
  }
  file.close();

  cout << solve(bars);
  return 0;
}