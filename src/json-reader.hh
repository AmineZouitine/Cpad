#include "singleton.hh"

template<typename TargetClass>
class JsonReader : public Singleton<JsonReader>
{
public:
    TargetClass& readJson(string path);
    void saveToJson(string path, TargetClass& currentObject);
};