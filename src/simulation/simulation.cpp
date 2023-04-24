#include "simulation.h"

Simulation::Simulation(Configuration& config) :
    top_crossroad(4, 0, 5, 0, 7, 4, 7, 3,
        config.top_crossroad_duration_time, config.top_crossroad_pause_time, map),
    bottom_crossroad(33, 0, 34, 0, 38, 3, 37, 3,
         config.bottom_crossroad_duration_time, config.bottom_crossroad_pause_time, map),
    right_crossroad(37, 59, 37, 60, 34, 63, 34, 62,
        config.right_crossroad_duration_time, config.right_crossroad_pause_time, map),
    config(config)
{
    Init();
}

void Simulation::Update() {
    Update_Semaphores();
    waiting_places.Update_Stop_Cells(map);
    Update_Vehicles();
    Remove_Vehicles();
    Try_Create_Car();
    std::this_thread::sleep_for(std::chrono::milliseconds(config.pause_milliseconds_count));
    config.iteration++;
    Update_Stats();
}

void Simulation::Update_Semaphores() {
    top_crossroad.Update();
    bottom_crossroad.Update();
    right_crossroad.Update();
}

void Simulation::Update_Vehicles() {
    for (auto& vehicle : vehicles) {
        clear_vehicles |= vehicle.Move_Vehicle();
    }
}

void Simulation::Init()
{
    map = Map();
    parking = Parking();
    config.iteration = 0;
}

Map &Simulation::Get_Map()
{
    return map;
}

void Simulation::Try_Create_Car()
{
    //TOP
    if (!creating_vehicle_on_top)
    {
        if (Vehicle::Start_Generate_Car(config.prob_vehicle_create_top)) {
            creating_vehicle_on_top = true;
            Vehicle new_vehicle = Create_New_Vehicle(Path::NVehicle_Start_Position::TOP);
            remain_vehicle_length_top = new_vehicle.Get_Vehicle_Length();
            vehicles.push_back(new_vehicle);
            Stats_Update_Vehicle(new_vehicle, true);
        }
    } else {
        if (remain_vehicle_length_top) {
            remain_vehicle_length_top--;
        } else {
            creating_vehicle_on_top = false;
        }
    }

    //BOTTOM
    if (!creating_vehicle_on_bottom)
    {
        if (Vehicle::Start_Generate_Car(config.prob_vehicle_create_bottom)) {
            creating_vehicle_on_bottom = true;
            Vehicle new_vehicle = Create_New_Vehicle(Path::NVehicle_Start_Position::BOTTOM);
            remain_vehicle_length_bottom = new_vehicle.Get_Vehicle_Length();
            vehicles.push_back(new_vehicle);
            Stats_Update_Vehicle(new_vehicle, true);
        }
    } else {
        if (remain_vehicle_length_bottom) {
            remain_vehicle_length_bottom--;
        } else {
            creating_vehicle_on_bottom = false;
        }
    }

    //RIGHT
    if (!creating_vehicle_on_right)
    {
        if (Vehicle::Start_Generate_Car(config.prob_vehicle_create_right)) {
            creating_vehicle_on_right = true;
            Vehicle new_vehicle = Create_New_Vehicle(Path::NVehicle_Start_Position::RIGHT);
            remain_vehicle_length_right = new_vehicle.Get_Vehicle_Length();
            vehicles.push_back(new_vehicle);
            Stats_Update_Vehicle(new_vehicle, true);
        }
    } else {
        if (remain_vehicle_length_right) {
            remain_vehicle_length_right--;
        } else {
            creating_vehicle_on_right = false;
        }
    }
}

// Create new vehicle
Vehicle Simulation::Create_New_Vehicle(Path::NVehicle_Start_Position position) {
    Vehicle::NVehicle_Type vehicle_type = Vehicle::Get_Vehicle_Type(config.prob_motorbike, config.prob_car, config.prob_van);
    const bool wanna_park = Vehicle::Wanna_Park(config.prob_park);
    Path::NVehicle_Path path_type = path.Get_Path_Type(position, wanna_park, false);
    const Cell start_cell = path.Get_Cell_By_Vehicle_Phase(path_type, 0);
    const Parking::NParting_Place street = wanna_park ? parking.Choose_Street_To_Park(config.prob_park_in_smet, config.prob_park_in_jung) : Parking::NParting_Place::None;
    const size_t iteration_for_park = wanna_park ? parking.Get_Iteration_For_Park(config.min_iteration_for_park, config.max_iteration_for_park) : 0;
    const size_t phases_count = path.Get_Phase_Count_By_Type(path_type);
    return {vehicle_type, start_cell, 0, wanna_park, position, phases_count, map, path_type, path, waiting_places, parking, iteration_for_park, street};
}

