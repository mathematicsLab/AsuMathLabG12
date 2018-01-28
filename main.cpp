#include<iostream>
#include"Matrix.h"
//#include"stdlib.h"
#include <stdio.h>
#include"string.h"
#include"map"
#include<string>
#include<fstream>
#include<stack>
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
      if( input[input.size()-1] !=';'){
           cout<<name<<'='<<endl;
       matMap.at(name).printMatrix();
      }
        for(int i=0;i<valuesIndex;i++){
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
		 if( input.size()<5)
		{
		
			if(it == matMap.end())
	   {
		  throw("The is no match matrix ") ;
		   
	   }
			else 
			matMap.at(name).printMatrix();
		}
		int c;
         it = matMap.find(name);
		 if(input.find('+')<input.size() && is){
             for(int i=input.find('=')+1;i<input.length();i++){
                 if(input[i]==' '){continue;}
                 else{ matrix1=input.substr(i,1);   break;}
             }

             for(int i=input.find('+')+1;i<input.length();i++)  {
                 if(input[i]==' ')continue;
                 else{ matrix2=input.substr(i,1);       break; }
             }      
            
          
			  if(it != matMap.end())
	   {
		   matMap.erase(it);
	   }
			 matMap.insert(pair<string,Matrix>(name,matMap.at(matrix1)+matMap.at(matrix2)));
         if(input[input.size()-1]!=';'){
           cout<<name<<'='<<endl;
       matMap.at(name).printMatrix();
       }   
          
      }
	  
		 if(sa<5000)
		 {
			 int sa2= sa+5;
			 matrix1=input.substr(sa2,1);
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
		 input.replace(sa,sa2+2,randommatrix[counterrandom]);
		 counterrandom++;
		 goto l1;
			}
			else
				throw("no such matrix ");
	}
			 

		 if(input.find('-')<input.size()&&is){
         string matrix1=input.substr(input.find('=')+1,input.find('-')-input.find('=')-1);   matrix1=trim(matrix1);
         string matrix2=input.substr(input.find('-')+1);   matrix2=trim(matrix2);
		  if(it != matMap.end())
	   {
		   matMap.erase(it);
	   }
         matMap.insert(pair<string,Matrix>(name,matMap.at(matrix1)-matMap.at(matrix2)));   
          if(input[input.size()-1]!=';'){
           cout<<name<<'='<<endl;
       matMap.at(name).printMatrix();
       }
      }

		 if(input.find('*')<input.size()&&is){
         string matrix1=input.substr(input.find('=')+1,input.find('*')-input.find('=')-1);   matrix1=trim(matrix1); 
        string matrix2=input.substr(input.find('*')+1);        matrix2=trim(matrix2); 
         if(it != matMap.end())
	   {
		   matMap.erase(it);
	   }
		matMap.insert(pair<string,Matrix>(name,matMap.at(matrix1)*matMap.at(matrix2)));   
         if(input[input.size()-1]!=';'){
           cout<<name<<'='<<endl;
       matMap.at(name).printMatrix();
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
		   numbermap.insert(pair<string,float>(label,resultts));
		   cout<<label<<" ="<<endl;
		   cout<<resultts<<endl;
	   }
	   if(input.find('/')<input.size() && input.find("./")>input.size()&&is){
         string matrix1=input.substr(input.find('=')+1,input.find('/')-input.find('=')-1);   matrix1=trim(matrix1);
        string matrix2=input.substr(input.find('/')+1);          matrix2=trim(matrix2); 
         if(it != matMap.end())
	   {
		   matMap.erase(it);
	   }
		matMap.insert(pair<string,Matrix>(name,matMap.at(matrix1)/matMap.at(matrix2)));   
          if(input[input.size()-1]!=';'){
           cout<<name<<'='<<endl;
       matMap.at(name).printMatrix();
       }
      }
	  
	  if(input.find("=")!=-1 && input.find("[") == -1 && input.find("+") == -1 &&is&& input.find("-") == -1 && input.find("*") == -1 && input.find("/") == -1 )
		{
			for(int ns=0;ns<input.size();ns++)
   {
	   ns=input.find(' ');
	   if(ns !=-1)
	   {
		   input.erase(ns,1);
	   }
	   else
		   break;
   }
			matrix1=input.substr(0,1);
			matrix2=input.substr(input.find("=")+1,input.size()-input.find("="));
			matMap.erase(matrix1);
			matMap.insert(pair<string,Matrix>(matrix1,matMap.at(matrix2)));
			 if(input[input.size()-1]!=';'){
			cout<<matrix1<<'='<<endl;
			matMap.at(matrix1).printMatrix();}
		}

      if(input.find("./")<input.size()&&is){
         string matrix1=input.substr(input.find('=')+1,input.find("./")-input.find('=')-1);  // matrix1=trim(matrix1);
         string matrix2=input.substr(input.find("./")+2);          matrix2=trim(matrix2); 

        int x1=matMap.count(matrix1);
        
        if(x1==0){
            double firstoperand=atof(matrix1.c_str()); 
            matMap.insert(pair<string,Matrix>(name,matMap.at(matrix2).elementDivision(firstoperand)));   
          if(input[input.size()-1]!=';'){
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
}


/*
int main(int argc, char* argv[]){
  
        string input;
    //create map for matrix
       // map<string, Matrix> matMap;       

    if(argc>1)
    {
    
    ifstream inFile;
    inFile.open(argv[1]);
    if (!inFile) {
    cout << "Unable to open file datafile.txt";
    exit(1);   // call system to stop    
   }
   while ( getline (inFile,input)) {

 cout<<input<<endl;
         operation(input);

}

    }
    
    do{
        getline(cin,input);
        operation(input);


      
    }
    while(input!="quite");

    return 0;
}  */
