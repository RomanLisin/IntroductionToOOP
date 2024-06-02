
#include <iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;


class Matrix {

    int** m;
    int height;
    int width;

    bool allocate(int height, int width) 
    {
        if (height <= 0 || width <= 0) 
        {
            return false;
        }
        this->height = height;
        this->width = width;
        m = new int* [height];
        for (int j = 0; j < height; j++) 
        {
            m[j] = new int[width];
            for (int i = 0; i < width; i++) 
            {
                m[j][i] = 0;
            }
        }
        return true;
    }

    void clear() {
        if (m != nullptr) 
        {
            for (int j = 0; j < height; j++) 
            {
                delete[] m[j];
            }
            delete[] m;
        }
        m = nullptr;
    }
    
    void copyTo(int** from) {
        for (int j = 0; j < height; j++) 
        {
            for (int i = 0; i < width; i++) 
            {
                m[j][i] = from[j][i];
            }
        }
    }

public:
    Matrix inverted()const;

      int get_width() const
      {
         return width;
      }

        int get_height() const
      {
        return height;
      }

        int** get_m()const
        {
            return m;
        }
      


    Matrix(int height, int width) 
    {
        if (height <= 0 || width <= 0) 
        {
            cout << "Wrong sizes!" << endl;
        }
        if (!allocate(height, width)) 
        {
            cout << "Wrong sizes!" << endl;
        }
    }
    Matrix(int size) : Matrix(size, size) {}

    Matrix() 
    {
        height = width = 0;
        m = nullptr;
    }
    Matrix(const Matrix& matrix) 
    {
        //if (this == &matrix) return *this;
        clear();
        allocate(matrix.height, matrix.width);
        copyTo(matrix.m);
    }
    ~Matrix() {
        clear();
    }
    int& operator()(int j, int i) 
    {
        if (j < 0 || j >= height || i < 0 || i >= width) 
        {
            cout << "Matrix index error!" << endl;
        }
        return m[j][i];
    }
    Matrix& operator=(const Matrix& matrix) {
        if (&matrix == this) 
        {
            return *this;
        }

        clear();
        allocate(matrix.height, matrix.width);
        copyTo(matrix.m);
        return *this;
    }

    void print() const 
    {
        if (m == nullptr) 
        {
            cout << "Empty matrix" << endl;
        }
        else 
        {
            for (int j = 0; j < height; j++)
            {
                for (int i = 0; i < width; i++)
                {
                    cout << "\t" << m[j][i];
                }
                cout << endl;
            }
         }
    }

