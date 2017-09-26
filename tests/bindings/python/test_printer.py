#
# Tests the Printer class bindings
#
import sys
import unittest

class PrinterTestCase(unittest.TestCase):

    def test_printer(self):
        import libcellml
        from libcellml import Printer
        
        # Test create/copy/destroy
        #x = Printer()
        #del(x)
        #y = Printer()
        #z = Printer(y)
        #del(y,z)
        
        # Test methods
        #TODO
        
        # std::string printModel(ModelPtr model)

        # std::string printModel(Model model)

        # std::string printModel(Model *model)

        # std::string printUnits(UnitsPtr units)

        # std::string printUnits(Units units)

        # std::string printVariable(VariablePtr variable)

        # std::string printVariable(Variable variable)

        # std::string printComponent(ComponentPtr component)

        # std::string printComponent(Component component)

if __name__ == '__main__':
    unittest.main()
