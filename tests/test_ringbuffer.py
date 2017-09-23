import unittest
from dslib import *
from sys import getrefcount

class TestRingBuffer(unittest.TestCase):
    def test_basic(self):
        b = RingBuffer(3)
        b.append("foo")
        b.append("bar")
        self.assertEqual(b[0], 'foo')
        self.assertEqual(len(b), 2)
        b.append("baz")
        b.append("buz")
        self.assertEqual(b[2], 'buz')
        self.assertEqual(b[0], 'bar')
        self.assertEqual(len(b), 3)

    def test_gc_on_delete(self):
        x = "obj"
        rc = getrefcount(x)
        b = RingBuffer(3)
        b.append(x)
        self.assertEqual(getrefcount(x), rc+1)
        b = None
        self.assertEqual(getrefcount(x), rc)

    def test_gc_on_cycle(self):
        x = "obj"
        rc = getrefcount(x)
        b = RingBuffer(3)
        b.append(x)
        self.assertEqual(getrefcount(x), rc+1)
        for i in range(20):
            b.append(str(i))
        self.assertEqual(getrefcount(x), rc)


if __name__ == '__main__':
    unittest.main()
