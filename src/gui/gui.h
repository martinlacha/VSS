#pragma once

#include "../simulation/map/map.h"
#include "../simulation/simulation.h"

namespace gui
{
    void Render_GUI();
    ImVec4 Get_Cell_Color(Map::NCell_Type cell_type);
}