#include<iostream>
#include"Matrix.h"
//#include   <ctype.h>
//#include"stdlib.h"
#include <stdio.h>
#include"string.h"
#include <map>
#include<string>
#include<math.h>
#include<stack>
#include <string>
#include <algorithm> 
//#include<sstream>
//#include <cctype>
//#include <locale>
#define PI 3.14159265
using namespace std;
void Matrix::copy(Matrix& m)
{
this->nRow = m.nRow;
this->nCol = m.nCol;
if((nRow*nCol)==0)
{pData=NULL; return;}
pData = new double*[nRow];
for(int iR=0;iR<nRow;iR++)
{pData[iR] = new double[nCol];
for(int iC=0;iC<nCol;iC++)
{pData[iR][iC] = m.pData[iR][iC];}}}
bool isAlphabetic(string check,int i)
{
	bool verify = true;
	for ( i ; i < check.length(); i++)
	{
		if (check[i] >= 'a' && check[i] <= 'z' || check[i] >= 'A' && check[i] <= 'Z')
		{verify = true;break;}
		else
		{
			verify = false;
			
		}
	}
	return verify;
}
int getWeight(char ch) {
   switch (ch) {
   case '^': return 3;
   case '/':
      case '*': return 2;
      case '+':
      case '-': return 1;
      default : return 0;
   }
}
void infix2postfix(string infix,string  &postfix, int size) {
   stack<char> s;
   int weight;
   int i = 0;
   int k = 0;
   char ch;
  for(int ns=0;ns<size;ns++)
   {
	   ns=infix.find(' ');
	   if(ns !=-1)
	   {
		   infix.erase(ns,1);
	   }
	   else
		   break;
   }
  size=infix.size();   
   while (i < size) {
      ch = infix[i];
      if (ch == '(') {
         s.push(ch);
         i++;
         continue;
      }
      if (ch == ')') {
         while (!s.empty() && s.top() != '(') {
            postfix[k++] = s.top();
            s.pop();
			postfix[k++]=' ';
         }
         if (!s.empty()) {
            s.pop();
         }
         i++;
         continue;
      }
      weight = getWeight(ch);
      if (weight == 0) {
		  if(i==0)
		  {
			   postfix[k++] = ch;
			 if( infix[i+1] == '-' || infix[i+1]=='*' || infix[i+1]=='/' || infix[i+1]=='+' || infix[i+1]=='^' || infix[i+1]==')')
			 {postfix[k++] = ' ';}
		  }
		  else
		  {
         if(infix[i-1]=='-' || infix[i-1]=='*' || infix[i-1]=='/' || infix[i-1] =='+' || infix[i-1]=='^'/*&& infix[i+1] == '-' && infix[i+1]=='*' && infix[i+1]=='/' && infix[i+1]=='+' && infix[i+1]=='^'*/)
		  {
			  postfix[k++] = ch;
			  if(infix[i+1] == ')' || infix[i+1] == '-' || infix[i+1]=='*' || infix[i+1]=='/' || infix[i+1]=='+' || infix[i+1]=='^'||infix[i+1]=='(')
				  postfix[k++]=' ';
		 }
		 else
		 {
			 postfix[k++] = ch;
			if( infix[i+1] == '-' || infix[i+1]=='*' || infix[i+1]=='/' || infix[i+1]=='+' || infix[i+1]=='^' || infix[i+1]==')'||infix[i+1]=='(')
			 {postfix[k++] = ' ';}
		 }
		  }
      }
      else {
         if (s.empty()) {
            s.push(ch);
         }
         else {
         
            while (!s.empty() && s.top() != '(' &&
                  weight <= getWeight(s.top())) {
               postfix[k++] = s.top();
               s.pop();
			   postfix[k++] = ' ';
            }
            s.push(ch);
         }
      }
      i++;
   } 
   if(postfix[k-1]!=' ')
   {postfix[k++] =' ';}
   while (!s.empty()) {
      postfix[k++] = s.top();
      s.pop();
	  if(s.size()!=0)
	  postfix[k++] =' ';
   }
   postfix[k] = 0;   
}
  float parsing(string postfix)
  {
	   int osa=postfix.find('\0');
   postfix.erase(osa);
   if(postfix[postfix.size()]==' ')
	   postfix.erase(postfix.size());
	  //postfix=infix2postfix(postfix);
	  stack<string> s;
	  string st;
	  int k=0;
	  int i =0;
	  int i2=0;
	  int found=0;
	  float op1,op2;
	  float result;
	  int ay1=0;
	  for(int man=0;man<postfix.size();man++)
	  {
		  ay1=postfix.find(" ",ay1+1);
		  if(ay1 != -1)
			  i2++;
		  else
			  break;
	  }
	  if(postfix[postfix.size()-1]==' ')
	  {
		  i2--;
	  }
	  while (i<i2+1)
	  {
		  found=postfix.find(" ",found+1);
		  st=postfix.substr(k,found-k);
		  k=found+1;
		  if(st == "/" || st == "+" || st == "-" || st == "*" || st == "^" )
		  {
			op2=stof(s.top());
			s.pop();
			 op1=stof(s.top());
			s.pop();
			if(st=="/")
			{	
				if(op2==0)throw ("Devided by zero");
				result=	op1/op2;
				s.push(to_string(result));
				i++;
				continue;
			}
			if(st=="+")
			{	
				result=	op1+op2;
				s.push(to_string(result));
				i++;
				continue;
			}
			if(st=="-")
			{	
				result=	op1-op2;
				s.push(to_string(result));
				i++;
				continue;
			}
			if(st=="*")
			{	
				result=	op1*op2;
				s.push(to_string(result));
				i++;
				continue;
			}
			if(st=="^")
			{	
				result=	pow(op1,op2);
				s.push(to_string(result));
				i++;
				continue;
			}
	  }
		  else
		  {
			  s.push(st);
		  }
		 i++;
	  }
	   result=stof(s.top());
		  s.pop();
		  return result;
  }
  Matrix parsing2(string postfix,map<string, Matrix>&matMap,map<string,float>&numbermap)
  {
	  string randomarray[6] = {"aA","bB","cC","dD","eE","fF"};
	int  counterra=0;
	  map<string,Matrix>::iterator it;
	  map<string,float>::iterator it2;
	   int osa=postfix.find('\0');
   postfix.erase(osa);
	  //postfix=infix2postfix(postfix);
	  stack<string> s;
	  string st;
	  int k=0;
	  int i =0;
	  int i2=0;
	  int found=0;
	  float op1,op2;
	  Matrix op3,op4;
	  Matrix result;
	  float result2;
	  int ay1=0;
	  for(int man=0;man<postfix.size();man++)
	  {
		  ay1=postfix.find(" ",ay1+1);
		  if(ay1 != -1)
			  i2++;
		  else
			  break;
	  }
	  int flag1=0,flag2=0,flag3=0,flag4=0;
	  if(postfix[postfix.size()-1]==' ')
	  {
		  i2--;
	  }
	  while (i<i2+1)
	  {
		  flag1=0;flag2=0;flag3=0;flag4=0;
		  found=postfix.find(" ",found+1);
		  st=postfix.substr(k,found-k);
		  //it=matMap.find(st);
		//  it2=numbermap.find(st);
		  k=found+1;
		  if(st == "/" || st == "+" || st == "-" || st == "*" || st == "^" )
		  {
			  it=matMap.find(s.top());
			  if(it!=matMap.end())
			  {
				  op4=matMap.at(s.top());
				  s.pop();
				  it=matMap.find(s.top());
				  flag4=1;
				 if(it!=matMap.end())
				 {
				op3=matMap.at(s.top());
				  s.pop();
				  flag3=1;
				 }
				 else 
				 {
					 op2=stof(s.top());
					 s.pop();
				 }
			  }
			  
			  else
			  {
			
			op2=stof(s.top());
			s.pop();
			it=matMap.find(s.top());
			if(it!=matMap.end())
			{
				op3=matMap.at(s.top());
				s.pop();
				flag2=1;
			}
			else
			{
			op1=stof(s.top());
			s.pop();
			}
			  }

			if(st=="/")
			{	
				if( flag1 == 0 &&flag2==0&&flag3==0&&flag4==0)
				{
					if(op2==0)throw("Devided By zero");
				result2 =	op1/op2;
				s.push(to_string(result2));
				i++;
				continue;
				}
				if(flag1==0&&flag2==0&&flag4==1&&flag3==1)
				{
					result = op3/op4;
					matMap.insert(pair<string,Matrix>(randomarray[counterra],result));
					s.push(randomarray[counterra]);
					i++;
					counterra++;
					continue;
				}
				if(flag1==0&&flag2==0&&flag3==0&&flag4==1)
				{
					result = op2 / op4;
					matMap.insert(pair<string,Matrix>(randomarray[counterra],result));
					s.push(randomarray[counterra]);
					i++;
					counterra++;
					continue;
				}
				if(flag1==0&&flag2==1&&flag3==0&&flag4==0)
				{
					result = op2 / op3 ;
					matMap.insert(pair<string,Matrix>(randomarray[counterra],result));
					s.push(randomarray[counterra]);
					i++;
					counterra++;
					continue;
				}
			}
			if(st=="+")
			{	
				if( flag1 == 0 &&flag2==0&&flag3==0&&flag4==0)
				{
				result2=	op1+op2;
				s.push(to_string(result2));
				i++;
				continue;
				}
				if(flag1==0&&flag2==0&&flag4==1&&flag3==1)
				{
					result = op3+op4;
					matMap.insert(pair<string,Matrix>(randomarray[counterra],result));
					s.push(randomarray[counterra]);
					i++;
					counterra++;
					continue;
				}
				if(flag1==0&&flag2==0&&flag3==0&&flag4==1)
				{
					result = op4 + op2;
					matMap.insert(pair<string,Matrix>(randomarray[counterra],result));
					s.push(randomarray[counterra]);
					i++;
					counterra++;
					continue;
				}
				if(flag1==0&&flag2==1&&flag3==0&&flag4==0)
				{
					result = op3 + op2 ;
					matMap.insert(pair<string,Matrix>(randomarray[counterra],result));
					s.push(randomarray[counterra]);
					i++;
					counterra++;
					continue;
				}
			}
			if(st=="-")
			{	
				if( flag1 == 0 &&flag2==0&&flag3==0&&flag4==0)
				{
				result2=	op1-op2;
				s.push(to_string(result2));
				i++;
				continue;
				}
				if(flag1==0&&flag2==0&&flag4==1&&flag3==1)
				{
					result = op3-op4;
					matMap.insert(pair<string,Matrix>(randomarray[counterra],result));
					s.push(randomarray[counterra]);
					i++;
					counterra++;
					continue;
				}
				if(flag1==0&&flag2==0&&flag3==0&&flag4==1)
				{
					result = op4 - op2;
					matMap.insert(pair<string,Matrix>(randomarray[counterra],result));
					s.push(randomarray[counterra]);
					i++;
					counterra++;
					continue;
				}
				if(flag1==0&&flag2==1&&flag3==0&&flag4==0)
				{
					result = op3 - op2 ;
					matMap.insert(pair<string,Matrix>(randomarray[counterra],result));
					s.push(randomarray[counterra]);
					i++;
					counterra++;
					continue;
				}
			}
			if(st=="*")
			{	
				if( flag1 == 0 &&flag2==0&&flag3==0&&flag4==0)
				{
				result2=	op1*op2;
				s.push(to_string(result2));
				i++;
				continue;
				}
				if(flag1==0&&flag2==0&&flag4==1&&flag3==1)
				{
					result = op3*op4;
					matMap.insert(pair<string,Matrix>(randomarray[counterra],result));
					s.push(randomarray[counterra]);
					i++;
					counterra++;
					continue;
				}
				if(flag1==0&&flag2==0&&flag3==0&&flag4==1)
				{
					result = op4 * op2;
					matMap.insert(pair<string,Matrix>(randomarray[counterra],result));
					s.push(randomarray[counterra]);
					i++;
					counterra++;
					continue;
				}
				if(flag1==0&&flag2==1&&flag3==0&&flag4==0)
				{
					result = op3 * op2 ;
					matMap.insert(pair<string,Matrix>(randomarray[counterra],result));
					s.push(randomarray[counterra]);
					i++;
					counterra++;
					continue;
				}
			}
			if(st=="^")
			{	
				if( flag1 == 0 &&flag2==0&&flag3==0&&flag4==0)
				{
				result2=	pow(op1,op2);
				s.push(to_string(result2));
				i++;
				continue;
				}
			}
			  }
		  else
		  {
			  s.push(st);
		  }
		 i++;
	  }
	  // result2=stof(s.top());
		//  s.pop();
	  result=matMap.at(s.top());
	  for(;counterra>=0;counterra--)
	  {
		  it=matMap.find(randomarray[counterra]);
		  if(it!=matMap.end())
		  matMap.erase(it);
	  }
	  return result ;
  }

