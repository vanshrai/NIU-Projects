/*********************
Vansh Rai Z1877949
CSCI 330
Assignment 11
11/25/2020
I certify that this is my own work and where appropriate an extension of the starter code provided for the assignment.
*********************/
#include "simplegraph.h"
#include <iterator> 
#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

int n; //Vertices
vector<int> traversed_nums;
vector<pair<int, int> > visit_order; //Vector pair to hold the visited vertices.
int inc_order = 0;
vector<int>::iterator graph_it;
list<int>::iterator adj_it;
list<int> temp_list;

Graph::Graph(const char * filename) {
  ifstream file(filename); //Using ifstream to read the file data.
  if (!file) {
    cout << "Failed to open file!\n";
    exit(EXIT_FAILURE);
  }
  string temp;
  getline(file, temp); //Getting the vertices
  size = stoi(temp); //Assiging the vertices

  for (size_t i = 0; i < size; i++) {
    char label;
    file >> label;
    labels.push_back(label); //Input the labels in the arr.
  }
  char line;
  int temp_int;
  for (int k = 0; k < size; k++) {
    file >> line; //Dumy read the first char
    for (int j = 0; j < size; j++) {
      file >> temp_int; //Reading numbers
      temp_list.push_back(temp_int);
    }
    adj_list.push_back(temp_list); //Pushing the temp list into the actual list
    temp_list.erase(temp_list.begin(), temp_list.end()); //Erasing the 
  }
  file.close();
}

void Graph::Depthfirst(int v) {
  int dist = 0;
  inc_order++; //Add order by 1
  traversed_nums[v] = inc_order;
  temp_list = adj_list[v]; //Assign actual list to a temp.
  for (adj_it = temp_list.begin(); adj_it != temp_list.end(); adj_it++) { //Go through the list.
    temp_list = adj_list[v];
    dist = distance(temp_list.begin(), adj_it);
    if ( * adj_it == 1 && traversed_nums[dist] == 0) { //If entry equals to 1
      visit_order.push_back(make_pair(v, dist)); //Make a pair 
      Depthfirst(dist);
    }
  }
}
void Graph::Traverse() {
  traversed_nums.resize(size);
  graph_it = find(traversed_nums.begin(), traversed_nums.end(), 0); //Find the index and put into the it.
  while (graph_it != traversed_nums.end()) { //Do while reach till the end
    Depthfirst(graph_it - traversed_nums.begin()); //Calling depth first.
    graph_it = find(traversed_nums.begin(), traversed_nums.end(), 0);
  }
  cout << "------- traverse of graph ------" << endl;
  for (int i = 0; i <= size; i++) {
    graph_it = find(traversed_nums.begin(), traversed_nums.end(), i); //Find i and put it in the it
    cout << labels[graph_it - traversed_nums.begin()] << " ";
  }
  cout << endl;
  for (unsigned int j = 0; j < visit_order.size(); j++) {
    cout << "(" << labels[visit_order[j].first] << ", " << labels[visit_order[j].second] << ") ";
  }
  cout << "\n--------- end of traverse -------\n\n";
}

void Graph::Print() const {
  cout << "\nNumber of vertices in the graph: " << size << endl;
  cout << "\n-------- graph -------";
  for (size_t i = 0; i < adj_list.size(); i++) {
    cout << "\n" << labels[i] << ":";
    for (size_t j = 0; j < adj_list[i].size(); j++) {
      auto p = adj_list[i].begin();
      advance(p, j);
      if ( * p == 1) {
        cout << " " << labels[j] << ",";
      }
    }
  }
  cout << "\n------- end of graph ------\n\n";
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    cerr << "args: input-file-name\n";
    return 1;
  }

  Graph g(argv[1]);

  g.Print();

  g.Traverse();

  return 0;
}