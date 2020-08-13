#
# Tests the ImportSource class bindings.
#
import unittest


class ImportSourceTestCase(unittest.TestCase):

    def test_import_source(self):
        from libcellml import ImportSource

        # Test create/copy/destroy
        x = ImportSource()
        del(x)

    def test_inheritance(self):
        import libcellml
        from libcellml import ImportSource

        x = ImportSource()
        self.assertIsInstance(x, libcellml.entity.Entity)

    def test_set_url(self):
        from libcellml import ImportSource

        # void setUrl(const std::string &reference)
        x = ImportSource()
        x.setUrl('')
        x.setUrl('hello')
        x.setUrl('')

    def test_url(self):
        from libcellml import ImportSource

        # std::string url()
        source = 'cheers'
        x = ImportSource()
        self.assertEqual(x.url(), '')
        x.setUrl(source)
        self.assertEqual(x.url(), source)
        x.setUrl('')
        self.assertEqual(x.url(), '')

    def test_set_model(self):
        from libcellml import ImportSource, Model

        # void setModel(const ModelPtr &model);
        x = ImportSource()
        x.setModel(None)
        x.setModel(Model())
        x.setModel(None)

    def test_model(self):
        from libcellml import ImportSource, Model

        # ModelPtr model() const;
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

        # bool hasModel() const;
        x = ImportSource()
        model = Model()
        self.assertFalse(x.hasModel())
        x.setModel(model)
        self.assertTrue(x.hasModel())
        x.setModel(None)
        self.assertFalse(x.hasModel())


if __name__ == '__main__':
    unittest.main()
