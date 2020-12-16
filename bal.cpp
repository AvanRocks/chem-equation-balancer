#include <iostream>
#include <string>
#include <map>
#include "Matrix.h"
using namespace std;
typedef vector<vector<int>> vii;

bool isCapital(char c) {
	return (c >= 'A' && c <= 'Z');
}

bool isLower(char c) {
	return (c >= 'a' && c <= 'z');
}

bool isDigit(char c) {
	return (c >= '0' && c <= '9');
}

bool isApprovedChar(char c) {
	if (isCapital(c)) return true;
	if (isLower(c)) return true;
	if (isDigit(c)) return true;
	if (c == '+') return true;
	if (c == '=') return true;

	return false;
}

string readEquation() {
	string eq;
	getline(cin, eq);

	for (unsigned int i=0; i<eq.length();) {
		if (!isApprovedChar(eq[i])) {
			eq.erase(i,1);
		} else {
			++i;
		}
	}

	return eq;
}

int parseDigits(const string &equation, unsigned int &idx) {
	string number = "";

	while (isDigit(equation[idx])) {
		number += equation[idx];
		idx++;
	}

	return stoi(number);
}

void parseElement(const string &equation, unsigned int &idx, string &element, int &quantity) {
	quantity = 1;
	element = "";

	if (isCapital(equation[idx])) {
		element += equation[idx];

		idx++;
	}

	if (isLower(equation[idx])) {
		element += equation[idx];

		idx++;
	}

	if (isDigit(equation[idx])) {
		quantity = parseDigits(equation, idx);
	}

}

// find out which elements are involved in the equation
// and associate them to a row in the matrix
void findElementsInvolved(string &equation, vii &matrix, map<string, int> &rowOfElement) {
	map<string, bool> alreadySeen;

	for (unsigned int i = 0; i < equation.length() ; ) {
		if (equation[i] == '+' || equation[i] == '=') {
			++i;
			continue;
		}

		string element;
		int quantity;
		parseElement(equation, i, element, quantity);

		if (!alreadySeen[element]) {
			alreadySeen[element] = true;
			matrix.push_back(vector<int>());
			rowOfElement[element] = matrix.size() - 1;
		}
	}
}

void fillColumnOfMatrix(vii &matrix, unsigned int columnNum) {
	for (unsigned int i = 0; i < matrix.size(); ++i) {
		if (matrix[i].size() < columnNum) {
			matrix[i].push_back(0);
		}
	}
}

void parseCompounds(string &equation, unsigned int start, unsigned int end, vii &matrix, map<string, int> &rowOfElement, bool isReactants) {
	unsigned int compoundNum;
	if (isReactants) {
		compoundNum = 1;
	} else {
		compoundNum = matrix[0].size() + 1;
	}

	for (unsigned int i = start; i < end; ) {
		if (equation[i] == '+') {
			fillColumnOfMatrix(matrix, compoundNum);

			compoundNum++;
			++i;
		} else {
			string element;
			int quantity;
			parseElement(equation, i, element, quantity);

			int row = rowOfElement[element];
			if (isReactants) {
				matrix[row].push_back(quantity);
			} else {
				matrix[row].push_back(-quantity);
			}
		}
	}


	fillColumnOfMatrix(matrix, compoundNum);
	compoundNum++;

}

vii toMatrix(string &equation) {
	vii matrix;

	map<string, int> rowOfElement;

	findElementsInvolved(equation, matrix, rowOfElement);

	unsigned int mid = equation.find('=');
	parseCompounds(equation,		 0,								mid, matrix, rowOfElement, true);
	parseCompounds(equation, mid+1, equation.length(), matrix, rowOfElement, false);

	return matrix;
}

void placeCoefficients(string &equation, vector<int> &coefficients) {
	int idx = 0;
	
	for (unsigned int i = 0; i < equation.length(); ++i) {
		if (i == 0) {
			if (coefficients[idx] != 1) {
				equation.insert(i, to_string(coefficients[idx]));
			}
			idx++;
		} else if (equation[i] == '+' || equation[i] == '=') {
			equation.insert(i, " ");
			++i;
		} else if (i >= 2 && (equation[i-1] == '+' || equation[i-1] == '=' )) {
			equation.insert(i, " ");
			++i;
			if (coefficients[idx] != 1) {
				equation.insert(i, to_string(coefficients[idx]));
			}
			idx++;
		}
	}
}

int main() {
	string equation = readEquation();

	Matrix matrix(toMatrix(equation));

	vector<int> coefficients = matrix.getCoefficients();

	placeCoefficients(equation, coefficients);

	cout<<'\n';
	cout<<equation<<'\n';

	return 0;
}