void Simulation::Remove_Vehicles() {
    int32_t index{};

    if (clear_vehicles) {
        std::cout << "Before clear: " << vehicles.size() << std::endl;
        for (auto vehicle : vehicles) {
            // Insert int temp vector only cars which are not remove from map
            if (!vehicle.Remove_Vehicle()) {
                vehicles_temp.insert(vehicles_temp.begin() + index, Vehicle(vehicle));
                index++;
            } else {
                Stats_Update_Vehicle(vehicle, false);
            }
        }
        vehicles.clear();
        std::copy(vehicles_temp.begin(), vehicles_temp.end(), std::back_inserter(vehicles));
        vehicles_temp.clear();
        clear_vehicles = false;
    }
    std::cout << "After clear: " << vehicles.size() << std::endl;
}

// Update stats of vehicle counts
void Simulation::Stats_Update_Vehicle(Vehicle &vehicle, bool add) {
    Vehicle::NVehicle_Type vehicle_type = vehicle.Get_Type();
    bool successfully_parked = vehicle.Want_Park() && vehicle.Vehicle_Parked();
    bool cant_parked = vehicle.Want_Park() && !vehicle.Vehicle_Parked();

    switch (vehicle_type) {
        case Vehicle::NVehicle_Type::VAN:
            config.van_count = add ? (config.van_count + 1) : (config.van_count - 1);
            if (vehicle.Remove_Vehicle()) {
                if (successfully_parked) {
                    config.vans_parked++;
                    config.vehicle_parked++;
                    config.park_attempt_stats[vehicle.Get_Attempt_To_Park()];
                } else if (cant_parked) {
                    config.vans_not_parked++;
                    config.vehicle_not_parked++;
                }
            }
            return;
        case Vehicle::NVehicle_Type::CAR:
            config.car_count = add ? (config.car_count + 1) : config.car_count - 1;
            if (vehicle.Remove_Vehicle()) {
                if (successfully_parked) {
                    config.cars_parked++;
                    config.vehicle_parked++;
                    config.park_attempt_stats[vehicle.Get_Attempt_To_Park()];
                } else if (cant_parked) {
                    config.cars_not_parked++;
                    config.vehicle_not_parked++;
                }
            }
            return;
        case Vehicle::NVehicle_Type::MOTORBIKE:
            config.motorbike_count = add ? (config.motorbike_count + 1) : (config.motorbike_count - 1);
            if (vehicle.Remove_Vehicle()) {
                if (successfully_parked) {
                    config.motorbike_parked++;
                    config.vehicle_parked++;
                    config.park_attempt_stats[vehicle.Get_Attempt_To_Park()];
                } else if (cant_parked) {
                    config.motorbike_not_parked++;
                    config.vehicle_not_parked++;
                }
            }
        return;
    }
}

void Simulation::Reset_Config_Params() {
    config.running = false;
    config.park_places_saved = false;

    config.top_crossroad_duration_time = 5;
    config.top_crossroad_pause_time = 3;
    config.bottom_crossroad_duration_time = 5;
    config.bottom_crossroad_pause_time = 3;
    config.right_crossroad_duration_time = 5;
    config.right_crossroad_pause_time = 3;

    config.pause_milliseconds_count = 100;

    config.prob_vehicle_create_top = 0.1;
    config.prob_vehicle_create_bottom = 0.1;
    config.prob_vehicle_create_right = 0.1;

    config.prob_motorbike = 0.2;
    config.prob_car = 0.65;
    config.prob_van = 0.15;

    config.prob_park = 0.2;
    config.prob_park_in_smet = 0.7;
    config.prob_park_in_jung = 0.3;
    config.min_iteration_for_park = 10;
    config.max_iteration_for_park = 500;
}

void Simulation::Reset_Stats_Params() {
    config.iteration = 0;
    config.van_count = 0;
    config.car_count = 0;
    config.motorbike_count = 0;
    config.iteration_array.clear();
    config.amount_of_vehicles.clear();
    config.amount_of_vans.clear();
    config.amount_of_cars.clear();
    config.amount_of_motorbikes.clear();

    config.park_attempt_stats = {0,0,0,0,0,
                                 0,0,0,0,0};
    config.vehicle_parked = 0;
    config.vans_parked = 0;
    config.cars_parked = 0;
    config.motorbike_parked = 0;

    config.vehicle_not_parked = 0;
    config.vans_not_parked = 0;
    config.cars_not_parked = 0;
    config.motorbike_not_parked = 0;

    vehicles.clear();
}

