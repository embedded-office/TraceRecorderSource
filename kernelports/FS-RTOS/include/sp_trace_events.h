/*
****************************************************************************************************
* (c) copyright by
*     Embedded Office GmbH & Co. KG       Tel : (07522) 97 00 08-0
*     Friedrich-Ebert-Str. 20/1           Fax : (07522) 97 00 08-99
*     D-88239 Wangen                      Mail: info@embedded-office.de
*                                         Web : http://www.embedded-office.de
*
* All rights reserved. Confidential and Proprietary. Protected by international copyright laws.
* Knowledge of the source code may not be used to write a similar product.
* This file may only be used in accordance with a license and should not be
* redistributed in any way.
****************************************************************************************************
*/
/*!
****************************************************************************************************
* \file     sp_trace_events.h
* \brief    �C/OS-MPU - API TRACE Layer
* \ingroup  OS_SP
*
* $Id: //stream_cert-mpu/task_tracealyzer-stm32_20220509/cert-mpu/trace/percepio/TraceRecorder/include/sp_trace_events.h#3 $
*
*           This file contains the API trace implementation for SystemView for uC/OS-MPU.
*
****************************************************************************************************
*/
/*----------------------------------------END OF HEADER-------------------------------------------*/
#include "sp_osapi.h"
#include "trcRecorder.h"

/*
************************************************************************************************************************
*                                     uC/OS-II Trace fixed defines for SystemView
************************************************************************************************************************
*/

#if (defined(OS_TRACE_EN) && (OS_TRACE_EN > 0u))
#define PSF_EVENT_SP_PROC_CREATE 							TRC_EVENT_LAST_ID
#define PSF_EVENT_SP_PROC_CREATE_FAILED						TRC_EVENT_LAST_ID + 1
#define PSF_EVENT_SP_PROC_ASSIGN							TRC_EVENT_LAST_ID + 2
#define PSF_EVENT_SP_PROC_ASSIGN_FAILED						TRC_EVENT_LAST_ID + 3
#define PSF_EVENT_SP_PROC_DEL								TRC_EVENT_LAST_ID + 4
#define PSF_EVENT_SP_PROC_DEL_FAILED						TRC_EVENT_LAST_ID + 5
#define PSF_EVENT_SP_PROC_GET								TRC_EVENT_LAST_ID + 6
#define PSF_EVENT_SP_PROC_KILL								TRC_EVENT_LAST_ID + 7
#define PSF_EVENT_SP_SHM_CREATE								TRC_EVENT_LAST_ID + 8
#define PSF_EVENT_SP_SHM_CREATE_FAILED						TRC_EVENT_LAST_ID + 9
#define PSF_EVENT_SP_SHM_ASSIGN								TRC_EVENT_LAST_ID + 10
#define PSF_EVENT_SP_SHM_ASSIGN_FAILED						TRC_EVENT_LAST_ID + 11
#define PSF_EVENT_SP_THREAD_STKMONGET                       TRC_EVENT_LAST_ID + 12
#define PSF_EVENT_SP_THREAD_STKMONGET_FAILED                TRC_EVENT_LAST_ID + 13
#define PSF_EVENT_SP_MONSTK_CREATE                          TRC_EVENT_LAST_ID + 14
#define PSF_EVENT_SP_MONSTK_CREATE_FAILED                   TRC_EVENT_LAST_ID + 15
#define PSF_EVENT_SP_MONSTKPTR_CHECK                        TRC_EVENT_LAST_ID + 16
#define PSF_EVENT_SP_MONSTKPTR_CHECK_FAILED                 TRC_EVENT_LAST_ID + 17
#define PSF_EVENT_SP_MON_STKPATTERNCHK                      TRC_EVENT_LAST_ID + 18
#define PSF_EVENT_SP_MON_STKPATTERNCHK_FAILED               TRC_EVENT_LAST_ID + 19
#define PSF_EVENT_SP_MON_STKUSGCHK                          TRC_EVENT_LAST_ID + 20
#define PSF_EVENT_SP_MON_STKUSGCHK_FAILED                   TRC_EVENT_LAST_ID + 21
#define PSF_EVENT_SP_MON_MPUCFGCHK                          TRC_EVENT_LAST_ID + 22
#endif

#ifndef COMMENTMACRO

#define spTraceStoreEvent_Param(_eventID, _param1) \
      SP_DO_PRIVIL(prvTraceEventCreate1(_eventID, _param1);)

#define spTraceStoreEvent_HandleParam(_eventID, _handle, _param1) \
      SP_DO_PRIVIL(prvTraceEventCreate2(_eventID, _handle, _param1);)

#define spTraceStoreEvent_HandleParamParam(_eventID, _handle, _param1, _param2) \
      SP_DO_PRIVIL(prvTraceEventCreate3(_eventID, _handle, _param1, _param2);)


/*
************************************************************************************************************************
*                                          uC/OS-II Trace Kernel-Related Macros
************************************************************************************************************************
*/
// #if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)
#if (defined(OS_TRACE_EN) && (OS_TRACE_EN > 0u))
#define  SP_TRACE_PROC_CREATE(phdl) \
	prvTraceEventCreate3(PSF_EVENT_SP_PROC_CREATE, phdl, phdl->Start, phdl->End);

