#pragma once
class Matrix
{
private:
	int** data;
	int rows;
	int cols;

	void copyFrom(const Matrix& other);
	void free();

public:
	Matrix(int rows, int cols);
	Matrix(const Matrix& other);
	Matrix& operator=(const Matrix& other);
	~Matrix();

	void setValue(int rows, int cols, int value);
	void printMatrix();
};

