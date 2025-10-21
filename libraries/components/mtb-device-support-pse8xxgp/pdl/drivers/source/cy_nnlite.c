/***************************************************************************//**
* \file   cy_nnlite.c
* \version 1.0
*
*
* Provides an API implementation of the nn lite accelerator driver.
*
*
*  Patched to support PDL emulation (including on 64-bit hosts)
*
********************************************************************************
* \copyright
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/
#include "cy_device.h"
#if defined (CY_IP_MXNNLITE)

#include "cy_nnlite.h"

#if defined(IFX_USE_MXNNLITE_STREAM_EMU)
    #include "cy_nnlite_pdl_emu.h"
#endif

#if defined(__cplusplus)
extern "C" {
#endif


#if CY_IP_MXNNLITE_VERSION==1
#define   STATUS_REG_MASK (MXNNLITE_1_0_STATUS_BUSY_STATUS_Msk | \
           MXNNLITE_1_0_STATUS_ACTIVATIONSTREAMERDONE_Msk)

#define NNLITE_VAL2FLD(field, value) _VAL2FLD(MXNNLITE_1_0_##field, value)
#define MXNNLITE_REGS      ((MXNNLITE_1_0_Type*) MXNNLITE_1_0_BASE)
#else
#define   STATUS_REG_MASK (MXNNLITE_2_0_STATUS_BUSY_STATUS_Msk | \
           MXNNLITE_2_0_STATUS_ACTIVATIONSTREAMERDONE_Msk)

#define NNLITE_VAL2FLD(field, value) _VAL2FLD(MXNNLITE_2_0_##field, value)
#define MXNNLITE_REGS        ((MXNNLITE_2_0_Type*) MXNNLITE_2_0_BASE)
#endif

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')       */
/*****************************************************************************/

/**
 *****************************************************************************
 ** nnlite driver init function, validate context structure and
 ** set driver to init state
 **
 ** [in]  context    pointer to the driver context structure
 *****************************************************************************/
cy_en_nnlite_status_t
Cy_NNLite_Init(NNLITE_Type *nnlite, cy_nnlite_context_t *context)
{

    cy_en_nnlite_status_t status;

    if ((NULL == nnlite) || (NULL == context))
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else if (context->nnliteState != CY_NNLITE_DEINIT)
    {
        status = CY_NNLITE_BAD_STATE;
    }
    else
    {
        context->nnliteState = CY_NNLITE_INIT;
        status = CY_NNLITE_SUCCESS;
    }

    return status;
}

/**
 *****************************************************************************
 ** nnlite driver deinit function check's for pending or ongoing
 ** operation and set driver state to deinit
 **
 **
 ** [in]  nnlite    base pointer of register map.
 **
 ** [in]  context    pointer to the driver context structure
 *****************************************************************************/
cy_en_nnlite_status_t
Cy_NNLite_DeInit(NNLITE_Type *nnlite, cy_nnlite_context_t *context)
{
    cy_en_nnlite_status_t status;
    if ((NULL == nnlite) || (NULL == context))
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else if ((context->nnliteState == CY_NNLITE_OP_STARTED) ||
             (context->nnliteState == CY_NNLITE_DEINIT))
    {
        /* operation is going on, can not deinit*/
        status = CY_NNLITE_BAD_STATE;
    }
    else
    {
        context->nnliteState = CY_NNLITE_DEINIT;
        status = CY_NNLITE_SUCCESS;
    }
    return status;
}

/**
 *****************************************************************************
 ** nnlite start operation, streamer should should be configured before
 ** calling this function, this function will write to start bit in CMD MEMIO
 **
 **
 ** [in]  nnlite    base pointer of register map.
 **
 ** [in]  context    pointer to the driver context structure
 *****************************************************************************/
cy_en_nnlite_status_t
Cy_NNLite_Start(NNLITE_Type *nnlite, cy_nnlite_context_t *context)
{
    cy_en_nnlite_status_t status;

    if ((NULL == nnlite) || (NULL == context))
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else if ((context->nnliteState != CY_NNLITE_CONFIG_STATE &&
              context->nnliteState != CY_NNLITE_OP_DONE)
#if !defined(IFX_USE_MXNNLITE_STREAM_EMU)
             && (nnlite == MXNNLITE_REGS)
#endif
            )
    {
        status = CY_NNLITE_BAD_STATE;
    }
    else
    {
        context->opStatus = CY_NNLITE_SUCCESS;
#if !defined(IFX_USE_MXNNLITE_STREAM_EMU)
        if (nnlite == MXNNLITE_REGS)
        {
            context->nnliteState = CY_NNLITE_OP_STARTED;
        }
#endif
        nnlite->CMD |= NNLITE_VAL2FLD(CMD_START_CMD, 1);


#if defined(IFX_USE_MXNNLITE_STREAM_EMU)
        // Emulate execution on NNlite immediately,
        // includes triggering of ISR
        NNLite_Emu_Run(nnlite);
#endif
        status = CY_NNLITE_SUCCESS;
    }
    return status;
}

/**
 *****************************************************************************
 ** nnlite stop/abort operation, can be used to stop/abort current operation
 ** or to reset all configuration, API write abort in CMD MEMIO which will
 ** reset all the registers
 **
 ** [in]  nnlite    base pointer of register map.
 **
 ** [in]  context    pointer to the driver context structure
 *****************************************************************************/
