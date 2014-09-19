
#include "Matrix.h"
#include "SUtils/BinaryIO.h"
#include "gsl/gsl_matrix.h"
#include "gsl/gsl_linalg.h"
#include <cassert>
#include <cmath>
#include <ctime>

namespace SMathLib {
;

// constructors and destructor.
// ------------------------------------------------------------------------- //

// default constructor.
Matrix::Matrix()
{
	rows    = 0;
	cols    = 0;
	matType = M_NULL;
	matrix  = NULL;
}

// creates r*c matrix. default type is M_ZEROS
Matrix::Matrix(int r, int c, int type)
{
	// rows and cols must be non-negative.
	assert(r>=0 && c>=0);
	
	// check if type is correct.
	assert(type == M_ZEROS || type == M_EYE ||
	       type == M_RAND  || type == M_ONES);
	
	rows = r;
	cols = c;
	
	if(rows==cols)
		matType = M_SQRMATRIX;
	if(rows==1 && cols!=1)
		matType = M_ROWVECTOR;
	if(rows!=1 && cols==1)
		matType = M_COLVECTOR;
	
	matrix = new double[rows*cols];
	assert(matrix);		// check if memory was allocated.
	
	// initialize matrix based on type.
	if(type == M_ZEROS)		// zero matrix.
	{
		for(int i=0 ; i<rows*cols ; i++)
			matrix[i] = 0;
	}
	
	else if(type == M_EYE)		// identity matrix.
	{
		for(int i=0 ; i<rows ; i++)
			for(int j=0 ; j<cols ; j++)
			{
				if(i==j)
					matrix[i*cols+j] = 1;
				else
					matrix[i*cols+j] = 0;
			}
	}
	
	else if(type == M_RAND)		// random matrix.
	{
		srand( (unsigned int) time(NULL) );
		for(int i=0 ; i<rows ; i++)
		{
			for(int j=0 ; j<cols ; j++)
				matrix[i*cols+j] = (double)(rand()%100)/100.0;
		}
	}
	
	else if(type == M_ONES)		// matrix with all ones.
	{
		for(int i=0 ; i<rows*cols ; i++)
		matrix[i] = 1;
	}
}

// constructs a matrix using a linear array.
Matrix::Matrix(int r, int c, double* data)
{
	// rows and cols must be non-negative.
	assert(r>=0 && c>=0);
	
	rows = r;
	cols = c;
	
	if(rows==cols)
		matType = M_SQRMATRIX;
	if(rows==1 && cols!=1)
		matType = M_ROWVECTOR;
	if(rows!=1 && cols==1)
		matType = M_COLVECTOR;
	
	matrix = new double[rows*cols];
	assert(matrix && data);	// check if memory was allocated.
	
	memcpy(matrix, data, rows*cols*sizeof(double));
}

// copy constructor.
Matrix::Matrix(const Matrix& B)
{
	rows    = 0;
	cols    = 0;
	matType = M_NULL;
	matrix  = NULL;
	
	// call assignment operator.
	*this = B;
}

// destructor.
Matrix::~Matrix()
{
	if(matrix)
		delete []matrix;
}
// ------------------------------------------------------------------------- //




// assignment, element indexing, submatrix indexing and casting operators.
// ------------------------------------------------------------------------- //

// assignment operator.
Matrix& Matrix::operator =(const Matrix& B)
{
//	assert(B.rows>=0 && B.cols>=0);	// dimensions of B must be positive.	
//	assert(B.matrix);				// B's matrix must be non-null.
	
	if((B.rows == 0 && B.cols == 0) || B.matrix == NULL)
	{
		rows   = 0;
		cols   = 0;
		matrix = NULL;
		return *this;
	}
	
	rows    = B.rows;
	cols    = B.cols;
	matType = B.matType;
	
	if(this->matrix)
		delete []this->matrix;
	this->matrix = new double[rows*cols];
	assert(this->matrix);	// check if memory was allocated.
	
	memcpy(this->matrix, B.matrix, rows*cols*sizeof(double));
	return *this;
}

// indexing operator.
double& Matrix::operator ()(int r, int c) const
{
	assert(r>=0 && r<rows && c>=0 && c<cols);
	assert(matrix);
	
	return matrix[r*cols + c];
}

// indexing operator
double& Matrix::operator [](int index) const
{
	assert(index>=0 && index<rows*cols);
	assert(matrix);
	
	return matrix[index];
}

// sub-matrix indexing operator.
Matrix Matrix::operator ()(int r1, int c1, int r2, int c2) const
{
	assert(r1>=0 && r2<rows && c1>=0 && c1<cols);
	
	Matrix submatrix;
	submatrix.rows = r2 - r1 + 1;
	submatrix.cols = c2 - c1 + 1;
	
	if(submatrix.rows == submatrix.cols)
		submatrix.matType = M_SQRMATRIX;
	else if(submatrix.rows==1 && submatrix.cols!=1)
		submatrix.matType = M_ROWVECTOR;
	else if(submatrix.rows!=1 && submatrix.cols==1)
		submatrix.matType = M_COLVECTOR;
	
	submatrix.matrix = new double[submatrix.rows*submatrix.cols];
	assert(submatrix.matrix);
	
	int x = 0, y = 0;
	for(int i=r1 ; i<=r2 ; i++)
	{
		y = 0;
		for(int j=c1 ; j<=c2 ; j++)
		{
			submatrix.matrix[x*submatrix.cols+y] = matrix[i*cols+j];
			y++;
		}
		x++;
	}
	
	return submatrix;
}

// ------------------------------------------------------------------------- //



// arithmetic operators.
// ------------------------------------------------------------------------- //
// addition operator.
Matrix Matrix::operator +(const Matrix& B) const
{
	assert(rows==B.rows && cols==B.cols);
	assert(matrix && B.matrix);
	
	Matrix temp(rows,cols);
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			temp.matrix[i*cols+j] = matrix[i*cols+j] + B.matrix[i*cols+j];
	return temp;
}

// addition operator.
Matrix& Matrix::operator +=(const Matrix& B)
{
	assert(rows==B.rows && cols==B.cols);
	assert(matrix && B.matrix);
	
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			matrix[i*cols+j] = matrix[i*cols+j] + B.matrix[i*cols+j];
	
	return *this;
}

// subtraction operator
Matrix Matrix::operator -(const Matrix& B) const
{
	assert(rows==B.rows && cols==B.cols);
	assert(matrix && B.matrix);
	
	Matrix temp(rows,cols);
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			temp.matrix[i*cols+j] = this->matrix[i*cols+j] - B.matrix[i*cols+j];
	return temp;
}

// subtraction operator.
Matrix& Matrix::operator -=(const Matrix& B)
{
	assert(rows==B.rows && cols==B.cols);
	assert(matrix && B.matrix);
	
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			matrix[i*cols+j] = this->matrix[i*cols+j] - B.matrix[i*cols+j];
	
	return *this;
}

// scalar multiplication.
Matrix Matrix::operator *(double s) const
{
	assert(matrix);
	
	Matrix temp(rows, cols);
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			temp.matrix[i*cols+j] = this->matrix[i*cols+j] * s;
	return temp;
}

// scalar multiplication.
Matrix& Matrix::operator *=(double s)
{
	assert(matrix);
	
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			matrix[i*cols+j] = this->matrix[i*cols+j] * s;
	
	return *this;
}

// scalar division.
Matrix Matrix::operator /(double s) const
{
	assert(matrix);
	
	Matrix temp(rows, cols);
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			temp.matrix[i*cols+j] = this->matrix[i*cols+j] / s;
	return temp;
}

Matrix& Matrix::operator /=(double s)
{
	assert(matrix);
	
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			matrix[i*cols+j] = this->matrix[i*cols+j] / s;
	
	return *this;
}

// matrix multiplication.
Matrix Matrix::operator *(const Matrix& B) const
{
	assert(cols == B.rows);
	
	Matrix temp(rows, B.cols);
	for(int i=0 ; i<rows ; i++)
	{
		for(int j=0 ; j<B.cols ; j++)
			for(int l=0 ; l<cols ; l++)
			{
				temp(i,j) = temp(i,j)+matrix[i*cols+l]*B.matrix[l*(B.cols)+j];
			}
	}
	
	return temp;
}

Matrix& Matrix::operator *=(const Matrix& B)
{
	assert(cols == B.rows);
	
	Matrix temp(rows, B.cols);
	for(int i=0 ; i<rows ; i++)
	{
		for(int j=0 ; j<B.cols ; j++)
			for(int l=0 ; l<cols ; l++)
			{
				temp(i,j) = temp(i,j)+matrix[i*cols+l]*B.matrix[l*(B.cols)+j];
			}
	}
	
	*this = temp;
	return *this;
}
// ------------------------------------------------------------------------- //




// logical operators.
// ------------------------------------------------------------------------- //

// check if two vectors are equal.
bool Matrix::operator ==(const Matrix& B) const
{
	assert(B.matrix && B.rows>=0 && B.cols>=0);
	assert(rows==B.rows && cols==B.cols);
	
	for(int i=0 ; i<rows*cols ; i++)
	{
		if(matrix[i] != B.matrix[i])
			return false;
	}
	
	return true;
}

// check if two vectors are not equal.
bool Matrix::operator !=(const Matrix& B) const
{
	assert(B.matrix && B.rows>=0 && B.cols>=0);
	assert(rows==B.rows && cols==B.cols);
	
	for(int i=0 ; i<rows*cols ; i++)
	{
		if(matrix[i] != B.matrix[i])
			return true;
	}
	
	return false;
}

// check equivalence of two matrices.
bool Matrix::IsEqual(const Matrix& B, double tolerance) const
{
	assert(B.matrix && B.rows>=0 && B.cols>=0);
	assert(rows==B.rows && cols==B.cols);
	
	for(int i=0 ; i<rows*cols ; i++)
	{
		if(fabs(matrix[i]-B.matrix[i]) > tolerance)
			return false;
	}
	
	return true;
}

// check equivalence of two matrices.
bool Matrix::IsNotEqual(const Matrix& B, double tolerance)	const
{
	assert(B.matrix && B.rows>=0 && B.cols>=0);
	assert(rows==B.rows && cols==B.cols);
	
	for(int i=0 ; i<rows*cols ; i++)
	{
		if(fabs(matrix[i]-B.matrix[i]) > tolerance)
			return true;
	}
	
	return false;
}
// ------------------------------------------------------------------------- //




// FUNCTIONS.
// ------------------------------------------------------------------------- //

// set submatrix of a matrix.
void Matrix::SetSubMatrix(int r1, int c1, int r2, int c2, 
                              const Matrix &B)
{
	assert(r1>=0 && r2<rows && c1>=0 && c2<cols);
	
	int x = 0, y = 0;
	for(int i=r1 ; i<=r2 ; i++)
	{
		y = 0;
		for(int j=c1 ; j<=c2 ; j++)
		{
			matrix[i*cols+j] = B.matrix[x*B.cols+y];
			y++;
		}
		x++;
	}
}

// set a row of the matrix.
void Matrix::SetRow(int r, const Matrix &B)
{
	assert(r>=0 && r<rows);
	
	for(int j=0 ; j<=cols ; j++)
		matrix[r*cols+j] = B.matrix[j];
}

// set a col of the matrix.
void Matrix::SetCol(int c, const Matrix &B)
{
	assert(c>=0 && c<cols);
	
	for(int i=0 ; i<=rows ; i++)
		matrix[i*cols+c] = B.matrix[i];
}

// Transpose of a matrix
Matrix Matrix::Transpose() const
{
	assert(matrix);
	
	Matrix temp(cols,rows);
	for(int i=0 ; i<rows ; i++)
		for(int j=0 ; j<cols ; j++)
			temp.matrix[j*rows+i] = this->matrix[i*cols+j];
	return temp;
}

// average elements in a row and return average vector.
Matrix Matrix::AvgRows() const
{
	Matrix avg(rows, 1);
	
	for(int i=0 ; i<rows ; i++)
	{
		for(int j=0 ; j<cols ; j++)
		{
			avg(i, 0) = avg(i, 0) + matrix[i*cols+j];
		}
		avg(i, 0) = avg(i, 0) / cols;
	}
	
	return avg;
}

// compute 2-norm of the vector.
double Matrix::VectorNorm()
{
	// must be a vector.
	if(rows != 1 && cols != 1)
		return -1;
	
	if(rows == 1 && cols == 1)
		return matrix[0];
	
	double norm = 0;
	for(int i=0 ; i<rows+cols-1 ; i++)
		norm += matrix[i]*matrix[i];
	
	return sqrt(norm);
}

// compute square of 2-norm of the vector.
double Matrix::VectorNorm2()
{
	// must be a vector.
	if(rows != 1 && cols != 1)
		return -1;
	
	if(rows == 1 && cols == 1)
		return matrix[0];
	
	double norm = 0;
	for(int i=0 ; i<rows+cols-1 ; i++)
		norm += matrix[i]*matrix[i];
	
	return norm;
}

// Find Inverse of a square matrix.
Matrix Matrix::Inverse() const
{
	assert(rows>0 && cols>0 && rows==cols);
	
	// Size of the square matrix.
	int _dim = rows;
	
	// Create a copy of the matrix.
	double* _matrixLU = new double[_dim*_dim];
	memcpy(_matrixLU, matrix, _dim*_dim*sizeof(double));
	gsl_matrix_view _gslLU = gsl_matrix_view_array(_matrixLU, _dim, _dim);
	
	// Compute the LU decomposition.
	gsl_permutation* p = gsl_permutation_alloc(_dim);
	int s;
	gsl_linalg_LU_decomp(&_gslLU.matrix, p, &s);
	
	// Compute inverse.
	Matrix _inverse(_dim, _dim);
	gsl_matrix_view gslI = gsl_matrix_view_array(_inverse.matrix, _dim, _dim);
	gsl_linalg_LU_invert(&_gslLU.matrix, p, &gslI.matrix);
	
	// Free local variables.
	gsl_permutation_free(p);
	delete [] _matrixLU;
	
	return _inverse;
}
// finds SVD of a matrix.
Matrix Matrix::Svd(Matrix* S, Matrix* V) const
{
	// Create a copy of the matrix.
	double* _matrixA = new double[rows*cols];
	memcpy(_matrixA, matrix, rows*cols*sizeof(double));
	gsl_matrix_view _gslA = gsl_matrix_view_array(_matrixA, rows, cols);
	
	// Create matrices for U, S and V.
	Matrix _S(cols, 1);
	*V = Matrix(cols, cols);
	gsl_vector_view _gslS = gsl_vector_view_array(_S.matrix, cols);
	gsl_matrix_view _gslV = gsl_matrix_view_array(V->matrix, cols, cols);
	
	Matrix _work(cols, 1);
	gsl_vector_view _gslWork = gsl_vector_view_array(_work.matrix, cols);
	gsl_linalg_SV_decomp(&_gslA.matrix, &_gslV.matrix, &_gslS.vector, &_gslWork.vector);
	
	*S = Matrix(cols, cols, M_ZEROS);
	for(int i=0 ; i<cols ; ++i)
	{
		S->matrix[i*cols+i] = _S.matrix[i];
	}
	
	return Matrix(rows, cols, _matrixA);
}
// return Determinant of matrix.
double Matrix::Determinant() const
{
	// Size of the square matrix.
	int _dim = rows;
	
	// Create a copy of the matrix.
	double* _matrixLU = new double[_dim*_dim];
	memcpy(_matrixLU, matrix, _dim*_dim*sizeof(double));
	gsl_matrix_view _gslLU = gsl_matrix_view_array(_matrixLU, _dim, _dim);
	
	// Compute the LU decomposition.
	gsl_permutation* p = gsl_permutation_alloc(_dim);
	int s;
	gsl_linalg_LU_decomp(&_gslLU.matrix, p, &s);
	
	// Compute determinant.
	double _det = gsl_linalg_LU_det(&_gslLU.matrix, s);
	
	// Free local variables.
	gsl_permutation_free(p);
	delete [] _matrixLU;
	
	return _det;
}
// ------------------------------------------------------------------------- //


// ------------------------------------------------------------------------- //
Matrix Matrix::SolveAxB(const Matrix& A, const Matrix& B)
{
	assert(A.rows==B.rows && B.cols==1);
	
	// Compute the LU decomposition of A.
	gsl_matrix*      gslA = gsl_matrix_alloc(A.rows, A.cols);
	gsl_permutation* p    = gsl_permutation_alloc(A.rows);
	int s;
	gsl_matrix_memcpy(gslA, &gsl_matrix_view_array(A.matrix, A.rows, A.cols).matrix);
	gsl_linalg_LU_decomp(gslA, p, &s);
	
	// Solve A x = B.
	gsl_vector* gslB = gsl_vector_alloc(B.rows);
	gsl_vector* gslX = gsl_vector_alloc(B.rows);
	gsl_vector_memcpy(gslB, &gsl_vector_view_array(B.matrix, B.rows).vector);
	gsl_linalg_LU_solve(gslA, p, gslB, gslX);
	
	// Copy result to Matrix type.
	Matrix X(A.cols, 1);
	gsl_vector_view gslTemp = gsl_vector_view_array(X.matrix, A.cols);
	gsl_vector_memcpy(&gslTemp.vector, gslX);
	
	// Free gsl variables.
	gsl_matrix_free(gslA);
	gsl_vector_free(gslB);
	gsl_vector_free(gslX);
	gsl_permutation_free(p);
	
	return X;
}
// ------------------------------------------------------------------------- //


// ------------------------------------------------------------------------- //
// for standard IO.
std::ostream& operator <<(std::ostream& out, const Matrix &B)
{
	if((B.rows==0 && B.cols==0) || B.matrix==NULL)
		out << "Null Matrix";
	
	out << B.rows << " " << B.cols;
	for(int i=0 ; i<B.rows ; i++)
	{
		out << std::endl;
		
		for(int j=0 ; j<B.cols ; j++)
			out << B(i,j) << " ";
	}
	return out;
}

std::istream& operator >>(std::istream& in, Matrix &B)
{
//	assert(B.rows!=0 && B.cols!=0 && B.matrix!=NULL);
	
	int r, c;
	in >> r >> c;
	B = Matrix(r, c);
	
	for(int i=0 ; i<B.rows ; i++)
		for(int j=0 ; j<B.cols ; j++)
			in >> B(i,j);
	return in;
}
// ------------------------------------------------------------------------- //


// ------------------------------------------------------------------------- //
Matrix Matrix::EigValsSymMat()
{
	Matrix eigVals;
	
	return eigVals;
}
// ------------------------------------------------------------------------- //


// ------------------------------------------------------------------------- //
void Matrix::Write(std::ostream& out) const
{
	if((rows==0 && cols==0) || matrix==NULL)
		out << "Null Matrix";
	
	out << rows << " " << cols;
	for(int i=0 ; i<rows ; i++)
	{
		out << std::endl;
		
		for(int j=0 ; j<cols ; j++)
			out << (*this)(i,j) << " ";
	}
}

void Matrix::Read(std::istream& in)
{
	int r, c;
	in >> r >> c;
	*this = Matrix(r, c);
	
	for(int i=0 ; i<rows ; i++)
		for(int j=0 ; j<cols ; j++)
			in >> (*this)(i,j);
}
// ------------------------------------------------------------------------- //


// ------------------------------------------------------------------------- //
void Matrix::WriteBin(std::ostream& out) const
{
	SUtils::writeFundamental(out, rows);
	SUtils::writeFundamental(out, cols);
	
	for(int i=0 ; i<rows ; i++)
	{
		for(int j=0 ; j<cols ; j++)
		{
			SUtils::writeFundamental(out,  this->matrix[i*cols + j]);
		}
	}
}

void Matrix::ReadBin(std::istream& in)
{
	rows = SUtils::readFundamental<int>(in);
	cols = SUtils::readFundamental<int>(in);
	
	*this = Matrix(rows, cols);
	
	for(int i=0 ; i<rows ; i++)
	{
		for(int j=0 ; j<cols ; j++)
		{
			this->matrix[i*cols + j] = SUtils::readFundamental<double>(in);
		}
	}
}
// ------------------------------------------------------------------------- //

};	// End namespace SMathLib.
