#include <map>
#include <string>
#include <iostream>
#include <string>
#include <locale>
#include <algorithm>
#include <cctype>
#include <memory>
#include "Matrix.h"
#include "UserInterface.h"
#include "DenseMatrix.h"
#include "SparseMatrix.h"
#include "MatrixCalc.h"
#include "Utility.h"



void UserInterface::SaveMatrix(DenseMatrix & m, char & var){

    auto it = matrices.find(var);

    if (it != matrices.end())
      it->second = m.clone();
    else
      matrices.insert(std::make_pair(var, m.clone()));

  std::cout << "Matrix has been assigned to variable "<< var << std::endl;
}

bool UserInterface::DetMatrix(std::string & input){
  size_t pos;
  char m;
  double res;
  int cols,rows;

  pos = input.find(".det()");
  m = input[pos-1];

  auto it = (matrices.find(m));

  if(it != matrices.end()){
    auto a = it->second;
    cols = a->getCols();
    rows = a->getRows();
    if(cols != rows){
      std::cout << "You cannot compute determinant of a non-square matrix!" << std::endl;
      return false;
    }
    DenseMatrix *ptr_d1 = dynamic_cast<DenseMatrix*> (a.get());
    SparseMatrix *ptr_s1 = dynamic_cast<SparseMatrix*> (a.get());
    DenseMatrix d1(0,0);

    if(a->getType() == "Dense")
      d1 = (*ptr_d1);
    else
      d1 = (*ptr_s1);

    res = MatrixCalc::Determinant(d1,cols);
    std::cout << res << std::endl;
  }else{
    std::cout << "Wrong variable!" << std::endl;
    return false;
  }

  return true;

}
bool UserInterface::InverseMatrix(std::string & input){
  size_t pos;
  char var,m;
  double det;
  bool assigned;
  DenseMatrix res(0,0);
  int cols,rows;

  var = Utility::AssignedVar(input);
  if(var == ' ')
    assigned = false;
  else
    assigned = true;

  pos = input.find(".inverse()");
  m = input[pos-1];

  auto it = (matrices.find(m));

  if(it != matrices.end()){
    auto a = it->second;
    cols = a->getCols();
    rows = a->getRows();
    if(cols != rows){
      std::cout << "You can only inverse square matrices" << std::endl;
      return false;
    }
    DenseMatrix *ptr_d1 = dynamic_cast<DenseMatrix*> (a.get());
    SparseMatrix *ptr_s1 = dynamic_cast<SparseMatrix*> (a.get());
    DenseMatrix d1(0,0);

    if(a->getType() == "Dense")
      d1 = (*ptr_d1);
    else
      d1 = (*ptr_s1);

    det = MatrixCalc::Determinant(d1,cols);

    if(det == 0){
      std::cout << "You cannot compute inverse of a singular matrix!" << std::endl;
      return false;
    }

    res = MatrixCalc::Inverse(d1,det);
    std::cout << res;

  }else{
    std::cout << "Wrong variable!" << std::endl;
    return false;
  }

  if(assigned)
    SaveMatrix(res,var);

  return true;

}

bool UserInterface::ConcatenateMatrix(std::string & input){
  size_t pos;
  char var,m,n;
  bool assigned;
  std::string s;
  DenseMatrix res(0,0);

  var = Utility::AssignedVar(input);
  if(var == ' ')
    assigned = false;
  else
    assigned = true;

  pos = input.find(".concat(");
  m = input[pos-1];
  input.erase(0,pos+8);
  pos = input.find(")");
  if(pos == std::string::npos){
    std::cout << "Wrong input!" << std::endl;
    return false;
  }

  s = input.substr(0,pos);
  s.erase(remove_if(s.begin(), s.end(), isspace), s.end());
  n = s[0];
  auto it1 = (matrices.find(m));
  auto it2 = (matrices.find(n));

  if(it1 != matrices.end() && it2 != matrices.end()){
    auto a = it1->second;
    auto b = it2->second;

    if(a->getRows() != b->getRows()){
      std::cout << "To concatenate 2 matrices they must have the same amount of rows!" << std::endl;
      return false;
    }
    DenseMatrix *ptr_d1 = dynamic_cast<DenseMatrix*> (a.get());
    SparseMatrix *ptr_s1 = dynamic_cast<SparseMatrix*> (a.get());
    DenseMatrix *ptr_d2 = dynamic_cast<DenseMatrix*> (b.get());
    SparseMatrix *ptr_s2 = dynamic_cast<SparseMatrix*> (b.get());
    DenseMatrix d1(0,0);
    DenseMatrix d2(0,0);

    if(a->getType() == "Dense")
      d1 = (*ptr_d1);
    else
      d1 = (*ptr_s1);

    if(b->getType() == "Dense")
      d2 = (*ptr_d2);
    else
      d2 = (*ptr_s2);

      res = MatrixCalc::Concatenate(d1,d2);
      std::cout << res;
  }else{
    std::cout << "Wrong variable!" << std::endl;
    return false;
  }

  if(assigned)
    SaveMatrix(res,var);

  return true;

}

