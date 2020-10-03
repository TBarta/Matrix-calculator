
#ifndef MATRIXCALC_H
#define MATRIXCALC_H

#include "DenseMatrix.h"
/**
 * Class that performs complex matrix computations
 */
class MatrixCalc {

public:
  /**
 * Function for getting transpose of matrix
 * @param[in] m DenseMatrix
 * @return Returns tranpose of passed matrix
 */
  static DenseMatrix Transpose(DenseMatrix & m);
  /**
 * Function for concatenating 2 matrices of the same size
 * @param[in] m DenseMatrix
  * @param[in] n DenseMatrix
 * @return Returns concatenated matrix of passed matrices
 */
  static DenseMatrix Concatenate(DenseMatrix & m,DenseMatrix & n);
  /**
 * Function for getting determinant of matrix
 * @param[in] m DenseMatrix
 * @param[in] n number of size of the matrix
 * @return Returns determinant of passed matrix
 */
  static double Determinant(DenseMatrix & m, int n);
  /**
 * Function for getting rank of matrix
 * @param[in] m DenseMatrix
 * @return Returns rank of passed matrix
 */
  static unsigned Rank(DenseMatrix m);
  /**
 * Function for calculating Gaussian elimination of the matrix
 * @param[in] m DenseMatrix
 * @return Returns matrix after Gaussian elimination
 */
  static DenseMatrix Gem(DenseMatrix m);
  /**
 * Function for getting inverse of matrix
 * @param[in] m DenseMatrix, determinant of the matrix
 * @param[in] det determinant of the matrix
 * @return Returns inverse of passed matrix
 */
  static DenseMatrix Inverse(DenseMatrix & m,double & det);
  /**
 * Function for cutting out matrix of desired size and from desired coordinates
 * @param[in] m DenseMatrix
 * @param[in] rows represents rows of desired matrix
 * @param[in] cols represents columns of desired matrix
 * @param[in] i row coordinate for cutting desired matrix
 * @param[in] i column coordinate for cutting desired matrix
 * @return Returns matrix of desired size cut out from desired coordinates
 */
  static DenseMatrix Split(DenseMatrix & m,unsigned rows, unsigned cols,unsigned i, unsigned j);
  /**
 * Help function for getting an inverse of matrices
 * @param[in] m DenseMatrix
 * @param[in] temp DenseMatrix
 * @param[in] p row of the matrix
 * @param[in] q column of the matrix
 * @param[in] n size of the matrix to be inversed
 * @return Returns tranpose if passed matrix
 */
  static void GetCofactor(const DenseMatrix & m, DenseMatrix & temp, int p, int q,int n);
  /**
 * Function that return adjoint matrix of matrix to be inversed
 * Help function for getting an inverse of matrices
 * @param[in] m DenseMatrix matrix to be inversed
 * @param[in] adj DenseMatrix matrix to be adjoint
 */
  static void Adjoint(const DenseMatrix & m,DenseMatrix & adj);
  /**
 * Function that swap rows in matrices
 * Help function for performing Gaussian elimination
 * @param[in] m DenseMatrix
 * @param[in] row to be swapped for
 * @param[in] row to be swapped
 */
  static void SwapRow(DenseMatrix & m, int i, int j);
  /**
 * Help function for performing Gaussian elimination
 * Basically a G3 operation of Gaussian elimination
 * @param[in] m DenseMatrix
 * @param[in] multiple number for multiply row
 * @param[in] i first row
 * @param[in] j second row
 */
  static void AddMultipleRow(DenseMatrix & m,double multiple, int i, int j);

};


#endif // MATRIXCALC_H
