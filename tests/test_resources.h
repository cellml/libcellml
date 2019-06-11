
#pragma once

class TestResources
{

public:

    enum ResourcesName
    {
        CELLML_INVALID_MODEL_RESOURCE = 1,
        CELLML_SINE_MODEL_RESOURCE = 2,
        CELLML_SINE_IMPORTS_MODEL_RESOURCE = 3,
        CELLML_ORD_MODEL_RESOURCE = 4,
        CELLML_COMPLEX_ENCAPSULATION_MODEL_RESOURCE = 5,
        CELLML_A_PLUS_B_MODEL_RESOURCE = 6,
        CELLML_COMPLEX_IMPORTS_MODEL_RESOURCE = 7,
        CELLML_UNITS_DEFINITIONS_RESOURCE = 8,
        CELLML_UNITS_IMPORT_MODEL_RESOURCE = 9,
        CELLML_IMPORT_LEVEL0_MODEL_RESOURCE = 10,
        CELLML_IMPORT_LEVEL0_UNRESOLVABLE_MODEL_RESOURCE = 11
    };

    TestResources()
    {  }

    ~TestResources()
    {  }

    static const char *getLocation(ResourcesName resourceName)
    {
        if (resourceName == TestResources::CELLML_SINE_MODEL_RESOURCE)
        {
            return "/Users/kmoy001/libCellML/tests/resources/sine_approximations.xml";
        }
        if (resourceName == TestResources::CELLML_SINE_IMPORTS_MODEL_RESOURCE)
        {
            return "/Users/kmoy001/libCellML/tests/resources/sine_approximations_import.xml";
        }
        if (resourceName == TestResources::CELLML_COMPLEX_IMPORTS_MODEL_RESOURCE)
        {
            return "/Users/kmoy001/libCellML/tests/resources/complex_imports.xml";
        }
        if (resourceName == TestResources::CELLML_COMPLEX_ENCAPSULATION_MODEL_RESOURCE)
        {
            return "/Users/kmoy001/libCellML/tests/resources/complex_encapsulation.xml";
        }
        if (resourceName == TestResources::CELLML_INVALID_MODEL_RESOURCE)
        {
            return "/Users/kmoy001/libCellML/tests/resources/invalid_cellml_2.0.xml";
        }
        if (resourceName == TestResources::CELLML_ORD_MODEL_RESOURCE)
        {
            return "/Users/kmoy001/libCellML/tests/resources/Ohara_Rudy_2011.cellml";
        }
        if (resourceName == TestResources::CELLML_A_PLUS_B_MODEL_RESOURCE)
        {
            return "/Users/kmoy001/libCellML/tests/resources/a_plus_b.cellml";
        }
        if (resourceName == TestResources::CELLML_UNITS_DEFINITIONS_RESOURCE)
        {
            return "/Users/kmoy001/libCellML/tests/resources/units_definitions.cellml";
        }
        if (resourceName == TestResources::CELLML_UNITS_IMPORT_MODEL_RESOURCE)
        {
            return "/Users/kmoy001/libCellML/tests/resources/import_units_model.cellml";
        }
        if (resourceName == TestResources::CELLML_UNITS_IMPORT_MODEL_RESOURCE)
        {
            return "/Users/kmoy001/libCellML/tests/resources/import_units_model.cellml";
        }
        if (resourceName == TestResources::CELLML_IMPORT_LEVEL0_MODEL_RESOURCE)
        {
            return "/Users/kmoy001/libCellML/tests/resources/level0.xml";
        }
        if (resourceName == TestResources::CELLML_IMPORT_LEVEL0_UNRESOLVABLE_MODEL_RESOURCE)
        {
            return "/Users/kmoy001/libCellML/tests/resources/level0-broken-imports.xml";
        }
        return nullptr;
    }
};
