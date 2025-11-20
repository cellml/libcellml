#
# Tests the GeneratorContext class bindings
#
import unittest


class GeneratorContextTestCase(unittest.TestCase):
    def test_create_destroy(self):
        from libcellml import GeneratorContext

        x = GeneratorContext()
        del x


if __name__ == '__main__':
    unittest.main()
