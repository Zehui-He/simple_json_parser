#pragma once
#include <unordered_map>
#include <string>
#include <json_fwd.h>
#include <json_value.h>

namespace json_parser {
    class Json {
    public:
        Json();

        template <typename Key, typename Value>
        void insert(Key&& key, Value&& val) {
            m_value.insert({std::forward<Key>(key), std::forward<Value>(val)});
        }

        template <typename Key>
        JsonValue& get(Key key) {
            return m_value.at(std::forward<Key>(key));
        }

        template <typename Key>
        JsonValue const& read(Key key) const {
            return m_value.at(std::forward<Key>(key));
        }

        size_t size() const {
            return m_value.size();
        }
        
        friend std::ostream& operator<<(std::ostream& os, const Json& json);

    private:
        std::unordered_map<std::string, JsonValue> m_value;
    }; // Json struct 
} // namespace json_parser
