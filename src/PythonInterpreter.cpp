//
// Created by 장은준 on 2022-05-14.
//

#include "PythonInterpreter.h"

PyObject* game_go(PyObject* self, PyObject* args) {
    PyObject* num;

    if (!PyArg_UnpackTuple(args, "go", 1, 1, &num)) {
        Py_RETURN_FALSE;
    }
    const unsigned long value = PyLong_AsUnsignedLong(num);
    if (PythonInterpreter::GetInstance()->go(value)) {
        Py_RETURN_TRUE;
    }
    Py_RETURN_FALSE;
}

PyObject* game_turn_left(PyObject* self, PyObject* args) {
    PyObject* num;

    if (!PyArg_UnpackTuple(args, "turn_left", 1, 1, &num)) {
        Py_RETURN_FALSE;
    }
    const unsigned long value = PyLong_AsUnsignedLong(num);
    if (PythonInterpreter::GetInstance()->turnleft(value)) {
        Py_RETURN_TRUE;
    }
    Py_RETURN_FALSE;
}

PyObject* game_turn_right(PyObject* self, PyObject* args) {
    PyObject* num;

    if (!PyArg_UnpackTuple(args, "turn_left", 1, 1, &num)) {
        Py_RETURN_FALSE;
    }
    const unsigned long value = PyLong_AsUnsignedLong(num);
    if (PythonInterpreter::GetInstance()->turnright(value)) {
        Py_RETURN_TRUE;
    }
    Py_RETURN_FALSE;
}

PyMethodDef gameMethods[] {
    {
        "go", &game_go, METH_VARARGS, "꿀벌이 현재 보는 방향으로 숫자만큼 전진합니다."
    },
    {
        "turn_left", &game_turn_left, METH_VARARGS, "꿀벌이 왼쪽으로 90 * 숫자 만큼 회전합니다."
    },
    {
        "turn_right", &game_turn_right, METH_VARARGS, "꿀벌이 오른쪽으로 90 * 숫자 만큼 회전합니다."
    },
    {nullptr, nullptr, 0, nullptr},
};

PyModuleDef gameModule {
    PyModuleDef_HEAD_INIT,
    "game",
    nullptr,
    -1,
    gameMethods,
    nullptr,
    nullptr,
    nullptr,
    nullptr
};

void PythonInterpreter::Initialize() {

    PyImport_AppendInittab("game", []() {
        return PyModule_Create(&gameModule);
    });

    Py_Initialize();
}

void PythonInterpreter::Release() {
    Py_Finalize();
}

int PythonInterpreter::RunScript(const char* src) {
    return PyRun_SimpleString(src);
}

bool PythonInterpreter::go(unsigned int num) {
    for (int i = 0; i < num; ++i) {
        if (!checkActions()) return false;
        this->actions.push_back(PlayerAction::Go);
    }
    return true;
}

bool PythonInterpreter::turnleft(int num) {
    for (int i = 0; i < num; ++i) {
        if (!checkActions()) return false;
        this->actions.push_back(PlayerAction::TurnLeft);
    }
    return true;
}

bool PythonInterpreter::turnright(int num) {
    for (int i = 0; i < num; ++i) {
        if (!checkActions()) return false;
        this->actions.push_back(PlayerAction::TurnRight);
    }
    return true;
}

bool PythonInterpreter::checkActions() {
    return this->actions.size() <= MAX_ACTION;
}

std::vector<PlayerAction> PythonInterpreter::GetActions() const {
    return this->actions;
}

void PythonInterpreter::ClearActions() {
    this->actions.clear();
}