bool UserInterface::RankMatrix(std::string & input){
  size_t pos;
  char var,m;
  bool assigned;
  unsigned res;

  var = Utility::AssignedVar(input);
  if(var == ' ')
    assigned = false;
  else
    assigned = true;

  pos = input.find(".rank()");
  m = input[pos-1];

  auto it = (matrices.find(m));

  if(it != matrices.end()){
    auto a = it->second;

    DenseMatrix *ptr_d1 = dynamic_cast<DenseMatrix*> (a.get());
    SparseMatrix *ptr_s1 = dynamic_cast<SparseMatrix*> (a.get());
    DenseMatrix d1(0,0);

    if(a->getType() == "Dense")
      d1 = (*ptr_d1);
    else
      d1 = (*ptr_s1);

    if(a->getCols() > a->getRows())
      d1 = MatrixCalc::Transpose(d1);

      res = MatrixCalc::Rank(d1);
      std::cout << res << std::endl;
  }else{
    std::cout << "Wrong variable!" << std::endl;
    return false;
  }

  return true;

}
bool UserInterface::SplitMatrix(std::string & input){

  size_t pos,pos_x,pos_y;
  char var,m;
  bool assigned;
  std::string s1,s2;
  unsigned cols,rows,x,y;
  DenseMatrix res(0,0);

  var = Utility::AssignedVar(input);
  if(var == ' ')
    assigned = false;
  else
    assigned = true;

  pos = input.find(".split(");
  m = input[pos-1];

  pos_x = input.find('(');
  pos_y = input.find(')');
  if(pos_x == std::string::npos || pos_y == std::string::npos){
    std::cout << "Wrong input" << std::endl;
    return false;
  }
  s1 = input.substr(pos_x,pos_y - pos_x + 1);

  pos_x = input.find('[');
  pos_y = input.find(']');
  if(pos_x == std::string::npos || pos_y == std::string::npos){
    std::cout << "Wrong input" << std::endl;
    return false;
  }
  s2 = input.substr(pos_x,pos_y - pos_x + 1);

// getting rid of whitespaces
  s1.erase(remove_if(s1.begin(), s1.end(), isspace), s1.end());
  s2.erase(remove_if(s2.begin(), s2.end(), isspace), s2.end());
  if(isdigit(s1[1]) && isdigit(s1[3]) && isdigit(s2[1]) && isdigit(s2[3])){
    rows = (unsigned)s1[1] - 48;
    cols = (unsigned)s1[3] - 48;
    x = (unsigned)s2[1] -48;
    y = (unsigned)s2[3] - 48;
  }else{
    std::cout << "Wrong input" << std::endl;
    return false;
  }

  auto it = (matrices.find(m));

  if(it != matrices.end()){
    auto a = it->second;
    if(a->getCols() < cols || a->getRows() < rows || (a->getRows() - x) < rows || (a->getCols() - y) < cols || rows < 2 || cols < 1 ){
      std::cout << "Wrong parameters!" << std::endl;
      return false;
    }
    DenseMatrix *ptr_d1 = dynamic_cast<DenseMatrix*> (a.get());
    SparseMatrix *ptr_s1 = dynamic_cast<SparseMatrix*> (a.get());
    DenseMatrix d1(0,0);

    if(a->getType() == "Dense")
      d1 = (*ptr_d1);
    else
      d1 = (*ptr_s1);

      res = MatrixCalc::Split(d1,rows,cols,x,y);
      std::cout << res;
  }else{
    std::cout << "Wrong variable!" << std::endl;
    return false;
  }
  if(assigned)
    SaveMatrix(res,var);

  return true;

}
bool UserInterface::GemMatrix(std::string & input){
  size_t pos;
  char var,m;
  bool assigned;
  DenseMatrix res(0,0);

  var = Utility::AssignedVar(input);
  if(var == ' ')
    assigned = false;
  else
    assigned = true;

  pos = input.find(".gem()");
  m = input[pos-1];

  auto it = (matrices.find(m));

  if(it != matrices.end()){
    auto a = it->second;
    if(a->getCols() == 1){
      std::cout << "You cannot use Gaussian elimination on vector" << std::endl;
      return false;
    }
    DenseMatrix *ptr_d1 = dynamic_cast<DenseMatrix*> (a.get());
    SparseMatrix *ptr_s1 = dynamic_cast<SparseMatrix*> (a.get());
    DenseMatrix d1(0,0);

    if(a->getType() == "Dense")
      d1 = (*ptr_d1);
    else
      d1 = (*ptr_s1);


    res = MatrixCalc::Gem(d1);

    std::cout << res;

  }else{
    std::cout << "Wrong variable!" << std::endl;
    return false;
  }

  if(assigned)
    SaveMatrix(res,var);

  return true;

}

