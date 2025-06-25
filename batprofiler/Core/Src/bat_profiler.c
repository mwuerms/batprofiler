/**
 * bat profile, bp
 * Martin Egli
 * 2025-06-19
 */
#include <stdbool.h>
#include <stddef.h>
#include "tim.h"
#include "gpio.h"
#include "bat_profiler.h"
#include "str_buf.h"

/**
 * convert a given current to timer CCR value to generate a pwm
 * @param  iload   current to convert
 * @return pwm timer_ccr value for pwm generation:
 *   pwm = 0: 0.0 %
 *   pwm = 1935: 19.35 %
 *   pwm = 2025: 20.25 %
 *   pwm = 10000: 100.00 %
 */
static const uint32_t rload_in_mohm = 100UL;
static const uint32_t rdiff_r1_in_kohm = 560UL;
static const uint32_t rdiff_r2_in_kohm =  10UL;
static const uint32_t vcc_in_mV = 3000UL;
static inline uint16_t convert_mA_to_pwm(uint32_t iload) {
    //printf(" convert_mA_to_pwm(%u)\n", iload);
    iload = (iload * rload_in_mohm); // VLOAD in mV
    //printf("  [0]: %u (VLOAD = VREF in mV)\n", iload);
    iload = (iload * (rdiff_r1_in_kohm + rdiff_r2_in_kohm)) / rdiff_r2_in_kohm;
    //printf("  [1]: %u (VREF_PWM in mV)\n", iload);
    iload = (iload * 10);
    //printf("  [2]: %u (x 100)\n", iload);
    iload = (iload) / vcc_in_mV;
    //printf("  [3]: %u (TIM_CCR for pwm)\n", iload);
    return iload;
}

#define BAT_PROFILE_MAX_NB_STEPS (16)
typedef struct {
    uint16_t nb_steps, step;
    uint16_t iload[BAT_PROFILE_MAX_NB_STEPS];
    uint16_t pwm[BAT_PROFILE_MAX_NB_STEPS];
    uint16_t delay_ms[BAT_PROFILE_MAX_NB_STEPS];
} bprofile_t;

#define BAT_PROFILE_MAX_NB_PROFILES (6)
typedef struct {
    uint16_t nb_profiles, current, state;
    bprofile_t profiles[BAT_PROFILE_MAX_NB_PROFILES];
} bp_ctrl_t;
static bp_ctrl_t bp_ctrl;
#define BAT_PROFILE_CTRL_STATE_OFF (0)
#define BAT_PROFILE_CTRL_STATE_ON (1)

/**
 * print all bat profiles out to uart
 */
