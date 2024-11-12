#include <iostream>
// #include <vector>
#include "city.h"
#include "util.h"

using namespace std;


int main() {
  City city(17);
  city.mapSides();
  city.loadPlaces();
  readIntro();

  int userPos = 0;

  int opt;
  while (true) {
    cout << "A donde quieres ir? Ingresa el numero del lugar, o '0' para salir" << endl;
    city.printCity();
    cin >> opt;
    city.BFSSearch(userPos, opt - 1);
    userPos = opt - 1;
    cout << "Muy bien! puedes checar tu ruta optimizada en el archivo 'ruta.txt'" << endl;
    char seguir;
    cout << "Quieres seguir desde tu nuevo lugar: " << city.getPlaceName(userPos) << "? (y/n)" << endl;
    cin >> seguir;
    if (seguir == 'n') break;
  }




}