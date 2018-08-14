#
# Tests the ImportSource class bindings.
#
import unittest


class ImportSourceTestCase(unittest.TestCase):

    def test_import_source(self):
        from libcellml import ImportSource

        # Test create/copy/destroy
        x = ImportSource()
        y = ImportSource()
        z = ImportSource(y)
        del(x, y, z)

    def test_inheritance(self):
        import libcellml
        from libcellml import ImportSource

        x = ImportSource()
        self.assertIsInstance(x, libcellml.Entity)

    def test_set_url(self):
        from libcellml import ImportSource

        # void setUrl(const std::string &reference)
        x = ImportSource()
        x.setUrl('')
        x.setUrl('hello')
        x.setUrl('')

    def test_get_url(self):
        from libcellml import ImportSource

        # std::string getUrl()
        source = 'cheers'
        x = ImportSource()
        self.assertEqual(x.getUrl(), '')
        x.setUrl(source)
        self.assertEqual(x.getUrl(), source)
        x.setUrl('')
        self.assertEqual(x.getUrl(), '')

    def test_set_model(self):
        from libcellml import ImportSource, Model

        # void setModel(libcellml::ModelPtr model);
        x = ImportSource()
        x.setModel(None)
        x.setModel(Model())
        x.setModel(None)

    def test_get_model(self):
        from libcellml import ImportSource, Model

        # libcellml::ModelPtr getModel() const;
        model = Model()
        model.setName('bert')
        x = ImportSource()
        self.assertIsNone(x.getModel())
        x.setModel(model)
        self.assertEqual(x.getModel().getName(), model.getName())
        x.setModel(None)
        self.assertIsNone(x.getModel())

    def test_has_model(self):
        from libcellml import ImportSource, Model

        # bool hasModel() const;
        x = ImportSource()
        self.assertFalse(x.hasModel())
        x.setModel(Model())
        self.assertTrue(x.hasModel())


if __name__ == '__main__':
    unittest.main()
