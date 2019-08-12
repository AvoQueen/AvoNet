#include "ActivationFunctions.h"
#include <cmath>


ActivationFunctions::ActivationFunctions(vFunctionCall f)
{
	function = f;
}

ActivationFunctions::ActivationFunctions()
{
	function = sigmoid; //standard function
}

double ActivationFunctions::uniformDistribution = 1.0;

double ActivationFunctions::sigmoid(double x)
{
	return 1.0 / (1.0 + exp(-x));
}

double ActivationFunctions::binaryStep(double x)
{
	return (x >= 0) ? 1.0 : 0.0;
}

double ActivationFunctions::tanH(double x)
{
	return tanh(x);
}

double ActivationFunctions::arcTan(double x)
{
	return atan(x);
}

double ActivationFunctions::arSinH(double x)
{
	return asinh(x);
}

double ActivationFunctions::isru(double x)
{
	return x / sqrt(1 + uniformDistribution * x * x);
}

double ActivationFunctions::isrlu(double x)
{
	return (x < 0) ? isru(x) : x;
}

double ActivationFunctions::sqnl(double x)
{
	return (x < 0) ? 
		((x < 2) ?
			x - x * x / 4 :
			1) : 
		((x < -2) ?
			-1 :
			x + x * x / 4);
}