cy_en_nnlite_status_t
Cy_NNLite_Stop(NNLITE_Type *nnlite, cy_nnlite_context_t *context)
{
    cy_en_nnlite_status_t status;
    if ((NULL == nnlite) || (NULL == context))
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
        nnlite->CMD |= NNLITE_VAL2FLD(CMD_ABORT_CMD, 1);
        context->nnliteState = CY_NNLITE_INIT;
        status = CY_NNLITE_SUCCESS;
    }
    return status;

}

/**
 *****************************************************************************
 ** nnlite get nnlite operation status, can be used to poll operation status
 **
 ** [in]  nnlite  base pointer of register map.
 **
 ** [out] opStatus    nnlite last operation status
 *****************************************************************************/
cy_en_nnlite_status_t
Cy_NNLite_GetOperationStatus(NNLITE_Type *nnlite, uint32_t *opStatus)
{
    cy_en_nnlite_status_t status = CY_NNLITE_SUCCESS;
    if ((NULL == nnlite) || (NULL == opStatus))
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
        *opStatus = (nnlite->STATUS & STATUS_REG_MASK);
    }

    return status;
}

#if CY_IP_MXNNLITE_VERSION==1
/**
 *****************************************************************************
 **   nnlite set Activation Type Control
 **
 **   [in]  nnlite    base pointer of register map.
 **
 **   [in]  nnLayer    NN Layer operation type
 **
 **   [in]  actEn    Output Activation enable
 **
 **   [in]  actDataSize    Activation size
 **
 **
 *****************************************************************************/
cy_en_nnlite_status_t
Cy_NNLite_ActivationTypeCtrl(NNLITE_Type *nnlite,

                             cy_en_nnlite_layer_t nnLayer,
                             bool actEn,
                             cy_en_nnlite_activation_size_t actDataSize
                            )
{
    cy_en_nnlite_status_t status;
    if ((NULL == nnlite))
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else if (nnLayer > CY_NNLITE_LAST_LAYER_CODE)
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
        nnlite->NNLAYER_ACTIVATION_TYPE_CTL =
            NNLITE_VAL2FLD(NNLAYER_ACTIVATION_TYPE_CTL_NNLAYER_TYPE_CTL, nnLayer) |
            NNLITE_VAL2FLD(NNLAYER_ACTIVATION_TYPE_CTL_ACTIVATION_FUNC_EN, actEn) |
            NNLITE_VAL2FLD(NNLAYER_ACTIVATION_TYPE_CTL_ACTIVATION_SIZE_CTL, actDataSize);
        status = CY_NNLITE_SUCCESS;
    }

    return status;

}
#endif


/**
 *****************************************************************************
 **   nnlite streamer buffer base set
 **
 **   [in]  nnlite    base pointer of register map.
 **
 **   [in]  strmId    streamer id
 **
 **   [in]  baseAddr    base address of buffer
 *****************************************************************************/
cy_en_nnlite_status_t
Cy_NNLite_StreamerBaseAddrSet(NNLITE_Type *nnlite,
                              cy_en_nnlite_streamer_id_t strmId, const void *baseAddr)
{
    cy_en_nnlite_status_t status = CY_NNLITE_SUCCESS;
    if ((NULL == nnlite) || (NULL == baseAddr))
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
        switch (strmId)
        {
        // Agents connected via RW bus-master connected to "EXP" (aka Ahb) bus on Explorer.
        case CY_NNLITE_ACTIVATION_STREAMER:
            nnlite->ACTIVATIONSTREAMERBASEADDR = (uintptr_t)cy_AhbRemapAddr(baseAddr);
            break;
        case CY_NNLITE_OUT_STREAMER:
            nnlite->OUTSTREAMERBASEADDR = (uintptr_t)cy_AhbRemapAddr(baseAddr);
            break;

        // Agents connected via (RO bus-master) connected to "CODE" bus on Explorer.
        case CY_NNLITE_WEIGHT_STREAMER:
            nnlite->WEIGHTSTREAMERBASEADDR = (uintptr_t)cy_CbusRemapAddr(baseAddr);
            break;
        case CY_NNLITE_BIAS_STREAMER:
            nnlite->BIASBASEADDR = (uintptr_t)cy_CbusRemapAddr(baseAddr);
            break;
#if CY_IP_MXNNLITE_VERSION==2
        case CY_NNLITE_SCALE_STREAMER:
            nnlite->SCALINGFACTORBASEADDR = (uintptr_t)cy_CbusRemapAddr(baseAddr);
            break;
        case CY_NNLITE_WEIGHT_COUNT_STREAMER:
            nnlite->NONZEROWEIGHTSPOINTER = (uintptr_t)cy_CbusRemapAddr(baseAddr);
            break;
        case CY_NNLITE_SPARSITY_MAP_STREAMER:
            nnlite->ACTIVATIONSTREAMERSPARSITYMAPBASEADDR = (uintptr_t)cy_CbusRemapAddr(baseAddr);
            break;
#endif
        default:
            status = CY_NNLITE_BAD_PARAM;
            break;
        }
    }

    return status;
}

