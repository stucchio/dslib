import unittest
from dslib import *
from sys import getrefcount

class TestFunctionalList(unittest.TestCase):
    def test_basic_fl(self):
        fl = FunctionalList("foo")
        self.assertEqual(fl.head(), "foo")
        self.assertEqual(fl.tail(), None)

        fl2 = fl.prepend("bar")
        self.assertEqual(fl2.head(), "bar")
        self.assertEqual(fl2.tail().head(), "foo")

    def test_length(self):
        fl = FunctionalList("foo")
        for i in range(10):
            fl = fl.prepend(str(i))
            self.assertqual(len(fl), i+1)

    def test_gc_on_delete(self):
        x = "obj"
        rc = getrefcount(x)
        fl1 = FunctionalList(x)
        self.assertEqual(getrefcount(x), rc+1)
        y = "baz"
        fl2 = FunctionalList(y, fl1)
        self.assertEqual(getrefcount(x), rc+1)
        fl1 = None
        self.assertEqual(getrefcount(x), rc+1)
        fl2 = None
        self.assertEqual(getrefcount(x), rc)

    def test_gc_on_delete2(self):
        x = "obj"
        rcx = getrefcount(x)
        fl1 = FunctionalList(x)
        self.assertEqual(getrefcount(x), rcx+1)
        y = "baz"
        rcy = getrefcount(y)
        fl2 = FunctionalList(y, fl1)
        self.assertEqual(getrefcount(x), rcx+1)
        fl3 = FunctionalList(y, fl1)
        fl1 = None
        #self.assertEqual(getrefcount(x), rc+1)
        fl2 = None
        fl3 = None
        self.assertEqual(getrefcount(x), rcx)

if __name__ == '__main__':
    unittest.main()
