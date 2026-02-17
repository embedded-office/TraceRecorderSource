/*
 * Trace Recorder for Tracealyzer v4.11.0
 * Copyright 2025 Percepio AB
 * www.percepio.com
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * For bare-metal use of Tracealyzer (no RTOS)
 */

#ifndef TRC_KERNEL_PORT_H
#define TRC_KERNEL_PORT_H

#include <trcDefines.h>

#ifdef __cplusplus
extern "C" {
#endif

#if (defined(OS_TRACE_EN) && (OS_TRACE_EN > 0u))
#undef OS_TRACE_INIT
#undef OS_TRACE_START
#undef OS_TRACE_STOP
#undef OS_TRACE_CLEAR
#define  OS_TRACE_INIT()                                      xTraceInitialize()
#define  OS_TRACE_START()                                     xTraceEnable(TRC_START)
#define  OS_TRACE_STOP()                                      xTraceDisable()
#define  OS_TRACE_CONTROL()                                   xTraceTzCtrl()
#define  OS_TRACE_CLEAR()                                     
#endif

#define TRC_USE_TRACEALYZER_RECORDER (TRC_CFG_USE_TRACEALYZER_RECORDER) /* Allows for disabling the recorder */

#if (TRC_USE_TRACEALYZER_RECORDER == 1)
	
#undef TRC_CFG_ENABLE_STACK_MONITOR
#define TRC_CFG_ENABLE_STACK_MONITOR 0

/*** Don't change the below definitions, unless you know what you are doing! ***/

#define TRACE_KERNEL_VERSION 0x1FF1

/* Dummy definitions, since no RTOS */
#define TRC_TICK_RATE_HZ 1 /* Must not be 0. */

/**
 * @def TRACE_CPU_CLOCK_HZ
 * @brief Trace CPU clock speed in Hz.
 */
#define TRACE_CPU_CLOCK_HZ TRC_CFG_CPU_CLOCK_HZ

#if (TRC_CFG_RECORDER_BUFFER_ALLOCATION == TRC_RECORDER_BUFFER_ALLOCATION_DYNAMIC)
#include <stdlib.h> /* Include malloc() */

/**
 * @internal Kernel port specific heap initialization
 */
#define TRC_KERNEL_PORT_HEAP_INIT(size)

/**
 * @internal Kernel port specific heap malloc definition
 */
#define TRC_KERNEL_PORT_HEAP_MALLOC(size) malloc(size)
#endif

/**
 * @internal Kernel port specific platform configuration. Maximum name length is 8!
 */

/**
 * @def TRC_PLATFORM_CFG
 * @brief This defines the basis for version specific lookup of
 * platform configuration files.
 * Should match the intended XML configuration file name.
 */
#define TRC_PLATFORM_CFG "FS-RTOS"

/**
 * @def TRC_PLATFORM_CFG_MAJOR
 * @brief Major release version for platform definition file.
 * Should match the intended XML configuration file name.
 */
#define TRC_PLATFORM_CFG_MAJOR 1

/**
 * @def TRC_PLATFORM_CFG_MINOR
 * @brief Minor release version for platform definition file.
 * Should match the intended XML configuration file name.
 */
#define TRC_PLATFORM_CFG_MINOR 0

/**
 * @def TRC_PLATFORM_CFG_PATCH
 * @brief Patchlevel release version for platform definition file.
 * Should match the intended XML configuration file name.
 */
#define TRC_PLATFORM_CFG_PATCH 0

#ifndef TRACE_ENTER_CRITICAL_SECTION
	#error "This hardware port has no definition for critical sections! See https://percepio.com/how-to-define-critical-sections-for-the-recorder/"
#endif

#define TRC_KERNEL_PORT_BUFFER_SIZE (sizeof(TraceTaskHandle_t) * (TRC_CFG_CORE_COUNT))

/**
 * @internal The kernel port data buffer
 */
typedef struct TraceKernelPortDataBuffer	/* Aligned */
{
	uint8_t buffer[TRC_KERNEL_PORT_BUFFER_SIZE];
} TraceKernelPortDataBuffer_t;

/**
 * @internal Initializes the kernel port
 * 
 * @param[in] pxBuffer Kernel port data buffer
 *
 * @retval TRC_FAIL Failure
 * @retval TRC_SUCCESS Success
 */
traceResult xTraceKernelPortInitialize(TraceKernelPortDataBuffer_t* const pxBuffer);

/**
 * @internal Enables the kernel port
 * 
 * @retval TRC_FAIL Failure
 * @retval TRC_SUCCESS Success
 */
traceResult xTraceKernelPortEnable(void);

/**
 * @internal Not used for BareMetal
 *
 * @param[in] uiTicks Tick count to delay
 * 
 * @retval TRC_FAIL Failure
 * @retval TRC_SUCCESS Success
 */
#define xTraceKernelPortDelay(uiTicks) TRC_COMMA_EXPR_TO_STATEMENT_EXPR_2((void)uiTicks, TRC_SUCCESS)

/**
 * @internal Query if scheduler is suspended. For Bare Metal systems this will always be false.
 *
 * @retval 1 Scheduler suspended
 * @retval 0 Scheduler not suspended
 */
#define xTraceKernelPortIsSchedulerSuspended() (0U)

/*************************************************************************/
/* KERNEL SPECIFIC OBJECT CONFIGURATION									 */
/*************************************************************************/

/*******************************************************************************
 * The event codes - should match the offline config file.
 ******************************************************************************/

// /*** Event codes for streaming - should match the Tracealyzer config file *****/
// #define PSF_EVENT_NULL_EVENT								0x00UL

// #define PSF_EVENT_TRACE_START								0x01UL
// #define PSF_EVENT_TS_CONFIG									0x02UL
// #define PSF_EVENT_OBJ_NAME									0x03UL
// #define PSF_EVENT_TASK_PRIORITY								0x04UL
// #define PSF_EVENT_DEFINE_ISR								0x05UL

// #define PSF_EVENT_IFE_NEXT									0x08UL
// #define PSF_EVENT_IFE_DIRECT								0x09UL

// #define PSF_EVENT_TASK_CREATE								0x10UL
// #define PSF_EVENT_TASK_DELETE								0x11UL
// #define PSF_EVENT_PROCESS_CREATE							0x12UL
// #define PSF_EVENT_PROCESS_DELETE							0x13UL
// #define PSF_EVENT_THREAD_CREATE								0x14UL
// #define PSF_EVENT_THREAD_DELETE								0x15UL

// #define PSF_EVENT_TASK_READY								0x20UL
// #define PSF_EVENT_ISR_BEGIN									0x21UL
// #define PSF_EVENT_ISR_RESUME								0x22UL
// #define PSF_EVENT_TS_BEGIN									0x23UL
// #define PSF_EVENT_TS_RESUME									0x24UL
// #define PSF_EVENT_TASK_ACTIVATE								0x25UL

// #define PSF_EVENT_MALLOC									0x30UL
// #define PSF_EVENT_FREE										0x31UL
// #define PSF_EVENT_MALLOC_FAILED								0x32UL
// #define PSF_EVENT_FREE_FAILED								0x33UL

// #define PSF_EVENT_LOWPOWER_BEGIN							0x38UL
// #define PSF_EVENT_LOWPOWER_END								0x39UL

// #define PSF_EVENT_STATEMACHINE_STATE_CREATE					0x40UL
// #define PSF_EVENT_STATEMACHINE_CREATE						0x41UL
// #define PSF_EVENT_STATEMACHINE_STATECHANGE					0x42UL

// #define PSF_EVENT_INTERVAL_CHANNEL_CREATE					0x43UL
// #define PSF_EVENT_INTERVAL_START							0x44UL
// #define PSF_EVENT_INTERVAL_STOP								0x45UL
// #define PSF_EVENT_INTERVAL_CHANNEL_SET_CREATE				0x46UL

// #define PSF_EVENT_EXTENSION_CREATE							0x47UL

// #define PSF_EVENT_HEAP_CREATE								0x48UL

// #define PSF_EVENT_COUNTER_CREATE							0x49UL
// #define PSF_EVENT_COUNTER_CHANGE							0x4AUL
// #define PSF_EVENT_COUNTER_LIMIT_EXCEEDED					0x4BUL

#define PSF_EVENT_DEPENDENCY_REGISTER						0x4CUL

#define PSF_EVENT_RUNNABLE_REGISTER							0x4DUL
#define PSF_EVENT_RUNNABLE_START							0x4EUL
#define PSF_EVENT_RUNNABLE_STOP								0x4FUL

// #define PSF_EVENT_USER_EVENT								0x50UL

#define PSF_EVENT_USER_EVENT_FIXED							0x58UL

// #define TRC_EVENT_LAST_ID									(PSF_EVENT_USER_EVENT_FIXED + 8ul)

/*******************************************************************************
 * The event codes - should match the offline config file.
 ******************************************************************************/

#define PSF_EVENT_NULL_EVENT								0x00

/* PSF event codes */
#define PSF_EVENT_TRACE_START								0x01
#define PSF_EVENT_TS_CONFIG									0x02
#define PSF_EVENT_OBJ_NAME									0x03
#define PSF_EVENT_TASK_PRIORITY								0x04
#define PSF_EVENT_TASK_PRIO_INHERIT							0x05
#define PSF_EVENT_TASK_PRIO_DISINHERIT						0x06
#define PSF_EVENT_DEFINE_ISR								0x07
#define PSF_EVENT_UNUSED_STACK								0x08

#define PSF_EVENT_TASK_CREATE								0x10
#define PSF_EVENT_MBOX_CREATE								0x11
#define PSF_EVENT_QUEUE_CREATE								0x13
#define PSF_EVENT_SEMAPHORE_CREATE					        0x14
#define PSF_EVENT_MUTEX_CREATE								0x15
#define PSF_EVENT_FLAG_CREATE							    0x16
#define PSF_EVENT_MEM_CREATE							    0x17
#define PSF_EVENT_TMR_CREATE							    0x18

#define PSF_EVENT_TASK_DELETE								0x20
#define PSF_EVENT_QUEUE_DELETE								0x21
#define PSF_EVENT_SEMAPHORE_DELETE							0x22
#define PSF_EVENT_MUTEX_DELETE								0x23
#define PSF_EVENT_FLAG_DELETE					   		    0x24
#define PSF_EVENT_MEM_DELETE								0x25

#define PSF_EVENT_TASK_READY								0x30
#define PSF_EVENT_NEW_TIME									0x31
#define PSF_EVENT_NEW_TIME_SCHEDULER_SUSPENDED				0x32
#define PSF_EVENT_ISR_BEGIN									0x33
#define PSF_EVENT_ISR_RESUME								0x34
#define PSF_EVENT_TS_BEGIN									0x35
#define PSF_EVENT_TS_RESUME									0x36
#define PSF_EVENT_TASK_ACTIVATE								0x37

#define PSF_EVENT_MALLOC									0x38
#define PSF_EVENT_FREE										0x39

#define PSF_EVENT_LOWPOWER_BEGIN							0x3A
#define PSF_EVENT_LOWPOWER_END								0x3B

#define PSF_EVENT_IFE_NEXT									0x3C
#define PSF_EVENT_IFE_DIRECT								0x3D

#define PSF_EVENT_TASK_CREATE_FAILED						0x40
#define PSF_EVENT_QUEUE_CREATE_FAILED						0x41
#define PSF_EVENT_SEMAPHORE_CREATE_FAILED			        0x42
#define PSF_EVENT_MUTEX_CREATE_FAILED						0x43
#define PSF_EVENT_FLAG_CREATE_FAILED						0x44
#define PSF_EVENT_MEM_CREATE_FAILED					        0x45

#define PSF_EVENT_SEM_SEND				        			0x52
#define PSF_EVENT_Q_SEND		    						0x53
#define PSF_EVENT_MUTEX_SEND								0x54
#define PSF_EVENT_FLAG_SEND						    		0x55
#define PSF_EVENT_MEM_SEND						    		0x56

#define PSF_EVENT_SEM_SEND_FAILED				        	0x59
#define PSF_EVENT_Q_SEND_FAILED		    					0x5A
#define PSF_EVENT_MUTEX_SEND_FAILED					    	0x5B
#define PSF_EVENT_FLAG_SEND_FAILED					   		0x5C
#define PSF_EVENT_MEM_SEND_FAILED					   		0x5D

#define PSF_EVENT_SEM_RECEIVE				       			0x62
#define PSF_EVENT_Q_RECEIVE		    						0x63
#define PSF_EVENT_MUTEX_RECEIVE								0x64
#define PSF_EVENT_FLAG_RECEIVE					    		0x65
#define PSF_EVENT_MEM_RECEIVE					    		0x66

#define PSF_EVENT_SEM_RECEIVE_FAILED		      			0x72
#define PSF_EVENT_Q_RECEIVE_FAILED		    				0x73
#define PSF_EVENT_MUTEX_RECEIVE_FAILED						0x74
#define PSF_EVENT_FLAG_RECEIVE_FAILED			    		0x75
#define PSF_EVENT_MEM_RECEIVE_FAILED			    		0x76

#define PSF_EVENT_SEM_RECEIVE_BLOCK				        	0x82
#define PSF_EVENT_Q_RECEIVE_BLOCK		    				0x83
#define PSF_EVENT_MUTEX_RECEIVE_BLOCK						0x84
#define PSF_EVENT_FLAG_RECEIVE_BLOCK					  	0x85
#define PSF_EVENT_MEM_RECEIVE_BLOCK				    		0x86

#define PSF_EVENT_TASK_DELAY								0xAA
#define PSF_EVENT_TASK_SUSPEND								0xAB
#define PSF_EVENT_TASK_RESUME								0xAC
#define PSF_EVENT_TASK_SUSPEND_FAILED						0xAD
#define PSF_EVENT_TASK_RESUME_FAILED						0xAE

#define PSF_EVENT_USER_EVENT								0xB4
#define PSF_EVENT_USER_EVENT_2								0xB5
#define PSF_EVENT_USER_EVENT_3								0xB6
#define PSF_EVENT_USER_EVENT_4								0xB7
#define PSF_EVENT_USER_EVENT_5								0xB8
#define PSF_EVENT_USER_EVENT_6								0xB9
#define PSF_EVENT_USER_EVENT_7								0xBA
#define PSF_EVENT_USER_EVENT_8								0xBB

#define PSF_EVENT_TASK_NAME_SET								0xBC

#define PSF_EVENT_NAME_SET									0xBD

#define PSF_EVENT_Q_POST_ENTER								0xBE
#define PSF_EVENT_Q_POST_FRONT_ENTER						0xBF
#define PSF_EVENT_Q_POST_OPT_ENTER							0xC0
#define PSF_EVENT_Q_POST_EXIT								0xC1
#define PSF_EVENT_Q_POST_FRONT_EXIT							0xC2
#define PSF_EVENT_Q_POST_OPT_EXIT							0xC3
#define PSF_EVENT_Q_PEND_ENTER								0xC4
#define PSF_EVENT_Q_PEND_EXIT								0xC5
#define PSF_EVENT_Q_DEL_ENTER								0xC6
#define PSF_EVENT_Q_DEL_EXIT 								0xC7

#define PSF_EVENT_SEM_POST_ENTER							0xC8
#define PSF_EVENT_SEM_POST_EXIT								0xC9
#define PSF_EVENT_SEM_PEND_ENTER							0xCA
#define PSF_EVENT_SEM_PEND_EXIT								0xCB
#define PSF_EVENT_SEM_DEL_ENTER								0xCC
#define PSF_EVENT_SEM_DEL_EXIT 								0xCD

#define PSF_EVENT_MUTEX_POST_ENTER							0xCE
#define PSF_EVENT_MUTEX_POST_EXIT							0xCF
#define PSF_EVENT_MUTEX_PEND_ENTER							0xD0
#define PSF_EVENT_MUTEX_PEND_EXIT							0xD1
#define PSF_EVENT_MUTEX_DEL_ENTER							0xD2
#define PSF_EVENT_MUTEX_DEL_EXIT 							0xD3

#define PSF_EVENT_FLAG_POST_ENTER							0xD4
#define PSF_EVENT_FLAG_POST_EXIT							0xD5
#define PSF_EVENT_FLAG_PEND_ENTER							0xD6
#define PSF_EVENT_FLAG_PEND_EXIT							0xD7
#define PSF_EVENT_FLAG_DEL_ENTER							0xD8
#define PSF_EVENT_FLAG_DEL_EXIT 							0xD9

#define PSF_EVENT_TMR_START_ENTER							0xDA
#define PSF_EVENT_TMR_START_EXIT							0xDB
#define PSF_EVENT_TMR_STOP_ENTER							0xDC
#define PSF_EVENT_TMR_STOP_EXIT								0xDD
#define PSF_EVENT_TMR_DEL_ENTER								0xDE
#define PSF_EVENT_TMR_DEL_EXIT 								0xDF
#define PSF_EVENT_TMR_EXPIRED 								0xE0

#define PSF_EVENT_MEM_PUT_ENTER								0xE1
#define PSF_EVENT_MEM_PUT_EXIT								0xE2
#define PSF_EVENT_MEM_GET_ENTER								0xE3
#define PSF_EVENT_MEM_GET_EXIT								0xE4

#define PSF_EVENT_ISR_ENTER									0xE5
#define PSF_EVENT_ISR_EXIT									0xE6
#define PSF_EVENT_ISR_EXIT_TO_SCHEDULER						0xE7

#define PSF_EVENT_MBOX_POST_ENTER							0xE9
#define PSF_EVENT_MBOX_POST_EXIT							0xEA
#define PSF_EVENT_MBOX_POST_OPT_ENTER						0xEB
#define PSF_EVENT_MBOX_POST_OPT_EXIT						0xEC
#define PSF_EVENT_MBOX_PEND_ENTER							0xED
#define PSF_EVENT_MBOX_PEND_EXIT							0xEE
#define PSF_EVENT_MBOX_DEL_ENTER							0xEF
#define PSF_EVENT_MBOX_DEL_EXIT 							0xF0

#define PSF_EVENT_EXTENSION_CREATE							0xF1

#define PSF_EVENT_HEAP_CREATE								0xF2

#define PSF_EVENT_COUNTER_CREATE							0xF3
#define PSF_EVENT_COUNTER_CHANGE							0xF4
#define PSF_EVENT_COUNTER_LIMIT_EXCEEDED					0xF5

#define PSF_EVENT_MUTEX_TAKE_RECURSIVE_BLOCK				0xF6

#define PSF_EVENT_INTERVAL_CHANNEL_CREATE					0xF7
#define PSF_EVENT_INTERVAL_START							0xF8

#define PSF_EVENT_INTERVAL_STOP								0xF9
#define PSF_EVENT_INTERVAL_CHANNEL_SET_CREATE				0xFA

#define PSF_EVENT_STATEMACHINE_STATE_CREATE					0xFB
#define PSF_EVENT_STATEMACHINE_CREATE						0xFC
#define PSF_EVENT_STATEMACHINE_STATECHANGE					0xFD

#define PSF_EVENT_MALLOC_FAILED								0xFE
#define PSF_EVENT_FREE_FAILED								0xFF

#define PSF_FLAG_EVENT_NAME_SET                             0x100
#define PSF_MEM_EVENT_NAME_SET                              0x101

#define TRC_EVENT_LAST_ID									(PSF_MEM_EVENT_NAME_SET + 1u)

/*** The trace macros for streaming ******************************************/
extern void* prvTrcTickTask;
#define TRACE_IF_NOT_TICK_TASK(p_tcb) if (prvTrcTickTask != (void*)p_tcb)

/* Called in OSTaskCreate */
/* Need to protect critical section without reallocating the SR.                     */
#undef OS_TRACE_TASK_CREATE
#define OS_TRACE_TASK_CREATE(p_tcb) \
	xTraceTaskRegisterWithoutHandle((void*)(p_tcb), (const char*)(p_tcb)->OSTCBTaskName, (TraceUnsignedBaseType_t)(p_tcb)->OSTCBPrio)
#undef OS_TRACE_TASK_NAME_SET
#define OS_TRACE_TASK_NAME_SET(p_tcb) \
    if (p_tcb != 0 && xTraceIsRecorderEnabled()) \
	{ \
    	xTraceObjectSetNameWithoutHandle(p_tcb, (const char*)p_tcb->OSTCBTaskName); \
    	xTraceRegisterString((const char*)p_tcb->OSTCBTaskName); \
		prvTraceEventCreate2(PSF_EVENT_TASK_NAME_SET, (void*)p_tcb, (uint32_t)p_tcb->OSTCBPrio); \
	} \
/* Called in OSTaskCreate, if it fails (typically if the stack can not be allocated) */
/* No need to protect critical section. */
#undef OS_TRACE_TASK_CREATE_FAILED
#define OS_TRACE_TASK_CREATE_FAILED(p_tcb) \
	prvTraceEventCreate2(PSF_EVENT_TASK_CREATE_FAILED, 0, 0)

/* Called on OSTaskDel */
/* No need to protect critical section. */
/* If this macro give you problem try increase optimization. */
#undef OS_TRACE_TASK_DEL
#define OS_TRACE_TASK_DEL(p_tcb) \
	xTraceTaskUnregisterWithoutHandle((void*)(p_tcb), (TraceUnsignedBaseType_t)(p_tcb)->OSTCBPrio)

/* Called for each task that becomes ready */
/* No need to protect critical section. */
#undef OS_TRACE_TASK_READY
#define OS_TRACE_TASK_READY( p_tcb ) \
	TRACE_IF_NOT_TICK_TASK(p_tcb) \
	{ \
		xTraceTaskReady((void*)(p_tcb)); \
	}

/* Called on each OS tick. Will call uiPortGetTimestamp to make sure it is called at least once every OS tick. */
/* No need to protect critical section. */
#if (TRC_CFG_INCLUDE_OSTICK_EVENTS == 1)
#undef OS_TRACE_TICK_INCREMENT

// { xTraceTimestampSetOsTickCount(OSTickCtr); prvTraceEventCreate1(PSF_EVENT_NEW_TIME, OSTickCtr); }
#define OS_TRACE_TICK_INCREMENT( OSTickCtr ) 	\
	do {                                                 \
	        if (xTraceIsRecorderEnabled()) {                         \
	            xTraceTimestampSetOsTickCount(OSTickCtr);         \
				prvTraceEventCreate1(PSF_EVENT_NEW_TIME, OSTickCtr); \
	        }                                                \
	    } while (0)

#else /* (TRC_CFG_INCLUDE_OSTICK_EVENTS == 1) */
#define OS_TRACE_TICK_INCREMENT( OSTickCtr ) 
#endif /* (TRC_CFG_INCLUDE_OSTICK_EVENTS == 1) */

extern volatile uint32_t uiTraceSystemState;

/* Called on each task-switch */
/* No need to protect critical section. */
#undef OS_TRACE_TASK_SWITCHED_IN
#define OS_TRACE_TASK_SWITCHED_IN(p_tcb) \
	TRACE_IF_NOT_TICK_TASK(p_tcb) \
	{ \
		xTraceTaskSwitch((void*)(p_tcb), (TraceUnsignedBaseType_t)(p_tcb)->OSTCBPrio); \
	}
	
#if (TRC_CFG_SCHEDULING_ONLY == 0)

/* Called on OSTaskSuspend */
/* No need to protect critical section. */
#undef OS_TRACE_TASK_SUSPEND
#define OS_TRACE_TASK_SUSPEND( p_tcb ) \
	if ((p_tcb) == 0) \
	{ \
		prvTraceEventCreate1(PSF_EVENT_TASK_SUSPEND, OSTCBCur); \
	} \
	else \
	{ \
		prvTraceEventCreate1(PSF_EVENT_TASK_SUSPEND, p_tcb); \
	}

#if (TRACE_CFG_USE_TICKLESS_IDLE != 0)

/* NOT USED */
/* No need to protect critical section. */
#undef traceLOW_POWER_IDLE_BEGIN
#define traceLOW_POWER_IDLE_BEGIN() \
	prvTraceStoreEvent_None(PSF_EVENT_LOWPOWER_BEGIN);

/* NOT USED */
/* No need to protect critical section. */
#undef traceLOW_POWER_IDLE_END
#define traceLOW_POWER_IDLE_END() \
	prvTraceStoreEvent_None(PSF_EVENT_LOWPOWER_END);

#endif

/* Called on OSTimeDly */
/* No need to protect critical section. */
#undef OS_TRACE_TASK_DLY
#define OS_TRACE_TASK_DLY(dly_ticks) \
	prvTraceEventCreate1(PSF_EVENT_TASK_DELAY, dly_ticks);

/* Called on OSEventNameSet */
/* No need to protect critical section. */
#undef OS_TRACE_EVENT_NAME_SET
#define OS_TRACE_EVENT_NAME_SET(p_event, p_name)                                                                      \
{                                                                                                                     \
    if (xTraceIsRecorderEnabled()) {                         \
		xTraceObjectSetNameWithoutHandle(p_event, (const char*)p_name);                                                   \
		if (((OS_EVENT*)p_event)->OSEventType <=  OS_EVENT_TYPE_MUTEX) {                                                  \
			prvTraceEventCreate2(PSF_EVENT_NAME_SET, (void*)p_event, ((OS_EVENT*)p_event)->OSEventType);        \
		} else if(((OS_FLAG_GRP*)p_event)->OSFlagType ==  OS_EVENT_TYPE_FLAG) {                                             \
			prvTraceEventCreate2(PSF_FLAG_EVENT_NAME_SET, (void*)p_event, ((OS_FLAG_GRP*)p_event)->OSFlagType); \
		} else {                                                                                                          \
			prvTraceEventCreate2(PSF_MEM_EVENT_NAME_SET, (void*)p_event, ((OS_MEM*)p_event)->OSMemBlkSize);     \
		}                                                                                                                 \
	}\
}

#undef OS_TRACE_MBOX_DEL_ENTER
#define OS_TRACE_MBOX_DEL_ENTER(p_mbox, opt) \
	xTraceObjectUnregisterWithoutHandle(PSF_EVENT_MBOX_DEL_ENTER, (void*)p_mbox, (TraceUnsignedBaseType_t)opt)

#undef OS_TRACE_MBOX_DEL_EXIT
#define OS_TRACE_MBOX_DEL_EXIT(RetVal) \
	xTraceObjectUnregisterWithoutHandle(PSF_EVENT_MBOX_DEL_EXIT, (void*)pevent, (TraceUnsignedBaseType_t)RetVal)

/* Called on OSQDel */
/* No need to protect critical section. */
#undef OS_TRACE_Q_DEL
#define OS_TRACE_Q_DEL( p_q ) \
	xTraceObjectUnregisterWithoutHandle(PSF_EVENT_QUEUE_DELETE, (void*)(p_q), 0)

#undef OS_TRACE_Q_DEL_ENTER
#define OS_TRACE_Q_DEL_ENTER(p_q, opt) \
	xTraceObjectUnregisterWithoutHandle(PSF_EVENT_Q_DEL_ENTER, (void*)p_q, (TraceUnsignedBaseType_t)opt)

#undef OS_TRACE_Q_DEL_EXIT
#define OS_TRACE_Q_DEL_EXIT(RetVal) \
	xTraceObjectUnregisterWithoutHandle(PSF_EVENT_MBOX_DEL_ENTER, (void*)pevent, (TraceUnsignedBaseType_t)RetVal)

/* Called on OSMutexDel */
/* No need to protect critical section. */
#undef OS_TRACE_MUTEX_DEL
#define OS_TRACE_MUTEX_DEL( p_mutex ) \
	xTraceObjectUnregisterWithoutHandle(PSF_EVENT_MUTEX_DELETE, (void*)(p_mutex), 0)

#undef OS_TRACE_MUTEX_DEL_ENTER
#define OS_TRACE_MUTEX_DEL_ENTER(p_mutex, opt) \
	xTraceObjectUnregisterWithoutHandle(PSF_EVENT_MUTEX_DEL_ENTER, (void*)p_mutex, (TraceUnsignedBaseType_t)opt)

#undef OS_TRACE_MUTEX_DEL_EXIT
#define OS_TRACE_MUTEX_DEL_EXIT(RetVal) \
	xTraceObjectUnregisterWithoutHandle(PSF_EVENT_MUTEX_DEL_EXIT, (void*)pevent, (TraceUnsignedBaseType_t)RetVal)

/* Called on OSSemDel */
/* No need to protect critical section. */
#undef OS_TRACE_SEM_DEL
#define OS_TRACE_SEM_DEL( p_sem ) \
	xTraceObjectUnregisterWithoutHandle(PSF_EVENT_SEMAPHORE_DELETE, (void*)(p_sem), 0)

#undef OS_TRACE_SEM_DEL_ENTER
#define OS_TRACE_SEM_DEL_ENTER(p_sem, opt) \
	xTraceObjectUnregisterWithoutHandle(PSF_EVENT_SEM_DEL_ENTER, (void*)p_sem, (TraceUnsignedBaseType_t)opt)

#undef OS_TRACE_SEM_DEL_EXIT
#define OS_TRACE_SEM_DEL_EXIT(RetVal) \
	xTraceObjectUnregisterWithoutHandle(PSF_EVENT_SEM_DEL_EXIT, (void*)pevent, (TraceUnsignedBaseType_t)RetVal)

/* Called on OSFlagDel */
/* No need to protect critical section. */
#undef OS_TRACE_FLAG_DEL
#define OS_TRACE_FLAG_DEL( p_grp ) \
	xTraceObjectUnregisterWithoutHandle(PSF_EVENT_FLAG_DELETE, (void*)(p_grp), 0)


#undef OS_TRACE_FLAG_DEL_ENTER
#define OS_TRACE_FLAG_DEL_ENTER(p_grp, opt) \
	xTraceObjectUnregisterWithoutHandle(PSF_EVENT_FLAG_DEL_ENTER, (void*)pgrp, (TraceUnsignedBaseType_t)opt)

#undef OS_TRACE_FLAG_DEL_EXIT
#define OS_TRACE_FLAG_DEL_EXIT(RetVal) \
	xTraceObjectUnregisterWithoutHandle(PSF_EVENT_FLAG_DEL_EXIT, (void*)pgrp, (TraceUnsignedBaseType_t)RetVal)

#undef OS_TRACE_MBOX_CREATE
#define OS_TRACE_MBOX_CREATE(p_mbox, p_name) \
	prvTraceEventCreate2(PSF_EVENT_MBOX_CREATE, (void*)p_mbox, (uint32_t)p_mbox->OSEventType);

/* Called from os_q.c. */
/* No need to protect critical section. */
#undef OS_TRACE_Q_CREATE
#define OS_TRACE_Q_CREATE(p_q, p_name ) \
	prvTraceEventCreate2(PSF_EVENT_QUEUE_CREATE, (void*)p_q, ((OS_Q*)p_q->OSEventPtr)->OSQSize);

/* Called from OSSemCreate. */
/* No need to protect critical section. */
#undef OS_TRACE_SEM_CREATE
#define OS_TRACE_SEM_CREATE( p_sem, p_name) \
    prvTraceEventCreate2(PSF_EVENT_SEMAPHORE_CREATE, (void*)p_sem, p_sem->OSEventCnt); \

/* Called from OSMutexCreate. */
/* No need to protect critical section. */
#undef OS_TRACE_MUTEX_CREATE
#define OS_TRACE_MUTEX_CREATE( p_mutex, p_name ) \
	prvTraceEventCreate2(PSF_EVENT_MUTEX_CREATE, (void*)p_mutex, p_mutex->OSEventType); \

/* Called from OSMemCreate. */
/* No need to protect critical section. */
#undef OS_TRACE_MEM_CREATE
#define OS_TRACE_MEM_CREATE( p_mem) \
	prvTraceEventCreate3(PSF_EVENT_MEM_CREATE, p_mem, p_mem->OSMemAddr, p_mem->OSMemBlkSize);

/* Called from OSFlagCreate. */
/* No need to protect critical section. */
#undef OS_TRACE_FLAG_CREATE
#define OS_TRACE_FLAG_CREATE( p_grp, p_name ) \
	prvTraceEventCreate2(PSF_EVENT_FLAG_CREATE, (uint32_t)p_grp, p_grp->OSFlagFlags); \

#undef OS_TRACE_MBOX_POST_ENTER
#define OS_TRACE_MBOX_POST_ENTER(p_mbox) \
		prvTraceEventCreate2(PSF_EVENT_MBOX_POST_ENTER, (uint32_t)p_mbox, (uint32_t)p_mbox->OSEventType);

#undef OS_TRACE_MBOX_POST_OPT_ENTER
#define OS_TRACE_MBOX_POST_OPT_ENTER(p_mbox, opt) \
		prvTraceEventCreate2(PSF_EVENT_MBOX_POST_OPT_ENTER, (void*)p_mbox, (uint8_t)opt);

#undef OS_TRACE_MBOX_POST_EXIT
#define OS_TRACE_MBOX_POST_EXIT(RetVal) \
		prvTraceEventCreate2(PSF_EVENT_MBOX_POST_EXIT, pevent, RetVal);

#undef OS_TRACE_MBOX_POST_OPT_EXIT
#define OS_TRACE_MBOX_POST_OPT_EXIT(RetVal) \
		prvTraceEventCreate2(PSF_EVENT_MBOX_POST_OPT_EXIT, pevent, RetVal);

/* Called when a signal is sent to a queue */
/* No need to protect critical section. */
#undef OS_TRACE_Q_POST
#define OS_TRACE_Q_POST(p_q) \
	if (p_q->MsgQ.NbrEntries >= p_q->MsgQ.NbrEntriesSize || OSMsgPool.NbrFree == 0u) \
	{ \
		prvTraceEventCreate2(PSF_EVENT_Q_SEND_FAILED, (void*)p_q, (uint8_t)(p_q->PendList.NbrEntries)); \
	} \
	else \
	{ \
		prvTraceEventCreate2(PSF_EVENT_Q_SEND, (void*)p_q, (uint8_t)(p_q->PendList.NbrEntries)); \
	}

#undef OS_TRACE_Q_POST_ENTER
#define OS_TRACE_Q_POST_ENTER(p_q) \
		prvTraceEventCreate2(PSF_EVENT_Q_POST_ENTER, (uint32_t)p_q, p_q->OSEventType);

#undef OS_TRACE_Q_POST_FRONT_ENTER
#define OS_TRACE_Q_POST_FRONT_ENTER(p_q) \
    	prvTraceEventCreate2(PSF_EVENT_Q_POST_FRONT_ENTER, (void*)p_q, p_q->OSEventType);

#undef OS_TRACE_Q_POST_OPT_ENTER
#define OS_TRACE_Q_POST_OPT_ENTER(p_q, opt) \
		prvTraceEventCreate2(PSF_EVENT_Q_POST_OPT_ENTER, (void*)p_q, (uint8_t)opt);

#undef OS_TRACE_Q_POST_EXIT
#define OS_TRACE_Q_POST_EXIT(RetVal) \
		prvTraceEventCreate2(PSF_EVENT_Q_POST_EXIT, pevent, RetVal);

#undef OS_TRACE_Q_POST_FRONT_EXIT
#define OS_TRACE_Q_POST_FRONT_EXIT(RetVal) \
		prvTraceEventCreate2(PSF_EVENT_Q_POST_FRONT_EXIT, pevent, RetVal);

#undef OS_TRACE_Q_POST_OPT_EXIT
#define OS_TRACE_Q_POST_OPT_EXIT(RetVal) \
		prvTraceEventCreate2(PSF_EVENT_Q_POST_OPT_EXIT, pevent, RetVal);

/* Called when a message failed to be sent to a queue (timeout) */
/* No need to protect critical section. */
#undef OS_TRACE_Q_POST_FAILED
#define OS_TRACE_Q_POST_FAILED(p_q) \
	prvTraceEventCreate2(PSF_EVENT_Q_SEND_FAILED, (void*)p_q, (uint8_t)(p_q->PendList.NbrEntries));

/* Called when a signal is sent to a semaphore */
/* No need to protect critical section. */
#undef OS_TRACE_SEM_POST
#define OS_TRACE_SEM_POST(p_sem) \
	if (p_sem->Ctr == (OS_SEM_CTR)-1) \
	{ \
		prvTraceEventCreate2(PSF_EVENT_SEM_SEND_FAILED, (void*)p_sem, (uint8_t)(p_sem->Ctr)); \
	} \
	else \
	{ \
		prvTraceEventCreate2(PSF_EVENT_SEM_SEND, (void*)p_sem, (uint8_t)(p_sem->Ctr)); \
	}

#undef OS_TRACE_SEM_POST_ENTER
#define OS_TRACE_SEM_POST_ENTER(p_sem) \
        prvTraceEventCreate2(PSF_EVENT_SEM_POST_ENTER, p_sem, (uint32_t)p_sem->OSEventType);

#undef OS_TRACE_SEM_POST_EXIT
#define OS_TRACE_SEM_POST_EXIT(RetVal) \
        prvTraceEventCreate2(PSF_EVENT_SEM_POST_EXIT, pevent, RetVal);

/* Called when a signal failed to be sent to a semaphore (timeout) */
/* No need to protect critical section. */
#undef OS_TRACE_SEM_POST_FAILED
#define OS_TRACE_SEM_POST_FAILED(p_tcb) \
	prvTraceEventCreate2(PSF_EVENT_SEM_SEND_FAILED, (void*)p_sem, (uint8_t)(p_sem->Ctr));

/* Called when a signal is sent to a mutex */
/* No need to protect critical section. */
#undef OS_TRACE_MUTEX_POST
#define OS_TRACE_MUTEX_POST(p_mutex) \
	prvTraceEventCreate1(PSF_EVENT_MUTEX_SEND, (uint32_t)p_mutex);

#undef OS_TRACE_MUTEX_POST_ENTER
#define OS_TRACE_MUTEX_POST_ENTER(p_mutex) \
		prvTraceEventCreate2(PSF_EVENT_MUTEX_POST_ENTER, (uint32_t)p_mutex, p_mutex->OSEventType);

#undef OS_TRACE_MUTEX_POST_EXIT
#define OS_TRACE_MUTEX_POST_EXIT(RetVal) \
		prvTraceEventCreate2(PSF_EVENT_MUTEX_POST_EXIT, pevent, RetVal);

/* Called when a message failed to be sent to a mutex (timeout) */
/* No need to protect critical section. */
#undef OS_TRACE_MUTEX_POST_FAILED
#define OS_TRACE_MUTEX_POST_FAILED(p_mutex) \
	prvTraceEventCreate1(PSF_EVENT_MUTEX_SEND_FAILED, (uint32_t)p_mutex);

/* Called when a signal is sent to a flag group */
/* No need to protect critical section. */
#undef OS_TRACE_FLAG_POST
#define OS_TRACE_FLAG_POST(p_grp) \
	switch (opt) \
	{ \
		case OS_OPT_POST_FLAG_SET: \
		case OS_OPT_POST_FLAG_SET | OS_OPT_POST_NO_SCHED: \
		case OS_OPT_POST_FLAG_CLR: \
		case OS_OPT_POST_FLAG_CLR | OS_OPT_POST_NO_SCHED: \
			prvTraceEventCreate1(PSF_EVENT_FLAG_SEND, (uint32_t)p_grp); \
			break; \
		default: \
			prvTraceEventCreate1(PSF_EVENT_FLAG_SEND_FAILED, (uint32_t)p_grp); \
			break; \
	}

/* Called when a message failed to be sent to a flag group (timeout) */
/* No need to protect critical section. */
#undef OS_TRACE_FLAG_POST_FAILED
#define OS_TRACE_FLAG_POST_FAILED(p_grp) \
	prvTraceEventCreate1(PSF_EVENT_FLAG_SEND_FAILED, (uint32_t)p_grp);

#undef OS_TRACE_FLAG_POST_ENTER
#define OS_TRACE_FLAG_POST_ENTER(p_grp, flags, opt) \
		prvTraceEventCreate3(PSF_EVENT_FLAG_POST_ENTER, (void*)p_grp, (uint32_t)flags, (uint32_t)opt);

#undef OS_TRACE_FLAG_POST_EXIT
#define OS_TRACE_FLAG_POST_EXIT(RetVal) \
        prvTraceEventCreate3(PSF_EVENT_FLAG_POST_EXIT, pgrp, flags, RetVal);

/* Called when a signal is sent to a memory partition */
/* No need to protect critical section. */
#undef OS_TRACE_MEM_PUT
#define OS_TRACE_MEM_PUT(p_mem) \
		prvTraceEventCreate2(PSF_EVENT_MEM_SEND, (void*)p_mem, (uint8_t)(p_mem->NbrFree));

/* Called when a message failed to be sent to a memory partition (timeout) */
/* No need to protect critical section. */
#undef OS_TRACE_MEM_PUT_FAILED
#define OS_TRACE_MEM_PUT_FAILED(p_mem) \
	prvTraceEventCreate1(PSF_EVENT_MEM_SEND_FAILED, (uint32_t)p_mem);

#undef OS_TRACE_MEM_PUT_ENTER
#define OS_TRACE_MEM_PUT_ENTER(p_mem, p_blk) \
		prvTraceEventCreate2(PSF_EVENT_MEM_PUT_ENTER, (void*)p_mem, (uint32_t)p_blk);

#undef OS_TRACE_MEM_PUT_EXIT
#define OS_TRACE_MEM_PUT_EXIT(RetVal) \
		prvTraceEventCreate2(PSF_EVENT_MEM_PUT_EXIT, pmem, (uint32_t)RetVal);

#undef OS_TRACE_MBOX_PEND_ENTER
#define OS_TRACE_MBOX_PEND_ENTER(p_mbox, timeout) \
	prvTraceEventCreate2(PSF_EVENT_MBOX_PEND_ENTER, (void*)p_mbox, (uint32_t)timeout);

#undef OS_TRACE_MBOX_PEND_EXIT
#define OS_TRACE_MBOX_PEND_EXIT(RetVal) \
	prvTraceEventCreate2(PSF_EVENT_MBOX_PEND_EXIT, pevent, (uint32_t)RetVal);

/* Called when a message is received from a semaphore */
/* No need to protect critical section. */
#undef OS_TRACE_SEM_PEND
#define OS_TRACE_SEM_PEND(p_sem) \
	prvTraceEventCreate2(PSF_EVENT_SEM_RECEIVE, (void*)p_sem, (uint8_t)(p_sem->Ctr));

#undef OS_TRACE_SEM_PEND_ENTER
#define OS_TRACE_SEM_PEND_ENTER(p_sem, timeout) \
	prvTraceEventCreate2(PSF_EVENT_SEM_PEND_ENTER, (void*)p_sem, (uint32_t)timeout);

#undef OS_TRACE_SEM_PEND_EXIT
#define OS_TRACE_SEM_PEND_EXIT(RetVal) \
	prvTraceEventCreate2(PSF_EVENT_SEM_PEND_EXIT, (uint32_t)pevent, RetVal);

/* Called when a message is received from a semaphore */
/* No need to protect critical section. */
#undef OS_TRACE_SEM_PEND_FAILED
#define OS_TRACE_SEM_PEND_FAILED(p_sem) \
	xTraceObjectSetNameWithoutHandle(p_sem, (const char*)p_sem->OSEventName); \
	prvTraceEventCreate2(PSF_EVENT_SEM_RECEIVE_FAILED, (void*)p_sem, (uint8_t)(p_sem->Ctr));

/* Called when a message is received from a semaphore */
/* No need to protect critical section. */
#undef OS_TRACE_SEM_PEND_BLOCK
#define OS_TRACE_SEM_PEND_BLOCK(p_sem) \
	prvTraceEventCreate2(PSF_EVENT_SEM_RECEIVE_BLOCK, (void*)p_sem, (uint8_t)(p_sem->Ctr));


/* Called when a message is received from a queue */
/* No need to protect critical section. */
#undef OS_TRACE_Q_PEND
#define OS_TRACE_Q_PEND(p_q) \
	prvTraceEventCreate2(PSF_EVENT_Q_RECEIVE, (void*)p_q, (uint8_t)(p_q->PendList.NbrEntries));

#undef OS_TRACE_Q_PEND_ENTER
#define OS_TRACE_Q_PEND_ENTER(p_q, timeout) \
	prvTraceEventCreate2(PSF_EVENT_Q_PEND_ENTER, (void*)p_q, (uint32_t)timeout);

#undef OS_TRACE_Q_PEND_EXIT
#define OS_TRACE_Q_PEND_EXIT(RetVal) \
    prvTraceEventCreate2(PSF_EVENT_Q_PEND_EXIT, (uint32_t)pevent, RetVal);

/* Called when a message is received from a queue */
/* No need to protect critical section. */
#undef OS_TRACE_Q_PEND_FAILED
#define OS_TRACE_Q_PEND_FAILED(p_q) \
	prvTraceEventCreate2(PSF_EVENT_Q_RECEIVE_FAILED, (void*)p_q, (uint8_t)(p_q->PendList.NbrEntries));

/* Called when a message is received from a queue */
/* No need to protect critical section. */
#undef OS_TRACE_Q_PEND_BLOCK
#define OS_TRACE_Q_PEND_BLOCK(p_q) \
	prvTraceEventCreate2(PSF_EVENT_Q_RECEIVE_BLOCK, (void*)p_q, (uint8_t)(p_q->PendList.NbrEntries));


/* Called when a signal is received from a mutex */
/* No need to protect critical section. */
#undef OS_TRACE_MUTEX_PEND
#define OS_TRACE_MUTEX_PEND(p_mutex) \
	prvTraceEventCreate1(PSF_EVENT_MUTEX_RECEIVE, (uint32_t)p_mutex);

#undef OS_TRACE_MUTEX_PEND_ENTER
#define OS_TRACE_MUTEX_PEND_ENTER(p_mutex, timeout) \
	prvTraceEventCreate2(PSF_EVENT_MUTEX_PEND_ENTER, (void*)p_mutex, (uint32_t)timeout);

#undef OS_TRACE_MUTEX_PEND_EXIT
#define OS_TRACE_MUTEX_PEND_EXIT(RetVal) \
	prvTraceEventCreate2(PSF_EVENT_MUTEX_PEND_EXIT, (uint32_t)pevent, RetVal);

/* Called when a signal is received from a mutex */
/* No need to protect critical section. */
#undef OS_TRACE_MUTEX_PEND_FAILED
#define OS_TRACE_MUTEX_PEND_FAILED(p_mutex) \
	prvTraceEventCreate1(PSF_EVENT_MUTEX_RECEIVE_FAILED, (void*)p_mutex);

/* Called when a signal is received from a mutex */
/* No need to protect critical section. */
#undef OS_TRACE_MUTEX_PEND_BLOCK
#define OS_TRACE_MUTEX_PEND_BLOCK(p_mutex) \
	prvTraceEventCreate1(PSF_EVENT_MUTEX_RECEIVE_BLOCK, (void*)p_mutex);

/* Called when a signal is received from a mutex */
/* No need to protect critical section. */
#undef OS_TRACE_FLAG_PEND_BLOCK
#define OS_TRACE_FLAG_PEND_BLOCK(p_grp) \
	prvTraceEventCreate1(PSF_EVENT_FLAG_RECEIVE_BLOCK, (uint32_t)p_grp);

/* Called when a signal is received from a flag group */
/* No need to protect critical section. */
#undef OS_TRACE_FLAG_PEND
#define OS_TRACE_FLAG_PEND(p_grp) \
	prvTraceEventCreate1(PSF_EVENT_FLAG_RECEIVE, (uint32_t)p_grp);

/* Called when a signal is received from a flag group */
/* No need to protect critical section. */
#undef OS_TRACE_FLAG_PEND_FAILED
#define OS_TRACE_FLAG_PEND_FAILED(p_grp) \
	prvTraceEventCreate1(PSF_EVENT_FLAG_RECEIVE_FAILED, (uint32_t)p_grp);

#undef OS_TRACE_FLAG_PEND_ENTER
#define OS_TRACE_FLAG_PEND_ENTER(p_grp, flags, timeout, opt) \
		prvTraceEventCreate3(PSF_EVENT_FLAG_PEND_ENTER, (void*)p_grp, (uint32_t)flags, (uint32_t)opt);

#undef OS_TRACE_FLAG_PEND_EXIT
#define OS_TRACE_FLAG_PEND_EXIT(RetVal) \
		prvTraceEventCreate3(PSF_EVENT_FLAG_PEND_EXIT, pgrp, flags, RetVal);

/* Called when a signal is received from a flag group */
/* No need to protect critical section. */
#undef OS_TRACE_MEM_GET_FAILED
#define OS_TRACE_MEM_GET_FAILED(p_mem) \
	prvTraceEventCreate2(PSF_EVENT_MEM_RECEIVE_FAILED, (void*)p_mem, (uint8_t)(p_mem->NbrFree));

#undef OS_TRACE_MEM_GET_ENTER
#define OS_TRACE_MEM_GET_ENTER(p_mem) \
		prvTraceEventCreate2(PSF_EVENT_MEM_GET_ENTER, p_mem, p_mem->OSMemFreeList);

#undef OS_TRACE_MEM_GET_EXIT
#define OS_TRACE_MEM_GET_EXIT(RetVal) \
		prvTraceEventCreate2(PSF_EVENT_MEM_GET_EXIT, pmem, (uint32_t)RetVal);

/* Called in OSTaskChangePrio */
#undef OS_TRACE_TASK_PRIO_CHANGE
#define OS_TRACE_TASK_PRIO_CHANGE( p_tcb, prio ) \
	xTraceObjectSetNameWithoutHandle(p_tcb, (const char*)p_tcb->OSTCBTaskName); \
	prvTraceEventCreate2(PSF_EVENT_TASK_PRIORITY, (void*)p_tcb, prio);
	
/* Called in by mutex operations, when the task's priority is changed to the one from the mutex's owner */
/* No need to protect critical section. */
#undef OS_TRACE_MUTEX_TASK_PRIO_INHERIT
#define OS_TRACE_MUTEX_TASK_PRIO_INHERIT( p_tcb, prio ) \
	prvTraceEventCreate2(PSF_EVENT_TASK_PRIO_INHERIT, (void*)p_tcb, prio);

/* Called in by mutex operations, when the task's priority is changed back to its original */
/* No need to protect critical section. */
#undef OS_TRACE_MUTEX_TASK_PRIO_DISINHERIT
#define OS_TRACE_MUTEX_TASK_PRIO_DISINHERIT( p_tcb, prio ) \
	prvTraceEventCreate2(PSF_EVENT_TASK_PRIO_DISINHERIT, (void*)p_tcb, prio);

/* Called in OSTaskResume */
/* No need to protect critical section. */
#undef OS_TRACE_TASK_RESUME
#define OS_TRACE_TASK_RESUME( p_tcb ) \
	xTraceObjectSetNameWithoutHandle(p_tcb, (const char*)p_tcb->OSTCBTaskName); \
	prvTraceEventCreate1(PSF_EVENT_TASK_RESUME, (uint32_t)p_tcb);


#endif

#endif

#ifdef __cplusplus
}
#endif

#endif