#include "QMatrix.h"
#include <stdlib.h>

bool QMatrix::std_ConvertToVector = true;

	QMatrix::QMatrix() {}

	QMatrix::QMatrix(int r, int c) : cols(c), rows(r) {
		data = new double* [r];
		for (int i = 0; i < r; i++)
		{
			data[i] = new double[c] {};
		}
	}

	QMatrix::QMatrix(int r, int c, double fill) : cols(c), rows(r) {
		data = new double* [r];
		for (int i = 0; i < r; i++)
		{
			data[i] = new double[c] {};
			for (int j = 0; j < c; j++)
			{
				data[i][j] = fill;
			}
		}
	}

	QMatrix::QMatrix(int r, int c, double min, double max) : cols(c), rows(r) {
		data = new double* [r];
		for (int i = 0; i < r; i++)
		{
			data[i] = new double[c] {};
			for (int j = 0; j < c; j++)
			{
				data[i][j] = (double) rand() / RAND_MAX * (max - min) + min;
			}
		}
	}

	QMatrix::QMatrix(int r, int c, int min, int max) : cols(c), rows(r) {
		data = new double* [r];
		for (int i = 0; i < r; i++)
		{
			data[i] = new double[c] {};
			for (int j = 0; j < c; j++)
			{
				data[i][j] = (int)(((double) rand() / RAND_MAX) * ((double) max - min + 0.3) + min); //+0.3 to add a chance to get the max value
			}
		}
	}

	QMatrix::QMatrix(double* d, bool vector)
	{
		if (vector)
		{
			cols = 1;
			rows = sizeof(*d) / sizeof(d);
			data = new double* [rows];
			for (int i = 0; i < rows; i++) 
			{
				data[i] = new double[1];
				data[i][0] = d[i];
			}
		}
		else {
			rows = 1;
			cols = sizeof(*d) / sizeof(d);
			data = new double* [1];
			data[0] = d;
		}
	}

	QMatrix::QMatrix(double** d)
	{
		rows = sizeof(**d) / sizeof(*d);
		cols = sizeof(*d) / sizeof(d);

		data = new double* [rows];
		for (int i = 0; i < rows; i++)
		{
			data[i] = d[i];
		}
	}

	QMatrix QMatrix::copy()
	{
		return QMatrix(data);
	}

	QMatrix QMatrix::getIdentity(int r, int c)
	{
		QMatrix result(r, c);
		result.setIdentity();
		return result;
	}

	void QMatrix::setIdentity(void)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				data[i][j] = (i == j) ? 1.0 : 0.0;
			}
		}
	}

	QMatrix QMatrix::identity()
	{
		return QMatrix::getIdentity(rows, cols);
	}

	QMatrix::~QMatrix() {
		//std::cout << "Matrix has been deleted?" << std::endl;
	}

	int QMatrix::getRows()
	{
		return rows;
	}

	int QMatrix::getCols()
	{
		return cols;
	}

	void QMatrix::fill(double value)
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				data[i][j] = value;
	}

	QMatrix QMatrix::map(double (*func)(double))
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				data[i][j] = func(data[i][j]);
			}
		}
		return *this;
	}

	void QMatrix::log()
	{
		std::cout << std::endl;
		for (int i = 0; i < rows; i++)
		{
			std::cout << "[ ";
			for (int j = 0; j < cols; j++)
			{
				std::cout << data[i][j] << " ";
			}
			std::cout << "]" << std::endl;
		}
	}

	bool QMatrix::sameDimensions(QMatrix& other)
	{
		return (rows == other.getRows() && cols == other.getCols());
	}

	//TODO: Add a hash-variant
	bool QMatrix::equals(QMatrix& other)
	{
		if(!sameDimensions(other))
			return false;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (data[i][j] != other.getData(i, j))
					return false;
			}
		}
		return true;
	}

	void QMatrix::setData(double** d)
	{
		data = d;
	}

	void QMatrix::setData(int row, int col, double value)
	{
		data[row][col] = value;
	}

	double QMatrix::getData(int row, int col)
	{
		return data[row][col];
	}

	double** QMatrix::getData()
	{
		return data;
	}

	QMatrix QMatrix::operator + (QMatrix mat2)
	{
		QMatrix result(rows, cols);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				result.setData(i, j, data[i][j] + mat2.getData(i, j));
			}
		}
		return result;
	}

	QMatrix QMatrix::operator += (QMatrix& mat2)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				data[i][j] += mat2.getData(i, j);
			}
		}
		return *this;
	}

	QMatrix QMatrix::add(QMatrix mat2)
	{
		return *this + mat2;
	}

	QMatrix QMatrix::operator + (double num)
	{
		QMatrix result(rows, cols);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				result.setData(i, j, data[i][j] + num);
			}
		}
		return result;
	}

	QMatrix QMatrix::operator += (double num)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				data[i][j] += num;
			}
		}
		return *this;
	}

	QMatrix QMatrix::add(double num)
	{
		return *this + num;
	}

	QMatrix operator+(double num, QMatrix mat2)
	{
		return mat2 + num;
	}

	QMatrix QMatrix::operator-()
	{
		QMatrix result(rows, cols);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				result.setData(i, j, -data[i][j]);
			}
		}
		return result;
	}

	QMatrix QMatrix::operator - (QMatrix mat2)
	{
		QMatrix result(rows, cols);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				result.setData(i, j, data[i][j] - mat2.getData(i, j));
			}
		}
		return result;
	}

	QMatrix QMatrix::operator -= (QMatrix& mat2)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				data[i][j] -= mat2.getData(i, j);
			}
		}
		return *this;
	}

	QMatrix QMatrix::sub(QMatrix mat2)
	{
		return *this - mat2;
	}

	QMatrix QMatrix::operator - (double num)
	{
		QMatrix result(rows, cols);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				result.setData(i, j, data[i][j] - num);
			}
		}
		return result;
	}

	QMatrix QMatrix::operator -= (double num)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				data[i][j] -= num;
			}
		}
		return *this;
	}

	QMatrix QMatrix::sub(double num)
	{
		return *this - num;
	}

	QMatrix operator-(double num, QMatrix mat2)
	{
		return -mat2 + num;
	}

	QMatrix QMatrix::operator * (QMatrix mat2)
	{
		int mat2_cols = mat2.getCols();

		QMatrix result(rows, mat2_cols);
		double cbuffer = 0.0;

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < mat2_cols; j++)
			{
				for (int c = 0; c < cols; c++)
				{
					cbuffer += data[i][c] * mat2.getData(c, j);
				}
				result.setData(i, j, cbuffer);
				cbuffer = 0.0;
			}
		}
		return result;
	}

	QMatrix QMatrix::operator *= (QMatrix& mat2)
	{
		int mat2_cols = mat2.getCols();

		QMatrix result(rows, mat2_cols);
		double cbuffer = 0.0;

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < mat2_cols; j++)
			{
				for (int c = 0; c < cols; c++)
				{
					cbuffer += data[i][c] * mat2.getData(c, j);
				}
				result.setData(i, j, cbuffer);
				cbuffer = 0.0;
			}
		}
		*this = result;
		return *this;
	}

	QMatrix QMatrix::mul(QMatrix mat2)
	{
		return *this * mat2;
	}

	QMatrix QMatrix::operator * (double num)
	{
		QMatrix result(rows, cols);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				result.setData(i, j, data[i][j] * num);
			}
		}
		return result;
	}

	QMatrix QMatrix::operator *= (double num)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				data[i][j] *= num;
			}
		}
		return *this;
	}

	QMatrix QMatrix::mul(double num)
	{
		return *this * num;
	}

	QMatrix operator*(double num, QMatrix mat2)
	{
		return mat2 * num;
	}

	QMatrix QMatrix::operator^(int num)
	{
		QMatrix result;

		if (num < 0)
		{
			printf("exponent has to be greater than 0");
			return *this;
		}
		else if (num == 0)
		{
			return getIdentity(rows, cols);
		}
		else if (num == 1)
		{
			return *this;
		}

		for (int i = 0; i < num; i++)
		{
			if (i == 0)
				result = *this * *this;
			else
				result = result * result;
		}
		return result;
	}

	double* QMatrix::operator[](int row)
	{
		return data[row];
	}

	bool QMatrix::operator==(QMatrix mat2)
	{
		if(!sameDimensions(mat2))
			return false;
		for (int i = 0; i < rows; i++)
			for (int j = 0; i < cols; j++)
				if (data[i][j] != mat2[i][j])
					return false;
		return true;
	}

	bool QMatrix::operator!=(QMatrix mat2)
	{
		if (!sameDimensions(mat2))
			return true;
		for (int i = 0; i < rows; i++)
			for (int j = 0; i < cols; j++)
				if (data[i][j] != mat2[i][j])
					return true;
		return false;
	}

	double QMatrix::arraymult_add(double* a1, double* a2, int size)
	{
		double result = 0.0;
		for (int i = 0; i < size; i++)
		{
			result += a1[i] * a2[i];
		}
		return result;
	}

	QMatrix QMatrix::transpose_1D()
	{
		QMatrix result(1, rows);
		for (int i = 0; i < rows; i++)
		{
			result.setData(0, i, data[i][0]);
		}
		return result;
	}

	QMatrix QMatrix::transpose()
	{
		QMatrix result(cols, rows);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				result.setData(j, i, data[i][j]);
			}
		}
		return result;
	}

	double QMatrix::sum()
	{
		double result = 0.0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				result += data[i][j];
			}
		}
		return result;
	}
