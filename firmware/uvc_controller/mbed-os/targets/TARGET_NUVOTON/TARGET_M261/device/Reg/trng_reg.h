/**************************************************************************//**
 * @file     trng_reg.h
 * @version  V1.00
 * @brief    TRNG register definition header file
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Nuvoton Technology Corp. nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/
#ifndef __TRNG_REG_H__
#define __TRNG_REG_H__

/** @addtogroup REGISTER Control Register

  @{

*/

/*---------------------- True Random Number Generator -------------------------*/
/**
    @addtogroup TRNG True Random Number Generator(TRNG)
    Memory Mapped Structure for TRNG Controller
@{ */

typedef struct
{


    /**
     * @var TRNG_T::CTL
     * Offset: 0x00  TRNG Control Register and Status
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TRNGEN    |Random Number Generator Enable Bit
     * |        |          |This bit can be set to 1 only after ACT (TRNG_ACT[7]) bit was set to 1 and READY (TRNG_CTL[7]) bit became 1.
     * |        |          |0 = TRNG disabled.
     * |        |          |1 = TRNG enabled.
     * |        |          |Note: TRNGEN is an enable bit of digital part
     * |        |          |When TRNG is not required to generate random number, TRNGEN bit and ACT (TRNG_ACT[7]) bit should be set to 0 to reduce power consumption.
     * |[1]     |DVIF      |Data Valid (Read Only)
     * |        |          |0 = Data is not valid. Reading from RNGD returns 0x00000000.
     * |        |          |1 = Data is valid. A valid random number can be read form RNGD.
     * |        |          |This bit is cleared to u20180u2019 by read TRNG_DATA.
     * |[5:2]   |CLKP      |Clock Prescaler
     * |        |          |The CLKP is the peripheral clock frequency range for the selected value , the CLKP must higher than or equal to the actual peripheral clock frequency (for correct random bit generation)
     * |        |          |To change the CLKP contents, first set TRNGEN bit to 0 and then change CLKP; finally, set TRNGEN bit to 1 to re-enable the TRNG module.
     * |        |          |0000 = 80 ~ 100 MHz.
     * |        |          |0001 = 60 ~ 80 MHz.
     * |        |          |0010 = 50 ~60 MHz.
     * |        |          |0011 = 40 ~50 MHz.
     * |        |          |0100 = 30 ~40 MHz.
     * |        |          |0101 = 25 ~30 MHz.
     * |        |          |0110 = 20 ~25 MHz.
     * |        |          |0111 = 15 ~20 MHz.
     * |        |          |1000 = 12 ~15 MHz.
     * |        |          |1001 = 9 ~12 MHz.
     * |        |          |1010 = 7 ~9 MHz.
     * |        |          |1011 = 6 ~7 MHz.
     * |        |          |1100 = 5 ~6 MHz.
     * |        |          |1101 = 4 ~5 MHz.
     * |        |          |1111 = Reserved.
     * |[6]     |DVIEN     |Data Valid Interrupt Enable Bit
     * |        |          |0 = Interrupt disabled..
     * |        |          |1 = Interrupt enabled.
     * |[7]     |READY     |Random Number Generator Ready (Read Only)
     * |        |          |After ACT (TRNG_ACT[7]) bit is set, the READY bit become to 1 after a delay of 90us~120us.
     * |        |          |0 = RNG is not ready or was not activated.
     * |        |          |1 = RNG is ready to be enabled..
     * |[31:8]  |Reversed  |Reversed
     * @var TRNG_T::DATA
     * Offset: 0x04  TRNG Data Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DATA      |Random Number Generator Data (Read Only)
     * |        |          |The DATA store the random number generated by TRNG and can be read only once.
     * @var TRNG_T::ACT
     * Offset: 0x0C  TRNG Activation Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[6:0]   |VER       |TRNG Version
     * |        |          |TRNG version number is dependent on TRNG module.
     * |        |          |0x02:(Current Version Number)
     * |[7]     |ACT       |Random Number Generator Activation
     * |        |          |After enable the ACT bit, it will active the TRNG module and wait the READY (TRNG_CTL[7]) bit to become 1.
     * |        |          |0 = TRNG inactive.
     * |        |          |1 = TRNG active.
     * |        |          |Note: ACT is an enable bit of analog part
     * |        |          |When TRNG is not required to generate random number, TRNGEN (TRNG_CTL[0]) bit and ACT bit should be set to 0 to reduce power consumption.
     */
    __IO uint32_t CTL;                   /*!< [0x0000] TRNG Control Register and Status                                 */
    __I  uint32_t DATA;                  /*!< [0x0004] TRNG Data Register                                               */
    __I  uint32_t RESERVE0[1];
    __IO uint32_t ACT;                   /*!< [0x000c] TRNG Activation Register                                         */

} TRNG_T;

