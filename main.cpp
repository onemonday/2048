#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>

#define KEY_ARROW 224
#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80

unsigned int nUsedCells = 0;
bool isGameWon = false;

class Cell {
public:
    Cell(unsigned int value = 0) {
        Cell::value = value;
        used = false;
    }

    static void moveUp(Cell (& field)[4][4]);
    static void moveDown(Cell (& field)[4][4]);
    static void moveRight(Cell (& field)[4][4]);
    static void moveLeft(Cell (& field)[4][4]);
    static void newGame(Cell (& field)[4][4]);
    static bool isGameLost(Cell (& field)[4][4]);

    void printValue();
    void updateValue(unsigned int newValue);

    static void printField(Cell (& field)[4][4]);
    static void createNewSquare(Cell (&field)[4][4]);

private:
    unsigned int value;
    bool used;
};

int random() {
    return rand() % 4;
}

void endScreen(Cell (& field)[4][4]);

int main() {
    srand(time(NULL));

    Cell field[4][4];

    // Game start
    Cell::createNewSquare(field);
    Cell::createNewSquare(field);
    Cell::printField(field);

    // Game logic
    while (true) {
        unsigned char button = getch();
        if (button == KEY_ARROW) {
            unsigned char arrow = getch();
            switch (arrow) {
                case KEY_UP:
                    Cell::moveUp(field);
                    break;
                case KEY_DOWN:
                    Cell::moveDown(field);
                    break;
                case KEY_LEFT:
                    Cell::moveLeft(field);
                    break;
                case KEY_RIGHT:
                    Cell::moveRight(field);
                    break;
            }
        } else  if (button == VK_ESCAPE){
            exit(0);
        }
        if (Cell::isGameLost(field) || isGameWon)
            endScreen(field);
    }
}

void Cell::printField(Cell (& field)[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            field[i][j].printValue();
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Cell::printValue() {
    if (value  == 0)
        std::cout << "_ ";
    else std::cout << value << " ";
}

void Cell::newGame(Cell (& field)[4][4]) {
    system ("cls");
    isGameWon = false;
    nUsedCells = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            field[i][j].value = 0;

    Cell::createNewSquare(field);
    Cell::createNewSquare(field);
    Cell::printField(field);
}

bool Cell::isGameLost(Cell (& field)[4][4]) {
    bool bFlag = false;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

            if (i != 3 && field[i][j].value == field[i+1][j].value)
                bFlag = true;
            if (j != 3 && field[i][j].value == field[i][j+1].value)
                bFlag = true;

            if (bFlag) break;
        }
        if (bFlag) break;
    }
    return !bFlag;
}

void Cell::updateValue(unsigned int newValue) {
    value = newValue;
    if (newValue == 2048)
        isGameWon = true;
}

void Cell::createNewSquare(Cell (& field)[4][4]) {
    if (nUsedCells == 16) return;
    while (true) {
        unsigned int xAxis = random();
        unsigned int yAxis = random();
        if (field[xAxis][yAxis].value != 0)
            continue;
        else {
            unsigned int newValue = random();
            if (newValue != 0)
                newValue = 2;
            else newValue = 4;

            field[xAxis][yAxis].value = newValue;
            nUsedCells++;
            break;
        }
    }
}

void Cell::moveUp(Cell (& field)[4][4]) {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            if (field[i][j].value != 0) {
                int returnPosition = i;
                while (i > 0) {
                    int prevPosition = i;
                    i--;
                    if (field[i][j].value == 0) {
                        field[i][j] = field[prevPosition][j];
                        field[prevPosition][j].value = 0;
                    } else if (field[i][j].value == field[prevPosition][j].value && !field[i][j].used && !field[prevPosition][j].used) {
                        field[i][j].updateValue(field[i][j].value << 1);
                        field[i][j].used = true;
                        field[prevPosition][j].value = 0;
                        nUsedCells--;
                    } else {
                        if (field[prevPosition][j].used)
                            field[prevPosition][j].used = false;
                        if (field[i][j].used)
                            field[i][j].used = false;
                        break;
                    }
                }
                i = returnPosition;
            }
        }
    }
    system("cls");
    Cell::createNewSquare(field);
    Cell::printField(field);
}

