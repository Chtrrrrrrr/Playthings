#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>

using namespace std;

class NeuralNetwork {
private:
    map<string, vector<double>> wordVectors; // Mapping of words to their corresponding word vectors
    map<string, vector<double>> contextVectors; // Mapping of context to their corresponding context vectors
    vector<string> contextMemory; // History of context

public:
    void train(string question, string answer) {
        vector<string> questionTokens = tokenize(question);
        vector<string> answerTokens = tokenize(answer);

        // Update word vectors
        for (string token : questionTokens) {
            if (wordVectors.find(token) == wordVectors.end()) {
                wordVectors[token] = generateRandomVector();
            }
        }

        // Update context vectors
        for (string token : answerTokens) {
            if (contextVectors.find(token) == contextVectors.end()) {
                contextVectors[token] = generateRandomVector();
            }
        }

        // Update context memory
        for (string token : answerTokens) {
            contextMemory.push_back(token);
        }
    }

    string chat(string question) {
        vector<string> questionTokens = tokenize(question);
        vector<double> questionVector = generateSentenceVector(questionTokens);
        double maxSimilarity = -1;
        string bestAnswer = "Sorry, I don't know.";

        // Find the most similar context vector
        for (auto& contextVectorPair : contextVectors) {
            double similarity = calculateSimilarity(questionVector, contextVectorPair.second);
            if (similarity > maxSimilarity) {
                maxSimilarity = similarity;
                bestAnswer = contextVectorPair.first;
            }
        }

        return bestAnswer;
    }

    void save() {
        ofstream file("Model.mdl");
        if (file.is_open()) {
            // Save word vectors
            file << "Word Vectors:\n";
            for (auto& wordVectorPair : wordVectors) {
                file << wordVectorPair.first << " ";
                for (double value : wordVectorPair.second) {
                    file << value << " ";
                }
                file << "\n";
            }

            // Save context vectors
            file << "Context Vectors:\n";
            for (auto& contextVectorPair : contextVectors) {
                file << contextVectorPair.first << " ";
                for (double value : contextVectorPair.second) {
                    file << value << " ";
                }
                file << "\n";
            }

            // Save context memory
            file << "Context Memory:\n";
            for (string token : contextMemory) {
                file << token << " ";
            }
            file << "\n";

            file.close();
        }
    }

    void load() {
        ifstream file("Model.mdl");
        if (file.is_open()) {
            string line;
            string section;
            while (getline(file, line)) {
                if (line == "Word Vectors:") {
                    section = "Word Vectors";
                }
                else if (line == "Context Vectors:") {
                    section = "Context Vectors";
                }
                else if (line == "Context Memory:") {
                    section = "Context Memory";
                }
                else {
                    if (section == "Word Vectors") {
                        vector<string> tokens = splitString(line, ' ');
                        string word = tokens[0];
                        vector<double> vector;
                        for (int i = 1; i < tokens.size(); i++) {
                            vector.push_back(stod(tokens[i]));
                        }
                        wordVectors[word] = vector;
                    }
                    else if (section == "Context Vectors") {
                        vector<string> tokens = splitString(line, ' ');
                        string context = tokens[0];
                        vector<double> vector;
                        for (int i = 1; i < tokens.size(); i++) {
                            vector.push_back(stod(tokens[i]));
                        }
                        contextVectors[context] = vector;
                    }
                    else if (section == "Context Memory") {
                        vector<string> tokens = splitString(line, ' ');
                        for (string token : tokens) {
                            contextMemory.push_back(token);
                        }
                    }
                }
            }
            file.close();
        }
    }

    void clear() {
        contextMemory.clear();
    }

private:
    vector<string> tokenize(string text) {
        vector<string> tokens;
        string token;
        for (char c : text) {
            if (c == ' ') {
                if (!token.empty()) {
                    tokens.push_back(token);
                    token.clear();
                }
            }
            else {
                token.push_back(c);
            }
        }
        if (!token.empty()) {
            tokens.push_back(token);
        }
        return tokens;
    }

    vector<string> splitString(string text, char delimiter) {
        vector<string> tokens;
        string token;
        for (char c : text) {
            if (c == delimiter) {
                if (!token.empty()) {
                    tokens.push_back(token);
                    token.clear();
                }
            }
            else {
                token.push_back(c);
            }
        }
        if (!token.empty()) {
            tokens.push_back(token);
        }
        return tokens;
    }

    vector<double> generateRandomVector() {
        vector<double> vector;
        for (int i = 0; i < 100; i++) {
            double value = (double)rand() / RAND_MAX;
            vector.push_back(value);
        }
        return vector;
    }

    vector<double> generateSentenceVector(vector<string>& tokens) {
        vector<double> sentenceVector(100, 0);
        for (string token : tokens) {
            if (wordVectors.find(token) != wordVectors.end()) {
                vector<double>& wordVector = wordVectors[token];
                for (int i = 0; i < 100; i++) {
                    sentenceVector[i] += wordVector[i];
                }
            }
        }
        return sentenceVector;
    }

    double calculateSimilarity(vector<double>& vector1, vector<double>& vector2) {
        double dotProduct = 0;
        double norm1 = 0;
        double norm2 = 0;
        for (int i = 0; i < 100; i++) {
            dotProduct += vector1[i] * vector2[i];
            norm1 += pow(vector1[i], 2);
            norm2 += pow(vector2[i], 2);
        }
        norm1 = sqrt(norm1);
        norm2 = sqrt(norm2);
        return dotProduct / (norm1 * norm2);
    }
};
