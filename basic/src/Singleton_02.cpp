//
// Created by asus on 9/12/2020.
//

#include "cstdio"

class Singleton1 {
private:
    Singleton1() = default;

    static Singleton1 instance;

public:
    static Singleton1 Instance;

    static void SetInstance() {
        Instance = instance;
    }

    static Singleton1 GetInstance() {
        return instance;
    }

};


// int main(int argc, char *argv[], char *envp[]) {
//
//     Singleton1::SetInstance();
//     Singleton1::GetInstance();
//
//     return 0;
// }
