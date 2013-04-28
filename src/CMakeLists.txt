
#
# Components, types and plugins.
#
# The CMake 'target' names are identical to the first argument of the
# macros below, except for orocos_typegen_headers, where the target is fully
# controlled by generated code of 'typegen'.
#

# Creates a component library libURRealTime-<target>.so
# and installs in the directory lib/orocos/URRealTime/
#
orocos_component(URRealTime URRealTime-component.hpp URRealTime-component.cpp) # ...you may add multiple source files
#
# You may add multiple orocos_component statements.

#
# Additional headers:
#
# Installs in the include/orocos/URRealTime/ directory
#
orocos_install_headers(URRealTime-component.hpp) # ...you may add multiple header files
#
# You may add multiple orocos_install_headers statements.

#
# Building a Plugin
#
# Creates a plugin library libURRealTime-plugin-<target>.so
# and installs in the directory lib/orocos/URRealTime/plugins/
#
# Be aware that a plugin may only have the loadRTTPlugin() function once defined in a .cpp file.
# This function is defined by the plugin and service CPP macros.
#
orocos_plugin(URRealTime-plugin URRealTime-plugin.cpp) # ...only one plugin function per library !
#
# You may add multiple orocos_plugin statements.


#
# Building a Service:
#
# Creates a plugin library libURRealTime-service-<target>.so
# and installs in the directory lib/orocos/URRealTime/plugins/
#
orocos_service(URRealTime-service URRealTime-service.cpp) # ...only one service per library !
#
# You may add multiple orocos_service statements.


#
# Building a typekit using typegen (recommended):
#
# Creates a typekit library libURRealTime-types-<target>.so
# and installs in the directory lib/orocos/@target@/URRealTime/types/
#
# The header will go in include/orocos/URRealTime/types/URRealTime/URRealTime-types.hpp
# So you can #include <URRealTime/URRealTime-types.hpp>
#
orocos_typegen_headers(include/URRealTime/URRealTime-types.hpp) # ...you may add multiple header files
#
# You may only have *ONE* orocos_typegen_headers statement in your toplevel CMakeFile.txt !


#
# Building a normal library (optional):
#
# Creates a library libsupport-<target>.so and installs it in
# lib/
#
orocos_library(support support.cpp) # ...you may add multiple source files
#
# You may add multiple orocos_library statements.


