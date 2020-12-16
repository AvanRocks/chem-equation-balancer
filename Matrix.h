#include <vector>
#include <exception>

class Matrix {
private:
	std::vector<std::vector<double>> mat;

	int numColumns();
	int numRows();
	std::vector<double> getRow(int rowNum);
	void fixRows(int col);
	void swapRows(int row1, int row2);
	void zeroUnder(int col);
	void zeroAbove(int col);
	std::vector<double> scale(std::vector<double> &row, double scaleBy);
	std::vector<double> add(std::vector<double> row1, std::vector<double> row2);
	std::vector<double> subtract(std::vector<double> row1, std::vector<double> row2);
	void replaceRow(int rowNum, std::vector<double> newRow);
	void scaleRows();
	void rref();

	static double gcd(int a, int b);
	static double getDenominator(double val);

public:
	Matrix(const std::vector<std::vector<int>> &data);

	void output();
	std::vector<int> getCoefficients();
};

class ImpossibleToBalance : public std::exception {};
class TooManyVariables : public std::exception {};