#define  SP_TRACE_PROC_CREATE_FAILED(sa, ea, err) \
	prvTraceEventCreate3(PSF_EVENT_SP_PROC_CREATE_FAILED, (uint32_t)sa, (uint32_t)ea, (uint32_t)err);

#define  SP_TRACE_PROC_ASSIGN(phdl, prio) \
	prvTraceEventCreate3(PSF_EVENT_SP_PROC_ASSIGN, (void*)phdl, phdl->ProcID, (uint32_t)prio);

#define  SP_TRACE_PROC_ASSIGN_FAILED(phdl, prio, err) \
	prvTraceEventCreate3(PSF_EVENT_SP_PROC_ASSIGN_FAILED, (void*)phdl, (uint32_t)prio, (uint32_t)err);

#define  SP_TRACE_PROC_DEL(phdl) \
	prvTraceEventCreate2(PSF_EVENT_SP_PROC_DEL, (void*)phdl, (uint32_t)phdl->ProcID);

#define  SP_TRACE_PROC_DEL_FAILED(phdl, err) \
	prvTraceEventCreate2(PSF_EVENT_SP_PROC_DEL_FAILED, (void*)phdl, (uint32_t)err);

#define  SP_TRACE_PROC_GET(prio) \
	prvTraceEventCreate1(PSF_EVENT_SP_PROC_GET, (uint32_t)prio);

#define  SP_TRACE_PROC_KILL(prio) \
	prvTraceEventCreate1(PSF_EVENT_SP_PROC_KILL, (uint32_t)prio);

#define  SP_TRACE_SHM_CREATE(shdl) \
	prvTraceEventCreate3(PSF_EVENT_SP_SHM_CREATE, shdl, shdl->Start, shdl->End);

#define  SP_TRACE_SHM_CREATE_FAILED(sa, ea, err) \
	prvTraceEventCreate3(PSF_EVENT_SP_SHM_CREATE_FAILED, (uint32_t)sa, (uint32_t)ea, (uint32_t)err);

#define  SP_TRACE_SHM_ASSIGN(shdl, phdl) \
	prvTraceEventCreate3(PSF_EVENT_SP_SHM_ASSIGN, (void*)shdl, (uint32_t)phdl, phdl->ProcID);

#define  SP_TRACE_SHM_ASSIGN_FAILED(shdl, phdl, err) \
	prvTraceEventCreate3(PSF_EVENT_SP_SHM_ASSIGN_FAILED, (void*)shdl, (uint32_t)phdl, (uint32_t)err);

#define  SP_TRACE_THREAD_STKMONGET(prio) \
    prvTraceEventCreate1(PSF_EVENT_SP_THREAD_STKMONGET, prio);

#define  SP_TRACE_THREAD_STKMONGET_FAILED(prio, err) \
    prvTraceEventCreate1(PSF_EVENT_SP_THREAD_STKMONGET_FAILED, err);

#define  SP_TRACE_MONSTK_CREATE(mdata, la, ha, sp, opt) \
    prvTraceEventCreate3(PSF_EVENT_SP_MONSTK_CREATE, mdata, la, ha);

#define  SP_TRACE_MONSTK_CREATE_FAILED(mdata, la, ha, sp, opt, err) \
    prvTraceEventCreate3(PSF_EVENT_SP_MONSTK_CREATE_FAILED, mdata, sp, err);

#define  SP_TRACE_MONSTKPTR_CHECK(mdata, sp) \
    prvTraceEventCreate3(PSF_EVENT_SP_MONSTKPTR_CHECK, mdata, sp, mdata->Size);

#define  SP_TRACE_MONSTKPTR_CHECK_FAILED(mdata, sp, err) \
    prvTraceEventCreate3(PSF_EVENT_SP_MONSTKPTR_CHECK_FAILED, mdata, sp, err);

#define  SP_TRACE_MON_STKPATTERNCHK(mdat) \
    prvTraceEventCreate2(PSF_EVENT_SP_MON_STKPATTERNCHK, mdat, mdat->Size);

#define  SP_TRACE_MON_STKPATTERNCHK_FAILED(mdata, err) \
    prvTraceEventCreate2(PSF_EVENT_SP_MON_STKPATTERNCHK_FAILED, mdata, err);

#define  SP_TRACE_MON_STKUSGCHK(mdat, used) \
    prvTraceEventCreate3(PSF_EVENT_SP_MON_STKUSGCHK, mdat, *used, mdat->Size);

#define  SP_TRACE_MON_STKUSGCHK_FAILED(mdat, used, err) \
    prvTraceEventCreate3(PSF_EVENT_SP_MON_STKUSGCHK_FAILED, mdat, *used, err);

#define  SP_TRACE_MON_MPUCFGCHK() \
    spTraceStoreEvent_Param(PSF_EVENT_SP_MON_MPUCFGCHK, spErr);

#endif
// #endif
/*
************************************************************************************************************************
*                                                   API Functions
************************************************************************************************************************
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
