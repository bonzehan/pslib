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
#include "ps_bus.h"

#if defined (STM32F10X_LD_VL) || (defined STM32F10X_MD_VL) || (defined STM32F10X_HD_VL)


namespace ps
{
    namespace gpio
    {
        enum base : const uint32_t
        {
            base_gpio_a = GPIOA_BASE,
            base_gpio_b = GPIOB_BASE,
            base_gpio_c = GPIOC_BASE,
            base_gpio_d = GPIOD_BASE,
            base_gpio_e = GPIOE_BASE,
            base_gpio_f = GPIOF_BASE,
            base_gpio_g = GPIOG_BASE,
        };

        class _gpio_a
        {
            _gpio_a() = delete;

            public:

            static const ps::gpio::base base = ps::gpio::base::base_gpio_a;
            static const ps::bus::apb_2::rcc_periph rcc_periph = 
                ps::bus::apb_2::rcc_periph::rcc_periph_gpio_a;
        };

        class _gpio_b
        {
            _gpio_b() = delete;

            public:

            static const ps::gpio::base base = ps::gpio::base::base_gpio_b;
            static const ps::bus::apb_2::rcc_periph rcc_periph = 
                ps::bus::apb_2::rcc_periph::rcc_periph_gpio_b;
        };

        class _gpio_c
        {
            _gpio_c() = delete;

            public:

            static const ps::gpio::base base = ps::gpio::base::base_gpio_c;
            static const ps::bus::apb_2::rcc_periph rcc_periph = 
                ps::bus::apb_2::rcc_periph::rcc_periph_gpio_c;
        };

        class _gpio_d
        {
            _gpio_d() = delete;

            public:

            static const ps::gpio::base base = ps::gpio::base::base_gpio_d;
            static const ps::bus::apb_2::rcc_periph rcc_periph = 
                ps::bus::apb_2::rcc_periph::rcc_periph_gpio_d;
        };

        class _gpio_e
        {
            _gpio_e() = delete;

            public:

            static const ps::gpio::base base = ps::gpio::base::base_gpio_e;
            static const ps::bus::apb_2::rcc_periph rcc_periph = 
                ps::bus::apb_2::rcc_periph::rcc_periph_gpio_e;
        };

        class _gpio_f
        {
            _gpio_f() = delete;

            public:

            static const ps::gpio::base base = ps::gpio::base::base_gpio_f;
            static const ps::bus::apb_2::rcc_periph rcc_periph = 
                ps::bus::apb_2::rcc_periph::rcc_periph_gpio_f;
        };

        class _gpio_g
        {
            _gpio_g() = delete;

            public:

            static const ps::gpio::base base = ps::gpio::base::base_gpio_g;
            static const ps::bus::apb_2::rcc_periph rcc_periph = 
                ps::bus::apb_2::rcc_periph::rcc_periph_gpio_g;
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
                    ps::bus::apb_2::enable_clock(T::rcc_periph);
                }

                static void disable_clock()
                {
                    ps::bus::apb_2::disable_clock(T::rcc_periph);
                }

                static void init(
                        ps::gpio::speed speed,
                        ps::gpio::mode mode,
                        ps::pin pin)
                {
                    // TODO
                    GPIO_InitTypeDef GPIO_InitStructure;
                    GPIO_InitStructure.GPIO_Pin = pin;
                    GPIO_InitStructure.GPIO_Speed = (GPIOSpeed_TypeDef)speed;
                    GPIO_InitStructure.GPIO_Mode = (GPIOMode_TypeDef)mode;
                    GPIO_Init((GPIO_TypeDef*)T::base, &GPIO_InitStructure);
                }

                static void init(
                        ps::gpio::speed speed,
                        ps::gpio::mode mode,
                        uint32_t pin)
                {
                    // TODO
                    GPIO_InitTypeDef GPIO_InitStructure;
                    GPIO_InitStructure.GPIO_Pin = pin;
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

    typedef ps::gpio::gpio< ps::gpio::_gpio_a > gpio_a;
    typedef ps::gpio::gpio< ps::gpio::_gpio_b > gpio_b;
    typedef ps::gpio::gpio< ps::gpio::_gpio_c > gpio_c;
    typedef ps::gpio::gpio< ps::gpio::_gpio_d > gpio_d;
    typedef ps::gpio::gpio< ps::gpio::_gpio_e > gpio_e;
    typedef ps::gpio::gpio< ps::gpio::_gpio_f > gpio_f;
    typedef ps::gpio::gpio< ps::gpio::_gpio_g > gpio_g;

}

#endif
#endif