class Exception
{
private:
	double r;
	double i;
public:
  const char* msg;
  Exception(const char* arg)
   : msg(arg)
  {
  }
};

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
     /*~Matrix()
    {
        for (int i=0;i<nCol;i++)
        {
            delete pData[i];
        }
        delete pData;
    } */ 

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
      double values[16];  int i=0;
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
        double det=0,m=1;
        for (int iC=0;iC<nCol;iC++)
        {
            det+=m * (pData[0][iC]) * getCofactor(0,iC).matDeterminant ();
            m*=-1;
        }
        return det;

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
    void Matrix::inverseMat (Matrix &A) //Get inverse of the matrix
    {
        double Const =A.matDeterminant();
        Matrix B(A.nRow,A.nCol);
        if (Const !=0)
        {
            Const=1.0/Const;
            B.minorMat(A);
            this->matTranspose(B);
            this->matProduct(Const);
        }
        else
            throw "ERROR: singular Matrix";
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
              pData[i][j]=0;//nan(" ");
              
        }
    }    


Matrix Matrix::operator / (Matrix & A)
    {
        Matrix B (A.nRow,A.nCol);
        Matrix C (nRow,nCol);
       if (A.matDeterminant()==0)
       {
           C.N_A_N();
           return C;
       }
       else
       {

        C.Copy(*this);
        B.inverseMat(A);
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
	 copy(a);
    return* this;
}//test2
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

  std::string trim_left(const std::string& str)
{
  const std::string pattern = " \f\n\r\t\v";
  return str.substr(str.find_first_not_of(pattern));
}

//
//Right trim
//
std::string trim_right(const std::string& str)
{
  const std::string pattern = " \f\n\r\t\v";
  return str.substr(0,str.find_last_not_of(pattern) + 1);
}

//
//Left and Right trim
//
std::string trim(const std::string& str)
{
  return trim_left(trim_right(str));
}

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



void operation(string input )


{
	int flaggq=0;
	l1:
	string randommatrix[]={"AA","BB","CC","GG","DD","EE","FF","HH","II","JJ","KK","LL","MM"};
	int foundeq=input.find("=");
	int counterrandom=0;
	input=trim(input);
	 size_t sa= input.find("sqrt(");
	 size_t sina = input.find("sin(");
	 size_t cosa = input.find("cos(");
	 size_t tana = input.find("tan(");
        static map<string, Matrix> matMap; 
		static map<string,Matrix>::iterator it;
		static map<string,float> numbermap;
		static map<string,float>::iterator it2;
		bool is =isAlphabetic(input,foundeq);
		if(input[input.size()-1]==';')	
		{
				flaggq=1;
				input.erase(input.size()-1);
		}
		if(input.find('[')!=-1 || input.find(']')!=-1)
		{
            //count number of rows $ col
        int numRow=1,numCol=1;
        for(int i=input.find('[');i<((input.find(';')<input.size()?input.find(';'):input.find(']')));i++){if(input[i]==' ' && input[i-1]!='[' && input[i+1]!=';')numCol++;}
        for(int i=input.find('[');i<input.find(']')-1;i++){if(input[i]==';' && input[i+1]!=']' && input[i+2]!=']' && input[i+3]!=']' )numRow++;}
        double values[2000]; int valuesIndex=0; 
         //replac space with commas
        for(int i=input.find('[')+1;i<input.find(']')+1;i++){
            if(input[i]==' ' || input[i]==';' || input[i]==']'  || input[i]=='[')
            {
                if(input[i-1]==','){continue;}
                else {input[i]=',';}
                }
        }
		

     int start=input.find('[')+1; int end=input.find(","); string s;
      // cout<<input<<endl;
        while(end<=input.size()){
         s=input.substr(start,end-start);   //cout<<s<<"--";
         values[valuesIndex]=atof(s.c_str());  valuesIndex++;
         start=end+1;
         end=input.find(",",end+1);
        }
      //  cout<<endl;

         

		
        string name;
		input+=" ";
			 for(int ia=0;ia<input.size()+1;ia++)
		 {
			 if(input[ia+1]==' ')
			 {
				 name=input.substr(0,ia+1);
				 break;
			 }

		 }
	   it = matMap.find(name);
	   if(it != matMap.end())
	   {
		   matMap.erase(it);
	   }
       matMap.insert(pair<string,Matrix>(name,Matrix(numRow,numCol)));
       matMap.at(name).setValue(values);
      if( input[input.size()-2] !=';'){
		   if(!flaggq)
		   {
			   cout<<name<<'='<<endl;
			   matMap.at(name).printMatrix();
		   }}
         }

         else{

			 string name;
			 input+=" ";
			 for(int ia=0;ia<input.size()+1;ia++)
		 {
			 if(input[ia+1]==' '||input[ia+1]=='=')
			 {
				 name=input.substr(0,ia+1);
				 break;
			 }

		 }
         string matrix1,matrix2,secondeInput;
		 it =matMap.find(name);
		 it2 = numbermap.find(name);
		 if( input.size()<5)
		{
		
			if(it == matMap.end()&&it2==numbermap.end())
	   {
		  throw("The is no such var ") ;
	   }
			else if(it!=matMap.end())
			{if(!flaggq)matMap.at(name).printMatrix();}
			else if(it2!=numbermap.end())
			{if(!flaggq)cout<<name<<" ="<<endl<<numbermap.at(name)<<endl;}
		}
		 if(sa<5000)
		 {
			 int sa2= sa+5;
			  int sa3=input.find(")",sa2);
			 matrix1=trim(input.substr(sa2,sa3-sa2));
			 it = matMap.find(matrix1);
			if( it != matMap.end())
			{ int col=matMap.at(matrix1).getCol(),row=matMap.at(matrix1).getRow();
		Matrix bb(row,col);
		for(int i =0;i<row;i++)
		{
			for(int j=0;j<col;j++)
			{
				bb.pData[i][j]=sqrt(matMap.at(matrix1).pData[i][j]);
			}
		}
		 matMap.insert(pair<string,Matrix>(randommatrix[counterrandom],bb));
		// matMap.at(randommatrix[counterrandom]).printMatrix();
		 input.replace(sa,sa3-sa+1,randommatrix[counterrandom]);
		 counterrandom++;
		 goto l1;
			}
			else if(isAlphabetic(matrix1,0))
				throw("no such matrix ");
			else
			{
				float sqrtrt=sqrt(stof(matrix1));
				input.replace(sa,sa3-sa+1,to_string(sqrtrt));
				goto l1;
			}
	}
		 if(sina<5000)
		 {
			 int sa2= sina+4;
			  int sa3=input.find(")",sa2);
			 matrix1=trim(input.substr(sa2,sa3-sa2));
			 it = matMap.find(matrix1);
			if( it != matMap.end())
			{ int col=matMap.at(matrix1).getCol(),row=matMap.at(matrix1).getRow();
		Matrix bb(row,col);
		bb.sin(matMap.at(matrix1));
		 matMap.insert(pair<string,Matrix>(randommatrix[counterrandom],bb));
		// matMap.at(randommatrix[counterrandom]).printMatrix();
		 input.replace(sina,sa3-sina+1,randommatrix[counterrandom]);
		 counterrandom++;
		 goto l1;
			}
			else if(isAlphabetic(matrix1,0))
				throw("no such matrix ");
			else
			{
				float sinnum=stof(matrix1);
				sinnum=sin(sinnum);
				input.replace(sina,sa3-sina+1,to_string(sinnum));
				goto l1;
			}
	}
		 if(cosa<5000)
		 {
			 int sa2= cosa+4;
			  int sa3=input.find(")",sa2);
			 matrix1=trim(input.substr(sa2,sa3-sa2));
			 it = matMap.find(matrix1);
			if( it != matMap.end())
			{ int col=matMap.at(matrix1).getCol(),row=matMap.at(matrix1).getRow();
		Matrix bb(row,col);
		bb.cos(matMap.at(matrix1));
		 matMap.insert(pair<string,Matrix>(randommatrix[counterrandom],bb));
		// matMap.at(randommatrix[counterrandom]).printMatrix();
		 input.replace(cosa,sa3-cosa+1,randommatrix[counterrandom]);
		 counterrandom++;
		 goto l1;
			}
			else if(isAlphabetic(matrix1,0))
				throw("no such matrix ");
			else
			{
				float sinnum=stof(matrix1);
				sinnum=cos(sinnum);
				input.replace(cosa,sa3-cosa+1,to_string(sinnum));
				goto l1;
			}
	}
			 if(tana<5000)
		 {
			 int sa2= tana+4;
			  int sa3=input.find(")",sa2);
			 matrix1=trim(input.substr(sa2,sa3-sa2));
			 it = matMap.find(matrix1);
			if( it != matMap.end())
			{ int col=matMap.at(matrix1).getCol(),row=matMap.at(matrix1).getRow();
		Matrix bb(row,col);
		bb.tan(matMap.at(matrix1));
		 matMap.insert(pair<string,Matrix>(randommatrix[counterrandom],bb));
		// matMap.at(randommatrix[counterrandom]).printMatrix();
		 input.replace(tana,sa3-tana+1,randommatrix[counterrandom]);
		 counterrandom++;
		 goto l1;
			}
			else if(isAlphabetic(matrix1,0))
				throw("no such matrix ");
			else
			{
				float sinnum=stof(matrix1);
				sinnum=tan(sinnum);
				input.replace(tana,sa3-tana+1,to_string(sinnum));
				goto l1;
			}
	}
		 if(is&&input.size()>5)
	   {
		   string label;
		   int xaa=input.find("=");
		   for(int aac=0;aac<xaa+1;aac++)
		   {
			   if(input[aac+1]== ' ')
			   {
				   label=input.substr(0,aac+1);
				   break;
			   }
		   }
		   string postfix= new char [input.size()*4];
		   infix2postfix(input.substr(xaa+1,input.size()-xaa),postfix,input.size());
		  // float resultts=parsing(postfix);
		   Matrix resultsaaq=parsing2(postfix,matMap,numbermap);//test
		  // numbermap.insert(pair<string,float>(label,resultts));
		   matMap.insert(pair<string,Matrix>(label,resultsaaq));
		   if(!flaggq)
			   {cout<<label<<" ="<<endl;
		   resultsaaq.printMatrix();}
		   //cout<<resultts<<endl;
		   for(;counterrandom>=0;counterrandom--)
	  {
		  it=matMap.find(randommatrix[counterrandom]);
		  if(it!=matMap.end())
		  matMap.erase(it);
	  }
	   }
	   if(!is)
	   {
		   string label;
		   int xaa=input.find("=");
		   for(int aac=0;aac<xaa+1;aac++)
		   {
			   if(input[aac+1]== ' ')
			   {
				   label=input.substr(0,aac+1);
				   break;
			   }
		   }
		   string postfix= new char [input.size()*4];
		   infix2postfix(input.substr(xaa+1,input.size()-xaa),postfix,input.size());
		   float resultts=parsing(postfix);
		   //Matrix resultsaaq=parsing2(postfix,matMap,numbermap);//test
		   numbermap.insert(pair<string,float>(label,resultts));
		   if(!flaggq)
			   {cout<<label<<" ="<<endl;
		   cout<<resultts<<endl;
		   }}
     

      if(input[input.size()-1]=='\''&&is){
         

             for(int i=input.find('=')+1;i<input.length();i++){
                 if(input[i]==' '){continue;}
                 else{ matrix1=input.substr(i,1);   break;}            
      }
     // Matrix c=transpose(matMap.at(matrix1));
     Matrix c(matMap.at(matrix1).nRow,matMap.at(matrix1).nCol);
        if (matMap.at(matrix1).nRow == matMap.at(matrix1).nCol)
        {
            for (int i=0;i<matMap.at(matrix1).nRow;i++)
            {
                for (int j=0;j<matMap.at(matrix1).nCol;j++)
                {
                    c.pData[i][j]=matMap.at(matrix1).pData[j][i];
                }
            }
        }
        else
          { cout<< "The matrix must be a square matrix";}
      matMap.insert(pair<string,Matrix>(name,c ));
             matMap.at(name).printMatrix();


         }  
}
}

int main(int argc, char* argv[]){
  
       int x=0;
        string s,input;
    
while ( getline (cin,input)) {

	try
	{
      operation(input);
	}
	catch(char* error)
	{
		cout<<"Error: "<<error<<endl;
	}
}

    }
