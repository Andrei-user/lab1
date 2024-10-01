#include <iostream>
#include <vector>
#include <fstream>

// Чтение матрицы
class MatrixReader {
public:
    static std::vector<std::vector<int>> readMatrixFromFile(const std::string& filename) {
        std::ifstream file(filename);
        std::vector<std::vector<int>> matrix;
        
        if (!file) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return matrix;
        }
        
        unsigned rows, cols;
        file >> rows >> cols;

        matrix.resize(rows, std::vector<int>(cols));

        for (unsigned i = 0; i < rows; ++i) {
            for (unsigned j = 0; j < cols; ++j) {
                file >> matrix[i][j];
            }
        }

        file.close();
        return matrix;
    }
};

// Запись матрицы в файл
class MatrixWriter {
public:
    static void writeMatrixToFile(const std::string& filename, const std::vector<std::vector<int>>& matrix) {
        std::ofstream file(filename);
        
        if (!file) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }
        
        unsigned rows = matrix.size();
        unsigned cols = matrix[0].size();

        file << rows << " " << cols << std::endl;

        for (unsigned i = 0; i < rows; ++i) {
            for (unsigned j = 0; j < cols; ++j) {
                file << matrix[i][j] << " ";
            }
            file << std::endl;
        }

        file.close();
    }
};

// Основной класс для работы с матрицами
class MatrixDense {
private:
    std::vector<std::vector<int>> _data;
    unsigned _rows, _cols;

public:
    MatrixDense(unsigned rows, unsigned cols) : _rows(rows), _cols(cols) {
        _data.resize(rows, std::vector<int>(cols, 0));
    }

    MatrixDense(const std::vector<std::vector<int>>& data) : _data(data) {
        _rows = data.size();
        _cols = data[0].size();
    }

    // Сложение матриц
    MatrixDense operator+(const MatrixDense& other) {
        if (_rows != other._rows || _cols != other._cols) {
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }

        MatrixDense result(_rows, _cols);
        for (unsigned i = 0; i < _rows; ++i) {
            for (unsigned j = 0; j < _cols; ++j) {
                result._data[i][j] = _data[i][j] + other._data[i][j];
            }
        }

        return result;
    }

    void printMatrix() const {
        for (unsigned i = 0; i < _rows; ++i) {
            for (unsigned j = 0; j < _cols; ++j) {
                std::cout << _data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    const std::vector<std::vector<int>>& getData() const {
        return _data;
    }
};

// Основная программа
int main() {
    // Чтение матриц из файлов
    std::vector<std::vector<int>> matrixData1 = MatrixReader::readMatrixFromFile("matrix1.txt");
    std::vector<std::vector<int>> matrixData2 = MatrixReader::readMatrixFromFile("matrix2.txt");

    MatrixDense matrix1(matrixData1);
    MatrixDense matrix2(matrixData2);

    // Сложение матриц
    MatrixDense resultMatrix = matrix1 + matrix2;

    // Запись результата в новый файл
    MatrixWriter::writeMatrixToFile("result_matrix.txt", resultMatrix.getData());
    std::cout << "Resulting matrix after addition:" << std::endl;
    resultMatrix.printMatrix();

    return 0;
}
