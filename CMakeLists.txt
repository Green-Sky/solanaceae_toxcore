cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(solanaceae)

add_library(solanaceae_toxcore
	./solanaceae/toxcore/utils.hpp
	./solanaceae/toxcore/utils.cpp

	./solanaceae/toxcore/tox_interface.hpp
	./solanaceae/toxcore/tox_interface.cpp
	./solanaceae/toxcore/tox_event_interface.hpp

	./solanaceae/toxcore/tox_default_impl.hpp
	./solanaceae/toxcore/tox_default_impl.cpp
	./solanaceae/toxcore/tox_event_provider_base.hpp
	./solanaceae/toxcore/tox_event_provider_base.cpp

	./solanaceae/toxcore/tox_event_logger.hpp
	./solanaceae/toxcore/tox_event_logger.cpp
)

target_include_directories(solanaceae_toxcore PUBLIC .)
target_compile_features(solanaceae_toxcore PUBLIC cxx_std_17)
target_link_libraries(solanaceae_toxcore PUBLIC
	toxcore
)

