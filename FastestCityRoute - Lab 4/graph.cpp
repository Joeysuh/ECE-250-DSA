#include "graph.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <sstream>
#include <algorithm>

double graph::travel(const edge& edge){ // helper to find the weight of an edge
    return edge.distance / (edge.speed * edge.traffic);
}

void graph::insert(int a, int b, double d, double s){ // fine

   // check if a is not in the graph, if it isn't we add the vertex
    if (adjacencyMap.find(a) == adjacencyMap.end()){
        adjacencyMap[a] = std::unordered_map<int, edge>();
    }
    // check if b is not in the graph, if it isn't we add the vertex
    if (adjacencyMap.find(b) == adjacencyMap.end()){
        adjacencyMap[b] = std::unordered_map<int, edge>();
    }

    // check if the edge already exists, if it does we update the edge
    if (adjacencyMap[a].find(b) != adjacencyMap[a].end()){
        adjacencyMap[a][b].distance = d;
        adjacencyMap[a][b].speed = s;
        adjacencyMap[b][a].distance = d;
        adjacencyMap[b][a].speed = s;
        return;
    }

    // insert the new edge
    adjacencyMap[a][b] = edge(d, s, 1.0);
    adjacencyMap[b][a] = edge(d, s, 1.0);
    std::cout << "success" << std::endl;
    return;
}

auto original_cout = std::cout.rdbuf();

// redirect cout to a null stream
void redirect(){
    std::cout.rdbuf(nullptr);
}
// restore cout to the original destination
void restore(){
    std::cout.rdbuf(original_cout);
}

void graph::load(std::string &filename){ // fine
    redirect();
    std::ifstream file(filename); // get filename
    std::string input; // inputs into graph
    
    while(std::getline(file, input)){ // while we get file and words
        std::vector<std::string> inputs; // vector of strings
        std::stringstream parser(input); // stringstream 
        std::string words; // input string

        while (parser >> words){ // while we parse the words of the file
            inputs.push_back(words);
        }
        insert(std::stoi(inputs[0]), std::stoi(inputs[1]), std::stod(inputs[2]), std::stod(inputs[3]));
    }


    file.close();
    restore(); // restore cout for a single print statment
    std::cout << "success" << std::endl;
}


bool graph::traffic(int a, int b, double A){ // fine
    bool updated = false;
    
    // if we find a and b in the adjacency map, we update the traffic and return the bool
    if (adjacencyMap.find(a) != adjacencyMap.end() && adjacencyMap[a].find(b) != adjacencyMap[a].end()){
        adjacencyMap[a][b].traffic = A;
        adjacencyMap[b][a].traffic = A;
        updated = true;
    }
    // if we update, we already printed so return true, else, we print failure
    if (updated){
        std::cout << "success" << std::endl;
    } else {
        std::cout << "failure" << std::endl;
    }

    return updated;
}

void graph::update(std::string &filename){ // fine
    // similair to load
    std::ifstream file(filename);
    std::string words;
    
    while (std::getline(file, words)){
        std::vector<std::string> inputs; // vector of strings to store the words 
        std::stringstream parser(words); // stringstream to parse the words 
        std::string word; // word string

        // parse the file and store them in the inputs vector
        while (parser >> word){
            inputs.push_back(word);
        }
        if (traffic(std::stoi(inputs[0]), std::stoi(inputs[1]), std::stod(inputs[2])) == true){ // if traffic has updated the bools
            continue; // since traffic has updated booleans, we don't have to do anything, just noting that traffic is uppdated
        }   
    file.close();
    return;
}
}

void graph::print(int a){  // fine
    // if we are unable to find vertex, FAIL
    if (!adjacencyMap.count(a)){
        std::cout << "failure" << std::endl;
        return;
    }
    // logic: use boolean to check if we are at the first element, if no then print a space for seperation in case more words as per lab manual
    bool first = true;
    // if not first vertex print a space and then print the word
    for (const auto& current : adjacencyMap[a]){
        if (!first) {
            std::cout << " ";
        }
        std::cout << current.first;
        first = false;
    }
// new line after all prints are done
    std::cout << std::endl;
}

void graph::remove(int a){ // fine
    // check if vertex a exists in the graph
    if (adjacencyMap.find(a) != adjacencyMap.end()){
        // remove vertex a from the edge set of all vertices adjacent to a
        for (auto it = adjacencyMap.begin(); it != adjacencyMap.end(); ++it){
            it->second.erase(a);
        }
        // remove vertex a from the graph
        adjacencyMap.erase(a);
        std::cout << "success" << std::endl;
    } else {
        std::cout << "failure" << std::endl;
    }
}

