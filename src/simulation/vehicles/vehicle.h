#pragma once

#include "imgui.h"
#include "../cell.h"
#include "../map/map.h"
#include "../map/semaphore.h"
#include "path.h"
#include "../map/semaphore_waiting_place.h"
#include "../map/parking_spot.h"

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

    enum class NMove_Direction : uint8_t {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };



    Vehicle(NVehicle_Type type, Cell start_position, size_t path_length, bool wanna_park, Path::NVehicle_Start_Position start,
            size_t phase_count, Map& map, Path::NVehicle_Path path_type, Path& path, Semaphore_Waiting_Place& places,
            Parking& parking_spot, size_t park_time, Parking::NParting_Place park_street);
    ~Vehicle() = default;
    bool Move_Vehicle();
    [[nodiscard]] size_t Get_Vehicle_Length() const;
    [[nodiscard]] Cell Get_Head_Cell() const;
    [[nodiscard]] Parking::NParting_Place Get_Parking_Street() const;
    [[nodiscard]] bool Want_Park() const;
    [[nodiscard]] bool Remove_Vehicle() const;
    static NVehicle_Type Get_Vehicle_Type(float prob_motorbike, float prob_car, float prob_van);
    static bool Start_Generate_Car(float probability);
    static bool Wanna_Park(float probability);
    void Start_Find_Parking_Spot() noexcept;
    void Stop_Find_Parking_Spot() noexcept;
    [[nodiscard]] NVehicle_Type Get_Type() const noexcept;

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
    //Parking
    bool want_to_park;
    bool already_parked;
    bool is_in_parking_mode;
    bool creating;
    bool exiting_map;
    bool remove;
    bool is_in_parking_zone;
    bool in_parking_spot;
    bool finding_paring_spot;
    bool leave_park_spot;
    size_t park_iterations;
    size_t attempt_to_park;
    Path::NVehicle_Start_Position start_position;
    Path::NVehicle_Path path_type;
    NMove_Direction direction;
    Map& map;
    Path& path;
    Parking& parking;
    Parking::NParting_Place want_park_in_street;
    Parking::NParting_Place try_currently_park_in_street;
    Parking::NParting_Spot current_parking;
    Semaphore_Waiting_Place& waiting_places;

    ImVec4 Generate_Unique_Color();
    bool Can_Vehicle_Move();
    void Change_Cells_And_Map();
    void Change_Cells_And_Map_By_Direction(Cell next_cell);
    void Set_New_Direction();
    static bool Is_Out_Of_Map(Cell& cell);
    bool Will_Go_To_Park_Zone();
    void Choose_New_Path_From_Park_Zone();
    void Try_Another_Park();
    void Start_Parking();
    void Try_To_Park();
    void Remove_Vehicle_From_Road();
    void Remove_Vehicle_From_Parking_Spot();
    bool Can_Leave_Park_Spot();
};