#
# Tests very basic Python libcellml functionality
#
import unittest
class BasicsTestCase(unittest.TestCase):
    def test_basics(self):
        import libcellml


def suite():
    #import ImportTestCase
    tests = unittest.TestSuite()
    tests.addTests(unittest.TestLoader().loadTestsFromTestCase(BasicsTestCase))
    return tests


if __name__ == '__main__':
    unittest.TextTestRunner().run(suite())


