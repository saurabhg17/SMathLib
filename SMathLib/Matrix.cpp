// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include "Matrix.h"
#include "CompareDouble.h"
#include <Eigen/Dense>
#include <Eigen/SVD>
#include <Eigen/LU>
#include <cassert>
#include <cmath>
#include <ctime>
#include <cstring>

namespace SMathLib {
;

// constructors and destructor.
// ------------------------------------------------------------------------- //

// default constructor.
Matrix::Matrix()
{
	rows    = 0;
	cols    = 0;
	matType = MatrixType::Null;
	matrix  = nullptr;
}

// creates r*c matrix. default type is M_ZEROS
Matrix::Matrix(size_t r, size_t c, MatrixType type)
{
	// rows and cols must be non-negative.
	assert(r>=0 && c>=0);
	
	rows = r;
	cols = c;
	
	if(rows == cols)
	{
		matType = MatrixType::Square;
	}
	if(rows == 1 && cols != 1)
	{
		matType = MatrixType::RowVector;
	}
	if(rows != 1 && cols == 1)
	{
		matType = MatrixType::ColumnVector;
	}
	
	matrix = new double[rows*cols];
	assert(matrix);
	
	// initialize matrix based on type.
	if(type == MatrixType::Zero)
	{
		memset(matrix, 0, rows * cols * sizeof(double));
	}
	
	else if(type == MatrixType::Identity)
	{
		for(size_t i=0 ; i<rows ; i++)
		{
			for(size_t j=0 ; j<cols ; j++)
			{
				if(i == j)
				{
					matrix[i * cols + j] = 1;
				}
				else
				{
					matrix[i * cols + j] = 0;
				}
			}
		}
	}
	
	else if(type == MatrixType::Random)
	{
		srand((unsigned int) time(nullptr));
		for(size_t i=0 ; i<rows ; i++)
		{
			for(size_t j=0 ; j<cols ; j++)
			{
				matrix[i * cols + j] = (double)(rand() % 100) / 100.0;
			}
		}
	}
	
	else if(type == MatrixType::Ones)
	{
		for(size_t i=0 ; i<rows*cols ; i++)
		{
			matrix[i] = 1;
		}
	}
}

// constructs a matrix using a linear array.
Matrix::Matrix(size_t r, size_t c, const double* data)
{
	// rows and cols must be non-negative.
	assert(r>=0 && c>=0);
	
	rows = r;
	cols = c;
	
	if (rows == cols)
	{
		matType = MatrixType::Square;
	}
	if (rows == 1 && cols != 1)
	{
		matType = MatrixType::RowVector;
	}
	if (rows != 1 && cols == 1)
	{
		matType = MatrixType::ColumnVector;
	}
	
	matrix = new double[rows*cols];
	assert(matrix && data);	// check if memory was allocated.
	
	memcpy(matrix, data, rows*cols*sizeof(double));
}

// copy constructor.
Matrix::Matrix(const Matrix& B)
{
	rows    = 0;
	cols    = 0;
	matType = MatrixType::Null;
	matrix  = nullptr;
	
	// call assignment operator.
	*this = B;
}

// destructor.
Matrix::~Matrix()
{
	if(matrix)
	{
		delete[] matrix;
	}
}
// ------------------------------------------------------------------------- //




// assignment, element indexing, submatrix indexing and casting operators.
// ------------------------------------------------------------------------- //

// assignment operator.
Matrix& Matrix::operator =(const Matrix& B)
{
	if((B.rows == 0 && B.cols == 0) || B.matrix == nullptr)
	{
		rows   = 0;
		cols   = 0;
		matrix = nullptr;
		return *this;
	}
	
	rows    = B.rows;
	cols    = B.cols;
	matType = B.matType;
	
	if(this->matrix)
	{
		delete[]this->matrix;
	}
	this->matrix = new double[rows*cols];
	assert(this->matrix);
	
	memcpy(this->matrix, B.matrix, rows*cols*sizeof(double));
	return *this;
}

// indexing operator.
double& Matrix::operator ()(size_t r, size_t c) const
{
	assert(r>=0 && r<rows && c>=0 && c<cols);
	assert(matrix);
	
	return matrix[r*cols + c];
}

// indexing operator
double& Matrix::operator [](size_t index) const
{
	assert(index>=0 && index<rows*cols);
	assert(matrix != nullptr);
	
	return matrix[index];
}

// sub-matrix indexing operator.
Matrix Matrix::operator ()(size_t r1, size_t c1, size_t r2, size_t c2) const
{
	assert(r1>=0 && r2<rows && c1>=0 && c1<cols);
	
	Matrix submatrix;
	submatrix.rows = r2 - r1 + 1;
	submatrix.cols = c2 - c1 + 1;
	
	if (submatrix.rows == submatrix.cols)
	{
		submatrix.matType = MatrixType::Square;
	}
	else if (submatrix.rows == 1 && submatrix.cols != 1)
	{
		submatrix.matType = MatrixType::RowVector;
	}
	else if (submatrix.rows != 1 && submatrix.cols == 1)
	{
		submatrix.matType = MatrixType::ColumnVector;
	}
	
	submatrix.matrix = new double[submatrix.rows*submatrix.cols];
	assert(submatrix.matrix);
	
	size_t x = 0, y = 0;
	for(size_t i=r1 ; i<=r2 ; i++)
	{
		y = 0;
		for(size_t j=c1 ; j<=c2 ; j++)
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
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			temp.matrix[i * cols + j] = matrix[i * cols + j] + B.matrix[i * cols + j];
		}
	}
	return temp;
}

