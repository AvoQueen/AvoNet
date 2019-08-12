#pragma once
#ifndef ACTIVATIONFUNCTIONS_H
#define ACTIVATIONFUNCTIONS_H

#include "QMatrix.h"

typedef double (*vFunctionCall)(double x);


class ActivationFunctions
{
public:
	ActivationFunctions(vFunctionCall activeFunction);
	ActivationFunctions();

	static double sigmoid(double x);
	static double binaryStep(double x);
	static double tanH(double x);
	static double arcTan(double x);
	static double arSinH(double x);
	static double isru(double x);
	static double isrlu(double x);
	static double sqnl(double x);
	static double uniformDistribution;

	QMatrix operator()(QMatrix mat)
	{
		return mat.map(function);
	}

private:
	vFunctionCall function;
};

#endif // ACTIVATIONFUNCTIONS_H