bool UserInterface::TransposeMatrix(std::string & input){
  size_t pos;
  char var,m;
  bool assigned;
  DenseMatrix res(0,0);

  var = Utility::AssignedVar(input);
  if(var == ' ')
    assigned = false;
  else
    assigned = true;

  pos = input.find(".trans()");
  m = input[pos-1];

  auto it = (matrices.find(m));

  if(it != matrices.end()){
    auto a = it->second;
    if(a->getCols() == 1){
      std::cout << "You cannot transpose a vector!" << std::endl;
      return false;
    }
    DenseMatrix *ptr_d1 = dynamic_cast<DenseMatrix*> (a.get());
    SparseMatrix *ptr_s1 = dynamic_cast<SparseMatrix*> (a.get());
    DenseMatrix d1(0,0);

    if(a->getType() == "Dense")
      d1 = (*ptr_d1);
    else
      d1 = (*ptr_s1);

      res = MatrixCalc::Transpose(d1);
      std::cout << res;
  }else{
    std::cout << "Wrong variable!" << std::endl;
    return false;
  }

  if(assigned)
    SaveMatrix(res,var);

  return true;

}
// SparseMatrix UserInterface::Transform(DenseMatrix& m){
//   unsigned rows = m.getRows();
//   unsigned cols = m.getCols();
//   SparseMatrix res(rows,cols);
//
//   for(unsigned i = 0; i < rows;i++){
//     for(unsigned j = 0; j < cols;j++){
//       if(m(i,j) != 0)
//         res.setValue(i,j,m(i,j));
//     }
//   }
//   return res;
// }

double UserInterface::NumberAndNumber(double & d1, double & d2, char & sign){
  switch(sign){
    case '+': return d1+d2;
              break;
    case '-': return d1-d2;
              break;
    default: return d1*d2;
              break;
  }
}
void UserInterface::Clear(){
  matrices.clear();
  std::cout << "All variables have been cleared" << std::endl;
}

void UserInterface::ComplexCalc(){
    std::cout << "You can do complex computations with matrices using these keywords :\nA.trans()\t\t- To get transposed matrix of matrix A\nA.inverse()\t\t- To get inversed matrix to matrix A\nA.det()\t\t\t- To get determinant of matrix A\nA.gem()\t\t\t- To perform the Gaussian elimination method with matrix A\nA.rank()\t\t\t- To get the rank of matrix A\nA.concat(B)\t\t- To concatinate matrix B(from the right)to matrix A\nA.split(3,3)[3,0]\t- To cut out matrix of size 3x3 from position 3 and 0" << std::endl;
}

void UserInterface::Help(){
  std::cout << "List of commands :\nquit\t- To quit the program\nclear\t- To clear all assigned variables\nmatrix\t- To show you how to work with matrices\ncalc\t- To show you syntax of more complex computations with matrices" << std::endl;
}

void UserInterface::MatrixHelp(){
  std::cout << "Valid syntax for creating matrix A is \"A=matrix([1,2,3],[4,5,6])\"\nVariables can only be a single character(a-z)(A-Z)\nTo add matrices A and B type \"A+B\"\nThis way you can use all following operators: +,-,*\nYou can find more complex computations by typing command \"calc\"\nRemember, always do one computation at a time or you might not get the correct result!" << std::endl;
}

void UserInterface::Quit(){
  std::cout << "Thank you for using Calctrix !" << std::endl;
  status = false;
}

void UserInterface::PrintVar(char & input)const{

  std::cout << *(matrices.find(input))->second;
}

