// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VSYNTH_TOP__SYMS_H_
#define VERILATED_VSYNTH_TOP__SYMS_H_  // guard

#include "verilated_heavy.h"

// INCLUDE MODULE CLASSES
#include "Vsynth_top.h"

// SYMS CLASS
class Vsynth_top__Syms : public VerilatedSyms {
  public:

    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;

    // SUBCELL STATE
    Vsynth_top*                    TOPp;

    // CREATORS
    Vsynth_top__Syms(VerilatedContext* contextp, Vsynth_top* topp, const char* namep);
    ~Vsynth_top__Syms();

    // METHODS
    inline const char* name() { return __Vm_namep; }

} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
