#pragma once

#include "imgui.h"
#include "../cell.h"
#include "../map/map.h"
#include "../map/semaphore.h"
#include "path.h"
#include "../map/semaphore_waiting_place.h"

#include <iostream>
#include <cstdint>
#include <ctime>
#include <vector>
#include <stdexcept>

class Vehicle
{
public:
    enum class NVehicle_Type : uint8_t {
        MOTORBIKE,
        CAR,
        VAN
    };

    enum class NVehicle_Mode : uint8_t {
        DRIVE,
        PARK_BETWEEN,
        PARK_VERTICAL,
        PARK_HORIZONTAL
    };

    enum class NMove_Direction : uint8_t {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };



    Vehicle(NVehicle_Type type, Cell start_position, size_t path_length, bool wanna_park, Path::NVehicle_Start_Position start,
            size_t phase_count, Map& map, Path::NVehicle_Path path_type, Path& path, Semaphore_Waiting_Place& places);
    void Move_Vehicle();
    [[nodiscard]] size_t Get_Vehicle_Length() const;
    bool Remove_Vehicle();
    static NVehicle_Type Get_Vehicle_Type(float prob_motorbike, float prob_car, float prob_van);
    static bool Start_Generate_Car(float probability);
    static bool Wanna_Park(float probability);

    Vehicle& operator=(Vehicle other) {

        return *this;
    }

private:
    NVehicle_Type vehicle_type;
    std::vector<Cell> cells;
    Cell start_cell;
    Cell last_cell;
    size_t vehicle_length;
    ImVec4 color;
    size_t length_to_drive;
    size_t phase_path;
    size_t phase_remain;
    bool want_to_park;
    bool already_parked;
    bool creating;
    bool exiting_map;
    bool remove;
    size_t attempt_to_park;
    Path::NVehicle_Start_Position start_position;
    Path::NVehicle_Path path_type;
    NMove_Direction direction;
    Map& map;
    Path& path;
    Semaphore_Waiting_Place& waiting_places;

    ImVec4 Generate_Unique_Color();
    bool Can_Vehicle_Move();
    void Change_Cells_And_Map();
    void Change_Cells_And_Map_By_Direction(Cell next_cell);
    void Set_New_Direction();
    static bool Is_Out_Of_Map(Cell& cell);
    void Add_Vehicle_Into_Map();
};