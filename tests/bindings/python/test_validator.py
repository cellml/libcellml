#
# Tests the Validator class bindings
#
import unittest


class ValidatorTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Validator

        x = Validator()
        del(x)
        y = Validator()
        z = Validator(y)
        del(y, z)

    def test_inheritance(self):
        import libcellml
        from libcellml import Validator

        # Test inheritance
        x = Validator()
        self.assertIsInstance(x, libcellml.Logger)

        # Test access to inherited methods
        self.assertIsNone(x.error(0))
        self.assertIsNone(x.error(-1))
        self.assertEqual(x.errorCount(), 0)
        x.addError(libcellml.Error())
        self.assertEqual(x.errorCount(), 1)

    def test_validate_model(self):
        import libcellml
        from libcellml import Validator

        # void validateModel(const ModelPtr &model)
        v = Validator()
        v.validateModel(libcellml.Model())


if __name__ == '__main__':
    unittest.main()
