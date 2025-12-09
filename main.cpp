#include <iostream>
#include <cmath>
#include <vector>

/**
 * @class Complex
 * @brief Класс для представления комплексных чисел
 * 
 * Класс представляет комплексное число вида a + bi, где a - действительная часть,
 * b - мнимая часть, i - мнимая единица. Реализованы основные математические операции
 * и перегрузки операторов.
 */
class Complex {
private:
    double real;        ///< Действительная часть комплексного числа
    double imag;        ///< Мнимая часть комплексного числа
    static int count;   ///< Статический счетчик созданных объектов

public:
    /**
     * @brief Конструктор по умолчанию
     * 
     * Создает комплексное число 0 + 0i
     */
    Complex() : real(0), imag(0) {count++;}

    /**
     * @brief Конструктор с параметрами
     * @param r Действительная часть
     * @param i Мнимая часть (по умолчанию 0)
     */
    Complex(double r, double i = 0) : real(r), imag(i) {count++;}

    /**
     * @brief Деструктор
     * 
     * Уменьшает счетчик объектов при уничтожении
     */
    ~Complex(){count--;}
    
    /**
     * @brief Возвращает действительную часть
     * @return Действительная часть комплексного числа
     */
    double getReal() const { return real; }
    
    /**
     * @brief Возвращает мнимую часть
     * @return Мнимая часть комплексного числа
     */
    double getImag() const { return imag; }
    
    /**
     * @brief Устанавливает действительную часть
     * @param r Новое значение действительной части
     */
    void setReal(double r) { real = r; }
    
    /**
     * @brief Устанавливает мнимую часть
     * @param i Новое значение мнимой части
     */
    void setImag(double i) { imag = i; }
    
    /**
     * @brief Вычисляет модуль комплексного числа
     * @return Модуль комплексного числа
     * 
     * Формула: √(real² + imag²)
     */
    double modulus() const {
        return std::sqrt(real * real + imag * imag);
    }
    
    /**
     * @brief Оператор вывода комплексного числа в поток
     * @param os Выходной поток
     * @param c Комплексное число для вывода
     * @return Ссылка на выходной поток
     * 
     * Форматы вывода:
     * - Если imag = 0: выводится только real
     * - Если real = 0: выводится imag + "i"
     * - Если imag > 0: "real + imag i"
     * - Если imag < 0: "real - |imag| i"
     */
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

    /**
     * @brief Префиксный инкремент (++complex)
     * @return Ссылка на измененный объект
     * 
     * Увеличивает действительную часть на 1
     */
    Complex& operator++() {
        ++real;
        return *this;
    }
    
    /**
     * @brief Постфиксный инкремент (complex++)
     * @return Копия объекта до инкремента
     * 
     * Увеличивает действительную часть на 1,
     * возвращает старое значение
     */
    Complex operator++(int) {
        Complex temp = *this;
        ++real;
        return temp;
    }
    
    /**
     * @brief Префиксный декремент (--complex)
     * @return Ссылка на измененный объект
     * 
     * Уменьшает действительную часть на 1
     */
    Complex& operator--() {
        --real;
        return *this;
    }
    
    /**
     * @brief Постфиксный декремент (complex--)
     * @return Копия объекта до декремента
     * 
     * Уменьшает действительную часть на 1,
     * возвращает старое значение
     */
    Complex operator--(int) {
        Complex temp = *this;
        --real;
        return temp;
    }
    
    /**
     * @brief Унарный минус
     * @return Новый объект с противоположными знаками обеих частей
     */
    Complex operator-() const {
        return Complex(-real, -imag);
    }

