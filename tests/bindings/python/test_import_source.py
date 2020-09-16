#
# Tests the ImportSource class bindings.
#
import unittest


class ImportSourceTestCase(unittest.TestCase):

    def test_create(self):
        from libcellml import ImportSource

        x = ImportSource()
        del(x)

    def test_inheritance(self):
        import libcellml
        from libcellml import ImportSource

        x = ImportSource()
        self.assertIsInstance(x, libcellml.entity.Entity)

    def test_url(self):
        from libcellml import ImportSource

        source = 'cheers'
        x = ImportSource()
        self.assertEqual(x.url(), '')
        x.setUrl(source)
        self.assertEqual(x.url(), source)
        x.setUrl('')
        self.assertEqual(x.url(), '')

    def test_model(self):
        from libcellml import ImportSource, Model

        model = Model()
        model.setName('bert')
        x = ImportSource()
        self.assertIsNone(x.model())
        x.setModel(model)
        self.assertEqual(x.model().name(), model.name())
        x.setModel(None)
        self.assertIsNone(x.model())

    def test_has_model(self):
        from libcellml import ImportSource, Model

        x = ImportSource()
        model = Model()
        self.assertFalse(x.hasModel())
        x.setModel(model)
        self.assertTrue(x.hasModel())
        x.setModel(None)
        self.assertFalse(x.hasModel())

    def test_clone(self):
        from libcellml import ImportSource

        sourceUrl = 'cheers'
        x = ImportSource()

        x.setUrl(sourceUrl)
        self.assertEqual(x.url(), sourceUrl)

        xCloned = x.clone()
        self.assertEqual(xCloned.url(), sourceUrl)


    def test_component(self):
        from libcellml import ImportSource, Component

        x = ImportSource()
        c1 = Component("c1")
        c2 = Component("c2")

        self.assertEqual(0, x.componentCount())

        x.addComponent(c1)
        x.addComponent(c2)

        self.assertEqual(2, x.componentCount())
        self.assertEqual("c2", x.component(1).name())

        x.removeComponent(1)

        self.assertEqual(1, x.componentCount())

        x.removeAllComponents()

        self.assertEqual(0, x.componentCount())


    def test_units(self):
        from libcellml import ImportSource, Units

        x = ImportSource()
        u1 = Units("u1")
        u2 = Units("u2")

        self.assertEqual(0, x.unitsCount())

        x.addUnits(u1)
        x.addUnits(u2)

        self.assertEqual(2, x.unitsCount())
        self.assertEqual("u2", x.units(1).name())

        x.removeUnits(1)

        self.assertEqual(1, x.unitsCount())

        x.removeAllUnits()

        self.assertEqual(0, x.unitsCount())



if __name__ == '__main__':
    unittest.main()
