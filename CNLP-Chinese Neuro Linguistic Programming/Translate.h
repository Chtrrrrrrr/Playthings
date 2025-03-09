#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// 定义一个结构体，用于存储单词对照
struct WordPair {
    string chinese;
    string english;
};

// 定义一个函数，用于保存单词对照到文件
void saveWordPairsToFile(const string& filename, const vector<WordPair>& wordPairs) {
    ofstream ofs(filename);
    if (!ofs) {
        cerr << "Error: Cannot open file " << filename << endl;
        return;
    }
    for (const auto& pair : wordPairs) {
        ofs << pair.chinese << "\t" << pair.english << endl;
    }
    ofs.close();
    cout << "Word pairs saved to file " << filename << endl;
}

// 定义一个函数，用于从文件中读取单词对照
vector<WordPair> readWordPairsFromFile(const string& filename) {
    vector<WordPair> wordPairs;
    ifstream ifs(filename);
    if (!ifs) {
        cerr << "Error: Cannot open file " << filename << endl;
        return wordPairs;
    }
    string line;
    while (getline(ifs, line)) {
        istringstream iss(line);
        string chinese, english;
        if (iss >> chinese >> english) {
            wordPairs.push_back({ chinese, english });
        }
    }
    ifs.close();
    cout << "Word pairs read from file " << filename << endl;
    return wordPairs;
}

// 定义一个函数，用于添加单词对照
void addWordPair(vector<WordPair>& wordPairs, const string& chinese, const string& english) {
    auto it = find_if(wordPairs.begin(), wordPairs.end(), [&chinese](const WordPair& pair) {return pair.chinese == chinese; });
    if (it != wordPairs.end()) {
        it->english = english;
    }
    else {
        wordPairs.push_back({ chinese, english });
    }
}

// 定义一个函数，用于中英文互译
string translate(const string& text, const vector<WordPair>& wordPairs, bool englishToChinese) {
    string result;
    bool inCodeBlock = false;
    for (auto it = text.begin(); it != text.end(); ) {
        if (*it == '`') {
            inCodeBlock = !inCodeBlock;
            result += *it;
            ++it;
            while (it != text.end() && *it != '`') {
                result += *it;
                ++it;
            }
            if (it != text.end()) {
                result += *it;
                ++it;
            }
        }
        else if (!inCodeBlock && it + 1 != text.end() && *it == '/' && *(it + 1) == '/') {
            while (it != text.end() && *it != '\n') {
                ++it;
            }
        }
        else {
            string word;
            while (it != text.end() && !isspace(*it)) {
                word += *it;
                ++it;
            }
            if (!word.empty()) {
                auto wp = find_if(wordPairs.begin(), wordPairs.end(), [&word](const WordPair& pair) {return pair.chinese == word || pair.english == word; });
                if (wp != wordPairs.end()) {
                    result += englishToChinese ? wp->chinese : wp->english;
                }
                else {
                    // 找相似词
                    string similarWord;
                    int maxScore = 0;
                    for (const auto& pair : wordPairs) {
                        int score = 0;
                        for (int i = 0; i < word.size(); ++i) {
                            if (pair.chinese.find(word[i]) != string::npos || pair.english.find(word[i]) != string::npos) {
                                ++score;
                            }
                        }
                        if (score > maxScore) {
                            maxScore = score;
                            similarWord = englishToChinese ? pair.chinese : pair.english;
                        }
                    }
                    if (maxScore * 2 >= word.size()) {
                        result += similarWord;
                    }
                    else {
                        result += "[unknown]";
                    }
                }
            }
            if (it != text.end()) {
                result += *it;
                ++it;
            }
        }
    }
    return result;
}
