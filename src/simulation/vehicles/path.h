#pragma once

#include "../cell.h"

#include <vector>
#include <cstdint>
#include <random>
#include <iostream>

class Path {
public:
    enum class NVehicle_Path : uint8_t {
        TOP_BOTTOM,
        TOP_RIGHT,
        TOP_PARK,
        BOTTOM_TOP,
        BOTTOM_RIGHT,
        BOTTOM_PARK,
        RIGHT_TOP,
        RIGHT_PARK,
        PARK_TOP,
        PARK_BOTTOM,
        PARK_RIGHT,
        PARK_PARK,
        ERROR_PATH
    };

    enum class NVehicle_Start_Position : uint8_t {
        TOP,
        BOTTOM,
        RIGHT
    };

    enum class NDirection : uint8_t {
        UP,
        DOWN,
        RIGHT,
        LEFT,
        ERROR_DIRECTION
    };

    Path();
    NVehicle_Path Get_Path_Type(NVehicle_Start_Position start_position, bool wanna_park, bool in_park_zone);
    Cell Get_Cell_By_Vehicle_Phase(NVehicle_Path type_path, size_t index);
    size_t Get_Length_By_Vehicle_Phase(NVehicle_Path type_path, size_t index);
    size_t Get_Phase_Count_By_Type(NVehicle_Path type);
    NDirection Get_Direction_By_Path_Type(NVehicle_Path type, size_t index);
private:
    std::vector<Cell> top_bottom_path;
    std::vector<size_t> top_bottom_path_length;
    std::vector<NDirection> top_bottom_path_direction;

    std::vector<Cell> top_right_path;
    std::vector<size_t> top_right_path_length;
    std::vector<NDirection> top_right_path_direction;

    std::vector<Cell> top_park_path;
    std::vector<size_t> top_park_path_length;
    std::vector<NDirection> top_park_path_direction;

    std::vector<Cell> bottom_top_path;
    std::vector<size_t> bottom_top_path_length;
    std::vector<NDirection> bottom_top_path_direction;

    std::vector<Cell> bottom_right_path;
    std::vector<size_t> bottom_right_path_length;
    std::vector<NDirection> bottom_right_path_direction;

    std::vector<Cell> bottom_park_path;
    std::vector<size_t> bottom_park_path_length;
    std::vector<NDirection> bottom_park_path_direction;

    std::vector<Cell> right_top_path;
    std::vector<size_t> right_top_path_length;
    std::vector<NDirection> right_top_path_direction;

    std::vector<Cell> right_park_path;
    std::vector<size_t> right_park_path_length;
    std::vector<NDirection> right_park_path_direction;

    std::vector<Cell> park_top_path;
    std::vector<size_t> park_top_path_length;
    std::vector<NDirection> park_top_path_direction;

    std::vector<Cell> park_bottom_path;
    std::vector<size_t> park_bottom_path_length;
    std::vector<NDirection> park_bottom_path_direction;

    std::vector<Cell> park_right_path;
    std::vector<size_t> park_right_path_length;
    std::vector<NDirection> park_right_path_direction;

    std::vector<Cell> park_park_path;
    std::vector<size_t> park_park_path_length;
    std::vector<NDirection> park_park_path_direction;
};