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

#ifndef PS_ARRAY_H
#define PS_ARRAY_H

#include <cstring>

namespace ps
{
    template< typename T, uint32_t SIZE >
        class array
        {
            T _data[SIZE];
            uint32_t _size;

            public:

            class iterator
            {
                friend class ps::array< T, SIZE >;

                T* _ptr_data;
                array< T, SIZE >* _ptr_arr;

                iterator(array< T, SIZE >* ptr_arr, T* ptr_data) :
                    _ptr_arr(ptr_arr), _ptr_data(ptr_data)
                {
                }

                public:
                iterator() : _ptr_arr(nullptr), _ptr_data(nullptr)
                {
                }

                iterator& operator= (const iterator& iter)
                {
                    _ptr_data = iter._ptr_data;
                    _ptr_arr  = iter._ptr_arr;
                    return *this;
                }

                bool operator== (const iterator& iter) const
                {
                    return _ptr_data == iter._ptr_data;
                }

                bool operator!= (const iterator& iter) const
                {
                    return _ptr_data != iter._ptr_data;
                }

                iterator& operator++ () // ++it
                {
                    ++_ptr_data;
                    return *this;
                }

                iterator operator++ (int) // it++
                {
                    ++_ptr_data;
                    return iterator(_ptr_arr, _ptr_data - 1);
                }

                iterator& operator-- () // --it
                {
                    --_ptr_data;
                    return *this;
                }

                iterator operator-- (int) // it--
                {
                    --_ptr_data;
                    return iterator(_ptr_arr, _ptr_data + 1);
                }

                T& operator* () const
                {
                    return *_ptr_data;
                }
            };

            class const_iterator
            {
                friend class ps::array< T, SIZE >;

                T* _ptr_data;
                array< T, SIZE >* _ptr_arr;

                const_iterator(array< T, SIZE >* ptr_arr, T* ptr_data) :
                    _ptr_arr(ptr_arr), _ptr_data(ptr_data)
                {
                }

                public:
                const_iterator() : _ptr_arr(nullptr), _ptr_data(nullptr)
                {
                }

                const_iterator& operator= (const const_iterator& iter)
                {
                    _ptr_data = iter._ptr_data;
                    _ptr_arr  = iter._ptr_arr;
                    return *this;
                }

                bool operator== (const const_iterator& iter) const
                {
                    return _ptr_data == iter._ptr_data;
                }

                bool operator!= (const const_iterator& iter) const
                {
                    return _ptr_data != iter._ptr_data;
                }

                const_iterator& operator++ () // ++it
                {
                    ++_ptr_data;
                    return *this;
                }

                const_iterator operator++ (int) // it++
                {
                    ++_ptr_data;
                    return const_iterator(_ptr_arr, _ptr_data + 1);
                }

                const_iterator& operator-- () // --it
                {
                    --_ptr_data;
                    return *this;
                }

                const_iterator operator-- (int) // it--
                {
                    --_ptr_data;
                    return const_iterator(_ptr_arr, _ptr_data + 1);
                }

                const T& operator* () const
                {
                    return *_ptr_data;
                }
            };

            array() : _size(0)
            {
            }

            array(const ps::array< T, SIZE >& arr) : _size(arr._size)
            {
                memcpy(_data, arr._data, arr.size() * sizeof(T));
            }

            array& operator= ( const array< T, SIZE >& arr )
            {
                memcpy(_data, arr._data, arr.size() * sizeof(T));
                _size = arr._size;
                return *this;
            }

            void push_back(T el)
            {
                if(_size < SIZE)
                {
                    *(_data + _size) = el;
                    ++_size;
                }
            }

            void pop_back()
            {
                if(_size)
                    --_size;
            }

            iterator begin()
            {
                return iterator(this, _data);
            }

            const_iterator begin() const
            {
                return const_iterator(this, _data);
            }

            iterator end()
            {
                return iterator(this, _data + _size);
            }

            const_iterator end() const
            {
                return const_iterator(this, _data + _size);
            }

            const T& front() const
            {
                return *_data;
            }

            const T& back() const
            {
                return *(_data + _size - bool(_size));
            }

            const bool empty() const
            {
                return bool(_size);
            }

            const uint32_t size() const
            {
                return _size;
            }

            void clear()
            {
                _size = 0;
            }

            void erase(iterator iter)
            {
                if(iter._ptr_data == nullptr || iter._ptr_data < _data || iter._ptr_data > (_data + _size))
                    return;
                if(iter._ptr_data > _data || iter._ptr_data < (_data + _size))
                    memcpy(iter._ptr_data, iter._ptr_data + 1, (_size - (iter._ptr_data - _data)) * sizeof(T));
                --_size;
            }

            const T* data() const
            {
                return _data;
            }

            void append(T* ptr_src, uint8_t num)
            {
                memcpy(_data + _size, ptr_src, num * sizeof(T));
            }
        };
}

#endif
