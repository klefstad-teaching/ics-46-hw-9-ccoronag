#include "ladder.h"

int main() {
    cout << edit_distance_within("cat", "bat", 1) << endl; // should be 1
    cout << edit_distance_within("cat", "bop", 2) << endl; // should be 0
    cout << edit_distance_within("chat", "cheat", 1) << endl; // should be 1
    
}