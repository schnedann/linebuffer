#include <sstream>

#include "linebuffer.h"

/**
 * @brief linebuffer::add
 * @param str - new Input String
 */
void linebuffer::add(const std::string& str){
  dll.push_back(str);
  return;
}

/**
 * @brief linebuffer::get_all_lines
 * @return
 */
with_error_t<std::string> linebuffer::get_all_lines(){
  std::stringstream ss;
  bool err = true;

  //from newest node to oldest
  size_t pos;
  auto newest_delim = Datastructures::rfind_match<std::string>(dll,[&pos,this](std::string const& str)->bool{
    //newest (last) delimiter is found at the back of the string
    pos = str.rfind(this->delimiter);
    bool found = (pos != std::string::npos);
    return found;
  });

  //If no err, delimiter was found
  if(!has_error(newest_delim)){
    auto last_node_ptr = Datastructures::get_node<std::string>(dll,newest_delim.second);
    if(!has_error(last_node_ptr)){
      //From oldest = first Node to the Node which contains the "newest" delimiter
      for(auto ptr = dll.get_next(nullptr); ptr!=last_node_ptr.second->next.get(); ptr = dll.get_next(ptr)){

      }
    }
  }

  return make_with_error<std::string>(err,ss.str());
}

/**
 * @brief linebuffer::size
 * @return accumulated size of all nodes in linebuffer
 */
size_t linebuffer::size(){
  size_t res = 0;
  //for all Nodes accumulate size of Strings
  Datastructures::for_each_node<std::string>(dll,[&res](Datastructures::dbllnkdlst<std::string>::wk_data_t dptr){
    res += dptr->size();
  });
  return res;
}
