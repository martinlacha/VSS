#include "vehicle.h"

Vehicle::Vehicle(Vehicle::NVehicle_Type type, int x, int y) : vehicle_type(type) {
    color = Generate_Unique_Color();
}

ImVec4 Vehicle::Generate_Unique_Color() {
    srand( (unsigned)time( nullptr ) );
    float x = (float) rand()/RAND_MAX;
    float y = (float) rand()/RAND_MAX;
    float z = (float) rand()/RAND_MAX;
    return {x, y, z, 1};
}