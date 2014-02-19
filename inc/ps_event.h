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

#ifndef PS_EVENT_H
#define PS_EVENT_H

#include <functional>

namespace ps 
{
    template< class > class event {};   
    template< typename _Res, typename... _ArgTypes >
        class event< _Res(_ArgTypes...) >
        {
            typedef ps::event< _Res(_ArgTypes...) > func_t;

            func_t _func;

            public: 

            event(): _func(nullptr)
            {
            }

            void operator() (_ArgTypes... arg)
            {
                if(_func)
                    _func(arg...);
            }

            event& operator= (func_t& func)
            {
                _func = func;
                return *this;
            }
        };
}

#endif
