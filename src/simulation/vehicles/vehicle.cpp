#include "vehicle.h"

Vehicle::Vehicle(Vehicle::NVehicle_Type type, Cell start_cell, size_t path_length, bool wanna_park, Path::NVehicle_Start_Position start,
                 size_t phase_count, Map& map, Path::NVehicle_Path path_type, Path& path, Semaphore_Waiting_Place& places) :
        vehicle_type(type), length_to_drive(path_length), already_parked(false), phase_path(0),
        start_cell(start_cell), attempt_to_park(0), want_to_park(wanna_park), start_position(start),
        phase_remain(phase_count), exiting_map(!wanna_park), map(map), remove(false), path_type(path_type),
        path(path), waiting_places(places), creating(true) {
    color = Generate_Unique_Color();
    last_cell = path.Get_Cell_By_Vehicle_Phase(path_type, phase_remain);
    switch (type) {
        case NVehicle_Type::MOTORBIKE:
            vehicle_length = 1;
            break;
        case NVehicle_Type::CAR:
            vehicle_length = 2;
            break;
        case NVehicle_Type::VAN:
            vehicle_length = 3;
            break;
    }
}

ImVec4 Vehicle::Generate_Unique_Color() {
    srand( (unsigned)time( nullptr ) );
    float x = (float) rand()/RAND_MAX;
    float y = (float) rand()/RAND_MAX;
    float z = (float) rand()/RAND_MAX;
    return {x, y, z, 1};
}

void Vehicle::Move_Vehicle() {
    if (!length_to_drive) {
        if (phase_remain) {
            Set_New_Direction();
            --phase_remain;
            ++phase_path;
        } else if (exiting_map) {
            length_to_drive = vehicle_length;
        } else {
            //TODO tady je možnost že nezaparkoval a možná chce to zkusit znovu
        }
    }

    if (Can_Vehicle_Move()) {
        Change_Cells_And_Map();
        length_to_drive--;
    }
}

Vehicle::NVehicle_Type Vehicle::Get_Vehicle_Type(float prob_motorbike, float prob_car, float prob_van) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution_generator(1, 100); // define the range

    int r = distribution_generator(gen);
    if (r <= (int)(prob_car * 100)) {
        return NVehicle_Type::MOTORBIKE;
    }
    else if (r <= (int)((prob_motorbike + prob_car) * 100)) {
        return NVehicle_Type::CAR;
    }
    else {
        return NVehicle_Type::VAN;
    }
}

bool Vehicle::Wanna_Park(float probability) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution_generator(1, 100); // define the range
    int r = distribution_generator(gen);
    if (r <= (int)(probability * 100)) {
        return true;
    }
    return false;
}

bool Vehicle::Start_Generate_Car(float probability) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution_generator(1, 100); // define the range
    int r = distribution_generator(gen);
    if (r <= (int)(probability * 100)) {
        return true;
    }
    return false;
}

size_t Vehicle::Get_Vehicle_Length() const {
    return vehicle_length;
}

bool Vehicle::Can_Vehicle_Move() {
    Cell head = cells.empty() ? path.Get_Cell_By_Vehicle_Phase(path_type, 0) : cells.at(0);
    if (waiting_places.Stop_On_Semaphore(head)) {
        return false;
    }

    switch (direction) {
        case NMove_Direction::UP:
            if (head.Get_X() == 0) {
                return true;
            }
            if (map.Get_Cell_Type(head.Get_X() - 1, head.Get_Y()) == Map::NCell_Type::V) {
                return false;
            }
            break;
        case NMove_Direction::DOWN:
            if (head.Get_X() == 39) {
                return true;
            }
            if (map.Get_Cell_Type(head.Get_X() + 1, head.Get_Y()) == Map::NCell_Type::V) {
                return false;
            }
            break;
        case NMove_Direction::RIGHT:
            if (head.Get_Y() == 63) {
                return true;
            }
            if (map.Get_Cell_Type(head.Get_X(), head.Get_Y() + 1) == Map::NCell_Type::V) {
                return false;
            }
            break;
        case NMove_Direction::LEFT:
            if (head.Get_Y() == 0) {
                return true;
            }
            if (map.Get_Cell_Type(head.Get_X(), head.Get_Y() - 1) == Map::NCell_Type::V) {
                return false;
            }
            break;
    }
    return true;
}

