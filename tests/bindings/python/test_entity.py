#
# Tests the entity class bindings
#
import unittest


class EntityTestCase(unittest.TestCase):

    def test_create(self):
        from libcellml.entity import Entity

        self.assertRaises(AttributeError, Entity)

    def test_id(self):
        from libcellml import Model

        # std::string id()
        x = Model()
        self.assertEqual(x.id(), '')

        # void setId(const std::string &id)
        idx = 'test'
        x.setId(idx)
        self.assertEqual(x.id(), idx)

    def test_parent(self):
        from libcellml import Model, Component

        x = Model("model")
        self.assertIsNone(x.parent())

        c = Component()
        self.assertIsNone(c.parent())
        c.setParent(x)
        self.assertEqual("model", c.parent().name())
        self.assertEqual(0, x.componentCount())

    def test_remove_parent(self):
        from libcellml import Model, Component

        m = Model()
        c = Component()
        c.setParent(m)
        self.assertIsNotNone(c.parent())
        c.removeParent()
        self.assertIsNone(c.parent())

    def test_has_parent(self):
        from libcellml import Component

        # bool hasParent(Component* c)
        x = Component()
        c1 = Component()
        self.assertFalse(x.hasParent())
        x.setParent(c1)
        self.assertTrue(x.hasParent())
        x.removeParent()
        self.assertFalse(x.hasParent())
        c2 = Component()
        c2.setParent(c1)
        x.setParent(c2)
        self.assertTrue(x.hasParent())

    def test_has_ancestor(self):
        from libcellml import Component

        # bool hasParent(Component* c)
        x = Component()
        c1 = Component()
        c2 = Component()
        self.assertFalse(c2.hasAncestor(c1))
        self.assertFalse(c2.hasAncestor(x))

        c1.setParent(x)
        c2.setParent(c1)
        self.assertTrue(c2.hasAncestor(c1))
        self.assertTrue(c2.hasAncestor(x))


class NamedEntityTestCase(unittest.TestCase):

    def test_create(self):
        from libcellml.namedentity import NamedEntity

        self.assertRaises(AttributeError, NamedEntity)


class LoggerTestCase(unittest.TestCase):

    def test_create(self):
        from libcellml.logger import Logger

        self.assertRaises(AttributeError, Logger)


    def test_issue_types(self):
        from libcellml import Parser, Issue

        p = Parser()

        i1 = Issue()
        i1.setLevel(Issue.Level.ERROR)
        i1.setDescription("error error")
        p.addIssue(i1)

        i4 = Issue()
        i4.setLevel(Issue.Level.WARNING)
        i4.setDescription("warning warning")
        p.addIssue(i4)

        i2 = Issue()
        i2.setLevel(Issue.Level.HINT)
        i2.setDescription("hint hint")
        p.addIssue(i2)

        i3 = Issue()
        i3.setLevel(Issue.Level.MESSAGE)
        i3.setDescription("message message")
        p.addIssue(i3)

        self.assertEqual(1, p.errorCount())
        error = p.error(0)
        self.assertEqual("error error", error.description())

        self.assertEqual(1, p.warningCount())
        warning = p.warning(0)
        self.assertEqual("warning warning", warning.description())

        self.assertEqual(1, p.hintCount())
        hint = p.hint(0)
        self.assertEqual("hint hint", hint.description())

        self.assertEqual(1, p.messageCount())
        message = p.message(0)
        self.assertEqual("message message", message.description())

        self.assertEqual(4, p.issueCount())
        p.removeAllIssues()
        self.assertEqual(0, p.issueCount())


if __name__ == '__main__':
    unittest.main()