#define BP_STR_SIZE (128)
static char bp_str[BP_STR_SIZE];
#define uart_send_string_blocking(...)
void bp_print_out_profiles(void) {
    uint16_t i, n;
    str_buf_clear(bp_str, BP_STR_SIZE);
	str_buf_append_string(bp_str, BP_STR_SIZE, "\navailable profiles: ");
    str_buf_append_uint16(bp_str, BP_STR_SIZE, bp_ctrl.nb_profiles);
    str_buf_append_char(bp_str, BP_STR_SIZE, '\n');
    uart_send_string_blocking(bp_str);

    if(bp_ctrl.nb_profiles == 0) {
        // error, no profiles available
        str_buf_clear(bp_str, BP_STR_SIZE);
	    str_buf_append_string(bp_str, BP_STR_SIZE, "\n!there are none!\n");
        uart_send_string_blocking(bp_str);
        return;
    }

    for(i = 0; i < bp_ctrl.nb_profiles; i++) {
        str_buf_clear(bp_str, BP_STR_SIZE);
        str_buf_append_string(bp_str, BP_STR_SIZE, " + profile: ");
        str_buf_append_uint16(bp_str, BP_STR_SIZE, i);
        str_buf_append_string(bp_str, BP_STR_SIZE, "\n   + nb steps: ");
        str_buf_append_uint16(bp_str, BP_STR_SIZE, bp_ctrl.profiles[i].nb_steps);
        str_buf_append_char(bp_str, BP_STR_SIZE, '\n');
        uart_send_string_blocking(bp_str);

        str_buf_clear(bp_str, BP_STR_SIZE);
        str_buf_append_string(bp_str, BP_STR_SIZE, "   + iload: ");
        uart_send_string_blocking(bp_str);
        
        str_buf_clear(bp_str, BP_STR_SIZE);
        str_buf_append_char(bp_str, BP_STR_SIZE, '[');
        for(n = 0; n < bp_ctrl.profiles[i].nb_steps; n++) {
            str_buf_append_uint16(bp_str, BP_STR_SIZE, n);
            str_buf_append_string(bp_str, BP_STR_SIZE, "]: ");
            str_buf_append_uint16(bp_str, BP_STR_SIZE, bp_ctrl.profiles[i].iload[n]);
            if(n == (bp_ctrl.profiles[i].nb_steps -1)) {
                // last
                str_buf_append_char(bp_str, BP_STR_SIZE, '\n');
            }
            else {
                str_buf_append_string(bp_str, BP_STR_SIZE, ", [");
            }
        }
        uart_send_string_blocking(bp_str);

        str_buf_clear(bp_str, BP_STR_SIZE);
        str_buf_append_string(bp_str, BP_STR_SIZE, "   + pwm: ");
        uart_send_string_blocking(bp_str);

        str_buf_clear(bp_str, BP_STR_SIZE);
        str_buf_append_char(bp_str, BP_STR_SIZE, '[');
        for(n = 0; n < bp_ctrl.profiles[i].nb_steps; n++) {
            str_buf_append_uint16(bp_str, BP_STR_SIZE, n);
            str_buf_append_string(bp_str, BP_STR_SIZE, "]: ");
            str_buf_append_uint16(bp_str, BP_STR_SIZE, bp_ctrl.profiles[i].pwm[n]);
            if(n == (bp_ctrl.profiles[i].nb_steps -1)) {
                // last
                str_buf_append_char(bp_str, BP_STR_SIZE, '\n');
            }
            else {
                str_buf_append_string(bp_str, BP_STR_SIZE, ", [");
            }
        }
        uart_send_string_blocking(bp_str);

        str_buf_clear(bp_str, BP_STR_SIZE);
        str_buf_append_string(bp_str, BP_STR_SIZE, "   + delay_ms: ");
        uart_send_string_blocking(bp_str);

        str_buf_clear(bp_str, BP_STR_SIZE);
        str_buf_append_char(bp_str, BP_STR_SIZE, '[');
        for(n = 0; n < bp_ctrl.profiles[i].nb_steps; n++) {
            str_buf_append_uint16(bp_str, BP_STR_SIZE, n);
            str_buf_append_string(bp_str, BP_STR_SIZE, "]: ");
            str_buf_append_uint16(bp_str, BP_STR_SIZE, bp_ctrl.profiles[i].delay_ms[n]);
            if(n == (bp_ctrl.profiles[i].nb_steps -1)) {
                // last
                str_buf_append_char(bp_str, BP_STR_SIZE, '\n');
            }
            else {
                str_buf_append_string(bp_str, BP_STR_SIZE, ", [");
            }
        }
        uart_send_string_blocking(bp_str);
    }
}

static void bp_start_timer(void) {
	tim22_start();
}


static void bp_start_single_delay_ms(uint16_t delay_ms) {
    if(delay_ms == 0) {
        // error, do not start
        return;
    }
    tim22_ch1_start_single_timeout(delay_ms, EV_BPROFILER_TIMEOUT1);
}

static void bp_display_states_on_leds(uint16_t state, uint16_t current_profile, uint16_t current_step) {
    // state: LED0
	gpio_clear_led(LED0_MASK);
	gpio_set_led(state & 0x01);

    // current_profile: LED1, 2, 3
	gpio_clear_led(LED3_MASK|LED2_MASK|LED1_MASK);
	gpio_set_led(((current_profile + 1) & 0x07) << 1);

    // current_step: LED4, 5, 6, 7
	gpio_clear_led(LED7_MASK|LED6_MASK|LED5_MASK|LED4_MASK);
	gpio_set_led(((current_step + 1) & 0x0F) << 4);

    return;
}

static void bp_next_profile(bp_ctrl_t *b) {
    if(b == NULL) {
        // error, invalid
        return;
    }
    b->current++;
    if(b->current >= b->nb_profiles) {
        b->current = 0;
    }
}

static void bp_next_profile_step(bprofile_t* p) {
    if(p == NULL) {
        // error, invalid
        return;
    }
    p->step++;
    if(p->step >= p->nb_steps) {
        p->step = 0;
    }
}

