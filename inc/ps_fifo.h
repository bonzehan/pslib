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

#ifndef PS_FIFO_H
#define PS_FIFO_H

namespace ps
{
    template< typename T, uint16_t SIZE >
        class fifo
        {
            T _data[SIZE];
            T* _frst_ptr;
            T* _last_ptr;

            public:

            fifo() : _frst_ptr(_data), _last_ptr(_data)
            {
            }

            bool empty()
            {
                return _last_ptr == _frst_ptr;
            }

            bool full()
            {
                return _last_ptr - _frst_ptr == SIZE;
            }

            T pop()
            {
                if(_last_ptr - frst_ptr)
                {
                    return *_frst_ptr++;
                }
                return nullptr;
            }

            void put(T o)
            {
                uint16_t offset = _last_ptr - _frst_ptr;
                if(_last_ptr = _data + SIZE)
                {
                    if(offset < SIZE)
                    {
                        memcpy(_data, _frst_ptr, _last_ptr - _frst_ptr)
                            _frst_ptr = _data;
                        _last_ptr = _data + offset;
                        ++_last_ptr;
                        *_last_ptr = o;
                    }
                }
                else
                {
                    ++_last_ptr;
                    *_last_ptr = o;
                }
            }
        };
}

#endif
