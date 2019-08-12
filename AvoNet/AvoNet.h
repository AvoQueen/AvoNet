#pragma once

#ifndef AVONET_H
#define AVONET_H

#include "QMatrix.h"
#include "ActivationFunctions.h"

enum availableFunctions {
	SIGMOID,
	BINARY_STEP,
	TAN_H,
	ARC_TAN,
	AR_SIN_H,
	ISRU,
	ISRLU,
	SQNL
};

class AvoNet
{
public:
	AvoNet(int* layeres, int amountOfLayeres);
	QMatrix fwPropagation(QMatrix input);
	void bwPropagation(QMatrix input, QMatrix result);

private:
	int inputs;
	int outputs;
	int nWeights;
	int nBias;
	QMatrix* mWeights;
	QMatrix* mBias;
	double learningRate;
	ActivationFunctions activation;
};

#endif // AVONET_H