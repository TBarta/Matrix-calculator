#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <memory>

	/**Parent class for matrix object  */
class Matrix
{
protected:
/** Storing rows of matrices */
unsigned rows;
/** Storing columns of matrices */
unsigned cols;
/** Storing type of matrix (sparse/dense).Used for future calculations */
std::string type;

public:
  /**
 * Virtual destructor
 */
virtual ~Matrix();
/**
* Virtual function for cloning shared pointers on parent class
* Used later for storing matrices in vector of shared pointers
*/
virtual std::shared_ptr <Matrix> clone()const = 0;
/**
* Print function for printing matrix
* @param[in] os ostream
*/
virtual void print(std::ostream & os)const = 0;
/**
* Function for setting value of element in matrix on passed certain row and column
* @param[in] i row coordinate
* @param[in] j column coordinate
* @param[in] v value to be set
*/
virtual void setValue(unsigned i, unsigned j, double v) = 0;
/**
* Function for getting type of each matrix
* @return Returns string  with type either Dense or Sparse
*/
std::string getType()const;
/**
* Function for getting rows of each matrix
* @return Returns number of rows in matrix
*/
unsigned getRows()const;
/**
* Function for getting rows of each matrix
* @return Returns number of columns in matrix
*/
unsigned getCols()const;
/**
* Overloaded << operator for printing out the matrix
* @param[in] os iostream
* @param[in] x Matrix
* @return ostream
*/

friend std::ostream& operator<<(std::ostream& os, const Matrix & x);

};

#endif // MATRIX_H
