#
# Tests the GeneratorProfile class bindings
#
import unittest


class GeneratorProfileTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import GeneratorProfile

        x = GeneratorProfile()
        del x

    def test_generator_profile(self):
        from libcellml import GeneratorProfile

        # Create a default, i.e. C, profile.
        p = GeneratorProfile()
        self.assertEqual(GeneratorProfile.Profile.C, p.profile())

        # Make the profile a Python profile.
        p.setProfile(GeneratorProfile.Profile.PYTHON)
        self.assertEqual(GeneratorProfile.Profile.PYTHON, p.profile())

        # Create a Python profile.
        pp = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
        self.assertEqual(GeneratorProfile.Profile.PYTHON, pp.profile())


if __name__ == '__main__':
    unittest.main()
