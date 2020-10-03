
#include<math.h>
#include "MatrixCalc.h"
#include "DenseMatrix.h"

DenseMatrix MatrixCalc::Split(DenseMatrix & m,unsigned rows, unsigned cols,unsigned x, unsigned y){
  DenseMatrix res(rows,cols);

  for (unsigned i = 0; i < rows; i++) {
    for (unsigned j = 0; j < cols; j++) {
      res.setValue(i,j,m(i+x,j+y));
    }
  }
  return res;
}

DenseMatrix MatrixCalc::Concatenate(DenseMatrix & m,DenseMatrix & n) {

  DenseMatrix res(m.getRows(), m.getCols() + n.getCols());

  for (unsigned i = 0; i < m.getRows(); i++) {
    for (unsigned j = 0; j < m.getCols(); j++) {
      res.setValue(i,j,m(i,j));
    }
  }
  for (unsigned i = 0; i < m.getRows(); i++) {
    for (unsigned j = 0; j < n.getCols(); j++) {
      res.setValue(i,m.getCols() + j,n(i,j));
    }
  }
  return res;
}


unsigned MatrixCalc::Rank(DenseMatrix m){
  unsigned rows;
  rows = m.getRows();
  unsigned rank = m.getCols();

 for (unsigned row = 0; row < rank; row++) {
     if (m(row,row)){
        for (unsigned col = 0; col < rows; col++){
            if (col != row) {
              double mult = (double)m(col,row) / m(row,row);
              for (unsigned i = 0; i < rank; i++){
                m.setValue(col,i, m(col,i) - mult * m(row,i));
              }
           }
        }
     }
     else{
         bool reduce = true;
         for (unsigned i = row + 1; i < rows;  i++){

             if (m(i,row)){
                 for (unsigned k = 0; k < rank; k++){
                     double temp = m(row,k);
                     m.setValue(row,k,m(i,k));
                     m.setValue(i,k,temp);
                 }
                 reduce = false;
                 break ;
             }
         }
         if (reduce){
           rank--;

           for (unsigned i = 0; i < rows; i ++)
               m.setValue(i,row,m(i,rank));
         }
         row--;
     }
 }
 return rank;
}

void MatrixCalc::SwapRow(DenseMatrix & m, int i, int j) {

    for (unsigned k = 0; k < m.getCols(); k++){
        double temp = m(i,k);
        m.setValue(i,k,m(j,k));
        m.setValue(j,k,temp);
    }
}

void MatrixCalc::AddMultipleRow(DenseMatrix & m,double multiple, int i, int j){

  for (unsigned k = 0; k < m.getCols(); k++){
      m.setValue(i,k,m(i,k)-(m(j,k)*multiple));
  }
}


void MatrixCalc::GetCofactor(const DenseMatrix & m, DenseMatrix & temp, int p, int q,int n){
  int i = 0, j = 0;

  for (int row = 0; row < n; row++){
    for (int col = 0; col < n; col++){
      if (row != p && col != q){
        temp.setValue(i,j++,m(row,col));
        if (j == n - 1){
            j = 0;
            i++;
          }
        }
      }
  }
}
void MatrixCalc::Adjoint(const DenseMatrix & m,DenseMatrix & adj)
{
  int sign = 1, n = m.getCols();
  DenseMatrix temp(n,n);

  if (n == 1) {
      adj.setValue(0,0,1);
      return;
  }

  for (int i = 0; i < n; i++){
    for (int j=0; j < n;j++){
      GetCofactor(m, temp, i, j, n);

      sign = ((i+j) % 2==0) ? 1 : -1;

      adj.setValue(j,i,(sign)*(Determinant(temp, n-1)));
    }
  }
}

DenseMatrix MatrixCalc::Inverse(DenseMatrix & m,double & det){

  int n = m.getRows();
  DenseMatrix res(n,n);


  // Find Adjoint
  DenseMatrix adj(n,n);
  Adjoint(m, adj);

  // Find Inverse by Adjoint / Det
  for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
          res.setValue(i,j,adj(i,j) / det);

  return res;
}

DenseMatrix MatrixCalc::Transpose(DenseMatrix & m){
  DenseMatrix res(m.getCols(), m.getRows());

  for (unsigned i=0; i<m.getCols(); i++) {
    for (unsigned j=0; j<m.getRows(); j++) {
      res.setValue(i,j,m(j,i));
    }
  }
  return res;
}

DenseMatrix MatrixCalc::Gem(DenseMatrix m){
  unsigned rows = m.getRows(),cols = m.getCols();

			unsigned lead = 0;
			for (unsigned r = 0; r < rows; r++) {
				if (cols <= lead) {
					break;
				}
				unsigned i = r;
				while (m(i,lead) == 0) {
					if (++i >= rows) {
						i = r;
						if (++lead >= cols) {
							return m;
						}
					}
				}
        MatrixCalc::SwapRow(m,i,r);

				double tmp = m(r,lead);

				for (unsigned k = 0; k < cols; k++) {
					m.setValue(r,k,m(r,k) / tmp);
				}


				for (unsigned i  = 0; i < rows; i++) {
					if (i != r) {
						MatrixCalc::AddMultipleRow(m,m(i,lead), i, r);
					}
				}
			}
			return m;
}


double MatrixCalc::Determinant(DenseMatrix & m, int n){
  double res = 0;
  int c, i, j, subi, subj;
  DenseMatrix submat(n,n);
  if (n == 2)
     res = ((m(0,0) * m(1,1)) - (m(1,0) * m(0,1)));
  else{
    for(c = 0; c < n; c++){
      subi = 0;
      for(i = 1; i < n; i++){
        subj = 0;
        for(j = 0; j < n; j++){
          if (j == c)
            continue;
          submat.setValue(subi,subj,m(i,j));
          subj++;
        }
        subi++;
      }
      res = res + (pow(-1 ,c) * m(0,c) * Determinant(submat, n - 1));
    }
  }
  return res;
}
