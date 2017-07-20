
#ifndef _SMATHLIB_MATRIX_H_
#define _SMATHLIB_MATRIX_H_

#include "SMathLib/Config.h"
#include <iostream>

namespace SMathLib {
;

// Some constants used to define matrix type.
const int M_NULL      = 0;
const int M_SQRMATRIX = 1;
const int M_ROWVECTOR = 2;
const int M_COLVECTOR = 3;
const int M_ZEROS     = 4;
const int M_ONES      = 5;
const int M_RAND      = 6;
const int M_EYE       = 7;

class SMATHLIB_DLL_API Matrix
{
	// for standard IO.
	SMATHLIB_DLL_API friend std::ostream& operator <<(std::ostream& out, const Matrix &B);
	SMATHLIB_DLL_API friend std::istream& operator >>(std::istream& in , Matrix &B);
	
public:
	
	// IO functions.
	void Write(std::ostream& out) const;
	void Read(std::istream& in);
	//void WriteBin(std::ostream& out) const;
	//void ReadBin(std::istream& in);
	
	// Functions.
	//double	Determinant() const;
	//Matrix  Svd(Matrix *sigma, Matrix *v) const;
	//Matrix  Inverse() const;
	Matrix  EigValsSymMat();
	Matrix	Transpose() const;
	Matrix  AvgRows() const;
	void    SetSubMatrix(int r1, int c1, int r2, int c2, const Matrix &B);
	void    SetRow(int r, const Matrix &B);
	void    SetCol(int c, const Matrix &B);
	double  VectorNorm();
	double  VectorNorm2();
	
	// Static functions.
	//static Matrix SolveAxB(const Matrix& A, const Matrix& B);
	
	// Logical operators.
	bool operator ==(const Matrix& B) const;
	bool operator !=(const Matrix& B) const;
	bool IsEqual(const Matrix& B, double tolerance) const;
	bool IsNotEqual(const Matrix& B, double tolerance) const;
	
	// Arithmetic operators.
	Matrix  operator +(const Matrix& B) const;
	Matrix  operator -(const Matrix& B) const;
	Matrix  operator *(const Matrix& B) const;
	Matrix  operator *(double s) const;
	Matrix  operator /(double s) const;
	Matrix& operator +=(const Matrix& B);
	Matrix& operator -=(const Matrix& B);
	Matrix& operator *=(const Matrix& B);
	Matrix& operator *=(double s);
	Matrix& operator /=(double s);
	
	
	// ------------------------------------------------------------
	//  Assignment, indexing and casting operators.
	Matrix& operator =(const Matrix& B);
	double& operator ()(int r, int c) const;
	double& operator [](int index) const;
	Matrix operator ()(int r1, int c1, int r2, int c2) const;
	// ------------------------------------------------------------
	
	
	// ------------------------------------------------------------
	// Constructors and destructor.
	Matrix();
	Matrix(int r, int c, int type = M_ZEROS);
	Matrix(int r, int c, double* data);
	Matrix(const Matrix& B);
	virtual ~Matrix();
	
	// Variables.
	int     rows;		// number of rows in matrix.
	int     cols;		// number of cols in matrix.
	int     matType;	// M_SQRMATRIX, M_ROWVECTOR, M_COLVECTOR.
	double* matrix;		// array storing matrix.
};

};	// End namespace SMathLib.

#endif // _SMATHLIB_MATRIX_H_
