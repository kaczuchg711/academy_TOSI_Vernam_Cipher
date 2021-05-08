#include <bitset>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>

using namespace std::chrono;

using namespace std;

char bitsToChar(string str) {
    char parsed = 0;
    for (int i = 0; i < 8; i++)
        if (str[i] == '1')
            parsed |= 1 << (7 - i);
    return parsed;
}

string toBinary(int n) {
    string r;
    while (n != 0) {
        r = (n % 2 == 0 ? "0" : "1") + r;
        n /= 2;
    }
    return r;
}

string code(const string &text, const string &key) {
    string ciphertext = string(8, ' ');

    for (int i = 0; i < text.length(); i++) {
        if (text[i] == '0')
            if (key[i] == '0')
                ciphertext[i] = '0';
            else
                ciphertext[i] = '1';
        else if (key[i] == '0')
            ciphertext[i] = '1';
        else
            ciphertext[i] = '0';
    }
    return ciphertext;
}

string decode(const string &ciphertext, const string &key) {
    return code(ciphertext, key);
}

string change_Character_to_bits_string(char ch) {
    return bitset<8>(ch).to_string();
}

void test(string fulltextAfterDecode, string fullText) {
    if (fulltextAfterDecode == fullText)
        cout << "OK" << endl;
    else
        cout << "Oh no" << endl;
}

int main() {
    auto start = high_resolution_clock::now();

    string nameOfFile = "alice.txt";
    ifstream MyReadFile("..\\" + nameOfFile);

    string line;
    string text;
    string fullText;
    string key;
    string fullKey;
    string ciphertext;
    string textAfterCode;
    string fulltextAfterDecode;
    string textAfterDecode;
    string fullCiphertext;
    srand(time(nullptr));

//  szyfrowanie
    while (getline(MyReadFile, line)) {
        fullText.append(line);
        for (char ch:line) {
            text = change_Character_to_bits_string(ch);
            key = toBinary((rand() % 128 + 128));
            fullKey.append(key);
            ciphertext = code(text, key);
            fullCiphertext.append(ciphertext);
        }
    }

//  deszyfrowanie
    for (int i = 0; i < fullCiphertext.length(); i += 8) {
        textAfterDecode = decode(fullCiphertext.substr(i, 8), fullKey.substr(i, 8));
        fulltextAfterDecode += bitsToChar(textAfterDecode);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout << "Time taken by program: " << duration.count() << " s" << endl;

    test(fulltextAfterDecode, fullText);



}