cmake_minimum_required(VERSION 2.8.3)
project(name_sorting)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/cnrConfigMacros.cmake)

cnr_set_flags()
###################

find_package(catkin REQUIRED COMPONENTS roscpp trajectory_msgs)
find_package(Eigen3 REQUIRED COMPONENTS Core)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES name_sorting
  CATKIN_DEPENDS roscpp trajectory_msgs
  DEPENDS 
)

include_directories(include ${catkin_INCLUDE_DIRS})

add_library(${PROJECT_NAME}
              src/${PROJECT_NAME}/name_sorting.cpp src/${PROJECT_NAME}/sort_trajectories.cpp)
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} ${EIGEN_LIBRARIES} Eigen3::Eigen)
add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
cnr_target_compile_options(${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} 
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
)

