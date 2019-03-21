#include "my_json.h"

my_json::my_json()
{}

int my_json::serialize(Json::Value &_in_val, std::string &_str_out)
{
#ifdef _STYLE_
    Json::StyledWriter _write;
#else
    Json::FastWriter _write;
#endif
    _str_out = _write.write(_in_val);
}

int my_json::deserialize(std::string &_in_str, Json::Value &_val_out)
{
    Json::Reader _reader;
    if(_reader.parse(_in_str, _val_out, false)){
        return 0;
    }else{
        return 1;
    }
}

my_json::~my_json()
{}
