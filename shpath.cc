#include <string>
#include <iostream>
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include <vector>
#include <set>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::tr1::unordered_map;
using std::tr1::unordered_set;
using std::pair;
using std::vector;
using std::make_pair;
using std::set;

struct less_cost {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
        if (a.second < b.second)
            return true;
        else if (a.second == b.second)
            return a.first < b.first;
        else
            return false;
    }
};

void change_priority(const int key, const int old_value, const int new_value, set<pair<int, int>, less_cost>* unvisited) {
    set<pair<int, int>, less_cost>::iterator elem = unvisited->find(make_pair(key, old_value));
    if (elem != unvisited->end()) {
        unvisited->erase(elem);
        unvisited->insert(make_pair(key, new_value));
    }
}

void create_cost_table(int id, unordered_map<int, vector< pair<int, int> > >& city_graph, set<pair<int, int>, less_cost>* unvisited, unordered_map<int, int>* costs) {
    for (vector< pair<int, int> >::const_iterator it = city_graph[id].begin(); it != city_graph[id].end(); ++it) {
        int nid = it->first;
        int edge_cost = it->second;
        int path_cost = (*costs)[id] + edge_cost;
        unordered_map<int, int>::iterator current_cost = costs->find(nid);
        if (current_cost == costs->end() || path_cost < current_cost->second) {
            if (current_cost != costs->end())
                change_priority(nid, current_cost->second, path_cost, unvisited); 
            (*costs)[nid] = path_cost;
        }
    }
    unvisited->erase(make_pair(id, (*costs)[id]));
    set<pair<int, int>, less_cost>::iterator next = unvisited->begin();
    if (next != unvisited->end()) {
        create_cost_table(next->first, city_graph, unvisited, costs);
    }
}

int minimum_distance(int city_a, int city_b, unordered_map<int, vector< pair<int, int> > >& city_graph) {
    unordered_map<int, int> costs;
    set<pair<int, int>, less_cost> unvisited;
    for (int i = 0; i < city_graph.size(); ++i) {
        unvisited.insert(make_pair(i, 200000));
        costs[i] = 200000;
    }
    change_priority(city_a, 200000, 0, &unvisited);
    costs[city_a] = 0;
    create_cost_table(city_a, city_graph, &unvisited, &costs);
    return costs[city_b];
}

int main(void) {
    int num_tests;
    cin >> num_tests;
    while (num_tests--) {
        unordered_map<int, vector< pair<int, int> > > city_graph;
        unordered_map<string, int> cities;
        int num_cities;
        cin >> num_cities;
        for (int c = 0; c < num_cities; ++c) {
            string name;
            cin >> name;
            cities[name] = c;
            int num_neighbors;
            cin >> num_neighbors;
            while (num_neighbors--) {
                int neighbor_id, cost;
                cin >> neighbor_id;
                cin >> cost;
                city_graph[c].push_back(make_pair(neighbor_id-1, cost));
            }
        }
        int num_paths;
        cin >> num_paths;
        while (num_paths--) {
            string name_a, name_b;
            cin >> name_a;
            cin >> name_b;
            cout << minimum_distance(cities[name_a], cities[name_b], city_graph) << endl;
        }
        cin.get();
    }
    return 0;
}
