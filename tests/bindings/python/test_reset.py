#
# Tests the bindings for OrderedEntity, which is the base class for all
# entities that can be ordered relative to one another.
#
import unittest


class OrderedEntityTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Reset

        x = Reset()
        y = Reset()
        z = Reset(y)
        del(x, y, z)

    def test_set_get_variable(self):
        from libcellml import Reset
        from libcellml import Variable

        r = Reset()
        v = Variable()
        v.setName("glucose")

        self.assertEqual(None, r.getVariable())

        r.setVariable(v)

        self.assertEqual("glucose", r.getVariable().getName())

    def test_add_when(self):
        from libcellml import Reset
        from libcellml import When

        # addWhen()
        w = When()
        x = Reset()
        x.addWhen(w)
        self.assertEqual(1, x.whenCount())

    def test_remove_when(self):
        from libcellml import Reset
        from libcellml import When

        w = When()
        r = Reset()

        r.addWhen(w)

        self.assertEqual(1, r.whenCount())

        self.assertTrue(r.removeWhen(0))
        self.assertEqual(0, r.whenCount())

        r.addWhen(w)

        self.assertTrue(r.removeWhen(w))
        self.assertEqual(0, r.whenCount())

    def test_remove_all_whens(self):
        from libcellml import Reset
        from libcellml import When

        w1 = When()
        w2 = When()
        w3 = When()
        r = Reset()

        r.addWhen(w1)
        r.addWhen(w2)
        r.addWhen(w3)
        self.assertEqual(3, r.whenCount())

        r.removeAllWhens()
        self.assertEqual(0, r.whenCount())

    def test_contains_when(self):
        from libcellml import Reset
        from libcellml import When

        w1 = When()
        w2 = When()
        r = Reset()

        r.addWhen(w1)

        self.assertTrue(r.containsWhen(w1))
        self.assertFalse(r.containsWhen(w2))

    def test_when(self):
        from libcellml import Reset
        from libcellml import When

        w = When()
        r = Reset()

        r.addWhen(w)

        self.assertEqual(None, r.getWhen(2))
        self.assertEqual(None, r.getWhen(-4))
        self.assertNotEqual(None, r.getWhen(0))

    def test_take_when(self):
        from libcellml import Reset
        from libcellml import When

        w = When()
        r = Reset()

        r.addWhen(w)

        self.assertEqual(1, r.whenCount())
        self.assertEqual(None, r.takeWhen(2))

        w_returned = r.takeWhen(0)

        self.assertNotEqual(None, w_returned)
        self.assertEqual(0, r.whenCount())

    def test_replace_when(self):
        from libcellml import Reset
        from libcellml import When

        w1 = When()
        w1.setCondition("x=exp(y)")
        w2 = When()
        w2.setValue("a=2")

        r = Reset()

        r.addWhen(w1)

        self.assertFalse(r.replaceWhen(3, w2))
        self.assertEqual("x=exp(y)", r.getWhen(0).getCondition())
        self.assertEqual("", r.getWhen(0).getValue())

        self.assertTrue(r.replaceWhen(0, w2))
        self.assertEqual("", r.getWhen(0).getCondition())
        self.assertEqual("a=2", r.getWhen(0).getValue())


if __name__ == '__main__':
    unittest.main()

