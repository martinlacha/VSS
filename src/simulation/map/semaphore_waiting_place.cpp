#include "semaphore_waiting_place.h"

Semaphore_Waiting_Place::Semaphore_Waiting_Place() {
    semaphore_stop_cells.push_back({Cell(5,1), Cell(5, 0), false});
    semaphore_stop_cells.push_back({Cell(6,3), Cell(7,3), false});
    semaphore_stop_cells.push_back({Cell(34,1), Cell(34,0), false});
    semaphore_stop_cells.push_back({Cell(37,3), Cell(37,4), false});
    semaphore_stop_cells.push_back({Cell(35, 3), Cell(34,0), false});
    semaphore_stop_cells.push_back({Cell(36,60), Cell(37,60), false});
    semaphore_stop_cells.push_back({Cell(35,62), Cell(34,62), false});
}

void Semaphore_Waiting_Place::Update_Stop_Cells(Map& map) {
    for (auto& waiting_place : semaphore_stop_cells) {
        Cell sem_cell = waiting_place.semaphore_cell;
        waiting_place.is_semaphore_green = map.Get_Cell_Type(sem_cell.Get_X(), sem_cell.Get_Y()) == Map::NCell_Type::S_G;
    }
}

bool Semaphore_Waiting_Place::Stop_On_Semaphore(Cell &cell) {
    for (auto& waiting_place : semaphore_stop_cells ) {
        if (cell.Get_X() == waiting_place.waiting_cell.Get_X() &&
            cell.Get_Y() == waiting_place.waiting_cell.Get_Y()) {
            return !waiting_place.is_semaphore_green;
        }
    }
    return false;
}