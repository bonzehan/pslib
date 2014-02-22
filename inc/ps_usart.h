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

#ifndef PS_USART_H
#define PS_USART_H

#ifdef EVENT
#include <functional>
#include "ps_event.h"
#endif

#include "misc.h"

#include "ps_stm32.h"
#include "ps_dma.h"

#if defined (STM32F10X_LD_VL) || (defined STM32F10X_MD_VL) || (defined STM32F10X_HD_VL)


namespace ps
{
    namespace usart
    {
        enum base : const uint32_t
        {
            base_usart_1 = USART1_BASE,
            base_usart_2 = USART2_BASE,
            base_usart_3 = USART3_BASE,
            base_uart_4  = UART4_BASE,
            base_uart_5  = UART5_BASE,
        };

        enum it : const uint16_t
        {
            it_pe   = USART_IT_PE,
            it_txe  = USART_IT_TXE,
            it_tc   = USART_IT_TC,
            it_rxne = USART_IT_RXNE,
            it_idle = USART_IT_IDLE,
            it_lbd  = USART_IT_LBD,
            it_cts  = USART_IT_CTS,
            it_err  = USART_IT_ERR,
            it_ore  = USART_IT_ORE,
            it_ne   = USART_IT_NE,
            it_fe   = USART_IT_FE
        };

        enum irqn : const uint8_t
        {
            irqn_usart_1 = USART1_IRQn,
            irqn_usart_2 = USART2_IRQn,
            irqn_usart_3 = USART3_IRQn,
        };

        class _usart_1
        {
            _usart_1() = delete;

            public:

            static const ps::usart::base base = ps::usart::base::base_usart_1;
            static const ps::bus::apb_2::rcc_periph rcc_periph = ps::bus::apb_2::rcc_periph_usart_1;
            static const ps::usart::irqn irqn = ps::usart::irqn::irqn_usart_1;

            typedef dma_1_4 dma_tx;
            typedef dma_1_5 dma_rx;
        };

        class _usart_2
        {
            _usart_2() = delete;

            public:

            static const ps::usart::base base = ps::usart::base::base_usart_2;
            static const ps::bus::apb_1::rcc_periph rcc_periph = ps::bus::apb_1::rcc_periph_usart_2;
            static const ps::usart::irqn irqn = ps::usart::irqn::irqn_usart_2;

            typedef dma_1_7 dma_tx;
            typedef dma_1_6 dma_rx;
        };

        class _usart_3
        {
            _usart_3() = delete;

            public:

            static const ps::usart::base base = ps::usart::base::base_usart_3;
            static const ps::bus::apb_1::rcc_periph rcc_periph = ps::bus::apb_1::rcc_periph_usart_3;
            static const ps::usart::irqn irqn = ps::usart::irqn::irqn_usart_3;

            typedef dma_1_2 dma_tx;
            typedef dma_1_3 dma_rx;
        };

        template< class B, class T >
            class usart
            {
                usart() = delete;

                public:

                static void enable_clock()
                {
                    B::enable_clock(T::rcc_periph);
                }

                static void disable_clock()
                {
                    B::disable_clock(T::rcc_periph);
                }

                static void deinit()
                {
                    USART_DeInit((USART_TypeDef*)T::base);
                }

                static void init(
                        const uint32_t baud_rate = 9600,
                        const uint16_t word_length = USART_WordLength_8b,
                        const uint16_t stop_bits = USART_StopBits_1,
                        const uint16_t parity = USART_Parity_No,
                        const uint16_t hardware_flow_control = USART_HardwareFlowControl_None,
                        const uint16_t mode = USART_Mode_Tx | USART_Mode_Rx)
                {
                    USART_InitTypeDef USART_InitStructure;
                    USART_InitStructure.USART_BaudRate = baud_rate;
                    USART_InitStructure.USART_WordLength = word_length;
                    USART_InitStructure.USART_StopBits = stop_bits;
                    USART_InitStructure.USART_Parity = parity;
                    USART_InitStructure.USART_HardwareFlowControl = hardware_flow_control;
                    USART_InitStructure.USART_Mode = mode;
                    USART_Init((USART_TypeDef*)T::base, &USART_InitStructure);
                }

