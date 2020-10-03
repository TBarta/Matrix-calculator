#include <map>
#include <iostream>
#include "SparseMatrix.h"
#include "Matrix.h"


SparseMatrix::SparseMatrix(unsigned m, unsigned n){
  this->type = "Sparse";
  this->rows = m;
  this->cols = n;
}

SparseMatrix::SparseMatrix(const SparseMatrix & rhs){
  s_matrix = rhs.s_matrix;
  cols = rhs.cols;
  rows = rhs.rows;
  type = rhs.type;
}

std::shared_ptr <Matrix> SparseMatrix::clone()const{
  return std::make_shared < SparseMatrix > ( *this );
}
void SparseMatrix::print(std::ostream & os)const{
  for (unsigned i=0; i < rows; i++) {
    for (unsigned j=0; j < cols; j++) {
      if((s_matrix.find(std::make_pair(i,j)) != s_matrix.end()))
        os << s_matrix.find(std::make_pair(i,j))->second << " ";
      else
        os << 0 << " ";
    }
    os << std::endl;
  }
}
void SparseMatrix::setValue(unsigned i, unsigned j, double v){
  s_matrix.insert(std::make_pair(std::make_pair(i,j),v));
}

// Access the individual elements

double SparseMatrix::operator()(const unsigned & row, const unsigned & col) const {
  if(s_matrix.find(std::make_pair(row,col)) != s_matrix.end()){
    return this->s_matrix.find(std::make_pair(row,col))->second;
  }else{
    return 0;
  }
}

SparseMatrix SparseMatrix::operator=(const SparseMatrix & rhs){

  unsigned rows = rhs.getRows();
  unsigned cols = rhs.getCols();

  SparseMatrix res(rows,cols);

  for(unsigned i = 0; i < rows; i++){
    for(unsigned j = 0; j < cols; j++)
    {
      res.setValue(i,j,rhs(i,j));
    }
  }
  return res;
}