// addition operator.
Matrix& Matrix::operator +=(const Matrix& B)
{
	assert(rows==B.rows && cols==B.cols);
	assert(matrix && B.matrix);
	
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			matrix[i * cols + j] = matrix[i * cols + j] + B.matrix[i * cols + j];
		}
	}
	
	return *this;
}

// subtraction operator
Matrix Matrix::operator -(const Matrix& B) const
{
	assert(rows==B.rows && cols==B.cols);
	assert(matrix && B.matrix);
	
	Matrix temp(rows,cols);
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			temp.matrix[i * cols + j] = this->matrix[i * cols + j] - B.matrix[i * cols + j];
		}
	}
	return temp;
}

// subtraction operator.
Matrix& Matrix::operator -=(const Matrix& B)
{
	assert(rows==B.rows && cols==B.cols);
	assert(matrix && B.matrix);
	
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			matrix[i * cols + j] = this->matrix[i * cols + j] - B.matrix[i * cols + j];
		}
	}
	
	return *this;
}

// scalar multiplication.
Matrix Matrix::operator *(double s) const
{
	assert(matrix);
	
	Matrix temp(rows, cols);
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			temp.matrix[i * cols + j] = this->matrix[i * cols + j] * s;
		}
	}
	return temp;
}

// scalar multiplication.
Matrix& Matrix::operator *=(double s)
{
	assert(matrix);
	
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			matrix[i * cols + j] = this->matrix[i * cols + j] * s;
		}
	}
	
	return *this;
}

// scalar division.
Matrix Matrix::operator /(double s) const
{
	assert(matrix);
	
	Matrix temp(rows, cols);
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			temp.matrix[i * cols + j] = this->matrix[i * cols + j] / s;
		}
	}

	return temp;
}

Matrix& Matrix::operator /=(double s)
{
	assert(matrix);
	
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			matrix[i * cols + j] = this->matrix[i * cols + j] / s;
		}
	}
	
	return *this;
}

// matrix multiplication.
Matrix Matrix::operator *(const Matrix& B) const
{
	assert(cols == B.rows);
	
	Matrix temp(rows, B.cols, MatrixType::Zero);
	for(size_t i=0 ; i<rows ; i++)
	{
		for (size_t j = 0; j < B.cols; j++)
		{
			for (size_t l = 0; l < cols; l++)
			{
				temp(i, j) = temp(i, j) + matrix[i * cols + l] * B.matrix[l * (B.cols) + j];
			}
		}
	}
	
	return temp;
}

