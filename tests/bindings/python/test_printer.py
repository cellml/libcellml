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
        '''
        x = Printer()
        del(x)
        y = Printer()
        z = Printer(y)
        del(y, z)
        
        # Test inheritance
        x = Printer()
        self.assertIsInstance(x, libcellml.Logger)

        # Test access to inherited methods
        idx = 'test'
        self.assertIsNone(x.getError(0))
        self.assertEqual(x.errorCount(), 0)
        x.addError(libcellml.Error())
        self.assertEqual(x.errorCount(), 1)
        del(x, idx)
        '''
        
        # Test own methods
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
