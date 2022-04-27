#pragma once

#include <string>
#include <vector>

class Element
{
public:
    Element(bool is_combo = true);
    Element(std::string name, bool is_folder = true);
    bool get_is_folder() const;
    std::string &get_name();
    bool get_is_combo() const;
    std::vector<Element> &get_combo_elements_();
    void set_name(std::string name);

private:
    bool is_folder_;
    std::string name_;
    bool is_combo_;
    std::vector<Element> combo_elements_;
};