#if CY_IP_MXNNLITE_VERSION==1
/**
 *****************************************************************************
 **   parse sparsity map, API will  parse sparsity bit map and update non
 **   zero weight pointer, sparsity bit map address and weight pointer in
 **   sparCfg, sparsity configuration structure

 **   [in]  sparsitybaseAddr sparsity map base address
 **
 **   [in]  sparseBitMapLen  Size of sparsity bitmap in bytes
 **
 **   [in]  activationRepeats  activation streamer repeat count
 **
 **   [out]  sparCfg sparsity configuration
 *****************************************************************************/
cy_en_nnlite_status_t
Cy_NNLite_ParseSparsity(NNLITE_Type *nnlite, const void *sparsitybaseAddr,
                        uint32_t activationRepeats, uint32_t sparseBitMapLen, cy_nnlite_sparsity_cfg_t *sparCfg)
{
    cy_en_nnlite_status_t status;
    uint32_t nonZeroWtLen;

    if ((NULL == nnlite) || (NULL == sparCfg) || (NULL == sparsitybaseAddr))
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
        /* nonzero wt pointer each of length 2 bytes */
        nonZeroWtLen =  activationRepeats * 2UL;
        sparCfg->nonZeroWtAddr = (uintptr_t)sparsitybaseAddr;
        sparCfg->sparsityBitMapAddr = (uintptr_t)sparsitybaseAddr + nonZeroWtLen;

        /* wt pointer == sparsebase + non zero wt pointer len +
         * len of sparse bit map
         * */
        sparCfg->wtAddr = (uintptr_t)sparsitybaseAddr + nonZeroWtLen + sparseBitMapLen;
        status = CY_NNLITE_SUCCESS;
    }

    return status;
}

/**
 *****************************************************************************
 **   configure sparsity from valid cy_nnlite_sparsity_cfg
 **   write non zero wt pointer and sparsity bit map MEMIO and enable sparsity
 **   in streamer mode MEMIO
 **
 **   [in]  nnlite base pointer of register map.
 **
 **   [in]  cy_nnlite_sparsity_cfg_t sparsity configuration
 *****************************************************************************/
cy_en_nnlite_status_t
Cy_NNLite_SparsityCfg(NNLITE_Type *nnlite, cy_nnlite_sparsity_cfg_t *sparCfg)
{
    cy_en_nnlite_status_t status;

    if ((NULL == nnlite) || (NULL == sparCfg))
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
        nnlite->NONZEROWEIGHTSPOINTER = cy_CbusRemapAddr((uint32_t *)sparCfg->nonZeroWtAddr);
        nnlite->ACTIVATIONSTREAMERSPARSITYMAPBASEADDR = cy_CbusRemapAddr((uint32_t *)sparCfg->sparsityBitMapAddr);
        status = CY_NNLITE_SUCCESS;
    }
    return status;
}


/**
 *****************************************************************************
 ** nnlite enable sparsity in streamer mode MEMIO
 **
 **   [in]  nnlite base pointer of register map.
 **
 **   [in] sparsityEn sparsity enable
 *****************************************************************************/
cy_en_nnlite_status_t
Cy_NNLite_SparsityEnable(NNLITE_Type *nnlite, bool sparsityEn)
{
    cy_en_nnlite_status_t status;
    if (NULL == nnlite)
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
        if (sparsityEn)
        {
            nnlite->STREAMERMODES |=
                NNLITE_VAL2FLD(STREAMERMODES_ACTIVATIONSTREAMERSPARSEEN, 1);
        }
        else
        {
            nnlite->STREAMERMODES &=
                ~(NNLITE_VAL2FLD(STREAMERMODES_ACTIVATIONSTREAMERSPARSEEN, 1));
        }
        status = CY_NNLITE_SUCCESS;
    }
    return status;
}
#endif

#if CY_IP_MXNNLITE_VERSION==1
/**
 *****************************************************************************
 **   nnlite activation streamer configuration set, API will configure
 **   parameters for activation streamer
 **
 **   [in]  nnlite    base pointer of register map.
 **
 **   [in]  context     pointer to the driver context structure
 **
 **   [in]  filterWidth  filter width
 **
 **   [in]  filterHeight   filter height
 **
 **   [in]  activationRepeats  activation streamer repeat count
 **
 **   [in]  inputWidth  input activation Width
 **
 **   [in]  inputHeight  input activation Height
 **
 **   [in]  inputChannel   input activation channels
 **
 **   [in]  startCol   starting column for activation
 **
 **   [in]  startRow   starting row for activation
 **
 **   [in]  padVal  padding value
 **
 **   [in]  padHeight  padding Height
 **
 **   [in]  padWidth   padding Width
 **
 **   [in]  strideCol  Stride column
 **
 **   [in]  strideRow  Stride rows
 **
 **   [in]  inputOffset input offset value
 *****************************************************************************/
#else
/**
 *****************************************************************************
 **   nnlite activation streamer configuration set, API will configure
 **   parameters for activation streamer
 **
 **   [in]  nnlite    base pointer of register map.
 **
 **   [in]  context     pointer to the driver context structure
 **
 **   [in]  filterWidth  filter width
 **
 **   [in]  filterHeight   filter height
 **
 **   [in]  activationRepeats  activation streamer repeat count
 **
 **   [in]  inputWidth  input activation Width
 **
 **   [in]  inputHeight  input activation Height
 **
 **   [in]  inputChannel   input activation channels
 **
 **   [in]  padVal  padding value
 **
 **   [in]  padHeight  padding Height
 **
 **   [in]  padWidth   padding Width
 **
 **   [in]  strideCol  Stride column
 **
 **   [in]  strideRow  Stride rows
 **
 **   [in]  inputOffset input offset value
 *****************************************************************************/
