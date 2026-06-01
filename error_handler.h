#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <string>
#include <exception>

using namespace std;

// ============ ПОЛЬЗОВАТЕЛЬСКИЕ ИСКЛЮЧЕНИЯ ============

// Ошибка: не удалось открыть файл
class FileOpenException : public exception {
private:
    string filename;
public:
    FileOpenException(const string& file) : filename(file) {}

    const char* what() const noexcept override {
        string msg = "Cannot open file: " + filename;
        static char result[256];
        strcpy_s(result, msg.c_str());
        return result;
    }
};

// Ошибка: не удалось записать в файл
class FileWriteException : public exception {
private:
    string filename;
public:
    FileWriteException(const string& file) : filename(file) {}

    const char* what() const noexcept override {
        string msg = "Cannot write to file: " + filename;
        static char result[256];
        strcpy_s(result, msg.c_str());
        return result;
    }
};

// Ошибка: неверный ввод пользователя
class InvalidInputException : public exception {
public:
    const char* what() const noexcept override {
        return "Invalid input. Expected 1-3";
    }
};

// Ошибка: файл пустой
class EmptyFileException : public exception {
public:
    const char* what() const noexcept override {
        return "File is empty";
    }
};

// ============ КЛАСС ДЛЯ ЛОГИРОВАНИЯ ОШИБОК ============

class ErrorHandler {
private:
    string logFile;

public:
    ErrorHandler(const string& log = "error.log");
    void logError(const string& errorMsg);
    void logException(const exception& e);
};

#endif  // ERROR_HANDLER_H