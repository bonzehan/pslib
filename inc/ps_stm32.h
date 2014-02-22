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

#ifndef PS_STM32F10X_H
#define PS_STM32F10X_H

#if defined (STM32F10X_LD_VL) || (defined STM32F10X_MD_VL) || (defined STM32F10X_HD_VL)

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

namespace ps
{
    enum pin : const uint16_t
    {
        pin_0   = GPIO_Pin_0,
        pin_1   = GPIO_Pin_1,
        pin_2   = GPIO_Pin_2,
        pin_3   = GPIO_Pin_3,
        pin_4   = GPIO_Pin_4,
        pin_5   = GPIO_Pin_5,
        pin_6   = GPIO_Pin_6,
        pin_7   = GPIO_Pin_7,
        pin_8   = GPIO_Pin_8,
        pin_9   = GPIO_Pin_9,
        pin_10  = GPIO_Pin_10,
        pin_11  = GPIO_Pin_11,
        pin_12  = GPIO_Pin_12,
        pin_13  = GPIO_Pin_13,
        pin_14  = GPIO_Pin_14,
        pin_15  = GPIO_Pin_15,
        pin_All = GPIO_Pin_All
    };
}

#endif
#endif
