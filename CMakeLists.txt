project(ptz-controller VERSION 1.0.0)
set(PROJECT_FULL_NAME "PTZ Controller")

set(ptz-controller_HEADERS
	locale.h
	controller.hpp
	dockwidget.hpp
	joystickwidget.hpp
	presetwidget.hpp
	settingsdialog.hpp)

set(ptz-controller_SOURCES
	module.c
	controller.cpp
	dockwidget.cpp
	joystickwidget.cpp
	presetwidget.cpp
	settingsdialog.cpp)

add_library(ptz-controller MODULE
	${ptz-controller_HEADERS}
	${ptz-controller_SOURCES})

find_package(Qt5Network REQUIRED)
target_link_libraries(ptz-controller
		obs-frontend-api
		libobs
		Qt5::Widgets
		Qt5::Core
		Qt5::Network)

install_obs_plugin_with_data(ptz-controller data)
