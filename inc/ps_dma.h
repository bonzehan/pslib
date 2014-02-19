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

#ifndef PS_DMA_H
#define PS_DMA_H

#include "misc.h"

#include "ps_stm32.h"

#if defined (STM32F10X_LD_VL) || (defined STM32F10X_MD_VL) || (defined STM32F10X_HD_VL)

#include "stm32f10x_dma.h"


namespace ps
{
    namespace hw
    {
        namespace dma
        {
            class dma_1_1
            {
                dma_1_1() = delete;

                public:

                static const uint32_t base    = DMA1_BASE;
                static const uint32_t base_ch = DMA1_Channel1_BASE;
                static const uint32_t rcc_ahb = RCC_AHBPeriph_DMA1;
                static const uint32_t it_mask = 
                    (uint32_t)(DMA_ISR_GIF1 | DMA_ISR_TCIF1 | DMA_ISR_HTIF1 | DMA_ISR_TEIF1);
            };

            class dma_1_2
            {
                dma_1_2() = delete;

                public:

                static const uint32_t base    = DMA1_BASE;
                static const uint32_t base_ch = DMA1_Channel2_BASE;
                static const uint32_t rcc_ahb = RCC_AHBPeriph_DMA1;
                static const uint32_t it_mask = 
                    (uint32_t)(DMA_ISR_GIF2 | DMA_ISR_TCIF2 | DMA_ISR_HTIF2 | DMA_ISR_TEIF2);
            };

            class dma_1_3
            {
                dma_1_3() = delete;

                public:

                static const uint32_t base    = DMA1_BASE;
                static const uint32_t base_ch = DMA1_Channel3_BASE;
                static const uint32_t rcc_ahb = RCC_AHBPeriph_DMA1;
                static const uint32_t it_mask = 
                    (uint32_t)(DMA_ISR_GIF3 | DMA_ISR_TCIF3 | DMA_ISR_HTIF3 | DMA_ISR_TEIF3);
            };

            class dma_1_4
            {
                dma_1_4() = delete;

                public:

                static const uint32_t base    = DMA1_BASE;
                static const uint32_t base_ch = DMA1_Channel4_BASE;
                static const uint32_t rcc_ahb = RCC_AHBPeriph_DMA1;
                static const uint32_t it_mask = 
                    (uint32_t)(DMA_ISR_GIF4 | DMA_ISR_TCIF4 | DMA_ISR_HTIF4 | DMA_ISR_TEIF4);
            };

            class dma_1_5
            {
                dma_1_5() = delete;

                public:

                static const uint32_t base    = DMA1_BASE;
                static const uint32_t base_ch = DMA1_Channel5_BASE;
                static const uint32_t rcc_ahb = RCC_AHBPeriph_DMA1;
                static const uint32_t it_mask = 
                    (uint32_t)(DMA_ISR_GIF5 | DMA_ISR_TCIF5 | DMA_ISR_HTIF5 | DMA_ISR_TEIF5);
            };

            class dma_1_6
            {
                dma_1_6() = delete;

                public:

                static const uint32_t base    = DMA1_BASE;
                static const uint32_t base_ch = DMA1_Channel6_BASE;
                static const uint32_t rcc_ahb = RCC_AHBPeriph_DMA1;
                static const uint32_t it_mask = 
                    (uint32_t)(DMA_ISR_GIF6 | DMA_ISR_TCIF6 | DMA_ISR_HTIF6 | DMA_ISR_TEIF6);
            };

            class dma_1_7
            {
                dma_1_7() = delete;

                public:

                static const uint32_t base    = DMA1_BASE;
                static const uint32_t base_ch = DMA1_Channel7_BASE;
                static const uint32_t rcc_ahb = RCC_AHBPeriph_DMA1;
                static const uint32_t it_mask = 
                    (uint32_t)(DMA_ISR_GIF7 | DMA_ISR_TCIF7 | DMA_ISR_HTIF7 | DMA_ISR_TEIF7);
            };

#ifdef STM32F10X_HD_VL
            class dma_2_1
            {
                dma_2_1() = delete;

                public:

                static const uint32_t base    = DMA2_BASE;
                static const uint32_t base_ch = DMA2_Channel1_BASE;
                static const uint32_t rcc_ahb = RCC_AHBPeriph_DMA2;
                static const uint32_t it_mask = 
                    (uint32_t)(DMA_ISR_GIF1 | DMA_ISR_TCIF1 | DMA_ISR_HTIF1 | DMA_ISR_TEIF1);
            };

            class dma_2_2
            {
                dma_2_2() = delete;

                public:

                static const uint32_t base    = DMA2_BASE;
                static const uint32_t base_ch = DMA2_Channel2_BASE;
                static const uint32_t rcc_ahb = RCC_AHBPeriph_DMA2;
                static const uint32_t it_mask = 
                    (uint32_t)(DMA_ISR_GIF2 | DMA_ISR_TCIF2 | DMA_ISR_HTIF2 | DMA_ISR_TEIF2);
            };

            class dma_2_3
            {
                dma_2_3() = delete;

                public:

