#include "error_mgnt.h"

/**
 * @brief Core::Flow::if_no_err
 * @param exec    - Function to execute as "if"-body
 * @param errhdlr - Function to execute as local Error Handler
 * @param err     - error indicator pass-through
 */
void Core::Flow::if_no_err(std::function<bool()> const& exec, std::function<void()> const& errhdlr, bool& err){
  if(exec){        //if exec function exists
    err = exec();  //Execute

    if(err){       //if error is signaled
      if(errhdlr){ //if error handler function exists
        errhdlr(); //Execute
      }
    }
  }
  return;
}

/**
 * @brief Core::Flow::if_no_err
 * @param exec    - Function to execute as "if"-body, with the possibility to set an local error-string
 * @param errhdlr - Function to execute as local Error Handler, with the possibility to use an local error-string
 * @param err     - error indicator pass-through
 */
void Core::Flow::if_no_err(std::function<bool (std::string&)> const& exec, std::function<void (const std::string&)> const& errhdlr, bool& err){
  std::string errstr;
  if(exec){              //if exec function exists
    err = exec(errstr);  //Execute

    if(err){             //if error is signaled
      if(errhdlr){       //if error handler function exists
        errhdlr(errstr); //Execute
      }
    }
  }
  return;
}
