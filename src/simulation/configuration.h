#pragma once

#include <iostream>

class Configuration {
public:
    Configuration() = default;
    // Configuration of crossroads and semaphores
    size_t top_crossroad_duration_time = 5;
    size_t top_crossroad_pause_time = 3;
    size_t bottom_crossroad_duration_time = 5;
    size_t bottom_crossroad_pause_time = 3;
    size_t right_crossroad_duration_time = 5;
    size_t right_crossroad_pause_time = 3;

    // Time of break between iteration
    size_t pause_milliseconds_count = 10;

    // Configuration of vehicles
    float prob_vehicle_create_top = 0.1;
    float prob_vehicle_create_bottom = 0.1;
    float prob_vehicle_create_right = 0.1;

    // Probabilities of create type vehicle
    float prob_motorbike = 0.2;
    float prob_car = 0.5;
    float prob_van = 0.3;

    // Probability of park
    float prob_park = 0.2;
    float next_park_try_step = 0.1;
};