#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <limits>

using namespace std;

// Простой мульти-итератор: объединяет 2 разных контейнера в один проход
class MultiIterator {
private:
    const vector<string>& emails;
    const list<string>& phones;

    size_t emailIndex;
    list<string>::const_iterator phoneIt;

public:
    MultiIterator(const vector<string>& e, const list<string>& p)
        : emails(e), phones(p), emailIndex(0), phoneIt(phones.begin()) {}

    bool hasNext() const {
        return (emailIndex < emails.size()) || (phoneIt != phones.end());
    }

    string next() {
        if (emailIndex < emails.size()) {
            string value = emails[emailIndex];
            emailIndex++;
            return value;
        }

        if (phoneIt != phones.end()) {
            string value = *phoneIt;
            ++phoneIt;
            return value;
        }

        return ""; // на случай, если вызвали next() без hasNext()
    }
};

int readNonNegativeInt(const string& prompt) {
    int n;
    while (true) {
        cout << prompt;
        cin >> n;

        if (cin.fail() || n < 0) {
            cout << "Ошибка ввода. Введите неотрицательное целое число.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return n;
        }
    }
}

int main() {
    setlocale(LC_ALL, "");

    vector<string> emailList;
    list<string> phoneList;

    int emailCount = readNonNegativeInt("Сколько email-адресов хотите ввести? ");
    for (int i = 0; i < emailCount; i++) {
        string email;
        cout << "Введите email #" << (i + 1) << ": ";
        getline(cin, email);

        if (email.empty()) {
            cout << "Пустая строка, сохранено как \"(пусто)\".\n";
            email = "(пусто)";
        }
        emailList.push_back(email);
    }

    int phoneCount = readNonNegativeInt("Сколько телефонов хотите ввести? ");
    for (int i = 0; i < phoneCount; i++) {
        string phone;
        cout << "Введите телефон #" << (i + 1) << ": ";
        getline(cin, phone);

        if (phone.empty()) {
            cout << "Пустая строка, сохранено как \"(пусто)\".\n";
            phone = "(пусто)";
        }
        phoneList.push_back(phone);
    }

    MultiIterator it(emailList, phoneList);

    cout << "\nОбщий последовательный вывод данных:\n";
    int number = 1;
    while (it.hasNext()) {
        cout << number << ") " << it.next() << "\n";
        number++;
    }

    if (number == 1) {
        cout << "Списки пустые.\n";
    }

    return 0;
}
