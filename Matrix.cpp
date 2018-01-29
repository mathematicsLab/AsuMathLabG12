#include<iostream>
#include"Matrix.h"
//#include"stdlib.h"
#include <stdio.h>
#include"string.h"
#include"map"
#include<string>
#include<math.h>
//#include<fstream>
#include <algorithm> 
//#include<sstream>
//#include <cctype>
//#include <locale>
using namespace std;

class Exception
{
public:
  const char* msg;
  Exception(const char* arg)
   : msg(arg)
  {
  }
};



    int nRow;
    int nCol;
    double **pData;
    char name;

    //default constructor
    Matrix:: Matrix()
    {
        this->nRow=0; this->nCol=0; 
        this->pData=new double*[0];
        for(int i=0;i<0;i++){
            this->pData[i]=new double[0];
        }       
    }

    // constructor
    Matrix::Matrix(int row,int col){
        
        nRow=row; nCol=col; 
        pData=new double*[row];
        for(int i=0;i<col;i++){
            pData[i]=new double[col];
        }       

    }
   /*  ~Matrix()
    {
        for (int i=0;i<nCol;i++)
        {
            delete pData[i];
        }
        delete pData;
    }  */

    void Matrix:: setValue(double data[]){
        //set values
        int i=0;
        for(int r=0;r<this->nRow;r++){
            for(int c=0;c<this->nCol;c++){
                this->pData[r][c]=data[i];
                i++;
            }
        }
    }

    //Getters
     // index operator. 
  

   
   double& Matrix::operator()(const int r, const int c)
  {
    if (pData != NULL && r > 0 && r <= nRow && c > 0 && c <= nCol)
    {
      return this->pData[r-1][c-1];
    }
    else
    {
      throw Exception("Subscript out of range");
    }
  }


 int Matrix::getRow(){
        return this->nRow;
    }
 int Matrix:: getCol(){
        return this->nCol;
    }
 double Matrix::get(int r,int c){
    return this->pData[r][c];
}

void Matrix::printMatrix(){
    for(int r=0;r<nRow;r++){
        for(int c=0;c<nCol;c++){
            cout<<pData[r][c]<<" ";
        }
        cout<<endl;
    }
}

 // add a double value 
 Matrix Matrix::add(Matrix a, double v)
  {
   int row=a.getRow(); int col=a.getCol(); int i=0;
    double *values=new double[row*col];
     
        for(int r=0;r<row;r++){
            for(int c=0;c<col;c++){
                values[i]=a.get(r,c)+v;
                i++;
            }
        }
         Matrix c(row,col);
    c.setValue(values);
    return c;

  }

  //add matrix with matrix
 Matrix Matrix:: add(Matrix a, Matrix b){
    int row=a.getRow(); int col=a.getCol(); int i=0;
    double *values=new double[row*col];
    //check that the two matrices has the same dimension
    if(a.getRow()==b.getRow() && a.getCol()==b.getCol()){
       
        for(int r=0;r<row;r++){
            for(int c=0;c<col;c++){
                values[i]=a.get(r,c)+b.get(r,c);
                i++;
            }
        }
                  
    }
    else
    {
      // give an error
      throw Exception("Dimensions does not match");
    }
    Matrix c(row,col);
    c.setValue(values);
    return c;
}

