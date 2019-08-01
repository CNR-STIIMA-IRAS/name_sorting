#include <name_sorting/name_sorting.h>

namespace name_sorting
{

  bool permutationName(  const std::vector<std::string>& order_names, 
                         std::vector<std::string>& names,
                         std::vector<double>& vector1,
                         std::vector<double>& vector2,
                         std::vector<double>& vector3)
  {
    if (names.size()<order_names.size())
    {
      ROS_ERROR("The vector of names to be sorted has size %zu, that is smaller than vector of the sorted names (%zu)",names.size(),order_names.size());
      return false;
    }
    if (names.size()!=vector1.size())
    {
      ROS_ERROR("name size is %zu, vector1 size is %zu",names.size(),vector1.size());
      return false;
    }
    if (names.size()!=vector2.size())
    {
      ROS_ERROR("name size is %zu, vector2 size is %zu",names.size(),vector2.size());
      return false;
    }
    if (names.size()!=vector3.size())
    {
      ROS_ERROR("name size is %zu, vector3 size is %zu",names.size(),vector3.size());
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
            std::iter_swap(vector1.begin()+iOrder, vector1.begin()+iNames);
            std::iter_swap(vector2.begin()+iOrder, vector2.begin()+iNames);
            std::iter_swap(vector3.begin()+iOrder,   vector3.begin()+iNames);
            break;
          }
          if (iNames==(names.size()-1))
          {
            ROS_ERROR("Joint %s missing",order_names.at(iOrder).c_str());

            std::stringstream ss;
            ROS_ERROR("The Joint '%s' that is in the vector of the sorted names, is missing in the vector to be sorted.",order_names.at(iOrder).c_str());

            ss << "Sorted Names: <";
            for( size_t i=0;i<order_names.size();i++)
              ss << order_names.at(i) <<",";
            ss << "> vs Names to be ordered: <";
            for( size_t i=0;i<names.size();i++)
              ss << names.at(i) <<",";
            ss <<">";
            ROS_ERROR_STREAM( ss.str() );

            return false;
          }
        }
      }
    }
    return true;
  }
  
  bool permutationName(  const std::vector<std::string>& order_names, 
                         std::vector<std::string>& names,
                         std::vector<double>& vector1,
                         std::vector<double>& vector2)
  {
    if (names.size()<order_names.size())
    {
      ROS_ERROR("names size (%zu) is smaller than order_names size (%zu)",names.size(),order_names.size());
      return false;
    }
    if (names.size()!=vector1.size())
    {
      ROS_ERROR("name size is %zu, vector1 size is %zu",names.size(),vector1.size());
      return false;
    }
    if (names.size()!=vector2.size())
    {
      ROS_ERROR("name size is %zu, vector2 size is %zu",names.size(),vector2.size());
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
            std::iter_swap(vector1.begin()+iOrder, vector1.begin()+iNames);
            std::iter_swap(vector2.begin()+iOrder, vector2.begin()+iNames);
            break;
          }
          if (iNames==(names.size()-1))
          {
            ROS_ERROR("Joint %s missing",order_names.at(iOrder).c_str());
            std::stringstream ss;
            ss << "Sorted Names: <";
            for( size_t i=0;i<order_names.size();i++)
              ss << order_names.at(i) <<",";
            ss << "> vs Names to be ordered: <";
            for( size_t i=0;i<names.size();i++)
              ss << names.at(i) <<",";
            ss <<">";
            ROS_ERROR_STREAM( ss.str() );
            return false;
          }
        }
      }
    }
    return true;
  }                                
  bool permutationName(  const std::vector<std::string>& order_names, 
                         std::vector<std::string>& names,
                         std::vector<double>& vector1)
  {
    if (names.size()<order_names.size())
    {
      ROS_ERROR("names size (%zu) is smaller than order_names size (%zu)",names.size(),order_names.size());
      return false;
    }
    if (names.size()!=vector1.size())
    {
      ROS_ERROR("name size is %zu, vector1 size is %zu",names.size(),vector1.size());
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
            std::iter_swap(vector1.begin()+iOrder, vector1.begin()+iNames);
            break;
          }
          if (iNames==(names.size()-1))
          {
            ROS_ERROR("Joint %s missing",order_names.at(iOrder).c_str());
            std::stringstream ss;
            ss << "Sorted Names: <";
            for( size_t i=0;i<order_names.size();i++)
              ss << order_names.at(i) <<",";
            ss << "> vs Names to be ordered: <";
            for( size_t i=0;i<names.size();i++)
              ss << names.at(i) <<",";
            ss <<">";
            ROS_ERROR_STREAM( ss.str() );
            return false;
          }
        }
      }
    }
    return true;
  }
  
  
}

