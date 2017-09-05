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

%include <std_string.i>

%module cellml
%{
#include <libcellml>
%}

#define PI 3.14159;

namespace libcellml {

class Units {
public:
    // Constructors
    Units();
    ~Units();
    Units(const Units &);
    //@TODO Move constructor
    //@TODO Assignment operator

    // Default units
    enum class StandardUnit {
        AMPERE,
        BECQUEREL,
        CANDELA,
        COULOMB,
        DIMENSIONLESS,
        FARAD,
        GRAM,
        GRAY,
        HENRY,
        HERTZ,
        JOULE,
        KATAL,
        KELVIN,
        KILOGRAM,
        LITER,
        LITRE,
        LUMEN,
        LUX,
        METER,
        METRE,
        MOLE,
        NEWTON,
        OHM,
        PASCAL,
        RADIAN,
        SECOND,
        SIEMENS,
        SIEVERT,
        STERADIAN,
        TESLA,
        VOLT,
        WATT,
        WEBER
    };
    
    // Test if a base unit
    bool isBaseUnit();
    
    // Show number of units in this base
    int unitCount();
    
    // Add units
    // Note: order of overloads is important!
    // See: http://swig.org/Doc1.3/SWIGPlus.html#SWIGPlus_overloaded_methods
    
    void addUnit(const std::string &, const std::string &, double, double);
};

class Model {
public:
  Model();
  ~Model();
  
  void removeAllUnits();
};

}