    /**
     * @brief Сложение комплексных чисел
     * @param other Второе слагаемое
     * @return Результат сложения
     */
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    /**
     * @brief Вычитание комплексных чисел
     * @param other Вычитаемое
     * @return Результат вычитания
     */
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }
    
    /**
     * @brief Умножение комплексных чисел
     * @param other Второй множитель
     * @return Результат умножения
     * 
     * Формула: (a+bi)(c+di) = (ac-bd) + (ad+bc)i
     */
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                      real * other.imag + imag * other.real);
    }
    
    /**
     * @brief Деление комплексных чисел
     * @param other Делитель
     * @return Результат деления
     * @throw std::runtime_error При делении на ноль
     * 
     * Формула: (a+bi)/(c+di) = ((ac+bd)/(c²+d²)) + ((bc-ad)/(c²+d²))i
     */
    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        if (denominator == 0) {
            throw std::runtime_error("Деление на ноль!");
        }
        return Complex((real * other.real + imag * other.imag) / denominator,
                      (imag * other.real - real * other.imag) / denominator);
    }
    
    /**
     * @brief Оператор "меньше" (сравнение модулей)
     * @param other Второе комплексное число
     * @return true если модуль текущего числа меньше модуля other
     */
    bool operator<(const Complex& other) const {
        return this->modulus() < other.modulus();
    }
    
    /**
     * @brief Оператор "больше" (сравнение модулей)
     * @param other Второе комплексное число
     * @return true если модуль текущего числа больше модуля other
     */
    bool operator>(const Complex& other) const {
        return this->modulus() > other.modulus();
    }
    
    /**
     * @brief Оператор "меньше или равно" (сравнение модулей)
     * @param other Второе комплексное число
     * @return true если модуль текущего числа ≤ модулю other
     */
    bool operator<=(const Complex& other) const {
        return this->modulus() <= other.modulus();
    }
    
    /**
     * @brief Оператор "больше или равно" (сравнение модулей)
     * @param other Второе комплексное число
     * @return true если модуль текущего числа ≥ модулю other
     */
    bool operator>=(const Complex& other) const {
        return this->modulus() >= other.modulus();
    }
    
    /**
     * @brief Оператор равенства (сравнение компонентов)
     * @param other Второе комплексное число
     * @return true если действительные и мнимые части равны
     */
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }
    
    /**
     * @brief Оператор неравенства
     * @param other Второе комплексное число
     * @return true если числа не равны
     */
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
};

/**
 * @struct OperationRecord
 * @brief Запись об операции для истории вычислений
 * 
 * Хранит информацию об одной выполненной операции:
 * тип операции, операнды и результат.
 */
struct OperationRecord {
    std::string operation;  ///< Тип операции (+, -, *, / и т.д.)
    Complex num1;           ///< Первый операнд
    Complex num2;           ///< Второй операнд (может быть пустым для унарных операций)
    Complex result;         ///< Результат операции
    
    /**
     * @brief Конструктор для бинарных операций
     * @param op Тип операции
     * @param n1 Первый операнд
     * @param n2 Второй операнд
     * @param res Результат операции
     */
    OperationRecord(const std::string& op, const Complex& n1, const Complex& n2, const Complex& res)
        : operation(op), num1(n1), num2(n2), result(res) {}
    
    /**
     * @brief Конструктор для унарных операций
     * @param op Тип операции
     * @param n1 Операнд
     * @param res Результат операции
     */
    OperationRecord(const std::string& op, const Complex& n1, const Complex& res)
        : operation(op), num1(n1), num2(0, 0), result(res) {}
    
    /**
     * @brief Вывод информации об операции
     * 
     * Формат вывода зависит от типа операции:
     * - Для унарных: "операция число = результат"
     * - Для бинарных: "число1 операция число2 = результат"
     */
    void display() const {
        if (num2.getReal() == 0 && num2.getImag() == 0) {
            std::cout << operation << " " << num1 << " = " << result;
        } else {
            std::cout << num1 << " " << operation << " " << num2 << " = " << result;
        }
        std::cout << std::endl;
    }
};

/**
 * @class Calculator
 * @brief Калькулятор комплексных чисел с историей операций
 * 
 * Предоставляет интерфейс для выполнения операций над комплексными числами
 * и ведения истории выполненных операций.
 */
class Calculator {
private:
    std::vector<OperationRecord> history;  ///< Вектор для хранения истории операций
    
public:
    /**
     * @brief Добавляет запись в историю операций
     * @param record Запись для добавления
     */
    void addToHistory(const OperationRecord& record) {
        history.push_back(record);
    }
    
    /**
     * @brief Просмотр истории операций
     * 
     * Выводит все сохраненные операции в порядке их выполнения.
     * Если история пуста, выводит соответствующее сообщение.
     */
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
    
