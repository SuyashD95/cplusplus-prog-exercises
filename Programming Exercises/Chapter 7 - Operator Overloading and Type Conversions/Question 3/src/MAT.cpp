/*
 * MAT.cpp
 * Author: suyashd95
 */

#include "MAT.h"

#include <iostream>

MAT::MAT(): rows(0), cols(0), matrix(NULL) { /*std::cout << "Default constructor called." << std::endl;*/ }

MAT::MAT(int x, int y) {

	rows = x;
	cols = y;

	if(rows != 0 && cols != 0) {

		matrix = new int*[rows];
		for(int i = 0; i < x; i++)
			matrix[i] = new int[cols];

		for(int i = 0; i < rows; i++)
			for(int j = 0; j < cols; j++)
				matrix[i][j] = 0;
	}
	else
		matrix = NULL;

//	std::cout << "Parameterized Constructor called." << std::endl;
}

MAT::MAT(const MAT& mat) {

	this->rows = mat.rows;
	this->cols = mat.cols;

	if(mat.matrix != NULL) {

		this->matrix = new int*[this->rows];
		for(int i = 0; i < this->rows; i++)
			this->matrix[i] = new int[this->cols];

		for(int i = 0; i < this->rows; i++)
			for(int j = 0; j < this->cols; j++)
				this->matrix[i][j] = mat.matrix[i][j];
	}
	else
		this->matrix = mat.matrix;

//	std::cout << "Copy Constructor called." << std::endl;
}

MAT& MAT::operator =(const MAT& rhs) {

	if(this != &rhs) {						// Self Assignment Check

		if(this->matrix != NULL) {

			if(this->rows == rhs.rows && this->cols == rhs.cols) {

				for(int i = 0; i < this->rows; i++)
					for(int j = 0; j < this->cols; j++)
						this->matrix[i][j] = rhs.matrix[i][j];
			}
			else
				std::cout << "ERROR: Dimensions of LHS matrix and RHS matrix are not matching. Hence, assignment not possible." << std::endl;
		}
		else {

			this->rows = rhs.rows;
			this->cols = rhs.cols;

			if(rhs.matrix != NULL) {		// Check for a NULL matrix on RHS

				this->matrix = new int*[this->rows];
				for(int i = 0; i < this->rows; i++)
					this->matrix[i] = new int[cols];

				for(int i = 0; i < this->rows; i++)
					for(int j = 0; j < this->cols; j++)
						this->matrix[i][j] = rhs.matrix[i][j];

			}
			else {

				this->matrix = NULL;
			}
		}
	}

//	std::cout << "Copy Assigment Operator called." << std::endl;
	return *this;
}

bool MAT::operator ==(const MAT& rhs) {

	if(this->rows == rhs.rows && this->cols == rhs.cols) {

		if(this->matrix == NULL && this->matrix == rhs.matrix) return true;

		else {

			bool equals = true;

			for(int i = 0; i < this->rows; i++)
				for(int j = 0; j < this->cols; j++)
					if(this->matrix[i][j] != rhs.matrix[i][j]) {

						equals = false;
						break;
					}

			return equals;
		}
	}
	else
		return false;
}

bool MAT::operator !=(const MAT& rhs) {

	if(this->rows == rhs.rows && this->cols == rhs.cols) {

		if(this->matrix == NULL && this->matrix == rhs.matrix) return false;	// Check for NULL matrix

		else {

			bool notEquals = false;

			for(int i = 0; i < this->rows; i++)
				for(int j = 0; j < this->cols; j++)
					if(this->matrix[i][j] == rhs.matrix[i][j]) {

						notEquals = true;
						break;
					}

			return notEquals;
		}
	}
	else
		return true;
}

MAT MAT::operator +(const MAT& mat) {

	if(this->matrix != NULL && mat.matrix != NULL) {

		if(this->rows == mat.rows && this->cols == mat.rows) {

			MAT sum(this->rows, this->cols);

			for(int i = 0; i < this->rows; i++)
				for(int j = 0; j < this->cols; j++)
					sum.matrix[i][j] = this->matrix[i][j] + mat.matrix[i][j];

			return sum;
		}
		else {

			std::cout << "ERROR: Row and column of the two matrices involved in this operation are different." << std::endl;
			return (MAT());
		}
	}
	else {

		std::cout << "ERROR: Cannot add a non-existent matrix." << std::endl;
		return(MAT());
	}
}