static void bp_set_profile_step(bprofile_t* p, uint16_t s) {
    if(p == NULL) {
        // error, invalid
        return;
    }
    if(s >= p->nb_steps) {
        // error, invalid step, do not set
        return;
    }
    p->step = s;
}

static uint16_t bp_get_profile_delay(bprofile_t* p) {
    if(p == NULL) {
        // error, invalid
        return 0;
    }
    return p->delay_ms[p->step];
}

static uint16_t bp_get_profile_pwm(bprofile_t* p) {
    if(p == NULL) {
        // error, invalid
        return 0;
    }
    return p->pwm[p->step];
}

/**
 * add iload and delay_ms to a given profile, and convert iload to pwm value
 * @param    p          profile to add to
 * @param	 len		nb elements
 * @param    iload      values to add to
 * @param    delay_ms   values to add to
 * @return   true: OK could add, false: some error happened, did not add
 */
static uint16_t bp_add_bat_profile(bprofile_t *p, uint16_t len, uint16_t *iload, uint16_t *delay_ms) {
    uint16_t n;
    if(p == NULL) {
        // error, invalid profile
        return false;
    }
    if((len == 0) || (len > BAT_PROFILE_MAX_NB_STEPS)) {
        // error, no elements or to many elements
        return false;
    }
    p->nb_steps = len;
    p->step = 0;
    for(n = 0; n != len; n++) {
        p->iload[n] = iload[n];
        p->pwm[n] = convert_mA_to_pwm(iload[n]);
        p->delay_ms[n] = delay_ms[n];
    }
    return true;
}

// - public functions ----------------------------------------------------------
void bp_init(void) {
    // add profiles
    uint16_t set_iload[BAT_PROFILE_MAX_NB_STEPS];
	uint16_t set_delay_ms[BAT_PROFILE_MAX_NB_STEPS];
	uint16_t n;

    bp_ctrl.nb_profiles = 0;

    n = 0;
    set_iload[n] = 20;
    set_delay_ms[n++] = 60000;
    if(bp_add_bat_profile(&(bp_ctrl.profiles[bp_ctrl.nb_profiles]), n, set_iload, set_delay_ms) == true) {
        // OK
        bp_ctrl.nb_profiles++;
    }

    n = 0;
	set_iload[n] = 100;
	set_delay_ms[n++] = 60000;
	if(bp_add_bat_profile(&(bp_ctrl.profiles[bp_ctrl.nb_profiles]), n, set_iload, set_delay_ms) == true) {
		// OK
		bp_ctrl.nb_profiles++;
	}

	n = 0;
	set_iload[n] = 200;
	set_delay_ms[n++] = 60000;
	if(bp_add_bat_profile(&(bp_ctrl.profiles[bp_ctrl.nb_profiles]), n, set_iload, set_delay_ms) == true) {
		// OK
		bp_ctrl.nb_profiles++;
	}

	n = 0;
	set_iload[n] = 250;
	set_delay_ms[n++] = 60000;
	if(bp_add_bat_profile(&(bp_ctrl.profiles[bp_ctrl.nb_profiles]), n, set_iload, set_delay_ms) == true) {
		// OK
		bp_ctrl.nb_profiles++;
	}

    n = 0;
    set_iload[n] = 0;
    set_delay_ms[n++] = 10000;
    set_iload[n] = 10;
	set_delay_ms[n++] = 10000;
	set_iload[n] = 20;
	set_delay_ms[n++] = 10000;
	set_iload[n] = 50;
	set_delay_ms[n++] = 10000;
	set_iload[n] = 100;
	set_delay_ms[n++] = 10000;
	set_iload[n] = 150;
	set_delay_ms[n++] = 10000;
    if(bp_add_bat_profile(&(bp_ctrl.profiles[bp_ctrl.nb_profiles]), n, set_iload, set_delay_ms) == true) {
        // OK
        bp_ctrl.nb_profiles++;
    }

    n = 0;
	set_iload[n] = 0;
	set_delay_ms[n++] = 10000;
	set_iload[n] = 10;
	set_delay_ms[n++] = 10000;
	set_iload[n] = 0;
	set_delay_ms[n++] = 10000;
	set_iload[n] = 20;
	set_delay_ms[n++] = 10000;
	set_iload[n] = 0;
	set_delay_ms[n++] = 10000;
	set_iload[n] = 30;
	set_delay_ms[n++] = 10000;
    if(bp_add_bat_profile(&(bp_ctrl.profiles[bp_ctrl.nb_profiles]), n, set_iload, set_delay_ms) == true) {
        // OK
        bp_ctrl.nb_profiles++;
    }
}

