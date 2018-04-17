#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
using namespace std;

/*
 * 簡單的矩陣相加和相乘
 */
 
class Matrix {
private:
	double ** data;			// 一個二維的double矩陣
	int row;			// 儲存data共有幾個row
	int col;			// 儲存data共有幾個col
	void setUp(int, int);		// utility function, 設定row和col的值
	
	static int count;

public:
	Matrix();			// default constructor, 什麼都不傳, 將data存入2*2都是0的值
	Matrix(int, int);		// constructor, 只設定大小, 資料預設為0
	Matrix(int, int, double [],int);// constructor, 將傳入的一維陣列轉存為二維陣列放入data中
	Matrix(const Matrix &);		// copy constructor
	~Matrix();			// destructor, 清理data

	void setData(int, int, double);	// 設定第(r,c)位置data的值

	int getRow() const;		// 回傳private member: row
	int getCol() const;		// 回傳private member: col
	double getData(int, int) const;	// 拿到矩陣(r,c)位置的值

	
	static int getCount();
	
	Matrix add(const Matrix &);		// 矩陣相加, 回傳相加後的矩陣
	Matrix multiply(const Matrix &);	// 矩陣相乘, 回傳相乘後之矩陣
	Matrix transpose();	// 矩陣轉置, 回傳轉置後的矩陣
    
	void displayData() {	// 將這個矩陣的資料印出來 (不必修改)
		for (int i = 0;i<row; i++) {
			for (int j = 0;j<col; j++) {
					cout<<data[i][j]<<"\t";
    			}
			cout<<""<<endl;
		}
	}
	
	
	friend Matrix operator+(Matrix&, const Matrix&);
	Matrix operator+(const double&);
	Matrix& operator=(const Matrix&);
	Matrix& operator+=(const Matrix&);
	Matrix operator++(int);
	friend Matrix operator*(Matrix&, const Matrix&);
	Matrix operator()();
	bool operator==(const Matrix&);
	friend ostream& operator<<(ostream&, const Matrix&);
	friend istream& operator>>(istream&, Matrix&);
};

#endif
