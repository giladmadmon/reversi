/**************
* Student name: Gilad Madmon
* Student ID: 305132599
* Exercise name: Exercise 2
**************/

#include "Position.h"
Position::Position(int row, int col) {
  this->row_ = row;
  this->column_ = col;
}
int Position::GetRow() const {
  return this->row_;
}
int Position::GetColumn() const {
  return this->column_;
}
bool Position::operator==(const Position &position) const {
  return this->GetRow() == position.GetRow() && this->GetColumn() == position.GetColumn();
}

