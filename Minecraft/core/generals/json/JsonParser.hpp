//
//  JsonParser.hpp
//  CarMapping
//
//  Created by Shun Sato on 8/6/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef JsonParser_hpp
#define JsonParser_hpp

#include <string>
#include <vector>

#include "picojson.h"

namespace JsonParser{
    template <typename T> T get(const picojson::object& jsonObject, const std::string& key, const T& valueToReturnOnFailed);
    
    /**
     * JSONObjectから指定したキーの値を取得
     * 対応型: std::string, double, picojson::object, picojson::array
     * @param jsonString 元のJSONObject
     * @param key キー
     * @param valueToReturnOnFailed 失敗した際に返す値
     * @return value
     */
    template <typename T> T get(const std::string& jsonString, const std::string& key, const T& valueToReturnOnFailed);
    
    /**
     * stringをjson形式に変換
     * 対応型: picojson::object, picojson::array
     * @param jsonString 元のJSONObject
     * @param valueToReturnOnFailed 失敗した際に返す値
     * @return object or array
     */
    template <typename T> T to(const std::string& jsonString, const T& valueToReturnOnFailed);
}


#endif /* JsonParser_hpp */
