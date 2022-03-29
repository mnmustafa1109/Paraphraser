#include <fstream>
#include <iostream>
#include <random>
using namespace std;

// generating a random number depending on the range it gives
int gen_rand(int min, int max) {
    static random_device rand_dev;
    static mt19937 gen(rand_dev());
    uniform_int_distribution<int> distr(min, max);
    return distr(gen);
}

int main() {
    // open the file for reading input.txt
    ifstream input("input.txt");
    string line = "";

    // calcylate total lines
    int lines = 0;
    input.clear();
    input.seekg(0, ios::beg);
    while (getline(input, line)) {
        lines++;
    }

    // creat words on how many lines are
    string* words = new string[lines];

    // declaring words per line
    int synonymPerLine[lines];
    for (int i = 0; i < lines; i++) {
        synonymPerLine[i] = 0;
    }
    // store it in an int array
    input.clear();
    input.seekg(0, ios::beg);
    for (int i = 0; i < lines; i++) {
        getline(input, line);
        for (auto x : line) {
            if (x == ' ') {
                synonymPerLine[i]++;
            }
        }
    }

    // declaring string arrays to store synonyms of every lines in a sperate
    // dimension
    string** synonym = new string*[lines];
    for (int i = 0; i < lines; i++) {
        synonym[i] = new string[synonymPerLine[i]];
    }

    // save the content of the whole file into a string
    string str;
    input.clear();
    input.seekg(0, ios::beg);
    while (getline(input, line)) {
        str = str + line + "\n";
    }

    // go through that string and save the synonyms in the array
    int currentLine = 0;
    int currentWord = 0;
    bool new_line = true;
    string word = "";
    for (auto x : str) {
        if (x == ' ') {
            // if its a new line store it in the array of words
            if (new_line == true) {
                words[currentLine] = word;
                new_line = false;
            } else {
                synonym[currentLine][currentWord] = word;
                currentWord++;
            }
            word = "";
        } else if (x == '\n') {
            synonym[currentLine][currentWord] = word;
            currentWord = 0;
            currentLine++;
            // if its the last word then make new line true for next iteration
            new_line = true;
            word = "";
        } else {
            word += x;
        }
    }

    // ask user for input
    string user_input;
    cout << "Enter a sentence to be paraphrased: ";
    getline(cin, user_input);

    // search through the whole string and replace the words with synonyms
    for (auto x : user_input) {
        if (x == ' ') {
            bool found = false;
            for (int i = 0; i < lines; i++) {
                if (words[i] == word) {
                    cout << synonym[i][gen_rand(0, synonymPerLine[i] - 1)]
                         << " ";
                    found = true;
                }
            }
            if (found == false) {
                cout << word << " ";
            }
            word = "";
        } else {
            word += x;
        }
    }

    return 0;
}