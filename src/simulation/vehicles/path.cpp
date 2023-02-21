#include "path.h"

Path::Path() {
    top_bottom_path = {{0, 1}, {39, 1}};
    top_bottom_path_length = {39};
    top_bottom_path_direction = {NDirection::DOWN};

    top_right_path = {{0, 1}, {36, 1}, {36, 63}};
    top_right_path_length = {37, 61};
    top_right_path_direction = {NDirection::DOWN, NDirection::RIGHT};

    top_park_path = {{0, 1}, {36, 1}, {36, 61}, {6, 61}, {6, 3}};
    top_park_path_length = {37, 60, 30, 58};
    top_park_path_direction = {NDirection::DOWN, NDirection::RIGHT, NDirection::UP, NDirection::LEFT};

    bottom_top_path = {{39, 2}, {0, 2}};
    bottom_top_path_length = {39};
    bottom_top_path_direction = {NDirection::UP};

    bottom_right_path = {{39, 2}, {36, 2}, {36, 63}};
    bottom_right_path_length = {4, 61};
    bottom_right_path_direction = {NDirection::UP, NDirection::RIGHT};

    bottom_park_path = {{39, 2}, {36, 2}, {36, 61}, {6, 61}, {6, 3}};
    bottom_park_path_length = {4, 59, 30, 58};
    bottom_park_path_direction = {NDirection::UP, NDirection::RIGHT, NDirection::UP, NDirection::LEFT};

    right_top_path = {{35, 63}, {35, 2}, {0, 2}};
    right_top_path_length = {62, 35};
    right_top_path_direction = {NDirection::LEFT, NDirection::UP};

    right_park_path = {{35, 63}, {35, 61}, {6, 61}, {6, 3}};
    right_park_path_length = {3, 29, 58};
    right_park_path_direction = {NDirection::LEFT, NDirection::UP, NDirection::LEFT};

    park_top_path = {{6, 3}, {6, 2}, {0, 2}};
    park_top_path_length = {1, 6};
    park_top_path_direction = {NDirection::LEFT, NDirection::UP};


    park_bottom_path = {{6, 3}, {6, 1}, {39, 1}};
    park_bottom_path_length = {2, 33};
    park_bottom_path_direction = {NDirection::LEFT, NDirection::DOWN};

    park_right_path = {{6, 3}, {6, 1}, {36, 1}, {36, 63}};
    park_right_path_length = {2, 30, 62};
    park_right_path_direction = {NDirection::LEFT, NDirection::DOWN, NDirection::RIGHT};

    park_park_path = {{6, 3}, {6, 1}, {36, 1}, {36, 61}, {6, 61}, {6, 3}};
    park_park_path_length = {2, 30, 60, 30, 58};
    park_park_path_direction = {NDirection::LEFT, NDirection::DOWN, NDirection::RIGHT, NDirection::UP, NDirection::LEFT};
}

Path::NVehicle_Path Path::Get_Path_Type(NVehicle_Start_Position start_position, float prob_park, bool in_park_zone) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution_generator(1, 100); // define the range

    int r = distribution_generator(gen);
    if (r <= (int)(prob_park * 100)) {
        if (in_park_zone) {
            return NVehicle_Path::PARK_PARK;
        } else {
            switch (start_position) {
                case NVehicle_Start_Position::TOP:
                    return NVehicle_Path::TOP_PARK;
                case NVehicle_Start_Position::BOTTOM:
                    return NVehicle_Path::BOTTOM_PARK;
                case NVehicle_Start_Position::RIGHT:
                    return NVehicle_Path::RIGHT_PARK;
            }
        }
    }
    else {
        r = distribution_generator(gen);
        if (in_park_zone) {
            if (r <= 33) {
                return NVehicle_Path::PARK_TOP;
            } else if (r <= 66) {
                return NVehicle_Path::PARK_BOTTOM;
            } else {
                return NVehicle_Path::PARK_RIGHT;
            }
        }
        switch (start_position) {
            case NVehicle_Start_Position::TOP:
                if (r < 50) {
                    return NVehicle_Path::TOP_BOTTOM;
                } else {
                    return NVehicle_Path::TOP_RIGHT;
                }
            case NVehicle_Start_Position::BOTTOM:
                if (r < 50) {
                    return NVehicle_Path::BOTTOM_TOP;
                } else {
                    return NVehicle_Path::BOTTOM_RIGHT;
                }
            case NVehicle_Start_Position::RIGHT:
                return NVehicle_Path::RIGHT_TOP;
        }
    }
    return NVehicle_Path::ERROR_PATH;
}

