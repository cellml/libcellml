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
        self.assertIsNone(x.issue(0))
        # self.assertIsNone(x.issue(-1))  # TODO Removed as negatives are not allowed as indices ... do they need to be ints intead of size_t?
        self.assertEqual(x.issueCount(), 0)
        x.addIssue(libcellml.Issue())
        self.assertEqual(x.issueCount(), 1)

    def test_validate_model(self):
        import libcellml
        from libcellml import Validator

        # void validateModel(const ModelPtr &model)
        v = Validator()
        v.validateModel(libcellml.Model())


if __name__ == '__main__':
    unittest.main()
