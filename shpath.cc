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

const int kMaxCost = 200000;

void ChangePriority(const int key, const int old_value, const int new_value, set<pair<int, int> >* unvisited) {
  set<pair<int, int> >::iterator elem = unvisited->find(make_pair(old_value, key));
  if (elem != unvisited->end()) {
    unvisited->erase(elem);
    unvisited->insert(make_pair(new_value, key));
  }
}

void CreateCostTable(int id, const unordered_map<int, vector<pair<int, int> > >& city_graph, set<pair<int, int> >* unvisited, unordered_map<int, int>* costs) {
  unordered_map<int, vector<pair<int, int> > >::const_iterator city_node = city_graph.find(id);
  if (city_node == city_graph.end())
    return;
  for (vector<pair<int, int> >::const_iterator it = city_node->second.begin(); it != city_node->second.end(); ++it) {
    int nid = it->first;
    int edge_cost = it->second;
    int path_cost = (*costs)[id] + edge_cost;
    unordered_map<int, int>::iterator current_cost = costs->find(nid);
    if (current_cost == costs->end() || path_cost < current_cost->second) {
      if (current_cost != costs->end())
        ChangePriority(nid, current_cost->second, path_cost, unvisited);
      (*costs)[nid] = path_cost;
    }
  }
  unvisited->erase(make_pair((*costs)[id], id));
  set<pair<int, int> >::iterator next = unvisited->begin();
  if (next != unvisited->end()) {
    CreateCostTable(next->second, city_graph, unvisited, costs);
  }
}

int MinimumDistance(int city_a, int city_b, const unordered_map<int, vector< pair<int, int> > >& city_graph) {
  unordered_map<int, int> costs;
  set<pair<int, int> > unvisited;
  for (int i = 0; i < city_graph.size(); ++i) {
    unvisited.insert(make_pair(kMaxCost, i));
    costs[i] = kMaxCost;
  }
  ChangePriority(city_a, kMaxCost, 0, &unvisited);
  costs[city_a] = 0;
  CreateCostTable(city_a, city_graph, &unvisited, &costs);
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
      cout << MinimumDistance(cities[name_a], cities[name_b], city_graph) << endl;
    }
    cin.get();
  }
  return 0;
}
