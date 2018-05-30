/* mstar-tv.h - Keytable for mstar_tv Remote Controller
 *
 * keymap imported from ir-keymaps.c
 *
 * Copyright (c) 2010 by Mauro Carvalho Chehab <mchehab@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */


#include <media/rc-core.h>
//#include <media/rc-map.h>
#include <linux/module.h>
/*
 * Jimmy Hsu <jimmy.hsu@mstarsemi.com>
 * this is the remote control that comes with the mstar smart tv
 * which based on STAOS standard.
 */

static struct rc_map_table rc6_6amode_tv[] = {
    { 12, KEY_POWER },
    { 0, KEY_0 },
    { 1, KEY_1 },
    { 2, KEY_2 },
    { 3, KEY_3 },
    { 4, KEY_4 },
    { 5, KEY_5 },
    { 6, KEY_6 },
    { 7, KEY_7 },
    { 8, KEY_8 },
    { 9, KEY_9 },
    { 109, KEY_RED },
    { 110, KEY_GREEN },
    { 111, KEY_YELLOW },
    { 112, KEY_BLUE },
    { 88, KEY_UP },
    { 89, KEY_DOWN },
    { 90, KEY_LEFT },
    { 91, KEY_RIGHT },
    { 92, KEY_ENTER },
    { 30, KEY_CHANNELUP },
    { 31, KEY_CHANNELDOWN },
    { 16, KEY_VOLUMEUP },
    { 17, KEY_VOLUMEDOWN },
    { 84, KEY_MENU },
    { 85, KEY_BACK },
    { 13, KEY_MUTE },
    { 60, KEY_EXIT },
    { 55, KEY_RECORD },     // REC
    { 15, KEY_INFO },
    { 33, KEY_REWIND },
    { 32, KEY_FORWARD },
    { 56, KEY_PLAY },
    { 57, KEY_PAUSE },
    { 49, KEY_STOP },
    { 204, KEY_EPG },        // (C)EPG
    { 213, KEY_MEDIA },
    { 70, KEY_ARCHIVE },
    { 129, KEY_CONTEXT_MENU },
};

static struct rc_map_list rc6_6amode_map = {
	.map = {
		.scan    = rc6_6amode_tv,
		.size    = ARRAY_SIZE(rc6_6amode_tv),
		.rc_type = RC_TYPE_UNKNOWN,	/* Legacy IR type */
		.name    = RC_MAP_RC6_6AMODE,
	}
};

static int __init init_rc_map_rc6_6amode(void)
{
	return rc_map_register(&rc6_6amode_map);
}

static void __exit exit_rc_map_rc6_6amode(void)
{
	rc_map_unregister(&rc6_6amode_map);
}

module_init(init_rc_map_rc6_6amode)
module_exit(exit_rc_map_rc6_6amode)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab <mchehab@redhat.com>");
