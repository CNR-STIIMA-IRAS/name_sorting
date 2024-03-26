#ifndef NAME_SORTING__SORT_TRAJECTORIES_H
#define NAME_SORTING__SORT_TRAJECTORIES_H

// ----
#include <trajectory_msgs/msg/joint_trajectory.hpp>
#include <Eigen/Core>
#include <Eigen/LU>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/logger.hpp>

namespace trajectory_processing
{

bool sort_trajectory(const std::vector<std::string>& joint_names,
                      const trajectory_msgs::msg::JointTrajectory& trj,
                        trajectory_msgs::msg::JointTrajectory& sorted_trj);

bool append_trajectories(trajectory_msgs::msg::JointTrajectory& trj,
                          const trajectory_msgs::msg::JointTrajectory& trj_to_be_appended);

void removeDuplicates(trajectory_msgs::msg::JointTrajectory& trj);

bool computeAccelerationVelocity(trajectory_msgs::msg::JointTrajectory& trj);

bool computeAccelerationVelocitySpline(trajectory_msgs::msg::JointTrajectory& trj);



}  // namespace trajectory_processing

#endif // NAME_SORTING__SORT_TRAJECTORIES_H
