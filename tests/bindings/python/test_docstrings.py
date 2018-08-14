#
# Tests if all CellML bindings have docstrings set.
#
import unittest
import types


class DocstringTestCase(unittest.TestCase):

    def test_docstrings(self):
        import libcellml

        # Scan for missing or empty docstrings
        def scan(root, missing, prefix=''):
            prefix += root.__name__
            if not root.__doc__:
                missing.append(prefix)
            prefix += '.'
            for x in dir(root):
                if x[:1] != '_' and x is not root:
                    child = getattr(root, x)
                    if isinstance(child, (type, types.FunctionType)):
                        scan(child, missing, prefix)

        missing = []
        scan(libcellml, missing)
        if missing:
            raise Exception('Missing docstrings for: ' + ', '.join(missing))


if __name__ == '__main__':
    unittest.main()
