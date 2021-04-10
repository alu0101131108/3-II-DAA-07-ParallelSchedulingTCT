#include "./../include/Table.hpp"
Table::Table()
{
  matrix_ = std::vector<std::vector<int>>(1, std::vector<int>(1, 0));
}

Table::Table(int rows, int cols, int fill_value) : rows_(rows), cols_(cols)
{
  assert(rows > 0 && cols > 0);
  matrix_ = std::vector<std::vector<int>>(rows, std::vector<int>(cols, fill_value));
}

void Table::set(int i, int j, int value)
{
  assert(i >= 0 && j >= 0);
  matrix_[i][j] = value;
}

int Table::get(int i, int j) const
{
  assert(i >= 0 && j >= 0);
  return matrix_[i][j];
}

void Table::reset(int rows, int cols, int fill_value)
{
  assert(rows > 0 && cols > 0);
  matrix_ = std::vector<std::vector<int>>(rows, std::vector<int>(cols, fill_value));
}

void Table::print()
{
  for (int i = 0; i < rows_; i++)
  {
    for (int j = 0; j < cols_; j++)
    {
      std::cout << "[" << matrix_[i][j] << "] ";
    }
    std::cout << std::endl;
  }
}

Table::~Table()
{
}