#endif
cy_en_nnlite_status_t
Cy_NNLite_ActivationStreamerCfg(NNLITE_Type *nnlite, cy_nnlite_context_t *context,
                                uint32_t filterWidth, uint32_t filterHeight,
                                uint32_t activationRepeats, uint32_t inputWidth,
                                uint32_t inputHeight, uint32_t inputChannel,
#if CY_IP_MXNNLITE_VERSION==1
                                uint32_t startCol, uint32_t startRow,
#endif
                                int16_t padVal, uint8_t padWidth, uint8_t padHeight,
                                uint8_t strideCol, uint8_t strideRow,
                                int32_t inputOffset)
{
    cy_en_nnlite_status_t status;
    uint32_t startColChannelTimesPadWidth;
    uint32_t startRowPadHeight;
    uint32_t padWidthTimesChannel;

    if ((NULL == nnlite) || (NULL == context))
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else if ((context->nnliteState == CY_NNLITE_INIT) ||
             (context->nnliteState ==  CY_NNLITE_OP_DONE))
    {
#if CY_IP_MXNNLITE_VERSION!=1
        static const int32_t startCol = 0;
        static const int32_t startRow = 0;
#endif
        padWidthTimesChannel = padWidth * inputChannel;
        startColChannelTimesPadWidth = startCol - padWidthTimesChannel;
        startRowPadHeight = startRow - padHeight;

        nnlite->ACTIVATIONSTREAMEROFFSET = (uint32_t)inputOffset;
        /* weights dims*/
        nnlite->ACTIVATIONSTREAMERKERNELCHANNELTIMESWIDTH = (filterWidth * inputChannel);
        nnlite->ACTIVATIONSTREAMERKERNELHEIGHT = filterHeight;

        /* is equal to number of filters for conv or equal to filer 2nd dimension for fc layer */
        nnlite->ACTIVATIONSTREAMERREPEATS = activationRepeats;

        /* input dims */
        nnlite->ACTIVATIONSTREAMERCHANNELTIMESWIDTH = (inputWidth * inputChannel);
        nnlite->ACTIVATIONSTREAMERHEIGHT = inputHeight;
        nnlite->ACTIVATIONSTREAMERSTARTCOL =  startColChannelTimesPadWidth;
        nnlite->ACTIVATIONSTREAMERSTARTROW = startRowPadHeight;
        nnlite->ACTIVATIONSTREAMERPADDING =
            NNLITE_VAL2FLD(ACTIVATIONSTREAMERPADDING_ACTIVATIONSTREAMERPADVALUE, padVal);

        nnlite->STRIDE =
            NNLITE_VAL2FLD(STRIDE_STRIDECHANNELTIMESCOLUMN, strideCol * inputChannel) |
            NNLITE_VAL2FLD(STRIDE_STRIDEROW, strideRow);
#if CY_IP_MXNNLITE_VERSION!=1
        nnlite->ACTIVATIONSTREAMERCHANNEL = inputChannel;
#endif
        status = CY_NNLITE_SUCCESS;
    }
    else
    {
        status = CY_NNLITE_BAD_STATE;
    }
    return status;
}

/**
 *****************************************************************************
 **   nnlite weight streamer configuration set, API will configure offset
 **   for weight streamer and weights per neuron parameter
 **
 **   [in]  nnlite    base pointer of register map.
 **
 **   [in]  context    pointer to the driver context structure
 **
 **   [in]  weightPerNeuron  wight/filter elements count per neuron
 **
 **   [in]  filterOffset   wight/filter elements offset value
 *****************************************************************************/
cy_en_nnlite_status_t
Cy_NNLite_WeightStreamerCfg(NNLITE_Type *nnlite, cy_nnlite_context_t *context,
                            uint32_t weightPerNeuron, int32_t filterOffset)
{
    cy_en_nnlite_status_t status;
    if ((NULL == nnlite) || (NULL == context))
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
        nnlite->WEIGHTSTREAMERKERNELCHANNELTIMESHEIGHTTIMESWIDTH = weightPerNeuron;
        nnlite->WEIGHTSTREAMEROFFSET = (uint32_t)filterOffset;
        status = CY_NNLITE_SUCCESS;
    }
    return status;
}
#if CY_IP_MXNNLITE_VERSION==1
/**
 *****************************************************************************
 **   nnlite out streamer configuration set, API will set clipping mask,
 **   offset, scaling factor ,width and height for output streamer
 **
 **   [in]  nnlite    base pointer of register map.
 **
 **   [in]  context    pointer to the driver context structure
 **
 **   [in]  clipping     output clipping setting mask or  max/min values
 **
 **   [in]  outputOffset   output elements offset value
 **
 **   [in]  outputScalingFactor  pointer output scaling factor(s)
 **
 *****************************************************************************/
