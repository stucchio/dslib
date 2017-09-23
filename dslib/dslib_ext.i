%module dslib_ext
%{
  #include "dslib_ext.hpp"
%}

%ignore FunctionalListStorage;

%include "dslib_ext.hpp"

%extend dslib_ext::RingBuffer {
    PyObject* __getitem__(unsigned int i) {
        return (*($self))[i];
    }

    unsigned int __len__() {
      return (*($self)).size();
    }
}

%extend dslib_ext::FunctionalList {
    unsigned int __len__() {
      return (*($self)).length();
    }
}
