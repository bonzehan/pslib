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

#ifndef PS_GPIO_H
#define PS_GPIO_H

#include "misc.h"

#include "ps_stm32.h"

#if defined (STM32F10X_LD_VL) || (defined STM32F10X_MD_VL) || (defined STM32F10X_HD_VL)

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"


namespace ps
{
    namespace hw
    {
        namespace gpio
        {
            class gpio_a
            {
                gpio_a() = delete;

                public:

                static const uint32_t base    = GPIOA_BASE;
                static const uint32_t rcc_apb = RCC_APB2Periph_GPIOA;
            };

            class gpio_b
            {
                gpio_b() = delete;

                public:

                static const uint32_t base    = GPIOB_BASE;
                static const uint32_t rcc_apb = RCC_APB2Periph_GPIOB;
            };

            class gpio_c
            {
                gpio_c() = delete;

                public:

                static const uint32_t base    = GPIOC_BASE;
                static const uint32_t rcc_apb = RCC_APB2Periph_GPIOC;
            };

            class gpio_d
            {
                gpio_d() = delete;

                public:

                static const uint32_t base    = GPIOD_BASE;
                static const uint32_t rcc_apb = RCC_APB2Periph_GPIOD;
            };

            class gpio_e
            {
                gpio_e() = delete;

                public:

                static const uint32_t base    = GPIOE_BASE;
                static const uint32_t rcc_apb = RCC_APB2Periph_GPIOE;
            };

            class gpio_f
            {
                gpio_f() = delete;

                public:

                static const uint32_t base    = GPIOF_BASE;
                static const uint32_t rcc_apb = RCC_APB2Periph_GPIOF;
            };

            class gpio_g
            {
                gpio_g() = delete;

                public:

                static const uint32_t base    = GPIOG_BASE;
                static const uint32_t rcc_apb = RCC_APB2Periph_GPIOG;
            };

            enum mode : const uint8_t
            {
                mode_ain         = GPIO_Mode_AIN,
                mode_in_floating = GPIO_Mode_IN_FLOATING,
                mode_ipd         = GPIO_Mode_IPD,
                mode_ipu         = GPIO_Mode_IPU,
                mode_out_od      = GPIO_Mode_Out_OD,
                mode_out_pp      = GPIO_Mode_Out_PP,
                mode_af_of       = GPIO_Mode_AF_OD,
                mode_af_pp       = GPIO_Mode_AF_PP,
            };

            enum speed : const uint8_t
            {
                speed_10MHz = 1,
                speed_2MHz, 
                speed_50MHz,
            };

            template< class T >
                class gpio
                {
                    gpio() = delete;

                    public:

                    static void enable_clock()
                    {
                        RCC->APB2ENR |= T::rcc_apb;
                    }

                    static void disable_clock()
                    {
                        RCC->APB2ENR &= ~T::rcc_apb;
                    }

                    static void init(
                            ps::hw::gpio::speed speed,
                            ps::hw::gpio::mode mode,
                            ps::hw::pin pin)
                    {
                        // TODO
                        GPIO_InitTypeDef GPIO_InitStructure;
                        GPIO_InitStructure.GPIO_Pin = pin;
                        GPIO_InitStructure.GPIO_Speed = (GPIOSpeed_TypeDef)speed;
                        GPIO_InitStructure.GPIO_Mode = (GPIOMode_TypeDef)mode;
                        GPIO_Init((GPIO_TypeDef*)T::base, &GPIO_InitStructure);
                    }

                    static void init(
                            hw::gpio::speed speed,
                            hw::gpio::mode mode,
                            uint16_t pins)
                    {
                        // TODO
                        GPIO_InitTypeDef GPIO_InitStructure;
                        GPIO_InitStructure.GPIO_Pin = pins;
                        GPIO_InitStructure.GPIO_Speed = (GPIOSpeed_TypeDef)speed;
                        GPIO_InitStructure.GPIO_Mode = (GPIOMode_TypeDef)mode;
                        GPIO_Init((GPIO_TypeDef*)T::base, &GPIO_InitStructure);
                    }

                    static void deinit()
                    {
                        RCC->APB2RSTR |= T::rcc_apb;
                        RCC->APB2RSTR &= ~T::rcc_apb;
                    }
                };
        }
    }
}

#endif
#endif
