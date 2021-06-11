// pch.cpp: source file corresponding to the pre-compiled header

#include "CorePch.h"
#include "Engine.h"
// When you are using pre-compiled headers, this source file is necessary for compilation to succeed.

std::unique_ptr<Engine> gEngine = std::make_unique<Engine>();