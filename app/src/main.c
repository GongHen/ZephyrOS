/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/reboot.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>

#include <zephyr/bindesc.h>


#include <app_event_manager.h>


#include <app_version.h>

#include "repo_version.h"


/* Module name is used by the Application Event Manager macros in this file */
#define MODULE main
#include <caf/events/module_state_event.h>

#include "modules_common.h"

LOG_MODULE_REGISTER(MODULE, CONFIG_APP_MODULE_LOG_LEVEL);


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

	if (app_event_manager_init()) {
		/* Without the Application Event Manager, the application will not work
		 * as intended. A reboot is required in an attempt to recover.
		 */
		LOG_ERR("Application Event Manager could not be initialized, rebooting...");
		k_sleep(K_SECONDS(5));
		sys_reboot(SYS_REBOOT_COLD);		
	} else {
		module_set_state(MODULE_STATE_READY);
	}	

	return 0;
}
