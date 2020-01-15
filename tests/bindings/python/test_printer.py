#
# Tests the Printer class bindings
#
import unittest


class PrinterTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Printer

        x = Printer()
        del(x)

    def test_inheritance(self):
        import libcellml
        from libcellml import Printer

        x = Printer()
        self.assertIsInstance(x, libcellml.logger.Logger)

        # Test access to inherited methods
        self.assertIsNone(x.error(0))
        self.assertIsNone(x.error(-1))
        self.assertEqual(x.errorCount(), 0)
        x.addError(libcellml.Issue())
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


if __name__ == '__main__':
    unittest.main()
