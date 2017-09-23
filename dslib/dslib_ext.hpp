#ifndef RINGBUFFER
#define RINGBUFFER

#include <boost/circular_buffer.hpp>
#include <boost/foreach.hpp>

#include <iostream>
#include <utility>

#include <Python.h>

namespace dslib_ext {

  class RingBuffer {
  public:
    RingBuffer(int sz) {
      buffer = boost::circular_buffer<PyObject*>(sz);
    };

    PyObject* operator[](unsigned int i) {
      if (buffer.size() == 0) {
        PyErr_SetString(PyExc_IndexError, "RingBuffer is empty.");
        return NULL;
      }
      if ((0 <= i) && (i < buffer.size())) {
        return buffer[i];
      } else {
        PyErr_SetString(PyExc_IndexError, "RingBuffer index out of range.");
        return NULL;
      }
    }

    void append(PyObject* obj) {
      if (buffer.full()) {
        PyObject* oldLast = *buffer.begin();
        Py_DECREF(oldLast);
      }
      Py_INCREF(obj);
      buffer.push_back(obj);
    }

    unsigned int size() {
      return buffer.size();
    }

    ~RingBuffer() {
      BOOST_FOREACH(PyObject* obj, buffer ) {
        Py_DECREF(obj);
      }
    };
  private:
    boost::circular_buffer<PyObject*> buffer;
  };

}

#endif
