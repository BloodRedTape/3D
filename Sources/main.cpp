#include <core/span.hpp>
#include "application.cpp"

int StraitXMain(Span<const char *> args){
    Application app;
    Application::s_Instance = &app;

    Application::Get().Run();

    return 0;
}