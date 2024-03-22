#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

class Neuron {
private:
    std::vector<double> weights; // Веса нейрона
    double bias; // Смещение (bias)
    double learning_rate; // Коэффициент обучения

public:
    // Конструктор класса Neuron
    Neuron(int num_inputs, double learning_rate) : learning_rate(learning_rate) {
        // Инициализация весов случайными значениями в диапазоне [-1, 1]
        for (int i = 0; i < num_inputs; ++i) {
            weights.push_back(((double)rand() / RAND_MAX) * 2 - 1);
        }
        // Инициализация смещения (bias) случайным значением в диапазоне [-1, 1]
        bias = ((double)rand() / RAND_MAX) * 2 - 1;
    }

    // Функция активации (в данном случае - ступенчатая функция)
    int activation(double sum) {
        // Если сумма входов и смещения (bias) больше или равна нулю, возвращает 1, иначе 0
        return sum >= 0 ? 1 : 0;
    }

    // Функция предсказания нейрона
    int predict(std::vector<double>& inputs) {
        double sum = bias; // Начальное значение суммы равно смещению (bias)
        // Суммируются произведения входов на соответствующие веса
        for (int i = 0; i < inputs.size(); ++i) {
            sum += inputs[i] * weights[i];
        }
        // Применение функции активации к сумме и возвращение результата
        return activation(sum);
    }

    // Функция обучения нейрона
    void train(std::vector<double>& inputs, int target) {
        int prediction = predict(inputs); // Предсказание нейрона для данного входа
        double error = target - prediction; // Вычисление ошибки предсказания
        // Корректировка весов в соответствии с ошибкой и коэффициентом обучения
        for (int i = 0; i < weights.size(); ++i) {
            weights[i] += error * inputs[i] * learning_rate;
        }
        // Корректировка смещения (bias) в соответствии с ошибкой и коэффициентом обучения
        bias += error * learning_rate;
    }
};

int main() {
    srand(time(NULL)); // Инициализация генератора случайных чисел

    // Обучающие данные для операции "ИЛИ"
    std::vector<std::vector<double>> training_data = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
    // Ожидаемые значения для операции "ИЛИ"
    std::vector<int> targets = { 0, 1, 1, 1 };

    Neuron neuron(2, 0.1); // Создание нейрона с двумя входами и коэффициентом обучения 0.1

    // Обучение нейрона
    for (int epoch = 0; epoch < 10000; ++epoch) { // Повторяем обучение на протяжении 10000 эпох
        // Проходимся по всем обучающим примерам
        for (int i = 0; i < training_data.size(); ++i) {
            neuron.train(training_data[i], targets[i]); // Обучаем нейрон на текущем примере
        }
    }

    // Проверка обученного нейрона
    std::cout << "Testing trained neuron:\n";
    for (int i = 0; i < training_data.size(); ++i) {
        std::cout << "Input: " << training_data[i][0] << ", " << training_data[i][1] << " -> ";
        std::cout << "Prediction: " << neuron.predict(training_data[i]) << std::endl; // Предсказываем значение для каждого обучающего примера
    }

    return 0;
}