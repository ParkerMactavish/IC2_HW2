#include "Matrix.h"
#include <iostream>

using namespace std;

void Matrix::setUp(int row, int col)//set up the row and col number, and altogether set up a matrix of size row * col
{
	this->row = row;
	this->col = col;
	data = new double*[row];
	for (int rowCnt = 0; rowCnt<row; rowCnt++)
	{
		data[rowCnt] = new double[col];
	}
}

Matrix::Matrix()//set up the simpliest matrix with a 2*2 size and all 0's in content
{
	setUp(2, 2);
	for (int rowCnt = 0; rowCnt<row; rowCnt++)
		for (int colCnt = 0; colCnt<col; colCnt++)
			setData(rowCnt, colCnt, 0);
		
	count++;
}

Matrix::Matrix(int row, int col)//set up a simple matrix with a row*col size and all 0's in content
{
	setUp(row, col);
	for (int rowCnt = 0; rowCnt<row; rowCnt++)
		for (int colCnt = 0; colCnt<col; colCnt++)
			setData(rowCnt, colCnt, 0);
		
	count++;
}

Matrix::Matrix(int row, int col, double data[], int length)//set up a 2d matrix with a 1d array with row*col size
{
	if (length != row*col) cout << "Error:The length of the one-dimentional array is wrong.";
	else
	{
		setUp(row, col);
		for (int rowCnt = 0; rowCnt < row; rowCnt++)
			for (int colCnt = 0; colCnt < col; colCnt++)
				setData(rowCnt, colCnt, data[rowCnt*col + colCnt]);
			
		count++;
	}
}

Matrix::Matrix(const Matrix& outer)//copy the 2d matrix from another
{
	this->row = outer.row;
	this->col = outer.col;
	setUp(this->row, this->col);
	for (int rowCnt = 0; rowCnt<row; rowCnt++)
		for (int colCnt = 0; colCnt<col; colCnt++)
			setData(rowCnt, colCnt, outer.getData(rowCnt, colCnt));
		
	count++;
}

Matrix::~Matrix()//delete all storages that the matrix uses
{
	for (int rowCnt = 0; rowCnt<row; rowCnt++)
		delete[] data[rowCnt];
	delete[] data;
	
	count--;
}



void Matrix::setData(int row, int col, double data)//set the element at (row, col) as data and check the validity first
{
	if (row < this->row&&col < this->col&&row >= 0 && col >= 0)
		this->data[row][col] = data;
	else if (row >= this->row || row < 0) cout << "Error:Row number out of range.";
	else if (col >= this->col || col < 0) cout << "Error:Col number out of range.";	
}

int Matrix::getRow()const { return this->row; }//get the row number

int Matrix::getCol() const { return this->col; }//get the col number

double Matrix::getData(int row, int col) const //get the element at (row, col) and check the validity first
{
	if(row < this->row&&col < this->col&&row >= 0 && col >= 0) return data[row][col];
	else if (row >= this->row || row < 0) cout << "Row number out of range.";
	else if (col >= this->col || col < 0) cout << "Col number out of range.";
}

int Matrix::count=0;

int Matrix::getCount(){return count;}

Matrix Matrix::add(const Matrix& Adder)//check if the sizes of two matrixes are the same and add all elements afterward
{
	if (this->row != Adder.getRow() || this->col != Adder.getCol())
	{
		cout << "Error:Matrices size not equal " << endl;
		Matrix Sum(1, 1);
		return Sum;
	}
	Matrix Sum(this->row, this->col);
	for (int rowCnt = 0; rowCnt<this->row; rowCnt++)
		for (int colCnt = 0; colCnt<this->col; colCnt++)
			Sum.setData(rowCnt, colCnt, this->getData(rowCnt, colCnt) + Adder.getData(rowCnt, colCnt));

	return Sum;
}

Matrix operator+(Matrix& lhs, const Matrix& rhs)
{
	if (lhs.row != rhs.row || lhs.col != rhs.col)
	{
		cout << "Error:Matrices size not equal " << endl;
		return lhs;
	}
	Matrix Sum(lhs.row, lhs.col);
	for (int rowCnt = 0; rowCnt<lhs.row; rowCnt++)
		for (int colCnt = 0; colCnt<lhs.col; colCnt++)
			Sum.data[rowCnt][colCnt]=lhs.data[rowCnt][colCnt] + rhs.data[rowCnt][colCnt];

	return Sum;
}

Matrix Matrix::operator+(const double& rhs)
{
	Matrix Sum(this->row, this->col);
	for (int rowCnt = 0; rowCnt<this->row; rowCnt++)
		for (int colCnt = 0; colCnt<this->col; colCnt++)
			Sum.data[rowCnt][colCnt]=this->data[rowCnt][ colCnt]+rhs;
		
	return Sum;
}

