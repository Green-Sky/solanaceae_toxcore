cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(solanaceae)

add_library(solanaceae_core
	./solanaceae/core/utils.hpp
	./solanaceae/core/utils.cpp

	./solanaceae/core/tox_interface.hpp
	./solanaceae/core/tox_interface.cpp
	./solanaceae/core/tox_event_interface.hpp

	./solanaceae/core/tox_default_impl.hpp
	./solanaceae/core/tox_default_impl.cpp
	./solanaceae/core/tox_event_provider_base.hpp
	./solanaceae/core/tox_event_provider_base.cpp

	./solanaceae/core/tox_event_logger.hpp
	./solanaceae/core/tox_event_logger.cpp
)

target_include_directories(solanaceae_core PUBLIC .)
target_compile_features(solanaceae_core PUBLIC cxx_std_17)
target_link_libraries(solanaceae_core PUBLIC
	toxcore
)

