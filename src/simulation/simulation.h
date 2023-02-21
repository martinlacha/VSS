#pragma once

#include "map/crossroad.h"
#include "map/map.h"
#include "vehicles/vehicle.h"
#include "vehicles/path.h"
#include "configuration.h"
#include "map/semaphore_waiting_place.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>

class Simulation {
public:
    Simulation(Configuration& config);
    void Update();
    Map& Get_Map();
private:
    Map map;
    Path path;
    Configuration config;
    Semaphore_Waiting_Place waiting_places;
    size_t iteration{};

    // Configuration of crossroads and semaphores
    Crossroad top_crossroad;
    Crossroad bottom_crossroad;
    Crossroad right_crossroad;
    std::chrono::milliseconds iteration_pause;

    // List of existing vehicles in simulation
    std::vector<Vehicle> vehicles;
    std::vector<Vehicle> vehicles_temp;

    bool creating_vehicle_on_top{};
    size_t remain_vehicle_length_top{};

    bool creating_vehicle_on_bottom{};
    size_t remain_vehicle_length_bottom{};

    bool creating_vehicle_on_right{};
    size_t remain_vehicle_length_right{};

    void Init();
    void Update_Semaphores();
    void Update_Vehicles();
    void Try_Create_Car();
private:
    [[nodiscard]] Vehicle Create_New_Vehicle(Path::NVehicle_Start_Position position);
    void Remove_Vehicles();
    bool clear_vehicles{};
};