Matrix& Matrix::operator=(const Matrix& rhs)
{
	for (int rowCnt = 0; rowCnt<row; rowCnt++)
		delete[] data[rowCnt];
	delete[] data;
	
	this->row = rhs.row;
	this->col = rhs.col;
	setUp(this->row, this->col);
	for (int rowCnt = 0; rowCnt<row; rowCnt++)
		for (int colCnt = 0; colCnt<col; colCnt++)
			this->data[rowCnt][colCnt]=rhs.data[rowCnt][colCnt];
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& rhs)
{
	*this=*this+rhs;
	return *this;
}

Matrix Matrix::operator++(int)
{
	Matrix tmp(*this);
	*this=*this+1;
	return tmp;
}


Matrix Matrix::multiply(const Matrix& Multiplier)//Do the matrix multiplication
{
	if (this->col != Multiplier.row)
	{
		cout << "Error:Matrices can't be multiplied due to size issue."<<endl;
		Matrix Product(1, 1);
		return Product;
	}
	Matrix Product(this->row, Multiplier.col);
	for (int prodRowCnt = 0; prodRowCnt < Product.row; prodRowCnt++)
	{
		for (int prodColCnt = 0; prodColCnt < Product.col; prodColCnt++)
		{
			double TmpElem=0;
			for (int innerCnt = 0; innerCnt < this->col; innerCnt++)
			{
				TmpElem += this->data[prodRowCnt][innerCnt] * Multiplier.data[innerCnt][prodColCnt];
			}
			Product.data[prodRowCnt][prodColCnt]=TmpElem;
		}
	}
	return Product;
}

Matrix operator*(Matrix& lhs, const Matrix& rhs)//Do the matrix multiplication
{
	if (lhs.getCol() != rhs.getRow())
	{
		cout << "Error:Matrices can't be multiplied due to size issue."<<endl;
		return lhs;
	}
	Matrix Product(lhs.row, rhs.col);
	for (int prodRowCnt = 0; prodRowCnt < Product.row; prodRowCnt++)
	{
		for (int prodColCnt = 0; prodColCnt < Product.col; prodColCnt++)
		{
			double TmpElem=0;
			for (int innerCnt = 0; innerCnt < lhs.col; innerCnt++)
			{
				TmpElem += lhs.data[prodRowCnt][innerCnt] * rhs.data[innerCnt][prodColCnt];
			}
			Product.data[prodRowCnt][prodColCnt]=TmpElem;
		}
	}
	return Product;
}

Matrix Matrix::transpose()//Transpose the Matrix
{
	Matrix Result(this->col, this->row);
	for (int rowCnt = 0; rowCnt < this->row; rowCnt++) 
	{
		for (int colCnt = 0; colCnt < this->col; colCnt++)
		{
			Result.data[colCnt][rowCnt]=this->data[rowCnt][colCnt];
		}
	}
	return Result;
}

Matrix Matrix::operator()()
{
	Matrix Result(this->col, this->row);
	for (int rowCnt = 0; rowCnt < this->row; rowCnt++) 
	{
		for (int colCnt = 0; colCnt < this->col; colCnt++)
		{
			Result.data[colCnt][rowCnt]=this->data[rowCnt][colCnt];
		}
	}
	return Result;
}

bool Matrix::operator==(const Matrix& rhs)
{
	if(this->row!=rhs.row) return false;
	if(this->col!=rhs.col) return false;
	
	bool Flag=true;
	for (int rowCnt = 0; rowCnt < this->row; rowCnt++) 
	{
		for (int colCnt = 0; colCnt < this->col; colCnt++)
		{
			if(this->data[rowCnt][colCnt]!=rhs.data[rowCnt][colCnt])
			{	
				Flag=false;
				break;	
			}
		}
	}
	
	return Flag;
}

ostream& operator<<(ostream& os, const Matrix& rhs)
{
	os<<endl;
	for (int i = 0;i<rhs.row; i++) {
		for (int j = 0;j<rhs.col; j++) {
			os<<rhs.data[i][j]<<"\t";
		}
		os<<""<<endl;
	}
	return os;
}

istream& operator>>(istream& is, Matrix& rhs)
{
	for (int i = 0;i<rhs.row; i++) {
		for (int j = 0;j<rhs.col; j++) {
			cout<<'('<<i+1<<", "<<j+1<<')'<<":";
			is>>rhs.data[i][j];
		}
	}
	return is;
}

