#include<iostream>
#include"Matrix.h"
//#include"stdlib.h"
#include <stdio.h>
#include"string.h"
#include"map"
#include<string>
#include<fstream>
#include <algorithm> 
#include <stack>
#include <math.h>
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

string matrixnames [100];
int matrixnum=0;

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

//function to get the close of a bracket 
int endBracketPos(int openPos,string input)
{
    int closePos,open2Pos,temp=openPos;
    while (1)
    {
        closePos=input.find(']',temp+1);
        open2Pos=input.find('[',openPos+1);
        if (closePos<open2Pos || open2Pos==string ::npos)
            return closePos;
        else
        {
            temp=closePos;
            openPos=open2Pos;
        }
    }
}


int matIndex(string s)
{
  int index = s[0];
  if (index >= 97)
    index = index - 97;
  else
    index = index - 65;
  return index;
}
string strValues(string str,string s = "[",string e ="]")
{
  int start = str.find(s);
  int end = str.find(e);
  if (start != std::string::npos && end != std::string::npos)
  {
    return str.substr(start, end + 1);
  }
  return "empty";
}
Matrix matFun(string s)
{
  string str = strValues( s,  "(", ")");
  std::remove_if(str.begin(), str.end(),[](char c){return std::isspace(static_cast<unsigned char>(c));});
  if (s.find("zeros") != std::string::npos)
  {
    return Matrix::zeros((int)str[1] - 48, (int)str[3] - 48);
  }
  else if (s.find("ones") != std::string::npos)
  {
    return Matrix::ones((int)str[1] - 48, (int)str[3] - 48);
  }
  else if (s.find("eye") != std::string::npos)
  {
    return Matrix::eye((int)str[1] - 48, (int)str[3] - 48);
  }
  else if(s.find("rand") != std::string::npos)
  {
    return Matrix::randM((int)str[1] - 48, (int)str[3] - 48);
  }
}

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
            postfix+= s.top();
            s.pop();
      postfix+=' ';
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
         postfix+= ch;
       if( infix[i+1] == '-' || infix[i+1]=='*' || infix[i+1]=='/' || infix[i+1]=='+' || infix[i+1]=='^' || infix[i+1]==')')
       {postfix+= ' ';}
      }
      else
      {
         if(infix[i-1]=='-' || infix[i-1]=='*' || infix[i-1]=='/' || infix[i-1] =='+' || infix[i-1]=='^'/*&& infix[i+1] == '-' && infix[i+1]=='*' && infix[i+1]=='/' && infix[i+1]=='+' && infix[i+1]=='^'*/)
      {
        postfix+= ch;
        if(infix[i+1] == ')' || infix[i+1] == '-' || infix[i+1]=='*' || infix[i+1]=='/' || infix[i+1]=='+' || infix[i+1]=='^'||infix[i+1]=='(')
          postfix+=' ';
     }
     else
     {
       postfix+= ch;
      if( infix[i+1] == '-' || infix[i+1]=='*' || infix[i+1]=='/' || infix[i+1]=='+' || infix[i+1]=='^' || infix[i+1]==')'||infix[i+1]=='(')
       {postfix+= ' ';}
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
               postfix+= s.top();
               s.pop();
         postfix+= ' ';
            }
            s.push(ch);
         }
      }
      i++;
   }
   if(postfix[postfix.size()-1]!=' ')
   {postfix+=' ';}
   while (!s.empty()) {
      postfix+= s.top();
      s.pop();
    if(s.size()!=0)
    postfix+=' ';
   }
   //postfix[k] = 0;
}

  float parsing(string postfix)
  {
     //int osa=postfix.find('\0');
   //postfix.erase(osa);
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
        result= op1/op2;
        s.push(to_string(result));
        i++;
        continue;
      }
      if(st=="+")
      {
        result= op1+op2;
        s.push(to_string(result));
        i++;
        continue;
      }
      if(st=="-")
      {
        result= op1-op2;
        s.push(to_string(result));
        i++;
        continue;
      }
      if(st=="*")
      {
        result= op1*op2;
        s.push(to_string(result));
        i++;
        continue;
      }
      if(st=="^")
      {
        result= pow(op1,op2);
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
    // int osa=postfix.find('\0');
   //postfix.erase(osa);
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
          if(op2==0)throw Exception("Devided By zero");
        result2 = op1/op2;
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
          result = op4 / op2;
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
        result2=  op1+op2;
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
        result2=  op1-op2;
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
        result2=  op1*op2;
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
        result2=  pow(op1,op2);
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
        if (input.find('./'))
        {
          input.replace(input.find('./'),2,'');
     
        }
        if(input.find('.^'))
        {
          input.replace(input.find('.^'),2,'!');
        }

        static map<string, Matrix> matMap; 
        //cout<<input<<endl;

        int COUNT=0;
        string name=input.substr(0,1);
        int index=0,temp=input.find('[');
        int print=1;
        if(input[input.size()-1] ==';')
        {
          print=0;
          input.erase(input.size()-1,1);
        }

        //cout<<print<<endl;
        //cout<<input<<endl;

        while (input.find('[',index) != string ::npos)
        {
          if(input.find('[',index) != string ::npos)
            COUNT++;
          index=temp+1;
          temp=input.find('[',index);

        }
        if (input.size() == 1)
        {
          //cout<<"3ebada2"<<endl;
          name=input;
          cout<<name<<" ="<<endl;
          matMap.at(name).printMatrix();
          cout<<endl;
        }

       else if (COUNT >1) // for matrix within a matrix
        {
          //cout<<"3ebada"<<endl;
          int pos,endPos,temp;
          for(int i=0;i<matrixnum;i++)
            if(input.find(matrixnames[i]) != string::npos)
            {
              //cout<<i<<" "<<matrixnames[i]<<endl;
              pos=input.find(matrixnames[i]);
              input.erase(pos,matrixnames[i].size());
              int nR=matMap.at(matrixnames[i]).getRow();
              int nC=matMap.at(matrixnames[i]).getCol();
              string mat;
              mat=matMap.at(matrixnames[i]).toString();
              input.insert(pos,mat);
            }

          //cout<<input<<endl;

            //cout<<input<<endl;


if (input.find('\n')!=string::npos)
{
    int n=input.find('\n');
    input.erase(n,1);
    input.insert(n,";");
}

 pos=0;
int Count=0;
string mat1,mat2;

while(input.find('[',pos)!=string::npos)
{
    temp=input.find('[',pos);
    endPos=endBracketPos(temp,input);
    if ( endPos==input.size()-1 || (temp==input.size()-2 && input[input.size()-1]==';')  || (input[temp-1] == ';' && input[endPos+1]==';') || input[temp+1]=='[' ||input[endPos+1]==';')
    {
        pos=temp+1;
        continue;
    }
    else
    {
        Count++;
        pos=temp+1;
    }
}
//cout<<Count<<endl;
int StartPos[Count];
int EndPos[Count];
int num=0;
pos=0;

while(input.find('[',pos)!= string::npos)
{
    temp=input.find('[',pos);
    endPos=endBracketPos(temp,input);
    if ( endPos==input.size()-1 || (temp==input.size()-2 && input[input.size()-1]==';')  || (input[temp-1] == ';' && input[endPos+1]==';'))
    {
        pos=temp+1;
        continue;
    }
    else
    {
        StartPos[num]=temp;
        EndPos[num]=endPos;
        pos=temp+1;
        num++;
    }
}
mat1=input.substr(StartPos[0],EndPos[0]-StartPos[0]+1);
Matrix A(mat1);
//A.printMatrix();
mat2=input.substr(StartPos[1],EndPos[1]-StartPos[1]+1);
Matrix B(mat2);
//B.printMatrix();

Matrix C(A.getRow(),A.getCol()+B.getCol());
C.horzcat(A,B);
//C.printMatrix();
input.erase(StartPos[0],EndPos[1]-StartPos[0]+1);
input.insert(StartPos[0],C.toString());
//cout<<input<<endl;
pos=0;
while(input.find('[',pos)!=string::npos)
{
    temp=input.find('[',pos);
    endPos=endBracketPos(temp,input);
    if(input[temp-1]==';' || input[temp+1]=='[' || input[endPos+1]==';')
    {
        input.erase(temp,1);
        input.erase(endPos,1);
    }
    pos=temp+1;
}
input.erase(0,input.find('['));
//cout<<input<<endl;

Matrix D(input);

       matMap.insert(pair<string,Matrix>(name,Matrix(input)));

        matrixnames[matrixnum]=name;
 matrixnum++;
 if (print ==1)
 {
  //cout<<print<<endl;
       cout<<name<<" ="<<endl;
       matMap.at(name).printMatrix();
 }

        }



                  else if (input.find("eye") != string::npos || input.find("rand") != string::npos || input.find("zeros") != string::npos || input.find("ones") != string::npos)
         {
            //string input = "z = eye( 4 , 4 )"; 
  string str = strValues(input, "(", ")");
  std::remove_if(str.begin(), str.end(),[](char c){return std::isspace(static_cast<unsigned char>(c));});
  string name = input.substr(0, 1);
  matMap.insert(pair<string, Matrix>(name, matFun(input)));
      matrixnames[matrixnum]=name;
       matrixnum++;
if (print == 1)
{
  cout << name << '=' << endl;
  matMap.at(name).printMatrix();
  cout<<endl;
}

         }
  else if(input.size()<=500)
  {

        //  cout<<"3atef"<<endl;
            int flaggq=0;
  l1:
  string randommatrix[]={"AA","BB","CC","GG","DD","EE","FF","HH","II","JJ","KK","LL","MM"};
  int foundeq=input.find("=");
  int counterrandom=0;
  name=input.substr(0,1);
 //cout<<name<<endl;
  input=trim(input);
   size_t sa= input.find("sqrt(");
   size_t sina = input.find("sin(");
   size_t cosa = input.find("cos(");
   size_t tana = input.find("tan(");
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




    input+=" ";
       for(int ia=0;ia<input.size()+1;ia++)
     {
       if(input[ia+1]==' ')
       {
         name=input.substr(0,ia+1);
         break;
       }
       cout<<name<<endl;

     }
     it = matMap.find(name);
     if(it != matMap.end())
     {
       matMap.erase(it);
     }
       matMap.insert(pair<string,Matrix>(name,Matrix(numRow,numCol)));
               matrixnames[matrixnum]=name;
               //cout<<name<<"!it"<<endl;
 matrixnum++;
       matMap.at(name).setValue(values);
      if( input[input.size()-2] !=';'){
       if(!flaggq)
       {
         cout<<name<<'='<<endl;
         matMap.at(name).printMatrix();
       }}
         }

         else{

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
     matMap.insert(pair<string,Matrix>(name,bb));
             matrixnames[matrixnum]=name;
             //cout<<name<<"sa"<<endl;
 matrixnum++;
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
     matMap.insert(pair<string,Matrix>(name,bb));
    // cout<<name<<"sina"<<endl;
             matrixnames[matrixnum]=name;
 matrixnum++;
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
     matMap.insert(pair<string,Matrix>(name,bb));
     //cout<<name<<"cosa"<<endl;
             matrixnames[matrixnum]=name;
 matrixnum++;
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
     matMap.insert(pair<string,Matrix>(name,bb));
     //cout<<name<<"tana"<<endl;
             matrixnames[matrixnum]=name;
 matrixnum++;
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
      //cout<<"HEna"<<endl;
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
       string postfix;//= new char [input.size()*4];
       infix2postfix(input.substr(xaa+1,input.size()-xaa),postfix,input.substr(xaa+1,input.size()-xaa).size());
      // float resultts=parsing(postfix);
       Matrix resultsaaq=parsing2(postfix,matMap,numbermap);//test
      // numbermap.insert(pair<string,float>(label,resultts));
       it = matMap.find(label);
     if(it != matMap.end())
     {
       matMap.erase(it);
     }

       matMap.insert(pair<string,Matrix>(name,resultsaaq));
       matrixnames[matrixnum]=name;
       //cout<<name<<"is&&"<<endl;
       //cout<<label<<endl;
       matrixnum++;
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
       string postfix;//= new char [input.size()*4];
       infix2postfix(input.substr(xaa+1,input.size()-xaa),postfix,input.substr(xaa+1,input.size()-xaa).size());
       float resultts=parsing(postfix);
       //Matrix resultsaaq=parsing2(postfix,matMap,numbermap);//test
       it = matMap.find(label);
     if(it != matMap.end())
     {
       matMap.erase(it);
     }
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
      //cout<<name<<"5555"<<endl;
              matrixnames[matrixnum]=name;
 matrixnum++;
             matMap.at(name).printMatrix();


         }
}
         }

            else if(input[input.size()-1]==']' || input[input.size()-2]==']' )
        {
         // cout<<"Mahmoud"<<endl;
            //count number of rows $ col
        int numRow=1,numCol=1;
        for(int i=input.find('[');i<((input.find(';')<input.size()?input.find(';'):input.find(']')));i++){if(input[i]==' ' && input[i-1]!='[' && input[i+1]!=';')numCol++;}
        for(int i=input.find('[');i<input.find(']')-1;i++){if(input[i]==';' && input[i+1]!=']' && input[i+2]!=']' && input[i+3]!=']' )numRow++;}
        double values[2000]; int valuesIndex=0; 

      /*  if(input[input.size()-1]==';'){
            input=input.substr(0,input.find(']')+1);
        }*/
//cout<<input<<endl;

         //replac space with commas
        for(int i=input.find('[')+1;i<input.find(']')+1;i++){
            if(input[i]==' ' || input[i]==';' || input[i]==']'  || input[i]=='[')
            {
                if(input[i-1]==','){continue;}
                else {input[i]=',';}
                }
        }
        
//cout<<input<<endl;
        // parse matrix element

     //   int start=input.find('=')+2; int end=input.find(",",start+1); string s;
     int start=input.find('[')+1; int end=input.find(",",start+2); string s;
      // cout<<input<<endl;
        while(end<=input.size()){
         s=input.substr(start,end-start);   //cout<<s<<"--";
         values[valuesIndex]=atof(s.c_str());  valuesIndex++;
         start=end+1;
         end=input.find(",",end+1);
        }
      //  cout<<endl;

         

       
       string name=input.substr(0,1);
       matrixnames[matrixnum]=name;
       matrixnum++;
      // name=trim(name);
    //  cout<<name<<">>>>"<<numRow<<','<<numCol<<endl;
     //  Matrix A(numRow,numCol);
       matMap.insert(pair<string,Matrix>(name,Matrix(numRow,numCol)));
       matMap.at(name).setValue(values);

      if(input[input.size()-1]!='?' && print ==1){
           cout<<name<<'='<<endl;
       matMap.at(name).printMatrix();
      }

       // cout<<"-----"<<valuesIndex<<"------"<<endl;
        for(int i=0;i<valuesIndex;i++){
        // cout<<values[i]<<endl;
        }
         }
         
         else{
         string name=input.substr(0,1);
        // name=trim(name);
         string matrix1,matrix2;

      if(input.find('/')<input.size() && input.find("./")>input.size()){
         string matrix1=input.substr(input.find('=')+1,input.find('/')-input.find('=')-1);   matrix1=trim(matrix1);
         string matrix2=input.substr(input.find('/')+1);          matrix2=trim(matrix2); 
         matMap.insert(pair<string,Matrix>(name,matMap.at(matrix1)/matMap.at(matrix2)));   
         matrixnames[matrixnum]=name;
         matrixnum++;
          if(input[input.size()-1]!=';' && print ==1){
           cout<<name<<'='<<endl;
       matMap.at(name).printMatrix();
       }
      }


      if(input.find("./")<input.size()){
         string matrix1=input.substr(input.find('=')+1,input.find("./")-input.find('=')-1);  // matrix1=trim(matrix1);
         string matrix2=input.substr(input.find("./")+2);          matrix2=trim(matrix2); 

        int x1=matMap.count(matrix1);
        
        if(x1==0){
            double firstoperand=atof(matrix1.c_str()); 
            matMap.insert(pair<string,Matrix>(name,matMap.at(matrix2).elementDivision(firstoperand))); 
                   matrixnames[matrixnum]=name;
       matrixnum++;  
          if(input[input.size()-1]!=';' && print ==1){
           cout<<name<<'='<<endl;
       matMap.at(name).printMatrix();
          }   
        }
       /* else{
            matMap.insert(pair<string,Matrix>(name,matMap.at(matrix1).elementDivision(matMap.at(matrix2))));   
          if(input[input.size()-1]!=';'){
           cout<<name<<'='<<endl;
       matMap.at(name).printMatrix();
       } 
        } */
       
       
      }




      if(input[input.size()-1]=='\''){
         

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
      for (int i=1;i<argc;i++)
        {input+=argv[i];
          input+=" ";
        }
      operation(input);

   }
   /*while ( inFile>>s && c<2) {
       if(s.find("]")<100){ remove(s.c_str()); input=input+s;  operation(input); input=""; c++;  } //cout<<input<<endl;
    
       else{ remove(s.c_str()); input=input+s+" ";  }
}*/

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