// subtract a double value (elements wise)
  Matrix Matrix::subtract(Matrix a, double v)
  {
    return add(a,-v);
  }

 Matrix Matrix::subtract(Matrix a, Matrix b){
    int row=a.getRow(); int col=a.getCol(); int i=0;
    double *values=new double[row*col];
    //check that the two matrices has the same dimension
    if(a.getRow()==b.getRow() && a.getCol()==b.getCol()){
       
        for(int r=0;r<row;r++){
            for(int c=0;c<col;c++){
                values[i]=a.get(r,c)-b.get(r,c);
                i++;
            }
        }
                  
    }
    else{cout<<"nonconformant arguments"<<endl;}
    Matrix c(row,col);
    c.setValue(values);
    return c;
}

 // multiply by double value 
  Matrix Matrix::Multiply(Matrix a,double v)
  {
    for (int r = 0; r < a.nRow; r++)
    {
      for (int c = 0; c < a.nCol; c++)
      {
        a.pData[r][c] *= v;
      }
    }
     return *this;
  }

  // multiply matrix by matrix
  Matrix Matrix::Multiply(Matrix a ,Matrix b){
      double values[a.nRow*b.nCol];  int i=0;
      // check if the dimensions match
     // cout<<a.nCol<<"--"<<b.nRow<<endl;
    if (a.nCol == b.nRow)
    {
      Matrix res(a.nRow, b.nCol);

      for (int r = 0; r < a.nRow; r++)
      {
        for (int c_res = 0; c_res < b.nCol; c_res++)
        {
          for (int c = 0; c < a.nCol; c++)
          {
            res.pData[r][c_res] += a.pData[r][c] * b.pData[c][c_res];
        //  values[i]+= a.pData[r][c] * b.pData[c][c_res];  
          }
        } 
        i++;
      }
     // res.setValue(values);
      return res;
    }
    else
    {
      // give an error
      throw Exception("Dimensions does not match");
    }
  }

  // divide by double value 
  Matrix Matrix:: Divide( double v)
  {
     return Multiply(*this,1/v);
  }

  Matrix Matrix::transpose(Matrix A) 
    {
        Matrix c(A.nRow,A.nCol);
        if (A.nRow == A.nCol)
        {
            for (int i=0;i<nRow;i++)
            {
                for (int j=0;j<nCol;j++)
                {
                    c.pData[i][j]=A.pData[j][i];
                }
            }
        }
        else
          { cout<< "The matrix must be a square matrix";}
            return c;
    }

    // swap two values
void Matrix::Swap(double& a, double& b)
{
  double temp = a;
  a = b;
  b = temp;
}

/**
 * returns a diagonal matrix with size n x n with ones at the diagonal
 * @param  v a vector
 * @return a diagonal matrix with ones on the diagonal
 */
Matrix Matrix::Diag(const int n)
{
  Matrix res = Matrix(n, n);
  for (int i = 1; i <= n; i++)
  {
    res(i, i) = 1;
  }
  return res;
}

/**
 * returns a diagonal matrix
 * @param  v a vector
 * @return a diagonal matrix with the given vector v on the diagonal
 */
Matrix Matrix::Diag( Matrix& v)
{
  Matrix res;
  if (v.getCol() == 1)
  {
    // the given matrix is a vector n x 1
    int rows = v.getRow();
    res = Matrix(rows, rows);

    // copy the values of the vector to the matrix
    for (int r=1; r <= rows; r++)
    {
      res(r, r) = v.get(r, 1);
    }
  }
  else if (v.getRow() == 1)
  {
    // the given matrix is a vector 1 x n
    int cols = v.getCol();
    res = Matrix(cols, cols);

    // copy the values of the vector to the matrix
    for (int c=1; c <= cols; c++)
    {
      res(c, c) = v.get(1, c);
    }
  }
  else
  {
    throw Exception("Parameter for diag must be a vector");
  }
  return res;
}

/**
   * returns the minor from the given matrix where
   * the selected row and column are removed
   */
  Matrix Matrix:: Minor(const int row, const int col) 
  {
    Matrix res;
    if (row > 0 && row <= nRow && col > 0 && col <= nCol)
    {
      res = Matrix(nRow - 1, nCol - 1);

      // copy the content of the matrix to the minor, except the selected
      for (int r = 1; r <= (nRow - (row >= nRow)); r++)
      {
        for (int c = 1; c <= (nCol - (col >= nCol)); c++)
        {
          res(r - (r > row), c - (c > col)) = pData[r-1][c-1];
        }
      }
    }
    else
    {
      throw Exception("Index for minor out of range");
    }

    return res;
  }


/*
 * returns the determinant of Matrix a
 */