    /**
     * @brief Очистка истории операций
     * 
     * Удаляет все записи из истории.
     */
    void clearHistory() {
        history.clear();
        std::cout << "История операций очищена." << std::endl;
    }

    /**
     * @brief Основной цикл работы калькулятора
     * 
     * Предоставляет интерактивное меню для выбора операций:
     * 1. Сложение
     * 2. Вычитание
     * 3. Умножение
     * 4. Деление
     * 5. Инкремент
     * 6. Декремент
     * 7. Сравнение модулей
     * 8. Унарный минус
     * 9. Вычисление модуля
     * 10. Просмотр истории
     * 11. Очистка истории
     * 0. Выход
     */
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
    /**
     * @brief Вывод меню операций
     */
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
    
    /**
     * @brief Ввод комплексного числа с консоли
     * @param prompt Приглашение для ввода
     * @return Введенное комплексное число
     */
    Complex inputComplex(const std::string& prompt) {
        double real, imag;
        std::cout << prompt << std::endl;
        std::cout << "  Действительная часть: ";
        std::cin >> real;
        std::cout << "  Мнимая часть: ";
        std::cin >> imag;
        return Complex(real, imag);
    }
    
    /**
     * @brief Пауза выполнения программы
     * 
     * Ожидает нажатия клавиши Enter для продолжения
     */
    void pause() {
        std::cout << "\nНажмите Enter для продолжения...";
        std::cin.ignore();
        std::cin.get();
    }
};

/**
 * @brief Инициализация статической переменной-счетчика
 */
int Complex::count = 0;

/**
 * @brief Основная функция программы
 * @return Код завершения программы
 * 
 * Демонстрирует работу всех функций программы:
 * 1. Создание и тестирование объектов Complex
 * 2. Демонстрация всех перегруженных операторов
 * 3. Тестирование системы истории операций
 * 4. Запуск интерактивного режима калькулятора
 */
int main() {
    // Демонстрация создания объектов Complex
    Complex c1(3, 4);
    Complex c2(1, -2);
    Complex c3(3, 4);

    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "c2 = " << c2 << std::endl;
    std::cout << "c3 = " << c3 << std::endl;
    std::cout << "Модуль c1 = " << c1.modulus() << std::endl;

    // Тестирование унарных операторов
    std::cout << "\nТест унарных операторов:" << std::endl;
    std::cout << "++c1 = " << ++c1 << std::endl;
    std::cout << "c2-- = " << c2-- << std::endl;
    std::cout << "После c2--: c2 = " << c2 << std::endl;
    std::cout << "-c1 = " << -c1 << std::endl;

    // Тестирование арифметических операторов
    std::cout << "\nТест арифметических операторов:" << std::endl;
    std::cout << "c1 + c2 = " << c1 + c2 << std::endl;
    std::cout << "c1 - c2 = " << c1 - c2 << std::endl;
    std::cout << "c1 * c2 = " << c1 * c2 << std::endl;
    std::cout << "c1 / Complex(2, 0) = " << c1 / Complex(2, 0) << std::endl;

    // Обновление значений после операций
    std::cout << "\nc1 = " << c1 << std::endl;
    std::cout << "c2 = " << c2 << std::endl;
    std::cout << "c3 = " << c3 << std::endl;
    
    // Тестирование операторов сравнения
    std::cout << "\nТест операторов сравнения (по модулю):" << std::endl;
    std::cout << "c1 < c2: " << (c1 < c2 ? "true" : "false") << std::endl;
    std::cout << "c1 > c2: " << (c1 > c2 ? "true" : "false") << std::endl;
    std::cout << "c1 == c3: " << (c1 == c3 ? "true" : "false") << std::endl;

    // Тестирование системы истории операций
    Calculator calc;
    Complex result = c1 + c2;
    calc.addToHistory(OperationRecord("+", c1, c2, result));
    
    result = ++c1;
    calc.addToHistory(OperationRecord("++", c1, result));
    
    result = c1 * c2;
    calc.addToHistory(OperationRecord("*", c1, c2, result));
    
    // Просмотр истории операций
    calc.viewHistory();

    // Запуск интерактивного режима калькулятора
    calc.performOperations();
    
    return 0;
}