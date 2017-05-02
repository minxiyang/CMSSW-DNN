/*
 * Python interface.
 *
 * Author:
 *   Marcel Rieger
 */

#ifndef DNN_BASE_PYTHONINTERFACE_H_FOO
#define DNN_BASE_PYTHONINTERFACE_H_FOO

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Python.h"

#include "DNN/Base/interface/Logger.h"

namespace dnn
{

class PythonInterface
{
public:
    PythonInterface(const LogLevel& level = INFO);
    virtual ~PythonInterface();

    void except(PyObject* obj, const std::string& msg) const;
    void release(PyObject*& ptr) const;

    PyObject* get(const std::string& name) const; // returns borrowed reference
    PyObject* call(PyObject* callable, PyObject* args = NULL) const; // returns new reference
    PyObject* call(const std::string& name, PyObject* args = NULL) const; // returns new reference
    PyObject* call(const std::string& name, int arg) const; // returns new reference
    PyObject* call(const std::string& name, double arg) const; // returns new reference
    PyObject* call(const std::string& name, const std::string& arg) const; // returns new reference

    void runScript(const std::string& script);
    void runFile(const std::string& filename);

    PyObject* createTuple(const std::vector<int>& v) const; // returns new reference
    PyObject* createTuple(const std::vector<double>& v) const; // returns new reference
    PyObject* createTuple(const std::vector<std::string>& v) const; // returns new reference

private:
    Logger logger;
    PyObject* context;

    void initialize() const;
    void finalize() const;

    bool hasContext() const;
    void startContext();

    static size_t nConsumers;
};

size_t PythonInterface::nConsumers = 0;

} // namepace dnn

#endif // DNN_BASE_PYTHONINTERFACE_H
