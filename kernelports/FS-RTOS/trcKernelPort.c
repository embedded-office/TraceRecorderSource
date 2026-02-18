/*
 * Trace Recorder for Tracealyzer v4.11.0
 * Copyright 2025 Percepio AB
 * www.percepio.com
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * For bare-metal use of Tracealyzer (no RTOS)
 */

#include <stdint.h>
#include <trcRecorder.h>

#if (TRC_USE_TRACEALYZER_RECORDER == 1)

void* prvTrcTickTask = 0;

typedef struct TraceKernelPortData
{
	TraceTaskHandle_t xTaskHandles[TRC_CFG_CORE_COUNT];
} TraceKernelPortData_t;

static TraceKernelPortData_t* pxKernelPortData TRC_CFG_RECORDER_DATA_ATTRIBUTE;

traceResult xTraceKernelPortInitialize(TraceKernelPortDataBuffer_t* const pxBuffer)
{
	TRC_ASSERT_EQUAL_SIZE(TraceKernelPortData_t, TraceKernelPortDataBuffer_t);

	if (pxBuffer == 0)
    {
        return TRC_FAIL;
    }
	
	pxKernelPortData = (TraceKernelPortData_t*)pxBuffer; /*cstat !MISRAC2004-11.4 !MISRAC2012-Rule-11.3 Suppress conversion between pointer types checks*/
	
	return TRC_SUCCESS;
}

traceResult xTraceKernelPortEnable(void)
{
	/*xTraceTzCtrl is handled directly in the App Time tick call in the RTOS*/
	
	return TRC_SUCCESS;
}

#endif
