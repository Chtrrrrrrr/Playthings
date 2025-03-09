#include "NeuralNetwork.h"
#include "Translate.h"
#include "QA.h"

#include <chrono>
#include <thread>
#include <random>

NeuralNetwork neuralNetwork;
vector<WordPair> wordPairs;
QA Qu2An;

void SaveUnknownQuestion(const std::string& q) {
    std::ofstream file("UnknownQuestion.unk", std::ios::app);
    if (file.is_open()) {
        file << q << std::endl;
        file.close();
    }
    else {
        std::cout << "Error:Unable to open file.";
    }
}
void train(string q, string a)
{
    Qu2An.insert(q, a);
    neuralNetwork.train(q, a);
}
void TranslateAdd(string c, string e)
{
    addWordPair(wordPairs, c, e);
}
void Save()
{
    neuralNetwork.save();
    saveWordPairsToFile("Translate.mdl", wordPairs);
    Qu2An.save("Question-Answer.mdl");
}
void Load()
{
    neuralNetwork.load();
    wordPairs = readWordPairsFromFile("Translate.mdl");
    Qu2An.load("Question-Answer.mdl");
}
string Chat(string q)
{
    if (Qu2An.find(q) != "")
        return Qu2An.find(q);
    else if (neuralNetwork.chat(q) != "Sorry, I don't know.")
        return neuralNetwork.chat(q);
    else
    {
        SaveUnknownQuestion(q);
        return "¶Ô²»Æð£¬ÎÒ²»ÖªµÀ£¬ÎÊÎÊÆäËûÄÚÈÝ°É£¨¸ÃÎÊÌâÒÑ¼ÇÂ¼·´À¡£©";
    }
}
void printstr(const std::string& str) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> char_dist(2, 4);
    std::uniform_real_distribution<> time_dist(0.01, 0.1);

    for (std::size_t i = 0; i < str.size();) {
        int len = char_dist(gen);
        if (i + len > str.size()) {
            len = str.size() - i;
        }
        std::string substr = str.substr(i, len);
        std::cout << substr;
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(time_dist(gen) * 1000)));
        i += len;
    }
}
int main() 
{
    Load();
    cout << "CNLP-Chinese Neuro Linguistic Proguamming Model\n" << "¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª\n";
    string question;
    string answer;
    for (;;) {
        cout << "|Äã|: ";
        getline(cin, question);
        cout << "¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª\n";
        if (question == "Î´Öª¼ÇÂ¼")
        {
            ifstream file("UnknownQuestion.unk");
            if (!file.is_open()) return false;
            string line;
            while (getline(file, line)) {
                cout << "Question:" << line << endl<<"Answer:";
                getline(cin, question);
                train(line, question);
                cout << "Success!\n";
            }
            file.close();
            Save();
        }
        if (question == "ÄãËµÊ²Ã´" || question == "ÔÙËµÒ»±é")
        {
            cout << "|CNLP|: ";
            printstr(answer);
            cout << endl << "¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª\n";
        }
        else
        {
            answer = Chat(question);
            cout << "|CNLP|: ";
            printstr(answer);
            cout << endl << "¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª\n";
        }
    }
    
    return 0;
}