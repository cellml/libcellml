#
# Tests the Model class bindings
#
import unittest


class ModelTestCase(unittest.TestCase):

    def test_create_destroy(self):
        import libcellml
        from libcellml import Model

        x = Model()
        del(x)

        y = Model('bob')
        self.assertEqual('bob', y.name())

        z = libcellml.Model()
        del z

    def test_inheritance(self):
        import libcellml
        from libcellml import Model

        x = Model()
        self.assertIsInstance(x, libcellml.componententity.ComponentEntity)
        self.assertIsInstance(x, libcellml.namedentity.NamedEntity)
        self.assertIsInstance(x, libcellml.entity.Entity)

        # Test access to inherited methods
        x = Model()
        idx = 'test'
        self.assertEqual(x.id(), '')
        x.setId(idx)
        self.assertEqual(x.id(), idx)

    def test_add_units(self):
        from libcellml import Model, Units

        # void addUnits(const UnitsPtr &units)
        m = Model()
        u = Units()
        m.addUnits(u)

    def test_remove_units(self):
        from libcellml import Model, Units

        # bool removeUnits(size_t index)
        m = Model()
        u = Units()
        self.assertFalse(m.removeUnits(0))
        self.assertFalse(m.removeUnits(1))
        self.assertFalse(m.removeUnits(-1))
        m.addUnits(u)
        self.assertFalse(m.removeUnits(1))
        self.assertFalse(m.removeUnits(-1))
        self.assertTrue(m.removeUnits(0))
        self.assertFalse(m.removeUnits(0))
        del(m, u)

        # bool removeUnits(const std::string &name)
        name = 'bert'
        m = Model()
        u = Units()
        u.setName(name)
        self.assertFalse(m.removeUnits(name))
        m.addUnits(u)
        self.assertFalse(m.removeUnits('ernie'))
        self.assertTrue(m.removeUnits(name))
        del(m, u, name)

        # bool removeUnits(const UnitsPtr &units)
        m = Model()
        u1 = Units()
        u2 = Units()
        self.assertFalse(m.removeUnits(u1))
        m.addUnits(u1)
        self.assertFalse(m.removeUnits(u2))
        self.assertFalse(m.removeUnits(u1))
        del(m, u1, u2)

    def test_remove_all_units(self):
        from libcellml import Model, Units

        # void removeAllUnits()
        m = Model()
        u1 = Units()
        u2 = Units()
        m.addUnits(u1)
        m.addUnits(u2)
        m.removeAllUnits()
        self.assertFalse(m.removeUnits(u1))
        self.assertFalse(m.removeUnits(u2))
        del(m, u1, u2)

    def test_has_units(self):
        from libcellml import Model, Units

        # bool hasUnits(const std::string &name)
        name = 'loud'
        m = Model()
        u = Units()
        u.setName(name)
        m.addUnits(u)
        self.assertFalse(m.hasUnits('hi'))
        self.assertTrue(m.hasUnits(name))

        # bool hasUnits(const UnitsPtr &units)
        self.assertTrue(m.hasUnits(u))
        v = Units()
        self.assertFalse(m.hasUnits(v))

    def test_units(self):
        from libcellml import Model, Units

        # UnitsPtr units(size_t index)
        name = 'naaame'
        m = Model()
        u = Units()
        u.setName(name)
        self.assertIsNone(m.units(0))
        self.assertIsNone(m.units(1))
        self.assertIsNone(m.units(-1))
        m.addUnits(u)
        self.assertIsNone(m.units(1))
        self.assertIsNone(m.units(-1))
        self.assertIsNotNone(m.units(0))
        self.assertEqual(m.units(0).name(), name)
        del(m, u, name)

        # UnitsPtr units(const std::string &name)
        name = 'kermit'
        m = Model()
        u = Units()
        u.setName(name)
        self.assertIsNone(m.units(name))
        m.addUnits(u)
        self.assertIsNotNone(m.units(name))
        self.assertEqual(m.units(name).name(), name)
        del(m, u, name)

    def test_take_units(self):
        from libcellml import Model, Units

        # UnitsPtr takeUnits(size_t index)
        name = 'piggy'
        m = Model()
        u = Units()
        u.setName(name)
        self.assertIsNone(m.takeUnits(0))
        self.assertIsNone(m.takeUnits(-1))
        self.assertIsNone(m.takeUnits(1))
        m.addUnits(u)
        self.assertIsNone(m.takeUnits(-1))
        self.assertIsNone(m.takeUnits(1))
        self.assertIsNotNone(m.takeUnits(0))
        self.assertIsNone(m.takeUnits(0))
        m.addUnits(Units())
        m.addUnits(u)
        self.assertEqual(m.takeUnits(1).name(), name)
        del(m, u)

        # UnitsPtr takeUnits(const std::string &name)
        name = 'aloha'
        m = Model()
        u = Units()
        u.setName(name)
        self.assertIsNone(m.takeUnits(name))
        m.addUnits(u)
        self.assertEqual(m.takeUnits(name).name(), name)
        self.assertIsNone(m.takeUnits(name))
        del(m, u, name)

    def test_replace_units(self):
        from libcellml import Model, Units

        # bool replaceUnits(size_t index, const UnitsPtr &units)
        m = Model()
        u1 = Units()
        u1.setName('a')
        m.addUnits(u1)
        u2 = Units()
        u2.setName('b')
        self.assertTrue(m.replaceUnits(0, u2))
        self.assertFalse(m.replaceUnits(1, u1))
        self.assertFalse(m.replaceUnits(-1, u1))
        self.assertEqual(m.units(0).name(), 'b')
        del(m, u1, u2)

        # bool replaceUnits(const std::string &name, const UnitsPtr &units)
        m = Model()
        a = Units()
        a.setName('a')
        m.addUnits(a)
        b = Units()
        b.setName('b')
        self.assertFalse(m.replaceUnits('b', a))
        self.assertTrue(m.replaceUnits('a', b))
        self.assertTrue(m.replaceUnits('b', a))
        self.assertFalse(m.replaceUnits('b', a))
        del(m, a, b)

        # bool replaceUnits(const UnitsPtr &oldUnits, const UnitsPtr &newUnits)
        m = Model()
        a = Units()
        m.addUnits(a)
        b = Units()
        self.assertFalse(m.replaceUnits(b, a))
        self.assertFalse(m.replaceUnits(a, b))
        self.assertFalse(m.replaceUnits(b, a))
        del(m, a, b)

    def test_units_count(self):
        from libcellml import Model, Units

        # size_t unitsCount()
        m = Model()
        self.assertEqual(m.unitsCount(), 0)
        m.addUnits(Units())
        self.assertEqual(m.unitsCount(), 1)
        m.addUnits(Units())
        self.assertEqual(m.unitsCount(), 2)
        m.removeAllUnits()
        self.assertEqual(m.unitsCount(), 0)
        del(m)

    def test_has_unresolved_imports(self):
        from libcellml import Model, Component, ImportSource

        # bool hasUnresolvedImports();
        m = Model()
        self.assertFalse(m.hasUnresolvedImports())
        c = Component()
        m.addComponent(c)
        self.assertFalse(m.hasUnresolvedImports())
        c.setImportSource(ImportSource())
        self.assertTrue(m.hasUnresolvedImports())

    def test_add_component(self):
        from libcellml import Model, Component

        m = Model()
        c = Component()

        self.assertEqual(0, m.componentCount())
        m.addComponent(c)
        self.assertTrue(m.containsComponent(c))
        self.assertEqual(1, m.componentCount())

    def test_remove_component(self):
        from libcellml import Model, Component

        m = Model()
        c1 = Component()
        c2 = Component()

        self.assertEqual(0, m.componentCount())
        m.addComponent(c1)
        m.addComponent(c2)
        self.assertEqual(2, m.componentCount())

        m.removeAllComponents()
        self.assertEqual(0, m.componentCount())

        m.addComponent(c1)
        m.addComponent(c2)

        self.assertEqual(2, m.componentCount())
        m.removeComponent(c2)
        self.assertEqual(1, m.componentCount())

    def test_ids(self):
      from libcellml import Model

      m = Model()
      self.assertEqual('', m.id())
      self.assertEqual('', m.encapsulationId())

      m.setId('main_model')
      m.setEncapsulationId('model_encapsulation')
      self.assertEqual('main_model', m.id())
      self.assertEqual('model_encapsulation', m.encapsulationId())



if __name__ == '__main__':
    unittest.main()
