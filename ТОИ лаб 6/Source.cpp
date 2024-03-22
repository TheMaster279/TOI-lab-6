#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

class Neuron {
private:
    std::vector<double> weights; // ���� �������
    double bias; // �������� (bias)
    double learning_rate; // ����������� ��������

public:
    // ����������� ������ Neuron
    Neuron(int num_inputs, double learning_rate) : learning_rate(learning_rate) {
        // ������������� ����� ���������� ���������� � ��������� [-1, 1]
        for (int i = 0; i < num_inputs; ++i) {
            weights.push_back(((double)rand() / RAND_MAX) * 2 - 1);
        }
        // ������������� �������� (bias) ��������� ��������� � ��������� [-1, 1]
        bias = ((double)rand() / RAND_MAX) * 2 - 1;
    }

    // ������� ��������� (� ������ ������ - ����������� �������)
    int activation(double sum) {
        // ���� ����� ������ � �������� (bias) ������ ��� ����� ����, ���������� 1, ����� 0
        return sum >= 0 ? 1 : 0;
    }

    // ������� ������������ �������
    int predict(std::vector<double>& inputs) {
        double sum = bias; // ��������� �������� ����� ����� �������� (bias)
        // ����������� ������������ ������ �� ��������������� ����
        for (int i = 0; i < inputs.size(); ++i) {
            sum += inputs[i] * weights[i];
        }
        // ���������� ������� ��������� � ����� � ����������� ����������
        return activation(sum);
    }

    // ������� �������� �������
    void train(std::vector<double>& inputs, int target) {
        int prediction = predict(inputs); // ������������ ������� ��� ������� �����
        double error = target - prediction; // ���������� ������ ������������
        // ������������� ����� � ������������ � ������� � ������������� ��������
        for (int i = 0; i < weights.size(); ++i) {
            weights[i] += error * inputs[i] * learning_rate;
        }
        // ������������� �������� (bias) � ������������ � ������� � ������������� ��������
        bias += error * learning_rate;
    }
};

int main() {
    srand(time(NULL)); // ������������� ���������� ��������� �����

    // ��������� ������ ��� �������� "���"
    std::vector<std::vector<double>> training_data = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
    // ��������� �������� ��� �������� "���"
    std::vector<int> targets = { 0, 1, 1, 1 };

    Neuron neuron(2, 0.1); // �������� ������� � ����� ������� � ������������� �������� 0.1

    // �������� �������
    for (int epoch = 0; epoch < 10000; ++epoch) { // ��������� �������� �� ���������� 10000 ����
        // ���������� �� ���� ��������� ��������
        for (int i = 0; i < training_data.size(); ++i) {
            neuron.train(training_data[i], targets[i]); // ������� ������ �� ������� �������
        }
    }

    // �������� ���������� �������
    std::cout << "Testing trained neuron:\n";
    for (int i = 0; i < training_data.size(); ++i) {
        std::cout << "Input: " << training_data[i][0] << ", " << training_data[i][1] << " -> ";
        std::cout << "Prediction: " << neuron.predict(training_data[i]) << std::endl; // ������������� �������� ��� ������� ���������� �������
    }

    return 0;
}