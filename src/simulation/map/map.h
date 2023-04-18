#pragma once

#include <cstdint>
#include <cstddef>

constexpr int map_height = 40;
constexpr int map_width = 64;
constexpr float cell_size = 15.0f;

class Map
{
public:
    Map() = default;
    enum class NCell_Type : uint8_t {
        V,              // VEHICLE
        R,              // ROAD
        B,              // BUILDING
        S,              // SEMAPHORE_BLACK
        S_R,            // SEMAPHORE_RED
        S_G,            // SEMAPHORE_GREEN
        P_F,            // PARKING_SPOT_FREE
        P_O,            // PARKING_SPOT_OCCUPIED
        G,              // PARK_GRASS
        W,              // SIDEWALK
        E               // ERROR
    };

    typedef NCell_Type t;
    NCell_Type* Get_Map();
    [[nodiscard]] int Get_Map_Height() const noexcept;
    [[nodiscard]] int Get_Map_Width() const noexcept;
    [[nodiscard]] NCell_Type Get_Cell_Type(size_t x, size_t y) const;
    void Set_Cell_Type(size_t x, size_t y, NCell_Type new_type);

private:
    NCell_Type map[map_height][map_width] = {
        // 1
        {
            t::B, t::R, t::R, t::W, t::G, t::G, t::G, t::G,
            t::G, t::G, t::G, t::G, t::G, t::G, t::G, t::G,
            t::G, t::G, t::G, t::G, t::G, t::G, t::G, t::G,
            t::G, t::G, t::G, t::G, t::G, t::G, t::G, t::G,
            t::G, t::G, t::G, t::G, t::G, t::G, t::G, t::G,
            t::G, t::G, t::G, t::G, t::G, t::G, t::G, t::G,
            t::G, t::G, t::G, t::G, t::G, t::G, t::G, t::G,
            t::G, t::G, t::G, t::G, t::G, t::G, t::G, t::G
        },
        // 2
        {
            t::B, t::R, t::R, t::W, t::G, t::G, t::G, t::G,
            t::G, t::G, t::G, t::G, t::G, t::G, t::G, t::G,
            t::G, t::G, t::G, t::G, t::G, t::G, t::G, t::G,
            t::G, t::G, t::G, t::G, t::G, t::G, t::G, t::G,
            t::G, t::G, t::G, t::G, t::G, t::G, t::G, t::G,
            t::G, t::G, t::G, t::G, t::G, t::G, t::G, t::G,
            t::G, t::G, t::G, t::G, t::G, t::G, t::G, t::G,
            t::G, t::G, t::G, t::G, t::G, t::G, t::G, t::G
        },
        // 3
        {
            t::B, t::R, t::R, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W
        },
        // 4
        {
            t::B, t::R, t::R, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W
        },
        // 5
        {
            t::S, t::R, t::R, t::W, t::W, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::W, t::W,   t::W, t::W, t::W
        },
        // 6
        {
            t::S, t::R, t::R, t::W, t::W, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::W, t::W,   t::W, t::W, t::W
        },
        // 7
        {
            t::B, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
        },
        // 8
        {
            t::B, t::R, t::R, t::S, t::S, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F, t::P_F,
            t::P_F, t::P_F, t::P_F, t::W, t::W,   t::R, t::W, t::B
        },
        // 9
        {
            t::B, t::R, t::R, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::R, t::W, t::B
        },
        // 10
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 11
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 12
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 13
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 14
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 15
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 16
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 17
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 18
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 19
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 20
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 21
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 22
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 23
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 24
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 25
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 26
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 27
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 28
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 29
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 30
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 31
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 32
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 33
        {
            t::B, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 34
        {
            t::S, t::R, t::R, t::W, t::B, t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,   t::B,
            t::B,   t::B,   t::B,   t::W, t::P_F, t::R, t::W, t::B
        },
        // 35
        {
            t::S, t::R, t::R, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::R, t::S, t::S
        },
        // 36
        {
            t::B, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R
        },
        // 37
        {
            t::B, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R,
            t::R, t::R, t::R, t::R, t::R, t::R, t::R, t::R
        },
        // 38
        {
            t::B, t::R, t::R, t::S, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::W, t::W, t::W, t::W, t::W,
            t::W, t::W, t::W, t::S, t::S, t::W, t::W, t::W
        },
        // 39
        {
            t::B, t::R, t::R, t::S, t::B, t::B, t::B, t::B,
            t::B, t::B, t::B, t::B, t::B, t::B, t::B, t::B,
            t::B, t::B, t::B, t::B, t::B, t::B, t::B, t::B,
            t::B, t::B, t::B, t::B, t::B, t::B, t::B, t::B,
            t::B, t::B, t::B, t::B, t::B, t::B, t::B, t::B,
            t::B, t::B, t::B, t::B, t::B, t::B, t::B, t::B,
            t::B, t::B, t::B, t::B, t::B, t::B, t::B, t::B,
            t::B, t::B, t::B, t::B, t::B, t::B, t::B, t::B
        },
        // 40
        {
            t::B, t::R, t::R, t::W, t::B, t::B, t::B, t::B,
            t::B, t::B, t::B, t::B, t::B, t::B, t::B, t::B,
            t::B, t::B, t::B, t::B, t::B, t::B, t::B, t::B,
            t::B, t::B, t::B, t::B, t::B, t::B, t::B, t::B,
            t::B, t::B, t::B, t::B, t::B, t::B, t::B, t::B,
            t::B, t::B, t::B, t::B, t::B, t::B, t::B, t::B,
            t::B, t::B, t::B, t::B, t::B, t::B, t::B, t::B,
            t::B, t::B, t::B, t::B, t::B, t::B, t::B, t::B,
        },
    };
};