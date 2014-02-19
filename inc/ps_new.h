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

#ifndef PS_NEW_H
#define PS_NEW_H

#include <new>
#include <cstdlib>

namespace ps 
{
    template < class T >
        T* New()
        {
            void* p = malloc(sizeof(T));
            if(p)
            {
                new(p) T();
            }
            // TODO
            //else
            //{
            //    exception
            //}
            return (T*)p;
        }

    template < class T, typename... ARG >
        T* New(ARG... arg)
        {
            void* p = malloc(sizeof(T));
            if(p)
            {
                new(p) T(arg...);
            }
            // TODO
            //else
            //{
            //    exception
            //}
            return (T*)p;
        }

    template < class T >
        void Free(T* ptr)
        {
            if(ptr)
            {
                ptr->~T();
                free(ptr);
            }
        }
}

#endif
