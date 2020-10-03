#ifndef DENSEMATRIX_H
#define DENSEMATRIX_H

#include "Matrix.h"
#include "SparseMatrix.h"
#include <vector>
#include <iostream>

/**
 * Child class of matrix.
 * It's used for dense matrices and its numbers are stored in 2D vector.
 * Also has overloaded operators for basic computations.
 */

class DenseMatrix : public Matrix {
	/**2D vector for storing numbers of matrix */
std::vector <std::vector<double> > d_matrix;


public:
  /**
 * Constructor takes 2 arguments and those are rows and columns of the matrix
 *
 * @param[in] m rows of the matrix
 * @param[in] n columns of the matrix
 */
  DenseMatrix(unsigned m, unsigned n);
  /**
 * Copy constructor
 * @param[in] rhs DenseMatrix
 */
  DenseMatrix(const DenseMatrix & rhs);
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
  * @return Returns a number which is stored on the passed coordinates
  */
  double operator()(const unsigned & rows, const unsigned & cols)const;

  /**
  * Overloaded operator for assigning sparse matrix to a dense matrix
  * @param[in] rhs SparseMatrix
  * @return Returns DenseMatrix
  */
  DenseMatrix operator=(const SparseMatrix & rhs);
  /**
  * Overloaded operator for assigning dense matrix to another dense matrix
  * @param[in] rhs DenseMatrix
  * @return Returns DenseMatrix
  */
  DenseMatrix operator=(const DenseMatrix & rhs);
  /**
  * Overloaded operator for adding dense matrix to another dense matrix
  * @param[in] rhs DenseMatrix
  * @return Returns DenseMatrix
  */
  DenseMatrix operator+(const DenseMatrix & rhs);
  /**
  * Overloaded operator for subtracting dense matrix from another dense matrix
  * @param[in] rhs DenseMatrix
  * @return Returns DenseMatrix
  */
  DenseMatrix operator-(const DenseMatrix & rhs);
  /**
  * Overloaded operator for multiplying dense matrix by another dense matrix
  * @param[in] rhs DenseMatrix
  * @return Returns DenseMatrix
  */
  DenseMatrix operator*(const DenseMatrix & rhs);
  /**
  * Overloaded operator for adding number to a matrix
  * @param[in] rhs double
  * @return Returns DenseMatrix
  */
  DenseMatrix operator+(const double& rhs);
  /**
  * Overloaded operator for subtracting number from a matrix
  * @param[in] rhs double
  * @return Returns DenseMatrix
  */
  DenseMatrix operator-(const double& rhs);
  /**
  * Overloaded operator for multiplying matrix by a number
  * @param[in] rhs double
  * @return Returns DenseMatrix
  */
  DenseMatrix operator*(const double& rhs);

};


#endif // DENSEMATRIX_H