#else
/**
 *****************************************************************************
 **   nnlite out streamer configuration set, API will set clipping mask,
 **   offset, scaling factor ,width and height for output streamer
 **
 **   [in]  nnlite    base pointer of register map.
 **
 **   [in]  context    pointer to the driver context structure
 **
 **   [in]  clipping     output clipping setting mask or  max/min values
 **
 **   [in]  outputOffset   output elements offset value
 **
 **   [in]  outputChannels  output Channels
 **
 *****************************************************************************/
#endif
cy_en_nnlite_status_t
Cy_NNLite_OutputStreamerCfg(NNLITE_Type *nnlite, cy_nnlite_context_t *context,
                            cy_nnlite_clipping_t clipping, int32_t outputOffset,
                            uint32_t outputWidth, uint32_t outputHeight,
#if CY_IP_MXNNLITE_VERSION==1
                            float outputScalingFactor
#else
                            uint32_t outputChannels
#endif
                           )
{
    cy_en_nnlite_status_t status;
    if ((NULL == nnlite) || (NULL == context))
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
#if CY_IP_MXNNLITE_VERSION==1
        void *scalingFactorPtr = (void *)&outputScalingFactor;
        nnlite->OUTSTREAMERCLIPPINGMASK = clipping;
        // Raw bits of the IEEE 32-bit f.p. value
        nnlite->OUTSTREAMERSCALINGFACTOR = *(uint32_t *)scalingFactorPtr;
#else
        nnlite->OUTSTREAMERCLIPPING =
            NNLITE_VAL2FLD(OUTSTREAMERCLIPPING_OUTSTREAMERCLIPPINGVALUEMIN, clipping.min) |
            NNLITE_VAL2FLD(OUTSTREAMERCLIPPING_OUTSTREAMERCLIPPINGVALUEMAX, clipping.max);
        nnlite->OUTPUTCHANNELS = outputChannels;
#endif
        nnlite->OUTPUTWIDTH = outputWidth;
        nnlite->OUTPUTHEIGHT = outputHeight;
        nnlite->OUTSTREAMEROUTPUTOFFSET = (uint32_t)outputOffset;
#if !defined(IFX_USE_MXNNLITE_STREAM_EMU)
        if (nnlite == MXNNLITE_REGS)
        {
            context->nnliteState = CY_NNLITE_CONFIG_STATE;
        }
#endif
        status = CY_NNLITE_SUCCESS;
    }
    return status;
}

#if CY_IP_MXNNLITE_VERSION==1
/**
 *****************************************************************************
 **   nnlite bias streamer enable
 **
 **   [in]  nnlite   base pointer of register map.
 **
 **   [in]  biasEn   bias streamer enable
 *****************************************************************************/
cy_en_nnlite_status_t
Cy_NNLite_BiasStreamerEnable(NNLITE_Type *nnlite, bool biasEn)
{
    cy_en_nnlite_status_t status;

    if (NULL == nnlite)
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
        status = CY_NNLITE_SUCCESS;
        if (biasEn)
        {
            nnlite->STREAMERMODES |= NNLITE_VAL2FLD(STREAMERMODES_BIASEN, 1);
        }
        else
        {
            nnlite->STREAMERMODES &= ~(NNLITE_VAL2FLD(STREAMERMODES_BIASEN, 1));
        }
    }
    return status;
}


/**
 *****************************************************************************
 **   nnlite set Interpolation lookup table to be used along
 **   with Cy_NNLite_SetinterpolationParam. For lut 0 and lut 1 both,
 **   Cy_NNLite_SetinterpolationParam need to be set.
 **
 **   [in]  nnlite    base pointer of register map.
 **
 **   [in]  lut      lookup table
 *****************************************************************************/
cy_en_nnlite_status_t
Cy_NNLite_SetInterpolationLUTAddr(NNLITE_Type *nnlite, bool lut)
{
    cy_en_nnlite_status_t status;
    if (NULL == nnlite)
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
        if (lut)
        {
            nnlite->INTERPOLATIONLUTADDR = 1U;
        }
        else
        {
            nnlite->INTERPOLATIONLUTADDR = 0U;
        }
        status = CY_NNLITE_SUCCESS;
    }
    return status;
}


/**
 *****************************************************************************
 ** Set interpolation parameters.
 **
 ** [in]  nnlite  nnlite base pointer.
 **
 ** [in] slope    number of elements.
 **
 ** [in] intercept  intercept value.
 *****************************************************************************/
cy_en_nnlite_status_t
Cy_NNLite_SetInterpolationParam(NNLITE_Type *nnlite,
                                uint16_t slope, uint16_t intercept)
{
    cy_en_nnlite_status_t status;
    if (NULL == nnlite)
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
#if defined(IFX_USE_MXNNLITE_STREAM_EMU)
        nnlite->INTERPOLATIONLUTWDATA[nnlite->INTERPOLATIONLUTADDR] =
            NNLITE_VAL2FLD(INTERPOLATIONLUTWDATA_INTERPOLATIONSLOPE, slope) |
            NNLITE_VAL2FLD(INTERPOLATIONLUTWDATA_INTERPOLATIONYINTERCEPT, intercept);
#else
        nnlite->INTERPOLATIONLUTWDATA =
            NNLITE_VAL2FLD(INTERPOLATIONLUTWDATA_INTERPOLATIONSLOPE, slope) |
            NNLITE_VAL2FLD(INTERPOLATIONLUTWDATA_INTERPOLATIONYINTERCEPT, intercept);
#endif
        status = CY_NNLITE_SUCCESS;
    }

    return status;
}

