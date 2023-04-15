#pragma once

#include <iostream>
#include <vector>

class Configuration {
public:
    Configuration() = default;
    // Statistics
    size_t iteration{};
    size_t van_count{};
    size_t car_count{};
    size_t motorbike_count{};
    std::vector<size_t> iteration_array{};
    std::vector<size_t> amount_of_vehicles{};
    std::vector<size_t> amount_of_vans{};
    std::vector<size_t> amount_of_cars{};
    std::vector<size_t> amount_of_motorbikes{};

    // Configuration of crossroads and semaphores
    size_t top_crossroad_duration_time = 5;
    size_t top_crossroad_pause_time = 3;
    size_t bottom_crossroad_duration_time = 5;
    size_t bottom_crossroad_pause_time = 3;
    size_t right_crossroad_duration_time = 5;
    size_t right_crossroad_pause_time = 3;

    // Time of break between iteration
    size_t pause_milliseconds_count = 0;

    // Configuration of vehicles
    float prob_vehicle_create_top = 0.1;
    float prob_vehicle_create_bottom = 0.1;
    float prob_vehicle_create_right = 0.1;

    // Probabilities of create type vehicle
    float prob_motorbike = 0.2;
    float prob_car = 0.65;
    float prob_van = 0.15;

    // Probability of park
    float prob_park = 0.2;
    float prob_park_in_smet = 0.7;
    float prob_park_in_jung = 0.3;
    size_t min_iteration_for_park = 10;
    size_t max_iteration_for_park = 50;
};