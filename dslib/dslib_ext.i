%module dslib_ext
%{
  #include "dslib_ext.hpp"
%}

%include "dslib_ext.hpp"

%extend dslib_ext::RingBuffer {
    PyObject* __getitem__(unsigned int i) {
        return (*($self))[i];
    }

    unsigned int __len__() {
      return (*($self)).size();
    }
}
