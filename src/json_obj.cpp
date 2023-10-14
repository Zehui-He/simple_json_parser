#include "json_obj.h"

JsonObj::Iterator JsonObj::begin() {
    return data_.begin();
}

JsonObj::Iterator JsonObj::end() {
    return data_.end();
}
