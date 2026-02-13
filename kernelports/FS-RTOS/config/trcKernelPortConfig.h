/*
 * Trace Recorder for Tracealyzer v4.11.0
 * Copyright 2025 Percepio AB
 * www.percepio.com
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Configuration parameters for the kernel port.
 * More settings can be found in trcKernelPortStreamingConfig.h.
 */

#ifndef TRC_KERNEL_PORT_CONFIG_H
#define TRC_KERNEL_PORT_CONFIG_H


#include <stdint.h>
#include "ucos_ii.h"
#include <trcDefines.h>

extern uint32_t HAL_CoreGetClkFreq(void);

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Setting this to 0 will completely disable the recorder
 */
#define TRC_CFG_USE_TRACEALYZER_RECORDER 1

/**
 * @brief Board CPU clock frequency in Hz. Must be changed from 0.
 */
#define TRC_CFG_CPU_CLOCK_HZ HAL_CoreGetClkFreq()

#ifdef __cplusplus
}
#endif

#endif /* TRC_KERNEL_PORT_CONFIG_H */
