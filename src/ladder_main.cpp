#include "ladder.h"

void test_edit_distance() {
    cout << edit_distance_within("cat", "bat", 1) << endl; // should be 1
    cout << edit_distance_within("cat", "bop", 2) << endl; // should be 0
    cout << edit_distance_within("chat", "cheat", 1) << endl; // should be 1

    cout << is_adjacent("cat", "bat") << endl;
    cout << is_adjacent("cat", "nom") << endl;
    cout << is_adjacent("chat", "cheat") << endl;
}

int main() {
    test_edit_distance();
    set<string> word_list;
    word_list.insert("hot");
    word_list.insert("dot");
    word_list.insert("dog");
    word_list.insert("lot");
    word_list.insert("log");
    word_list.insert("cog");
    // load_words(word_list, "../src/words.txt");
    cout << "done loading words" << endl;
    vector<string> ladder = generate_word_ladder("hit", "cog", word_list);
    print_word_ladder(ladder);
    cout << endl;
}