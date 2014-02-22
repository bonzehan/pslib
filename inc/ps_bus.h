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

#ifndef PS_BUS_H
#define PS_BUS_H

#include "ps_stm32.h"


namespace ps
{
    namespace bus
    {
        class ahb
        {
            ahb() = delete;

            static uint16_t& __div()
            {
                static uint16_t div;
                return div;
            }

            public:

            enum div : const uint32_t
            {
                div_1   = 1,
                div_2   = 2,
                div_4   = 4,
                div_8   = 8,
                div_16  = 16,
                div_64  = 64,
                div_128 = 128,
                div_256 = 256,
                div_512 = 512,
            };

            enum rcc_periph : const uint32_t
            {
                rcc_periph_dma1       = RCC_AHBPeriph_DMA1,
                rcc_periph_dma2       = RCC_AHBPeriph_DMA2,
                rcc_periph_sram       = RCC_AHBPeriph_SRAM,
                rcc_periph_flitf      = RCC_AHBPeriph_FLITF,
                rcc_periph_crc        = RCC_AHBPeriph_CRC,
#ifndef STM32F10X_CL
                rcc_periph_FSMC       = RCC_AHBPeriph_FSMC,
                rcc_periph_SDIO       = RCC_AHBPeriph_SDIO,
#else
                rcc_periph_OTG_FS     = RCC_AHBPeriph_OTG_FS, 
                rcc_periph_ETH_MAC    = RCC_AHBPeriph_ETH_MAC, 
                rcc_periph_ETH_MAC_Tx = RCC_AHBPeriph_ETH_MAC_Tx, 
                rcc_periph_ETH_MAC_Rx = RCC_AHBPeriph_ETH_MAC_Rx, 
#endif
            };

            static void set_div(ps::bus::ahb::div div)
            {
                __div() = (uint16_t)div;
            }

            static const ps::bus::ahb::div get_div()
            {
                return (ps::bus::ahb::div)__div();
            }

            static const uint32_t get_raw_div()
            {
                switch((uint32_t)__div())
                {
                    case 1:
                        return RCC_CFGR_HPRE_DIV1;
                    case 2:
                        return RCC_CFGR_HPRE_DIV2;
                    case 4:
                        return RCC_CFGR_HPRE_DIV4; 
                    case 8:
                        return RCC_CFGR_HPRE_DIV8;
                    case 16:
                        return RCC_CFGR_HPRE_DIV16;
                    case 64:
                        return RCC_CFGR_HPRE_DIV64;
                    case 128:
                        return RCC_CFGR_HPRE_DIV128;
                    case 256:
                        return RCC_CFGR_HPRE_DIV256;
                    case 512:
                        return RCC_CFGR_HPRE_DIV512;
                    default:
                        return RCC_CFGR_HPRE_DIV1;
                }
            }

            static void enable_clock(ps::bus::ahb::rcc_periph rcc_periph)
            {
                RCC->AHBENR |= rcc_periph;
            }

            static void disable_clock(ps::bus::ahb::rcc_periph rcc_periph)
            {
                RCC->AHBENR &= ~rcc_periph;
            }
        };

        class apb_1
        {
            apb_1() = delete;

            static uint8_t& __div()
            {
                static uint8_t div;
                return div;
            }

            public:

            enum div : const uint8_t
            {
                div_1  = 1,
                div_2  = 2,
                div_4  = 4,
                div_8  = 8,
                div_16 = 16,
            };

            enum rcc_periph : const uint32_t
            {
                rcc_periph_tim_2   = RCC_APB1Periph_TIM2,
                rcc_periph_tim_3   = RCC_APB1Periph_TIM3,
                rcc_periph_tim_4   = RCC_APB1Periph_TIM4,
                rcc_periph_tim_5   = RCC_APB1Periph_TIM5,
                rcc_periph_tim_6   = RCC_APB1Periph_TIM6,
                rcc_periph_tim_7   = RCC_APB1Periph_TIM7,
                rcc_periph_tim_12  = RCC_APB1Periph_TIM12 ,
                rcc_periph_tim_13  = RCC_APB1Periph_TIM13 ,
                rcc_periph_tim_14  = RCC_APB1Periph_TIM14 ,
                rcc_periph_wwdg    = RCC_APB1Periph_WWDG,
                rcc_periph_spi_2   = RCC_APB1Periph_SPI2,
                rcc_periph_spi_3   = RCC_APB1Periph_SPI3,
                rcc_periph_usart_2 = RCC_APB1Periph_USART2,
                rcc_periph_usart_3 = RCC_APB1Periph_USART3,
                rcc_periph_uart_4  = RCC_APB1Periph_UART4,
                rcc_periph_uart_5  = RCC_APB1Periph_UART5,
                rcc_periph_i2c_1   = RCC_APB1Periph_I2C1,
                rcc_periph_i2c_2   = RCC_APB1Periph_I2C2,
                rcc_periph_usb     = RCC_APB1Periph_USB,
                rcc_periph_can_1   = RCC_APB1Periph_CAN1,
                rcc_periph_can_2   = RCC_APB1Periph_CAN2,
                rcc_periph_bkp     = RCC_APB1Periph_BKP,
                rcc_periph_pwr     = RCC_APB1Periph_PWR,
                rcc_periph_dac     = RCC_APB1Periph_DAC,
                rcc_periph_cec     = RCC_APB1Periph_CEC,
            };