Matrix& Matrix::operator *=(const Matrix& B)
{
	assert(cols == B.rows);
	
	Matrix temp(rows, B.cols);
	for(size_t i=0 ; i<rows ; i++)
	{
		for(size_t j=0 ; j<B.cols ; j++)
			for(size_t l=0 ; l<cols ; l++)
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
	
	for(size_t i=0 ; i<rows*cols ; i++)
	{
		if (matrix[i] != B.matrix[i])
		{
			return false;
		}
	}
	
	return true;
}

// check if two vectors are not equal.
bool Matrix::operator !=(const Matrix& B) const
{
	assert(B.matrix && B.rows>=0 && B.cols>=0);
	assert(rows==B.rows && cols==B.cols);
	
	for(size_t i=0 ; i<rows*cols ; i++)
	{
		if (matrix[i] != B.matrix[i])
		{
			return true;
		}
	}
	
	return false;
}

// check equivalence of two matrices.
bool Matrix::IsEqual(const Matrix& B, double tolerance) const
{
	assert(B.matrix && B.rows>=0 && B.cols>=0);
	assert(rows==B.rows && cols==B.cols);
	
	for(size_t i=0 ; i<rows*cols ; i++)
	{
		if(!glCompareDouble(matrix[i], B.matrix[i], tolerance, tolerance) )
		{
			return false;
		}
	}
	
	return true;
}

// check equivalence of two matrices.
bool Matrix::IsNotEqual(const Matrix& B, double tolerance)	const
{
	return !this->IsEqual(B, tolerance);
}
// ------------------------------------------------------------------------- //




// FUNCTIONS.
// ------------------------------------------------------------------------- //

// set submatrix of a matrix.
void Matrix::SetSubMatrix(size_t r1, size_t c1, size_t r2, size_t c2, const Matrix &B)
{
	assert(r1>=0 && r2<rows && c1>=0 && c2<cols);
	
	size_t x = 0, y = 0;
	for(size_t i=r1 ; i<=r2 ; i++)
	{
		y = 0;
		for(size_t j=c1 ; j<=c2 ; j++)
		{
			matrix[i*cols+j] = B.matrix[x*B.cols+y];
			y++;
		}
		x++;
	}
}

// set a row of the matrix.
void Matrix::SetRow(size_t r, const Matrix &B)
{
	assert(r>=0 && r<rows);
	
	for (size_t j = 0; j <= cols; j++)
	{
		matrix[r * cols + j] = B.matrix[j];
	}
}

// set a col of the matrix.
void Matrix::SetCol(size_t c, const Matrix &B)
{
	assert(c>=0 && c<cols);
	
	for (size_t i = 0; i <= rows; i++)
	{
		matrix[i * cols + c] = B.matrix[i];
	}
}

// Transpose of a matrix
Matrix Matrix::Transpose() const
{
	assert(matrix);
	
	Matrix temp(cols,rows);
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			temp.matrix[j * rows + i] = this->matrix[i * cols + j];
		}
	}
	return temp;
}

