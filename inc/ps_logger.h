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

#ifndef PS_LOG_H
#define PS_LOG_H

#include "ps_util.h"

namespace ps
{
    namespace log
    {
        enum level : uint8_t
        {
            critical = 0,
            error    = 1,
            warning  = 2,
            info     = 3,
            debug    = 4
        };

        template< class I >
            class logger
            {
                char* _prompt;
                uint8_t _level;

                void _print(const char level, const char* pBuff) const
                {
                    I::write((uint8_t)'[');
                    char time[16];
                    I::write(ps::util::itoa32(time, ps::sys::get_tick(), 10));
                    I::write(']');
                    I::write(' ');
                    I::write(_prompt);
                    I::write(' ');
                    I::write('[');
                    I::write(level);
                    I::write(']');
                    I::write(' ');
                    I::write(pBuff);
                    I::write('\n');
                }

                public:

                logger(char* prompt="", ps::log::level level=ps::log::critical):
                    _prompt(prompt), _level(level)
                {
                }

                void set_prompt(char* prompt)
                {
                    _prompt = prompt;
                }

                void set_level(ps::log::level level)
                {
                    _level = level;
                }

                void critical(const char* pBuff) const
                {
                    if(_level >= ps::log::critical)
                    {
                        _print('C', pBuff);
                    }
                }

                void error(const char* pBuff) const
                {
                    if(_level >= ps::log::error)
                    {
                        _print('E', pBuff);
                    }
                }

                void warning(const char* pBuff) const
                {
                    if(_level >= ps::log::warning)
                    {
                        _print('W', pBuff);
                    }
                }

                void info(const char* pBuff) const
                {
                    if(_level >= ps::log::info)
                    {
                        _print('I', pBuff);
                    }
                }

                void debug(const char* pBuff) const
                {
                    if(_level >= ps::log::debug)
                    {
                        _print('D', pBuff);
                    }
                }
            };
    }
}

#endif
