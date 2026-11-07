/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Internal definitions shared by the offmode_charger objects.
 */
#ifndef __OFFMODE_CHARGER_INTERNAL_H
#define __OFFMODE_CHARGER_INTERNAL_H

#include <linux/types.h>

/*
 * Snapshot of the battery/charger state, -1 / S32_MIN mean "unknown".
 * status uses the POWER_SUPPLY_STATUS_* values.
 */
struct offmode_charger_state {
	int capacity;
	int status;
	int temp;		/* 0.1 degree C */
	int present;
	int online;

	/* session statistics, filled by the core */
	u32 power_uw;		/* instantaneous battery power */
	u64 charge_ms;		/* accumulated charging time */
	u32 avg_power_uw;	/* average power over the session */
};

/* offmode_charger_display.c */
int offmode_charger_display_init(void);
void offmode_charger_display_update(const struct offmode_charger_state *st,
				    bool anim);
void offmode_charger_display_shutdown(void);

/* offmode_charger_font.c */
const u8 *offmode_charger_font_glyph(unsigned char c);

/* offmode_charger_log.c */
void offmode_charger_log(const char *fmt, ...);
void offmode_charger_warn(const char *fmt, ...);
void offmode_charger_log_start(void);
void offmode_charger_log_flush(void);

/* normal events: always go to the kernel log and to /data */
#define pclog(fmt, ...)		offmode_charger_log(fmt, ##__VA_ARGS__)
#define pcwarn(fmt, ...)	offmode_charger_warn(fmt, ##__VA_ARGS__)

/* verbose per-poll / per-redraw lines, only with CONFIG_OFFMODE_CHARGER_DEBUG */
#ifdef CONFIG_OFFMODE_CHARGER_DEBUG
#define pcdbg(fmt, ...)		offmode_charger_log(fmt, ##__VA_ARGS__)
#else
#define pcdbg(fmt, ...)		do { } while (0)
#endif

#endif /* __OFFMODE_CHARGER_INTERNAL_H */
