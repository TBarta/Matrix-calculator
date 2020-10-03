#include "DenseMatrix.h"
#include "SparseMatrix.h"


DenseMatrix::DenseMatrix(unsigned m, unsigned n){
  this->type = "Dense";
  this->rows = m;
  this->cols = n;
  // resizing matrix according to rows and columns
  d_matrix.resize(m);
  for (unsigned i=0; i<d_matrix.size(); i++) {
    d_matrix[i].resize(n);
  }
}

DenseMatrix::DenseMatrix(const DenseMatrix & rhs){
  d_matrix = rhs.d_matrix;
  cols = rhs.cols;
  rows = rhs.rows;
  type = rhs.type;
}
std::shared_ptr <Matrix> DenseMatrix::clone()const{
  unsigned zeros = 0;
  double size,sparsity;

  size = rows * cols;

  for (unsigned i=0; i < rows; i++) {
    for (unsigned j=0; j < cols; j++) {
      if(d_matrix[i][j] == 0)
        zeros++;
    }
  }
  sparsity = (zeros / size);

  if(sparsity > 0.5)
    return std::make_shared < DenseMatrix > ( *this );
  else{
    SparseMatrix res(rows,cols);
    for(unsigned i = 0; i < rows;i++){
      for(unsigned j = 0; j < cols;j++){
        if(d_matrix[i][j] != 0)
          res.setValue(i,j,d_matrix[i][j]);
      }
    }
    return res.clone();
  }
}
void DenseMatrix::print(std::ostream & os)const{
  for (unsigned i=0; i < rows; i++) {
    for (unsigned j=0; j < cols; j++) {
      os << d_matrix[i][j] << " ";
    }
    os << std::endl;
  }
}
void DenseMatrix::setValue(unsigned i, unsigned j, double v){
  d_matrix[i][j] = v;
}

// Access the individual elements

double DenseMatrix::operator()(const unsigned & row, const unsigned & col) const {
  return this->d_matrix[row][col];
}
DenseMatrix DenseMatrix::operator=(const SparseMatrix& rhs){

  this->rows = rhs.getRows();
  this->cols = rhs.getCols();

  d_matrix.resize(rows);
  for (unsigned i=0; i<d_matrix.size(); i++) {
    d_matrix[i].resize(cols);
  }

  for (unsigned i=0; i<rows; i++) {
    for (unsigned j=0; j<cols; j++) {
      d_matrix[i][j] = rhs(i, j);
    }
  }

  return *this;
}

DenseMatrix DenseMatrix::operator=(const DenseMatrix & rhs){

    this->rows = rhs.getRows();
    this->cols = rhs.getCols();

    d_matrix.resize(rows);
    for (unsigned i=0; i<d_matrix.size(); i++) {
      d_matrix[i].resize(cols);
    }

    for (unsigned i=0; i<rows; i++) {
      for (unsigned j=0; j<cols; j++) {
        d_matrix[i][j] = rhs(i, j);
      }
    }

    return *this;
}

// + operator
DenseMatrix DenseMatrix::operator+(const DenseMatrix & rhs){
  DenseMatrix res(this->rows, this->cols);
  for (unsigned i=0; i < rows; i++) {
    for (unsigned j=0; j < cols; j++) {
    res.setValue(i,j,d_matrix[i][j] + rhs(i,j));
    }
  }
  return res;
}



DenseMatrix DenseMatrix::operator-(const DenseMatrix & rhs){
  DenseMatrix res(this->rows, this->cols);
  for (unsigned i=0; i < rows; i++) {
    for (unsigned j=0; j < cols; j++) {
    res.setValue(i,j,d_matrix[i][j] - rhs(i,j));
    }
  }
  return res;
}

DenseMatrix DenseMatrix::operator*(const DenseMatrix& rhs) {
  unsigned r_rows = rhs.getRows();
  unsigned r_cols = rhs.getCols();
  DenseMatrix res(this->rows, r_cols);
  double d;

  for (unsigned i=0; i<this->rows; i++) {
    for (unsigned j=0; j<r_cols; j++) {
      d = 0;
      for (unsigned k=0; k<r_rows; k++) {
        d += d_matrix[i][k] * rhs(k,j);
      }
      res.setValue(i,j, d);
    }
  }
  return res;
}

DenseMatrix DenseMatrix::operator+(const double& rhs) {
  DenseMatrix res(this->rows, this->cols);

  for (unsigned i=0; i<rows; i++) {
    for (unsigned j=0; j<cols; j++) {
      res.setValue(i,j, d_matrix[i][j] + rhs);
    }
  }
  return res;
}
DenseMatrix DenseMatrix::operator-(const double& rhs) {
  DenseMatrix res(this->rows, this->cols);

  for (unsigned i=0; i<rows; i++) {
    for (unsigned j=0; j<cols; j++) {
      res.setValue(i,j, d_matrix[i][j] - rhs);
    }
  }
  return res;
}
DenseMatrix DenseMatrix::operator*(const double& rhs) {
  DenseMatrix res(this->rows, this->cols);

  for (unsigned i=0; i<rows; i++) {
    for (unsigned j=0; j<cols; j++) {
      res.setValue(i,j, d_matrix[i][j] * rhs);
    }
  }
  return res;
}