double Matrix::Det( Matrix& a)
{
  double d = 0;    // value of the determinant
  int rows = a.getRow();
  int cols = a.getRow();

  if (rows == cols)
  {
    // this is a square matrix
    if (rows == 1)
    {
      // this is a 1 x 1 matrix
      d = a.get(1, 1);
    }
    else if (rows == 2)
    {
      // this is a 2 x 2 matrix
      // the determinant of [a11,a12;a21,a22] is det = a11*a22-a21*a12
      d = a.get(1, 1) * a.get(2, 2) - a.get(2, 1) * a.get(1, 2);
    }
    else
    {
      // this is a matrix of 3 x 3 or larger
      for (int c = 1; c <= cols; c++)
      {
        Matrix M = a.Minor(1, c);
        //d += pow(-1, 1+c) * a(1, c) * Det(M);
        d += (c%2 + c%2 - 1) * a.get(1, c) * Det(M); // faster than with pow()
      }
    }
  }
  else
  {
    throw Exception("Matrix must be square");
  }
  return d;
}
/*
// swap two values
void Swap(double& a, double& b)
{
  double temp = a;
  a = b;
  b = temp;
}
*/

    /*
 * returns the inverse of Matrix a
 */
Matrix Matrix::Inv( Matrix& a)
{
  Matrix res;
  double d = 0;    // value of the determinant
  int rows = a.getRow();
  int cols = a.getRow();

  d = Det(a);
  if (rows == cols && d != 0)
  {
    // this is a square matrix
    if (rows == 1)
    {
      // this is a 1 x 1 matrix
      res = Matrix(rows, cols);
      res(1, 1) = 1 / a.get(1, 1);
    }
    else if (rows == 2)
    {
      // this is a 2 x 2 matrix
      res = Matrix(rows, cols);
      res(1, 1) = a.get(2, 2);
      res(1, 2) = -a.get(1, 2);
      res(2, 1) = -a.get(2, 1);
      res(2, 2) = a.get(1, 1);
      //res = (1/d) * res;
      res=Multiply(res,(1/d));
    }
    else
    {
      // this is a matrix of 3 x 3 or larger
      // calculate inverse using gauss-jordan elimination
      //   http://mathworld.wolfram.com/MatrixInverse.html
      //   http://math.uww.edu/~mcfarlat/inverse.htm
      res = Diag(rows);   // a diagonal matrix with ones at the diagonal
      Matrix ai = a;    // make a copy of Matrix a

      for (int c = 1; c <= cols; c++)
      {
        // element (c, c) should be non zero. if not, swap content
        // of lower rows
        int r;
        for (r = c; r <= rows && ai(r, c) == 0; r++)
        {
        }
        if (r != c)
        {
          // swap rows
          for (int s = 1; s <= cols; s++)
          {
            Swap(ai(c, s), ai(r, s));
            Swap(res(c, s), res(r, s));
          }
        }

        // eliminate non-zero values on the other rows at column c
        for (int r = 1; r <= rows; r++)
        {
          if(r != c)
          {
            // eleminate value at column c and row r
            if (ai(r, c) != 0)
            {
              double f = - ai(r, c) / ai(c, c);

              // add (f * row c) to row r to eleminate the value
              // at column c
              for (int s = 1; s <= cols; s++)
              {
                ai(r, s) += f * ai(c, s);
                res(r, s) += f * res(c, s);
              }
            }
          }
          else
          {
            // make value at (c, c) one,
            // divide each value on row r with the value at ai(c,c)
            double f = ai(c, c);
            for (int s = 1; s <= cols; s++)
            {
              ai(r, s) /= f;
              res(r, s) /= f;
            }
          }
        }
      }
    }
  }
  else
  {
    if (rows == cols)
    {
      throw Exception("Matrix must be square");
    }
    else
    {
      throw Exception("Determinant of matrix is zero");
    }
  }
  return res;
}

  // division of Matrix with Matrix
  Matrix Matrix::Divide ( Matrix a, Matrix b)
  {
    // check if the dimensions match: must be square and equal sizes
    if (a.nRow == a.nCol && a.nRow == a.nCol && b.nRow == b.nCol)

    {
      Matrix res(a.nRow, a.nCol);
     
     // res = a * Inv(b);
     res=Multiply(a,Inv(b));

      return res;
    }
    else
    {
      // give an error
      throw Exception("Dimensions does not match");
    }

    // return an empty matrix (this never happens but just for safety)
    return Matrix();
  } 

  //*******************************************************************************************
  Matrix Matrix::getCofactor(int row,int column)   //get the cofactor of matrix NXN
    {
        if((nRow<1 &&nCol <1))
            throw "Invalid Matrix Dimension";
         Matrix subMat (nRow-1,nCol-1);

         for (int iR=0;iR<subMat.nRow;iR++)
         {
             for (int iC=0;iC<subMat.nCol;iC++)
             {
                 int sR=(iR<row)?iR:iR+1;
                 int sC=(iC<column)?iC:iC+1;
                 subMat.pData[iR][iC]=pData[sR][sC];

             }
         }
         return subMat;
    }

    double Matrix::matDeterminant ()
    {
        if (nRow!=nCol)
            throw "The matrix must be a square matrix";
        if (nRow ==1 && nCol==1)
            return pData[0][0];
        else if (nRow ==2 && nCol == 2)
            return pData[0][0]*pData[1][1]-pData[1][0]*pData[0][1];
        else
        {
            double det=1,temp,temp1;
            int r=0;
            while (r<nRow)
            {
                temp=pData[r][r];
                for (int ir=r+1;ir<nRow;ir++)
                {
                    for (int ic=0;ic<nCol;ic++)
                    {
                        pData[ir][ic]=pData[ir][ic]-(pData[ir][r]/temp)*pData[r][ic];
                    }
                }
                r++;
            }
            for (int i=0;i<nRow;i++)
                det*=pData[i][i];
            return det;
        }
    }
    void Matrix::matProduct(double Const) //Multiply each number in the matrix with Constant
    {
        for (int i=0;i<nRow;i++)
        {
            for (int j=0;j<nCol;j++)
            {
                pData[i][j]*=Const;
            }
        }
    }
    void Matrix::minorMat (Matrix &A)  // get matrix of minors
    {
        double sign =1;
        if (nRow==A.nRow && nCol==A.nCol)
        {
            for (int i=0;i<nRow;i++)
            {
                for (int j=0;j<nRow;j++)
                {
                    pData[i][j]=A.getCofactor(i,j).matDeterminant();
                    pData[i][j]*=sign;
                    sign*=-1;
                }
              sign*=-1;
            }
        }
    }
    void Matrix::matTranspose(Matrix &A) //get the transpose of matrix
    {
        if (A.nRow == A.nCol)
        {
            for (int i=0;i<nRow;i++)
            {
                for (int j=0;j<nCol;j++)
                {
                    pData[i][j]=A.pData[j][i];
                }
            }
        }
        else
            "The matrix must be a square matrix";
    }

    bool Matrix :: isZeros()
    {
        int temp=0;
        for (int ir=0;ir<nRow;ir++)
        {
            for (int ic=0;ic<nCol;ic++)
            {
                if (pData[ir][ic] == 0)
                {
                    temp++;
                }
            }
        }
        if (temp == nRow * nCol)
            return true;
        else
            return false;
    }


        void Matrix :: eye ()
    {
        for (int i=0;i<nRow;i++)
        {
            for (int j=0;j<nCol;j++)
            {
                if (i==j)
                    pData[i][j]=1;
                else
                    pData[i][j]=0;
            }
        }
    }


   void Matrix :: inverseMat (Matrix A)
    {
        eye();
        double temp,temp1,temp2,temp3,temp4;
        int r=0;
        while (r<nRow)
        {
        temp=A.pData[r][r];
        if (temp == 0 )
        {
            for (int ir=r;ir<nRow;ir++)
            {
            if (r == nRow-1)
            	break;
            temp1=A.pData[r+1][r];
            for (int ic=0;ic<nCol;ic++)
            {
            	if (temp1 == 0) break;
            	temp3=A.pData[r][ic];
            	temp4=pData[r][ic];
                A.pData[ir][ic]=A.pData[ir+1][ic]/temp1;
                pData[ir][ic]=pData[ir+1][ic]/temp1;
                A.pData[ir+1][ic]=temp3;
                pData[ir+1][ic]=temp4;
                temp2=1;
            }
            if (temp2 ==1 ) break;
            }
        }
        else 
        {
        for (int c=0;c<nCol;c++)
        {
        A.pData[r][c]/=temp;
        pData[r][c]/=temp;
        temp2=A.pData[r][c];
        temp3=pData[r][c];
        }
    }

        if (r==0)
        {
           for (int ir=r+1;ir<nRow;ir++)
        {
            temp1=A.pData[ir][r];
            for (int ic=0;ic<nCol;ic++)
            {
                A.pData[ir][ic]-=temp1*A.pData[r][ic];
                pData[ir][ic]-=temp1*pData[r][ic];
                temp2=A.pData[ir][ic];
                temp3=pData[ir][ic];
            }
        }
        }
        else if (r==nRow-1)
        {
            for (int ir=r-1;ir>=0;ir--)
            {
                temp1=A.pData[ir][r];
                for (int ic=0;ic<nCol;ic++)
                {
                A.pData[ir][ic]-=temp1*A.pData[r][ic] ;
                pData[ir][ic]-=temp1*pData[r][ic] ;
                temp2=A.pData[ir][ic];
                temp3=pData[ir][ic];
                }
            }
        }
        else
        {
             for (int ir=r+1;ir<nRow;ir++)
        {
            temp1=A.pData[ir][r];
            for (int ic=0;ic<nCol;ic++)
            {
                A.pData[ir][ic]-=temp1*A.pData[r][ic] ;
                pData[ir][ic]-=temp1*pData[r][ic];
                temp2=A.pData[ir][ic];
                temp3=pData[ir][ic];
            }
        }

          for (int ir=r-1;ir>=0;ir--)
            {
                temp1=A.pData[ir][r];
                for (int ic=0;ic<nCol;ic++)
                {
                A.pData[ir][ic]-=temp1*A.pData[r][ic];
                pData[ir][ic]-=temp1*pData[r][ic] ;
                temp2=A.pData[ir][ic];
                temp3=pData[ir][ic];
                }
            }

        }

        r++;
        }
    }

