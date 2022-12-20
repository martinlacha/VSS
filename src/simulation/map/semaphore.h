#pragma once

#include "../cell.h"
#include "imgui.h"
#include "map.h"

class Semaphore {
public:
    enum class NSemaphore_State {
        BLACK,
        RED,
        GREEN
    };
    Semaphore(int bottom_x, int bottom_y, int top_x, int top_y, size_t count_iterations, Map& map);
    Semaphore();
    void Change_State_To_Black();
    void Change_State_To_Red();
    void Change_State_to_Green();
private:
    Map& map;
    NSemaphore_State current_state;
    Cell top_box;
    Cell bottom_box;
    size_t iteration_to_change;

    void Set_Map_Cell_Type(Map::NCell_Type top_type, Map::NCell_Type bottom_type);
};