            static void set_div(ps::bus::apb_1::div div)
            {
                __div() = (uint8_t)div;
            }

            static const ps::bus::apb_1::div get_div()
            {
                return (ps::bus::apb_1::div)__div();
            }

            static const uint32_t get_raw_div()
            {
                switch((uint32_t)__div())
                {
                    case 1:
                        return RCC_CFGR_PPRE1_DIV1;
                    case 2:
                        return RCC_CFGR_PPRE1_DIV2;
                    case 4:
                        return RCC_CFGR_PPRE1_DIV4;
                    case 8:
                        return RCC_CFGR_PPRE1_DIV8;
                    case 16:
                        return RCC_CFGR_PPRE1_DIV16;
                }
            }

            static void enable_clock(ps::bus::apb_1::rcc_periph rcc_periph)
            {
                RCC->APB1ENR |= rcc_periph;
            }

            static void disable_clock(ps::bus::apb_1::rcc_periph rcc_periph)
            {
                RCC->APB1ENR &= ~rcc_periph;
            }
        };

        class apb_2
        {
            apb_2() = delete;

            static uint8_t& __div()
            {
                static uint8_t div;
                return div;
            }

            public:

            enum div : const uint8_t
            {
                div_1  = 1,
                div_2  = 2,
                div_4  = 4,
                div_8  = 8,
                div_16 = 16,
            };

            enum rcc_periph : const uint32_t
            {
                rcc_periph_afio    = RCC_APB2Periph_AFIO,
                rcc_periph_gpio_a  = RCC_APB2Periph_GPIOA,
                rcc_periph_gpio_b  = RCC_APB2Periph_GPIOB,
                rcc_periph_gpio_c  = RCC_APB2Periph_GPIOC,
                rcc_periph_gpio_d  = RCC_APB2Periph_GPIOD,
                rcc_periph_gpio_e  = RCC_APB2Periph_GPIOE,
                rcc_periph_gpio_f  = RCC_APB2Periph_GPIOF,
                rcc_periph_gpio_g  = RCC_APB2Periph_GPIOG,
                rcc_periph_adc_1   = RCC_APB2Periph_ADC1,
                rcc_periph_adc_2   = RCC_APB2Periph_ADC2,
                rcc_periph_tim_1   = RCC_APB2Periph_TIM1,
                rcc_periph_spi_1   = RCC_APB2Periph_SPI1,
                rcc_periph_tim_8   = RCC_APB2Periph_TIM8,
                rcc_periph_usart_1 = RCC_APB2Periph_USART1,
                rcc_periph_adc_3   = RCC_APB2Periph_ADC3,
                rcc_periph_tim_15  = RCC_APB2Periph_TIM15,
                rcc_periph_tim_16  = RCC_APB2Periph_TIM16,
                rcc_periph_tim_17  = RCC_APB2Periph_TIM17,
                rcc_periph_tim_9   = RCC_APB2Periph_TIM9,
                rcc_periph_tim_10  = RCC_APB2Periph_TIM10,
                rcc_periph_tim_11  = RCC_APB2Periph_TIM11,
            };

            static void set_div(ps::bus::apb_2::div div)
            {
                __div() = (uint8_t)div;
            }

            static const ps::bus::apb_2::div get_div()
            {
                return (ps::bus::apb_2::div)__div();
            }

            static const uint32_t get_raw_div()
            {
                switch((uint32_t)__div())
                {
                    case 1:
                        return RCC_CFGR_PPRE2_DIV1;
                    case 2:
                        return RCC_CFGR_PPRE2_DIV2;
                    case 4:
                        return RCC_CFGR_PPRE2_DIV4;
                    case 8:
                        return RCC_CFGR_PPRE2_DIV8;
                    case 16:
                        return RCC_CFGR_PPRE2_DIV16;
                }
            }

            static void enable_clock(ps::bus::apb_2::rcc_periph rcc_periph)
            {
                RCC->APB2ENR |= rcc_periph;
            }

            static void disable_clock(ps::bus::apb_2::rcc_periph rcc_periph)
            {
                RCC->APB2ENR &= ~rcc_periph;
            }
        };
    }
}

#endif