void Matrix::multiply (Matrix &A) // Multiply Two matrices
{
    if (nCol != A.nRow)
        throw ("Invalid Matrix Dimension");
    Matrix B(nRow,A.nCol);
    for (int iR=0;iR<B.nRow;iR++)
    {
        for (int iC=0;iC<B.nCol;iC++)
        {
            B.pData[iR][iC]=0;
            for (int k=0;k<A.nCol;k++)
                B.pData[iR][iC]+=pData[iR][k]*A.pData[k][iC];
        }
    }
    this->Copy(B);
}
    void Matrix::Copy(Matrix& A)
    {
        if ((nRow != A.nRow) || (nCol != A.nCol))
            throw "the Matrices must have the same dimension";

            for (int i=0;i<nRow;i++)
            {
                for (int j=0;j<nCol;j++)
                    pData[i][j]=A.pData[i][j];
            }
    }
    /*
   
    Matrix Matrix::operator / (Matrix & A)
    {
       
        Matrix B (A.nRow,A.nCol);
        Matrix C (nRow,nCol);
        C.Copy(*this);
        B.inverseMat(A);
        C.multiply(B);
       
        return C;

    } */


     void Matrix::N_A_N ()   //put not a number a value in case of divide by a singular matrix
    {
        for (int i=0;i<nRow;i++)
        {
            for (int j=0;j<nCol;j++)
              pData[i][j]=nan(" ");
              
        }
    }    


