#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error creating word ladder from \"" << word1 << "\" to \"" << word2 << "\": " << msg << endl;
}

// void load_words(set<string> & word_list, const string& file_name) {
//     ifstream inFile;
//     inFile.open(file_name);

//     string line;

//     while(getline(inFile, line)) {
//         word_list.push_back(line);
//     }
//     inFile.close();
// }

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

// bool is_adjacent(const string& word1, const string& word2) {
    // int w1_len = word1.length();
    // int w2_len = word2.length();

    // // case where both words are the same length and just checks if there are more than 1 differences
    // if (w1_len == w2_len){ 
    //     int differences = 0;
    //     for (int i = 0; i < w1_len; ++i) {
    //         if (word1[i] != word2[i]) {
    //             ++differences;
    //             if (differences > 1) {return false;}
    //         }
    //     }
    //     return true;
    // }
    // // case where the lengths differ by one and need to check if the words are adjacent.
    // else if (w1_len - w2_len == 1 || w1_len - w2_len == -1) {
    //     string shortest = w1_len < w2_len ? word1 : word2; // get the shortest of the two
    //     string other = shortest == word1 ? word2 : word1; // get the other word

    //     // loop through the shortest word and add every char from a-z at every index to see if it matches the other word
    //     for (int i = 0; i < shortest.length(); ++i) {
    //         string word_copy = tolower(shortest); // create a copy since insert modifies the given string
    //         string other_copy = tolower(other); // create a lower case copy so the strings can be compared
    //         for (char c = 'a'; c <= 'z'; ++c) {
    //             if (word_copy.insert(i, 1, c) == other_copy) {
    //                 return true;
    //             }
    //         }
    //     }
    // }
    // else {

    // }
// }

// vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {

// }