#ifndef CITY_H_
#define CITY_H_

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class Place {
private:
    string name;

public:
    Place(string);
    ~Place();
friend class City;
};

Place::Place(string nme) {
    name = nme;
}

Place::~Place() {
    name = "";
}

// vector<string> createCity() {
//     vector<string> places;
//     places.push_back("");
// }

class City {
private:
    int size;
    vector<int> * sides;
    int * matrix;
    vector<Place*> places;
    int getU(string);
    int getV(string);
    int getMin(const vector<int>&);

public:
    City(int);
    void mapSides();
    void loadPlaces();
    // void mapMatrix();
    void BFSSearch(int, int);
    void sortMapSides();
    bool checkFinish(const vector<pair<bool, int>>&, int);
    vector<int> getPath(const vector<pair<bool, int>>&, int, int);
    void printCity();
    string getPlaceName(int);
};

City::City(int sze) { // O(1)
    size = sze;
}

void City::mapSides() { // O(n) n = numero de conexiones/adyencias
    sides = new vector<int>[size];
    ifstream read ("city.txt");
    string line;
    int u, v;
    if (read.is_open()) {
        while (getline(read, line)) {
            u = getU(line);
            v = getV(line);
            sides[u].push_back(v);
            sides[v].push_back(u);
        }
        read.close();
    } else {
        cout << "file not found" << endl;
    }
    sortMapSides();
}

void City::loadPlaces() { // O(n) n = numero de lugares
    ifstream read("places.txt");
    string line;
    int i = 0;
    if (read.is_open()) {
        while (getline(read, line)) {
            Place * new_place = new Place(line);
            places.push_back(new_place);
        }
    }
}

int City::getU(string line) { // O(1)
    int u = 0;
    string num = "";
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ' ') break;
        num += line[i];
    }
    reverse(num.begin(), num.end());
    for (int i = 0; i < num.length(); i++) {
        u += (num[i] - '0') * pow(10, i);
    }

    return u;
}

int City::getV(string line) { // O(1)
    reverse(line.begin(), line.end());
    int v = 0;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ' ') break;
        v += (line[i] - '0') *  pow(10, i);
    }
    
    return v;
}

void City::sortMapSides() { // O(n) n = numero de conexiones
    for (int i = 0; i < size; i++) {
        sort(sides[i].begin(), sides[i].end());
    }
}

void City::BFSSearch(int start, int goal) { // O(n + log(n)) n = size de la ciudad
    queue<int> q;
    vector<pair<bool, int>> visited(size, {false, -1}); // O(n) n = size de la ciudad

    q.push(start);

    while (!q.empty()) { // O(n) n = size de la ciudad
        int node = q.front();
        visited[node].first = true;
        vector<int> currPaths;
        for (int i = 0; i < sides[node].size(); i++) { // O(1) n en teoría no pasará de 10
            int conn = sides[node][i];
            if (visited[conn].first == true) {
                currPaths.push_back(visited[conn].second);
            } else {
                q.push(conn);
            }
        }
        if (currPaths.empty()) visited[node].second = 0;
        else {
            visited[node].second = getMin(currPaths) + 1;
        }
        if (node == goal && checkFinish(visited, goal)) break; // save time if all neighbors of goal have been checked
        q.pop();
    }

    vector<int> shortestPath = getPath(visited, start, goal); // O(log(n))

    ofstream write("ruta.txt");
    if (write.is_open()) {
        write << "Esta es tu ruta optima: \n";
        write << "Empezando en: " << places[start]->name << "\n"; 
        for (int i = 1; i < shortestPath.size(); i++) {
            write << i << ". " << places[shortestPath[i]]->name << "\n";
        }
        write << "y ahi estas, con tan solo " << visited[goal].second << " movimientos!";
        write.close();
    } else {
        cout << "Unable to open file";
    } 
}

bool City::checkFinish(const vector<pair<bool, int>>& visited, int goal) { // O(1) n en teoría no pasa de 10
    for (int i = 0; i < sides[goal].size(); i++) {
        if (visited[sides[goal][i]].second == false) return false;
    }
    return true;
}

vector<int> City::getPath(const vector<pair<bool, int>>& visited, int start, int goal) { // O(log (n)) en promedio, asumiendo la ciudad no es una linea recta
    int lengthPath = visited[goal].second;
    vector<int> path(lengthPath + 1);
    int pathIndex = 0;

    int node = goal;
    while (node != start) { // O(n) n = longitud de la ruta optima (< n) 
        path[pathIndex] = node;
        pathIndex++;
        lengthPath--;
        for (int i = 0; i < sides[node].size(); i++) { // O(1) n < 10
            if (visited[sides[node][i]].second == lengthPath) {
                node = sides[node][i];
            }
        }
    }

    path[pathIndex] = node;

    reverse(path.begin(), path.end()); 
    return path;
}

int City::getMin(const vector<int>& vec) { // O(1) n < 10 en teoria
    int min = vec[0];
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] < min) min = vec[i];
    }
    return min;
}

void City::printCity() { // O(n) n = numero de lugares
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << places[i]->name << endl;
    }
}

string City::getPlaceName(int place) { // O(1)
    return places[place]->name;
}

#endif