Matrix Matrix::operator / (Matrix &A)
    {
        Matrix B (A.nRow,A.nCol);
        B.inverseMat(A);
        Matrix C (nRow,nCol);
       if (A.matDeterminant() == 0)
       {
           C.N_A_N();
           return C;
       }
       else
       {

        C.Copy(*this);
        C.multiply(B);

        return C;
        }
    }

    //Divide element by element

    Matrix Matrix::elementDivision (Matrix &A)
    {
        if (nRow != A.nRow && nCol!= A.nCol)
            throw Exception("Invalid Matrix Dimension");

            Matrix B(nRow,nCol);
            for (int r=0;r<nRow;r++)
            {
                for (int c=0;c<nCol;c++)
                {
                    B.pData[r][c]=pData[r][c]/A.pData[r][c];
                }
            }
            return B;
    }

    Matrix Matrix::elementDivision (double A)
    {
       

            Matrix B(nRow,nCol);
            for (int r=0;r<nRow;r++)
            {
                for (int c=0;c<nCol;c++)
                {
                    B.pData[r][c]=A/pData[r][c];
                }
            }
            return B;
    }

    
   
  //*******************************************************************************************

 Matrix Matrix::operator+ ( double b)
  {
  return Matrix::add(*this,b);
  }

  Matrix Matrix::operator +(Matrix a){
    return Matrix::add(*this,a);
}

  Matrix Matrix:: operator -(Matrix a){
    Matrix C=Matrix::subtract(*this,a);
    return C;
}

 Matrix Matrix::operator -(double v){
    Matrix C=Matrix::subtract(*this,v);
    return C;
}
 Matrix Matrix::operator =(Matrix a){
    Matrix t;
     t.nRow = a.nRow;
    t.nCol = a.nCol;
    t.pData = new double*[a.nRow];
    for (int r = 0; r < a.nRow; r++)
    {
      t.pData[r] = new double[a.nCol];

      // copy the values from the matrix a
      for (int c = 0; c < a.nCol; c++)
      {
        t.pData[r][c] = a.pData[r][c];
      }
    }
    return t;
}
 Matrix Matrix:: Transpose(Matrix A) //get the transpose of matrix
    {
        Matrix c(A.nRow,A.nCol);
        if (A.nRow == A.nCol)
        {
            for (int i=0;i<nRow;i++)
            {
                for (int j=0;j<nCol;j++)
                {
                    c.pData[i][j]=A.pData[j][i];
                }
            }
        }
        else
            "The matrix must be a square matrix";
            return c;
    }


