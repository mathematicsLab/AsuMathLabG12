class Matrix
{
    public:
    int nRow;
    int nCol;
    double **pData;
    char name;

    //default constructor
    public: Matrix();

    // constructor
    public : Matrix(int row,int col);

    public : Matrix(std::string s);
   /*  ~Matrix()
    {
        for (int i=0;i<nCol;i++)
        {
            delete pData[i];
        }
        delete pData;
    }  */


    void setValue(double data[]);
    Matrix Inv( Matrix& a);
    void Swap(double& a, double& b);
    double Det( Matrix& a);
    Matrix Diag( Matrix& v);
    Matrix Diag(const int n);
      Matrix Minor(const int row, const int col) ;
        Matrix Divide ( Matrix a, Matrix b);

        void N_A_N ();
            Matrix elementDivision (Matrix &A);
            Matrix elementDivision (double A);

    public:void horzcat(Matrix& A,Matrix& B);
   public:void reset();
   public:std::string toString();

		public:static Matrix zeros(int nR, int nC);
		public:static Matrix ones(int nR, int nC);
		public:static Matrix eye(int nR, int nC);
		public:static Matrix randM(int nR, int nC);
public: static Matrix sin(Matrix m);
public: static Matrix cos(Matrix m);
public: static Matrix tan(Matrix m);





    //Getters
     // index operator.

  public: double& operator () (const int r, const int c);


public: int getRow();
public: int getCol();
public: double get(int r,int c);

public:void printMatrix();

 // add a double value
 public: Matrix add(Matrix a, double v);

  //add matrix with matrix
public: static Matrix add(Matrix a, Matrix b);

// subtract a double value (elements wise)
public:  Matrix subtract(Matrix a, double v);

public: static Matrix subtract(Matrix a, Matrix b);

 // multiply by double value
  Matrix Multiply(Matrix a,double v);

  // multiply matrix by matrix
  Matrix Multiply(Matrix a ,Matrix b);

  // divide by double value
  Matrix Divide( double v);
  Matrix transpose(Matrix A);

  // division of Matrix with Matrix
 /* Matrix Divide ( Matrix a, Matrix b)
  {
    // check if the dimensions match: must be square and equal sizes
    if (a.nRow == a.nCol && a.nRow == a.nCol && b.nRow == b.nCol)
    {
      Matrix res(a.nRow, a.nCol);

      res = a * Inv(b);

      return res;
    }
    else
    {
      // give an error
      throw Exception("Dimensions does not match");
    }

    // return an empty matrix (this never happens but just for safety)
    return Matrix();
  } */

  //*******************************************************************************************
  public:Matrix getCofactor(int row,int column) ;  //get the cofactor of matrix NXN

   public: double matDeterminant ();
    public:void matProduct(double Const); //Multiply each number in the matrix with Constant

    public:void minorMat (Matrix &A);  // get matrix of minors

  public:  void matTranspose(Matrix &A); //get the transpose of matrix

    public:void inverseMat (Matrix A); //Get inverse of the matrix

    void eye ();
    bool isZeros();

   public:void multiply (Matrix &A); // Multiply Two matrices

   public: void copy(Matrix& A);
  public:  Matrix operator / (Matrix& A);
public:Matrix operator / (float x);

  //*******************************************************************************************
	//power members//
 public :Matrix getpower (Matrix s,int A);
 // get (double)(fractional) power for 1x1 matrix
 public :Matrix getDpower (Matrix s , double a);
 public :Matrix logAlgorithm(Matrix m,int A);//optimized power
 public :Matrix elementPower (int A);
 public :Matrix elementDPower (double A);
 public :void printMF(Matrix s);

//******************************************************************************************

 public: Matrix operator+ ( double b);

public:  Matrix operator +(Matrix a);

public:  Matrix operator -(Matrix a);

public:  Matrix operator -(double v);
public: Matrix operator =(Matrix a);
public: Matrix Transpose(Matrix A); //get the transpose of matrix



// operator multiplication
  public: Matrix operator* ( Matrix b);

  // multiplication of Matrix with double
  public: Matrix operator* ( double b);
 /* Matrix operator/(Matrix b){
      return Divide(*this,b);
  } */
  public : Matrix operator^ (int mad);
  public : Matrix operator^ (double mad);
  public : Matrix operator!(int mad);
  public : Matrix operator!(double mad);

};