void bp_start(void) {
    bp_ctrl.current = 0;
    bp_ctrl.state = BAT_PROFILE_CTRL_STATE_OFF;

    str_buf_clear(bp_str, BP_STR_SIZE);
    str_buf_append_string(bp_str, BP_STR_SIZE, "\n starting batprofiler");
    uart_send_string_blocking(bp_str);
    
    bp_start_timer();
    bp_display_states_on_leds(bp_ctrl.state, bp_ctrl.current, bp_ctrl.profiles[bp_ctrl.current].step);
}

void bp_process_events(uint16_t event) {
    if(bp_ctrl.state == BAT_PROFILE_CTRL_STATE_OFF) {
        switch(event) {
            case EV_BTN0_PRESSED:
                // nothing to do
                __NOP();
                break;
            case EV_BTN0_LONG:
                // start
                bp_ctrl.state = BAT_PROFILE_CTRL_STATE_ON;
                // 1st step
				bp_set_profile_step(&(bp_ctrl.profiles[bp_ctrl.current]), 0);
				bp_start_single_delay_ms(bp_get_profile_delay(&(bp_ctrl.profiles[bp_ctrl.current])));
				pwm_start(bp_get_profile_pwm(&(bp_ctrl.profiles[bp_ctrl.current])));
                break;
            case EV_BTN1_PRESSED:
                // next profile
                bp_next_profile(&bp_ctrl);
                break;
            case EV_BTN1_LONG:
                // nothing to do
                __NOP();
                break;
            case EV_TIMEOUT1:
                // nothing to do
                __NOP();
                break;
        }
    }
    else {
        switch(event) {
            case EV_BTN0_PRESSED:
                // nothing to do
                __NOP();
                break;
            case EV_BTN0_LONG:
                // stop
                bp_ctrl.state = BAT_PROFILE_CTRL_STATE_OFF;
                bp_set_profile_step(&(bp_ctrl.profiles[bp_ctrl.current]), 0);
                pwm_stop();
                break;
            case EV_BTN1_PRESSED:
                // nothing to do
                __NOP();
                break;
            case EV_BTN1_LONG:
                // nothing to do
                __NOP();
                break;
            case EV_TIMEOUT1:
                // next step
				bp_next_profile_step(&(bp_ctrl.profiles[bp_ctrl.current]));
				bp_start_single_delay_ms(bp_get_profile_delay(&(bp_ctrl.profiles[bp_ctrl.current])));
				pwm_start(bp_get_profile_pwm(&(bp_ctrl.profiles[bp_ctrl.current])));
                break;
        }
    }
    bp_display_states_on_leds(bp_ctrl.state, bp_ctrl.current, bp_ctrl.profiles[bp_ctrl.current].step);
}


#warning ___TODO_ put to uart.c
/*
adjust, code for stm32f103
uint16_t uart_init(void) {
    MX_USART1_UART_Init();
    fifo_init(&(uart_ctrl.tx_fifo), uart_tx_buffer, UART_BUFFER_SIZE);
    return true;
}

uint16_t uart_send_buffer(uint8_t *buffer, uint16_t length) {
    uint16_t n;
    for(n = 0; n < length; n++) {
        if(fifo_try_append(&(uart_ctrl.tx_fifo)) == false) {
            // fifo is full, stop here
            break;
        }
        ((uint8_t *)(uart_ctrl.tx_fifo.data))[uart_ctrl.tx_fifo.wr_proc] = buffer[n];
        fifo_finalize_append(&(uart_ctrl.tx_fifo));
    }
    uart_start_transmit();
    return n;
}

uint16_t uart_send_string(char *str) {
    uint16_t n, len;
    len = strlen(str);
    for(n = 0;n < len;n++) {
        if(str[n] == 0) {
            // end of string found, stop here
            break;
        }
        if(fifo_try_append(&(uart_ctrl.tx_fifo)) == false) {
            // fifo is full, stop here
            break;
        }
        ((uint8_t *)(uart_ctrl.tx_fifo.data))[uart_ctrl.tx_fifo.wr_proc] = str[n];
        fifo_finalize_append(&(uart_ctrl.tx_fifo));
    }

    uart_start_transmit();
    return n;
}

uint16_t uart_send_string_blocking(char *str) {
// implement
}
*/
