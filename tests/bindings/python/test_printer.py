#
# Tests the Printer class bindings
#
import unittest


class PrinterTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Printer

        x = Printer()
        del(x)
        y = Printer()
        z = Printer(y)
        del(y, z)

    def test_inheritance(self):
        import libcellml
        from libcellml import Printer

        x = Printer()
        self.assertIsInstance(x, libcellml.Logger)

        # Test access to inherited methods
        self.assertIsNone(x.error(0))
        self.assertIsNone(x.error(-1))
        self.assertEqual(x.errorCount(), 0)
        x.addError(libcellml.Error())
        self.assertEqual(x.errorCount(), 1)

    def test_print_model(self):
        from libcellml import Printer, Model

        # std::string printModel(ModelPtr model)
        p = Printer()
        self.assertIsInstance(p.printModel(Model()), str)

        # std::string printModel(Model model)
        # This method shadows printModel(ModelPtr) so wasn't added

        # std::string printModel(Model *model)
        # This method shadows printModel(ModelPtr) so wasn't added

    def test_print_units(self):
        from libcellml import Printer, Units

        # std::string printUnits(UnitsPtr units)
        p = Printer()
        self.assertIsInstance(p.printUnits(Units()), str)

        # std::string printUnits(Units units)
        # This method shadows printUnits(UnitsPtr) so wasn't added

    def test_print_variable(self):
        from libcellml import Printer, Variable

        # std::string printVariable(VariablePtr variable)\
        p = Printer()
        self.assertIsInstance(p.printVariable(Variable()), str)

        # This method shadows printVariable(VariablePtr) so wasn't added
        # std::string printVariable(Variable variable)

    def test_print_component(self):
        from libcellml import Printer, Component

        # std::string printComponent(ComponentPtr component)
        p = Printer()
        self.assertIsInstance(p.printComponent(Component()), str)

        # This method shadows printComponent(ComponentPtr) so wasn't added
        # std::string printComponent(Component component)

    def test_print_reset(self):
        from libcellml import Printer, Reset

        # std::string printReset(ResetPtr reset) const;
        p = Printer()
        self.assertIsInstance(p.printReset(Reset()), str)

        # This method shadows printReset(ResetPtr) so wasn't added
        # std::string printReset(Reset reset) const;


if __name__ == '__main__':
    unittest.main()
