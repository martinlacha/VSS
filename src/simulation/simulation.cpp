#include "simulation.h"

Simulation::Simulation() :
    top_crossroad(4, 0, 5, 0, 7, 4, 7, 3,
        top_crossroad_duration_time, top_crossroad_pause_time, map),
    bottom_crossroad(33, 0, 34, 0, 38, 3, 37, 3,
         bottom_crossroad_duration_time, bottom_crossroad_pause_time, map),
    right_crossroad(37, 59, 37, 60, 34, 63, 34, 62,
        right_crossroad_duration_time, right_crossroad_pause_time, map)
{
    Init();
}

void Simulation::Update() {
    std::cout << iteration << "Update" << std::endl;
    iteration++;

    Update_Semaphores();
    Update_Cars();

    if (iteration == 100)
    {
        iteration = 0;
    }
    std::this_thread::sleep_for(iteration_pause);
}

void Simulation::Update_Semaphores() {
    top_crossroad.Update();
    bottom_crossroad.Update();
    right_crossroad.Update();
}

void Simulation::Update_Cars() {

}

void Simulation::Init() {
    map = Map();
    iteration = 0;
    iteration_pause = std::chrono::milliseconds(pause_milliseconds_count);
}

Map &Simulation::Get_Map() {
    return map;
}
