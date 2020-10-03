#include "Matrix.h"


Matrix::~Matrix() {}

std::string Matrix::getType()const{
  return this->type;
}
unsigned Matrix::getRows()const{
  return this->rows;
}
unsigned Matrix::getCols()const{
  return this->cols;
}

std::ostream& operator<<(std::ostream& os, const Matrix & x) {
	x.print ( os );
	return os;
}
