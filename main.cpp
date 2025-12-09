#include <iostream>
#include <cmath>

class Complex {
private:
    double real;
    double imag;
    static int count;

public:
    // Конструкторы
    Complex() : real(0), imag(0) {count++;}
    Complex(double r, double i = 0) : real(r), imag(i) {count++;}
    // Деструктор
    ~Complex(){count--;}
    
    // Геттеры
    double getReal() const { return real; }
    double getImag() const { return imag; }
    
    // Сеттеры
    void setReal(double r) { real = r; }
    void setImag(double i) { imag = i; }
    
    // Модуль комплексного числа
    double modulus() const {
        return std::sqrt(real * real + imag * imag);
    }
    
    // Вывод комплексного числа
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        if (c.imag == 0) {
            os << c.real;
        } else if (c.real == 0) {
            os << c.imag << "i";
        } else if (c.imag > 0) {
            os << c.real << " + " << c.imag << "i";
        } else {
            os << c.real << " - " << -c.imag << "i";
        }
        return os;
    }

   
    // ++complex (увеличиваем действительную часть)
    Complex& operator++() {
        ++real;
        return *this;
    }
    // complex++ (постфиксный)
    Complex operator++(int) {
        Complex temp = *this;
        ++real;
        return temp;
    }
    // --complex (уменьшаем действительную часть)
    Complex& operator--() {
        --real;
        return *this;
    }
    // complex-- (постфиксный)
    Complex operator--(int) {
        Complex temp = *this;
        --real;
        return temp;
    }
    
    // Унарный минус
    Complex operator-() const {
        return Complex(-real, -imag);
    }

    // Бинарные арифметические операторы
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }
    
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                      real * other.imag + imag * other.real);
    }
    
    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        if (denominator == 0) {
            throw std::runtime_error("Деление на ноль!");
        }
        return Complex((real * other.real + imag * other.imag) / denominator,
                      (imag * other.real - real * other.imag) / denominator);
    }
    
    // Операторы сравнения (сравниваем модули)
    bool operator<(const Complex& other) const {
        return this->modulus() < other.modulus();
    }
    
    bool operator>(const Complex& other) const {
        return this->modulus() > other.modulus();
    }
    
    bool operator<=(const Complex& other) const {
        return this->modulus() <= other.modulus();
    }
    
    bool operator>=(const Complex& other) const {
        return this->modulus() >= other.modulus();
    }
    
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }
    
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
};

int Complex::count = 0;

int main() {
    Complex c1(3, 4);
    Complex c2(1, -2);
    Complex c3(3, 4);

    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "c2 = " << c2 << std::endl;
    std::cout << "c3 = " << c3 << std::endl;
    std::cout << "Модуль c1 = " << c1.modulus() << std::endl;

    std::cout << "\nТест унарных операторов:" << std::endl;
    std::cout << "++c1 = " << ++c1 << std::endl;
    std::cout << "c2-- = " << c2-- << std::endl;
    std::cout << "После c2--: c2 = " << c2 << std::endl;
    std::cout << "-c1 = " << -c1 << std::endl;

    std::cout << "Тест арифметических операторов:" << std::endl;
    std::cout << "c1 + c2 = " << c1 + c2 << std::endl;
    std::cout << "c1 - c2 = " << c1 - c2 << std::endl;
    std::cout << "c1 * c2 = " << c1 * c2 << std::endl;
    std::cout << "c1 / Complex(2, 0) = " << c1 / Complex(2, 0) << std::endl;

    std::cout << "\nc1 = " << c1 << std::endl;
    std::cout << "c2 = " << c2 << std::endl;
    std::cout << "c3 = " << c3 << std::endl;
    
    std::cout << "\nТест операторов сравнения (по модулю):" << std::endl;
    std::cout << "c1 < c2: " << (c1 < c2 ? "true" : "false") << std::endl;
    std::cout << "c1 > c2: " << (c1 > c2 ? "true" : "false") << std::endl;
    std::cout << "c1 == c3: " << (c1 == c3 ? "true" : "false") << std::endl;
    
    return 0;
}