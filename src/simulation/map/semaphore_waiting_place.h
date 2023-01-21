#pragma once

#include "../cell.h"
#include "../map/map.h"

#include <vector>

class Semaphore_Waiting_Place {
public:
    struct NSemaphore_Waiting_Place {
        Cell waiting_cell;
        Cell semaphore_cell;
        bool is_semaphore_green;
    };

    Semaphore_Waiting_Place();
    void Update_Stop_Cells(Map& map);
    bool Stop_On_Semaphore(Cell &cell);

private:
    std::vector<NSemaphore_Waiting_Place> semaphore_stop_cells;

};