#
# Tests the Error class bindings
#
import sys
import unittest

class ErrorTestCase(unittest.TestCase):

    def test_error(self):
        import libcellml
        from libcellml import Error
        
        # Test create/copy/destroy
        x = Error()
        del(x)
        y = Error()
        z = Error(y)
        del(y,z)
        
        # Test Kind enum
        #TODO
        '''
        COMPONENT,
        CONNECTION,
        ENCAPSULATION,
        IMPORT,
        MATHML,
        MODEL,
        UNDEFINED,
        UNITS,
        VARIABLE,
        XML
        '''
  
        # Test methods
        #TODO
        
        # void setDescription(const std::string& description)

        # std::string getDescription()

        # void setKind(Kind kind)

        # Kind getKind()

        # bool isKind(const Kind &kind)

        # void setRule(SpecificationRule rule)

        # SpecificationRule getRule()

        # std::string getSpecificationHeading()

        # void setComponent(const ComponentPtr &component)

        # ComponentPtr getComponent()

        # void setImport(const ImportPtr &import)

        # ImportPtr getImport()

        # void setModel(const ModelPtr &model)

        # ModelPtr getModel()

        # void setUnits(const UnitsPtr &units)
        
        # UnitsPtr getUnits()

        # void setVariable(const VariablePtr &variable)

        # VariablePtr getVariable()

if __name__ == '__main__':
    unittest.main()
