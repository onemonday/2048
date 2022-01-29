#include <iostream>
#include <time.h>
#include <windows.h>

int random() {
    return rand() % 4;
}

class Cell {
public:
    Cell(unsigned int value = 0) {
        Cell::value = value;
    }

    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void printValue();
    void updateValue(unsigned int newValue);

    static void createNewSquare(Cell (&field)[4][4]);

private:
    unsigned int value;
};

int main() {
    srand(time(NULL));

    Cell field[4][4];

    // Game start
    Cell::createNewSquare(field);
    Cell::createNewSquare(field);

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++)
            field[i][j].printValue();
        std::cout << std::endl;
    }

    return 0;
}

void Cell::printValue(){
    if (value == 0)
        std::cout << "_";
    else std::cout << value;
}

void Cell::updateValue(unsigned int newValue) {
    value = newValue;
}

void Cell::createNewSquare(Cell (& field)[4][4]) {
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
            break;
        }
    }
}

void Cell::moveUp() {

}
