#
# Copyright (c) 2018 - 2020 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#
add_subdirectory_ifdef(CONFIG_APP_EVENT_MANAGER	app_event_manager)
add_subdirectory_ifdef(CONFIG_APP_EVENT_MANAGER	app_event_manager_profiler_tracer)
add_subdirectory_ifdef(CONFIG_EVENT_MANAGER_PROXY event_manager_proxy)
add_subdirectory_ifdef(CONFIG_CAF caf)
