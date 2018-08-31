#ifndef name_sorting__201808101353
#define name_sorting__201808101353

#include <ros/console.h>
namespace name_sorting
{
  bool permutationName( const std::vector<std::string>& order_names, 
                        std::vector<std::string>& names,
                        std::vector<double>& position, 
                        std::vector<double>& velocity, 
                        std::vector<double>& effort);
  
  bool permutationName( const std::vector<std::string>& order_names, 
                        std::vector<std::string>& names,
                        std::vector<double>& position, 
                        std::vector<double>& velocity);
  bool permutationName( const std::vector<std::string>& order_names, 
                        std::vector<std::string>& names,
                        std::vector<double>& position);
  

  
}


#endif 