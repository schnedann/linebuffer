#include "scope_guard.h"

using namespace Core::Runtime;

void Scope_Guard::exec(){
  if(callbk && !triggered){
    triggered=true;
    //normally you should never assign a throwing function,
    //as it is executed from a destructor. So we souround
    //the call with a "do nothing" block.
    try{
      callbk();
    }catch(...){}
  }
  return;
}

Scope_Guard::~Scope_Guard(){
  exec();
  return;
}

/**
 * @brief Scope_Guard::trigger - trigger the callbk earlier,
 *        and prevent a second execution
 */
void Scope_Guard::trigger(){
  exec();
  return;
}