void Cell::moveDown(Cell (&field)[4][4]) {
    for (int j = 0; j < 4; j++) {
        for (int i = 3; i >= 0; i--) {
            if (field[i][j].value != 0) {
                int returnPosition = i;
                while (i < 3) {
                    int prevPosition = i;
                    i++;
                    if (field[i][j].value == 0) {
                        field[i][j] = field[prevPosition][j];
                        field[prevPosition][j].value = 0;
                    } else if (field[i][j].value == field[prevPosition][j].value && !field[i][j].used && !field[prevPosition][j].used) {
                        field[i][j].updateValue(field[i][j].value << 1);
                        field[i][j].used = true;
                        field[prevPosition][j].value = 0;
                        nUsedCells--;
                    } else {
                        if (field[prevPosition][j].used)
                            field[prevPosition][j].used = false;
                        if (field[i][j].used)
                            field[i][j].used = false;
                        break;
                    }
                }
                i = returnPosition;
            }
        }
    }
    system("cls");
    Cell::createNewSquare(field);
    Cell::printField(field);
}

void Cell::moveLeft(Cell (&field)[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (field[i][j].value != 0) {
                int returnPosition = j;
                while (j > 0) {
                    int prevPosition = j;
                    j--;
                    if (field[i][j].value == 0) {
                        field[i][j] = field[i][prevPosition];
                        field[i][prevPosition].value = 0;
                    } else if (field[i][j].value == field[i][prevPosition].value && !field[i][j].used && !field[i][prevPosition].used) {
                        field[i][j].updateValue(field[i][j].value << 1);
                        field[i][j].used = true;
                        field[i][prevPosition].value = 0;
                        nUsedCells--;
                    } else {
                        if (field[i][prevPosition].used)
                            field[i][prevPosition].used = false;
                        if (field[i][j].used)
                            field[i][j].used = false;
                        break;
                    }
                }
                j = returnPosition;
            }
        }
    }
    system("cls");
    Cell::createNewSquare(field);
    Cell::printField(field);
}
void Cell::moveRight(Cell (&field)[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j >= 0; j--) {
            if (field[i][j].value != 0) {
                int returnPosition = j;
                while (j < 3) {
                    int prevPosition = j;
                    j++;
                    if (field[i][j].value == 0) {
                        field[i][j] = field[i][prevPosition];
                        field[i][prevPosition].value = 0;
                    } else if (field[i][j].value == field[i][prevPosition].value && !field[i][j].used && !field[i][prevPosition].used) {
                        field[i][j].updateValue(field[i][j].value << 1);
                        field[i][j].used = true;
                        field[i][prevPosition].value = 0;
                        nUsedCells--;
                    } else {
                        if (field[i][prevPosition].used)
                            field[i][prevPosition].used = false;
                        if (field[i][j].used)
                            field[i][j].used = false;
                        break;
                    }
                }
                j = returnPosition;
            }
        }
    }
    system("cls");
    Cell::createNewSquare(field);
    Cell::printField(field);
}

void endScreen(Cell (& field)[4][4]) {
    system("cls");
    if (isGameWon)
        std::cout << "Congratulations! You've scored 2048!" << std::endl << std::endl;
    else
        std::cout << "Game over. No more possible moves." << std::endl << std::endl;

    std::cout << "Do you want to continue?" << std::endl;
    std::cout << "n - start a new game" << std::endl;
    std::cout << "ESC - quit" << std::endl;

    while (true) {
        unsigned char key = getch();
        if (key == 'n' || key == 'N') {
            Cell::newGame(field);
            break;
        }
        else if (key == VK_ESCAPE)
            exit(0);
    }
}
