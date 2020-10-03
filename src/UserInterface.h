
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <map>
#include "DenseMatrix.h"
#include "SparseMatrix.h"

/**
* Class that creates users interface
* Users working with the program using commands,variables and operators
* UserInterface takes those commands, checks their validity and then passes the arguments for calculation
* It also stores matrices assigned to variables and performs some basic operations(+,-,*) on its own
*/
class UserInterface{
/**Map of shared pointers pointing on matrix and chars(variables) for storing assigned matrices*/
std::map < char, std::shared_ptr <Matrix> > matrices;
/**Status that tells if the program is running or not */
bool status;
public:
  /**
   * Function that is basically a while loop in which the program runs
   */
  void Run();
  /**
   * Function that clears all stored matrices and variables
   */
  void Clear();
  /**
   * Function that prints some help commands
   */
  void Help();
  /**
   * Function that turns the program off
   */
  void Quit();
  /**
   * Function that prints instructions on how to work with matrices
   */
  void MatrixHelp();
  /**
   * Function that prints instructions for complex calculations
   */
  void ComplexCalc();

  /**
   * Function that prints matrix assigned to passed variable
   * @param[in] var Variable printed matrix is assigned to
   */
  void PrintVar(char & input)const;
  /**
   * Function that saves matrix and its assigned variable
   * It's also determines if the matrix is to be saved as sparse or dense
   * In case it transforms it to sparse since calculations are done with dense matrices
   * @param[in] M DenseMatrix to be saved
   * @param[in] var Variable to be saved
   */
  void SaveMatrix(DenseMatrix & m, char & var);
  /**
   * Function that transforms Dense matrix into Sparse
   * Used before saving matrix
   * @param[in] m DenseMatrix
   * @return Returns a SparseMatrix
   */
  // SparseMatrix Transform(DenseMatrix & m);
  // /**
  //  * Function that takes input and creates matrix out of it
  //  * @param[in] input string
  //  * @return Returns True if creation was successful, False otherwise
  //  */
  bool CreateMatrix(std::string & input);
  /**
   * Function that takes input and creates transposed matrix out of it
   * @param[in] input string
   * @return Returns True if operation was successful, False otherwise
   */
  bool TransposeMatrix(std::string & input);
  /**
   * Function that takes input and gets rank of matrix out of it
   * @param[in] input string
   * @return Returns True if operation was successful, False otherwise
   */
  bool RankMatrix(std::string & input);
  /**
   * Function that takes input and gets determinant of matrix out of it
   * @param[in] input string
   * @return Returns True if operation was successful, False otherwise
   */
  bool DetMatrix(std::string & input);
  /**
   * Function that takes input and gets inverse of matrix out of it
   * @param[in] input string
   * @return Returns True if operation was successful, False otherwise
   */
  bool InverseMatrix(std::string & input);
  /**
   * Function that takes input and performs Gaussian elimination with matrix out of it
   * @param[in] input string
   * @return Returns True if operation was successful, False otherwise
   */
  bool GemMatrix(std::string & input);
  /**
   * Function that takes input and concatenates 2 matrices together
   * @param[in] input string
   * @return Returns True if operation was successful, False otherwise
   */
  bool ConcatenateMatrix(std::string & input);
  /**
   * Function that takes input and cuts out matrix out of another
   * @param[in] input string
   * @return Returns True if operation was successful, False otherwise
   */
  bool SplitMatrix(std::string & input);
  /**
   * Function that decides which basic operation(*,-,+) to be performed
   * Also determines if it's to be perfomed on matrix and matrix/number and matrix/number and number
   * @param[in] input string
   * @return Returns True if operation was successful, False otherwise
   */
  bool BasicOperations(std::string & input, size_t pos);
  /**
   * Function that performs basic operations on matrix and another matrix
   * @param[in] char m1 variable of first matrix
   * @param[in] char m1 variable of second matrix
   * @param[in] char sign that determines the operation
   * @return Returns result matrix
   */
  DenseMatrix MatrixAndMatrix(char & m1, char & m2, char & sign);
  /**
   * Function that performs basic operations on matrix and number
   * @param[in] m1 variable of the matrix
   * @param[in] d1 number that the matrix is operated by
   * @param[in] sign that determines the operation
   * @return Returns result matrix
   */
  DenseMatrix MatrixAndNumber(char & m, double & n, char & sign);
  /**
   * Function that performs basic operations on number and number
   * @param[in] d1 the first number
   * @param[in] d2 the second number
   * @param[in] sign that determines the operation
   * @return Returns result number
   */
  double NumberAndNumber(double & d1, double & d2, char & sign);


};

#endif // USERINTERFACE_H
