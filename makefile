all: reverse_interpolator polynomial_interpolator numerical_differentiator equation_solver

reverse_interpolator:
	cd ReverseInterpolation && make

polynomial_interpolator:
	cd PolynomialInterpolation && make

numerical_differentiator:
	cd NumericalDifferentiation && make

equation_solver:
	cd NonLinearEquations && make