


#include <name_sorting/sort_trajectories.hpp>
// ----

namespace trajectory_processing
{
bool sort_trajectory(const std::vector<std::string>& joint_names, const trajectory_msgs::msg::JointTrajectory &trj, trajectory_msgs::msg::JointTrajectory &sorted_trj)
{
  const std::vector<std::string>& names=trj.joint_names;
  if (names.size()!=joint_names.size())
  {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Joint names dimensions are different");
    return false;
  }
  std::vector<int> order_idx(joint_names.size());



  for (unsigned int iOrder=0;iOrder<joint_names.size();iOrder++)
  {
    RCLCPP_DEBUG( rclcpp::get_logger("rclcpp"), "index %u, original trajectory %s, sorted trajectory %s",iOrder,names.at(iOrder).c_str(),joint_names.at(iOrder).c_str());
    if (names.at(iOrder).compare(joint_names.at(iOrder)))
    {
      for (unsigned int iNames=0;iNames<names.size();iNames++)
      {
        if (!joint_names.at(iOrder).compare(names.at(iNames)))
        {
          order_idx.at(iOrder)=iNames;
          RCLCPP_DEBUG(rclcpp::get_logger("rclcpp"), "Joint %s (index %u) of original trajectory will be in position %u",names.at(iNames).c_str(),iOrder,iNames);
          break;
        }
        if (iNames==(names.size()-1))
        {
          RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Joint %s missing",joint_names.at(iOrder).c_str());
          return false;
        }
      }
    }
    else
    {
      order_idx.at(iOrder)=iOrder;
      RCLCPP_DEBUG(rclcpp::get_logger("rclcpp"), "Joint %s (index %u) of original trajectory will be in position %u",names.at(iOrder).c_str(),iOrder,iOrder);
    }
  }

  sorted_trj.joint_names=joint_names;
  sorted_trj.header=trj.header;

  for (const trajectory_msgs::msg::JointTrajectoryPoint& pnt: trj.points)
  {
    sorted_trj.points.push_back(pnt);
    for (unsigned int iOrder=0;iOrder<joint_names.size();iOrder++)
    {
      sorted_trj.points.back().positions.at(iOrder)=pnt.positions.at(order_idx.at(iOrder));
      if (pnt.velocities.size()>0)
        sorted_trj.points.back().velocities.at(iOrder)=pnt.velocities.at(order_idx.at(iOrder));
      if (pnt.accelerations.size()>0)
        sorted_trj.points.back().accelerations.at(iOrder)=pnt.accelerations.at(order_idx.at(iOrder));
      if (pnt.effort.size()>0)
        sorted_trj.points.back().effort.at(iOrder)=pnt.effort.at(order_idx.at(iOrder));
    }
  }
  return true;
}


bool append_trajectories(trajectory_msgs::msg::JointTrajectory& trj, const trajectory_msgs::msg::JointTrajectory& trj_to_be_appended)
{
  trajectory_msgs::msg::JointTrajectory sorted_trj_to_be_appended;
  if (!sort_trajectory(trj.joint_names,trj_to_be_appended,sorted_trj_to_be_appended))
    return false;


  rclcpp::Duration delta(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(0.001)));
  rclcpp::Duration end_of_original_trj(trj.points.back().time_from_start);
  end_of_original_trj=end_of_original_trj+delta;
  for (const trajectory_msgs::msg::JointTrajectoryPoint& pnt: sorted_trj_to_be_appended.points)
  {
    trj.points.push_back(pnt);
    rclcpp::Duration t=pnt.time_from_start;
    trj.points.back().time_from_start=t+end_of_original_trj;
  }

  return true;
}

void removeDuplicates(trajectory_msgs::msg::JointTrajectory& trj)
{
  for (unsigned int iPnt=1;iPnt<trj.points.size();iPnt++)
  {
    rclcpp::Duration t1=trj.points.at(iPnt-1).time_from_start;
    rclcpp::Duration t2=trj.points.at(iPnt).time_from_start;

    if ((t2.seconds()-t1.seconds())>1e-6)
    {
      break;
    }

    for (unsigned int iax=0;iax<trj.points.at(iPnt).positions.size();iax++)
    {
      if (std::abs(trj.points.at(iPnt).positions.at(iax)-trj.points.at(iPnt-1).positions.at(iax))>1e-4)
      {
        break;
      }
    }

    RCLCPP_FATAL(rclcpp::get_logger("rclcpp"), "erasing point %u",iPnt);
    trj.points.erase(trj.points.begin()+iPnt);
  }
  return;
}

