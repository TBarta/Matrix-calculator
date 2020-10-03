#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include "Matrix.h"
#include <map>
#include <iostream>

/**
 * Child class of matrix.
 * It's used for sparse matrices and its numbers are stored in map of value and coordinates of the value.
 * Also has some overloaded operators.
 */
class SparseMatrix : public Matrix {
	/**Map for storing numbers and coordinates of values in matrix */
std::map <std::pair<unsigned,unsigned>, double> s_matrix;

public:
  /**
 * Constructor takes 2 arguments and those are rows and columns of the matrix
 *
 * @param[in] m rows of the matrix
 * @param[in] n columns of the matrix
 */
  SparseMatrix(unsigned m, unsigned n);
  /**
 * Copy constructor
 * @param[in] rhs SparseMatrix
 */
  SparseMatrix(const SparseMatrix & rhs);
  /**
 * Virtual function for cloning shared pointers on parent class
 * Used later for storing matrices in vector of shared pointers
 */
  virtual std::shared_ptr <Matrix> clone()const;
  /**
 * Print function for printing matrix
 * @param[in] os ostream
 */
  virtual void print(std::ostream & os)const;
  /**
 * Function for setting value of element in matrix on passed certain row and column
 * @param[in] i row coordinate
 * @param[in] j column coordinate
 * @param[in] v value to be set
 */
  virtual void setValue(unsigned i, unsigned j, double v);
  /**
 * operator for accessing each element of matrix
 * @param[in] rows row coordinate
 * @param[in] cols column coordinate
 * @return Returns a number which is on stored on the passed coordinates
 */
  double operator()(const unsigned & rows, const unsigned & cols)const;
  /**
  * Overloaded operator for assigning sparse matrix to another sparse matrix
  * @param[in] rhs SparseMatrix
  * @return Returns SparseMatrix
  */
  SparseMatrix operator=(const SparseMatrix & rhs);

};

#endif // SPARSEMATRIX_H
