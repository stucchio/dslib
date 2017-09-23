#ifndef RINGBUFFER
#define RINGBUFFER

#include <boost/circular_buffer.hpp>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>
#include <utility>

#include <Python.h>

namespace dslib_ext {

  namespace implementation {
    class FunctionalListStorage {
    public:
      FunctionalListStorage(PyObject* head) {
        tailStorage.reset();
        obj = head;
        Py_INCREF(obj);
        size = 0;
      }

      FunctionalListStorage(PyObject* head, boost::shared_ptr<FunctionalListStorage> _tail) {
        tailStorage = _tail;
        obj = head;
        Py_INCREF(obj);
        size = tailStorage->size+1;
      }

      ~FunctionalListStorage() {
        Py_DECREF(obj);
        if (tailStorage) {
          tailStorage.reset();
        }
      }

      PyObject* head() {
        return obj;
      }

      FunctionalListStorage* tail() {
        return tailStorage.get();
      }

      size_t length() {
        return size;
      }

    private:
      boost::shared_ptr<FunctionalListStorage> tailStorage;
      PyObject* obj;
      size_t size;
    };
  }

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

  class FunctionalList {
  public:
    FunctionalList(PyObject* head) {
      storage.reset(new implementation::FunctionalListStorage(head));
    }
    FunctionalList(PyObject* head, FunctionalList* tail) {
      storage.reset(new implementation::FunctionalListStorage(head, tail->storage));
    }
    FunctionalList(implementation::FunctionalListStorage* s) {
      storage.reset(s);
    }

    FunctionalList* prepend(PyObject* obj) {
      return new FunctionalList(obj, this);
    }

    PyObject* head() {
      return storage->head();
    }

    FunctionalList* tail() {
      implementation::FunctionalListStorage* tail = storage->tail();
      if (tail) {
        return new FunctionalList(tail);
      } else {
        return NULL;
      }
    }

    size_t length() {
      return storage->length();
    }

  private:
    boost::shared_ptr<implementation::FunctionalListStorage> storage;
  };
}

#endif
