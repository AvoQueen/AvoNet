#pragma once
#include <iostream>
#include <random>
#include <ctime>

namespace rs {

	typedef unsigned int uint;

	template<class T>
	class Raster
	{
	public: //constructor and destructor
		Raster(uint rows, uint cols);
		virtual ~Raster();

	public: //Operator overloading
		T& operator()(uint row, uint col) const;
		T& operator[](uint index) const;

		Raster<T> operator+(const Raster<T>& raster) const;
		Raster<T> operator+(const T& elem) const;
		void operator+=(Raster<T>& raster);
		void operator+=(const T& elem);

		Raster<T> operator-(const Raster<T>& raster) const;
		Raster<T> operator-(const T& elem) const;
		void operator-=(Raster<T>& raster);
		void operator-=(const T& elem);

		Raster<T> operator/(const Raster<T>& raster) const;
		Raster<T> operator/(const T& elem) const;
		void operator/=(Raster<T>& raster);
		void operator/=(const T& elem);

	public: //begin- and end-pointer
		T* begin();
		T* end();

	public: //utility functions
		const Raster<T>& fill(T fill);
		void print() const;

	public: //static utility functions
		static Raster<T> Identity(uint rows, uint cols);
		static Raster<T> Random(uint rows, uint cols);
		static Raster<T> Rotation2D(double radians);
		static void refreshRandomSeed();

	private:
		T* pData;
		uint rows;
		uint cols;
	};

	template<class T>
	inline Raster<T>::Raster(uint rows, uint cols)
		: rows(rows), cols(cols)
	{
		pData = new T[rows * cols];
	}

	template<class T>
	inline Raster<T>::~Raster()
	{
		delete[] pData;
	}

	template<class T>
	inline T& Raster<T>::operator()(uint row, uint col) const
	{
		return pData[row * cols + cols];
	}

	template<class T>
	inline T& Raster<T>::operator[](uint index) const
	{
		return pData[index];
	}

	template<class T>
	inline Raster<T> Raster<T>::operator+(const Raster<T>& raster) const
	{
		Raster<T> result(rows, cols);
		for (uint i = 0; i < rows * cols; i++)
		{
			result[i] = pData[i] + raster[i];
		}
		return result;
	}

	template<class T>
	inline Raster<T> Raster<T>::operator+(const T& elem) const
	{
		Raster<T> result(rows, cols);
		for (uint i = 0; i < rows * cols; i++)
		{
			result[i] = pData[i] + elem;
		}
		return result;
	}

	template<class T>
	inline void Raster<T>::operator+=(Raster<T>& raster)
	{
		for (uint i = 0; i < rows * cols; i++)
		{
			pData[i] += raster[i];
		}
	}

	template<class T>
	inline void Raster<T>::operator+=(const T& elem)
	{
		for (uint i = 0; i < rows * cols; i++)
		{
			pData[i] += elem;
		}
	}

	template<class T>
	inline Raster<T> Raster<T>::operator-(const Raster<T>& raster) const
	{
		Raster<T> result(rows, cols);
		for (uint i = 0; i < rows * cols; i++)
		{
			result[i] = pData[i] - raster[i];
		}
		return result;
	}

	template<class T>
	inline Raster<T> Raster<T>::operator-(const T& elem) const
	{
		Raster<T> result(rows, cols);
		for (uint i = 0; i < rows * cols; i++)
		{
			result[i] = pData[i] - elem;
		}
		return result;
	}

	template<class T>
	inline void Raster<T>::operator-=(Raster<T>& raster)
	{
		for (uint i = 0; i < rows * cols; i++)
		{
			pData[i] -= raster[i];
		}
	}

	template<class T>
	inline void Raster<T>::operator-=(const T& elem)
	{
		for (uint i = 0; i < rows * cols; i++)
		{
			pData[i] -= elem;
		}
	}

	template<class T>
	inline Raster<T> Raster<T>::operator/(const Raster<T>& raster) const
	{
		Raster<T> result(rows, cols);
		for (uint i = 0; i < rows * cols; i++)
		{
			result[i] = pData[i] / raster[i];
		}
		return result;
	}

	template<class T>
	inline Raster<T> Raster<T>::operator/(const T& elem) const
	{
		Raster<T> result(rows, cols);
		for (uint i = 0; i < rows * cols; i++)
		{
			result[i] = pData[i] / elem;
		}
		return result;
	}

	template<class T>
	inline void Raster<T>::operator/=(Raster<T>& raster)
	{
		for (uint i = 0; i < rows * cols; i++)
		{
			pData[i] /= raster[i];
		}
	}

	template<class T>
	inline void Raster<T>::operator/=(const T& elem)
	{
		for (uint i = 0; i < rows * cols; i++)
		{
			pData[i] /= elem;
		}
	}

	template<class T>
	inline  T* Raster<T>::begin()
	{
		return pData;
	}

	template<class T>
	inline T* Raster<T>::end()
	{
		return pData + (rows * cols);
	}

	template<class T>
	inline const Raster<T>& Raster<T>::fill(T fill)
	{
		for (uint i = 0; i < rows * cols; i++)
		{
			pData[i] = fill;
		}
		return *this;
	}

	template<class T>
	void Raster<T>::print() const
	{
		for (uint i = 0; i < rows; i++)
		{
			std::cout << "[ ";
			for (uint j = 0; j < cols; j++)
			{
				std::cout << pData[i * cols + j] << " ";
			}
			std::cout << "]" << std::endl;
		}
	}

	template<class T>
	inline Raster<T> Raster<T>::Identity(uint rows, uint cols)
	{
		Raster<T> result(rows, cols);
		for (uint i = 0; i < rows * cols; i++)
			result[i] = (i % (cols + 1) == 0) ? 1 : 0;
		return result;
	}

	template<class T>
	inline Raster<T> Raster<T>::Random(uint rows, uint cols)
	{
		Raster<T> result(rows, cols);
		for (T* t = result.begin(); t != result.end(); t++)
			*t = rand();
		return result;
	}

	template<class T>
	inline Raster<T> Raster<T>::Rotation2D(double radians)
	{
		Raster<T> result(2, 2);
		result[0] = cos(radians);
		result[1] = -sin(radians);
		result[2] = sin(radians);
		result[3] = cos(radians);
		return result;
	}

	template<class T>
	inline void Raster<T>::refreshRandomSeed()
	{
		srand((uint)std::time(0));
	}

	typedef Raster<int> iRaster;
	typedef Raster<float> fRaster;
	typedef Raster<double> dRaster;
}