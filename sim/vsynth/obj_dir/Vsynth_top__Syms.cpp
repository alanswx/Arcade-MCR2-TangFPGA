// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vsynth_top__Syms.h"
#include "Vsynth_top.h"



// FUNCTIONS
Vsynth_top__Syms::~Vsynth_top__Syms()
{
}

Vsynth_top__Syms::Vsynth_top__Syms(VerilatedContext* contextp, Vsynth_top* topp, const char* namep)
    // Setup locals
    : VerilatedSyms{contextp}
    , __Vm_namep(namep)
    , __Vm_didInit(false)
    // Setup submodule names
{
    // Pointer to top level
    TOPp = topp;
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOPp->__Vconfigure(this, true);
}
