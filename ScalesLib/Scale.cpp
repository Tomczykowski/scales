#include "Scale.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

Scale::Scale(double weight, string const& unit) {
    if ( toGramsMap.find(unit) == toGramsMap.end() ) {
        throw std::logic_error("cannot find this unit");
    } else {
        this->weight = weight;
        this->unit = unit;
    }
}

Scale::Scale() noexcept {
    weight = 0;
    unit = "";
}

double Scale::getWeight() const noexcept {
    return weight;
}

string Scale::getUnit() const noexcept {
    return unit;
}

void Scale::setWeight(double const& weight) noexcept {
    this->weight = weight;
}

void Scale::setUnit(string const& unit) noexcept {
    this->unit = unit;
}

void Scale::changeUnit(string const& conversionUnit) noexcept {
    if(conversionUnit == this->unit)
        return;
    double inGrams = this->weight * toGramsMap.find(this->unit)->second;
    this->weight = inGrams/toGramsMap.find(conversionUnit)->second;
    this->unit = conversionUnit;
}

double Scale::getWeightIn(string const& conversionUnit) const noexcept{
    if(conversionUnit == this->unit)
        return this->weight;
    double inGrams = this->weight * toGramsMap.find(this->unit)->second;
    return inGrams / toGramsMap.find(conversionUnit)->second;
}

void Scale::addWeight(double const& weight) noexcept {
    this->weight += weight;
}

Scale Scale::heavier(Scale const& s) const noexcept {
    if(this->weight > s.getWeightIn(this->unit))
        return Scale(this->weight, this->unit);
    else
        return Scale(s.getWeight(), s.getUnit());
}

Scale Scale::lighter(Scale const& s) const noexcept {
    if(this->weight < s.getWeightIn(this->unit))
        return Scale(this->weight, this->unit);
    else
        return Scale(s.getWeight(), s.getUnit());
}

Scale Scale::operator+(Scale const& s) const noexcept {
    Scale sum = *this;
    sum += s;
    return sum;
}

Scale Scale::operator-(Scale const& s) const noexcept {
    Scale diff = *this;
    diff -= s;
    return diff;
}

Scale Scale::operator+(double const& weight) const noexcept {
    Scale sum = *this;
    sum += weight;
    return sum;
}

Scale Scale::operator-(double const& weight) const noexcept {
    Scale diff = *this;
    diff -= weight;
    return diff;
}

void Scale::operator+=(Scale const& s) noexcept {
    this->weight += s.getWeightIn(this->unit);
}

void Scale::operator-=(Scale const& s) noexcept {
    double result = weight - s.getWeightIn(unit);
    if( result < 0)
        result = 0;
    weight = result;
}

void Scale::operator+=(double const& weight) noexcept {
    this->weight += weight;
}

void Scale::operator-=(double const& weight) noexcept {
    double result = this->weight - weight;
    if(result < 0)
        result = 0;
    this->weight = result;
}

bool Scale::operator==(Scale const& s) const noexcept {
    double my_grams = this->getWeightIn("g"); // convert to grams cuz it is the smallest unit
    double his_grams = s.getWeightIn("g");
    return (abs(my_grams - his_grams) < 0.00001);
}

bool Scale::operator==(double const& weight) const noexcept {
    return(abs(this->weight - weight) < 0.00001);
}

bool Scale::operator<(Scale const& s) const noexcept {
    double my_grams = this->getWeightIn("g"); // convert to grams cuz it is the smallest unit
    double his_grams = s.getWeightIn("g");
    return (my_grams < his_grams);
}

bool Scale::operator>(Scale const& s) const noexcept {
    double my_grams = this->getWeightIn("g"); // convert to grams cuz it is the smallest unit
    double his_grams = s.getWeightIn("g");
    return (my_grams > his_grams);
}

bool Scale::operator<(double const& weight) const noexcept {
    return (this->weight < weight);
}

bool Scale::operator>(double const& weight) const noexcept {
    return (this->weight > weight);
}

ostream& operator<<(ostream& output, Scale const& s) noexcept {
    output << s.getWeight() << "[" << s.getUnit() << "]";
    return output;
}

istream& operator>>(istream &input, Scale &s) noexcept {
    double weight;
    string unit;
    cout << "Enter weight :";
    input >> weight;
    cout << "Enter unit :";
    input >> unit;
    s.setUnit(unit);
    s.setWeight(weight);
    return input;
}

bool Scale::operator==(string const& unit) const noexcept {
    return this->unit == unit;
}

void Scale::operator++(int) noexcept {
    weight++;
}

void Scale::operator--(int) noexcept {
    weight--;
}

Scale Scale::operator*(const double &weight) const noexcept {
    return Scale(this->weight * weight, this->unit );
}

Scale Scale::operator/(const double &weight) const {
    if(weight == 0){
        throw std::logic_error("Division by 0! \n");
    }
    return Scale(this->weight / weight, this->unit);
}