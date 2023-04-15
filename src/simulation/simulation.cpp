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
    std::this_thread::sleep_for(iteration_pause);
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
            Stats_Update_Vehicle(new_vehicle.Get_Type(), true);
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
            Stats_Update_Vehicle(new_vehicle.Get_Type(), true);
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
            Stats_Update_Vehicle(new_vehicle.Get_Type(), true);
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
            if (!vehicle.Remove_Vehicle()) {
                vehicles_temp.insert(vehicles_temp.begin() + index, Vehicle(vehicle));
                index++;
                Stats_Update_Vehicle(vehicle.Get_Type(), false);
            }
        }
        vehicles.clear();
        std::copy(vehicles_temp.begin(), vehicles_temp.end(), std::back_inserter(vehicles));
        vehicles_temp.clear();
        clear_vehicles = false;
        std::cout << "After clear: " << vehicles.size() << std::endl;
    }
}

// Update stats of vehicle counts
void Simulation::Stats_Update_Vehicle(Vehicle::NVehicle_Type vehicle_type, bool add) {
    switch (vehicle_type) {
        case Vehicle::NVehicle_Type::VAN:
            if (!config.van_count && !add) {
                std::cout << "Error vans count sub." << std::endl;
                return;
            }
            config.van_count = add ? (config.van_count + 1) : (config.van_count - 1);
            return;
        case Vehicle::NVehicle_Type::CAR:
            if (!config.car_count && !add) {
                std::cout << "Error cars count sub." << std::endl;
                return;
            }
            config.car_count = add ? (config.car_count + 1) : config.car_count - 1;
            return;
        case Vehicle::NVehicle_Type::MOTORBIKE:
            if (!config.motorbike_count && !add) {
                std::cout << "Error motorbike count sub." << std::endl;
                return;
            }
            config.motorbike_count = add ? (config.motorbike_count + 1) : (config.motorbike_count - 1);
            return;
    }
}

void Simulation::Reset_Config_Params() {
    config.top_crossroad_duration_time = 5;
    config.top_crossroad_pause_time = 3;
    config.bottom_crossroad_duration_time = 5;
    config.bottom_crossroad_pause_time = 3;
    config.right_crossroad_duration_time = 5;
    config.right_crossroad_pause_time = 3;

    config.pause_milliseconds_count = 10;

    config.prob_vehicle_create_top = 0.1;
    config.prob_vehicle_create_bottom = 0.1;
    config.prob_vehicle_create_right = 0.1;
    config.prob_motorbike = 0.2;
    config.prob_car = 0.5;
    config.prob_van = 0.3;
    config.prob_park = 1.0;
    config.prob_park_in_smet = 0.0;
    config.prob_park_in_jung = 1.0;
    config.min_iteration_for_park = 10;
    config.max_iteration_for_park = 100;
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
}

void Simulation::Update_Stats() noexcept {
    config.amount_of_vehicles.push_back(vehicles.size());
    config.amount_of_vans.push_back(config.van_count);
    config.amount_of_cars.push_back(config.car_count);
    config.amount_of_motorbikes.push_back(config.motorbike_count);
    config.iteration_array.push_back(config.iteration);

    if (config.car_count > 1000 ||
        config.van_count > 1000 ||
        config.motorbike_count > 1000) {
        std::cout << "" << std::endl;
    }
}
