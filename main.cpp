#include <iostream>
#include <cmath>
#include <vector>

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

struct OperationRecord {
    std::string operation;
    Complex num1;
    Complex num2;
    Complex result;
    
    OperationRecord(const std::string& op, const Complex& n1, const Complex& n2, const Complex& res)
        : operation(op), num1(n1), num2(n2), result(res) {}
    
    OperationRecord(const std::string& op, const Complex& n1, const Complex& res)
        : operation(op), num1(n1), num2(0, 0), result(res) {}
    
    void display() const {
        if (num2.getReal() == 0 && num2.getImag() == 0) {
            std::cout << operation << " " << num1 << " = " << result;
        } else {
            std::cout << num1 << " " << operation << " " << num2 << " = " << result;
        }
        std::cout << std::endl;
    }
};

class Calculator {
private:
    std::vector<OperationRecord> history;
    
public:
    // Добавление записи в историю
    void addToHistory(const OperationRecord& record) {
        history.push_back(record);
    }
    
    // Просмотр истории операций
    void viewHistory() const {
        if (history.empty()) {
            std::cout << "История операций пуста." << std::endl;
            return;
        }
        
        std::cout << "\n=== История операций ===" << std::endl;
        for (size_t i = 0; i < history.size(); ++i) {
            std::cout << i + 1 << ". ";
            history[i].display();
        }
        std::cout << "========================\n" << std::endl;
    }
    
    // Очистка истории
    void clearHistory() {
        history.clear();
        std::cout << "История операций очищена." << std::endl;
    }

