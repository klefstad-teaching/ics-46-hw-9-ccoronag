#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error creating word ladder from \"" << word1 << "\" to \"" << word2 << "\": " << msg << endl;
}



bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    const int word1_len = str1.length();
    const int word2_len = str2.length();
    int cache[word1_len+1][word2_len+1];
    for (int i = 0; i < word1_len+1; ++i) {
        fill(cache[i], cache[i] + word2_len+1, 0);
    }

    // initialize first row
    for (int i = 0; i < word2_len+1; ++i) {
        cache[0][i] = i;
    }
    // initializw first col
    for (int i = 0; i < word1_len+1; ++i) {
        cache[i][0] = i;
    }

    //iterate through the cache from the bottom right to the top-left
    for (int i = 1; i < word1_len+1; ++i) {
        for (int j = 1; j < word2_len+1; ++j) {
            // are the characters we are comparing equal
            if (str1[i-1] == str2[j-1]) {
                cache[i][j] = cache[i-1][j-1];
            }
            else {
                cache[i][j] = 1 + min_of_three(cache[i-1][j], // delete
                                    cache[i][j-1], // insert
                                    cache[i-1][j-1]); // replace
            }
        }
    }
    return cache[word1_len][word2_len] <= d;
}

int min_of_three(const int& a, const int& b, const int& c) {
    int min = a;
    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }
    return min;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        error(begin_word, end_word, "Starting word and destination word cannot be the same word.");
        return {};
    }
    
    if (find(word_list.begin(), word_list.end(), end_word) == word_list.end()) {
        error(begin_word, end_word, "The destination word is not in the word bank.");
        return {};
    }

    queue<vector<string>> ladder_queue;
    vector<string> first_vector;
    first_vector.push_back(begin_word);
    ladder_queue.push(first_vector);
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder[ladder.size()-1];
        for (string word : word_list) {
            // cout << "inner" << endl;
            if (is_adjacent(last_word, word)) {
                if (!visited.contains(word)) {
                    visited.insert(word);
                    vector<string> new_ladder(ladder);
                    new_ladder.push_back(word);
                    if (word == end_word) {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
        // cout << "done with inner" << endl;
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream inFile;
    inFile.open(file_name);

    string line;

    while(getline(inFile, line)) {
        for (char &c : line) {
            c = tolower(c);
        }
        word_list.insert(line);
    }

    inFile.close();
}

void print_word_ladder(const vector<string>& ladder) {
    for (string word : ladder) {
        cout << word << ' ';
    }
}