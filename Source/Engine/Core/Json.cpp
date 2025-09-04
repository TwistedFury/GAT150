#include "Json.h"
#include "File.h"
#include "Logger.h"

#include <rapidjson/istreamwrapper.h>
#include <iostream>

namespace swaws::json
{
    bool Load(const std::string& filename, document_t& document) {
        // read the file into a string
        std::string buffer;
        if (!file::ReadTextFile(filename, buffer)) {
            Logger::Error("Could not read file: {}.", filename);
            return false;
        }

        // convert the string into a json stream
        std::stringstream stream(buffer);
        rapidjson::IStreamWrapper istream(stream);

        // set the json document from the stream
        document.ParseStream(istream);
        // check if the parse was successful
        if (!document.IsObject()) {
            Logger::Error("Could not parse Json: {}.", filename);
            return false;
        }

        return true;
    }

    bool Read(const value_t& value, const std::string& name, int& data, bool required) {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt()) {
            if (required) Logger::Error("Could not read Json value (int): {}.", name);
            return false;
        }

        // get the data
        data = value[name.c_str()].GetInt();

        return true;
    }

    bool Read(const value_t& value, const std::string& name, float& data, bool required) {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsNumber()) {
            if (required) Logger::Error("Could not read Json value (float): {}.", name);
            return false;
        }

        // get the data
        data = value[name.c_str()].GetFloat();

        return true;
    }

    bool Read(const value_t& value, const std::string& name, bool& data, bool required) {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool()) {
            if (required) Logger::Error("Could not read Json value (bool): {}.", name);
            return false;
        }

        // get the data
        data = value[name.c_str()].GetBool();

        return true;
    }

    bool Read(const value_t& value, const std::string& name, std::string& data, bool required) {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString()) {
            if (required) Logger::Error("Could not read Json value (string): {}.", name);
            return false;
        }

        // get the data
        data = value[name.c_str()].GetString();

        return true;
    }

    bool Read(const value_t& value, const std::string& name, vec2& data, bool required) {
        // check if the value has the "<name>" and is an array with 2 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2) {
            if (required) Logger::Error("Could not read Json value (vec2): {}.", name);
            return false;
        }

        // get json array object
        auto& array = value[name.c_str()];
        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++) {
            if (!array[i].IsNumber()) {
                Logger::Error("Could not read Json value: {}.", name);
                return false;
            }
            i == 0 ? data.x = array[i].GetFloat() : data.y = array[i].GetFloat();
        }

        return true;
    }

    bool Read(const value_t& value, const std::string& name, vec3& data, bool required) {
        // check if the value has the "<name>" and is an array with 2 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 3) {
            if (required) Logger::Error("Could not read Json value (vec3): {}.", name);
            return false;
        }

        // get json array object
        auto& array = value[name.c_str()];
        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++) {
            if (!array[i].IsNumber()) {
                Logger::Error("Could not read Json value: {}.", name);
                return false;
            }
            i == 0 ? data.r = array[i].GetFloat() : i == 1 ? data.g = array[i].GetFloat() : data.b = array[i].GetFloat();
        }

        return true;
    }

    bool Read(const value_t& value, const std::string& name, std::vector<int>& data, bool required)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray()) {
            if (required) Logger::Error("Could not read Json value (std::vector<int>): {}.", name);
            return false;
        }
        auto& array = value[name.c_str()];
        data.reserve(data.size() + array.Size());
        for (rapidjson::SizeType i = 0; i < array.Size(); i++) {
            const auto& v = array[i];
            if (v.IsInt()) {
                data.push_back(v.GetInt());
            } else if (v.IsUint()) {
                unsigned ui = v.GetUint();
                if (ui <= static_cast<unsigned>(std::numeric_limits<int>::max())) {
                    data.push_back(static_cast<int>(ui));
                } else {
                    Logger::Error("Value out of int range in array {}[{}]", name, i);
                    return false;
                }
            } else {
                Logger::Error("Could not read Json value (int array element type) {}[{}]", name, i);
                return false;
            }
        }
        return true;
    }

    bool Read(const value_t& value, const std::string& name, std::vector<uint32_t>& data, bool required)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray()) {
            if (required) Logger::Error("Could not read Json value (std::vector<uint32_t>): {}.", name);
            return false;
        }
        auto& array = value[name.c_str()];
        data.reserve(data.size() + array.Size());
        for (rapidjson::SizeType i = 0; i < array.Size(); i++) {
            const auto& v = array[i];
            if (!(v.IsUint() || v.IsUint64() || v.IsInt() || v.IsInt64())) {
                Logger::Error("Non-integer numeric in {}[{}]", name, i);
                return false;
            }
            uint64_t raw = v.IsUint64() ? v.GetUint64() :
                           v.IsInt64()  ? static_cast<uint64_t>(v.GetInt64()) :
                           v.IsUint()   ? v.GetUint() :
                                          static_cast<uint64_t>(v.GetInt());
            if (raw > std::numeric_limits<uint32_t>::max()) {
                Logger::Error("Value out of uint32 range in {}[{}]", name, i);
                return false;
            }
            data.push_back(static_cast<uint32_t>(raw));
        }
        return true;
    }
}