#pragma once
#include <string>
#include <vector>
#include <exception>

#ifdef _WIN32
#define PLUGIN_EXPORT extern "C" __declspec(dllexport)
#else
#define PLUGIN_EXPORT extern "C" __attribute__((visibility("default")))
#endif

struct PluginError : public std::exception {
    std::string msg;
    explicit PluginError(std::string m) : msg(std::move(m)) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

class IPlugin {
public:
    virtual ~IPlugin() = default;

    virtual const char* Name() const = 0;

    virtual int Arity() const = 0;

    virtual double Call(const std::vector<double>& args) = 0;
};

typedef IPlugin* (*CreatePluginFn)();

PLUGIN_EXPORT IPlugin* CreatePlugin();