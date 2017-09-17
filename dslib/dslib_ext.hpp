#ifndef RINGBUFFER
#define RINGBUFFER

#include <boost/circular_buffer.hpp>
#include <boost/circular_buffer/space_optimized.hpp>

namespace dslib_ext {

  class RingBuffer {
  public:
    RingBuffer(int sz) {
      buffer = boost::circular_buffer_space_optimized<int>(sz);
    };
    ~RingBuffer() {
    };
  private:
    boost::circular_buffer_space_optimized<int> buffer;
  };

}

#endif