#else

/**
 * @brief Raw bits representing IEEE754 float value
 *;
 * @param x
 * @return raw bits representation of input.
 */
static inline uint32_t Cy_NNLite_Float_Rawbits(float x)
{
    union float_bits
    {
        float fval;
        uint32_t rawbits;
    }   mush;
    mush.fval = x;
    return mush.rawbits;
}

/**
 *****************************************************************************
 ** \brief  Set pre/post arithmetic/accumulation scaling
 **
 ** \param [in]   nnlite    base pointer of NNLIte register map.
 **
 ** \param [in]   preScalingFactor Pre-scaling factor to input prior to arithmetic/accumulation operation
 **
 ** \param [in]   postScalingFactors    Post-scaling factor(s) to be applied after arithmetic/accumulation
 **
 ** \retval Refer \ref cy_en_nnlite_status_t
 **
 ** @note Scale factors are restricted IEEE754 float values.  For NNLite V2.0
 ** supported exponents [8,-24] are supported.   Mantissa is rounded to 16-bits.  Non Nan etc.
 **
 **
 *****************************************************************************/

cy_en_nnlite_status_t
Cy_NNLite_SetPrePostScaling(NNLITE_Type *nnlite, float preScalingFactor, const float *postScalingFactors)
{
    cy_en_nnlite_status_t status;
    if (NULL == nnlite)
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
        nnlite->SCALINGFACTORBASEADDR = (uintptr_t)cy_CbusRemapAddr((void *)postScalingFactors);
        nnlite->INPUTRESCALINGFACTOR = Cy_NNLite_Float_Rawbits(preScalingFactor);
        status = CY_NNLITE_SUCCESS;
    }
    return status;
}

/**
 *****************************************************************************
 ** \brief  set interpolation parameters
 **
 ** \param [in]   nnlite    base pointer of NNLIte register map.
 **
 ** \param [in]   segment  lookup segment table  addr (0: [-inf..0], 1: [0..inf] )
 **
 ** \param [in]   gradient     slope value for interpolation (IEEE 32-bit
 ** float mantissa will be rounded to 7 bits)
 **
 **
 ** \retval Refer \ref cy_en_nnlite_status_t
 **
 *****************************************************************************/
cy_en_nnlite_status_t
Cy_NNLite_SetInterpolationParam(NNLITE_Type *nnlite,
                                uint32_t segment,
                                float gradient)
{
    cy_en_nnlite_status_t status;
    if (NULL == nnlite || segment > 1)
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
        uint32_t *lut_regs_base = (uint32_t*)&nnlite->INTERPOLATIONLUTDATA0;
        uint32_t slope_bits = Cy_NNLite_Float_Rawbits(gradient);
        lut_regs_base[segment] = slope_bits;
        status = CY_NNLITE_SUCCESS;
    }

    return status;

}

/**
 *****************************************************************************
 *
 * @brief Configure NNLite for Q1.15 complex FFT
 *
 * NNLite implements Decimation-in-Time   Radix-2 FFT
 *
 * @note FFT length =^= Number complex input values *2 = #
 * @param [in]  nnlite  base pointer of NNLIte register map.
 * @param [in] context  pointer to the driver context structure.
 * @param [in] ppBuf0   Input / ping-pong buffer 0, Output (even stages/# values)
 * @param [in] ppBuf1   ping-pong buffer 1, Output (odd stages/# values)
 * @param [in] fftStages   log_2(FFT length)
 *
 * @retval Refer \ref cy_en_nnlite_status_t
 *****************************************************************************
 */

