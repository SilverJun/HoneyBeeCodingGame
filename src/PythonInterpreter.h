//
// Created by 장은준 on 2022-05-14.
//

#ifndef HONEYBEECODINGGAME_PYTHONINTERPRETER_H
#define HONEYBEECODINGGAME_PYTHONINTERPRETER_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <string>

class PythonInterpreter {

public:
    void Initialize();

    int RunScript(const char* src);
    void Release();


};


#endif //HONEYBEECODINGGAME_PYTHONINTERPRETER_H