// average elements in a row and return average vector.
Matrix Matrix::AvgRows() const
{
	Matrix avg(rows, 1);
	
	for(size_t i=0 ; i<rows ; i++)
	{
		for(size_t j=0 ; j<cols ; j++)
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
	if (rows != 1 && cols != 1)
	{
		return -1;
	}
	
	if (rows == 1 && cols == 1)
	{
		return matrix[0];
	}
	
	double norm = 0;
	for (size_t i = 0; i < rows + cols - 1; i++)
	{
		norm += matrix[i] * matrix[i];
	}
	
	return sqrt(norm);
}

// compute square of 2-norm of the vector.
double Matrix::VectorNorm2()
{
	// must be a vector.
	if (rows != 1 && cols != 1)
	{
		return -1;
	}
	
	if (rows == 1 && cols == 1)
	{
		return matrix[0];
	}
	
	double norm = 0;
	for (size_t i = 0; i < rows + cols - 1; i++)
	{
		norm += matrix[i] * matrix[i];
	}
	
	return norm;
}

Matrix Matrix::Diagonal() const
{
	assert(rows == cols);
	Matrix _diagonal(rows, 1);
	for(size_t i=0 ; i<rows ; ++i)
	{
		_diagonal.matrix[i] = matrix[i*cols+i];
	}
	return _diagonal;
}

// Find Inverse of a square matrix.
Matrix Matrix::Inverse() const
{
	assert(rows>0 && cols>0 && rows==cols);
	
	double* _buffer = new double[rows * cols];
	memcpy(_buffer, matrix, rows * cols * sizeof(double));

	typedef  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatrixXd;
	Eigen::Map<MatrixXd> _map(_buffer, rows, cols);
	_map = _map.inverse();

	Matrix _inverse(rows, cols);
	_inverse.matrix = _buffer;
	return _inverse;
}

// finds SVD of a matrix.
Matrix Matrix::Svd(Matrix* S, Matrix* V) const
{
	typedef  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatrixXd;
	Eigen::Map<MatrixXd> _map(matrix, rows, cols);

	Eigen::BDCSVD<MatrixXd> _results = _map.bdcSvd(Eigen::ComputeFullU | Eigen::ComputeFullV);
	const Eigen::MatrixXd&     _U       = _results.matrixU();
	const Eigen::VectorXd&     _S       = _results.singularValues();
	const Eigen::MatrixXd&     _V       = _results.matrixV();

	Matrix U(size_t(_U.rows()), size_t(_U.cols()), _U.data());
	*S = Matrix(size_t(_S.rows()), size_t(_S.cols()), _S.data());
	*V = Matrix(size_t(_V.rows()), size_t(_V.cols()), _V.data());
	return U;
}

// return Determinant of matrix.
double Matrix::Determinant() const
{
	typedef  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatrixXd;
	Eigen::Map<MatrixXd> _map(matrix, rows, cols);
	return _map.determinant();
}
// ------------------------------------------------------------------------- //


// ------------------------------------------------------------------------- //
Matrix Matrix::SolveAxB(const Matrix& A, const Matrix& B)
{
	typedef  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatrixXd;
	Eigen::Map<MatrixXd> _A(A.matrix, A.rows, A.cols);
	Eigen::Map<MatrixXd> _B(B.matrix, B.rows, B.cols);

	const Eigen::MatrixXd& _X = _A.partialPivLu().solve(_B);

	//const Eigen::MatrixXd& _X = _A.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(_B);
	return Matrix(size_t(_X.rows()), size_t(_X.cols()), _X.data());
}
// ------------------------------------------------------------------------- //


// ------------------------------------------------------------------------- //
// for standard IO.
std::ostream& operator <<(std::ostream& out, const Matrix &B)
{
	if ((B.rows == 0 && B.cols == 0) || B.matrix == nullptr)
	{
		out << "Null Matrix";
	}
	
	out << B.rows << " " << B.cols;
	for(size_t i=0 ; i<B.rows ; i++)
	{
		out << std::endl;
		
		for (size_t j = 0; j < B.cols; j++)
		{
			out << B(i, j) << " ";
		}
	}
	return out;
}

std::istream& operator >>(std::istream& in, Matrix &B)
{
//	assert(B.rows!=0 && B.cols!=0 && B.matrix!=NULL);
	
	size_t r, c;
	in >> r >> c;
	B = Matrix(r, c);
	
	for (size_t i = 0; i < B.rows; i++)
	{
		for (size_t j = 0; j < B.cols; j++)
		{
			in >> B(i, j);
		}
	}
	return in;
}
// ------------------------------------------------------------------------- //


// ------------------------------------------------------------------------- //
void Matrix::Write(std::ostream& out) const
{
	if ((rows == 0 && cols == 0) || matrix == nullptr)
	{
		out << "Null Matrix";
	}
	
	out << rows << " " << cols;
	for(size_t i=0 ; i<rows ; i++)
	{
		out << std::endl;
		
		for (size_t j = 0; j < cols; j++)
		{
			out << (*this)(i, j) << " ";
		}
	}
}

void Matrix::Read(std::istream& in)
{
	size_t r, c;
	in >> r >> c;
	*this = Matrix(r, c);
	
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			in >> (*this)(i, j);
		}
	}
}
// ------------------------------------------------------------------------- //

};	// End namespace SMathLib.
