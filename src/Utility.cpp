#include <string>
#include <iostream>
#include <algorithm>

#include "Utility.h"


char Utility::AssignedVar(std::string & input){
  char var;
  size_t pos_c;
  std::string s;
  pos_c = input.find("=");
  if(pos_c == std::string::npos){
    var = ' ';
  }else{
    s = input.substr(0,pos_c);
    input.erase(0, pos_c + 1);
    s.erase(remove_if(s.begin(), s.end(), isspace), s.end());
    if((std::isalpha(s[0])) && (s.length()==1)){
      var = s[0];
    }else{
      std::cout << "Matrix can be assigned only to a single character" << std::endl;
      var = ' ';
    }
  }
  return var;
}

std::string Utility::InputCheck(std::string & input){
  // [1,2,3][2,3,5]
  char prev = ' ';
  std::string res;
  unsigned l=0,r=0;
  bool first = true;
  for(char& c : input){
    if(c != '-' && c != ',' && c != '[' && c != ']' && c != '.' && !isdigit(c))
      return " ";

    if(c == ']')
      r++;
    else if(c == '[')
      l++;
    if((!isdigit(c) && c == prev ) || (c == ']' && !isdigit(prev)) || (prev == ',' && !isdigit(c) && c != '[' && c != '-') || (c == ',' && !isdigit(prev) && prev != ']'))
      return " ";
    else if((prev == '.' && !isdigit(c)) || (!isdigit(prev) && c == '.'))
      return " ";
    else if((prev == '-' && !isdigit(c)) || (c == '-' && prev != '[' && prev != ','))
      return " ";

    if(!first && c == '[' && prev != ',')
      return " ";

    if(isdigit(c) || c=='.' || c==',' || c=='-')
      res += c;

    if(first)
      first = false;
    prev = c;
  }
  if(r != l || r <= 1 || l <= 1)
    return " ";

  return res;
}

std::string Utility::StrToUpper(std::string str){
  for(unsigned i = 0;i<str.length();i++){
    str[i] = toupper(str[i]);
  }
  return str;
}

// std::string Utility::CheckType(DenseMatrix & m){
//   unsigned zeros = 0;
//   double size,sparsity;
//
//   size = m.getRows() * m.getCols();
//
//   for (unsigned i=0; i < m.getRows(); i++) {
//     for (unsigned j=0; j < m.getCols(); j++) {
//       if(m(i,j) == 0)
//         zeros++;
//     }
//   }
//   sparsity = (zeros / size);
//
//   if(sparsity > 0.5)
//     return "Sparse";
//   else
//     return "Dense";
// }
