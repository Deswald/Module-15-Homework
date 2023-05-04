#pragma once
#include <iostream>
#include <string.h>
#pragma warning(disable : 4996)
#define NAMELENGTH 10  // «афиксируем длину имени

typedef char UserName[NAMELENGTH]; // тип им€ 

class HashTable { // хеш-таблица
public:

    HashTable() {
        count = 0;
        mem_size = 8;
        array = new Pair[mem_size];
    }
    ~HashTable() {
        delete[] array;
    }
    void printInfo()
    {
        for (int i = 0; i < mem_size; i++)
        {
            std::cout << "User " << array[i].user_name << std::endl;
            std::cout << " password: " << array[i].user_password << std::endl;
        }
    }

    void reg(UserName name, int pass)
    {
        int index = -1, i = 0;
        // берем пробы по всем i от 0 до размера массива
        for (; i < mem_size; i++) {
            index = hash_func_login(name, i);
            if (array[index].status != enPairStatus::engaged) {
                // найдена пуста€ €чейка, занимаем ее
                break;
            }
        }
        if (i >= mem_size) return; // все перебрали, нет места

        // кладем в свободную €чейку пару
        array[index] = Pair(name, hash_func_password(pass));
        count++;
    }

private:

    enum enPairStatus {
        free, // свободен
        engaged, //зан€т
        deleted //удален
    };

    struct Pair { // пара ключ-значение

        Pair() : // конструктор по умолчанию
            user_name(""),
            user_password(-1),
            status(enPairStatus::free) {

        }
        Pair(UserName name, int pass) : // конструктор копировани€
            user_password(pass),
            status(enPairStatus::engaged) {
            strcpy(user_name, name);
        }
        Pair& operator = (const Pair& other) { //  оператор присваивани€
            user_password = other.user_password;
            strcpy(user_name, other.user_name);
            status = other.status;

            return *this;
        }

        UserName user_name; // ключ
        int user_password; // значение

        enPairStatus status; // состо€ние €чейки
    };

    int hash_func_login(UserName name, int offset)
    {
        // вычисл€ем индекс
        int sum = 0, i = 0;
        for (; i < strlen(name); i++) {
            sum += name[i];
        }
        // квадратичные пробы
        return (sum % mem_size + offset * offset) % mem_size;
    }

    int hash_func_password(int pass)
    {
        const double A = 0.7;
        const int M = 10;
        return (M * (A * pass - int(A * pass)));
    }

    Pair* array;
    int mem_size;
    int count;
};


