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

#ifndef PS_SYS_TIMER_H
#define PS_SYS_TIMER_H

#include "ps_stm32.h"

namespace ps
{
    class sys
    {
        sys() = delete;

        static void __set_clock()
        {
            volatile uint32_t StartUpCounter = 0, HSEStatus = 0;

            // SYSCLK, HCLK, PCLK2 and PCLK1 configuration
            // Enable HSE
            RCC->CR |= ((uint32_t)RCC_CR_HSEON);

            // Wait till HSE is ready and if Time out is reached exit
            do
            {
                HSEStatus = RCC->CR & RCC_CR_HSERDY;
                StartUpCounter++;  
            } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

            if ((RCC->CR & RCC_CR_HSERDY) != RESET)
            {
                HSEStatus = (uint32_t)0x01;
            }
            else
            {
                HSEStatus = (uint32_t)0x00;
            }  

            if (HSEStatus == (uint32_t)0x01)
            {
                RCC->CFGR |= (uint32_t)ps::hw::ahb::div_1;
                RCC->CFGR |= (uint32_t)ps::hw::apb_1::div_1;
                RCC->CFGR |= (uint32_t)ps::hw::apb_2::div_1;

                // Set SYSCLK to 24MHz
                RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
                RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_PREDIV1 | RCC_CFGR_PLLXTPRE_PREDIV1_Div2 | RCC_CFGR_PLLMULL6);

                // Enable PLL
                RCC->CR |= RCC_CR_PLLON;

                // Wait till PLL is ready
                while((RCC->CR & RCC_CR_PLLRDY) == 0)
                {
                }

                // Select PLL as system clock source 
                RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
                RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

                // Wait till PLL is used as system clock source
                while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
                {
                }
            }
            else
            { 
                // If HSE fails to start-up, the application will have wrong clock
                // configuration. User can add here some code to deal with this error
            } 
        }

        static uint64_t& __tick()
        {
            static uint64_t tick;
            return tick;
        }

        static uint32_t& __tick_scale()
        {
            static uint32_t tickScale;
            return tickScale;
        }

        static uint32_t& __delay()
        {
            static uint32_t delay;
            return delay;
        }

        public:

        static void init()
        {
            // Reset the RCC clock configuration to the default reset state(for debug purpose)
            // Set HSION bit
            RCC->CR |= (uint32_t)0x00000001;

            // Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits
            RCC->CFGR &= (uint32_t)0xF8FF0000;

            // Reset HSEON, CSSON and PLLON bits
            RCC->CR &= (uint32_t)0xFEF6FFFF;

            // Reset HSEBYP bit
            RCC->CR &= (uint32_t)0xFFFBFFFF;

            // Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits
            RCC->CFGR &= (uint32_t)0xFF80FFFF;

            // Disable all interrupts and clear pending bits
            RCC->CIR = 0x009F0000;

            // Reset CFGR2 register
            RCC->CFGR2 = 0x00000000;      

            // Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers
            // Configure the Flash Latency cycles and enable prefetch buffer
            __set_clock();
        }

        static bool tick_init(uint32_t tickScale)
        {
            __tick_scale() = tickScale;

            RCC_ClocksTypeDef RCC_Clocks;
            RCC_GetClocksFreq(&RCC_Clocks);

            //SysTick_Config(RCC_Clocks.HCLK_Frequency / tickScale);

            uint32_t ticks = RCC_Clocks.HCLK_Frequency / tickScale;
            if(ticks > SysTick_LOAD_RELOAD_Msk) return false;
            SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;
            NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
            SysTick->VAL  = 0;
            SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | 
                SysTick_CTRL_TICKINT_Msk   | 
                SysTick_CTRL_ENABLE_Msk;
            return true;
        }

        static const uint64_t get_tick()
        {
            return __tick();
        }

        static const uint32_t get_tick_scale()
        {
            return __tick_scale();
        }

        static void tick_incr()
        {
            __tick()++;
            __delay()--;
        }

        static void sleep_ms(uint32_t ms)
        {
            __delay() = (ms * (get_tick_scale()>>2)) / 250; 
            while(__delay() != 0);
        }
    };
}

#endif
