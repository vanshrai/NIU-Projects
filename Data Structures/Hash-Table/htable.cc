/*********************
Vansh Rai Z1877949
CSCI 340
Assignment 10 
11/16/2020
I certify that this is my own work and where appropriate an extension of the starter code provided for the assignment.
*********************/
#include "htable.h"

#define N1 10  // num of decimal digits
#define N2 26  // num of upper-case letters

void ptsort(vector <Entry*>); 
bool compare(Entry*, Entry*);
// Hash function, you may NOT modify this function
int HT::hash(const string &s) {
  int n = (N2 * N1) * (s[0] - 'A') + N1 * (s[1] - 'A') + (s[2] - '0');

  return n % hsize;
}

// You will complete the code below ...
HT::HT(const unsigned &hs) {
  hTable.resize(hs); //Resizing htable
  pTable.resize(hs); //Resizing htable
  hsize = hs;
}

HT::~HT() {
  for (size_t i = 0; i < hsize ; i++) {
    hTable.at(i).~list(); //Deallocating the list
  }
  hTable.~vector(); //Deallocating the vectors.
  pTable.~vector();
}

void HT::insert(const Entry & e) {
  int i = hash(e.key); //Store hash
  Entry * ptr = new Entry(e.key, e.desc, e.num); //new temp pointer
  list < Entry > & l = hTable[i]; //Assigning the list in a new list
  list < Entry > ::iterator itfind = find_if(l.begin(), l.end(), compare); //Iterator to use find_if
  if (itfind == l.end()) {
    hTable[i].push_back(e); //Adding to the list
    pTable.push_back(ptr); //Adding to the ptrtable
    cout << "inserted!";
  } else {
    cout << "Duplicates!";
  }
}

void HT::search(const string & s) {
  int i = hash(s);
  list < Entry > & a = hTable[i];
  list < Entry > ::iterator it = find_if(a.begin(), a.end(), compare);
  if (it != a.end()) {
    cout << "\n ==> number: " << setw(4);
  } else
    cout << s << "not in table!!";
}

void HT::hTable_print() {
  bool lastEmpty = false;
  for (size_t i = 0; i < hsize; i++) {
    list < Entry > & a = hTable[i];
    for (auto v: a) {
      if (!v.key.empty()) {
        if (lastEmpty)
          cout << endl;
        cout << setw(4) << i << ":  " << v.key << " - " <<
          setw(5) << v.num << "   -  " << v.desc << endl;
        lastEmpty = false;
      } 
      else
        lastEmpty = true;
    }
  }
  cout << endl;
}
void HT::pTable_print() {
  ptsort(pTable);
  for (unsigned int i = 0; i < hsize; i++) {
    Entry * a = pTable[i];
    Entry val = * a; {
      cout << val.key << val.num << val.desc << endl;
    }
  }
}

bool compare(Entry * a, Entry * b) {
  return (a -> key < b -> key) ? true : false; //compare function
}

void ptsort(vector < Entry * > ptrtable) {
  sort(ptrtable.begin(), ptrtable.end(), compare); //Sorting
}