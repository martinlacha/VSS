#pragma once

#include "map/crossroad.h"
#include "map/map.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

class Simulation {
public:
    Simulation();
    void Update();
    Map& Get_Map();
private:
    Map map;
    size_t iteration;
    size_t top_crossroad_duration_time = 5;
    size_t top_crossroad_pause_time = 3;
    size_t bottom_crossroad_duration_time = 5;
    size_t bottom_crossroad_pause_time = 3;
    size_t right_crossroad_duration_time = 5;
    size_t right_crossroad_pause_time = 3;
    size_t pause_milliseconds_count = 500;
    std::chrono::milliseconds iteration_pause;
    Crossroad top_crossroad;
    Crossroad bottom_crossroad;
    Crossroad right_crossroad;

    void Init();
    void Update_Semaphores();
    void Update_Cars();
};