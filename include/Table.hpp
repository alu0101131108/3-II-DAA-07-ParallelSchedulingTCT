#ifndef __TABLE_H__
#define __TABLE_H__
#include <vector>
#include <iostream>
#include <cassert>

class Table
{
private:
  std::vector<std::vector<int>> matrix_;
  int rows_;
  int cols_;

public:
  Table();
  Table(int rows, int cols, int fill_value = 0);
  void set(int i, int j, int value);
  int get(int i, int j) const;
  void reset(int rows, int cols, int fill_value = 0);
  void print();
  ~Table();
};

#endif // __TABLE_H__