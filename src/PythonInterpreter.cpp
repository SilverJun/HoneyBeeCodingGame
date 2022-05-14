//
// Created by 장은준 on 2022-05-14.
//

#include "PythonInterpreter.h"

void PythonInterpreter::Initialize() {
    Py_Initialize();
}

void PythonInterpreter::Release() {
    Py_Finalize();
}

int PythonInterpreter::RunScript(const char* src) {
    return PyRun_SimpleString(src);
}
