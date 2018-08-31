#include <name_sorting/name_sorting.h>

namespace name_sorting
{

  bool permutationName(  const std::vector<std::string>& order_names, 
                         std::vector<std::string>& names,
                         std::vector<double>& position, 
                         std::vector<double>& velocity, 
                         std::vector<double>& effort)
  {
    if (names.size()<order_names.size())
    {
      ROS_ERROR("names size (%zu) is smaller than order_names size (%zu)",names.size(),order_names.size());
      return false;
    }
    if (names.size()!=position.size())
    {
      ROS_ERROR("name size is %zu, position size is %zu",names.size(),position.size());
      return false;
    }
    if (names.size()!=velocity.size())
    {
      ROS_ERROR("name size is %zu, velocity size is %zu",names.size(),velocity.size());
      return false;
    }
    if (names.size()!=effort.size())
    {
      ROS_ERROR("name size is %zu, effort size is %zu",names.size(),effort.size());
      return false;
    }
    
    
    
    for (unsigned int iOrder=0;iOrder<order_names.size();iOrder++)
    {
      if (names.at(iOrder).compare(order_names.at(iOrder)))
      {
        for (unsigned int iNames=iOrder+1;iNames<names.size();iNames++)
        {
          if (!order_names.at(iOrder).compare(names.at(iNames)))
          { 
            std::iter_swap(names.begin()+iOrder,    names.begin()+iNames);
            std::iter_swap(position.begin()+iOrder, position.begin()+iNames);
            std::iter_swap(velocity.begin()+iOrder, velocity.begin()+iNames);
            std::iter_swap(effort.begin()+iOrder,   effort.begin()+iNames);
            break;
          }
          if (iNames==(names.size()-1))
          {
            ROS_ERROR("Joint %s missing",order_names.at(iOrder).c_str());
            return false;
          }
        }
      }
    }
    return true;
  }
  
  bool permutationName(  const std::vector<std::string>& order_names, 
                         std::vector<std::string>& names,
                         std::vector<double>& position, 
                         std::vector<double>& velocity)
  {
    if (names.size()<order_names.size())
    {
      ROS_ERROR("names size (%zu) is smaller than order_names size (%zu)",names.size(),order_names.size());
      return false;
    }
    if (names.size()!=position.size())
    {
      ROS_ERROR("name size is %zu, position size is %zu",names.size(),position.size());
      return false;
    }
    if (names.size()!=velocity.size())
    {
      ROS_ERROR("name size is %zu, velocity size is %zu",names.size(),velocity.size());
      return false;
    }
    
    for (unsigned int iOrder=0;iOrder<order_names.size();iOrder++)
    {
      if (names.at(iOrder).compare(order_names.at(iOrder)))
      {
        for (unsigned int iNames=iOrder+1;iNames<names.size();iNames++)
        {
          if (!order_names.at(iOrder).compare(names.at(iNames)))
          { 
            std::iter_swap(names.begin()+iOrder,    names.begin()+iNames);
            std::iter_swap(position.begin()+iOrder, position.begin()+iNames);
            std::iter_swap(velocity.begin()+iOrder, velocity.begin()+iNames);
            break;
          }
          if (iNames==(names.size()-1))
          {
            ROS_ERROR("Joint %s missing",order_names.at(iOrder).c_str());
            return false;
          }
        }
      }
    }
    return true;
  }                                
  bool permutationName(  const std::vector<std::string>& order_names, 
                         std::vector<std::string>& names,
                         std::vector<double>& position)
  {
    if (names.size()<order_names.size())
    {
      ROS_ERROR("names size (%zu) is smaller than order_names size (%zu)",names.size(),order_names.size());
      return false;
    }
    if (names.size()!=position.size())
    {
      ROS_ERROR("name size is %zu, position size is %zu",names.size(),position.size());
      return false;
    }
    
    for (unsigned int iOrder=0;iOrder<order_names.size();iOrder++)
    {
      if (names.at(iOrder).compare(order_names.at(iOrder)))
      {
        for (unsigned int iNames=iOrder+1;iNames<names.size();iNames++)
        {
          if (!order_names.at(iOrder).compare(names.at(iNames)))
          { 
            std::iter_swap(names.begin()+iOrder,    names.begin()+iNames);
            std::iter_swap(position.begin()+iOrder, position.begin()+iNames);
            break;
          }
          if (iNames==(names.size()-1))
          {
            ROS_ERROR("Joint %s missing",order_names.at(iOrder).c_str());
            return false;
          }
        }
      }
    }
    return true;
  }
  
  
}
