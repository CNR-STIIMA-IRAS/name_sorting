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
/**
 * @brief Sorts a trajectory based on the specified order of joint names.
 *
 * @param joint_names The desired order of joint names.
 * @param trj The original trajectory to be sorted.
 * @param sorted_trj The resulting sorted trajectory.
 * @return bool True if the trajectory was successfully sorted, false otherwise.
 */
bool sort_trajectory(const std::vector<std::string>& joint_names,
                      const trajectory_msgs::msg::JointTrajectory& trj,
                        trajectory_msgs::msg::JointTrajectory& sorted_trj);

/**
 * @brief Appends a trajectory to another, ensuring that joint names are in the same order.
 *
 * @param trj The main trajectory to which another trajectory is appended.
 * @param trj_to_be_appended The trajectory to append.
 * @return bool True if the append operation was successful, false otherwise.
 */
bool append_trajectories(trajectory_msgs::msg::JointTrajectory& trj,
                          const trajectory_msgs::msg::JointTrajectory& trj_to_be_appended);

/**
 * @brief Removes duplicate points from a trajectory based on a specified tolerance.
 *
 * @param trj The trajectory from which duplicates will be removed.
 */
void removeDuplicates(trajectory_msgs::msg::JointTrajectory& trj);

/**
 * @brief Calculates the velocities and accelerations for each point in a trajectory.
 *
 * @param trj The trajectory for which to compute velocities and accelerations.
 * @return bool True if computations were successful, false otherwise.
 */
bool computeAccelerationVelocity(trajectory_msgs::msg::JointTrajectory& trj);

bool computeAccelerationVelocitySpline(trajectory_msgs::msg::JointTrajectory& trj);



}  // namespace trajectory_processing

#endif // NAME_SORTING__SORT_TRAJECTORIES_H
