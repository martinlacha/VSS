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
    void Generate_Start_State();
    void Update_Top_Crossroad() noexcept;
    void Update_Bottom_Crossroad() noexcept;
    void Update_Right_Crossroad() noexcept;

    Simulation& operator=(const Simulation &rhs) {
        this->map = rhs.map;
        this->vehicles.clear();
        for (const auto& vehicle : rhs.vehicles) {
            this->vehicles.emplace_back(Vehicle(vehicle));
        }
        this->path = rhs.path;
        this->parking = rhs.parking;
        this->config = rhs.config;
        this->clear_vehicles = rhs.clear_vehicles;
        this->remain_vehicle_length_top = rhs.remain_vehicle_length_right;
        this->remain_vehicle_length_bottom = rhs.remain_vehicle_length_bottom;
        this->remain_vehicle_length_right = rhs.remain_vehicle_length_right;
        this->creating_vehicle_on_top = rhs.creating_vehicle_on_top;
        this->creating_vehicle_on_bottom = rhs.creating_vehicle_on_bottom;
        this->creating_vehicle_on_right = rhs.creating_vehicle_on_right;
        return *this;
    };

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
    [[nodiscard]] Vehicle Create_New_Vehicle(Path::NVehicle_Start_Position position);
    void Remove_Vehicles();
    bool clear_vehicles{};
    void Stats_Update_Vehicle(Vehicle &vehicle, bool add);
    void Update_Stats() noexcept;
    [[nodiscard]] Vehicle Create_Parked_Vehicle(Parking::NParting_Place street, Cell head_cell, Parking::NParting_Spot park_place, int drive_length, bool van_allowed);
};