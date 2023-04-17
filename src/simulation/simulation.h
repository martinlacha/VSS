#pragma once

#include "map/crossroad.h"
#include "map/map.h"
#include "vehicles/vehicle.h"
#include "vehicles/path.h"
#include "configuration.h"
#include "map/semaphore_waiting_place.h"
#include "map/parking_spot.h"

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

    void Restart();

private:
    Map map;
    Parking parking;
    Path path;
    Configuration &config;
    Semaphore_Waiting_Place waiting_places;

    // Configuration of crossroads and semaphores
    Crossroad top_crossroad;
    Crossroad bottom_crossroad;
    Crossroad right_crossroad;

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
    void Reset_Config_Params();
    void Reset_Stats_Params();
    void Update_Semaphores();
    void Update_Vehicles();
    void Try_Create_Car();
private:
    [[nodiscard]] Vehicle Create_New_Vehicle(Path::NVehicle_Start_Position position);
    void Remove_Vehicles();
    bool clear_vehicles{};
    void Stats_Update_Vehicle(Vehicle &vehicle, bool add);
    void Update_Stats() noexcept;
};