MAT MAT::operator -() {

	if(this->matrix != NULL) {

		for(int i = 0; i < this->rows; i++)
			for(int j = 0; j < this->cols; j++)
				this->matrix[i][j] = -this->matrix[i][j];
	}
	else
		std::cout << "ERROR: Cannot perform a unary - operation on a non-existent matrix" << std::endl;

	return *this;
}

MAT MAT::operator -(const MAT& mat) {

	if(this->matrix != NULL && mat.matrix != NULL) {

		if(this->rows == mat.rows && this->cols == mat.rows) {

			MAT diff(this->rows, this->cols);

			for(int i = 0; i < this->rows; i++)
				for(int j = 0; j < this->cols; j++)
					diff.matrix[i][j] = this->matrix[i][j] - mat.matrix[i][j];

			return diff;
		}
		else {

			std::cout << "ERROR: Row and column of the two matrices involved in this operation are different." << std::endl;
			return (MAT());
		}
	}
	else {

		std::cout << "ERROR: Cannot subtract a non-existent matrix." << std::endl;
		return (MAT());
	}
}

MAT MAT::operator *(const MAT& mat) {

	if(this->matrix != NULL && mat.matrix != NULL) {

		if(this->cols == mat.rows) {

			MAT product(this->rows, mat.cols);
			int const commonDim = this->cols;		// Or, int const commonDim = mat.rows;

			for(int a = 0; a < this->rows; a++)
				for(int c = 0; c < mat.cols; c++)
					for(int b = 0; b < commonDim; b++)
						product.matrix[a][c] += this->matrix[a][b] * mat.matrix[b][c];

			return product;
		}
		else {

			std::cout << "ERROR: Columns of the first operand (matrix preceding *)"
					  << "and the Rows of the second operand (matrix following *) are different." << std::endl;
			return (MAT());
		}
	}
	else {

		std::cout << "ERROR: Cannot multiply a non-existent matrix." << std::endl;
		return (MAT());
	}


}

MAT::operator bool() {								// Used for checking NULL matrices

	return this->matrix != NULL;
}

MAT::~MAT() {

	if(matrix != NULL) {

		for (int i = 0; i < rows; i++)
			delete[] matrix[rows];
		delete[] matrix[cols];
	}
//	std::cout << "Destructor called." << std::endl;
}

MAT operator *(const MAT& mat, const int scalar) {

	if(mat.matrix != NULL) {

		MAT product(mat.rows, mat.cols);

		for(int i = 0; i < product.rows; i++)
			for(int j = 0; j < product.rows; j++)
				product.matrix[i][j] = mat.matrix[i][j] * scalar;

		return product;
	}
	else {

		std::cout << "ERROR: Cannot multiply a number with a NULL matrix." << std::endl;
		return (MAT());
	}
}

MAT operator *(const int scalar, const MAT& mat) {

	if(mat.matrix != NULL) {

		MAT product(mat.rows, mat.cols);

		for(int i = 0; i < product.rows; i++)
			for(int j = 0; j < product.rows; j++)
				product.matrix[i][j] = mat.matrix[i][j] * scalar;

		return product;
	}
	else {

		std::cout << "ERROR: Cannot multiply a number with a NULL matrix." << std::endl;
		return (MAT());
	}
}

std::ostream& operator <<(std::ostream& out, const MAT& mat) {

	if(mat.matrix != NULL) {

			out << "Displaying a matrix of size " << mat.rows << " x " << mat.cols << "...\n" << std::endl;
			for (int i = 0; i < mat.rows; i++) {

				for (int j = 0; j < mat.cols; j++)
					out << "matrix[" << i + 1 << "][" << j + 1 << "]: " << mat.matrix[i][j] << std::endl;
				out << std::endl;
			}
			out << "The matrix has been successfully displayed." << std::endl;
		}
		else
			out << "ERROR: Cannot display a non-existent matrix." << std::endl;

	return out;
}

std::istream& operator >>(std::istream& in, MAT& mat) {

	if(mat.matrix != NULL) {

			std::cout << "Populating a matrix of size " << mat.rows << " x " << mat.cols << "...\n" << std::endl;
			for (int i = 0; i < mat.rows; i++) {

				for (int j = 0; j < mat.cols; j++) {

					std::cout << "Enter the value of matrix[" << i + 1 << "][" << j + 1 << "]: " << std::flush;
					in >> mat.matrix[i][j];
				}
				std::cout << std::endl;
			}

			std::cout << "The matrix has been successfully populated." << std::endl;
		}
		else
			std::cout << "ERROR: Cannot populate a non-existent matrix." << std::endl;

	return in;
}