bool UserInterface::CreateMatrix(std::string & input){

  std::vector<double> nums;
  bool assigned;
  std::string checked,v,s;
  unsigned rows,cols,zeros = 0;
  double d;
  size_t pos_c,pos_col,col_count,row_count;
  char var;



  var = Utility::AssignedVar(input);
  if(var == ' ')
    assigned = false;
  else
    assigned = true;


// FIRST INPUT CHECKING + GETTING RID OF TRASH
  pos_c = input.find('(');
  if(pos_c == std::string::npos){
    return false;
  }else{
    input.erase(0,pos_c+1);
    pos_c = input.find(')');
    if(pos_c == std::string::npos)
      return false;
  }
  input.erase(input.begin()+pos_c,input.end());

  // CHECK INPUT FUNCTION
  checked = Utility::InputCheck(input);
  if(checked == " ")
    return false;

  // SELECTING OUT COLUMS AND ROWS
  row_count = std::count(input.begin(), input.end(), '[');
  pos_col = input.find(']');
  col_count = std::count(input.begin(), input.begin()+pos_col, ',');

  rows = (row_count);
  cols = (col_count + 1);

  // FILLING NUMS VECTOR, USING ',' AS A DELIMITER
  while ((pos_c = checked.find(',')) != std::string::npos) {
      s = checked.substr(0, pos_c);
      try {
          d = std::stod(s);
      } catch (const std::invalid_argument&) {
          return false;
      } catch (const std::out_of_range&) {
          return false;
      }
      if(d == 0)
        zeros++;
      nums.push_back(d);
      checked.erase(0, pos_c + 1);
  }
  // PUSHING WHATS LEFT AFTER LAST ','
  try {
      d = std::stod(checked);
  } catch (const std::invalid_argument&) {
      return false;
  } catch (const std::out_of_range&) {
      return false;
  }
  if(d == 0)
    zeros++;
  nums.push_back(d);

//  CHECKING IF ROWS ARE MATCHING NUMBERS

  if(rows <= 0 || (nums.size() % rows) != 0)
    return false;

  // CREATE MATRIX OBJECT
  DenseMatrix res(rows,cols);
  unsigned k = 0;
  for(unsigned i = 0; i < rows;i++){
    for(unsigned j = 0; j < cols;j++){
      res.setValue(i,j,nums[k]);
      k++;
    }
  }
  std::cout << res;
 // SAVING MATRIX
  if(assigned)
    SaveMatrix(res,var);

  return true;
}

DenseMatrix UserInterface::MatrixAndMatrix(char & m1, char & m2, char & sign){

      auto a = (matrices.find(m1)->second);
      auto b = (matrices.find(m2)->second);

      DenseMatrix *ptr_d1 = dynamic_cast<DenseMatrix*> (a.get());
      DenseMatrix *ptr_d2 = dynamic_cast<DenseMatrix*> (b.get());
      SparseMatrix *ptr_s1 = dynamic_cast<SparseMatrix*> (a.get());
      SparseMatrix *ptr_s2 = dynamic_cast<SparseMatrix*> (b.get());

      DenseMatrix d1(0,0);
      DenseMatrix d2(0,0);
      DenseMatrix res(0,0);

      if((a->getType() == "Dense") && (b->getType() == "Dense")){
        d1 = (*ptr_d1);
        d2 = (*ptr_d2);
      }else if((a->getType() == "Dense") && (b->getType() == "Sparse")){
        d1 = (*ptr_d1);
        d2 = (*ptr_s2);
      }else if((a->getType() == "Sparse") && (b->getType() == "Dense")){
        d1 = (*ptr_s1);
        d2 = (*ptr_d2);
      }else{
        d1 = (*ptr_s1);
        d2 = (*ptr_s2);
      }

      if(sign != '*' && ((a->getCols() != b->getCols()) || (a->getRows() != b->getRows()))){
        std::cout << "To add or subtract matrices, they must be the same size!" << std::endl;
      }else if(sign == '*' && (a->getCols() != b->getRows())){
        std::cout << "To multiply 2 matrices, the rows of the first must be the same size as the columns of the second!" << std::endl;
      }else if(sign== '+'){
        res = d1+d2;
      }else if(sign== '-'){
        res = d1-d2;
      }else{
        res = d1 * d2;
      }
      return res;
  }

  DenseMatrix UserInterface::MatrixAndNumber(char & m, double & n, char & sign){

    auto a = (matrices.find(m)->second);

    DenseMatrix *ptr_d1 = dynamic_cast<DenseMatrix*> (a.get());
    SparseMatrix *ptr_s1 = dynamic_cast<SparseMatrix*> (a.get());

    DenseMatrix d1(0,0);
    DenseMatrix res(0,0);

    if(a->getType() == "Dense")
      d1 = (*ptr_d1);
    else
      d1 = (*ptr_s1);

    if(sign == '+')
      res = (d1+n);
    else if( sign == '-')
      res = (d1-n);
    else
      res = (d1*n);


    return res;
  }

  bool UserInterface::BasicOperations(std::string & input, size_t pos){
    bool assigned,v1,v2;
    char sign, var;
    std::string s1,s2,s3;
    double d1,d2;
    DenseMatrix res(0,0);

    sign = input[pos];
    s1 = input.substr(0,pos);
    s2 = input.substr(pos+1);


    var = Utility::AssignedVar(s1);
    if(var == ' ')
      assigned = false;
    else
      assigned = true;


    s1.erase(remove_if(s1.begin(), s1.end(), isspace), s1.end());
    s2.erase(remove_if(s2.begin(), s2.end(), isspace), s2.end());


    try {
        d1 = std::stod(s1);
        v1 = false;
    } catch (const std::invalid_argument&) {
        v1 = true;
    } catch (const std::out_of_range&) {
        std::cout << "Invalid operation" << std::endl;
        return false;
    }
    try {
        d2 = std::stod(s2);
        v2 = false;
    } catch (const std::invalid_argument&) {
        v2 = true;
    } catch (const std::out_of_range&) {
        std::cout << "Invalid operation" << std::endl;
        return false;
    }

    if((v1 && s1.length() != 1) || (v2 && s2.length() != 1))
    {
      std::cout << "Wrong input!\nRemember, you can only do one calculation at a time." << std::endl;
      return false;
    }

    if(v1 && !v2 &&(matrices.find(s1[0]) != matrices.end())){
        res = MatrixAndNumber(s1[0],d2,sign);
        std::cout << res;
    }else if(!v1 && v2 && (matrices.find(s2[0]) != matrices.end())){
      if(sign != '-'){
          res = MatrixAndNumber(s2[0],d1,sign);
          std::cout << res;
        }else{
        std::cout << "You cannot subtract matrix from a number" << std::endl;
        return false;
        }
    }else if(!v1 && !v2 && assigned){
      std::cout << "You can only assign matrices to variables" << std::endl;
      return false;
    }else if(!v1 && !v2){
      std::cout << NumberAndNumber(d1,d2,sign) << std::endl;
    }else if((matrices.find(s1[0]) != matrices.end()) && (matrices.find(s2[0]) != matrices.end())){
      res =  MatrixAndMatrix(s1[0],s2[0],sign);
      std::cout << res;
    }else{
      std::cout << "Wrong input or variables!" << std::endl;
      return false;
    }

    if(assigned && res.getRows() != 0)
      SaveMatrix(res,var);


    return true;
  }

