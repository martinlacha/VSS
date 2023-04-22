#pragma once

#include <iostream>
#include <vector>
#include <array>

class Configuration {
public:
    Configuration() = default;

    // GUI configuration
    bool running = false;
    bool park_places_saved = false;

    // Statistics
    size_t iteration{};
    size_t van_count{};
    size_t car_count{};
    size_t motorbike_count{};
    std::vector<std::uint32_t> iteration_array{0};
    std::vector<std::uint32_t> amount_of_vehicles{0};
    std::vector<std::uint32_t> amount_of_vans{0};
    std::vector<std::uint32_t> amount_of_cars{0};
    std::vector<std::uint32_t> amount_of_motorbikes{0};

    std::array<int, 10> park_attempt_stats{0,0,0,0,0,
                                           0,0,0,0,0,};
    int vehicle_parked{};
    int vans_parked{};
    int cars_parked{};
    int motorbike_parked{};

    int vehicle_not_parked{};
    int vans_not_parked{};
    int cars_not_parked{};
    int motorbike_not_parked{};

    // Configuration of crossroads and semaphores
    size_t top_crossroad_duration_time = 5;
    size_t top_crossroad_pause_time = 3;
    size_t bottom_crossroad_duration_time = 5;
    size_t bottom_crossroad_pause_time = 3;
    size_t right_crossroad_duration_time = 5;
    size_t right_crossroad_pause_time = 3;

    // Time of break between iteration
    int pause_milliseconds_count = 100;

    // Intensity of amount of vehicles per time
    float intensity_of_traffic = 0.2;

    // Configuration of vehicles
    float prob_vehicle_create_top = 0.1;
    float prob_vehicle_create_bottom = 0.1;
    float prob_vehicle_create_right = 0.1;

    // Probabilities of create type vehicle
    float prob_motorbike = 0.2;
    float prob_car = 0.65;
    float prob_van = 0.15;

    // Probability of park
    float percentage_of_occupied_parking_spots = 0.0;
    float prob_park = 0.2;
    float prob_park_in_smet = 0.7;
    float prob_park_in_jung = 0.3;
    int min_iteration_for_park = 10;
    int max_iteration_for_park = 500;
};