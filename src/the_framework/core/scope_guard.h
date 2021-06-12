/******************************************************************************/
/** Exception save execution of cleanup-worker as Destructor replacement     **/
/** Callback called when instance gets destroyed usage e.g. when you want to **/
/** config a fire and forget cleanup function initially and don't need to    **/
/** reference it later in code...                                            **/
/** so cleanup is also called on exceptions automaticly...                   **/
/** Danny Schneider, 2019-2021                                               **/
/******************************************************************************/

/*
 * Copyright (c) 2019-2021, Danny Schneider
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer. (of course you are
 * allowed to extend the above copyright notice by the means of adding your
 * name and date if and only if you have contributed to the source)
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Redistributions of any forked and or modified version of this code in binary
 * form need to make the source code availible upon request. If maintainance of any
 * forked and or modified version of this code is stopped, future access to the code
 * needs to be ensured e.g. by at least uploading it to an public open platform and
 * or the official original repository if availible.
 *
 * 4. Usage of this code (stating Discrimination Against Fields of Endeavor [*1] )
 * neither in source nor in binary form - in any military, intelligence,
 * public surveillance, surveillance state , political supression context is forbidden
 * Simply:
 * do not use this software to harm people or to violate non-derogable human rights
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * [*1]: Comment of Conndition 4, yes this conndition violates the Open Source Definition
 * But as an Engineer with a german background I do believe you are responsible how the
 * things are used you develop. So yes, even if Conndition 4 might be circumvented and/or
 * be ignored by bad people, I want to state with this liecense, that my intend is to not
 * have the software used to harm people, and I want to ask you to respect this.
 */

#ifndef SCOPE_GUARD_H
#define SCOPE_GUARD_H

#include <functional>

namespace Core {

namespace Runtime {

/**
 * @brief The Scope_Guard class
 * Assign a function e.g. some cleanup code to the scope-gurad
 * if any following code in this scope triggers an exception,
 * the stack unwinding will ensure our assigned cleanup is called
 *
 * example:
 * {
 * init()
 * work()
 * cleanup()
 * }
 * if work throws an exception, cleanup is never executed.
 * so we use the scopeguard
 * {
 * init()
 * sg(cleanup)
 * work()
 * }
 * now we have registered the cleanup prior to the exception, so
 * when the stack-unwinder destroys sg, the cleanup will be executed!
 *
 */
class Scope_Guard{
private:
  bool triggered{false};
  std::function<void()> callbk;

  void exec();
public:
  Scope_Guard()=default;
  explicit Scope_Guard(std::function<void()> _cb):callbk(_cb){}
  ~Scope_Guard();
  void trigger();
};

} //namespace

} //namespace

#endif // SCOPE_GUARD_H
