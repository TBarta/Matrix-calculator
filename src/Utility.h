#ifndef UTILITY_H
#define UTILITY_H

#include "DenseMatrix.h"
#include "SparseMatrix.h"

/**
 * Class that stores utiliy functions that are needed in UserInterface
 * Mainly works with input
 */

class Utility
{

public:
  /**
  * Checks if matrix is assigned to a variable
  * If it is assigned it returns the variable else returns a empty char
  * @param[in] input string
  * @return Returns variable if there is any
  */
  static char AssignedVar(std::string & input);
  /**
  * Checks input when creating a matrix
  * @param[in] input string
  * @return Returns string of numbers to be added to matrix or and empty string if the input if wrong
  */
  static std::string InputCheck(std::string & input);
  /**
  * Takes string and returns it in uppercase
  * @param[in] input string
  * @return Returns the passed string in upper case
  */
  static std::string StrToUpper(std::string str);
  /**
  * Checks type of matrix (sparse/dense)
  * @param[in] m DenseMatrix
  * @return Returns either Dense or Sparse depending on zeros in matrix
  */
  // static std::string CheckType(DenseMatrix & m);
  
};



#endif // UTILITY_H
