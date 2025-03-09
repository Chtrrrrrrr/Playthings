#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <easyx.h>
#include <stdlib.h>

using namespace std;

class NeuralNetwork {
private:
    int input_nodes;        // �����ڵ���
    int hidden_nodes;       // ���ز�ڵ���
    int output_nodes;       // �����ڵ���
    double learning_rate;   // ѧϰ��

    vector<vector<double>> weights_input_hidden;   // ����㵽���ز��Ȩ��
    vector<vector<double>> weights_hidden_output;  // ���ز㵽������Ȩ��

    vector<double> inputs;      // �����ڵ��ֵ
    vector<double> hidden;      // ���ز�ڵ��ֵ
    vector<double> outputs;     // �����ڵ��ֵ

    vector<double> targets;     // ��ȷ��

    // ����� sigmoid
    double sigmoid(double x) {
        return 1.0 / (1.0 + exp(-x));
    }

    // ������ĵ��� sigmoid �ĵ���
    double sigmoid_derivative(double x) {
        return x * (1.0 - x);
    }

    // �������Ȩ��
    double random_weight() {
        return (double)rand() / RAND_MAX * 2.0 - 1.0;
    }

public:
    // ���캯��
    NeuralNetwork(int input_nodes, int hidden_nodes, int output_nodes, double learning_rate) {
        this->input_nodes = input_nodes;
        this->hidden_nodes = hidden_nodes;
        this->output_nodes = output_nodes;
        this->learning_rate = learning_rate;

        // ��ʼ��Ȩ��
        for (int i = 0; i < input_nodes; i++) {
            vector<double> row;
            for (int j = 0; j < hidden_nodes; j++) {
                row.push_back(random_weight());
            }
            weights_input_hidden.push_back(row);
        }

        for (int i = 0; i < hidden_nodes; i++) {
            vector<double> row;
            for (int j = 0; j < output_nodes; j++) {
                row.push_back(random_weight());
            }
            weights_hidden_output.push_back(row);
        }
    }

    // ǰ�򴫲�
    void feed_forward() {
        // �������ز�ڵ��ֵ
        for (int i = 0; i < hidden_nodes; i++) {
            double sum = 0.0;
            for (int j = 0; j < input_nodes; j++) {
                sum += inputs[j] * weights_input_hidden[j][i];
            }
            hidden[i] = sigmoid(sum);
        }

        // ���������ڵ��ֵ
        for (int i = 0; i < output_nodes; i++) {
            double sum = 0.0;
            for (int j = 0; j < hidden_nodes; j++) {
                sum += hidden[j] * weights_hidden_output[j][i];
            }
            outputs[i] = sigmoid(sum);
        }
    }

    // ���򴫲�
    void back_propagation() {
        // ������������
        vector<double> output_errors(output_nodes);
        for (int i = 0; i < output_nodes; i++) {
            double error = targets[i] - outputs[i];
            output_errors[i] = error * sigmoid_derivative(outputs[i]);
        }

        // �������ز����
        vector<double> hidden_errors(hidden_nodes);
        for (int i = 0; i < hidden_nodes; i++) {
            double error = 0.0;
            for (int j = 0; j < output_nodes; j++) {
                error += output_errors[j] * weights_hidden_output[i][j];
            }
            hidden_errors[i] = error * sigmoid_derivative(hidden[i]);
        }

        // �������ز㵽������Ȩ��
        for (int i = 0; i < hidden_nodes; i++) {
            for (int j = 0; j < output_nodes; j++) {
                double delta = learning_rate * output_errors[j] * hidden[i];
                weights_hidden_output[i][j] += delta;
            }
        }

        // ��������㵽���ز��Ȩ��
        for (int i = 0; i < input_nodes; i++) {
            for (int j = 0; j < hidden_nodes; j++) {
                double delta = learning_rate * hidden_errors[j] * inputs[i];
                weights_input_hidden[i][j] += delta;
            }
        }
    }

    // ѵ������
    void train(string image_path, char target) {
        // ��ʼ������㡢���ز㡢�����
        inputs.resize(input_nodes);
        hidden.resize(hidden_nodes);
        outputs.resize(output_nodes);

        // ��ȡͼƬ
        IMAGE image;
        loadimage(&image, image_path.c_str());

        // ��ͼƬ�����ص�ת��Ϊ�����ڵ��ֵ��0.0 ~ 1.0��
        for (int i = 0; i < input_nodes; i++) {
            int x = i % 28;
            int y = i / 28;
            inputs[i] = (double)GetPixel(GetImageHDC(&image), x, y) / 255.0;
        }

        // ��Ŀ��ת��Ϊ�����ڵ��ֵ
        targets.resize(output_nodes);
        for (int i = 0; i < output_nodes; i++) {
            if (i == target - '0') {
                targets[i] = 1.0;
            }
            else {
                targets[i] = 0.0;
            }
        }

        // ǰ�򴫲�
        feed_forward();

        // ���򴫲�
        back_propagation();
    }

