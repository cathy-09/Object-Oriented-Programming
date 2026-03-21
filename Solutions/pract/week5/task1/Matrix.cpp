#include "Matrix.h"
#include <iostream>

void Matrix::copyFrom(const Matrix& other)
{
	this->rows = other.rows;
	this->cols = other.cols;

	data = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		data[i] = new int[cols];
		for (int j = 0; j < cols; j++)
		{
			data[i][j] = other.data[i][j];
		}
	}
}

void Matrix::free()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] data[i];
	}
	delete[] data;
}

Matrix::Matrix(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;

	data = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		data[i] = new int[cols] {0};
	}
}

Matrix::Matrix(const Matrix& other)
{
	copyFrom(other);
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Matrix::~Matrix()
{
	free();
}

void Matrix::setValue(int rows, int cols, int value)
{
	if (rows > this->rows || cols > this->cols)
	{
		return;
	}
	data[rows][cols] = value;
}

void Matrix::printMatrix()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << data[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

