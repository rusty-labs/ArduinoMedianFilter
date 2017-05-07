#ifndef ArduinoMedianFilter_h
#define ArduinoMedianFilter_h

/*
  Copyright(c) 2017 Rustam Iskenderov

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files(the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions :

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/


/*
  Low memory usage sorting algorithm for running median filter.
  Perfect for small arrays.
*/

template <typename T, typename S, S _size> class ArduinoMedianFilter
{
  public:

    ArduinoMedianFilter()
    {
      clear();
    };

    void clear()
    {
      _ctr = 0;
      _idx = 0;
      _sorted = false;
    };

    void add(T value)
    {
      _buffer[_idx++] = value;

      if (_idx >= _size)
        _idx = 0;

      if (_ctr < _size)
        ++_ctr;
    };

    bool getMedian(T& value)
    {
      if (_ctr > 0)
      {
        sort();
        value = _buffer[_ctr / 2];
        return true;
      }
      return false;
    };


    bool getAverage(S samples, T &value)
    {
      if (_ctr > 0 && samples > 0)
      {
        if (_ctr < samples)
          samples = _ctr;

        S start = (_ctr - samples) / 2;
        S end = start + samples;

        sort();

        T sum = 0;
        for (S i = start; i < end; ++i)
        {
          sum += _buffer[i];
        }
        value = sum / samples;
        return true;
      }
      return false;
    }


  private:
    S _ctr;
    S _idx;
    T _buffer[_size];
    bool _sorted;

    // partial bubble sort
    void sort()
    {
      S optCtr = _sorted ? _idx - 1 : _ctr - 1;

      for (S i = 0; i < optCtr; ++i)
      {
        for (S k = 0; k < (_ctr - (i + 1)); ++k)
        {
          if (_buffer[k] > _buffer[k + 1])
          {
            T t = _buffer[k];
            _buffer[k] = _buffer[k + 1];
            _buffer[k + 1] = t;
          }
        }
      }

      _sorted = true;
    }
};

#endif