void Vehicle::Change_Cells_And_Map() {
    if (creating) {
        if (cells.empty()) {
            Cell first_cell = path.Get_Cell_By_Vehicle_Phase(path_type, 0);
            cells.push_back(first_cell);
            map.Set_Cell_Type(first_cell.Get_X(), first_cell.Get_Y(), Map::NCell_Type::V);
            if (vehicle_type == NVehicle_Type::MOTORBIKE) {
                creating = false;
            }
            return;
        } else {
            cells.push_back(start_cell);
        }
    }
    Cell head = cells.at(0);
    switch (direction) {
        case NMove_Direction::UP:
            Change_Cells_And_Map_By_Direction({head.Get_X() - 1, head.Get_Y()});
            break;
        case NMove_Direction::DOWN:
            Change_Cells_And_Map_By_Direction({head.Get_X() + 1, head.Get_Y()});
            break;
        case NMove_Direction::LEFT:
            Change_Cells_And_Map_By_Direction({head.Get_X(), head.Get_Y() - 1});
            break;
        case NMove_Direction::RIGHT:
            Change_Cells_And_Map_By_Direction({head.Get_X(), head.Get_Y() + 1});
            break;
    }

    for (auto& cell : cells) {
        std::cout << cell.Get_X() << ":" << cell.Get_Y() << "-";
    }
    std::cout << std::endl;
}

void Vehicle::Change_Cells_And_Map_By_Direction(Cell next_cell) {
    Cell prev_cell;
    bool erase_first_cell = false;
    for (size_t i = 0; i < cells.size(); ++i) {
        Cell cell = cells.at(i);

        if (i == 0) {
            if (!Is_Out_Of_Map(next_cell)) {
                cells[0] = next_cell;
                map.Set_Cell_Type(next_cell.Get_X(), next_cell.Get_Y(), Map::NCell_Type::V);
            } else {
                erase_first_cell = true;
                prev_cell = cell;
                continue;
            }
            prev_cell = Cell(cell.Get_X(), cell.Get_Y());
            if (vehicle_type == NVehicle_Type::MOTORBIKE) {
                map.Set_Cell_Type(prev_cell.Get_X(), prev_cell.Get_Y(), Map::NCell_Type::R);
            }
        } else {
            cells[i] = prev_cell;
            map.Set_Cell_Type(prev_cell.Get_X(), prev_cell.Get_Y(), Map::NCell_Type::V);
            prev_cell = cell;

            if (i == vehicle_length - 1 && creating) {
                creating = false;
                break;
            } else if (i == vehicle_length - 1) {
                map.Set_Cell_Type(cell.Get_X(), cell.Get_Y(), Map::NCell_Type::R);
                break;
            }
        }
    }

    if (erase_first_cell) {
        cells.erase(cells.begin());
    }

    if (cells.empty()) {
        map.Set_Cell_Type(last_cell.Get_X(), last_cell.Get_Y(), Map::NCell_Type::R);
        remove = true;
    }
}

bool Vehicle::Is_Out_Of_Map(Cell& cell) {
    size_t x = cell.Get_X(), y = cell.Get_Y();
    if (x < 0 || x > 40) {
        return true;
    }
    if (y < 0 || y > 64) {
        return true;
    }
    return false;
}

void Vehicle::Set_New_Direction() {
    Path::NDirection direct = path.Get_Direction_By_Path_Type(path_type, phase_path);

    if (direct == Path::NDirection::UP) {
        direction = NMove_Direction::UP;
    } else if (direct == Path::NDirection::DOWN) {
        direction = NMove_Direction::DOWN;
    } else if (direct == Path::NDirection::LEFT) {
        direction = NMove_Direction::LEFT;
    } else if (direct == Path::NDirection::RIGHT) {
        direction = NMove_Direction::RIGHT;
    } else {
        throw std::invalid_argument("Error direction");
    }
    length_to_drive = path.Get_Length_By_Vehicle_Phase(path_type, phase_path) + vehicle_length + 2;
}

bool Vehicle::Remove_Vehicle() {
    return remove;
}

void Vehicle::Add_Vehicle_Into_Map() {
    if (cells.empty()) {

    } else  {

    }
}

