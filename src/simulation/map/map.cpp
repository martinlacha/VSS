#include "map.h"

 Map::NCell_Type* Map::Get_Map()
 {
    NCell_Type* map_ptr = &map[0][0];
    return map_ptr;
}

int Map::Get_Map_Height() const noexcept {
    return map_height;
}

int Map::Get_Map_Width() const noexcept {
    return map_width;
}

Map::NCell_Type Map::Get_Cell_Type(size_t x, size_t y) const {
    return map[x][y];
}

void Map::Set_Cell_Type(size_t x, size_t y, Map::NCell_Type new_type) {
    map[x][y] = new_type;
}