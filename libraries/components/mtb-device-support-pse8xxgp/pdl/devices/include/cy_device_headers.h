/***************************************************************************//**
* \file cy_device_headers.h
*
* \brief
* Common header file to be included by the drivers.
*
********************************************************************************
* \copyright
* (c) (2016-2025), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef _CY_DEVICE_HEADERS_H_
#define _CY_DEVICE_HEADERS_H_

#if defined (COMPONENT_SECURE_DEVICE)

    #if defined (PSE846GPS4DBZC4A)
        #include "pse846gps4dbzc4a_s.h"
    #elif defined (PSE846GPS2DBZC4A)
        #include "pse846gps2dbzc4a_s.h"
    #elif defined (PSE846GOS4DBZC4A)
        #include "pse846gos4dbzc4a_s.h"
    #elif defined (PSE846GOS2DBZC4A)
        #include "pse846gos2dbzc4a_s.h"
    #elif defined (PSE845GPS4DFNC4A)
        #include "pse845gps4dfnc4a_s.h"
    #elif defined (PSE845GPS4DFMC4A)
        #include "pse845gps4dfmc4a_s.h"
    #elif defined (PSE845GPS2DFNC4A)
        #include "pse845gps2dfnc4a_s.h"
    #elif defined (PSE845GPS2DFMC4A)
        #include "pse845gps2dfmc4a_s.h"
    #elif defined (PSE845GOS4DFNC4A)
        #include "pse845gos4dfnc4a_s.h"
    #elif defined (PSE845GOS4DFMC4A)
        #include "pse845gos4dfmc4a_s.h"
    #elif defined (PSE845GOS2DFNC4A)
        #include "pse845gos2dfnc4a_s.h"
    #elif defined (PSE845GOS2DFMC4A)
        #include "pse845gos2dfmc4a_s.h"
    #elif defined (PSE846GPS4DBZQ3A)
        #include "pse846gps4dbzq3a_s.h"
    #elif defined (PSE846GPS2DBZQ3A)
        #include "pse846gps2dbzq3a_s.h"
    #elif defined (PSE846GOS4DBZQ3A)
        #include "pse846gos4dbzq3a_s.h"
    #elif defined (PSE846GOS2DBZQ3A)
        #include "pse846gos2dbzq3a_s.h"
    #elif defined (PSE832GOS4DFNC4A)
        #include "pse832gos4dfnc4a_s.h"
    #elif defined (PSE833GOS4DBZC4A)
        #include "pse833gos4dbzc4a_s.h"
    #elif defined (PSE832GOS2DFNC4A)
        #include "pse832gos2dfnc4a_s.h"
    #elif defined (PSE833GOS2DBZC4A)
        #include "pse833gos2dbzc4a_s.h"
    #elif defined (PSE832GMS4DFNC4A)
        #include "pse832gms4dfnc4a_s.h"
    #elif defined (PSE833GMS4DBZC4A)
        #include "pse833gms4dbzc4a_s.h"
    #elif defined (PSE832GMS2DFNC4A)
        #include "pse832gms2dfnc4a_s.h"
    #elif defined (PSE833GMS2DBZC4A)
        #include "pse833gms2dbzc4a_s.h"
    #elif defined (PSE833GOS4DBZQ3A)
        #include "pse833gos4dbzq3a_s.h"
    #elif defined (PSE833GOS2DBZQ3A)
        #include "pse833gos2dbzq3a_s.h"
    #elif defined (PSE833GMS4DBZQ3A)
        #include "pse833gms4dbzq3a_s.h"
    #elif defined (PSE833GMS2DBZQ3A)
        #include "pse833gms2dbzq3a_s.h"
    #elif defined (PSE822GOS4DFNC4A)
        #include "pse822gos4dfnc4a_s.h"
    #elif defined (PSE823GOS4DBZC4A)
        #include "pse823gos4dbzc4a_s.h"
    #elif defined (PSE822GOS2DFNC4A)
        #include "pse822gos2dfnc4a_s.h"
    #elif defined (PSE823GOS2DBZC4A)
        #include "pse823gos2dbzc4a_s.h"
    #elif defined (PSE822GMS4DFNC4A)
        #include "pse822gms4dfnc4a_s.h"
    #elif defined (PSE823GMS4DBZC4A)
        #include "pse823gms4dbzc4a_s.h"
    #elif defined (PSE822GMS2DFNC4A)
        #include "pse822gms2dfnc4a_s.h"
    #elif defined (PSE823GMS2DBZC4A)
        #include "pse823gms2dbzc4a_s.h"
    #elif defined (PSE823GOS4DBZQ3A)
        #include "pse823gos4dbzq3a_s.h"
    #elif defined (PSE823GOS2DBZQ3A)
        #include "pse823gos2dbzq3a_s.h"
    #elif defined (PSE823GMS4DBZQ3A)
        #include "pse823gms4dbzq3a_s.h"
    #elif defined (PSE823GMS2DBZQ3A)
        #include "pse823gms2dbzq3a_s.h"
    #elif defined (PSE812GOS4DFNC4A)
        #include "pse812gos4dfnc4a_s.h"
    #elif defined (PSE813GOS4DBZC4A)
        #include "pse813gos4dbzc4a_s.h"
    #elif defined (PSE812GOS2DFNC4A)
        #include "pse812gos2dfnc4a_s.h"
    #elif defined (PSE813GOS2DBZC4A)
        #include "pse813gos2dbzc4a_s.h"
    #elif defined (PSE812GMS4DFNC4A)
        #include "pse812gms4dfnc4a_s.h"
    #elif defined (PSE813GMS4DBZC4A)
        #include "pse813gms4dbzc4a_s.h"
    #elif defined (PSE812GMS2DFNC4A)
        #include "pse812gms2dfnc4a_s.h"
    #elif defined (PSE813GMS2DBZC4A)
        #include "pse813gms2dbzc4a_s.h"
    #elif defined (PSE813GOS4DBZQ3A)
        #include "pse813gos4dbzq3a_s.h"
    #elif defined (PSE813GOS2DBZQ3A)
        #include "pse813gos2dbzq3a_s.h"
    #elif defined (PSE813GMS4DBZQ3A)
        #include "pse813gms4dbzq3a_s.h"
    #elif defined (PSE813GMS2DBZQ3A)
        #include "pse813gms2dbzq3a_s.h"
    #elif defined (PSE845GPS4DFMC4)
        #include "pse845gps4dfmc4_s.h"
    #elif defined (PSE845GPS4DFNC4)
        #include "pse845gps4dfnc4_s.h"
    #elif defined (PSE846GPS4DBZC4)
        #include "pse846gps4dbzc4_s.h"
    #elif defined (PSE846GPS4DAEI3)
        #include "pse846gps4daei3_s.h"
    #elif defined (PSE845GPS2DFMC4)
        #include "pse845gps2dfmc4_s.h"
    #elif defined (PSE845GPS2DFNC4)
        #include "pse845gps2dfnc4_s.h"
    #elif defined (PSE846GPS2DBZC4)
        #include "pse846gps2dbzc4_s.h"
    #elif defined (PSE846GPS2DAEI3)
        #include "pse846gps2daei3_s.h"
    #elif defined (PSE845GOS4DFMC4)
        #include "pse845gos4dfmc4_s.h"
    #elif defined (PSE845GOS4DFNC4)
        #include "pse845gos4dfnc4_s.h"
    #elif defined (PSE846GOS4DBZC4)
        #include "pse846gos4dbzc4_s.h"
    #elif defined (PSE846GOS4DAEI3)
        #include "pse846gos4daei3_s.h"
    #elif defined (PSE845GOS2DFMC4)
        #include "pse845gos2dfmc4_s.h"
    #elif defined (PSE845GOS2DFNC4)
        #include "pse845gos2dfnc4_s.h"
    #elif defined (PSE846GOS2DBZC4)
        #include "pse846gos2dbzc4_s.h"
    #elif defined (PSE846GOS2DAEI3)
        #include "pse846gos2daei3_s.h"
    #else
        #error Undefined part number. Consider updating PDL via ModusToolbox Library Manager to resolve the issue.
    #endif

#else
    #if defined (PSE846GPS4DBZC4A)
        #include "pse846gps4dbzc4a.h"
    #elif defined (PSE846GPS2DBZC4A)
        #include "pse846gps2dbzc4a.h"
    #elif defined (PSE846GOS4DBZC4A)
        #include "pse846gos4dbzc4a.h"
    #elif defined (PSE846GOS2DBZC4A)
        #include "pse846gos2dbzc4a.h"
    #elif defined (PSE845GPS4DFNC4A)
        #include "pse845gps4dfnc4a.h"
    #elif defined (PSE845GPS4DFMC4A)
        #include "pse845gps4dfmc4a.h"
    #elif defined (PSE845GPS2DFNC4A)
        #include "pse845gps2dfnc4a.h"
    #elif defined (PSE845GPS2DFMC4A)
        #include "pse845gps2dfmc4a.h"
    #elif defined (PSE845GOS4DFNC4A)
        #include "pse845gos4dfnc4a.h"
    #elif defined (PSE845GOS4DFMC4A)
        #include "pse845gos4dfmc4a.h"
    #elif defined (PSE845GOS2DFNC4A)
        #include "pse845gos2dfnc4a.h"
    #elif defined (PSE845GOS2DFMC4A)
        #include "pse845gos2dfmc4a.h"
    #elif defined (PSE846GPS4DBZQ3A)
        #include "pse846gps4dbzq3a.h"
    #elif defined (PSE846GPS2DBZQ3A)
        #include "pse846gps2dbzq3a.h"
    #elif defined (PSE846GOS4DBZQ3A)
        #include "pse846gos4dbzq3a.h"
    #elif defined (PSE846GOS2DBZQ3A)
        #include "pse846gos2dbzq3a.h"
    #elif defined (PSE832GOS4DFNC4A)
        #include "pse832gos4dfnc4a.h"
    #elif defined (PSE833GOS4DBZC4A)
        #include "pse833gos4dbzc4a.h"
    #elif defined (PSE832GOS2DFNC4A)
        #include "pse832gos2dfnc4a.h"
    #elif defined (PSE833GOS2DBZC4A)
        #include "pse833gos2dbzc4a.h"
    #elif defined (PSE832GMS4DFNC4A)
        #include "pse832gms4dfnc4a.h"
    #elif defined (PSE833GMS4DBZC4A)
        #include "pse833gms4dbzc4a.h"
    #elif defined (PSE832GMS2DFNC4A)
        #include "pse832gms2dfnc4a.h"
    #elif defined (PSE833GMS2DBZC4A)
        #include "pse833gms2dbzc4a.h"
    #elif defined (PSE833GOS4DBZQ3A)
        #include "pse833gos4dbzq3a.h"
    #elif defined (PSE833GOS2DBZQ3A)
        #include "pse833gos2dbzq3a.h"
    #elif defined (PSE833GMS4DBZQ3A)
        #include "pse833gms4dbzq3a.h"
    #elif defined (PSE833GMS2DBZQ3A)
        #include "pse833gms2dbzq3a.h"
    #elif defined (PSE822GOS4DFNC4A)
        #include "pse822gos4dfnc4a.h"
    #elif defined (PSE823GOS4DBZC4A)
        #include "pse823gos4dbzc4a.h"
    #elif defined (PSE822GOS2DFNC4A)
        #include "pse822gos2dfnc4a.h"
    #elif defined (PSE823GOS2DBZC4A)
        #include "pse823gos2dbzc4a.h"
    #elif defined (PSE822GMS4DFNC4A)
        #include "pse822gms4dfnc4a.h"
    #elif defined (PSE823GMS4DBZC4A)
        #include "pse823gms4dbzc4a.h"
    #elif defined (PSE822GMS2DFNC4A)
        #include "pse822gms2dfnc4a.h"
    #elif defined (PSE823GMS2DBZC4A)
        #include "pse823gms2dbzc4a.h"
    #elif defined (PSE823GOS4DBZQ3A)
        #include "pse823gos4dbzq3a.h"
    #elif defined (PSE823GOS2DBZQ3A)
        #include "pse823gos2dbzq3a.h"
    #elif defined (PSE823GMS4DBZQ3A)
        #include "pse823gms4dbzq3a.h"
    #elif defined (PSE823GMS2DBZQ3A)
        #include "pse823gms2dbzq3a.h"
    #elif defined (PSE812GOS4DFNC4A)
        #include "pse812gos4dfnc4a.h"
    #elif defined (PSE813GOS4DBZC4A)
        #include "pse813gos4dbzc4a.h"
    #elif defined (PSE812GOS2DFNC4A)
        #include "pse812gos2dfnc4a.h"
    #elif defined (PSE813GOS2DBZC4A)
        #include "pse813gos2dbzc4a.h"
    #elif defined (PSE812GMS4DFNC4A)
        #include "pse812gms4dfnc4a.h"
    #elif defined (PSE813GMS4DBZC4A)
        #include "pse813gms4dbzc4a.h"
    #elif defined (PSE812GMS2DFNC4A)
        #include "pse812gms2dfnc4a.h"
    #elif defined (PSE813GMS2DBZC4A)
        #include "pse813gms2dbzc4a.h"
    #elif defined (PSE813GOS4DBZQ3A)
        #include "pse813gos4dbzq3a.h"
    #elif defined (PSE813GOS2DBZQ3A)
        #include "pse813gos2dbzq3a.h"
    #elif defined (PSE813GMS4DBZQ3A)
        #include "pse813gms4dbzq3a.h"
    #elif defined (PSE813GMS2DBZQ3A)
        #include "pse813gms2dbzq3a.h"
    #elif defined (PSE845GPS4DFMC4)
        #include "pse845gps4dfmc4.h"
    #elif defined (PSE845GPS4DFNC4)
        #include "pse845gps4dfnc4.h"
    #elif defined (PSE846GPS4DBZC4)
        #include "pse846gps4dbzc4.h"
    #elif defined (PSE846GPS4DAEI3)
        #include "pse846gps4daei3.h"
    #elif defined (PSE845GPS2DFMC4)
        #include "pse845gps2dfmc4.h"
    #elif defined (PSE845GPS2DFNC4)
        #include "pse845gps2dfnc4.h"
    #elif defined (PSE846GPS2DBZC4)
        #include "pse846gps2dbzc4.h"
    #elif defined (PSE846GPS2DAEI3)
        #include "pse846gps2daei3.h"
    #elif defined (PSE845GOS4DFMC4)
        #include "pse845gos4dfmc4.h"
    #elif defined (PSE845GOS4DFNC4)
        #include "pse845gos4dfnc4.h"
    #elif defined (PSE846GOS4DBZC4)
        #include "pse846gos4dbzc4.h"
    #elif defined (PSE846GOS4DAEI3)
        #include "pse846gos4daei3.h"
    #elif defined (PSE845GOS2DFMC4)
        #include "pse845gos2dfmc4.h"
    #elif defined (PSE845GOS2DFNC4)
        #include "pse845gos2dfnc4.h"
    #elif defined (PSE846GOS2DBZC4)
        #include "pse846gos2dbzc4.h"
    #elif defined (PSE846GOS2DAEI3)
        #include "pse846gos2daei3.h"
    #else
        #error Undefined part number. Consider updating PDL via ModusToolbox Library Manager to resolve the issue.
    #endif

#endif

#endif /* _CY_DEVICE_HEADERS_H_ */


/* [] END OF FILE */
