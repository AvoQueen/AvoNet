#include "AvoNet.h"
#include <vector>

AvoNet::AvoNet(int* layers, int amt)
{
	if (amt < 2)
	{
		printf("There need to be at least 2 layeres (input and output)!");
		/*
			Initialize as 'empty'
		*/
		nWeights = 0;
		nBias = 0;
		inputs = 0;
		outputs = 0;
		learningRate = 0;
		mWeights = new QMatrix[0];
		mBias = new QMatrix[0];

		//exit the constructor
		return;
	}

	nWeights = amt - 1;
	nBias = amt - 1;
	inputs = layers[0];
	outputs = layers[amt - 1];

	mWeights = new QMatrix[nWeights];
	mBias = new QMatrix[nBias];

	for (int i = 0; i < amt - 1; i++)
	{
		double range = 1.0 / sqrt(layers[i]);
		mWeights[i] = QMatrix(layers[i + 1], layers[i], -range, range);
		mBias[i] = QMatrix(layers[i + 1], 1, -range, range);
	}

	//Setting standards for the beginning
	learningRate = 0.05;
	ActivationFunctions activation(ActivationFunctions::sigmoid);
}

QMatrix AvoNet::fwPropagation(QMatrix input)
{
	QMatrix O = input;
	for (int i = 0; i < nWeights; i++)
	{
		O = activation((mWeights[i] * O) + mBias[i]);
	}
	return O;
}

void AvoNet::bwPropagation(QMatrix I, QMatrix R)
{
	std::vector<QMatrix> outputs; //list of outputs
	outputs.resize(nWeights + 1); //set the size to the amount of layers

	outputs[0] = I; //set the first element

	//forward propagation
	for (int i = 0; i < nWeights; i++)
	{
		outputs[i + 1] = activation((mWeights[i] * outputs[i]) + mBias[i]); //fill the list with all outputs
	}

	QMatrix O_k; //value of next layer
	QMatrix O_j_T; //value of previous layer (transposed)
	QMatrix E; // Error

	//backward propagation
	for (int i = nWeights; i > 0; i--) //iterate from left to right
	{
		O_k		= outputs[i];
		O_j_T	= outputs[i - 1].transpose();

		if (i == nWeights)
			E = R - O_k;
		else
			E = mWeights[i].transpose() * E;
		
		QMatrix dB = learningRate * E * O_k * (1 - O_k);
		QMatrix dW = dB * O_j_T;

		//update weights
		mWeights[i - 1] = mWeights[i - 1] + dW;
		mBias[i - 1] = mBias[i - 1] + dB;
	}
}