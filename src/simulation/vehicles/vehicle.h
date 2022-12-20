#pragma once

#include "imgui.h"
#include "../cell.h"

#include <cstdint>
#include <ctime>
#include <vector>

class Vehicle
{
public:
    enum class NVehicle_Type : uint8_t {
        MOTORBIKE,
        CAR,
        VAN
    };

    Vehicle(NVehicle_Type type, int x, int y);
private:
    NVehicle_Type vehicle_type;
    std::vector<Cell> cells;
    ImVec4 color;

    ImVec4 Generate_Unique_Color();
};