bool computeAccelerationVelocity(trajectory_msgs::msg::JointTrajectory& trj)
{
  if (trj.points.size()<2)
  {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "trajectory should have at least 2 points");
    return false;
  }

  for (unsigned int iPnt=1;iPnt<trj.points.size();iPnt++)
  {
    trj.points.at(iPnt).velocities.resize(trj.points.at(iPnt).positions.size(),0);
    trj.points.at(iPnt).accelerations.resize(trj.points.at(iPnt).accelerations.size(),0);
  }

  for (unsigned int iPnt=1;iPnt<(trj.points.size());iPnt++)
  {
    rclcpp::Duration t1=trj.points.at(iPnt-1).time_from_start;
    rclcpp::Duration t2=trj.points.at(iPnt).time_from_start;
    double new_t=t1.seconds()+std::max(1.0e-5,t2.seconds()-t1.seconds());
    rclcpp::Duration new_time(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(new_t)));
    trj.points.at(iPnt).time_from_start=new_time;
  }

  for  (unsigned int iAx=0;iAx<trj.points.at(0).positions.size();iAx++)
  {

    for (unsigned int iPnt=1;iPnt<(trj.points.size()-1);iPnt++)
    {
      rclcpp::Duration t1=trj.points.at(iPnt-1).time_from_start;
      rclcpp::Duration t2=trj.points.at(iPnt+1).time_from_start;
      trj.points.at(iPnt).velocities.at(iAx)=(trj.points.at(iPnt+1).positions.at(iAx)-trj.points.at(iPnt-1).positions.at(iAx))/(t2.seconds()-t1.seconds());
    }

    //compute accelerations
    for (unsigned int iPnt=1;iPnt<(trj.points.size()-1);iPnt++)
    {
      rclcpp::Duration t1=trj.points.at(iPnt-1).time_from_start;
      rclcpp::Duration t2=trj.points.at(iPnt+1).time_from_start;
      trj.points.at(iPnt).accelerations.at(iAx)=(trj.points.at(iPnt+1).velocities.at(iAx)-trj.points.at(iPnt-1).velocities.at(iAx))/(t2.seconds()-t1.seconds());
    }
  }

  return true;
}

bool computeAccelerationVelocitySpline(trajectory_msgs::msg::JointTrajectory& trj)
{


  if (trj.points.size()<2)
  {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "trajectory should have at least 2 points");
    return false;
  }


  for (unsigned int iPnt=1;iPnt<trj.points.size();iPnt++)
  {
    trj.points.at(iPnt).velocities.resize(trj.points.at(iPnt).positions.size(),0);
    trj.points.at(iPnt).accelerations.resize(trj.points.at(iPnt).accelerations.size(),0);
  }

  for (unsigned int iPnt=1;iPnt<(trj.points.size());iPnt++)
  {
    rclcpp::Duration t1=trj.points.at(iPnt-1).time_from_start;
    rclcpp::Duration t2=trj.points.at(iPnt).time_from_start;
    double new_t=t1.seconds()+std::max(1.0e-5,t2.seconds()-t1.seconds());
    rclcpp::Duration new_time(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(new_t)));
    trj.points.at(iPnt).time_from_start=new_time;
  }
  for  (unsigned int iAx=0;iAx<trj.points.at(0).positions.size();iAx++)
  {
    // p(t) = p(0)+v*t + 0.5*a*t^2
    // p(0) = p(0)
    // p(t1) = p(0)+v*t1+0.5*a*(t1^2)
    // p(t2) = p(0)+v*t2+0.5*a*(t2^2)

    //    [t1 0.5*t1^2]  [v] = [p(t1)-p(0)]
    //    [t2 0.5*t2^2]  [a] = [p(t2)-p(0)]

    for (unsigned int iPnt=1;iPnt<(trj.points.size()-1);iPnt++)
    {
      rclcpp::Duration time_prev=trj.points.at(iPnt-1).time_from_start;
      rclcpp::Duration time=trj.points.at(iPnt).time_from_start;
      rclcpp::Duration time_post=trj.points.at(iPnt+1).time_from_start;

      double t1=time_prev.seconds()-time.seconds();
      double t2=time_post.seconds()-time.seconds();

      double dp1=trj.points.at(iPnt-1).positions.at(iAx)-trj.points.at(iPnt).positions.at(iAx);
      double dp2=trj.points.at(iPnt+1).positions.at(iAx)-trj.points.at(iPnt).positions.at(iAx);

      Eigen::MatrixXd mtx(2,2);
      mtx(0,0)= t1; mtx(0,1)=0.5*t1*t1;
      mtx(1,0)= t2; mtx(1,1)=0.5*t2*t2;
      Eigen::VectorXd dp(2);
      dp(0)=dp1;
      dp(1)=dp2;

      Eigen::VectorXd res=mtx.inverse()*dp;
      trj.points.at(iPnt-1).velocities.at(iAx)=res(0);
      trj.points.at(iPnt-1).accelerations.at(iAx)=res(1);

    }

  }

  return true;
}
}