Cell Path::Get_Cell_By_Vehicle_Phase(NVehicle_Path type_path, size_t index) {
    Cell next_cell;
    switch (type_path) {
        case NVehicle_Path::TOP_BOTTOM:
            next_cell = top_bottom_path[index];
            break;
        case NVehicle_Path::TOP_RIGHT:
            next_cell = top_right_path[index];
            break;
        case NVehicle_Path::TOP_PARK:
            next_cell = top_park_path[index];
            break;
        case NVehicle_Path::BOTTOM_TOP:
            next_cell = bottom_top_path[index];
            break;
        case NVehicle_Path::BOTTOM_RIGHT:
            next_cell = bottom_right_path[index];
            break;
        case NVehicle_Path::BOTTOM_PARK:
            next_cell = bottom_park_path[index];
            break;
        case NVehicle_Path::RIGHT_TOP:
            next_cell = right_top_path[index];
            break;
        case NVehicle_Path::RIGHT_PARK:
            next_cell = right_park_path[index];
            break;
        case NVehicle_Path::PARK_TOP:
            next_cell = park_top_path[index];
            break;
        case NVehicle_Path::PARK_BOTTOM:
            next_cell = park_bottom_path[index];
            break;
        case NVehicle_Path::PARK_RIGHT:
            next_cell = park_right_path[index];
            break;
        case NVehicle_Path::PARK_PARK:
            next_cell = park_park_path[index];
            break;
        case NVehicle_Path::ERROR_PATH:
            std::cout << "Error: Invalid path type." << std::endl;
            break;
        default:
            std::cout << "Error: Invalid vehicle path for index: " << index << std::endl;
            next_cell =  {0, 0};
    }
    return next_cell;
}

size_t Path::Get_Length_By_Vehicle_Phase(NVehicle_Path type_path, size_t index) {
    index--;
    switch (type_path) {
        case NVehicle_Path::TOP_BOTTOM:
            return top_bottom_path_length[index];
        case NVehicle_Path::TOP_RIGHT:
            return top_right_path_length[index];
        case NVehicle_Path::TOP_PARK:
            return top_park_path_length[index];
        case NVehicle_Path::BOTTOM_TOP:
            return bottom_top_path_length[index];
        case NVehicle_Path::BOTTOM_RIGHT:
            return bottom_right_path_length[index];
        case NVehicle_Path::BOTTOM_PARK:
            return bottom_park_path_length[index];
        case NVehicle_Path::RIGHT_TOP:
            return right_top_path_length[index];
        case NVehicle_Path::RIGHT_PARK:
            return right_park_path_length[index];
        case NVehicle_Path::PARK_TOP:
            return park_top_path_length[index];
        case NVehicle_Path::PARK_BOTTOM:
            return park_bottom_path_length[index];
        case NVehicle_Path::PARK_RIGHT:
            return park_right_path_length[index];
        case NVehicle_Path::PARK_PARK:
            return park_park_path_length[index];
        case NVehicle_Path::ERROR_PATH:
            break;
    }
    return -1;
}

size_t Path::Get_Phase_Count_By_Type(Path::NVehicle_Path type) {
    switch (type) {
        case NVehicle_Path::TOP_BOTTOM:
            return top_bottom_path_length.size();
        case NVehicle_Path::TOP_RIGHT:
            return top_right_path_length.size();
        case NVehicle_Path::TOP_PARK:
            return top_park_path_length.size();
        case NVehicle_Path::BOTTOM_TOP:
            return bottom_top_path_length.size();
        case NVehicle_Path::BOTTOM_RIGHT:
            return bottom_right_path_length.size();
        case NVehicle_Path::BOTTOM_PARK:
            return bottom_park_path_length.size();
        case NVehicle_Path::RIGHT_TOP:
            return right_top_path_length.size();
        case NVehicle_Path::RIGHT_PARK:
            return right_park_path_length.size();
        case NVehicle_Path::PARK_TOP:
            return park_top_path_length.size();
        case NVehicle_Path::PARK_BOTTOM:
            return park_bottom_path_length.size();
        case NVehicle_Path::PARK_RIGHT:
            return park_right_path_length.size();
        case NVehicle_Path::PARK_PARK:
            return park_park_path_length.size();
        case NVehicle_Path::ERROR_PATH:
            break;
    }
    return -1;
}

Path::NDirection Path::Get_Direction_By_Path_Type(NVehicle_Path type, size_t index) {
    switch (type) {
        case NVehicle_Path::TOP_BOTTOM:
            return top_bottom_path_direction[index];
        case NVehicle_Path::TOP_RIGHT:
            return top_right_path_direction[index];
        case NVehicle_Path::TOP_PARK:
            return top_park_path_direction[index];
        case NVehicle_Path::BOTTOM_TOP:
            return bottom_top_path_direction[index];
        case NVehicle_Path::BOTTOM_RIGHT:
            return bottom_right_path_direction[index];
        case NVehicle_Path::BOTTOM_PARK:
            return bottom_park_path_direction[index];
        case NVehicle_Path::RIGHT_TOP:
            return right_top_path_direction[index];
        case NVehicle_Path::RIGHT_PARK:
            return right_park_path_direction[index];
        case NVehicle_Path::PARK_TOP:
            return park_top_path_direction[index];
        case NVehicle_Path::PARK_BOTTOM:
            return park_bottom_path_direction[index];
        case NVehicle_Path::PARK_RIGHT:
            return park_right_path_direction[index];
        case NVehicle_Path::PARK_PARK:
            return park_park_path_direction[index];
        case NVehicle_Path::ERROR_PATH:
            std::cout << "Error_Path: Get_Direction_By_Path_Type";
            break;
    }
    return NDirection::ERROR_DIRECTION;
}
