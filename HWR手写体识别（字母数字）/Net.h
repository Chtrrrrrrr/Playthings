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
    int input_nodes;        // 输入层节点数
    int hidden_nodes;       // 隐藏层节点数
    int output_nodes;       // 输出层节点数
    double learning_rate;   // 学习率

    vector<vector<double>> weights_input_hidden;   // 输入层到隐藏层的权重
    vector<vector<double>> weights_hidden_output;  // 隐藏层到输出层的权重

    vector<double> inputs;      // 输入层节点的值
    vector<double> hidden;      // 隐藏层节点的值
    vector<double> outputs;     // 输出层节点的值

    vector<double> targets;     // 正确答案

    // 激活函数 sigmoid
    double sigmoid(double x) {
        return 1.0 / (1.0 + exp(-x));
    }

    // 激活函数的导数 sigmoid 的导数
    double sigmoid_derivative(double x) {
        return x * (1.0 - x);
    }

    // 随机生成权重
    double random_weight() {
        return (double)rand() / RAND_MAX * 2.0 - 1.0;
    }

public:
    // 构造函数
    NeuralNetwork(int input_nodes, int hidden_nodes, int output_nodes, double learning_rate) {
        this->input_nodes = input_nodes;
        this->hidden_nodes = hidden_nodes;
        this->output_nodes = output_nodes;
        this->learning_rate = learning_rate;

        // 初始化权重
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

    // 前向传播
    void feed_forward() {
        // 计算隐藏层节点的值
        for (int i = 0; i < hidden_nodes; i++) {
            double sum = 0.0;
            for (int j = 0; j < input_nodes; j++) {
                sum += inputs[j] * weights_input_hidden[j][i];
            }
            hidden[i] = sigmoid(sum);
        }

        // 计算输出层节点的值
        for (int i = 0; i < output_nodes; i++) {
            double sum = 0.0;
            for (int j = 0; j < hidden_nodes; j++) {
                sum += hidden[j] * weights_hidden_output[j][i];
            }
            outputs[i] = sigmoid(sum);
        }
    }

    // 反向传播
    void back_propagation() {
        // 计算输出层误差
        vector<double> output_errors(output_nodes);
        for (int i = 0; i < output_nodes; i++) {
            double error = targets[i] - outputs[i];
            output_errors[i] = error * sigmoid_derivative(outputs[i]);
        }

        // 计算隐藏层误差
        vector<double> hidden_errors(hidden_nodes);
        for (int i = 0; i < hidden_nodes; i++) {
            double error = 0.0;
            for (int j = 0; j < output_nodes; j++) {
                error += output_errors[j] * weights_hidden_output[i][j];
            }
            hidden_errors[i] = error * sigmoid_derivative(hidden[i]);
        }

        // 更新隐藏层到输出层的权重
        for (int i = 0; i < hidden_nodes; i++) {
            for (int j = 0; j < output_nodes; j++) {
                double delta = learning_rate * output_errors[j] * hidden[i];
                weights_hidden_output[i][j] += delta;
            }
        }

        // 更新输入层到隐藏层的权重
        for (int i = 0; i < input_nodes; i++) {
            for (int j = 0; j < hidden_nodes; j++) {
                double delta = learning_rate * hidden_errors[j] * inputs[i];
                weights_input_hidden[i][j] += delta;
            }
        }
    }

    // 训练函数
    void train(string image_path, char target) {
        // 初始化输入层、隐藏层、输出层
        inputs.resize(input_nodes);
        hidden.resize(hidden_nodes);
        outputs.resize(output_nodes);

        // 读取图片
        IMAGE image;
        loadimage(&image, image_path.c_str());

        // 将图片的像素点转换为输入层节点的值（0.0 ~ 1.0）
        for (int i = 0; i < input_nodes; i++) {
            int x = i % 28;
            int y = i / 28;
            inputs[i] = (double)GetPixel(GetImageHDC(&image), x, y) / 255.0;
        }

        // 将目标转换为输出层节点的值
        targets.resize(output_nodes);
        for (int i = 0; i < output_nodes; i++) {
            if (i == target - '0') {
                targets[i] = 1.0;
            }
            else {
                targets[i] = 0.0;
            }
        }

        // 前向传播
        feed_forward();

        // 反向传播
        back_propagation();
    }

    // 训练函数直接图片
    void train(IMAGE image, char target) {
        // 初始化输入层、隐藏层、输出层
        inputs.resize(input_nodes);
        hidden.resize(hidden_nodes);
        outputs.resize(output_nodes);

        // 将图片的像素点转换为输入层节点的值（0.0 ~ 1.0）
        for (int i = 0; i < input_nodes; i++) {
            int x = i % 28;
            int y = i / 28;
            inputs[i] = (double)GetPixel(GetImageHDC(&image), x, y) / 255.0;
        }

        // 将目标转换为输出层节点的值
        targets.resize(output_nodes);
        for (int i = 0; i < output_nodes; i++) {
            if (i == target - '0') {
                targets[i] = 1.0;
            }
            else {
                targets[i] = 0.0;
            }
        }

        // 前向传播
        feed_forward();

        // 反向传播
        back_propagation();
    }

    // 使用函数
    char predict(string image_path) {
        // 初始化输入层、隐藏层、输出层
        inputs.resize(input_nodes);
        hidden.resize(hidden_nodes);
        outputs.resize(output_nodes);

        // 读取图片
        IMAGE image;
        loadimage(&image, image_path.c_str());

        // 将图片的像素点转换为输入层节点的值（0.0 ~ 1.0）
        for (int i = 0; i < input_nodes; i++) {
            int x = i % 28;
            int y = i / 28;
            inputs[i] = (double)GetPixel(GetImageHDC(&image), x, y) / 255.0;
        }

        // 前向传播
        feed_forward();

        // 找到输出层节点值最大的节点
        int max_index = 0;
        double max_value = outputs[0];
        for (int i = 1; i < output_nodes; i++) {
            if (outputs[i] > max_value) {
                max_index = i;
                max_value = outputs[i];
            }
        }

        // 将输出层节点的值转换为字符
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

    // 使用函数
    char predict(IMAGE image) {
        // 初始化输入层、隐藏层、输出层
        inputs.resize(input_nodes);
        hidden.resize(hidden_nodes);
        outputs.resize(output_nodes);

        // 将图片的像素点转换为输入层节点的值（0.0 ~ 1.0）
        for (int i = 0; i < input_nodes; i++) {
            int x = i % 28;
            int y = i / 28;
            inputs[i] = (double)GetPixel(GetImageHDC(&image), x, y) / 255.0;
        }

        // 前向传播
        feed_forward();

        // 找到输出层节点值最大的节点
        int max_index = 0;
        double max_value = outputs[0];
        for (int i = 1; i < output_nodes; i++) {
            if (outputs[i] > max_value) {
                max_index = i;
                max_value = outputs[i];
            }
        }

        // 将输出层节点的值转换为字符
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

    // 读取函数
    void load_parameters(string file_path) {
        ifstream in(file_path);

        // 读取输入层到隐藏层的权重
        for (int i = 0; i < input_nodes; i++) {
            vector<double> row;
            for (int j = 0; j < hidden_nodes; j++) {
                double weight;
                in >> weight;
                row.push_back(weight);
            }
            weights_input_hidden.push_back(row);
        }

        // 读取隐藏层到输出层的权重
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

    // 保存函数
    void save_parameters(string file_path) {
        ofstream out(file_path);

        // 保存输入层到隐藏层的权重
        for (int i = 0; i < input_nodes; i++) {
            for (int j = 0; j < hidden_nodes; j++) {
                out << weights_input_hidden[i][j] << " ";
            }
            out << endl;
        }

        // 保存隐藏层到输出层的权重
        for (int i = 0; i < hidden_nodes; i++) {
            for (int j = 0; j < output_nodes; j++) {
                out << weights_hidden_output[i][j] << " ";
            }
            out << endl;
        }

        out.close();
    }
};
