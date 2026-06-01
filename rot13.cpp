#include "rot13.h"
#include "error_handler.h"
#include <fstream>
#include <iostream>
#include <cctype>

using namespace std;

Rot13::Rot13() {}

char Rot13::transformChar(char c) const {
    if (c >= 'A' && c <= 'Z') {
        return 'A' + (c - 'A' + 13) % 26;
    }
    else if (c >= 'a' && c <= 'z') {
        return 'a' + (c - 'a' + 13) % 26;
    }
    else {
        return c;
    }
}

string Rot13::encrypt(const string& text) const {
    string result = text;
    for (size_t i = 0; i < result.length(); i++) {
        result[i] = transformChar(result[i]);
    }
    return result;
}

string Rot13::decrypt(const string& text) const {
    return encrypt(text);
}

// Функция чтения и шифрования из файла с ВЫБРОСОМ ИСКЛЮЧЕНИЙ
string Rot13::encryptFromFile(const string& filename) const {
    ifstream file(filename);

    // ПРОВЕРКА: удалось ли открыть файл?
    if (!file.is_open()) {
        throw FileOpenException(filename);  // ← ВЫБРАСЫВАЕМ ИСКЛЮЧЕНИЕ
    }

    string content;
    string line;
    while (getline(file, line)) {
        content += line + "\n";
    }
    file.close();

    // ПРОВЕРКА: не пустой ли файл?
    if (content.empty()) {
        throw EmptyFileException();  // ← ВЫБРАСЫВАЕМ ИСКЛЮЧЕНИЕ
    }

    // Убираем лишний перевод строки в конце
    if (!content.empty() && content.back() == '\n') {
        content.pop_back();
    }

    return encrypt(content);
}

// Функция сохранения в файл с ВЫБРОСОМ ИСКЛЮЧЕНИЙ
bool Rot13::saveToFile(const string& filename, const string& content) const {
    ofstream file(filename);

    // ПРОВЕРКА: удалось ли создать/открыть файл для записи?
    if (!file.is_open()) {
        throw FileWriteException(filename);  // ← ВЫБРАСЫВАЕМ ИСКЛЮЧЕНИЕ
    }

    file << content;
    file.close();
    return true;
}