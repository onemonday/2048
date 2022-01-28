#include <iostream>
#include <time.h>

int random() {
    unsigned int randomNumber = rand() % 4;
    if (randomNumber == 0)
        return 4;
    else return randomNumber;
}

class Cell {
public:
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();

    void printValue();
    void updateValue(unsigned int newValue);
private:
    unsigned int value = 0;
};

int main() {
    srand(time(NULL));

    Cell field[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            field[i][j].updateValue(random());
            field[i][j].printValue();
        }
        std::cout << std::endl;
    }
}

void Cell::printValue(){
    std::cout << value;
}

void Cell::updateValue(unsigned int newValue) {
    value = newValue;.
}