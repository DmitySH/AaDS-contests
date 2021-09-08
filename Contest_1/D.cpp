#include <iostream>

using namespace std;

bool Compare(string s1, string s2) {
    int i = 0;
    if (s1.length() != s2.length()) {
        return false;
    }

    while (i < s1.length()) {
        if (s1[i] != s2[i]) {
            return false;
        }
        i++;
    }
    return true;
}

int main() {
    string s1, s2;
    cin >> s1;
    cin >> s2;
    if(Compare(s1, s2)) {
        cout << "yes";
    }
    else {
        cout << "no";
    }
}

