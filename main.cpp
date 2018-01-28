#include<iostream>
#include"Matrix.h"
//#include"stdlib.h"
#include <stdio.h>
#include"string.h"
#include"map"
#include<string>
#include<fstream>
#include <algorithm> 
//#include<sstream>
//#include <cctype>
//#include <locale>
using namespace std;

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


void operation(string input )
{
        static map<string, Matrix> matMap; 

        int COUNT=0;
        string name=input.substr(0,1);
        int index=0,temp=input.find('[');
        while (input.find('[',index) != string ::npos)
        {
        	if(input.find('[',index) != string ::npos)
        		COUNT++;
        	index=temp+1;
        	temp=input.find('[',index);

        }
        if (COUNT >1) // for matrix within a matrix
        {
        	int pos,endPos,temp;
        	for(int i=0;i<matrixnum;i++)
        		if(input.find(matrixnames[i]) != string::npos)
        		{
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
 cout<<name<<" ="<<endl;
       matMap.at(name).printMatrix();

        }

        else if(input[input.size()-1]==']' || input[input.size()-2]==']' ){
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

      if(input[input.size()-1]!='?'){
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


         
         if(input.find('+')<input.size()){
             name="C";
             for(int i=input.find('=')+1;i<input.length();i++){
                 if(input[i]==' '){continue;}
                 else{ matrix1=input.substr(i,1);   break;}
             }

             for(int i=input.find('+')+1;i<input.length();i++)  {
                 if(input[i]==' ')continue;
                 else{ matrix2=input.substr(i,1);       break; }
             }      
            
        
        //  matrix2=input.substr(input.find('+')+1);    matrix2=trim(matrix2);    cout<<matrix2<<matrix2.length()<<endl;  
         matMap.insert(pair<string,Matrix>(name,matMap.at(matrix1)+matMap.at(matrix2)));
                matrixnames[matrixnum]=name;
       matrixnum++;
         //matMap.at(name).printMatrix();
         if(input[input.size()-1]!=';'){
           cout<<name<<'='<<endl;
       matMap.at(name).printMatrix();
       }   
          
      }



      if(input.find('-')<input.size()){
         string matrix1=input.substr(input.find('=')+1,input.find('-')-input.find('=')-1);   matrix1=trim(matrix1);
         string matrix2=input.substr(input.find('-')+1);   matrix2=trim(matrix2);    
         matMap.insert(pair<string,Matrix>(name,matMap.at(matrix1)-matMap.at(matrix2)));   
         matrixnames[matrixnum]=name;
       matrixnum++;
          if(input[input.size()-1]!=';'){
           cout<<name<<'='<<endl;
       matMap.at(name).printMatrix();
       }
      }

       if(input.find('*')<input.size()){
         string matrix1=input.substr(input.find('=')+1,input.find('*')-input.find('=')-1);   matrix1=trim(matrix1); 
         string matrix2=input.substr(input.find('*')+1);        matrix2=trim(matrix2); 
         matMap.insert(pair<string,Matrix>(name,matMap.at(matrix1)*matMap.at(matrix2)));  
         matrixnames[matrixnum]=name;
       matrixnum++; 
         if(input[input.size()-1]!=';'){
           cout<<name<<'='<<endl;
       matMap.at(name).printMatrix();
       }
      }

      if(input.find('/')<input.size() && input.find("./")>input.size()){
         string matrix1=input.substr(input.find('=')+1,input.find('/')-input.find('=')-1);   matrix1=trim(matrix1);
         string matrix2=input.substr(input.find('/')+1);          matrix2=trim(matrix2); 
         matMap.insert(pair<string,Matrix>(name,matMap.at(matrix1)/matMap.at(matrix2)));   
         matrixnames[matrixnum]=name;
         matrixnum++;
          if(input[input.size()-1]!=';'){
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