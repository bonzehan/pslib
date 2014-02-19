/* 
   Copyright 2011-2014 Propeller Systems
   propellersystems@gmail.com

   This file is part of PSLib.

   PSLib is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   PSLib is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with PSLib.  If not, see <http://www.gnu.org/licenses/>.
   */

#ifndef PS_RING_BUFFER_H
#define PS_RING_BUFFER_H

namespace ps
{
    template< typename T, uint16_t SIZE >
        class ringbuffer
        {
            T _data[SIZE];
            uint16_t _w_pos;
            uint16_t _r_pos;
            uint16_t _element_to_read;

            void __seek_read()
            {
                --_element_to_read;
                _r_pos = (_r_pos + 1) % SIZE;
            }

            void __seek_write()
            {
                ++_element_to_read;
                _w_pos = (_w_pos + 1) % SIZE;
            }

            public:

            class itrator;
            class reverse_iterator;

            class iterator
            {
                uint16_t _pos;
                ringbuffer* _ptr_data;

                friend class ringbuffer< T, SIZE >;

                iterator(uint16_t pos, ringbuffer* ptr_data) :
                    _pos(pos), _ptr_data(ptr_data)
                {
                }

                public:

                iterator() : _pos(0), _ptr_data(nullptr)
                {
                }

                iterator(const reverse_iterator& iter)
                {   
                    _pos = iter._pos;
                    _ptr_data = iter._ptr_data;
                }

                iterator& operator= (const iterator& iter)
                {
                    _pos = iter._pos;
                    _ptr_data = iter._ptr_data;
                    return *this;
                }

                iterator& operator= (const reverse_iterator& iter)
                {
                    _pos = iter._pos;
                    _ptr_data = iter._ptr_data;
                    return *this;
                }

                iterator& operator++ () // ++it
                {
                    _pos = (_pos + 1) % SIZE;
                    return *this;
                }

                iterator operator++ (int) // it++
                {
                    uint16_t tmp = _pos;
                    _pos = (_pos + 1) % SIZE;
                    return iterator(tmp, _ptr_data);
                }

                iterator& operator-- () // --it
                {
                    _pos = (SIZE + _pos - 1) % SIZE;
                    return *this;
                }

                iterator operator-- (int) // it--
                {
                    uint16_t tmp = _pos;
                    _pos = (SIZE + _pos - 1) % SIZE;
                    return iterator(tmp, _ptr_data);
                }

                bool operator== (const iterator& iter) const
                {
                    return _pos == iter._pos;
                }

                bool operator== (const reverse_iterator& iter) const
                {
                    return _pos == iter._pos;
                }

                bool operator!= (const iterator& iter) const
                {
                    return _pos != iter._pos;
                }

                bool operator!= (const reverse_iterator& iter) const
                {
                    return _pos != iter._pos;
                }

                T operator* () const
                {
                    return _ptr_data->_data[_pos];
                }

                T* operator& () const
                {
                    return _ptr_data->_data + _pos;
                }

                T operator[] (const uint16_t i) const
                {
                    return _ptr_data->_data[(_pos+i) % SIZE];
                }
            };

            class reverse_iterator
            {
                uint16_t  _pos;
                ringbuffer* _ptr_data;

                friend class ringbuffer< T, SIZE >;

                reverse_iterator(uint16_t pos, ringbuffer* ptr_data) :
                    _pos(pos), _ptr_data(ptr_data)
                {
                }

                public:

                reverse_iterator() : _pos(0), _ptr_data(nullptr)
                {
                }

                reverse_iterator(const iterator& iter)
                {   
                    _pos = iter._pos;
                    _ptr_data = iter._ptr_data;
                }

                reverse_iterator& operator= (const reverse_iterator& iter)
                {
                    _pos = iter._pos;
                    _ptr_data = iter._ptr_data;
                    return *this;
                }

                reverse_iterator& operator= (const iterator& iter)
                {
                    _pos = iter._pos;
                    _ptr_data = iter._ptr_data;
                    return *this;
                }

                reverse_iterator& operator++ () // ++it
                {
                    _pos = (SIZE + _pos - 1) % SIZE;
                    return *this;
                }

                reverse_iterator operator++ (int) // it++
                {
                    uint16_t tmp = _pos;
                    _pos = (SIZE + _pos - 1) % SIZE;
                    return reverse_iterator(tmp, _ptr_data);
                }

                reverse_iterator& operator-- () // --it
                {
                    ++_pos;
                    _pos = (_pos + 1) % SIZE;
                    return *this;
                }

                reverse_iterator operator-- (int) // it--
                {
                    uint16_t tmp = _pos;
                    _pos = (_pos + 1) % SIZE;
                    return reverse_iterator(tmp, _ptr_data);
                }

                bool operator== (const reverse_iterator& iter) const
                {
                    return _pos == iter._pos;
                }

                bool operator== (const iterator& iter) const
                {
                    return _pos == iter._pos;
                }

                bool operator!= (const reverse_iterator& iter) const
                {
                    return _pos != iter._pos;
                }

                bool operator!= (const iterator& iter) const
                {
                    return _pos != iter._pos;
                }

                T operator* () const
                {
                    return _ptr_data->_data[_pos];
                }

                T* operator& () const
                {
                    return _ptr_data->_data + _pos;
                }

                T operator[] (const uint16_t i) const
                {
                    return _ptr_data->_data[(SIZE+_pos-i) % SIZE];
                }
            };

            ringbuffer() : _w_pos(0), _r_pos(0), _element_to_read(0)
            {
            }

            // read -> seek
            T read()
            {
                uint16_t r_pos = _r_pos;
                if(_element_to_read > 0)
                {
                    __seek_read();
                }
                return _data[r_pos];
            }

            // write -> seek
            void write(T data)
            {
                if(_element_to_read < SIZE)
                {
                    _data[_w_pos] = data;
                    __seek_write();
                }
            }

            void write_force(T data)
            {
                if(_element_to_read == SIZE)
                    __seek_read();
                _data[_w_pos] = data;
                __seek_write();
            }

            const std::function< T(void) > fread = [this] () -> T 
            {
                return this->read();
            };

            const std::function< void(T) > fwrite = [this] (T data)
            {
                this->write(data);
            };

            const std::function< void(T) > fwrite_force = [this] (T data)
            {
                this->write_force(data);
            };

            uint16_t element_to_read_to_read() const
            {
                return _element_to_read;
            }

            uint16_t element_to_read_to_write() const
            {
                return SIZE - _element_to_read;
            }

            uint16_t size() const
            {
                return SIZE;
            }

            void seek_read(uint16_t count)
            {
                if(count > _element_to_read) 
                {
                    _r_pos = _w_pos;
                    _element_to_read = 0;
                }
                else
                {
                    _r_pos = (_r_pos + count) % SIZE;
                    _element_to_read -= count;
                }
            }

            void flush()
            {
                _r_pos = _w_pos;
                _element_to_read = 0;
            }   

            void clear()
            {
                _r_pos = 0;
                _w_pos = 0;
                _element_to_read = 0;
            }

            iterator begin()
            {
                return iterator(_r_pos, this);
            }

            reverse_iterator rbegin()
            {
                return reverse_iterator(_w_pos>0 ? _w_pos-1 : SIZE-1, this);
            }

            iterator end()
            {
                return iterator(_w_pos, this);
            }

            reverse_iterator rend()
            {
                return reverse_iterator(_r_pos>0 ? _r_pos-1 : SIZE-1, this);
            }
        };
}

#endif
