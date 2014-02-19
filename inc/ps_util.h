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

#ifndef PS_UTIL_H
#define PS_UTIL_H


namespace ps
{
    namespace util
    {
        char* itoa32(char* pBuff, int32_t value, int8_t width = 0)
        {
            if(value >= 0)
            {
                pBuff[10] = '\0';
                for(uint8_t i = 9; i >= 0; --i)
                {
                    int32_t tmp_value = value;
                    value /= 10;
                    pBuff[i] = "0123456789"[tmp_value - value * 10];
                    if(value == 0 and 10 - i >= width)
                        return pBuff + i;
                }
            }
            else
            {
                value = -value;
                width -= 1;
                pBuff[11] = '\0';
                for(uint8_t i = 10; i > 0; --i)
                {
                    int32_t tmp_value = value;
                    value /= 10;
                    pBuff[i] = "0123456789"[tmp_value - value * 10];
                    if(value == 0 and 11 - i >= width)
                    {
                        pBuff[i-1] = '-';
                        return pBuff + i - 1;
                    }
                }
            }
        }
    }
}

#endif
