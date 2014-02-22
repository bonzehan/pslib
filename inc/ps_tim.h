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

#ifdef EVENT
#include <functional>
#endif

#include "misc.h"

#include "ps_stm32.h"
#include "ps_bus.h"

#if defined (STM32F10X_LD_VL) || (defined STM32F10X_MD_VL) || (defined STM32F10X_HD_VL)

#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "stm32f10x_tim.h"


namespace ps
{
    namespace tim
    {
        enum base : const uint32_t
        {
            base_tim_1  = TIM1_BASE,
            base_tim_2  = TIM2_BASE,
            base_tim_3  = TIM3_BASE,
            base_tim_4  = TIM4_BASE,
            base_tim_5  = TIM5_BASE,
            base_tim_6  = TIM6_BASE,
            base_tim_7  = TIM7_BASE,
            base_tim_8  = TIM8_BASE,
            base_tim_9  = TIM9_BASE,
            base_tim_10 = TIM10_BASE,
            base_tim_11 = TIM11_BASE,
            base_tim_12 = TIM12_BASE,
            base_tim_13 = TIM13_BASE,
            base_tim_14 = TIM14_BASE,
            base_tim_15 = TIM15_BASE,
            base_tim_16 = TIM16_BASE,
            base_tim_17 = TIM17_BASE,
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

        class _tim_1
        {
            _tim_1() = delete;

            public:

            static const ps::tim::base base = ps::tim::base::base_tim_1;
            static const ps::bus::apb_2::rcc_periph rcc_periph = ps::bus::apb_2::rcc_periph_tim_1;
        };

        class _tim_2
        {
            _tim_2() = delete;

            public:

            static const ps::tim::base base = ps::tim::base::base_tim_2;
            static const ps::bus::apb_1::rcc_periph rcc_periph = ps::bus::apb_1::rcc_periph_tim_2;
        };

        class _tim_3
        {
            _tim_3() = delete;

            public:

            static const ps::tim::base base = ps::tim::base::base_tim_3;
            static const ps::bus::apb_1::rcc_periph rcc_periph = ps::bus::apb_1::rcc_periph_tim_3;
        };

        class _tim_4
        {
            _tim_4() = delete;

            public:

            static const ps::tim::base base = ps::tim::base::base_tim_4;
            static const ps::bus::apb_1::rcc_periph rcc_periph = ps::bus::apb_1::rcc_periph_tim_4;
        };

        class _tim_6
        {
            _tim_6() = delete;

            public:

            static const ps::tim::base base = ps::tim::base::base_tim_6;
            static const ps::bus::apb_1::rcc_periph rcc_periph = ps::bus::apb_1::rcc_periph_tim_6;
        };

        class _tim_7
        {
            _tim_7() = delete;

            public:

            static const ps::tim::base base = ps::tim::base::base_tim_7;
            static const ps::bus::apb_1::rcc_periph rcc_periph = ps::bus::apb_1::rcc_periph_tim_7;
        };

        class _tim_15
        {
            _tim_15() = delete;

            public:

            static const ps::tim::base base = ps::tim::base::base_tim_15;
            static const ps::bus::apb_2::rcc_periph rcc_periph = ps::bus::apb_2::rcc_periph_tim_15;
        };

        class _tim_16
        {
            _tim_16() = delete;

            public:

            static const ps::tim::base base = ps::tim::base::base_tim_16;
            static const ps::bus::apb_2::rcc_periph rcc_periph = ps::bus::apb_2::rcc_periph_tim_16;
        };

        class _tim_17
        {
            _tim_17() = delete;

            public:

            static const ps::tim::base base = ps::tim::base::base_tim_17;
            static const ps::bus::apb_2::rcc_periph rcc_periph = ps::bus::apb_2::rcc_periph_tim_17;
        };

        template< class B, class T >
            class tim
            {
                tim() = delete;

                public:

                static void enable_clock()
                {
                    B::enable_clock(T::rcc_periph);
                }

                static void disable_clock()
                {
                    B::disable_clock(T::rcc_periph);
                }

                static void init(const uint32_t freq_hz, const uint32_t period) 
                {
                    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
                    TIM_TimeBaseStructure.TIM_Period = period; 

                    // Prescaler = (TIMCLK / TIM counter clock) - 1
                    // TIM counter clock = HCLK / APB_DIV * (1 or 2)
                    // TODO
                    RCC_ClocksTypeDef RCC_Clocks;
                    RCC_GetClocksFreq(&RCC_Clocks);

                    uint32_t tim_clk =
                        RCC_Clocks.HCLK_Frequency / (uint32_t)B::get_div();
                    if(B::get_div() != B::div::div_1)
                        tim_clk * 2;

                    TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t)(tim_clk / freq_hz - 1); 
                    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
                    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
                    TIM_TimeBaseInit((TIM_TypeDef*)T::base, &TIM_TimeBaseStructure);
                }

                static void deinit()
                {
                }
            };
    }

    typedef ps::tim::tim< ps::bus::apb_2, ps::tim::_tim_1 > tim_1;
    typedef ps::tim::tim< ps::bus::apb_1, ps::tim::_tim_2 > tim_2;
    typedef ps::tim::tim< ps::bus::apb_1, ps::tim::_tim_3 > tim_3;

}

#endif
#endif
