#include "Matrix.h"
#include <iostream>
#include <math.h>
using namespace std;

static double getGCD(double a, double b) {
	if ( (a - 0) <= 1e-6) return a;
	if ( (b - 0) <= 1e-6) return b;

	if ( abs(a - b) <= 1e-6) return a;

if (a > b) 
		return getGCD(a-b, b);
	else
		return getGCD(a, b-a);
}

double Matrix::getDenominator(double val) {
	int precision = 1e6;
	double gcd = getGCD(val * precision, precision);
	if (gcd == 0)
		gcd = 1;
	double denominator = precision / gcd;

	return denominator;
}

Matrix::Matrix(const vector<vector<int>> &data) {
	for (auto row : data) {
		int size = row.size();
		mat.push_back(vector<double>(size));
		for (int i=0; i < size; ++i) {
			mat.back()[i] = row[i];
		}
	}
}

int Matrix::numColumns() {
	if (mat.size() == 0) {
		return 0;
	} else {
		return mat.back().size();
	}
}

int Matrix::numRows() {
	return mat.size();
}

void Matrix::output() {
	for (int row = 0; row < numRows(); ++row) {
		for (int col = 0; col < numColumns(); ++col) {
			cout<<mat[row][col]<<' ';
		}
		cout<<'\n';
	}
	cout<<'\n';
}

void Matrix::swapRows(int row1, int row2) {
	if (row1 == row2) {
		return;
	} else {
		mat[row1].swap(mat[row2]);
	}
}

void Matrix::fixRows(int col) {
	int pivotRow = col;

	for (int row = pivotRow; row < numRows(); ++row) {
		if (mat[row][col] != 0) {
			swapRows(row, pivotRow);
			return;
		}
	}
}

vector<double> Matrix::getRow(int rowNum) {
	return mat[rowNum];
}

vector<double> Matrix::scale(vector<double> &row, double scaleBy) {
	vector<double> ret;

	for (unsigned int i=0; i<row.size(); ++i) {
		ret.push_back(row[i]*scaleBy);
	}

	return ret;
}

vector<double> Matrix::add(vector<double> row1, vector<double> row2) {
	vector<double> ret;

	for (int col = 0; col < numColumns(); ++col) {
		ret.push_back(row1[col] + row2[col]);
	}

	return ret;
}

vector<double> Matrix::subtract(vector<double> row1, vector<double> row2) {
	return add(row1, scale(row2, -1));
}

void Matrix::replaceRow(int rowNum, vector<double> newRow) {
	mat[rowNum] = newRow;
}

void Matrix::zeroUnder(int col) {
	int pivotRowNum = col;

	for (int row = pivotRowNum+1; row < numRows(); ++row) {
			double pivot = mat[pivotRowNum][col];
			double curr = mat[row][col];
		if (curr != 0) {
			vector<double> currRow = getRow(row);
			vector<double> pivotRow = getRow(pivotRowNum);
			replaceRow(row, subtract(currRow, scale( pivotRow, (double)curr/pivot )) );
		}
	}
}

void Matrix::scaleRows() {
	for (int row = 0; row < numRows(); ++row) {
		int pivotColumn = row;

		if (pivotColumn < numColumns()) {
			double pivot = mat[row][pivotColumn];
			if (pivot != 0) {
				vector<double> currRow = getRow(row);

				replaceRow(row, scale(currRow, (double)1/pivot) );
			}
		}
	}
}

void Matrix::zeroAbove(int col) {
	int pivotRowNum = col;

	if (pivotRowNum >= numRows()) {
		return;
	}

	for (int row = pivotRowNum - 1; row >= 0; --row) {
		double pivot = mat[pivotRowNum][col];
		double curr = mat[row][col];
		if (pivot != 0 && curr != 0) {
			vector<double> currRow = getRow(row);
			vector<double> pivotRow = getRow(pivotRowNum);
			replaceRow(row, subtract(currRow, scale( pivotRow, (double)curr/pivot )) );
		}
	}
}

void Matrix::rref() {
	
	// row-echelon form
	for (int col = 0; col < numColumns(); ++col) {
		fixRows(col);

		zeroUnder(col);
	}

	scaleRows();

	// zeros above
	for (int col = numColumns() - 1; col >= 0; --col) {
		zeroAbove(col);
	}

}

vector<int> Matrix::getCoefficients() {
	this->rref();

	// check for too many variables
	if (numColumns() > numRows() + 1) {
		throw TooManyVariables();
	}
	
	vector<int> coefficients;
	vector<double> tmp;
	double best=1.0;

	for (int row = 0; row < numRows(); ++row) {
		if (mat[row].back() == 0) {

			// check if row is empty (all zeros)
			bool isEmpty = true;
			for (auto val : mat[row]) {
				if (val != 0) {
					isEmpty = false;
					break;
				}
			}
			
			if (isEmpty == false) {
				throw ImpossibleToBalance();
			}
		} else {
			tmp.push_back(mat[row].back() * -1);
			best=max(best, getDenominator(tmp.back()));
		}
	}

	// free variable
	tmp.push_back(1);

	double factor = max(1.0, best);

	for (auto val : tmp) {
		coefficients.push_back(round(val * factor));
	}

	return coefficients;
}
