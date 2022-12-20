#include "cell.h"

Cell::Cell(int x, int y) : x(x), y(y) {

}

void Cell::Set_Position(int new_x, int new_y) {
    x = new_x;
    y = new_y;
}

int Cell::Get_X() const noexcept {
    return x;
}

int Cell::Get_Y() const noexcept {
    return y;
}
