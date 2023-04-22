#pragma once

#include <cstdint>
#include <array>
#include <random>

#include "../configuration.h"
#include "../cell.h"

class Parking {
public:
    enum class NParting_Place : uint8_t {
        J_STREET,
        S_STREET,
        None
    };

    enum class NParting_Spot : uint8_t {
        J_ROADSIDE_PARKING,
        S_ANGLED_PARKING,
        S_ROADSIDE_PARKING,
        None
    };

    NParting_Place Choose_Street_To_Park(float prob_smet, float prob_jung);
    size_t Get_Iteration_For_Park(size_t min, size_t max);
    bool Is_In_Begin_First_Decision_Spot(Cell head);
    bool Is_In_End_First_Decision_Spot(Cell head);
    bool Is_In_Begin_Second_Decision_Spot(Cell head);
    bool Is_In_End_Second_Decision_Spot(Cell head);

private:
    Cell jung_begin_parking_cell = {33, 61};
    Cell jung_end_parking_cell = {8, 61};
    Cell smet_begin_parking_cell = {6, 58};
    Cell smet_end_parking_cell = {6, 4};
};