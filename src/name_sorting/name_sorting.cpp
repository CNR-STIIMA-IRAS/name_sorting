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
      ROS_ERROR("The vector of names to be sorted has size %zu, that is smaller than vector of the sorted names (%zu)",names.size(),order_names.size());
      return false;
    }
    if (names.size()!=position.size())
    {
      ROS_ERROR("Input Mismatch. The size of the vector of names is %zu, while position size is %zu",names.size(),position.size());
      return false;
    }
    if (names.size()!=velocity.size())
    {
      ROS_ERROR("Input Mismatch. The size of the vector of names is %zu, while velocity size is %zu",names.size(),velocity.size());
      return false;
    }
    if (names.size()!=effort.size())
    {
      ROS_ERROR("Inut Mismatch. The size of the vecotr of the names is %zu, while effort size is %zu",names.size(),effort.size());
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
                         std::vector<double>& position, 
                         std::vector<double>& velocity)
  {
    if (names.size()<order_names.size())
    {
	  ROS_ERROR("The vector of names to be sorted has size %zu, that is smaller than vector of the sorted names (%zu)",names.size(),order_names.size());
      return false;
    }
    if (names.size()!=position.size())
    {
      ROS_ERROR("Input Mismatch. The size of the vector of names is %zu, while position size is %zu",names.size(),position.size());
      return false;
    }
    if (names.size()!=velocity.size())
    {
      ROS_ERROR("Input Mismatch. The size of the vector of names is %zu, while velocity size is %zu",names.size(),velocity.size());
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
                         std::vector<double>& position)
  {
    if (names.size()<order_names.size())
    {
      ROS_ERROR("The vector of names to be sorted has size %zu, that is smaller than vector of the sorted names (%zu)",names.size(),order_names.size());
      return false;
    }
    if (names.size()!=position.size())
    {
      ROS_ERROR("Input Mismatch. The size of the vector of names is %zu, while position size is %zu",names.size(),position.size());
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
  
  
}

