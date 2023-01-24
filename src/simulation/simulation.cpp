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
    iteration++;

    Update_Semaphores();
    waiting_places.Update_Stop_Cells(map);
    Update_Vehicles();
    Remove_Vehicles();
    if (iteration == 10)
    {
        Try_Create_Car();
        iteration = 0;
    }
    std::this_thread::sleep_for(iteration_pause);

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
    iteration = 0;
    iteration_pause = std::chrono::milliseconds(config.pause_milliseconds_count);
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
        }
    } else {
        if (remain_vehicle_length_right) {
            remain_vehicle_length_right--;
        } else {
            creating_vehicle_on_right = false;
        }
    }
}

Vehicle Simulation::Create_New_Vehicle(Path::NVehicle_Start_Position position) {
    // TODO Test Vehicle type
    //Vehicle::NVehicle_Type vehicle_type = Vehicle::Get_Vehicle_Type(config.prob_motorbike, config.prob_car, config.prob_van);
    Vehicle::NVehicle_Type vehicle_type;
    if (phase == 1) {
        vehicle_type = Vehicle::NVehicle_Type::MOTORBIKE;
    } else if (phase == 2) {
        vehicle_type = Vehicle::NVehicle_Type::CAR;
    } else if (phase == 3) {
        vehicle_type = Vehicle::NVehicle_Type::VAN;
        phase = 0;
    }
    phase++;

    //TODO TEST Path type
    //Path::NVehicle_Path path_type = path.Get_Path_Type(position, config.prob_park);
    Path::NVehicle_Path path_type = Path::NVehicle_Path::TOP_BOTTOM;


    const Cell start_cell = path.Get_Cell_By_Vehicle_Phase(path_type, 0);
    const bool wanna_park = Vehicle::Wanna_Park(config.prob_park);
    const size_t phases_count = path.Get_Phase_Count_By_Type(path_type);
    return {vehicle_type, start_cell, 0, wanna_park, position, phases_count, map, path_type, path, waiting_places};
}

void Simulation::Remove_Vehicles() {
    //vehicles.erase(std::remove_if(vehicles.begin(), vehicles.end(), [](Vehicle& obj) { return obj.Remove_Vehicle(); }),vehicles.end());
    int32_t index{};
    if (clear_vehicles) {
        std::cout << "Before clear: " << vehicles.size() << std::endl;
        for (auto vehicle : vehicles) {
            if (!vehicle.Remove_Vehicle()) {
                vehicles_temp.insert(vehicles_temp.begin() + index, Vehicle(vehicle));
                index++;
            }
        }
        vehicles.clear();
        std::copy(vehicles_temp.begin(), vehicles_temp.end(), std::back_inserter(vehicles));
        clear_vehicles = false;
        std::cout << "After clear: " << vehicles.size() << std::endl;
    }

    /*
    auto it = vehicles.begin();
    while (true) {
        if (vehicles.empty() || it == vehicles.end()) {
            break;
        }

        Vehicle vehicle = *(it);
        if (vehicle.Remove_Vehicle()) {
            vehicles.erase(it);
            it = vehicles.begin();
            std::cout << "Remaining cars: " << vehicles.size() << std::endl;
            continue;
        }
        it++;
    }
    */
}