#ifndef SIMPLEGRAPH_H
#define SIMPLEGRAPH_H
#include <list>
#include <vector>

class Graph {
 private:
  int                          size;
  std::vector<std::list<int> > adj_list;
  std::vector<char>            labels;
  void                         Depthfirst(int);

 public:
  Graph(const char* filename);
  ~Graph(){ 
    adj_list = std::vector<std::list<int>>(); 
    labels = std::vector<char>();
  };
  int  Getsize() const {return size;};
  void Traverse();
  void Print() const;
};

#endif // SIMPLEGRAPH_H
