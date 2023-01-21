#pragma once


class Cell {
public:
    Cell(int x, int y);
    Cell() = default;
    void Set_Position(int new_x, int new_y);
    int Get_X() const noexcept;
    int Get_Y() const noexcept;
    bool Are_Same_Cells(Cell& another_cell) const;
private:
    int x, y;
};