cy_en_nnlite_status_t
Cy_NNLite_FFTCfg(NNLITE_Type *nnlite,
                 cy_nnlite_context_t *context,
                 void *ppBuf0, void *ppBuf1,
                 unsigned int fftStages)
{
    cy_en_nnlite_status_t status;

    if ((NULL == ppBuf0) || (NULL == ppBuf1))
    {
        return CY_NNLITE_BAD_PARAM;
    }
    if (fftStages < 4u || fftStages > 10u)
    {
        return CY_NNLITE_BAD_PARAM;
    }
    status = Cy_NNLite_StreamerBaseAddrSet(nnlite, CY_NNLITE_ACTIVATION_STREAMER, ppBuf0);
    if (status != CY_NNLITE_SUCCESS)
    {
        return status;
    }
    status = Cy_NNLite_StreamerBaseAddrSet(nnlite, CY_NNLITE_WEIGHT_STREAMER, ppBuf0);
    if (status != CY_NNLITE_SUCCESS)
    {
        return status;
    }
    status = Cy_NNLite_StreamerBaseAddrSet(nnlite, CY_NNLITE_OUT_STREAMER, ppBuf1);
    if (status != CY_NNLITE_SUCCESS)
    {
        return status;
    }
    status = Cy_NNLite_StreamerBaseAddrSet(nnlite, CY_NNLITE_BIAS_STREAMER, ppBuf1);
    if (status != CY_NNLITE_SUCCESS)
    {
        return status;
    }

    // 2* length FFT = 2 * 2^(# FFT stages)
    nnlite->WEIGHTSTREAMERKERNELCHANNELTIMESHEIGHTTIMESWIDTH =
        1 << (1 + fftStages);
    nnlite->OUTPUTWIDTH = fftStages;
    nnlite->NNLAYER_CTL =
        _VAL2FLD(MXNNLITE_2_0_NNLAYER_CTL_INPUT_SIZE_CTL, CY_NNLITE_ACTIVATION_16BIT) |
        _VAL2FLD(MXNNLITE_2_0_NNLAYER_CTL_WEIGHT_SIZE_CTL, CY_NNLITE_ACTIVATION_16BIT) |
        _VAL2FLD(MXNNLITE_2_0_NNLAYER_CTL_OUTPUT_SIZE_CTL, CY_NNLITE_OUTPUT_32BIT) |
        _VAL2FLD(MXNNLITE_2_0_NNLAYER_CTL_FETCH_MODE, CY_NNLITE_ACT_WGT) |
        _VAL2FLD(MXNNLITE_2_0_NNLAYER_CTL_WPREFETCH_LEN, CY_NNLITE_PREFETCH_WORD_4x128) |
        _VAL2FLD(MXNNLITE_2_0_NNLAYER_CTL_FFT_EN, 1);
#if !defined(IFX_USE_MXNNLITE_STREAM_EMU)
    if (nnlite == MXNNLITE_REGS)
    {
        context->nnliteState = CY_NNLITE_CONFIG_STATE;
    }
#endif
    return status;
}

#endif

/**
 *****************************************************************************
 **   nnlite get nnlite interrupt status
 **
 **   [in]  nnlite    base pointer of register map.
 **
 **   [out]  intrStatus    nnlite interrupt status register
 *****************************************************************************/
cy_en_nnlite_status_t
Cy_NNLite_GetInterruptStatus(NNLITE_Type *nnlite, uint32_t *intrStatus)
{
    cy_en_nnlite_status_t status;

    if ((NULL == nnlite) || (NULL == intrStatus))
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
        *intrStatus   = nnlite->INTR;
        status = CY_NNLITE_SUCCESS;
    }

    return status;

}

/**
 *****************************************************************************
 **   get nnlite interrupt mask
 **
 **   [in]  nnlite    base pointer of register map.
 **
 **   [out]  intrMask  nnlite interrupt mask
 *****************************************************************************/
cy_en_nnlite_status_t
Cy_NNLite_GetInterruptMask(NNLITE_Type *nnlite, uint32_t *intrMask)
{
    cy_en_nnlite_status_t status;

    if ((NULL == nnlite) || (NULL == intrMask))
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
        *intrMask = nnlite->INTR_MASK;
        status = CY_NNLITE_SUCCESS;
    }
    return status;

}

/*****************************************************************************
**   nnlite get driver state
**
**   [in]  nnlite base pointer of register map.
**
**   [in]  context    pointer to the driver context structure
**
**   [out]  nnliteState nnlite driver state
*****************************************************************************/
cy_en_nnlite_status_t Cy_NNLite_GetDriverState(NNLITE_Type *nnlite,
        cy_nnlite_context_t *context,
        cy_en_nnlite_state_t *nnliteState)
{
    cy_en_nnlite_status_t status = CY_NNLITE_SUCCESS;
    if ((NULL == nnlite) || (NULL == nnliteState))
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
        *nnliteState = context->nnliteState;
    }
    return status;
}

/**
 *****************************************************************************
 **    nnlite set datawire trigger control, trigger datawire for next layer
 **   when trigger is 1
 **
 **   [in]  nnlite    base pointer of register map.
 **
 **   [in]  trigEn  datawire trigger enable
 *****************************************************************************/
cy_en_nnlite_status_t
Cy_NNLite_DatawireTriggerEnable(NNLITE_Type *nnlite, bool trigEn)
{
    cy_en_nnlite_status_t status;

    if (NULL == nnlite)
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
        nnlite->TRIG_MASK = (uint32_t)trigEn;
        status = CY_NNLITE_SUCCESS;
    }
    return status;
}

/**
 *****************************************************************************
 **    nnlite set interrupt mask, available interrupt are operation STATUS Done,
 **    MEM Fetch Error different streamers, Output Saturation interrupt
 **
 **   [in]  nnlite    base pointer of register map.
 **
 **   [in]  intrMask      interrupt mask value
 *****************************************************************************/
cy_en_nnlite_status_t
Cy_NNLite_SetInterruptMask(NNLITE_Type *nnlite, uint32_t intrMask)
{
    cy_en_nnlite_status_t status;

    if (NULL == nnlite)
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
        nnlite->INTR_MASK = (intrMask & 0x7FUL);
        status = CY_NNLITE_SUCCESS;
    }
    return status;

}

/**
 *****************************************************************************
 **    clear nnlite interrupts
 **
 **   [in]  nnlite    base pointer of register map.
 **
 **   [in]  intrMask     nnlite interrupts to be cleared
 *****************************************************************************/
