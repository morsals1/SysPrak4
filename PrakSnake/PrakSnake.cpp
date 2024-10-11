
// PrakSnake.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>

struct Node {
    char data;
    int x, y;
    Node* next;
    Node(char value, int x_pos, int y_pos) : data(value), x(x_pos), y(y_pos), next(nullptr) {}
};

class Snake {
private:
    Node* head;
    Node* tail;
    int fruitX, fruitY;
    bool fruitExists;
    bool checkGame;
    char direction;

public:
    Snake() {
        checkGame = true;
        head = nullptr;
        tail = nullptr;
        direction = 'd';
        fruitExists = false;
        head = new Node('>', 10, 20);
        tail = head;
    }

    void draw() {
        for (int i = 0; i <= 20; ++i) {
            if (i == 0 || i == 20) {
                for (int j = 0; j <= 40; ++j) {
                    std::cout << "#";
                }
            }
            else {
                std::cout << "#";
                for (int j = 0; j <= 40 - 2; ++j) {
                    if (i == fruitX && j == fruitY) {
                        std::cout << "*";
                    }
                    else {
                        Node* temp = head;
                        bool isPartOfSnake = false;
                        while (temp != nullptr) {
                            if (temp->x == i && temp->y == j) {
                                std::cout << temp->data;
                                isPartOfSnake = true;
                                break;
                            }
                            temp = temp->next;
                        }
                        if (!isPartOfSnake) {
                            std::cout << ' ';
                        }
                    }
                }
                std::cout << "#";
            }
            std::cout << "\n";
        }
    }

    void move() {
        if (_kbhit()) {
            char input = _getch();

            if ((input == 'w' && direction != 's') ||
                (input == 's' && direction != 'w') ||
                (input == 'a' && direction != 'd') ||
                (input == 'd' && direction != 'a')) {
                direction = input;
            }
        }

        int newX = head->x;
        int newY = head->y;

        switch (direction) {
        case 'w': newX -= 1; break;
        case 's': newX += 1; break;
        case 'a': newY -= 1; break;
        case 'd': newY += 1; break;
        }

        if (newX < 1 || newX > 19 || newY < 0 || newY > 38) {
            checkGame = false;
            return;
        }

        Node* current = head;
        while (current != nullptr) {
            if (current->x == newX && current->y == newY) {
                checkGame = false;
                return;
            }
            current = current->next;
        }

        Node* newHead = new Node('>', newX, newY);
        newHead->next = head;
        head = newHead;

        if (head->x == fruitX && head->y == fruitY) {
            fruitExists = false;
        }
        else {

            Node* temp = head;
            while (temp->next->next != nullptr) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
    }

    void End() {
        if (!checkGame) {
            std::cout << "Игра окончена! Вы достигли границы поля.\n";
            exit(0);
        }
    }

    void fruit_spawn() {
        if (fruitExists) return;

        bool validPosition;
        srand(time(NULL));

        do {
            validPosition = true;
            fruitX = rand() % (19 - 1 + 1) + 1;
            fruitY = rand() % (38 - 0 + 1) + 0;

            Node* current = head;
            while (current != nullptr) {
                if (current->x == fruitX && current->y == fruitY) {
                    validPosition = false;
                    break;
                }
                current = current->next;
            }
        } while (!validPosition);

        fruitExists = true;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Snake sn;
    int startgame;

    std::cout << "w - вверх; s - вниз; a - влево; d - вправо\n1 - начать\n ";
    std::cin >> startgame;

    if (startgame == 1) {
        while (true) {
            sn.move();
            sn.draw();
            sn.End();
            sn.fruit_spawn();

            system("cls");
            Sleep(100);
        }
    }
    else {
        std::cout << "Закрытие программы...";
    }
    return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.