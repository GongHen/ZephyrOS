/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#include <zephyr/bindesc.h>

#include <app_version.h>

#include <stdio.h>
#include "repo_version.h"

LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);


int main(void)
{
	printk("Zephyr version: %s\n", BINDESC_GET_STR(kernel_version_string));
	printk("App version: %s\n", BINDESC_GET_STR(app_version_string));
	printk("Build time: %s\n", BINDESC_GET_STR(build_date_time_string));
	printk("Compiler: %s %s\n", BINDESC_GET_STR(c_compiler_name),
		BINDESC_GET_STR(c_compiler_version));

    // printk("App Version %d.%d-%s-%s\n", APP_VERSION_MAJOR, APP_VERSION_MINOR, REPO_DATE, REPO_HASH);
	// printk("version: %s\n", REPO_VERSION);
    // printk("date: %s\n", REPO_DATE);
    // printk("hash: %s\n", REPO_HASH);
	printk("App Version %s-%s-%s\n", BINDESC_GET_STR(app_version_string), REPO_DATE, REPO_HASH);
	
	// printk("App build version: %s\n", APP_BUILD_VERSION);
	return 0;
}
