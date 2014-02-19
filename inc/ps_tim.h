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

#ifndef PS_TIM_H
#define PS_TIM_H

#include <functional>

#include "misc.h"

#include "ps_stm32.h"
#include "ps_event.h"

#if defined (STM32F10X_LD_VL) || (defined STM32F10X_MD_VL) || (defined STM32F10X_HD_VL)

#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "stm32f10x_tim.h"


namespace ps
{
    namespace hw
    {
        namespace tim
        {
            class tim_2
            {
                tim_2() = delete;

                public:

                static const uint32_t base = TIM1_BASE;
            };

            enum it : const uint16_t
            {
                it_update = TIM_IT_Update,
                it_cc_1 = TIM_IT_CC1,
                it_cc_2 = TIM_IT_CC2,
                it_cc_3 = TIM_IT_CC3,
                it_cc_4 = TIM_IT_CC4,
                it_com = TIM_IT_COM,
                it_trigger = TIM_IT_Trigger,
                it_break = TIM_IT_Break
            };

            template< class T >
                class tim
                {
                    tim() = delete;

                    public:

                    static void enable_clock()
                    {
                        RCC->APB1ENR |= RCC_APB1Periph;
                    }

                    static void disable_clock()
                    {
                        RCC->APB1ENR &= ~RCC_APB1Periph;
                    }

                    static void init()
                    {
                    }

                    static void deinit()
                    {
                    }
                };
        }
    }
}

#endif
#endif
