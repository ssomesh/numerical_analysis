#include <iostream>
#include <vector>
#include <unordered_map>

// Function to evaluate polynomial using Horner's method
double horner(const int D, double* coefficients, const double x) {
  // Start with the highest-degree coefficient
  double result = coefficients[D];

  // Evaluate from the highest degree to the constant term
  for (int i = D-1; i >= 0; --i) {
    result = result * x + coefficients[i];
  }
  return result;
}

// Function to evaluate polynomial using Horner's method
double horner(const int D, const std::unordered_map<int,double>& coefficients_map, const double x) {
  // Start with the highest-degree coefficient
  double result = coefficients_map.at(D);

  // Evaluate from the highest degree to the constant term
  for (int i=D-1; i >= 0; --i) {
    result *= x; // scale result by x

    if(coefficients_map.find(i) != coefficients_map.end()) // the coefficient of x^i is non-zero, and is therefore in the map
    {
      result += coefficients_map.at(i); // add coefficient of x^i to result
    }
  }
  return result;
}

int main(int argc, char** argv) {

  const int D = 4; // degree of the polynomial
  double x = (double)1/3;  // Point where the polynomial is evaluated

#if 1
  /* Dense case: when all the coefficients are stored (whether zero or nonzero) */
  // Example: P(x) = 1 + 0*x - x^2 + x^3 + 2x^4 evaluated at x = 1/3 gives the answer 77/81 = 0.95...
  //std::vector<double> coefficients = {1, 0, -1, 1, 2};
  double coefficients[D+1] = {1, 0, -1, 1, 2}; // Polynomial coefficients (a0, a1, a2, a3, a4); a0 => constant term, a4 => coefficient of the highest degree term
  double result1 = horner(D, coefficients, x);
#endif

#if 1
  /* Sparse case: when only the nonzero coefficients are stored */
  // Example: P(x) = 1 + 0*x - x^2 + x^3 + 2x^4 evaluated at x = 1/3 gives the answer 77/81 = 0.95...
  std::unordered_map<int,double> coefficients_map = {{0,1.0},{2,-1.0},{3,1.0},{4,2.0}}; // < degree of term (power of x), coefficient of term >
  double result2 = horner(D, coefficients_map, x);
#endif

  std::cout << "The value of the polynomial at x  = " << x << " (evaluated using the dense case) is: " << result1 << std::endl;
  std::cout << "The value of the polynomial at x  = " << x << " (evaluated using the sparse case) is: " << result2 << std::endl;

  return 0;
}

