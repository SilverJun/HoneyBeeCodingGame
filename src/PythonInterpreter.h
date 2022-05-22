//
// Created by 장은준 on 2022-05-14.
//

#ifndef HONEYBEECODINGGAME_PYTHONINTERPRETER_H
#define HONEYBEECODINGGAME_PYTHONINTERPRETER_H

#define PY_SSIZE_T_CLEAN
#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

#include <string>
#include <vector>
#include "Singleton.h"
#include "PlayerAction.h"

class PythonInterpreter: public Singleton<PythonInterpreter> {
    std::vector<PlayerAction> actions;
    static constexpr unsigned int MAX_ACTION = 1000;

public:
    virtual ~PythonInterpreter() = default;
    void Initialize();

    int RunScript(const char* src);
    void Release();

    std::vector<PlayerAction> GetActions() const;
    void ClearActions();


    // Python APIs
    bool go(unsigned int block);
    bool turnleft(int num);
    bool turnright(int num);

    bool checkActions();

};


#endif //HONEYBEECODINGGAME_PYTHONINTERPRETER_H
