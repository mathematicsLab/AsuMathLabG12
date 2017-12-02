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
        static map<string, Matrix> matMap; 

        if(input[input.size()-1]==']' || input[input.size()-2]==']' ){
            //count number of rows $ col
        int numRow=1,numCol=1;
        for(int i=input.find('[');i<((input.find(';')<input.size()?input.find(';'):input.find(']')));i++){if(input[i]==' ' && input[i-1]!='[' && input[i+1]!=';')numCol++;}
        for(int i=input.find('[');i<input.find(']')-1;i++){if(input[i]==';' && input[i+1]!=']' && input[i+2]!=']' && input[i+3]!=']' )numRow++;}
        double values[2000]; int valuesIndex=0; 

        if(input[input.size()-1]==';'){
            input=input.substr(0,input.find(']')+1);
        }
cout<<input<<endl;

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
     int start=input.find('[')+1; int end=input.find(","); string s;
      // cout<<input<<endl;
        while(end<=input.size()){
         s=input.substr(start,end-start);   //cout<<s<<"--";
         values[valuesIndex]=atof(s.c_str());  valuesIndex++;
         start=end+1;
         end=input.find(",",end+1);
        }
      //  cout<<endl;

         

       
       string name=input.substr(0,1);
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
          if(input[input.size()-1]!=';'){
           cout<<name<<'='<<endl;
       matMap.at(name).printMatrix();
       }
      }

       if(input.find('*')<input.size()){
         string matrix1=input.substr(input.find('=')+1,input.find('*')-input.find('=')-1);   matrix1=trim(matrix1); 
         string matrix2=input.substr(input.find('*')+1);        matrix2=trim(matrix2); 
         matMap.insert(pair<string,Matrix>(name,matMap.at(matrix1)*matMap.at(matrix2)));   
         if(input[input.size()-1]!=';'){
           cout<<name<<'='<<endl;
       matMap.at(name).printMatrix();
       }
      }

      if(input.find('/')<input.size() && input.find("./")>input.size()){
         string matrix1=input.substr(input.find('=')+1,input.find('/')-input.find('=')-1);   matrix1=trim(matrix1);
         string matrix2=input.substr(input.find('/')+1);          matrix2=trim(matrix2); 
         matMap.insert(pair<string,Matrix>(name,matMap.at(matrix1)/matMap.at(matrix2)));   
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

 cout<<input<<endl;
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
