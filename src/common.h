
/*
Copyright libCellML Contributors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#pragma once

#include <map>
#include <vector>

namespace libcellml {

/**
* Vector of base units. NB not const as added to if need be by user-defined units
*/
std::vector<std::string> baseUnitsList = {
    "ampere",
    "candela", 
    "dimensionless", 
    "kelvin",
    "kilogram",
    "metre",
    "mole", 
    "second", 
};

/**
*  Map connecting standard built-in units to their base unit components and their exponents.
*
*/
const std::map< std::string, std::map<std::string, double> > standardUnitsList = {
    {"ampere", {{"ampere",1.0}}},
    {"candela", {{"candela",1.0}}},
    {"dimensionless", {{"dimensionless",1.0}}},
    {"kelvin", {{"kelvin",1.0}}},
    {"kilogram", {{"kilogram",1.0}}},
    {"metre", {{"metre",1.0}}},
    {"mole", {{"mole",1.0}}},
    {"second", {{"second",1.0}}}, 
    {"becquerel", {{"second",-1.0}}},
    {"coulomb", {
        {"ampere",-1.0},
        {"second",1.0}}},
    {"farad", {
        {"ampere",2.0},
        {"kilogram",-1.0},
        {"metre",-2.0},
        {"second",-4.0}}},
    {"gram", {{"kilogram",1.0}}},
    {"gray", {
        {"metre",2.0},
        {"second",-2.0}}},
    {"henry", {
        {"ampere",-2.0},
        {"kilogram",1.0},
        {"metre",2.0},
        {"second",-2.0}}},
    {"hertz", {{"second",-1.0}}},
    {"joule", {
        {"kilogram",1.0},
        {"metre",2.0},
        {"second",-2.0}}},
    {"katal", {
        {"mole",1.0},
        {"second",-1.0}}},
    {"liter", {{"metre",3.0}}},
    {"litre", {{"metre",3.0}}},
    {"lumen", {{"candela",1.0}}},
    {"lux", {
        {"candela",1.0},
        {"metre",-2.0}}}, 
    {"meter", {{"metre",1.0}}},
    {"newton", {
        {"kilogram",1.0},
        {"metre",1.0},
        {"second",-2.0}}},
    {"ohm", {
        {"ampere",-2.0},
        {"kilogram",1.0},
        {"metre",2.0},
        {"second",-3.0}}},
    {"pascal", {
        {"kilogram",1.0},
        {"metre",-1.0},
        {"second",-2.0}}},
    {"radian", {{"dimensionless",1.0}}},
    {"siemens", {
        {"ampere",2.0},
        {"kilogram",-1.0},
        {"metre",-2.0},
        {"second",3.0}}},
    {"sievert", {
        {"metre",2.0},
        {"second",-2.0}}},
    {"steradian", {{"dimensionless",1.0}}},
    {"tesla", {
        {"ampere",-1.0},
        {"kilogram",1.0},
        {"second",-2.0}}},
    {"volt", {
        {"ampere",-1.0},
        {"kilogram",1.0},
        {"metre",2.0},
        {"second",-3.0}}},
    {"watt", {
        {"kilogram",1.0},
        {"metre",2.0},
        {"second",-3.0}}},
    {"weber", {
        {"ampere",-1.0},
        {"kilogram",1.0},
        {"metre",2.0},
        {"second",-2.0}}},
};

/**
* Map connecting standard built-in units to the multiplier exponent of their base unit components.
*/
const std::map<std::string, double> standardMultiplierList = {
    {"ampere",0.0},
    {"candela",0.0},
    {"dimensionless",0.0},
    {"kelvin",0.0},
    {"kilogram",0.0},
    {"metre",0.0},
    {"mole",0.0},
    {"second",0.0},

    {"becquerel",0.0},
    {"coulomb",0.0},
    {"farad",0.0},
    {"gram",-3.0},
    {"gray",0.0},
    {"henry",0.0},
    {"hertz",0.0},
    {"joule",0.0},
    {"katal",0.0},
    {"liter",-3.0},
    {"litre",-3.0},
    {"lumen",0.0},
    {"lux",0.0},
    {"meter",0.0},
    {"newton",0.0},
    {"ohm",0.0},
    {"pascal",0.0},
    {"radian",0.0},
    {"siemens",0.0},
    {"sievert",0.0},
    {"steradian",0.0},
    {"tesla",0.0},
    {"volt",0.0},
    {"watt",0.0},
    {"weber",0.0} 
};

/**
* Map connecting prefix strings to their exponent (eg: "kilo"-> 10^3)
*/
const std::map<std::string, int> standardPrefixList = {
    {"yotta",24},
    {"zetta",21},
    {"exa",18},
    {"peta",15},
    {"tera",12},
    {"giga",9},
    {"mega",6},
    {"kilo",3},
    {"hecto",2},
    {"deca",1},
    {"deka",1}, // TODO included here for now - will both be supported in the future?
    {"deci",-1},
    {"centi",-2},
    {"milli",-3},
    {"micro",-6},
    {"nano",-9},
    {"pico",-12},
    {"femto",-15},
    {"atto",-18},
    {"zepto",-21},
    {"yocto",-24},
    {"",0},
    {"-24",-24}, // TODO Used to set these programmatically but can't do that in .h file?
    {"-23",-23},
    {"-22",-22},
    {"-21",-21},
    {"-20",-20},
    {"-19",-19},
    {"-18",-18},
    {"-17",-17},
    {"-16",-16},
    {"-15",-15},
    {"-14",-14},
    {"-13",-13},
    {"-12",-12},
    {"-11",-11},
    {"-10",-10},
    {"-9",-9},
    {"-8",-8},
    {"-7",-7},
    {"-6",-6},
    {"-5",-5},
    {"-4",-4},
    {"-3",-3},
    {"-2",-2},
    {"-1",-1},
    {"0",0},
    {"1",1},
    {"2",2},
    {"3",3},
    {"4",4},
    {"5",5},
    {"6",6},
    {"7",7},
    {"8",8},
    {"9",9},
    {"10",10},
    {"11",11},
    {"12",12},
    {"13",13},
    {"14",14},
    {"15",15},
    {"16",16},
    {"17",17},
    {"18",18},
    {"19",19},
    {"20",20},
    {"21",21},
    {"22",22},
    {"23",23},
    {"24",24},
};

/*
* List of mathml elements which are supported TODO need to pass to other checkers?
*/
const std::vector<std::string> supportedMathMLElements = {
    "ci", "cn", "sep", "apply", "piecewise", "piece", "otherwise", "eq", "neq", "gt", "lt", "geq", "leq", "and", "or",
    "xor", "not", "plus", "minus", "times", "divide", "power", "root", "abs", "exp", "ln", "log", "floor",
    "ceiling", "min", "max", "rem", "diff", "bvar", "logbase", "degree", "sin", "cos", "tan", "sec", "csc",
    "cot", "sinh", "cosh", "tanh", "sech", "csch", "coth", "arcsin", "arccos", "arctan", "arcsec", "arccsc",
    "arccot", "arcsinh", "arccosh", "arctanh", "arcsech", "arccsch", "arccoth", "pi", "exponentiale",
    "notanumber", "infinity", "true", "false"
};

}
