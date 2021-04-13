// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SMATHLIB_MATRIX_H_
#define _SMATHLIB_MATRIX_H_

#include "SMathLib/Config.h"
#include <iostream>

namespace SMathLib {
;

// Define the matrix type.
enum class MatrixType
{
	Null         = 0,
	Square       = 1,
	RowVector    = 2,
	ColumnVector = 3,
	Zero         = 4,
	Ones         = 5,
	Random       = 6,
	Identity     = 7
};


class SMATHLIB_DLL_API Matrix
{
	// for standard IO.
	SMATHLIB_DLL_API friend std::ostream& operator <<(std::ostream& out, const Matrix &B);
	SMATHLIB_DLL_API friend std::istream& operator >>(std::istream& in , Matrix &B);
	
public:
	
	// IO functions.
	void Write(std::ostream& out) const;
	void Read(std::istream& in);
	
	// Functions.
	double	Determinant() const;
	Matrix  Svd(Matrix* sigma, Matrix* v) const;
	Matrix  Inverse() const;
	Matrix	Transpose() const;
	Matrix  AvgRows() const;
	void    SetSubMatrix(size_t r1, size_t c1, size_t r2, size_t c2, const Matrix &B);
	void    SetRow(size_t r, const Matrix &B);
	void    SetCol(size_t c, const Matrix &B);
	double  VectorNorm();
	double  VectorNorm2();
	Matrix  Diagonal() const;
	
	// Static functions.
	static Matrix SolveAxB(const Matrix& A, const Matrix& b);
	
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
	double& operator ()(size_t r, size_t c) const;
	double& operator [](size_t index) const;
	Matrix operator ()(size_t r1, size_t c1, size_t r2, size_t c2) const;
	// ------------------------------------------------------------
	
	
	// ------------------------------------------------------------
	// Constructors and destructor.
	Matrix();
	Matrix(size_t r, size_t c, MatrixType type = MatrixType::Zero);
	Matrix(size_t r, size_t c, const double* data);
	Matrix(const Matrix& B);
	virtual ~Matrix();
	
	// Variables.
	size_t     rows;    // number of rows in matrix.
	size_t     cols;    // number of cols in matrix.
	MatrixType matType; // M_SQRMATRIX, M_ROWVECTOR, M_COLVECTOR.
	double*    matrix;  // array storing matrix.
};

};	// End namespace SMathLib.

#endif // _SMATHLIB_MATRIX_H_
