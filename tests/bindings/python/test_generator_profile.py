#
# Tests the GeneratorProfile class bindings
#
import unittest


class GeneratorProfileTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import GeneratorProfile

        x = GeneratorProfile()
        del x

    def test_profile(self):
        from libcellml import GeneratorProfile

        p = GeneratorProfile()
        self.assertEqual(GeneratorProfile.Profile.C, p.profile())

        p.setProfile(GeneratorProfile.Profile.PYTHON)
        self.assertEqual(GeneratorProfile.Profile.PYTHON, p.profile())

    def test_has_interface(self):
        from libcellml import GeneratorProfile

        p = GeneratorProfile()

        self.assertTrue(p.hasInterface())

        p.setHasInterface(False)
        self.assertFalse(p.hasInterface())


if __name__ == '__main__':
    unittest.main()