/**
    @addtogroup TRNG_CONST TRNG Bit Field Definition
    Constant Definitions for TRNG Controller
@{ */

#define TRNG_CTL_TRNGEN_Pos              (0)                                               /*!< TRNG_T::CTL: TRNGEN Position           */
#define TRNG_CTL_TRNGEN_Msk              (0x1ul << TRNG_CTL_TRNGEN_Pos)                    /*!< TRNG_T::CTL: TRNGEN Mask               */

#define TRNG_CTL_DVIF_Pos                (1)                                               /*!< TRNG_T::CTL: DVIF Position             */
#define TRNG_CTL_DVIF_Msk                (0x1ul << TRNG_CTL_DVIF_Pos)                      /*!< TRNG_T::CTL: DVIF Mask                 */

#define TRNG_CTL_CLKP_Pos                (2)                                               /*!< TRNG_T::CTL: CLKP Position             */
#define TRNG_CTL_CLKP_Msk                (0xful << TRNG_CTL_CLKP_Pos)                      /*!< TRNG_T::CTL: CLKP Mask                 */

#define TRNG_CTL_DVIEN_Pos               (6)                                               /*!< TRNG_T::CTL: DVIEN Position            */
#define TRNG_CTL_DVIEN_Msk               (0x1ul << TRNG_CTL_DVIEN_Pos)                     /*!< TRNG_T::CTL: DVIEN Mask                */

#define TRNG_CTL_READY_Pos               (7)                                               /*!< TRNG_T::CTL: READY Position            */
#define TRNG_CTL_READY_Msk               (0x1ul << TRNG_CTL_READY_Pos)                     /*!< TRNG_T::CTL: READY Mask                */

#define TRNG_CTL_Reversed_Pos            (8)                                               /*!< TRNG_T::CTL: Reversed Position         */
#define TRNG_CTL_Reversed_Msk            (0xfffffful << TRNG_CTL_Reversed_Pos)             /*!< TRNG_T::CTL: Reversed Mask             */

#define TRNG_DATA_DATA_Pos               (0)                                               /*!< TRNG_T::DATA: DATA Position            */
#define TRNG_DATA_DATA_Msk               (0xfful << TRNG_DATA_DATA_Pos)                    /*!< TRNG_T::DATA: DATA Mask                */

#define TRNG_ACT_VER_Pos                 (0)                                               /*!< TRNG_T::ACT: VER Position              */
#define TRNG_ACT_VER_Msk                 (0x7ful << TRNG_ACT_VER_Pos)                      /*!< TRNG_T::ACT: VER Mask                  */

#define TRNG_ACT_ACT_Pos                 (7)                                               /*!< TRNG_T::ACT: ACT Position              */
#define TRNG_ACT_ACT_Msk                 (0x1ul << TRNG_ACT_ACT_Pos)                       /*!< TRNG_T::ACT: ACT Mask                  */

/**@}*/ /* TRNG_CONST */
/**@}*/ /* end of TRNG register group */
/**@}*/ /* end of REGISTER group */


#endif /* __TRNG_REG_H__ */
