#include "semaphore.h"

Semaphore::Semaphore(int bottom_x, int bottom_y, int top_x, int top_y, size_t count_iterations, Map& map) :
        current_state(NSemaphore_State::BLACK), iteration_to_change(count_iterations), map(map) {
    top_box = Cell(top_x, top_y);
    bottom_box = Cell(bottom_x, bottom_y);
}

void Semaphore::Change_State_To_Black() {
    current_state = NSemaphore_State::BLACK;
    Set_Map_Cell_Type(Map::NCell_Type::S,Map::NCell_Type::S);
}

void Semaphore::Change_State_To_Red() {
    current_state = NSemaphore_State::RED;
    Set_Map_Cell_Type(Map::NCell_Type::S,Map::NCell_Type::S_R);
}

void Semaphore::Change_State_to_Green() {
    current_state = NSemaphore_State::GREEN;
    Set_Map_Cell_Type(Map::NCell_Type::S_G,Map::NCell_Type::S);
}

void Semaphore::Set_Map_Cell_Type(Map::NCell_Type top_type, Map::NCell_Type bottom_type) {
    map.Set_Cell_Type(bottom_box.Get_X(), bottom_box.Get_Y(), bottom_type);
    map.Set_Cell_Type(top_box.Get_X(), top_box.Get_Y(), top_type);
}
