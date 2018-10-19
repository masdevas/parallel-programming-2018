#ifndef MPI_TASK1_13_MATRIX_HPP
#define MPI_TASK1_13_MATRIX_HPP

#include <iostream>
#include <iomanip>
#include <random>

template<typename T>
class Matrix {

public:

    explicit Matrix(int rows = 2, int columns = 2) : rows_(rows), columns_(columns), data_(new T[rows * columns]) {
    }

    ~Matrix() {
        delete data_;
    }

    Matrix(const Matrix &matrix) : rows_(matrix.rows_), columns_(matrix.columns_) {
        data_ = new T[rows_ * columns_];
        for (int i = 0; i < rows_ * columns_; ++i) {
            data_[i] = matrix.data_[i];
        }
    }

    Matrix &operator=(const Matrix &matrix) {
        delete data_;
        rows_ = matrix.rows_;
        columns_ = matrix.columns_;
        data_ = new T[rows_ * columns_];
        for (int i = 0; i < rows_ * columns_; i++) {
            data_[i] = matrix.data_[i];
        }
        return *this;
    }

    void Show() {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < columns_; j++) {
                std::cout << " " << std::setw(5) << data_[i*columns_ + j] << " ";
            }
            std::cout << '\n';
        }
    }

    void FillRand(int low_limit, int high_limit) {
        std::mt19937 generator(static_cast<unsigned>(time(nullptr)));
        std::uniform_real_distribution<double> distribution(low_limit, high_limit);
        for (int i = 0; i < rows_ * columns_; i++) {
            data_[i] = static_cast<T>(distribution(generator));
        }
    }

    T* Data() {
        return data_;
    }

private:
    T* data_;

    int rows_;

    int columns_;
};

#endif