void Simulation::Update_Stats() noexcept {
    config.amount_of_vehicles.push_back(vehicles.size());
    config.amount_of_vans.push_back(config.van_count);
    config.amount_of_cars.push_back(config.car_count);
    config.amount_of_motorbikes.push_back(config.motorbike_count);
    config.iteration_array.push_back(config.iteration);
}

void Simulation::Restart() {
    map = Map();
    Reset_Config_Params();
    Reset_Stats_Params();
}

void Simulation::Generate_Start_State() {
    //Jungmann street
    std::pair<Cell, Cell> jung_edges = parking.Get_Jung_Street_Edges();
    const int j_y = jung_edges.first.Get_Y();
    int drive_length = 0;
    for (int j_x = jung_edges.first.Get_X(); j_x > jung_edges.second.Get_X(); j_x--) {
        if (map.Get_Cell_Type(j_x, j_y) == Map::NCell_Type::P_F &&
            parking.Create_Vehicle_On_Current_Spot(config.percentage_of_occupied_parking_spots)) {
            drive_length = j_x - jung_edges.second.Get_X() + 3;
            Vehicle parked_vehicle = Create_Parked_Vehicle(Parking::NParting_Place::J_STREET, Cell(j_x, j_y + 1), Parking::NParting_Spot::J_ROADSIDE_PARKING, drive_length, true);
            vehicles.push_back(parked_vehicle);
        }
    }

    //Smet street
    std::pair<Cell, Cell> smet_edges = parking.Get_Smet_Street_Edges();
    const int s_x = smet_edges.first.Get_X();
    for (int s_y = smet_edges.first.Get_Y(); s_y > smet_edges.second.Get_Y(); s_y--) {
        if (map.Get_Cell_Type(s_x - 1, s_y) == Map::NCell_Type::P_F &&
            parking.Create_Vehicle_On_Current_Spot(config.percentage_of_occupied_parking_spots)) {
            drive_length = s_y - smet_edges.second.Get_Y() + 3;
            Vehicle parked_vehicle = Create_Parked_Vehicle(Parking::NParting_Place::S_STREET, Cell(s_x, s_y), Parking::NParting_Spot::S_ANGLED_PARKING, drive_length, false);
            vehicles.push_back(parked_vehicle);
        }
        if (map.Get_Cell_Type(s_x, s_y) == Map::NCell_Type::P_F &&
            parking.Create_Vehicle_On_Current_Spot(config.percentage_of_occupied_parking_spots)) {
            drive_length = s_x - smet_edges.second.Get_X() + 3;
            Vehicle parked_vehicle = Create_Parked_Vehicle(Parking::NParting_Place::J_STREET, Cell(s_x, s_y), Parking::NParting_Spot::S_ROADSIDE_PARKING, drive_length, true);
            vehicles.push_back(parked_vehicle);
        }
    }
}

Vehicle Simulation::Create_Parked_Vehicle(Parking::NParting_Place street, Cell head_cell, Parking::NParting_Spot park_place, int drive_length, bool van_allowed) {
    Vehicle::NVehicle_Type vehicle_type = Vehicle::Get_Vehicle_Type(config.prob_motorbike, config.prob_car, config.prob_van);
    while (!van_allowed && vehicle_type == Vehicle::NVehicle_Type::VAN) {
        vehicle_type = Vehicle::Get_Vehicle_Type(config.prob_motorbike, config.prob_car, config.prob_van);
    }
    const bool wanna_park = true;
    Path::NVehicle_Path path_type = Path::NVehicle_Path::RIGHT_PARK;
    const Cell start_cell = head_cell;
    const size_t iteration_for_park = parking.Get_Iteration_For_Park(config.min_iteration_for_park, config.max_iteration_for_park);
    std::size_t phases_count = 0;
    if (street == Parking::NParting_Place::J_STREET) {
        phases_count = 1;
    } else {
        phases_count = 0;
    }
    Vehicle newVehicle = {vehicle_type, start_cell, 0, wanna_park, Path::NVehicle_Start_Position::RIGHT, phases_count,
            map, path_type, path, waiting_places, parking, iteration_for_park, street};
    newVehicle.Setup_Parked_Vehicle(park_place, drive_length);
    return newVehicle;
}
