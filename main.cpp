#include <iostream>
#include "rot13.h"
#include "error_handler.h"

using namespace std;

void showMenu() {
    cout << "\n========================================" << endl;
    cout << "      ROT13 - Encryption/Decryption" << endl;
    cout << "========================================" << endl;
    cout << "1. Encrypt/Decrypt text (keyboard input)" << endl;
    cout << "2. Encrypt/Decrypt text from file" << endl;
    cout << "3. Exit" << endl;
    cout << "Select action (1-3): ";
}

int main() {
    ErrorHandler logger;
    Rot13 cipher;
    int choice = 0;
    string text;
    string filename;
    string result;

    do {
        try {
            showMenu();
            cin >> choice;

            // ПРОВЕРКА: корректный ли ввод?
            if (cin.fail()) {
                cin.clear();
                cin.ignore(32767, '\n');
                throw InvalidInputException();  // ← ВЫБРАСЫВАЕМ
            }

            cin.ignore();

            switch (choice) {
            case 1:
                cout << "\nEnter text: ";
                getline(cin, text);
                result = cipher.encrypt(text);
                cout << "\n--- RESULT ---" << endl;
                cout << "Original: " << text << endl;
                cout << "Encrypted: " << result << endl;
                cout << "Verify (ROT13 again): " << cipher.encrypt(result) << endl;
                break;

            case 2:
                cout << "\nEnter filename: ";
                getline(cin, filename);
                
                // ЗДЕСЬ МОЖЕТ ВЫЛЕТЕТЬ ИСКЛЮЧЕНИЕ
                result = cipher.encryptFromFile(filename);
                
                cout << "\n--- RESULT ---" << endl;
                cout << result << endl;

                cout << "\nSave result to output.txt? (y/n): ";
                char save;
                cin >> save;
                if (save == 'y' || save == 'Y') {
                    // ЗДЕСЬ ТОЖЕ МОЖЕТ ВЫЛЕТЕТЬ ИСКЛЮЧЕНИЕ
                    cipher.saveToFile("output.txt", result);
                    cout << "Saved to output.txt" << endl;
                }
                break;

            case 3:
                cout << "\nGoodbye!" << endl;
                break;

            default:
                throw InvalidInputException();  // ← ВЫБРАСЫВАЕМ
            }
        }
        // ============ ОБРАБОТКА ВСЕХ ИСКЛЮЧЕНИЙ ============
        catch (const FileOpenException& e) {
            logger.logException(e);           // Запись в error.log
            cerr << "ERROR: " << e.what() << endl;  // Вывод на экран
        }
        catch (const FileWriteException& e) {
            logger.logException(e);
            cerr << "ERROR: " << e.what() << endl;
        }
        catch (const EmptyFileException& e) {
            logger.logException(e);
            cerr << "ERROR: " << e.what() << endl;
        }
        catch (const InvalidInputException& e) {
            logger.logException(e);
            cerr << "ERROR: " << e.what() << endl;
        }
        catch (const exception& e) {
            logger.logException(e);
            cerr << "UNKNOWN ERROR: " << e.what() << endl;
        }
    } while (choice != 3);

    return 0;
}