#include <iomanip>
#include <map>
#include <string>

#ifndef PROI_ZAD2_WOJCIECHSEKULACZW16_SCALES_H
#define PROI_ZAD2_WOJCIECHSEKULACZW16_SCALES_H

using namespace std;

const std::map<string, double> toGramsMap{
        {"mg", 0.001},
        {"dag", 10.0},
        {"kg", 1000.0},
        {"lb", 453.5923},
        {"oz", 28.3495},
        {"cwt", 50802.3454},
        {"g", 1.0}
};

class Scale
{
private:
    double weight;
    string unit;
public:
    Scale(double weight, string const& unit);
    Scale() noexcept;
    double getWeight() const noexcept;
    string getUnit() const noexcept;
    void setWeight(double const& weight) noexcept;
    void setUnit(string const& unit) noexcept;
    void changeUnit(string const& conversionUnit) noexcept; // changes object unit to given unit (with weight of mass)
    double getWeightIn(string const& conversionUnit) const noexcept;
    void addWeight(double const& weight) noexcept;
    
    Scale heavier(Scale const& s) const noexcept; // returns heavier object
    Scale lighter(Scale const& s) const noexcept; // returns lighter object

    Scale operator+(Scale const& s) const noexcept; // returns Scale object with unit of object on which method is run
    Scale operator-(Scale const& s) const noexcept; // returns Scale object with unit of object on which method is run
    Scale operator+(double const& weight) const noexcept; // I assume that given weight is in objects unit
    Scale operator-(double const& weight) const noexcept; // I assume that given weight is in objects unit
    Scale operator*(double const& weight) const noexcept;
    Scale operator/(double const& weight) const;

    void operator+=(Scale const& s) noexcept; // ads weight in objects unit
    void operator-=(Scale const& s) noexcept; // ads weight in objects unit
    void operator+=(double const& weight) noexcept; // I assume that given weight is in objects unit
    void operator-=(double const& weight) noexcept; // I assume that given weight is in objects unit
    void operator++(int) noexcept;
    void operator--(int) noexcept;

    bool operator==(Scale const& s) const noexcept; // return true if weights are even in grams
    bool operator==(double const& weight) const noexcept;
    bool operator==(string const& unit) const noexcept;

    bool operator<(Scale const& s) const noexcept;
    bool operator>(Scale const& s) const noexcept;

    bool operator<(double const& weight) const noexcept; // I assume that given weight is in objects unit
    bool operator>(double const& weight) const noexcept; // I assume that given weight is in objects unit

};

ostream & operator<<(ostream& output, Scale const& s) noexcept;
istream & operator>>(istream& input, Scale & s) noexcept;

#endif //PROI_ZAD2_WOJCIECHSEKULACZW16_SCALES_H
