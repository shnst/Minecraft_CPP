//
//  JsonParser.cpp
//  CarMapping
//
//  Created by Shun Sato on 8/6/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "JsonParser.hpp"
#include "picojson.h"

template<typename T>
T JsonParser::get(const std::string& jsonString, const std::string& key, const T& valueToReturnOnFailed){
    picojson::value v;
    std::string err;
    picojson::parse(v, jsonString.begin(), jsonString.end(), &err);
    
    if (err.empty() && v.is<picojson::object>())
    {
        picojson::object& o = v.get<picojson::object>();
        if(o.find(key.c_str()) == o.end()){
            std::cout << "JsonParser::Get not found key:" << key << std::endl;
            return valueToReturnOnFailed;
        }
        if(!o[key.c_str()].is<T>()){
            std::cout << "JsonParser::Get type is not matched key:" << key << std::endl;
            return valueToReturnOnFailed;
        }
        return o[key.c_str()].get<T>();
    }
    
    std::cout << "JsonParser::Get invalid jsonString error:" << err << std::endl;
    return valueToReturnOnFailed;
}
/**
 * 現状対応している型
 */
template std::string JsonParser::get<std::string>(const std::string& jsonString, const std::string& key, const std::string& valueToReturnOnFailed);
template double JsonParser::get<double>(const std::string& jsonString, const std::string& key, const double& valueToReturnOnFailed);
template picojson::array JsonParser::get<picojson::array>(const std::string& jsonString, const std::string& key, const picojson::array& valueToReturnOnFailed);
template picojson::object JsonParser::get<picojson::object>(const std::string& jsonString, const std::string& key, const picojson::object& valueToReturnOnFailed);


template<typename T>
T JsonParser::to(const std::string& jsonString, const T& valueToReturnOnFailed){
    picojson::value v;
    std::string err;
    picojson::parse(v, jsonString.begin(), jsonString.end(), &err);
    if (err.empty() && v.is<T>())
    {
        return v.get<T>();
    }
    std::cout << "JsonParser::To invalid jsonString error:" << err << std::endl;
    return valueToReturnOnFailed;
}
template picojson::array JsonParser::to<picojson::array>(const std::string& jsonString, const picojson::array& valueToReturnOnFailed);
template picojson::object JsonParser::to<picojson::object>(const std::string& jsonString, const picojson::object& valueToReturnOnFailed);
