#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <sstream>


class graph {
private:
struct edge{
    
    double distance;
    double speed;
    double traffic;
    edge(double distance = 0.0, double speed = 0.0, double traffic = 0.0) : distance(distance), speed(speed), traffic(traffic){
    }; // edge constructor to take distance and speed, and traffic
};

    std::unordered_map<int, std::unordered_map<int, edge>> adjacencyMap;
    double travel(const edge& edge); // travel function to calculate the weight of an edge (d/S*A)

public:
    graph() = default;
    ~graph() = default;
    // act using a as source and b as dest?
    void insert(int a, int b, double d, double s);
    void load(std::string &filename);
    bool traffic(int a, int b, double A);
    void update(std::string &filename);
    void print(int a);
    void remove(int a);     
    void path(int a, int b);
    void lowest(int a, int b);
    int exit();
};
