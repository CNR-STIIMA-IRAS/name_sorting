cmake_minimum_required(VERSION 3.5)
project(name_sorting)

# XXX CHECK ###
#include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/cnrConfigMacros.cmake)
#cnr_set_flags()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(trajectory_msgs REQUIRED)
find_package(Eigen3 REQUIRED COMPONENTS Core)

set(ROS_VERSION $ENV{ROS_VERSION})
if(ROS_VERSION STREQUAL "")
  message(FATAL_ERROR "No supported version of ROS found!")
endif()

add_library(${PROJECT_NAME}
  src/${PROJECT_NAME}/name_sorting.cpp
  src/${PROJECT_NAME}/sort_trajectories.cpp)

target_compile_definitions(${PROJECT_NAME} PUBLIC -DROS_X=${ROS_VERSION})

ament_target_dependencies(${PROJECT_NAME} PUBLIC
  rclcpp
  trajectory_msgs)

include_directories(
   include
   ${EIGEN3_INCLUDE_DIRS}
 )
target_link_libraries(${PROJECT_NAME} PUBLIC
     Eigen3::Eigen
    ${trajectory_msgs_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC
"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
"$<INSTALL_INTERFACE:include/${PROJECT_NAME}>"
)

install(
  DIRECTORY include/
  DESTINATION include/${PROJECT_NAME}
)
install(
  TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
)
install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_package()
