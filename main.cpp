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
using namespace std;
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
					result = op2/op4;
					matMap.insert(pair<string,Matrix>(randomarray[counterra],result));
					s.push(randomarray[counterra]);
					i++;
					counterra++;
					continue;
				}
				if(flag1==0&&flag2==1&&flag3==0&&flag4==0)
				{
					result = op3 / op2 ;
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
void operation(string input )

{
	l1:
	string randommatrix[]={"AA","BB","CC","GG"};
	int foundeq=input.find("=");
	int counterrandom=0;
	input=trim(input);
	 size_t sa= input.find("sqrt(");
        static map<string, Matrix> matMap; 
		static map<string,Matrix>::iterator it;
		static map<string,float> numbermap;
		static map<string,float>::iterator it2;
		bool is =isAlphabetic(input,foundeq);
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
           cout<<name<<'='<<endl;
       matMap.at(name).printMatrix();
      }
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
			matMap.at(name).printMatrix();
			else if(it2!=numbermap.end())
				cout<<name<<" ="<<endl<<numbermap.at(name);
		}
		 if(sa<5000)
		 {
			 int sa2= sa+5;
			 matrix1=input.substr(sa2,1);
			 int sa3=input.find(")",sa2);
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
			else
				throw("no such matrix ");
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
		   cout<<label<<" ="<<endl;
		   resultsaaq.printMatrix();
		   //cout<<resultts<<endl;
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
		   cout<<label<<" ="<<endl;
		   cout<<resultts<<endl;
	   }
     

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
        string s;
    //create map for matrix
       // map<string, Matrix> matMap;       

    if(argc>1)
    {
        string input;   int c=0;   

    ifstream inFile;
    inFile.open(argv[1]);
    if (!inFile) {
    cout << "Unable to open file datafile.txt";
   }
   while ( inFile>>s && c<2) {
       if(s.find("]")<100){ remove(s.c_str()); input=input+s;  operation(input); input=""; c++;  } //cout<<input<<endl;
    
       else{ remove(s.c_str()); input=input+s+" ";  }
}

while ( getline (inFile,input)) {

// cout<<input<<endl;
      operation(input);

}

    }
 /*   
    
 string s="B = [1.2 2.3 3.2;[1.3 2.4 3.1;4.6 1.3 5.1]]";

string t="[2.2 7.3;4.8 2.4;3.6 9.1;8.7 6.1]";

Matrix A(s);
A.printMatrix();
Matrix B(t);
B.printMatrix();
Matrix C(3,2);
C.horzcat(A,B);
C.printMatrix();

cout<<A.toString()<<endl;

*/

    return 0;
}
