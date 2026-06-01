#ifndef ROT13_H
#define ROT13_H

#include <string>

using namespace std;

class Rot13 {
private:
    char transformChar(char c) const;

public:
    Rot13();
    string encrypt(const string& text) const;
    string decrypt(const string& text) const;
    string encryptFromFile(const string& filename) const;
    bool saveToFile(const string& filename, const string& content) const;
};

#endif