                static void init_nvic()
                {
                    NVIC_InitTypeDef NVIC_InitStructure;
                    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
                    NVIC_InitStructure.NVIC_IRQChannel = T::irqn;
                    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
                    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
                    NVIC_Init(&NVIC_InitStructure);
                }

                static void enable_it(ps::usart::it it)
                {
                    USART_ClearITPendingBit((USART_TypeDef*)T::base, it);
                    USART_ITConfig((USART_TypeDef*)T::base, it, ENABLE);
                }

                static void disable_it(ps::usart::it it)
                {
                    USART_ITConfig((USART_TypeDef*)T::base, it, DISABLE);
                }

                static void enable()
                {
                    USART_Cmd((USART_TypeDef*)T::base, ENABLE);
                }

                static void disable()
                {
                    USART_Cmd((USART_TypeDef*)T::base, DISABLE);
                }

                static void write(const uint8_t byte)
                {
                    while(USART_GetFlagStatus((USART_TypeDef*)T::base, USART_FLAG_TC) == RESET)
                    {
                    }
                    USART_SendData((USART_TypeDef*)T::base, byte);
                }

                static void write(const uint8_t* ptr_data, uint32_t size)
                {
                    while(size--)
                    {
                        write(*ptr_data); 
                        ++ptr_data;
                    }
                }

                static void write(const char* ptr_data)
                {
                    while(*ptr_data)
                    {
                        write((const uint8_t)(*ptr_data)); 
                        ++ptr_data;
                    }
                }

                static uint8_t read()
                {
                    //USART_ITConfig((USART_TypeDef*)T::base, usart< T >::it_rxne, DISABLE);
                    //while(USART_GetITStatus((USART_TypeDef*)T::base, usart::it_rxne) == RESET)
                    //{
                    //}
                    //USART_ITConfig((USART_TypeDef*)T::base, usart::it_rxne, ENABLE);
                    //return (uint8_t)USART_ReceiveData((USART_TypeDef*)T::base);
                }

                static bool byte_available()
                {
                    return (USART_GetITStatus((USART_TypeDef*)T::base, usart::it_rxne) == SET);
                }

                static void init_dma_tx()
                {
                    T::dma_tx::enable_clock();
                    T::dma_tx::init(
                            ps::dma::dir::prph_dst,
                            ps::dma::mode::normal,
                            ps::dma::incr::prph_incr_di,
                            ps::dma::incr::mem_incr_en,
                            ps::dma::size::byte,
                            ps::dma::size::byte,
                            ps::dma::priority::high,
                            ps::dma::m2m::m2m_di);
                    USART_DMACmd((USART_TypeDef*)T::base, USART_DMAReq_Tx, ENABLE);
                }

                static void write_dma(uint8_t* ptr_data, uint32_t size)
                {
                    T::dma_tx::init_data(
                            (uint32_t*)&(((USART_TypeDef*)T::base)->DR),
                            (uint32_t*)ptr_data,
                            size);
                    T::dma_tx::enable();
                }
#ifdef EVENT
                static std::function< void(void) >    tx_ev;
                static std::function< void(uint8_t) > rx_ev;
                static std::function< void(void) >    dma_ht_ev;
                static std::function< void(void) >    dma_tc_ev;
                static std::function< void(void) >    dma_er_ev;
#endif
            };

#ifdef EVENT
        template< class T >
            std::function< void(void) >    ps::usart< B, T >::tx_ev = nullptr;
        template< class T >
            std::function< void(uint8_t) > ps::usart< B, T >::rx_ev = nullptr;
        template< class T >
            std::function< void(void) >    ps::usart< B, T >::dma_ht_ev = nullptr;
        template< class T >
            std::function< void(void) >    ps::usart< B, T >::dma_tc_ev = nullptr;
        template< class T >
            std::function< void(void) >    ps::usart< B, T >::dma_er_ev = nullptr;
#endif
    }

    typedef ps::usart::usart< ps::bus::apb_2, ps::usart::_usart_1 > usart_1;
    typedef ps::usart::usart< ps::bus::apb_1, ps::usart::_usart_2 > usart_2;
    typedef ps::usart::usart< ps::bus::apb_1, ps::usart::_usart_3 > usart_3;

}

#endif
#endif
