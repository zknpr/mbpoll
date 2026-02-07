/* Copyright (c) 2015-2025 Pascal JEAN, All rights reserved. */

#ifndef _CHIPIO_H_
#define _CHIPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mbpoll-config.h"
#include <stdbool.h>

struct xMbPollContext;

#ifdef USE_CHIPIO
#include <chipio/serial.h>
#include <sysio/rpi.h>
typedef struct xChipIoContext {
  int iSlaveAddr;
  int iIrqPin;
  xChipIo * xChip;
  xChipIoSerial * xChipSerial;
} xChipIoContext;
#else
typedef struct xChipIoContext {
  int iSlaveAddr;
  int iIrqPin;
} xChipIoContext;
#endif

/* functions ================================================================ */
bool bChipIoHandleOption(int opt, const char * optarg, struct xMbPollContext * ctx);
bool bChipIoSetup(struct xMbPollContext * ctx);
void vChipIoClose(struct xMbPollContext * ctx);
void vChipIoPrintUsageOptions(void);
const char * sChipIoGetAddStr(const struct xMbPollContext * ctx);

#ifdef __cplusplus
}
#endif

#endif /* _CHIPIO_H_ */
