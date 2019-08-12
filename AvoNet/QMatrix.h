#pragma once

#ifndef QMATRIX_H
#define QMATRIX_H

#include <iostream>

	class QMatrix
	{
	public:
		QMatrix();
		QMatrix(int r, int c);
		QMatrix(int r, int c, double fill);
		QMatrix(int r, int c, int min, int max);
		QMatrix(int r, int c, double min, double max);
		QMatrix(double* data, bool isVector = std_ConvertToVector);
		QMatrix(double** data);

		QMatrix copy();

		static QMatrix getIdentity(int r, int c);
		void setIdentity(void);
		QMatrix identity();

		virtual ~QMatrix();

		int getRows();
		int getCols();

		void fill(double value);

		QMatrix map(double (*func)(double));

		void log();

		bool sameDimensions(QMatrix& other);
		bool equals(QMatrix& other);

		void setData(double** d);
		void setData(int row, int col, double value);
		//WIP
		void setRow(int row, double* data);
		void setColumn(int column, double* data);

		double getData(int row, int col);
		double** getData();
		//WIP
		double* getRow(int row);
		double* getColumn(int column);

		//basic matrix-arithmetic
		QMatrix operator + (QMatrix mat2);
		QMatrix operator += (QMatrix& mat2);
		QMatrix add(QMatrix mat2);
		QMatrix operator + (double num);
		QMatrix operator += (double num);
		QMatrix add(double num);
		friend QMatrix operator + (double num, QMatrix mat2);

		QMatrix operator - ();
		QMatrix operator - (QMatrix mat2);
		QMatrix operator -= (QMatrix& mat2);
		QMatrix sub(QMatrix mat2);
		QMatrix operator - (double num);
		QMatrix operator -= (double num);
		QMatrix sub(double num);
		friend QMatrix operator - (double num, QMatrix mat2);

		QMatrix operator * (QMatrix mat2);
		QMatrix operator *= (QMatrix& mat2);
		QMatrix mul(QMatrix mat2);
		QMatrix operator * (double num);
		QMatrix operator *= (double num);
		QMatrix mul(double num);
		friend QMatrix operator * (double num, QMatrix mat2);

		//WIP
		QMatrix operator ^(int num);

		double* operator[](int row);
		
		bool operator==(QMatrix mat2);
		bool operator!=(QMatrix mat2);


		double arraymult_add(double* a1, double* a2, int size);
		QMatrix transpose_1D();
		QMatrix transpose();

		double sum();

		static bool std_ConvertToVector;

	protected:

	private:
		int cols;
		int rows;
		double** data;
	};
#endif // QMATRIX_H

