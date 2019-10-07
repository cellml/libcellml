#
# Tests the bindings for OrderedEntity, which is the base class for all
# entities that can be ordered relative to one another.
#
import unittest


class OrderedEntityTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import OrderedEntity

        x = OrderedEntity()
        y = OrderedEntity()
        z = OrderedEntity(y)
        del(x, y, z)

    def test_set_order(self):
        from libcellml import OrderedEntity

        x = OrderedEntity()
        x.setOrder(3)
        self.assertEqual(3, x.order())

    def test_is_order_set(self):
        from libcellml import OrderedEntity

        # bool isOrderSet()
        x = OrderedEntity()
        self.assertFalse(x.isOrderSet())
        x.setOrder(2)
        self.assertTrue(x.isOrderSet())

    def test_unset_order(self):
        from libcellml import OrderedEntity

        # unsetOrder()
        x = OrderedEntity()
        x.setOrder(-4)
        self.assertTrue(x.isOrderSet())
        x.unsetOrder()
        self.assertFalse(x.isOrderSet())


if __name__ == '__main__':
    unittest.main()