    void performOperations() {
        int choice;
        Complex num1, num2, result;
        
        do {
            displayMenu();
            std::cout << "Выберите операцию: ";
            std::cin >> choice;
            
            switch (choice) {
                case 1: { // Сложение
                    std::cout << "\n--- Сложение ---" << std::endl;
                    num1 = inputComplex("Введите первое число:");
                    num2 = inputComplex("Введите второе число:");
                    result = num1 + num2;
                    std::cout << "Результат: " << num1 << " + " << num2 << " = " << result << std::endl;
                    addToHistory(OperationRecord("+", num1, num2, result));
                    break;
                }
                case 2: { // Вычитание
                    std::cout << "\n--- Вычитание ---" << std::endl;
                    num1 = inputComplex("Введите первое число:");
                    num2 = inputComplex("Введите второе число:");
                    result = num1 - num2;
                    std::cout << "Результат: " << num1 << " - " << num2 << " = " << result << std::endl;
                    addToHistory(OperationRecord("-", num1, num2, result));
                    break;
                }
                case 3: { // Умножение
                    std::cout << "\n--- Умножение ---" << std::endl;
                    num1 = inputComplex("Введите первое число:");
                    num2 = inputComplex("Введите второе число:");
                    result = num1 * num2;
                    std::cout << "Результат: " << num1 << " * " << num2 << " = " << result << std::endl;
                    addToHistory(OperationRecord("*", num1, num2, result));
                    break;
                }
                case 4: { // Деление
                    std::cout << "\n--- Деление ---" << std::endl;
                    num1 = inputComplex("Введите первое число:");
                    num2 = inputComplex("Введите второе число:");
                    try {
                        result = num1 / num2;
                        std::cout << "Результат: " << num1 << " / " << num2 << " = " << result << std::endl;
                        addToHistory(OperationRecord("/", num1, num2, result));
                    } catch (const std::runtime_error& e) {
                        std::cout << "Ошибка: " << e.what() << std::endl;
                    }
                    break;
                }
                case 5: { // Инкремент
                    std::cout << "\n--- Инкремент (++x) ---" << std::endl;
                    num1 = inputComplex("Введите число:");
                    Complex original = num1;
                    result = ++num1;
                    std::cout << "Результат: ++" << original << " = " << result << std::endl;
                    addToHistory(OperationRecord("++(префикс)", original, result));
                    break;
                }
                case 6: { // Декремент
                    std::cout << "\n--- Декремент (--x) ---" << std::endl;
                    num1 = inputComplex("Введите число:");
                    Complex original = num1;
                    result = --num1;
                    std::cout << "Результат: --" << original << " = " << result << std::endl;
                    addToHistory(OperationRecord("--(префикс)", original, result));
                    break;
                }
                case 7: { // Сравнение
                    std::cout << "\n--- Сравнение модулей ---" << std::endl;
                    num1 = inputComplex("Введите первое число:");
                    num2 = inputComplex("Введите второе число:");
                    std::cout << "|" << num1 << "| = " << num1.modulus() << std::endl;
                    std::cout << "|" << num2 << "| = " << num2.modulus() << std::endl;
                    
                    if (num1 == num2) {
                        std::cout << "Модули чисел равны" << std::endl;
                    } else if (num1 < num2) {
                        std::cout << "Модуль первого числа меньше" << std::endl;
                    } else {
                        std::cout << "Модуль первого числа больше" << std::endl;
                    }
                    addToHistory(OperationRecord("сравнение", num1, num2, 
                        Complex(std::max(num1.modulus(), num2.modulus()), 0)));
                    break;
                }
                case 8: { // Унарный минус
                    std::cout << "\n--- Унарный минус ---" << std::endl;
                    num1 = inputComplex("Введите число:");
                    result = -num1;
                    std::cout << "Результат: -" << num1 << " = " << result << std::endl;
                    addToHistory(OperationRecord("унарный -", num1, result));
                    break;
                }
                case 9: { // Модуль
                    std::cout << "\n--- Модуль числа ---" << std::endl;
                    num1 = inputComplex("Введите число:");
                    double mod = num1.modulus();
                    std::cout << "Модуль " << num1 << " = " << mod << std::endl;
                    addToHistory(OperationRecord("модуль", num1, Complex(mod, 0)));
                    break;
                }
                case 10: // История
                    viewHistory();
                    break;
                case 11: // Очистка истории
                    clearHistory();
                    break;
                case 0: // Выход
                    std::cout << "Выход из программы." << std::endl;
                    break;
                default:
                    std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
            }
            
            if (choice != 0 && choice != 10 && choice != 11) {
                pause();
            }
            
        } while (choice != 0);
    }
    
private:
    void displayMenu() const {
        std::cout << "\n=== Калькулятор комплексных чисел ===" << std::endl;
        std::cout << "1. Сложение" << std::endl;
        std::cout << "2. Вычитание" << std::endl;
        std::cout << "3. Умножение" << std::endl;
        std::cout << "4. Деление" << std::endl;
        std::cout << "5. Инкремент (++x)" << std::endl;
        std::cout << "6. Декремент (--x)" << std::endl;
        std::cout << "7. Сравнение модулей" << std::endl;
        std::cout << "8. Унарный минус" << std::endl;
        std::cout << "9. Вычисление модуля" << std::endl;
        std::cout << "10. Просмотр истории операций" << std::endl;
        std::cout << "11. Очистка истории операций" << std::endl;
        std::cout << "0. Выход" << std::endl;
    }
    
    Complex inputComplex(const std::string& prompt) {
        double real, imag;
        std::cout << prompt << std::endl;
        std::cout << "  Действительная часть: ";
        std::cin >> real;
        std::cout << "  Мнимая часть: ";
        std::cin >> imag;
        return Complex(real, imag);
    }
    
    void pause() {
        std::cout << "\nНажмите Enter для продолжения...";
        std::cin.ignore();
        std::cin.get();
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

    std::cout << "\nТест арифметических операторов:" << std::endl;
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

    // Тестирование с записью в историю
    Calculator calc;
    Complex result = c1 + c2;
    calc.addToHistory(OperationRecord("+", c1, c2, result));
    
    result = ++c1;
    calc.addToHistory(OperationRecord("++", c1, result));
    
    result = c1 * c2;
    calc.addToHistory(OperationRecord("*", c1, c2, result));
    
    // Просмотр истории
    calc.viewHistory();

    calc.performOperations();
    
    return 0;
}