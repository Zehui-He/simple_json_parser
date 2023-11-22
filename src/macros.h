#pragma once 

#define CONSTRUCT_WITH_DATA(Datatype) JsonValue::JsonValue(Datatype data) { this->data = data; }