    void randomize()
    {
        if (m == nullptr)
        {
            cout << "Empty matrix";
        }
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                m[j][i] = rand() % 10;
            }
        }
    }

    Matrix operator+(const Matrix& other) const
    {
     if (height != other.height ||  width != other.width) 
     {
     cout << "Matrix dimensions mismatch";
    }

     Matrix result(height, width);

     for (int j = 0; j < height; j++) 
     {
         for (int i = 0; i < width; i++) {
                result(j, i) = m[j][i] + other.m[j][i];
         }
     }
     return result;
    }
    Matrix operator-(const Matrix& other) const 
    {
        if (height != other.height || width != other.width) 
        {
            cout << "Matrix dimensions mismatch";
        }
        Matrix result(height, width);
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                result(j, i) = m[j][i] - other.m[j][i];
            }
        }
        return result;
    }
    Matrix operator*(const Matrix& other) const 
    {
        if (width != other.height) {
            cout << "Matrix dimensions mismatch";
        }
        Matrix result(height, other.width);
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < other.width; k++) 
            {
                for (int i = 0; i < width; i++) 
                {
                    result(j, k) += m[j][i] * other.m[i][k];
                }
            }
        }
        return result;
    }
    /*Matrix operator/(const Matrix& other) const {
      if (width != other.height) {
        cout <<"Matrix dimensions mismatch";
      }
      Matrix result(height, other.width);
      for (int j = 0; j < height; j++) {
        for (int k = 0; k < other.width; k++) {
          for (int i = 0; i < width; i++) {
            result(j, k) += m[j][i] / other.m[i][k];
          }
        }
      }
      return result;
    }*/    // Wrong
    Matrix operator/(const Matrix& other) const 
    {
        if (width != other.height) 
        {
            cout << "Matrix dimensions mismatch";
        }
        Matrix inverseOther = other.inverted();
        return (*this) * inverseOther;
    }
    Matrix& operator+=(const Matrix& other) 
    {
        if (height != other.height || width != other.width) 
        {
            cout << "Matrix dimensions mismatch";
        }
        for (int j = 0; j < height; j++) 
        {
            for (int i = 0; i < width; i++) 
            {
                m[j][i] += other.m[j][i];
            }
        }
        return *this;
    }
    Matrix& operator-=(const Matrix& other) 
    {
        if (height != other.height || width != other.width) 
        {

                cout << "Matrix dimensions mismatch";
        }
        for (int j = 0; j < height; j++) 
        {
            for (int i = 0; i < width; i++) 
            {
                m[j][i] -= other.m[j][i];
            }
        }
        return *this;
    }
    Matrix& operator*=(const Matrix& other) 
    {
        if (width != other.height)
        {
            cout << "Matrix dimensions mismatch";
        }
        Matrix temp(height, other.width);
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < other.width; k++) 
            {
                for (int i = 0; i < width; i++) 
                {
                    temp(j, k) += m[j][i] * other.m[i][k];
                }
            }
        }
        *this = temp;
        return *this;
    }
    Matrix& operator/=(const Matrix& other) 
    {
        if (width != other.height) 
        {
            cout << "Matrix dimensions mismatch";
        }
        Matrix temp(height, other.width);
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < other.width; k++) 
            {
                for (int i = 0; i < width; i++) 
                {
                    temp(j, k) += m[j][i] / other.m[i][k];
                }
            }
        }
        *this = temp;
        return *this;
    }
    bool operator==(const Matrix& other) const 
    {
        if (height != other.height || width != other.width) 
        {
            return false;
        }
        for (int j = 0; j < height; j++) 
        {
            for (int i = 0; i < width; i++) 
            {
                if (m[j][i] != other.m[j][i]) 
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool operator!=(const Matrix& other) const 
    {
        return!(*this == other);
    }
};
void determinant(Matrix& L, Matrix& U);
void main()
{
    Matrix mat1(2); mat1.randomize(); mat1.print(); cout << endl;
    Matrix mat2 = mat1; mat2.print(); cout << endl;
    Matrix mat3;
    mat3 = mat1 + mat2;
    mat3.print();
    cout << endl;
    mat3 = mat1 * mat2;
    Matrix mat4 = mat1 / mat2;
    mat4.print();
    Matrix mat5;
    mat5.randomize();
    mat5 += mat1;
    mat5.print();
    Matrix mat6;
    mat6.randomize();
    mat6 *= mat2;
    mat6.print();

}

Matrix Matrix::inverted() const {
    int n = width;
    Matrix L(n, n);
    Matrix U(n, n);
    determinant(L, U);
    Matrix result(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result(i, j) = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        result(i, i) = 1;
        for (int j = i; j < n; j++) {
            double sum = 0;
            for (int k = i; k < j; k++) {
                sum += L(j, k) * result(k, i);
            }
            result(j, i) = (j == i ? 1 : -sum) / L(j, j);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            double sum = 0;
            for (int k = 0; k < j; k++) {
                sum += U(i, k) * result(k, j);
            }
            result(i, j) = -sum / U(i, i);
        }
    }
    return result;
}
void determinant(Matrix& L, Matrix& U)
{
    int n = L.get_width();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            L (i, j) = (i == j ? 1 : 0);
            U(i, j) = U.get_m()[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double factor = U(j, i) / U(i, i);
            for (int k = i; k < n; k++) {
                U(j, k) -= factor * U(i, k);
            }
            L(j, i) = factor;
        }
    }
}