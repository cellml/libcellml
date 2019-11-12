#
# Tests the entity class bindings
#
import unittest


class EntityTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Entity

        x = Entity()
        del(x)
        y = Entity()
        z = Entity(y)
        del(y, z)

    def test_id(self):
        from libcellml import Entity

        # std::string id()
        x = Entity()
        self.assertEqual(x.id(), '')

        # void setId(const std::string &id)
        idx = 'test'
        x.setId(idx)
        self.assertEqual(x.id(), idx)

    def test_copy_constructor(self):
        from libcellml import Entity

        x = Entity()
        idx = 'hello'
        x.setId(idx)
        y = Entity(x)
        self.assertEqual(y.id(), idx)

    def test_parent(self):
        from libcellml import Entity

        x = Entity()
        self.assertIsNone(x.parent())

    def test_set_parent(self):
        from libcellml import Entity, Model, Component

        m = Model()
        x = Entity()
        x.setParent(m)
        self.assertIsNotNone(x.parent())
        # TODO: Check equivalence

        c = Component()
        x = Entity()
        x.setParent(c)
        self.assertIsNotNone(x.parent())
        # TODO: Check equivalence

    def test_clear_parent(self):
        from libcellml import Entity, Model, Component

        # void clearParent()
        x = Entity()
        self.assertIsNone(x.parent())
        m = Model()
        x.setParent(m)
        self.assertIsNotNone(x.parent())
        x.clearParent()
        self.assertIsNone(x.parent())
        c = Component()
        x.setParent(c)
        self.assertIsNotNone(x.parent())
        x.clearParent()
        self.assertIsNone(x.parent())

    def test_has_parent(self):
        from libcellml import Entity, Component

        # bool hasParent(Component* c)
        x = Entity()
        c1 = Component()
        self.assertFalse(x.hasParent())
        x.setParent(c1)
        self.assertTrue(x.hasParent())
        x.clearParent()
        self.assertFalse(x.hasParent())
        c2 = Component()
        c2.setParent(c1)
        x.setParent(c2)
        self.assertTrue(x.hasParent())


if __name__ == '__main__':
    unittest.main()
