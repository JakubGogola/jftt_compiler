#include <string>
#include <vector>
#include <map>

#include "data.hpp"
#include "defs.hpp"

data::data() {
    this->mem_offset = 0;
    this->code_offset = 0;
    this->next_label = 0;
}