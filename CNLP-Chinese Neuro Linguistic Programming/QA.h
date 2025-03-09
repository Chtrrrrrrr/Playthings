#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class QA {
private:
    unordered_map<string, vector<string>> data; // 哈希表存储问题和答案
    double similarityThreshold = 0.65; // 相似度阈值

public:
    bool save(string filename) {
        ofstream file(filename);
        if (!file.is_open()) return false;
        for (auto it = data.begin(); it != data.end(); ++it) {
            file << it->first << " ";
            for (auto ans : it->second) {
                file << ans << " ";
            }
            file << endl;
        }
        file.close();
        return true;
    }

    bool load(string filename) {
        ifstream file(filename);
        if (!file.is_open()) return false;
        string line;
        while (getline(file, line)) {
            vector<string> tokens;
            size_t pos = 0;
            while ((pos = line.find(" ")) != string::npos) {
                string token = line.substr(0, pos);
                tokens.push_back(token);
                line.erase(0, pos + 1);
            }
            string question = tokens[0];
            tokens.erase(tokens.begin());
            data[question] = tokens;
        }
        file.close();
        return true;
    }

    void insert(string question, string answer) {
        if (data.find(question) != data.end()) {
            data[question].push_back(answer);
        }
        else {
            vector<string> answers;
            answers.push_back(answer);
            data[question] = answers;
        }
    }

    string find(string question) {
        if (data.find(question) != data.end()) {
            vector<string> answers = data[question];
            if (answers.size() == 1) {
                return answers[0];
            }
            else {
                int index = rand() % answers.size();
                return answers[index];
            }
        }
        else {
            double maxSim = 0;
            string bestMatch;
            for (auto it = data.begin(); it != data.end(); ++it) {
                string q = it->first;
                double sim = similarity(question, q);
                if (sim > maxSim) {
                    maxSim = sim;
                    bestMatch = q;
                }
            }
            if (maxSim >= similarityThreshold) {
                vector<string> answers = data[bestMatch];
                if (answers.size() == 1) {
                    return answers[0];
                }
                else {
                    int index = rand() % answers.size();
                    return answers[index];
                }
            }
            else {
                return "";
            }
        }
    }

    double similarity(string s1, string s2) {
        if (s1 == s2) return 1.0;
        int n = s1.length();
        int m = s2.length();
        if (n == 0 || m == 0) return 0.0;
        vector<vector<double>> dp(n + 1, vector<double>(m + 1, 0));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[n][m] / max(n, m);
    }
};