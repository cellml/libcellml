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

    def test_parent_model(self):
        from libcellml import Entity

        # ModelPtr parentModel
        # TODO: This method might be moved out of entity!
        # TODO: If not, this needs a workaround!
        x = Entity()
        self.assertIsNone(x.parentModel())

    def test_parent_component(self):
        from libcellml import Entity

        # ComponentPtr parentComponent
        # TODO: This method might be moved out of entity!
        # TODO: If not, this needs a workaround!
        x = Entity()
        self.assertIsNone(x.parentComponent())

    def test_set_parent(self):
        from libcellml import Entity, Model, Component

        # void setParent(Model *parent)
        m = Model()
        x = Entity()
        x.setParent(m)
        self.assertIsNotNone(x.parentModel())
        # TODO: Check equivalence

        c = Component()
        x = Entity()
        x.setParent(c)
        self.assertIsNotNone(x.parentComponent())
        # TODO: Check equivalence

    def test_clear_parent(self):
        from libcellml import Entity, Model, Component

        # void clearParent()
        x = Entity()
        self.assertIsNone(x.parentModel())
        m = Model()
        x.setParent(m)
        self.assertIsNotNone(x.parentModel())
        x.clearParent()
        self.assertIsNone(x.parentComponent())
        c = Component()
        x.setParent(c)
        self.assertIsNotNone(x.parentComponent())
        x.clearParent()
        self.assertIsNone(x.parentModel())
        self.assertIsNone(x.parentComponent())

    def test_has_parent(self):
        from libcellml import Entity, Component

        # bool hasParent(Component* c)
        x = Entity()
        c1 = Component()
        self.assertFalse(x.hasAncestor(c1))
        x.setParent(c1)
        self.assertTrue(x.hasAncestor(c1))
        x.clearParent()
        self.assertFalse(x.hasAncestor(c1))
        c2 = Component()
        c2.setParent(c1)
        x.setParent(c2)
        self.assertTrue(x.hasAncestor(c1))


if __name__ == '__main__':
    unittest.main()
