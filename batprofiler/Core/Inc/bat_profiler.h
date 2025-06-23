/**
 * bat profile, bp
 * Martin Egli
 * 2025-06-19
 */

// - includes ------------------------------------------------------------------
#ifndef INC_BAT_PROFILER_H_
#define INC_BAT_PROFILER_H_

#include "main.h"


void bp_init(void);

#define EV_BTN0_PRESSED (0)
#define EV_BTN0_LONG (1)
#define EV_BTN1_PRESSED (2)
#define EV_BTN1_LONG (3)
#define EV_TIMEOUT1 (4)
void bp_process_events(uint16_t event);

#endif /* INC_BAT_PROFILER_H_ */