cy_en_nnlite_status_t
Cy_NNLite_InterruptClear(NNLITE_Type *nnlite, uint32_t intrMask)
{
    cy_en_nnlite_status_t status;

    if (NULL == nnlite)
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
        // INTR is a write-1-to-clear register ...
#if defined(IFX_USE_MXNNLITE_STREAM_EMU)
        // Emulate RW1C behaviour....
        nnlite->INTR &= ~(intrMask & 0x7Fu);
#else
        nnlite->INTR &= (intrMask & 0x3FFu);
#endif
        status = CY_NNLITE_SUCCESS;
    }
    return status;

}

/**
 *****************************************************************************
 **    interrupt mask to status mapping
 **
 **   [in]  intrStatus interrupt status
 *****************************************************************************/

#if CY_IP_MXNNLITE_VERSION==1
static cy_en_nnlite_status_t
Cy_NNLite_InterruptStatusToErrMap(uint32_t intrStatus)
{
    cy_en_nnlite_status_t status;
    switch (intrStatus)
    {
    case MXNNLITE_1_0_INTR_INTR_DONE_Msk:
        status = CY_NNLITE_SUCCESS;
        break;
    case MXNNLITE_1_0_INTR_INTR_MEM_ERR_SPARSITY_Msk:
        status = CY_NNLITE_MEM_ERR_SPARSITY;
        break;
    case MXNNLITE_1_0_INTR_INTR_MEM_ERR_ACTIVATIONSTREAMER_Msk:
        status = CY_NNLITE_MEM_ERR_ACTIVATION_STREAMER;
        break;
    case MXNNLITE_1_0_INTR_INTR_MEM_ERR_WEIGHTSTREAMER_Msk:
        status = CY_NNLITE_MEM_ERR_WEIGHT_STREAMER;
        break;
    case MXNNLITE_1_0_INTR_INTR_MEM_ERR_BIASSTREAMER_Msk:
        status = CY_NNLITE_MEM_ERR_BIAS_STREAMER;
        break;
    case MXNNLITE_1_0_INTR_INTR_MEM_ERR_OUTPUTSTREAMER_Msk:
        status = CY_NNLITE_MEM_ERR_OUTPUT_STREAMER;
        break;
    case MXNNLITE_1_0_INTR_INTR_SATURATION_Msk:/* fall through for saturation */
    case (MXNNLITE_1_0_INTR_INTR_DONE_Msk | MXNNLITE_1_0_INTR_INTR_SATURATION_Msk) :
        status = CY_NNLITE_SATURATION;
        break;
    default :
        status = CY_NNLITE_SUCCESS;
        break;

    }
    return status;
}
#else
static cy_en_nnlite_status_t
Cy_NNLite_InterruptStatusToErrMap(uint32_t intrStatus)
{
    cy_en_nnlite_status_t status;
    if (intrStatus & NNLITE_INTR_READ_ERRORS_MASK)
    {
        status = CY_NNLITE_MEM_READ_ERR;
    }
    else if (intrStatus & NNLITE_INTR_WRITE_ERRORS_MASK)
    {
        status = CY_NNLITE_MEM_WRITE_ERR;
    }
    else if (intrStatus & NNLITE_SATURATION_MASK)
    {
        status = CY_NNLITE_SATURATION_EVENT;
    }
    else
    {
        status = CY_NNLITE_SUCCESS;
    }
    return status;
}
#endif

/**
 *****************************************************************************
 ** wait for completion of operation, will wait for BUSY_STATUS to go low,
 ** in busy loop
 **
 ** [in]  nnlite    base pointer of register map.
 **
 ** [in]  context    pointer to the driver context structure
*****************************************************************************/
cy_en_nnlite_status_t Cy_NNLite_WaitForCompletion(NNLITE_Type *nnlite,
        cy_nnlite_context_t *context)
{
    cy_en_nnlite_status_t status;
    uint32_t interruptStatus;
    if ((NULL == nnlite) || (NULL == context))
    {
        status = CY_NNLITE_BAD_PARAM;
    }
    else
    {
        /* poll for Busy bit */
        do
        {
        }
        while (1U == (nnlite->STATUS & STATUS_REG_MASK));

        (void)Cy_NNLite_GetInterruptStatus(nnlite, &interruptStatus);
        status = Cy_NNLite_InterruptStatusToErrMap(interruptStatus);
        (void)Cy_NNLite_InterruptClear(nnlite, interruptStatus);

        if (context->nnliteState == CY_NNLITE_OP_STARTED)
        {
            context->nnliteState = CY_NNLITE_OP_DONE;
        }
    }
    return status;
}

/**
 *****************************************************************************
 **    nnlite  ISR handler
 **
 **   [in]  nnlite    base pointer of register map.
 **
 **   [in]  context    nnlite context structure pointer
 *****************************************************************************/
void Cy_NNLite_InterruptHandler(NNLITE_Type *nnlite,
                                cy_nnlite_context_t *context)
{
    uint32_t intrStatus = 0;

    (void)Cy_NNLite_GetInterruptStatus(nnlite, &intrStatus);
    if (context->nnliteState == CY_NNLITE_OP_STARTED)
    {
        context->opStatus = Cy_NNLite_InterruptStatusToErrMap(intrStatus);
        context->opIntrStatus = intrStatus;
        context->nnliteState = CY_NNLITE_OP_DONE;
    }

    (void)Cy_NNLite_InterruptClear(nnlite, intrStatus);
}


#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXNNLITE */

/* [] END OF FILE */