void graph::path(int a, int b){
    // set the precision for output to 3 decimal places
    std::cout << std::fixed << std::showpoint;
    std::cout << std::setprecision(3);

    // check if start and end vertices exist in the graph
    if (!adjacencyMap.count(a) || !adjacencyMap.count(b)){
        std::cout << "failure" << std::endl;
        return;
    }

    // initialize distance and visited maps
    std::unordered_map<int, double> dist;
    std::unordered_map<int, bool> visited;
    std::unordered_map<int, int> previous;

    // setup from lectures, initialize all distances to infinity and visited to false
    for (const auto& vert : adjacencyMap){
        dist[vert.first] = std::numeric_limits<double>::max();
        visited[vert.first] = false;
    }


    // create a priority queue to store vertices and their distances
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;

    // set the distance of the start vertex to 0 and add it to the priority queue
    dist[a] = 0;
    pq.push({0, a});

    while (!pq.empty()){
        // get the vertex with the minimum distance from the priority queue
        int current = pq.top().second;
        pq.pop();
        // if the current vertex is the end vertex do logic specified below
        if (current == b){ // if we are at the end vertex we print the path and return
            std::vector<int> path; 
            int vertex = current;
            while (vertex != a){ // traverse backwards b/c thru prev until we reach start and add vertex to path
                path.push_back(vertex);
                vertex = previous[vertex];
            }
            path.push_back(a);
            std::reverse(path.begin(), path.end()); // we reverse b/c it's backwards on iterations
            for (int v : path){ // print all the vertex that leads us to destination
                std::cout << v << " ";
            }
            std::cout << std::endl;
            return;
        }

        // if the current vertex has already been visited, skip it
        if (visited[current]) {
            continue;
        }
        visited[current] = true;

        // update the distances of the neighboring vertices
        for (auto& adj : adjacencyMap[current]){
            int neighbor = adj.first;
            double weight = travel(adj.second);
            double totaldist = dist[current] + weight;

            if (totaldist < dist[neighbor]){ // if total distance is less than the distance of the neighbor update the distance and add to the priority queue since we have a shorter path
                dist[neighbor] = totaldist;
                previous[neighbor] = current;
                pq.push({totaldist, neighbor});
            }
        }
    }

    std::cout << "failure" << std::endl;
    return;
}

void graph::lowest(int a, int b) {
    // set the precision for output to 3 decimal places
    std::cout << std::fixed << std::showpoint; 
    std::cout << std::setprecision(3);

    // check if start and end vertices exist in the graph
    if (!adjacencyMap.count(a) || !adjacencyMap.count(b)){
        std::cout << "failure" << std::endl;
        return;
    }

    // initialize distance and visited maps
    std::unordered_map<int, double> dist;
    std::unordered_map<int, bool> visited;
    std::unordered_map<int, int> previous;
    for (const auto& vert : adjacencyMap){
        dist[vert.first] = std::numeric_limits<double>::max(); 
        visited[vert.first] = false;
        previous[vert.first] = -1;
    }

    // create a priority queue to store vertices and their distances
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;
        
    // set the distance of the start vertex to 0 and add it to the priority queue
    dist[a] = 0;
    pq.push({0, a}); //push start
    // while pq not empty
    while (!pq.empty()){
        // get the vertex with the minimum distance from the priority queue
        int current = pq.top().second;
        pq.pop();
          
        // if the current vertex is the end vertex, print the distance and return
        if (current == b){
            std::cout << dist[current] << std::endl;
            return;
        }
        // if the current vertex has already been visited, skip it
        if (visited[current]){
            continue;
        }

        // mark the current vertex as visited
        visited[current] = true;

        // update the distances of the neighboring vertices
        for (auto& adj : adjacencyMap[current]) {
            int neighbor = adj.first;
            double weight = travel(adj.second); // edge weight calculation
            double totaldist = dist[current] + weight; // total weight + dist calculation
            // if total distance is less than the distance of the neighbor update the distance and add to the priority queue
            if (totaldist < dist[neighbor]){
                dist[neighbor] = totaldist;
                previous[neighbor] = current;
                pq.push({dist[neighbor], neighbor});
            }
        }
    }
    
    std::cout << "failure" << std::endl; // if all else fails, print failure
    return;
}

int graph::exit(){
    return 0;
}
