#pragma once
#ifndef AVOCNN_H
#define AVOCNN_H


class AvoCNN
{
public:
	AvoCNN();

	//core-functions of a cnn
	void convolute();
	void ReLU();
	void pool();

protected:
private:
};

#endif // AVOCNN_H