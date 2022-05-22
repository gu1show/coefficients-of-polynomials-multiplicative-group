#include <iostream>;
#include <vector>;

using VectorInt1D = std::vector<int>;

void shiftToLeft(std::vector<VectorInt1D>& multiplicativeGroup, int row)
{
	for (int i = 0; i < static_cast<int>(multiplicativeGroup[0].size()) - 1; i++)
		multiplicativeGroup[row][i] = multiplicativeGroup[row - 1][i + 1];
}

VectorInt1D divideByIrreduciblePolynomial(const VectorInt1D& polynomial, 
	                                      const VectorInt1D& irreduciblePolymonial,
	                                      int degree)
{
	int quotient = polynomial[0] / irreduciblePolymonial[0];
	VectorInt1D newPolynomial(polynomial.size());

	for (int i = polynomial.size() - 1; i > -1; i--)
		if ((polynomial[i] - irreduciblePolymonial[i] * quotient) >= 0)
			newPolynomial[i] = polynomial[i] - irreduciblePolymonial[i] * quotient;
		else 
		{
			newPolynomial[i] = polynomial[i] - irreduciblePolymonial[i] * quotient;
			while (newPolynomial[i] < 0) newPolynomial[i] += degree;
		}
	return newPolynomial;
}

bool isTheSame(const std::vector<VectorInt1D>& polynomial, int index)
{
	int i = 0;
	bool isFound = false;
	while ((i < index)  && (!isFound))
	{
		int j = 1;
		while (
			   (j < int(polynomial[index].size())) && (!isFound) && 
			   (polynomial[index][j] == polynomial[i][j])
			  ) j++;

		if (j == int(polynomial[index].size())) isFound = true;
		i++;
	}

	if (isFound) return true;
	else return false;
}

void outputPolymonial(const VectorInt1D& polynomial) 
{
	for (int i = 1; i < static_cast<int>(polynomial.size()); i++)
		std::cout << polynomial[i] << ' ';
	std::cout << '\n';
}

int main()
{
	int degree = 0, numeralSystem = 0;

	std::cout << "Input a degree of a polynomial ";
	std::cin >> degree;
	std::cout << "Input a numeral system of a polynomial ";
	std::cin >> numeralSystem;

	VectorInt1D irreduciblePolymonial(numeralSystem + 1);
	std::cout << "Input the coefficients of the irreducible polynomial ";
	for (int i = 0; i < static_cast<int>(irreduciblePolymonial.size()); i++)
		std::cin >> irreduciblePolymonial[i];

	std::vector<VectorInt1D> multiplicativeGroup(pow(degree, numeralSystem) - 1,
		                                         VectorInt1D(numeralSystem + 1));

	multiplicativeGroup[0][numeralSystem] = 1;
	std::cout << 1 << ") ";
	outputPolymonial(multiplicativeGroup[0]);

	bool isIrreducible = true;
	int i = 1;
	while ((i < static_cast<int>(pow(degree, numeralSystem) - 1)) && (isIrreducible))
	{
		shiftToLeft(multiplicativeGroup, i);
		if (multiplicativeGroup[i][0] != 0)
			multiplicativeGroup[i] = divideByIrreduciblePolynomial(multiplicativeGroup[i],
				                                                   irreduciblePolymonial,
				                                                   degree);
		
		if (isTheSame(multiplicativeGroup, i - 1))
		{
			std::cout << "Stop! The polynomial is not irreducible!";
			isIrreducible = false;
		}
		else 
		{
			std::cout << i + 1 << ") ";
			outputPolymonial(multiplicativeGroup[i]);
			i++;
		}
	}
}
