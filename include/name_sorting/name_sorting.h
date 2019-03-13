#ifndef name_sorting__201808101353
#define name_sorting__201808101353

#include <ros/console.h>
namespace name_sorting
{
  /**
   * \brief 
   * permutationName, reorder vectors. 
   * *order_names* names in the desired order
   * *names* current order of names, 
   * *vector1*, *vector2*, *vector3* vectors to be reordered
   */
  bool permutationName( const std::vector<std::string>& order_names, 
                        std::vector<std::string>& names,
                        std::vector<double>& vector1,
                        std::vector<double>& vector2,
                        std::vector<double>& vector3);
  
  /**
   * \brief 
   * permutationName, reorder vectors. 
   * *order_names* names in the desired order
   * *names* current order of names, 
   * *vector1*, *vector2* vectors to be reordered
   */
  bool permutationName(const std::vector<std::string>& order_names,
                        std::vector<std::string>& names,
                        std::vector<double>& vector1,
                        std::vector<double>& vector2);
  /**
   * \brief 
   * permutationName, reorder vectors. 
   * *order_names* names in the desired order
   * *names* current order of names, 
   * *vector1* vector to be reordered
   */
  bool permutationName(const std::vector<std::string>& order_names,
                        std::vector<std::string>& names,
                        std::vector<double>& vector1);
  

  
}


#endif 
