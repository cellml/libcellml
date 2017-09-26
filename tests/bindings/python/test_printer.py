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
        x = Printer(libcellml.Format.XML)
        del(x)
        y = Printer(libcellml.Format.XML)
        z = Printer(y)
        del(y, z)
        
        # Test inheritance
        x = Printer(libcellml.Format.XML)
        self.assertIsInstance(x, libcellml.Logger)

        # Test access to inherited methods
        idx = 'test'
        self.assertIsNone(x.getError(0))
        self.assertIsNone(x.getError(-1))
        self.assertEqual(x.errorCount(), 0)
        x.addError(libcellml.Error())
        self.assertEqual(x.errorCount(), 1)
        del(x, idx)
        
        # Test own methods
        
        # std::string printModel(ModelPtr model)
        p = Printer(libcellml.Format.XML)
        self.assertIsInstance(p.printModel(libcellml.Model()), str)
        del(p)

        # std::string printModel(Model model)
        # This method shadows printModel(ModelPtr) so wasn't added

        # std::string printModel(Model *model)
        # This method shadows printModel(ModelPtr) so wasn't added

        # std::string printUnits(UnitsPtr units)
        p = Printer(libcellml.Format.XML)
        self.assertIsInstance(p.printUnits(libcellml.Units()), str)
        del(p)

        # std::string printUnits(Units units)
        # This method shadows printUnits(UnitsPtr) so wasn't added

        # std::string printVariable(VariablePtr variable)\
        p = Printer(libcellml.Format.XML)
        self.assertIsInstance(p.printVariable(libcellml.Variable()), str)
        del(p)

        # This method shadows printVariable(VariablePtr) so wasn't added
        # std::string printVariable(Variable variable)

        # std::string printComponent(ComponentPtr component)
        p = Printer(libcellml.Format.XML)
        self.assertIsInstance(p.printComponent(libcellml.Component()), str)
        del(p)

        # This method shadows printComponent(ComponentPtr) so wasn't added
        # std::string printComponent(Component component)

if __name__ == '__main__':
    unittest.main()