                static const uint32_t base    = DMA2_BASE;
                static const uint32_t base_ch = DMA2_Channel3_BASE;
                static const uint32_t rcc_ahb = RCC_AHBPeriph_DMA2;
                static const uint32_t it_mask = 
                    (uint32_t)(DMA_ISR_GIF3 | DMA_ISR_TCIF3 | DMA_ISR_HTIF3 | DMA_ISR_TEIF3);
            };

            class dma_2_4
            {
                dma_2_4() = delete;

                public:

                static const uint32_t base    = DMA2_BASE;
                static const uint32_t base_ch = DMA2_Channel4_BASE;
                static const uint32_t rcc_ahb = RCC_AHBPeriph_DMA2;
                static const uint32_t it_mask = 
                    (uint32_t)(DMA_ISR_GIF4 | DMA_ISR_TCIF4 | DMA_ISR_HTIF4 | DMA_ISR_TEIF4);
            };

            class dma_2_5
            {
                dma_2_5() = delete;

                public:

                static const uint32_t base    = DMA2_BASE;
                static const uint32_t base_ch = DMA2_Channel5_BASE;
                static const uint32_t rcc_ahb = RCC_AHBPeriph_DMA2;
                static const uint32_t it_mask = 
                    (uint32_t)(DMA_ISR_GIF5 | DMA_ISR_TCIF5 | DMA_ISR_HTIF5 | DMA_ISR_TEIF5);
            };
#endif

            enum dir : const uint32_t
            {
                prph_dst = DMA_DIR_PeripheralDST,
                prph_src = DMA_DIR_PeripheralSRC,
            };

            enum incr : const uint32_t
            {
                prph_incr_en = DMA_PeripheralInc_Enable,
                prph_incr_di = DMA_PeripheralInc_Disable,
                mem_incr_en  = DMA_MemoryInc_Enable,
                mem_incr_di  = DMA_MemoryInc_Disable,
            };

            enum mode : const uint32_t
            {
                circul = DMA_Mode_Circular,
                normal = DMA_Mode_Normal,
            };

            enum size : const uint32_t
            {
                byte = DMA_MemoryDataSize_Byte,
                half = DMA_MemoryDataSize_HalfWord,
                word = DMA_MemoryDataSize_Word,
            };

            enum priority : const uint32_t
            {
                very_high = DMA_Priority_VeryHigh,
                high      = DMA_Priority_High,
                medium    = DMA_Priority_Medium,
                low       = DMA_Priority_Low,
            };

            enum m2m : const uint32_t
            {
                m2m_en = DMA_M2M_Enable,
                m2m_di = DMA_M2M_Disable,
            };

            template < class T >
                class dma
                {
                    dma() = delete;

                    public:

                    static void enable_clock()
                    {
                        RCC->AHBENR |= T::rcc_ahb;
                    }

                    static void disable_clock()
                    {
                        RCC->AHBENR &= ~T::rcc_ahb;
                    }

                    static void init(
                            hw::dma::dir dir,
                            hw::dma::mode mode,
                            hw::dma::incr prph_incr,
                            hw::dma::incr mem_incr,
                            hw::dma::size prph_size,
                            hw::dma::size mem_size,
                            hw::dma::priority priority,
                            hw::dma::m2m m2m)
                    {
                        uint32_t tmpreg = 0x0;
                        tmpreg = ((DMA_Channel_TypeDef*)T::base_ch)->CCR;
                        tmpreg &= (uint32_t)0xFFFF800F;
                        tmpreg |= dir | mode | prph_incr | mem_incr |
                            prph_size | mem_size | priority | m2m;

                        ((DMA_Channel_TypeDef*)T::base_ch)->CCR = tmpreg;
                    }

                    static void deinit()
                    {
                        (DMA_Channel_TypeDef*)T::dma_ch_base->CCR   &= (uint16_t)(~DMA_CCR1_EN);
                        (DMA_Channel_TypeDef*)T::dma_ch_base->CCR   = 0;
                        (DMA_Channel_TypeDef*)T::dma_ch_base->CNDTR = 0;
                        (DMA_Channel_TypeDef*)T::dma_ch_base->CPAR  = 0;
                        (DMA_Channel_TypeDef*)T::dma_ch_base->CMAR  = 0;
                        (DMA_TypeDef*)T::dma_base-> IFCR |= T::it_mask;
                    }

                    static void init_data(
                            uint32_t* prph_base_addr,
                            uint32_t* mem_base_addr,
                            uint32_t size)
                    {
                        ((DMA_Channel_TypeDef*)T::base_ch)->CNDTR = size;
                        ((DMA_Channel_TypeDef*)T::base_ch)->CPAR = (uint32_t)prph_base_addr;
                        ((DMA_Channel_TypeDef*)T::base_ch)->CMAR = (uint32_t)mem_base_addr;
                    }

                    static void enable()
                    {
                        ((DMA_Channel_TypeDef*)T::base_ch)->CCR |= DMA_CCR1_EN;
                    }

                    static void disable()
                    {
                        ((DMA_Channel_TypeDef*)T::base_ch)->CCR &= (uint16_t)(~DMA_CCR1_EN);
                    }
                };
        }
    }
}

#endif
#endif
