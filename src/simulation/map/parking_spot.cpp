#include "parking_spot.h"

bool Parking::Is_In_Begin_First_Decision_Spot(Cell head) {
    return jung_begin_parking_cell.Are_Same_Cells(head);
}

bool Parking::Is_In_Begin_Second_Decision_Spot(Cell head) {
    return smet_begin_parking_cell.Are_Same_Cells(head);
}

bool Parking::Is_In_End_First_Decision_Spot(Cell head) {
    return jung_end_parking_cell.Are_Same_Cells(head);
}

bool Parking::Is_In_End_Second_Decision_Spot(Cell head) {
    return smet_end_parking_cell.Are_Same_Cells(head);
}

Parking::NParting_Place Parking::Choose_Street_To_Park(float prob_smet, float prob_jung) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution_generator(1, 100); // define the range

    int r = distribution_generator(gen);
    if (r <= (int)(prob_smet * 100)) {
        return NParting_Place::S_STREET;
    } else {
        return NParting_Place::J_STREET;
    }
}

size_t Parking::Get_Iteration_For_Park(size_t min, size_t max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution_generator((int)min,(int)max); // define the range

    size_t iterations = distribution_generator(gen);
    return iterations;
}

bool Parking::Create_Vehicle_On_Current_Spot(float probability) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution_generator(1, 100); // define the range

    int r = distribution_generator(gen);
    if (r <= (int)(probability * 100)) {
        return true;
    } else {
        return false;
    }
}

std::pair<Cell, Cell> Parking::Get_Jung_Street_Edges() {
    return { jung_first_parking_cell, jung_last_parking_cell };
}

std::pair<Cell, Cell> Parking::Get_Smet_Street_Edges() {
    return { smet_first_parking_cell, smet_last_parking_cell };
}
