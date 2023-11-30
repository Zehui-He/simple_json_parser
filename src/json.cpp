#include "json.h"

namespace json_parser {
    Json::Json() : m_data(nullptr) {};

    Json::Json(int data) : m_data(data) {};

    Json::Json(double data) : m_data(data) {};

    Json::Json(unsigned int data) : m_data(data) {};

    Json::Json(bool data) : m_data(data) {};

    Json::Json(std::string&& data) : m_data(std::make_unique<std::string>(std::move(data))) {};

    Json::Json(JsonArray&& data) : m_data(std::make_unique<JsonArray>(std::move(data))) {};

    Json::Json(JsonObject&& data) : m_data(std::make_unique<JsonObject>(std::move(data))) {};

    Json::Json(JsonValueType t) {
        switch (t) {
            case JsonValueType::int_t:
                m_data = 0;
                break;
            case JsonValueType::double_t:
                m_data = 0;
                break;
            case JsonValueType::unsigned_int_t:
                m_data = 0;
                break;
            case JsonValueType::bool_t:
                m_data = false;
                break;
            case JsonValueType::string_t:
                m_data = std::make_unique<std::string>(std::string());
                break;
            case JsonValueType::array_t:
                m_data = std::make_unique<JsonArray>(JsonArray());
                break;
            case JsonValueType::object_t:
                m_data = std::make_unique<JsonObject>(JsonObject());
                break;
            case JsonValueType::null_t:
                m_data = nullptr;
                break;
            default:
                throw std::runtime_error("No implemented for this type.");
        }
    };

    Json::Json(Json&& other) noexcept {
        m_data = std::move(other.m_data);
        other.m_data = nullptr;
    }

    JsonValueType Json::get_type() const {
        return static_cast<JsonValueType>(m_data.index());
    }

    std::ostream& operator<<(std::ostream& os, const Json& json) {
        switch (json.get_type()) {
            case JsonValueType::int_t:
                os << std::get<int>(json.m_data);
                break;
            case JsonValueType::double_t:
                os << std::get<double>(json.m_data);
                break;
            case JsonValueType::unsigned_int_t:
                os << std::get<unsigned int>(json.m_data);
                break;
            case JsonValueType::bool_t:
                if (std::get<bool>(json.m_data)) {
                    os << "true";
                } else {
                    os << "false";
                }
                break;
            case JsonValueType::string_t:
                os << *std::get<std::unique_ptr<std::string>>(json.m_data);
                break;
            case JsonValueType::array_t:
                os << "This is an array";
                break;
            case JsonValueType::object_t:
                os << "This is an objet";
                break;
            case JsonValueType::null_t:
                os << "null";
                break;
            default:
                throw std::runtime_error("No implemented for this type.");
        }
        return os;
    }
}
