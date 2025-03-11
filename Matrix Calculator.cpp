#include <iostream>
#include <vector>

class Matrix {
private:
    std::vector<std::vector<double>> data;
    int rows, cols;

public:
    Matrix(int r, int c) : rows(r), cols(c), data(r, std::vector<double>(c, 0)) {}

    void FillMatrix() {
        std::cout << "Enter elements row-wise (" << rows << "x" << cols << " matrix):\n";
        for (auto &row : data)
            for (auto &elem : row)
                std::cin >> elem;
    }

    void PrintMatrix() const {
        for (const auto &row : data) {
            for (const auto &elem : row)
                std::cout << elem << " ";
            std::cout << "\n";
        }
    }

    Matrix operator+(const Matrix &other) const {
        if (rows != other.rows || cols != other.cols)
            throw std::invalid_argument("Matrix dimensions must match for addition!");

        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];

        return result;
    }

    Matrix operator*(const Matrix &other) const {
        if (cols != other.rows)
            throw std::invalid_argument("Invalid matrix multiplication dimensions!");

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < other.cols; ++j)
                for (int k = 0; k < cols; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];

        return result;
    }

    Matrix Transpose() const {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[j][i] = data[i][j];

        return result;
    }
};

int main() {
    int r1, c1, r2, c2;
    std::cout << "Enter dimensions for first matrix (rows cols): ";
    std::cin >> r1 >> c1;
    Matrix A(r1, c1);
    A.FillMatrix();

    std::cout << "Enter dimensions for second matrix (rows cols): ";
    std::cin >> r2 >> c2;
    Matrix B(r2, c2);
    B.FillMatrix();

    std::cout << "Matrix A:\n";
    A.PrintMatrix();

    std::cout << "Matrix B:\n";
    B.PrintMatrix();

    try {
        std::cout << "Matrix A + B:\n";
        (A + B).PrintMatrix();
    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
    }

    try {
        std::cout << "Matrix A * B:\n";
        (A * B).PrintMatrix();
    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
    }

    std::cout << "Transpose of Matrix A:\n";
    A.Transpose().PrintMatrix();

    return 0;
}
