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
Fastest running median filter for arduino.
Working on assumption that input values are positive integers.
Sorting algorithm has linear complexity O(2*N)
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
	};

	void add(T value)
	{
		_buffer[_idx++] = value;

		if (_idx >= _size)
		{
			_idx = 0;
		}

		if (_ctr < _size)
		{
			++_ctr;
		}
	};

	bool getMedian(T& value)
	{
		if (_ctr > 0)
		{
			value = sort((_ctr - 1) / 2, ((_ctr - 1) / 2) + 1);
			return true;
		}
		return false;
	};


	bool getAverage(S samples, T &value)
	{
		if (_ctr > 0 && samples > 0 && samples <= _size)
		{
			if (_ctr < samples)
			{
				samples = _ctr;
			}

			S start = (_ctr - samples) / 2;
			S end = start + samples;
			value = sort(start, end);

			return true;
		}
		return false;
	}


private:
	S _ctr;
	S _idx;
	T _buffer[_size];
	S _counters[_size];

	T sort(S start, S end)
	{
		for (S i = 0; i < _size; ++i)
		{
			_counters[i] = 0;
		}

		for (S i = 0; i < _ctr; ++i)
		{
			++_counters[_buffer[i]];
		}

		S idx = 0;
		T sum = 0;
		S sumCtr = 0;
		for (S i = 0; i < _size; ++i)
		{
			if (_counters[i] == 0)
			{
				continue;
			}

			if (idx >= start && idx <= end)
			{
				sum += i*_counters[i];
				sumCtr += _counters[i];
			}

			idx += _counters[i];
		}

		return sum / sumCtr;
	}
};

#endif