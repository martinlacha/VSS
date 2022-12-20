#pragma once

#include "semaphore.h"

#include <iostream>

class Crossroad {
public:
    enum class NCrossroad_State {
        FIRST,
        SECOND,
        NONE
    };
    Crossroad(int f_bottom_x, int f_bottom_y, int f_top_x, int f_top_y,
              int s_bottom_x, int s_bottom_y, int s_top_x, int s_top_y,
              size_t count_iterations, size_t pause_count, Map& map);
    Crossroad() = default;
    void Update();
private:
    Map& map;
    size_t count_iteration_to_switch;
    size_t next_switch;
    size_t pause_iteration_count;
    Semaphore first_semaphore;
    Semaphore second_semaphore;
    NCrossroad_State current_state;
    NCrossroad_State previous_state;
};