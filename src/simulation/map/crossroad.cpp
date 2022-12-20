#include "crossroad.h"

Crossroad::Crossroad(int f_bottom_x, int f_bottom_y, int f_top_x, int f_top_y,
                     int s_bottom_x, int s_bottom_y, int s_top_x, int s_top_y,
                     size_t count_iterations, size_t pause_count, Map& map) :
                     map(map),
                     first_semaphore(f_bottom_x, f_bottom_y, f_top_x, f_top_y, count_iterations, map),
                     second_semaphore(s_bottom_x, s_bottom_y, s_top_x, s_top_y, count_iterations, map)
                     {
    count_iteration_to_switch = count_iterations;
    next_switch = 1;
    pause_iteration_count = pause_count;
    //first_semaphore = Semaphore(f_bottom_x, f_bottom_y, f_top_x, f_top_y, count_iterations, map);
    //second_semaphore = Semaphore(s_bottom_x, s_bottom_y, s_top_x, s_top_y, count_iterations, map);
    previous_state = NCrossroad_State::NONE;
    current_state = NCrossroad_State::FIRST;
    first_semaphore.Change_State_to_Green();
    second_semaphore.Change_State_To_Red();
}

void Crossroad::Update() {
    if (next_switch == 0)
    {
        if (current_state == NCrossroad_State::FIRST || current_state == NCrossroad_State::SECOND)
        {
            std::cout << "Semaphore: Black" << std::endl;
            next_switch = pause_iteration_count;
            previous_state = current_state;
            current_state = NCrossroad_State::NONE;
            first_semaphore.Change_State_To_Black();
            second_semaphore.Change_State_To_Black();
        }
        else
        {
            next_switch = count_iteration_to_switch;
            if (previous_state == NCrossroad_State::FIRST)
            {
                std::cout << "Semaphore1: G" << std::endl;
                std::cout << "Semaphore2: R" << std::endl;
                previous_state = current_state;
                current_state = NCrossroad_State::SECOND;
                first_semaphore.Change_State_To_Red();
                second_semaphore.Change_State_to_Green();
            }
            else if (previous_state == NCrossroad_State::SECOND)
            {
                std::cout << "Semaphore1: R" << std::endl;
                std::cout << "Semaphore2: G" << std::endl;
                previous_state = current_state;
                current_state = NCrossroad_State::FIRST;
                first_semaphore.Change_State_to_Green();
                second_semaphore.Change_State_To_Red();
            }
        }
    }
    next_switch--;
}
