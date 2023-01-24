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
    size_t pause_milliseconds_count = 50;

    // Configuration of vehicles
    float prob_vehicle_create_top = 1.0;
    float prob_vehicle_create_bottom = 0.0;
    float prob_vehicle_create_right = 0.0;

    // Probabilities of create type vehicle
    float prob_motorbike = 0.33;
    float prob_car = 0.34;
    float prob_van = 0.33;

    // Probability of park
    float prob_park = 0.0;
};