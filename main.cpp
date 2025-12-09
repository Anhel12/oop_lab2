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
};

int Complex::count = 0;

int main() {
    Complex c1(3, 4);
    Complex c2(1, -2);
    
    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "c2 = " << c2 << std::endl;
    std::cout << "Модуль c1 = " << c1.modulus() << std::endl;

    std::cout << "\nТест унарных операторов:" << std::endl;
    std::cout << "++c1 = " << ++c1 << std::endl;
    std::cout << "c2-- = " << c2-- << std::endl;
    std::cout << "После c2--: c2 = " << c2 << std::endl;
    std::cout << "-c1 = " << -c1 << std::endl;
    
    return 0;
}