    // ѵ������ֱ��ͼƬ
    void train(IMAGE image, char target) {
        // ��ʼ������㡢���ز㡢�����
        inputs.resize(input_nodes);
        hidden.resize(hidden_nodes);
        outputs.resize(output_nodes);

        // ��ͼƬ�����ص�ת��Ϊ�����ڵ��ֵ��0.0 ~ 1.0��
        for (int i = 0; i < input_nodes; i++) {
            int x = i % 28;
            int y = i / 28;
            inputs[i] = (double)GetPixel(GetImageHDC(&image), x, y) / 255.0;
        }

        // ��Ŀ��ת��Ϊ�����ڵ��ֵ
        targets.resize(output_nodes);
        for (int i = 0; i < output_nodes; i++) {
            if (i == target - '0') {
                targets[i] = 1.0;
            }
            else {
                targets[i] = 0.0;
            }
        }

        // ǰ�򴫲�
        feed_forward();

        // ���򴫲�
        back_propagation();
    }

    // ʹ�ú���
    char predict(string image_path) {
        // ��ʼ������㡢���ز㡢�����
        inputs.resize(input_nodes);
        hidden.resize(hidden_nodes);
        outputs.resize(output_nodes);

        // ��ȡͼƬ
        IMAGE image;
        loadimage(&image, image_path.c_str());

        // ��ͼƬ�����ص�ת��Ϊ�����ڵ��ֵ��0.0 ~ 1.0��
        for (int i = 0; i < input_nodes; i++) {
            int x = i % 28;
            int y = i / 28;
            inputs[i] = (double)GetPixel(GetImageHDC(&image), x, y) / 255.0;
        }

        // ǰ�򴫲�
        feed_forward();

        // �ҵ������ڵ�ֵ���Ľڵ�
        int max_index = 0;
        double max_value = outputs[0];
        for (int i = 1; i < output_nodes; i++) {
            if (outputs[i] > max_value) {
                max_index = i;
                max_value = outputs[i];
            }
        }

        // �������ڵ��ֵת��Ϊ�ַ�
        if (max_index <= 9) {
            return '0' + max_index;
        }
        else if (max_index <= 35) {
            return 'a' + max_index - 10;
        }
        else {
            return 'A' + max_index - 36;
        }
    }

    // ʹ�ú���
    char predict(IMAGE image) {
        // ��ʼ������㡢���ز㡢�����
        inputs.resize(input_nodes);
        hidden.resize(hidden_nodes);
        outputs.resize(output_nodes);

        // ��ͼƬ�����ص�ת��Ϊ�����ڵ��ֵ��0.0 ~ 1.0��
        for (int i = 0; i < input_nodes; i++) {
            int x = i % 28;
            int y = i / 28;
            inputs[i] = (double)GetPixel(GetImageHDC(&image), x, y) / 255.0;
        }

        // ǰ�򴫲�
        feed_forward();

        // �ҵ������ڵ�ֵ���Ľڵ�
        int max_index = 0;
        double max_value = outputs[0];
        for (int i = 1; i < output_nodes; i++) {
            if (outputs[i] > max_value) {
                max_index = i;
                max_value = outputs[i];
            }
        }

        // �������ڵ��ֵת��Ϊ�ַ�
        if (max_index <= 9) {
            return '0' + max_index;
        }
        else if (max_index <= 35) {
            return 'a' + max_index - 10;
        }
        else {
            return 'A' + max_index - 36;
        }
    }

    // ��ȡ����
    void load_parameters(string file_path) {
        ifstream in(file_path);

        // ��ȡ����㵽���ز��Ȩ��
        for (int i = 0; i < input_nodes; i++) {
            vector<double> row;
            for (int j = 0; j < hidden_nodes; j++) {
                double weight;
                in >> weight;
                row.push_back(weight);
            }
            weights_input_hidden.push_back(row);
        }

        // ��ȡ���ز㵽������Ȩ��
        for (int i = 0; i < hidden_nodes; i++) {
            vector<double> row;
            for (int j = 0; j < output_nodes; j++) {
                double weight;
                in >> weight;
                row.push_back(weight);
            }
            weights_hidden_output.push_back(row);
        }

        in.close();
    }

    // ���溯��
    void save_parameters(string file_path) {
        ofstream out(file_path);

        // ��������㵽���ز��Ȩ��
        for (int i = 0; i < input_nodes; i++) {
            for (int j = 0; j < hidden_nodes; j++) {
                out << weights_input_hidden[i][j] << " ";
            }
            out << endl;
        }

        // �������ز㵽������Ȩ��
        for (int i = 0; i < hidden_nodes; i++) {
            for (int j = 0; j < output_nodes; j++) {
                out << weights_hidden_output[i][j] << " ";
            }
            out << endl;
        }

        out.close();
    }
};