void UserInterface::Run(){
  std::string input;
  size_t sign_pos;
  status = true;

  std::cout << "Welcome to matrix calculator Calctrix v.1.1 \n If you need help, please type \'help\'" << std::endl;
  while(status){
    sign_pos = 0;
    std::getline (std::cin,input);

    if(Utility::StrToUpper(input) ==  "CALC")
      ComplexCalc();
    if(Utility::StrToUpper(input) ==  "HELP")
      Help();
    if(Utility::StrToUpper(input) ==  "QUIT")
      Quit();
    if(Utility::StrToUpper(input) ==  "CLEAR")
      Clear();
    if(Utility::StrToUpper(input) ==  "MATRIX"){
      MatrixHelp();
      input = "";
    }
    if(input.find("matrix(") != std::string::npos){
      if(!CreateMatrix(input)){
        std::cout << "Matrix could not be created" << std::endl;
      }
      input = "";
    }


    if(input.find("+") != std::string::npos)
      sign_pos = input.find("+");
    else if(input.find("-") != std::string::npos)
      sign_pos = input.find("-");
    else if(input.find("*") != std::string::npos)
      sign_pos = input.find("*");

    if(sign_pos != 0) {
      BasicOperations(input,sign_pos);
      input = "";
    }
    if(input.find(".rank()") != std::string::npos){
      RankMatrix(input);
      input = "";
    }
    if(input.find(".trans()") != std::string::npos){
      TransposeMatrix(input);
      input = "";
    }
    if(input.find(".det()") != std::string::npos){
      DetMatrix(input);
      input = "";
    }
    if(input.find(".inverse()") != std::string::npos){
      InverseMatrix(input);
      input = "";
    }
    if(input.find(".concat(") != std::string::npos){
      ConcatenateMatrix(input);
      input = "";
    }
    if(input.find(".split(") != std::string::npos){
      SplitMatrix(input);
      input = "";
    }
    if(input.find(".gem()") != std::string::npos){
      GemMatrix(input);
      input = "";
    }


    if(input.length()==1 && std::isalpha(input[0])){
      if(matrices.find(input[0]) != matrices.end()){
        PrintVar(input[0]);
      }
    }
  }
}