// operator multiplication
  Matrix Matrix::operator* ( Matrix b)
  {
    return Multiply(*this, b);
  }

  

  // multiplication of Matrix with double
  Matrix Matrix::operator* ( double b)
  {
    
    return Multiply(*this,b);
  }
 /* Matrix operator/(Matrix b){
      return Divide(*this,b);
  } */

  Matrix Matrix::sin(Matrix m){
	 Matrix temp(m.nRow,m.nCol);
	 for(int i=0; i<m.nRow; i++){
			 for(int j=0; j<m.nCol; j++){
				  temp.pData[i][j]=std::sin(m.pData[i][j]);
			 }
	 }
	 return temp;
}

  Matrix Matrix::cos(Matrix m){
	 Matrix temp(m.nRow,m.nCol);
	 for(int i=0; i<m.nRow; i++){
			 for(int j=0; j<m.nCol; j++){
				  temp.pData[i][j]=std::cos(m.pData[i][j]);
			 }
	 }
	 return temp;
}

  Matrix Matrix::tan(Matrix m){
	 Matrix temp(m.nRow,m.nCol);
	 for(int i=0; i<m.nRow; i++){
			 for(int j=0; j<m.nCol; j++){
				  temp.pData[i][j]=std::tan(m.pData[i][j]);
			 }
	 }
	 return temp;
}
