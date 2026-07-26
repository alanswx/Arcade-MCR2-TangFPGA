// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsynth_top.h for the primary calling header

#include "Vsynth_top.h"
#include "Vsynth_top__Syms.h"

//==========

VerilatedContext* Vsynth_top::contextp() {
    return __VlSymsp->_vm_contextp__;
}

void Vsynth_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vsynth_top::eval\n"); );
    Vsynth_top__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vsynth_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("synth_top.v", 3, "",
                "Verilated model didn't converge\n"
                "- See https://verilator.org/warn/DIDNOTCONVERGE");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vsynth_top::_eval_initial_loop(Vsynth_top__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("synth_top.v", 3, "",
                "Verilated model didn't DC converge\n"
                "- See https://verilator.org/warn/DIDNOTCONVERGE");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vsynth_top::_sequent__TOP__2(Vsynth_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth_top::_sequent__TOP__2\n"); );
    Vsynth_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7988_q 
        = (1U & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n114_o)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8214_q 
        = (1U & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n114_o)));
}

VL_INLINE_OPT void Vsynth_top::_sequent__TOP__3(Vsynth_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth_top::_sequent__TOP__3\n"); );
    Vsynth_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*7:0*/ __Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram__v0;
    CData/*0:0*/ __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram__v0;
    CData/*0:0*/ __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line0__v0;
    CData/*0:0*/ __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line1__v0;
    CData/*0:0*/ __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line2__v0;
    CData/*0:0*/ __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line3__v0;
    CData/*7:0*/ __Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf0__v0;
    CData/*0:0*/ __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf0__v0;
    CData/*7:0*/ __Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf1__v0;
    CData/*0:0*/ __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf1__v0;
    CData/*7:0*/ __Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf2__v0;
    CData/*0:0*/ __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf2__v0;
    CData/*7:0*/ __Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf3__v0;
    CData/*0:0*/ __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf3__v0;
    CData/*7:0*/ __Vdly__synth_top__DOT__bridge__DOT__beat;
    CData/*7:0*/ __Vdly__synth_top__DOT__bridge__DOT__blen_q;
    CData/*1:0*/ __Vdly__synth_top__DOT__bridge__DOT__state;
    CData/*3:0*/ __Vdly__synth_top__DOT__ddr__DOT__cnt;
    CData/*0:0*/ __Vdlyvset__synth_top__DOT__ddr__DOT__pipe__v13;
    CData/*0:0*/ __Vdlyvset__synth_top__DOT__ddr__DOT__ram__v0;
    SData/*10:0*/ __Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line0__v0;
    SData/*10:0*/ __Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line1__v0;
    SData/*10:0*/ __Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line2__v0;
    SData/*10:0*/ __Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line3__v0;
    VlWide<4>/*127:0*/ __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram__v0;
    IData/*23:0*/ __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line0__v0;
    IData/*23:0*/ __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line1__v0;
    IData/*23:0*/ __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line2__v0;
    IData/*23:0*/ __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line3__v0;
    IData/*23:0*/ __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf0__v0;
    IData/*23:0*/ __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf1__v0;
    IData/*23:0*/ __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf2__v0;
    IData/*23:0*/ __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf3__v0;
    IData/*24:0*/ __Vdly__synth_top__DOT__bridge__DOT__addr_q;
    IData/*18:0*/ __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v0;
    IData/*18:0*/ __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v1;
    IData/*18:0*/ __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v2;
    IData/*18:0*/ __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v3;
    IData/*18:0*/ __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v4;
    IData/*18:0*/ __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v5;
    IData/*18:0*/ __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v6;
    IData/*18:0*/ __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v7;
    IData/*18:0*/ __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v8;
    IData/*18:0*/ __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v9;
    IData/*18:0*/ __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v10;
    IData/*18:0*/ __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v11;
    IData/*18:0*/ __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v13;
    IData/*17:0*/ __Vdlyvdim0__synth_top__DOT__ddr__DOT__ram__v0;
    VlWide<4>/*127:0*/ __Vdlyvval__synth_top__DOT__ddr__DOT__ram__v0;
    VlWide<3>/*95:0*/ __Vtemp9;
    VlWide<4>/*127:0*/ __Vtemp14;
    VlWide<4>/*127:0*/ __Vtemp17;
    VlWide<4>/*127:0*/ __Vtemp20;
    VlWide<3>/*95:0*/ __Vtemp23;
    VlWide<5>/*159:0*/ __Vtemp61;
    VlWide<5>/*159:0*/ __Vtemp63;
    VlWide<3>/*95:0*/ __Vtemp64;
    VlWide<3>/*95:0*/ __Vtemp65;
    VlWide<4>/*127:0*/ __Vtemp66;
    VlWide<6>/*191:0*/ __Vtemp68;
    VlWide<3>/*95:0*/ __Vtemp80;
    VlWide<4>/*127:0*/ __Vtemp87;
    VlWide<3>/*95:0*/ __Vtemp89;
    VlWide<4>/*127:0*/ __Vtemp90;
    VlWide<5>/*159:0*/ __Vtemp91;
    VlWide<6>/*191:0*/ __Vtemp92;
    VlWide<3>/*95:0*/ __Vtemp112;
    VlWide<4>/*127:0*/ __Vtemp116;
    VlWide<4>/*127:0*/ __Vtemp119;
    VlWide<4>/*127:0*/ __Vtemp122;
    VlWide<4>/*127:0*/ __Vtemp125;
    VlWide<4>/*127:0*/ __Vtemp128;
    VlWide<4>/*127:0*/ __Vtemp131;
    VlWide<4>/*127:0*/ __Vtemp134;
    VlWide<4>/*127:0*/ __Vtemp137;
    VlWide<4>/*127:0*/ __Vtemp140;
    VlWide<4>/*127:0*/ __Vtemp143;
    VlWide<4>/*127:0*/ __Vtemp146;
    VlWide<4>/*127:0*/ __Vtemp149;
    VlWide<4>/*127:0*/ __Vtemp152;
    VlWide<4>/*127:0*/ __Vtemp155;
    VlWide<4>/*127:0*/ __Vtemp158;
    VlWide<4>/*127:0*/ __Vtemp161;
    VlWide<4>/*127:0*/ __Vtemp164;
    VlWide<4>/*127:0*/ __Vtemp167;
    VlWide<4>/*127:0*/ __Vtemp170;
    VlWide<4>/*127:0*/ __Vtemp173;
    VlWide<4>/*127:0*/ __Vtemp176;
    VlWide<4>/*127:0*/ __Vtemp179;
    VlWide<4>/*127:0*/ __Vtemp187;
    VlWide<4>/*127:0*/ __Vtemp190;
    VlWide<4>/*127:0*/ __Vtemp193;
    VlWide<4>/*127:0*/ __Vtemp196;
    VlWide<4>/*127:0*/ __Vtemp199;
    VlWide<4>/*127:0*/ __Vtemp202;
    VlWide<4>/*127:0*/ __Vtemp205;
    VlWide<4>/*127:0*/ __Vtemp208;
    VlWide<4>/*127:0*/ __Vtemp211;
    VlWide<4>/*127:0*/ __Vtemp214;
    VlWide<4>/*127:0*/ __Vtemp217;
    VlWide<4>/*127:0*/ __Vtemp220;
    VlWide<4>/*127:0*/ __Vtemp223;
    VlWide<4>/*127:0*/ __Vtemp226;
    VlWide<4>/*127:0*/ __Vtemp229;
    VlWide<4>/*127:0*/ __Vtemp232;
    VlWide<4>/*127:0*/ __Vtemp235;
    VlWide<4>/*127:0*/ __Vtemp238;
    VlWide<4>/*127:0*/ __Vtemp241;
    VlWide<4>/*127:0*/ __Vtemp244;
    VlWide<4>/*127:0*/ __Vtemp247;
    VlWide<4>/*127:0*/ __Vtemp250;
    VlWide<4>/*127:0*/ __Vtemp253;
    VlWide<4>/*127:0*/ __Vtemp256;
    VlWide<4>/*127:0*/ __Vtemp259;
    VlWide<4>/*127:0*/ __Vtemp262;
    VlWide<4>/*127:0*/ __Vtemp265;
    VlWide<4>/*127:0*/ __Vtemp268;
    VlWide<4>/*127:0*/ __Vtemp271;
    VlWide<4>/*127:0*/ __Vtemp274;
    VlWide<4>/*127:0*/ __Vtemp277;
    VlWide<4>/*127:0*/ __Vtemp280;
    VlWide<4>/*127:0*/ __Vtemp283;
    VlWide<4>/*127:0*/ __Vtemp286;
    VlWide<4>/*127:0*/ __Vtemp289;
    VlWide<4>/*127:0*/ __Vtemp292;
    VlWide<4>/*127:0*/ __Vtemp295;
    VlWide<4>/*127:0*/ __Vtemp298;
    VlWide<4>/*127:0*/ __Vtemp301;
    VlWide<4>/*127:0*/ __Vtemp304;
    VlWide<4>/*127:0*/ __Vtemp307;
    VlWide<4>/*127:0*/ __Vtemp310;
    VlWide<4>/*127:0*/ __Vtemp313;
    VlWide<4>/*127:0*/ __Vtemp316;
    VlWide<4>/*127:0*/ __Vtemp319;
    VlWide<4>/*127:0*/ __Vtemp322;
    VlWide<4>/*127:0*/ __Vtemp325;
    VlWide<4>/*127:0*/ __Vtemp328;
    VlWide<4>/*127:0*/ __Vtemp331;
    VlWide<4>/*127:0*/ __Vtemp334;
    VlWide<4>/*127:0*/ __Vtemp337;
    VlWide<4>/*127:0*/ __Vtemp340;
    VlWide<4>/*127:0*/ __Vtemp343;
    VlWide<4>/*127:0*/ __Vtemp346;
    VlWide<4>/*127:0*/ __Vtemp349;
    VlWide<4>/*127:0*/ __Vtemp352;
    VlWide<4>/*127:0*/ __Vtemp355;
    VlWide<4>/*127:0*/ __Vtemp358;
    // Body
    __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram__v0 = 0U;
    __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf3__v0 = 0U;
    __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf2__v0 = 0U;
    __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf1__v0 = 0U;
    __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf0__v0 = 0U;
    __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line3__v0 = 0U;
    __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line2__v0 = 0U;
    __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line1__v0 = 0U;
    __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line0__v0 = 0U;
    __Vdly__synth_top__DOT__ddr__DOT__cnt = vlTOPp->synth_top__DOT__ddr__DOT__cnt;
    __Vdly__synth_top__DOT__bridge__DOT__blen_q = vlTOPp->synth_top__DOT__bridge__DOT__blen_q;
    __Vdly__synth_top__DOT__bridge__DOT__addr_q = vlTOPp->synth_top__DOT__bridge__DOT__addr_q;
    __Vdly__synth_top__DOT__bridge__DOT__beat = vlTOPp->synth_top__DOT__bridge__DOT__beat;
    __Vdlyvset__synth_top__DOT__ddr__DOT__ram__v0 = 0U;
    __Vdly__synth_top__DOT__bridge__DOT__state = vlTOPp->synth_top__DOT__bridge__DOT__state;
    __Vdlyvset__synth_top__DOT__ddr__DOT__pipe__v13 = 0U;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8499_q 
        = ((0xff00U & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6378_o) 
                        * (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6378_o)) 
                       << 1U)) | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6378_o));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8497_q 
        = ((0xff00U & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4687_o) 
                        * (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4687_o)) 
                       << 1U)) | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4687_o));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[0U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7063_o[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[1U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7063_o[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[2U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7063_o[2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[0U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5380_o[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[1U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5380_o[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[2U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5380_o[2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8418_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4649_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8417_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4647_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8554_q[0U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7311_o[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8554_q[1U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7311_o[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8554_q[2U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7311_o[2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8554_q[3U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7311_o[3U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8554_q[4U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7311_o[4U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8554_q[5U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7311_o[5U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8551_q[0U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5633_o[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8551_q[1U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5633_o[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8551_q[2U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5633_o[2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8551_q[3U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5633_o[3U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8551_q[4U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5633_o[4U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8551_q[5U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5633_o[5U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8514_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7132_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8512_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5450_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8378_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8377_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8375_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8374_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8372_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8371_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8351_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8350_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8348_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8347_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8345_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8344_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8207_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8206_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8204_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8203_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8187_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8186_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8184_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8183_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8416_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8415_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8413_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8412_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8036_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8035_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8153_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8152_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8144_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8143_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7927_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7926_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7918_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7917_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8327_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8326_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8278_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8277_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8201_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8200_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8147_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8146_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8068_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8067_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7941_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7940_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7930_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7929_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8045_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8044_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8381_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8380_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8062_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8061_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7938_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7937_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8458_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8457_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8438_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8437_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8534_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8533_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7951_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7950_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8385_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8384_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8366_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8365_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8006_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8005_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8163_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8162_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8574_q 
        = (1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8311_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8281_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8280_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8009_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8008_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8455_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5734_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8135_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8134_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8470_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8469_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8461_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8460_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8150_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8149_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8141_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8140_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7924_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7923_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7915_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7914_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8531_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8530_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8272_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8271_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8261_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6021_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7997_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7996_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7984_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7983_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7978_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7977_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7971_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7970_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7958_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7957_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8453_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8452_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8299_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8298_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7975_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7974_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7955_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7954_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8042_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8041_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8033_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8032_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8097_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8096_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7987_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7986_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7981_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7980_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8178_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8177_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8166_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8165_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8363_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8362_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8426_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8425_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8210_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8209_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8550_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8548_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8549_q 
        = (0x3ffU & ((IData)(0x100U) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8548_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8360_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8359_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8071_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8070_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8169_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8168_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8305_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8304_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8293_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8292_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8172_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8171_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8091_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8090_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8467_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8466_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8403_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8402_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7933_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7932_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8077_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8076_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8259_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6020_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8047_q 
        = (0xfffU & ((IData)(5U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8039_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8406_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8405_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8464_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8463_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8321_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8320_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8269_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8268_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8118_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8117_o;
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7965_q) {
        __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram__v0[0U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7961_q[0U];
        __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram__v0[1U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7961_q[1U];
        __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram__v0[2U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7961_q[2U];
        __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram__v0[3U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7961_q[3U];
        __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram__v0 = 1U;
        __Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram__v0 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7947_q;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8213_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8212_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8000_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7999_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7994_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7993_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8138_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8137_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7944_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7943_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8546_q 
        = (0xffffffU & ((0xff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[4U] 
                                      << 8U)) | ((0xffU 
                                                  & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[3U] 
                                                     >> 0x18U)) 
                                                 | (0xff00U 
                                                    & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[4U] 
                                                       << 8U)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8112_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8111_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7991_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7990_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8324_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8323_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8479_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8478_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8353_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8422_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8421_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[0U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8197_o[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[1U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8197_o[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[2U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8197_o[2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[3U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8197_o[3U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[4U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8197_o[4U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8012_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8011_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram
        [vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8190_q][0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[1U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram
        [vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8190_q][1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[2U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram
        [vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8190_q][2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[3U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram
        [vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8190_q][3U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8075_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8074_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8290_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8289_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8476_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8475_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8115_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8114_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8396_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8030_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8029_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4089_q 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__scalaire_off_v)
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2954_o));
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8557_q) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[0U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4369_o[0U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4369_o[1U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[2U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4369_o[2U];
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[0U] 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8558_q)
                ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8540_q[0U]
                : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4369_o[0U]);
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8558_q)
                ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8540_q[1U]
                : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4369_o[1U]);
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[2U] 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8558_q)
                ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8540_q[2U]
                : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4369_o[2U]);
    }
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4069_q 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__scalaire_bib_v;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4063_q 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__scalaire_prim_v;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4069_q 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2948_o;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4063_q 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2944_o;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8103_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8102_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4066_q 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__scalaire_last_v)
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2946_o));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8339_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8338_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8333_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8332_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8100_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8099_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8109_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8108_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8106_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8105_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8257_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6019_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8336_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8335_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8503_q[0U] 
        = (IData)(((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4907_o 
                    << 8U) | (QData)((IData)((0xffU 
                                              & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                  << 0x10U) 
                                                 | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                    >> 0x10U)))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8503_q[1U] 
        = ((0xfffe0000U & ((IData)(((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4980_o 
                                     << 8U) | (QData)((IData)(
                                                              (0xffU 
                                                               & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                                   << 8U) 
                                                                  | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                                     >> 0x18U))))))) 
                           << 0x11U)) | (IData)((((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4907_o 
                                                   << 8U) 
                                                  | (QData)((IData)(
                                                                    (0xffU 
                                                                     & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                                         << 0x10U) 
                                                                        | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                                           >> 0x10U)))))) 
                                                 >> 0x20U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8503_q[2U] 
        = ((0x1ffffU & ((IData)(((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4980_o 
                                  << 8U) | (QData)((IData)(
                                                           (0xffU 
                                                            & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                                << 8U) 
                                                               | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                                  >> 0x18U))))))) 
                        >> 0xfU)) | (0xfffe0000U & 
                                     ((IData)((((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4980_o 
                                                 << 8U) 
                                                | (QData)((IData)(
                                                                  (0xffU 
                                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                                       << 8U) 
                                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                                         >> 0x18U)))))) 
                                               >> 0x20U)) 
                                      << 0x11U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8503_q[3U] 
        = ((0xfffffffcU & ((IData)(((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5053_o 
                                     << 8U) | (QData)((IData)(
                                                              (0xffU 
                                                               & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U]))))) 
                           << 2U)) | (0x1ffffU & ((IData)(
                                                          (((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4980_o 
                                                             << 8U) 
                                                            | (QData)((IData)(
                                                                              (0xffU 
                                                                               & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                                                << 8U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                                                >> 0x18U)))))) 
                                                           >> 0x20U)) 
                                                  >> 0xfU)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8503_q[4U] 
        = ((3U & ((IData)(((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5053_o 
                            << 8U) | (QData)((IData)(
                                                     (0xffU 
                                                      & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U]))))) 
                  >> 0x1eU)) | (0xfffffffcU & ((IData)(
                                                       (((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5053_o 
                                                          << 8U) 
                                                         | (QData)((IData)(
                                                                           (0xffU 
                                                                            & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U])))) 
                                                        >> 0x20U)) 
                                               << 2U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8002_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8454_q 
        = (((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4519_o)) 
            << 0x2aU) | (((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4559_o)) 
                          << 0x15U) | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4599_o))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8484_q 
        = (0xffU & ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8018_q))
                     ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                        >> 4U) : ((0x800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q))
                                   ? (~ ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6405_o) 
                                         >> 7U)) : 
                                  ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6405_o) 
                                   >> 7U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8409_q 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_bibu)
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2930_o));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8570_q 
        = (1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8307_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8254_q 
        = VL_LTES_III(1,32,32, 0x800U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8241_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8253_q 
        = VL_LTES_III(1,32,32, 0x800U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8239_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8252_q 
        = VL_LTES_III(1,32,32, 0x800U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8237_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8251_q 
        = VL_LTES_III(1,32,32, 0x800U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8235_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8620_data 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf3
        [(0xffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8241_q))];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8617_data 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf2
        [(0xffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8239_q))];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8614_data 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf1
        [(0xffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8237_q))];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8611_data 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf0
        [(0xffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8235_q))];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8608_data 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_line3
        [(0x7ffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8241_q))];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8605_data 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_line2
        [(0x7ffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8239_q))];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8602_data 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_line1
        [(0x7ffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8237_q))];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8599_data 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_line0
        [(0x7ffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8235_q))];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8572_q 
        = (1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8309_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8175_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8174_o;
    if ((VL_LTES_III(1,32,32, 0x800U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8233_q)) 
         & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8255_q) 
            >> 3U))) {
        __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf3__v0 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8246_q;
        __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf3__v0 = 1U;
        __Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf3__v0 
            = (0xffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8233_q));
    }
    if ((VL_LTES_III(1,32,32, 0x800U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8233_q)) 
         & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8255_q) 
            >> 2U))) {
        __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf2__v0 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8246_q;
        __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf2__v0 = 1U;
        __Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf2__v0 
            = (0xffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8233_q));
    }
    if ((VL_LTES_III(1,32,32, 0x800U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8233_q)) 
         & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8255_q) 
            >> 1U))) {
        __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf1__v0 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8246_q;
        __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf1__v0 = 1U;
        __Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf1__v0 
            = (0xffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8233_q));
    }
    if ((VL_LTES_III(1,32,32, 0x800U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8233_q)) 
         & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8255_q))) {
        __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf0__v0 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8246_q;
        __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf0__v0 = 1U;
        __Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf0__v0 
            = (0xffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8233_q));
    }
    if ((VL_GTS_III(1,32,32, 0x800U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8233_q)) 
         & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8255_q) 
            >> 3U))) {
        __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line3__v0 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8246_q;
        __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line3__v0 = 1U;
        __Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line3__v0 
            = (0x7ffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8233_q));
    }
    if ((VL_GTS_III(1,32,32, 0x800U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8233_q)) 
         & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8255_q) 
            >> 2U))) {
        __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line2__v0 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8246_q;
        __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line2__v0 = 1U;
        __Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line2__v0 
            = (0x7ffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8233_q));
    }
    if ((VL_GTS_III(1,32,32, 0x800U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8233_q)) 
         & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8255_q) 
            >> 1U))) {
        __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line1__v0 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8246_q;
        __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line1__v0 = 1U;
        __Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line1__v0 
            = (0x7ffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8233_q));
    }
    if ((VL_GTS_III(1,32,32, 0x800U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8233_q)) 
         & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8255_q))) {
        __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line0__v0 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8246_q;
        __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line0__v0 = 1U;
        __Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line0__v0 
            = (0x7ffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8233_q));
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8126_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8120_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8130_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8129_o;
    __Vtemp9[0U] = (IData)((((QData)((IData)(((0x20000U 
                                               & ((IData)(
                                                          (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8529_q 
                                                           >> 0x1dU)) 
                                                  << 0x11U)) 
                                              | (0x1ff80U 
                                                 & ((IData)(
                                                            (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8529_q 
                                                             >> 0x14U)) 
                                                    << 7U))))) 
                             << 0x24U) | (((QData)((IData)(
                                                           ((0x20000U 
                                                             & ((IData)(
                                                                        (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8529_q 
                                                                         >> 0x13U)) 
                                                                << 0x11U)) 
                                                            | (0x1ff80U 
                                                               & ((IData)(
                                                                          (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8529_q 
                                                                           >> 0xaU)) 
                                                                  << 7U))))) 
                                           << 0x12U) 
                                          | (QData)((IData)(
                                                            ((0x20000U 
                                                              & ((IData)(
                                                                         (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8529_q 
                                                                          >> 9U)) 
                                                                 << 0x11U)) 
                                                             | (0x1ff80U 
                                                                & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8529_q) 
                                                                   << 7U))))))));
    __Vtemp9[1U] = ((0xe0000000U & ((IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8529_q 
                                             >> 0x1eU)) 
                                    << 0x1dU)) | (IData)(
                                                         ((((QData)((IData)(
                                                                            ((0x20000U 
                                                                              & ((IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8529_q 
                                                                                >> 0x1dU)) 
                                                                                << 0x11U)) 
                                                                             | (0x1ff80U 
                                                                                & ((IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8529_q 
                                                                                >> 0x14U)) 
                                                                                << 7U))))) 
                                                            << 0x24U) 
                                                           | (((QData)((IData)(
                                                                               ((0x20000U 
                                                                                & ((IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8529_q 
                                                                                >> 0x13U)) 
                                                                                << 0x11U)) 
                                                                                | (0x1ff80U 
                                                                                & ((IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8529_q 
                                                                                >> 0xaU)) 
                                                                                << 7U))))) 
                                                               << 0x12U) 
                                                              | (QData)((IData)(
                                                                                ((0x20000U 
                                                                                & ((IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8529_q 
                                                                                >> 9U)) 
                                                                                << 0x11U)) 
                                                                                | (0x1ff80U 
                                                                                & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8529_q) 
                                                                                << 7U))))))) 
                                                          >> 0x20U)));
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8557_q) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[0U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8540_q[0U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8540_q[1U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[2U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8540_q[2U];
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[0U] 
            = __Vtemp9[0U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
            = __Vtemp9[1U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[2U] 
            = (0x3fffffU & ((0x80U & ((IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8529_q 
                                               >> 0x27U)) 
                                      << 7U)) | (0x7fU 
                                                 & ((IData)(
                                                            (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8529_q 
                                                             >> 0x1eU)) 
                                                    >> 3U))));
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8123_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8073_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8072_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8302_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8301_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8053_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8052_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8263_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6022_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8088_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8087_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8506_q[0U] 
        = (IData)(((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6593_o 
                    << 8U) | (QData)((IData)((0xffU 
                                              & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                  << 0x10U) 
                                                 | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                    >> 0x10U)))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8506_q[1U] 
        = ((0xfffe0000U & ((IData)(((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6666_o 
                                     << 8U) | (QData)((IData)(
                                                              (0xffU 
                                                               & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                                   << 8U) 
                                                                  | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                                     >> 0x18U))))))) 
                           << 0x11U)) | (IData)((((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6593_o 
                                                   << 8U) 
                                                  | (QData)((IData)(
                                                                    (0xffU 
                                                                     & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                                         << 0x10U) 
                                                                        | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                                           >> 0x10U)))))) 
                                                 >> 0x20U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8506_q[2U] 
        = ((0x1ffffU & ((IData)(((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6666_o 
                                  << 8U) | (QData)((IData)(
                                                           (0xffU 
                                                            & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                                << 8U) 
                                                               | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                                  >> 0x18U))))))) 
                        >> 0xfU)) | (0xfffe0000U & 
                                     ((IData)((((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6666_o 
                                                 << 8U) 
                                                | (QData)((IData)(
                                                                  (0xffU 
                                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                                       << 8U) 
                                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                                         >> 0x18U)))))) 
                                               >> 0x20U)) 
                                      << 0x11U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8506_q[3U] 
        = ((0xfffffffcU & ((IData)(((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6739_o 
                                     << 8U) | (QData)((IData)(
                                                              (0xffU 
                                                               & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U]))))) 
                           << 2U)) | (0x1ffffU & ((IData)(
                                                          (((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6666_o 
                                                             << 8U) 
                                                            | (QData)((IData)(
                                                                              (0xffU 
                                                                               & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                                                << 8U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                                                >> 0x18U)))))) 
                                                           >> 0x20U)) 
                                                  >> 0xfU)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8506_q[4U] 
        = ((3U & ((IData)(((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6739_o 
                            << 8U) | (QData)((IData)(
                                                     (0xffU 
                                                      & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U]))))) 
                  >> 0x1eU)) | (0xfffffffcU & ((IData)(
                                                       (((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6739_o 
                                                          << 8U) 
                                                         | (QData)((IData)(
                                                                           (0xffU 
                                                                            & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U])))) 
                                                        >> 0x20U)) 
                                               << 2U)));
    if ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8313_q))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8568_q 
            = (0xffU & ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7401_o))
                         ? (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8502_q 
                            >> 0x10U) : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7401_o))
                                          ? (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8487_q 
                                             >> 0x10U)
                                          : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7401_o))
                                              ? (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8542_q 
                                                 >> 0x10U)
                                              : (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8542_q 
                                                 >> 0x10U)))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8566_q 
            = (0xffU & ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7401_o))
                         ? (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8502_q 
                            >> 8U) : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7401_o))
                                       ? (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8487_q 
                                          >> 8U) : 
                                      ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7401_o))
                                        ? (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8542_q 
                                           >> 8U) : 
                                       (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8542_q 
                                        >> 8U)))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8564_q 
            = (0xffU & ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7401_o))
                         ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8502_q
                         : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7401_o))
                             ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8487_q
                             : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8542_q)));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8568_q = 0U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8566_q = 0U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8564_q = 0U;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4230_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q 
        = (0xffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                    >> 4U));
    VL_EXTEND_WW(120,108, __Vtemp14, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp17, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8482_q 
        = (0xffU & ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8015_q))
                     ? ((__Vtemp14[1U] << 4U) | (__Vtemp14[0U] 
                                                 >> 0x1cU))
                     : ((8U & __Vtemp17[1U]) ? (~ ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4716_o) 
                                                   >> 7U))
                         : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4716_o) 
                            >> 7U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8369_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8368_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8193_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8192_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8400_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8399_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8524_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8523_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8341_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8181_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8180_o;
    VL_EXTEND_WW(120,108, __Vtemp20, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8544_q 
        = ((0x80000000U & __Vtemp20[2U]) ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8430_q
            : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8434_q);
    if (((IData)(vlTOPp->synth_top__DOT__app_en) & (IData)(vlTOPp->synth_top__DOT__ddr__DOT__rdy))) {
        if ((0U == ((2U == (IData)(vlTOPp->synth_top__DOT__bridge__DOT__state))
                     ? 1U : 0U))) {
            if (vlTOPp->synth_top__DOT__bridge__DOT__wr_go) {
                __Vdlyvval__synth_top__DOT__ddr__DOT__ram__v0[0U] 
                    = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8593_data[0U];
                __Vdlyvval__synth_top__DOT__ddr__DOT__ram__v0[1U] 
                    = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8593_data[1U];
                __Vdlyvval__synth_top__DOT__ddr__DOT__ram__v0[2U] 
                    = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8593_data[2U];
                __Vdlyvval__synth_top__DOT__ddr__DOT__ram__v0[3U] 
                    = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8593_data[3U];
                __Vdlyvset__synth_top__DOT__ddr__DOT__ram__v0 = 1U;
                __Vdlyvdim0__synth_top__DOT__ddr__DOT__ram__v0 
                    = (0x3ffffU & vlTOPp->synth_top__DOT__bridge__DOT__addr_q);
            }
        }
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8020_o;
    if (vlTOPp->reset_na) {
        if ((0U == (IData)(vlTOPp->synth_top__DOT__bridge__DOT__state))) {
            __Vdly__synth_top__DOT__bridge__DOT__beat = 0U;
            __Vdly__synth_top__DOT__bridge__DOT__addr_q 
                = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8591_q;
            __Vdly__synth_top__DOT__bridge__DOT__blen_q = 0x80U;
            if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7912_q) {
                __Vdly__synth_top__DOT__bridge__DOT__state = 1U;
            } else if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7921_q) {
                __Vdly__synth_top__DOT__bridge__DOT__state = 2U;
            }
        } else if ((1U == (IData)(vlTOPp->synth_top__DOT__bridge__DOT__state))) {
            if (vlTOPp->synth_top__DOT__bridge__DOT__wr_go) {
                __Vdly__synth_top__DOT__bridge__DOT__addr_q 
                    = (0x1ffffffU & ((IData)(1U) + vlTOPp->synth_top__DOT__bridge__DOT__addr_q));
                __Vdly__synth_top__DOT__bridge__DOT__beat 
                    = (0xffU & ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__bridge__DOT__beat)));
                if (((IData)(vlTOPp->synth_top__DOT__bridge__DOT__beat) 
                     == ((IData)(vlTOPp->synth_top__DOT__bridge__DOT__blen_q) 
                         - (IData)(1U)))) {
                    __Vdly__synth_top__DOT__bridge__DOT__state = 0U;
                }
            }
        } else if ((2U == (IData)(vlTOPp->synth_top__DOT__bridge__DOT__state))) {
            if (vlTOPp->synth_top__DOT__bridge__DOT__rd_go) {
                __Vdly__synth_top__DOT__bridge__DOT__addr_q 
                    = (0x1ffffffU & ((IData)(1U) + vlTOPp->synth_top__DOT__bridge__DOT__addr_q));
                __Vdly__synth_top__DOT__bridge__DOT__beat 
                    = (0xffU & ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__bridge__DOT__beat)));
                if (((IData)(vlTOPp->synth_top__DOT__bridge__DOT__beat) 
                     == ((IData)(vlTOPp->synth_top__DOT__bridge__DOT__blen_q) 
                         - (IData)(1U)))) {
                    __Vdly__synth_top__DOT__bridge__DOT__state = 0U;
                }
            }
        } else {
            __Vdly__synth_top__DOT__bridge__DOT__state = 0U;
        }
    } else {
        __Vdly__synth_top__DOT__bridge__DOT__state = 0U;
        __Vdly__synth_top__DOT__bridge__DOT__beat = 0U;
        __Vdly__synth_top__DOT__bridge__DOT__addr_q = 0U;
        __Vdly__synth_top__DOT__bridge__DOT__blen_q = 0x80U;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8158_q 
        = (1U & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)
                  ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8159_o) 
                     >> 0xeU) : ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                                  ? (VL_GTES_III(1,32,32, 1U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8357_q)) 
                                     | ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8159_o) 
                                        >> 0xeU)) : 
                                 ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o)) 
                                  & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8159_o) 
                                     >> 0xeU)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8296_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8295_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8154_q 
        = ((0x3ffeU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8159_o) 
                       >> 1U)) | (VL_LTS_III(1,32,32, 
                                             (0xfffU 
                                              & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8410_q 
                                                 >> 0xcU)), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q)) 
                                  & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8159_o) 
                                     >> 1U)));
    vlTOPp->synth_top__DOT__app_rd_data_valid = 0U;
    if ((0x40000U & vlTOPp->synth_top__DOT__ddr__DOT__pipe
         [0xcU])) {
        vlTOPp->synth_top__DOT__app_rd_data[0U] = vlTOPp->synth_top__DOT__ddr__DOT__ram
            [(0x3ffffU & vlTOPp->synth_top__DOT__ddr__DOT__pipe
              [0xcU])][0U];
        vlTOPp->synth_top__DOT__app_rd_data[1U] = vlTOPp->synth_top__DOT__ddr__DOT__ram
            [(0x3ffffU & vlTOPp->synth_top__DOT__ddr__DOT__pipe
              [0xcU])][1U];
        vlTOPp->synth_top__DOT__app_rd_data[2U] = vlTOPp->synth_top__DOT__ddr__DOT__ram
            [(0x3ffffU & vlTOPp->synth_top__DOT__ddr__DOT__pipe
              [0xcU])][2U];
        vlTOPp->synth_top__DOT__app_rd_data[3U] = vlTOPp->synth_top__DOT__ddr__DOT__ram
            [(0x3ffffU & vlTOPp->synth_top__DOT__ddr__DOT__pipe
              [0xcU])][3U];
        vlTOPp->synth_top__DOT__app_rd_data_valid = 1U;
    }
    vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2 = 
        vlTOPp->synth_top__DOT__ddr__DOT__pipe[0xbU];
    __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v0 
        = vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2;
    vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2 = 
        vlTOPp->synth_top__DOT__ddr__DOT__pipe[0xaU];
    __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v1 
        = vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2;
    vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2 = 
        vlTOPp->synth_top__DOT__ddr__DOT__pipe[9U];
    __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v2 
        = vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2;
    vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2 = 
        vlTOPp->synth_top__DOT__ddr__DOT__pipe[8U];
    __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v3 
        = vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2;
    vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2 = 
        vlTOPp->synth_top__DOT__ddr__DOT__pipe[7U];
    __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v4 
        = vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2;
    vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2 = 
        vlTOPp->synth_top__DOT__ddr__DOT__pipe[6U];
    __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v5 
        = vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2;
    vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2 = 
        vlTOPp->synth_top__DOT__ddr__DOT__pipe[5U];
    __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v6 
        = vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2;
    vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2 = 
        vlTOPp->synth_top__DOT__ddr__DOT__pipe[4U];
    __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v7 
        = vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2;
    vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2 = 
        vlTOPp->synth_top__DOT__ddr__DOT__pipe[3U];
    __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v8 
        = vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2;
    vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2 = 
        vlTOPp->synth_top__DOT__ddr__DOT__pipe[2U];
    __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v9 
        = vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2;
    vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2 = 
        vlTOPp->synth_top__DOT__ddr__DOT__pipe[1U];
    __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v10 
        = vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2;
    vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2 = 
        vlTOPp->synth_top__DOT__ddr__DOT__pipe[0U];
    __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v11 
        = vlTOPp->synth_top__DOT__ddr__DOT____Vlvbound2;
    if (((IData)(vlTOPp->synth_top__DOT__app_en) & (IData)(vlTOPp->synth_top__DOT__ddr__DOT__rdy))) {
        if ((0U != ((2U == (IData)(vlTOPp->synth_top__DOT__bridge__DOT__state))
                     ? 1U : 0U))) {
            __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v13 
                = (0x40000U | (0x3ffffU & vlTOPp->synth_top__DOT__bridge__DOT__addr_q));
            __Vdlyvset__synth_top__DOT__ddr__DOT__pipe__v13 = 1U;
        }
    }
    if (__Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram__v0) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram[__Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram__v0][0U] 
            = __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram__v0[0U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram[__Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram__v0][1U] 
            = __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram__v0[1U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram[__Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram__v0][2U] 
            = __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram__v0[2U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram[__Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram__v0][3U] 
            = __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_dpram__v0[3U];
    }
    if (__Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf3__v0) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf3[__Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf3__v0] 
            = __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf3__v0;
    }
    if (__Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf2__v0) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf2[__Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf2__v0] 
            = __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf2__v0;
    }
    if (__Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf1__v0) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf1[__Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf1__v0] 
            = __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf1__v0;
    }
    if (__Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf0__v0) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf0[__Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf0__v0] 
            = __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_linf0__v0;
    }
    if (__Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line3__v0) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_line3[__Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line3__v0] 
            = __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line3__v0;
    }
    if (__Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line2__v0) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_line2[__Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line2__v0] 
            = __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line2__v0;
    }
    if (__Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line1__v0) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_line1[__Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line1__v0] 
            = __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line1__v0;
    }
    if (__Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line0__v0) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_line0[__Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line0__v0] 
            = __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__o_line0__v0;
    }
    vlTOPp->synth_top__DOT__bridge__DOT__blen_q = __Vdly__synth_top__DOT__bridge__DOT__blen_q;
    vlTOPp->synth_top__DOT__bridge__DOT__beat = __Vdly__synth_top__DOT__bridge__DOT__beat;
    if (__Vdlyvset__synth_top__DOT__ddr__DOT__ram__v0) {
        vlTOPp->synth_top__DOT__ddr__DOT__ram[__Vdlyvdim0__synth_top__DOT__ddr__DOT__ram__v0][0U] 
            = __Vdlyvval__synth_top__DOT__ddr__DOT__ram__v0[0U];
        vlTOPp->synth_top__DOT__ddr__DOT__ram[__Vdlyvdim0__synth_top__DOT__ddr__DOT__ram__v0][1U] 
            = __Vdlyvval__synth_top__DOT__ddr__DOT__ram__v0[1U];
        vlTOPp->synth_top__DOT__ddr__DOT__ram[__Vdlyvdim0__synth_top__DOT__ddr__DOT__ram__v0][2U] 
            = __Vdlyvval__synth_top__DOT__ddr__DOT__ram__v0[2U];
        vlTOPp->synth_top__DOT__ddr__DOT__ram[__Vdlyvdim0__synth_top__DOT__ddr__DOT__ram__v0][3U] 
            = __Vdlyvval__synth_top__DOT__ddr__DOT__ram__v0[3U];
    }
    vlTOPp->synth_top__DOT__bridge__DOT__addr_q = __Vdly__synth_top__DOT__bridge__DOT__addr_q;
    vlTOPp->synth_top__DOT__ddr__DOT__pipe[0xcU] = __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v0;
    vlTOPp->synth_top__DOT__ddr__DOT__pipe[0xbU] = __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v1;
    vlTOPp->synth_top__DOT__ddr__DOT__pipe[0xaU] = __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v2;
    vlTOPp->synth_top__DOT__ddr__DOT__pipe[9U] = __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v3;
    vlTOPp->synth_top__DOT__ddr__DOT__pipe[8U] = __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v4;
    vlTOPp->synth_top__DOT__ddr__DOT__pipe[7U] = __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v5;
    vlTOPp->synth_top__DOT__ddr__DOT__pipe[6U] = __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v6;
    vlTOPp->synth_top__DOT__ddr__DOT__pipe[5U] = __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v7;
    vlTOPp->synth_top__DOT__ddr__DOT__pipe[4U] = __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v8;
    vlTOPp->synth_top__DOT__ddr__DOT__pipe[3U] = __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v9;
    vlTOPp->synth_top__DOT__ddr__DOT__pipe[2U] = __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v10;
    vlTOPp->synth_top__DOT__ddr__DOT__pipe[1U] = __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v11;
    vlTOPp->synth_top__DOT__ddr__DOT__pipe[0U] = 0U;
    if (__Vdlyvset__synth_top__DOT__ddr__DOT__pipe__v13) {
        vlTOPp->synth_top__DOT__ddr__DOT__pipe[0U] 
            = __Vdlyvval__synth_top__DOT__ddr__DOT__pipe__v13;
    }
    vlTOPp->synth_top__DOT__bridge__DOT__state = __Vdly__synth_top__DOT__bridge__DOT__state;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6405_o 
        = (0xffffU & ((0xffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8499_q)) 
                      * (0xffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8499_q) 
                                  >> 8U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4716_o 
        = (0xffffU & ((0xffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8497_q)) 
                      * (0xffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8497_q) 
                                  >> 8U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4649_o 
        = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8416_q) 
            << 0xbU) | (0x7ffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8418_q) 
                                  >> 1U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4647_o 
        = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8413_q) 
            << 0xbU) | (0x7ffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8417_q) 
                                  >> 1U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8533_q 
        = (((QData)((IData)((0x3ffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9906_o)))) 
            << 0x1eU) | (QData)((IData)(((0x3ff00000U 
                                          & ((IData)(
                                                     (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9906_o 
                                                      >> 0xaU)) 
                                             << 0x14U)) 
                                         | ((0xffc00U 
                                             & ((IData)(
                                                        (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9906_o 
                                                         >> 0x14U)) 
                                                << 0xaU)) 
                                            | (0x3ffU 
                                               & (IData)(
                                                         (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9906_o 
                                                          >> 0x1eU))))))));
    vlTOPp->o_de = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8574_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8311_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6176_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8530_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4252_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8548_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8547_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8076_q 
        = VL_LTS_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8079_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8082_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8039_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8038_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7965_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7964_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7961_q[0U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7960_o[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7961_q[1U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7960_o[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7961_q[2U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7960_o[2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7961_q[3U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7960_o[3U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7947_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7946_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4204_o 
        = (0xffU & (((0xffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8546_q) 
                     > (0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8546_q 
                                 >> 8U))) ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8546_q
                     : (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8546_q 
                        >> 8U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1832_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7994_q) 
           & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7991_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8190_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8189_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8074_q 
        = VL_LTS_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8079_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8056_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3038_o 
        = (((2U == (3U & ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8476_q)))) 
            << 2U) | (((1U == (3U & ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8476_q)))) 
                       << 1U) | (0U == (3U & ((IData)(1U) 
                                              + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8476_q))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__scalaire_off_v 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4089_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8558_q 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8556_q) 
           & (0U != (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8015_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__scalaire_bib_v 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4069_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__scalaire_prim_v 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4063_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__scalaire_last_v 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4066_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2236_o 
        = ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8103_q)) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8100_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2321_o 
        = ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8109_q)) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8106_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5986_o 
        = VL_LTS_III(1,32,32, ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8257_q)), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8030_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2883_o 
        = VL_LTS_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8336_q), 
                     ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8333_q) 
                      - (IData)(1U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_bibu 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8409_q;
    vlTOPp->o_hs = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8570_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8307_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6172_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6292_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8254_q)
            ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8620_data
            : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8608_data);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8241_q 
        = (0xfffU & ((0x800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q))
                      ? ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                          ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6246_o
                          : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                              ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6253_o
                              : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6246_o))
                      : ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                          ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6253_o
                          : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6246_o)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6290_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8253_q)
            ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8617_data
            : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8605_data);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8239_q 
        = (0xfffU & ((0x800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q))
                      ? ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                          ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6246_o
                          : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                              ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6246_o
                              : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                                  ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6253_o
                                  : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6246_o)))
                      : ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                          ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6246_o
                          : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                              ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6253_o
                              : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6246_o))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6288_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8252_q)
            ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8614_data
            : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8602_data);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8237_q 
        = (0xfffU & ((0x800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q))
                      ? ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                          ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6246_o
                          : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                              ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6246_o
                              : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                                  ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6246_o
                                  : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6253_o)))
                      : ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                          ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6246_o
                          : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                              ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6246_o
                              : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                                  ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6253_o
                                  : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6246_o)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6286_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8251_q)
            ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8611_data
            : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8599_data);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8235_q 
        = (0xfffU & ((0x800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q))
                      ? ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                          ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6253_o
                          : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6246_o)
                      : ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                          ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6246_o
                          : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                              ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6246_o
                              : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                                  ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6246_o
                                  : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6253_o)))));
    vlTOPp->o_vs = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8572_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8309_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6174_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8233_q 
        = (0xfffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8410_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8255_q 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8388_q) 
           & ((8U & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8159_o) 
                     << 3U)) | ((4U & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8159_o) 
                                       << 2U)) | ((2U 
                                                   & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8159_o) 
                                                      << 1U)) 
                                                  | (1U 
                                                     & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8159_o))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8246_q 
        = ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5714_o))
            ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8500_q
            : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5714_o))
                ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8485_q
                : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8543_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2293_o 
        = (((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q)) 
            & (1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q))) 
           | ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q)) 
              & (2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2464_o 
        = (((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q)) 
            & (1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q))) 
           | ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q)) 
              & (2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2266_o 
        = (((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q)) 
            & (0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q))) 
           | ((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q)) 
              & (1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2437_o 
        = (((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q)) 
            & (0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q))) 
           | ((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q)) 
              & (1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8540_q[0U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8539_q[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8540_q[1U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8539_q[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8540_q[2U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8539_q[2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8557_q 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8555_q) 
           & (0U != (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8018_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8529_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8528_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2378_o 
        = (((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8130_q)) 
            & (1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q))) 
           | ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8130_q)) 
              & (2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2548_o 
        = (((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q)) 
            & (1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8130_q))) 
           | ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q)) 
              & (2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8130_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2351_o 
        = (((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8130_q)) 
            & (0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q))) 
           | ((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8130_q)) 
              & (1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2521_o 
        = (((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q)) 
            & (0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8130_q))) 
           | ((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q)) 
              & (1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8130_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8072_q 
        = (VL_LTS_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8266_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8059_q)) 
           & (VL_GTES_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8266_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8094_q)) 
              & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8083_q) 
                  | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8085_q)) 
                 & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8065_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2735_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8302_q) 
           - ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8053_q) 
              << 1U));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2763_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8263_q) 
           == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8088_q));
    vlTOPp->o_b = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8568_q;
    vlTOPp->o_g = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8566_q;
    vlTOPp->o_r = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8564_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8502_q 
        = ((((0x200U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7180_o))
              ? 0U : ((0U != (3U & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7180_o) 
                                    >> 8U))) ? 0xffU
                       : (0xffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7180_o)))) 
            << 0x10U) | ((((0x200U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7162_o))
                            ? 0U : ((0U != (3U & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7162_o) 
                                                  >> 8U)))
                                     ? 0xffU : (0xffU 
                                                & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7162_o)))) 
                          << 8U) | ((0x200U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7142_o))
                                     ? 0U : ((0U != 
                                              (3U & 
                                               ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7142_o) 
                                                >> 8U)))
                                              ? 0xffU
                                              : (0xffU 
                                                 & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7142_o))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8542_q 
        = ((((0x40000U & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7358_o)
              ? 0U : ((0U != (0xfU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7358_o 
                                      >> 0xfU))) ? 0xffU
                       : (0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7358_o 
                                   >> 7U)))) << 0x10U) 
           | ((((0x40000U & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7340_o)
                 ? 0U : ((0U != (0xfU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7340_o 
                                         >> 0xfU)))
                          ? 0xffU : (0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7340_o 
                                              >> 7U)))) 
               << 8U) | ((0x40000U & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7321_o)
                          ? 0U : ((0U != (0xfU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7321_o 
                                                  >> 0xfU)))
                                   ? 0xffU : (0xffU 
                                              & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7321_o 
                                                 >> 7U))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8313_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6178_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8487_q 
        = ((((1U & (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8490_q 
                            >> 0x32U))) ? 0U : ((1U 
                                                 & (IData)(
                                                           (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8490_q 
                                                            >> 0x32U)))
                                                 ? 0xffU
                                                 : 
                                                (0xffU 
                                                 & (IData)(
                                                           (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8490_q 
                                                            >> 0x2aU))))) 
            << 0x10U) | ((((1U & (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8490_q 
                                          >> 0x21U)))
                            ? 0U : ((1U & (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8490_q 
                                                   >> 0x21U)))
                                     ? 0xffU : (0xffU 
                                                & (IData)(
                                                          (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8490_q 
                                                           >> 0x19U))))) 
                          << 8U) | ((1U & (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8490_q 
                                                   >> 0x10U)))
                                     ? 0U : ((1U & (IData)(
                                                           (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8490_q 
                                                            >> 0x10U)))
                                              ? 0xffU
                                              : (0xffU 
                                                 & (IData)(
                                                           (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8490_q 
                                                            >> 8U)))))));
    if ((8U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9866_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x14U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x13U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x12U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x13U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x12U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x11U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x12U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x11U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x10U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x10U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xfU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xfU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xeU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xdU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xeU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xdU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xcU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xdU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xcU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xbU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xbU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xaU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9868_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x28U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x27U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x26U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x27U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x26U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x25U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x26U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x25U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x24U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x24U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x23U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x23U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x22U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x21U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x22U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x21U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x20U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x21U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x20U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x1fU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x1fU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x1eU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9870_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x3cU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x3bU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x3aU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x3bU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x3aU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x39U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x3aU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x39U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x38U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x38U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x37U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x37U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x36U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x35U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x36U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x35U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x34U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x35U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x34U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x33U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x33U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x32U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9872_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x50U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x4fU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x4eU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x4fU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x4eU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x4dU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x4eU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x4dU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x4cU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x4cU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x4bU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x4bU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x4aU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x49U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x4aU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x49U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x48U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x49U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x48U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x47U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x47U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x46U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9874_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x64U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x63U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x62U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x63U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x62U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x61U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x62U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x61U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x60U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x60U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x5fU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x5fU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x5eU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x5dU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x5eU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x5dU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x5cU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x5dU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x5cU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x5bU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x5bU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x5aU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9876_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x78U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x77U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x76U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x77U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x76U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x75U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x76U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x75U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x74U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x74U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x73U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x73U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x72U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x71U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x72U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x71U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x70U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x71U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x70U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x6fU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x6fU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x6eU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9878_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x8cU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x8bU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x8aU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x8bU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x8aU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x89U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x8aU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x89U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x88U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x88U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x87U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x87U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x86U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x85U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x86U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x85U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x84U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x85U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x84U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x83U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x83U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x82U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9880_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa0U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x9fU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x9eU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x9fU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x9eU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x9dU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x9eU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x9dU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x9cU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x9cU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x9bU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x9bU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x9aU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x99U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x9aU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x99U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x98U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x99U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x98U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x97U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x97U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x96U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9882_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb4U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb3U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb2U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb3U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb2U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb1U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb2U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb1U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb0U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb0U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xafU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xafU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xaeU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xadU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xaeU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xadU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xacU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xadU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xacU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xabU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xabU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xaaU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9884_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc8U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc7U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc6U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc7U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc6U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc5U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc6U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc5U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc4U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc4U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc3U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc3U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc2U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc1U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc2U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc1U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc0U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc1U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc0U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xbfU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xbfU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xbeU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9886_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xdcU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xdbU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xdaU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xdbU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xdaU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd9U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xdaU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd9U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd8U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd8U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd7U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd7U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd6U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd5U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd6U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd5U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd4U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd5U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd4U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd3U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd3U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd2U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9888_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf0U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xefU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xeeU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xefU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xeeU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xedU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xeeU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xedU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xecU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xecU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xebU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xebU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xeaU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe9U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xeaU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe9U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe8U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe9U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe8U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe7U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe7U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe6U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9890_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x104U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x103U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x102U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x103U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x102U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x101U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x102U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x101U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x100U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x100U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xffU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xffU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xfeU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xfdU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xfeU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xfdU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xfcU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xfdU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xfcU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xfbU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xfbU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xfaU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9892_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x118U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x117U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x116U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x117U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x116U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x115U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x116U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x115U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x114U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x114U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x113U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x113U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x112U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x111U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x112U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x111U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x110U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x111U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x110U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x10fU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x10fU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x10eU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9894_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x12cU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x12bU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x12aU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x12bU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x12aU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x129U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x12aU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x129U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x128U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x128U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x127U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x127U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x126U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x125U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x126U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x125U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x124U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x125U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x124U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x123U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x123U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x122U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9896_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x13fU])) 
                                               << 8U) 
                                              | ((QData)((IData)(
                                                                 vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x13eU])) 
                                                 >> 0x18U))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x13fU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x13eU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x13dU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x13eU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x13dU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x13cU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x13cU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x13bU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x13bU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x13aU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x139U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x13aU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x139U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x138U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x139U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x138U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x137U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x137U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x136U])))))));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9866_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xaU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[9U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[8U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[9U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[8U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[7U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[8U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[7U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[6U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[6U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[5U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[5U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[4U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[3U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[4U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[3U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[2U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[3U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[2U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[1U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[1U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9868_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x1eU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x1dU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x1cU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x1dU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x1cU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x1bU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x1cU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x1bU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x1aU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x1aU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x19U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x19U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x18U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x17U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x18U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x17U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x16U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x17U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x16U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x15U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x15U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x14U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9870_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x32U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x31U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x30U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x31U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x30U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x2fU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x30U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x2fU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x2eU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x2eU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x2dU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x2dU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x2cU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x2bU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x2cU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x2bU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x2aU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x2bU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x2aU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x29U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x29U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x28U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9872_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x46U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x45U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x44U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x45U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x44U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x43U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x44U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x43U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x42U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x42U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x41U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x41U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x40U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x3fU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x40U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x3fU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x3eU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x3fU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x3eU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x3dU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x3dU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x3cU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9874_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x5aU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x59U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x58U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x59U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x58U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x57U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x58U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x57U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x56U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x56U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x55U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x55U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x54U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x53U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x54U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x53U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x52U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x53U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x52U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x51U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x51U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x50U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9876_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x6eU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x6dU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x6cU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x6dU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x6cU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x6bU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x6cU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x6bU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x6aU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x6aU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x69U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x69U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x68U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x67U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x68U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x67U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x66U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x67U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x66U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x65U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x65U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x64U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9878_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x82U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x81U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x80U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x81U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x80U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x7fU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x80U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x7fU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x7eU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x7eU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x7dU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x7dU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x7cU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x7bU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x7cU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x7bU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x7aU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x7bU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x7aU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x79U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x79U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x78U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9880_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x96U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x95U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x94U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x95U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x94U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x93U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x94U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x93U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x92U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x92U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x91U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x91U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x90U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x8fU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x90U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x8fU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x8eU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x8fU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x8eU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x8dU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x8dU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x8cU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9882_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xaaU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa9U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa8U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa9U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa8U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa7U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa8U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa7U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa6U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa6U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa5U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa5U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa4U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa3U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa4U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa3U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa2U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa3U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa2U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa1U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa1U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xa0U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9884_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xbeU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xbdU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xbcU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xbdU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xbcU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xbbU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xbcU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xbbU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xbaU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xbaU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb9U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb9U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb8U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb7U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb8U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb7U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb6U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb7U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb6U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb5U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb5U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xb4U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9886_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd2U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd1U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd0U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd1U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd0U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xcfU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xd0U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xcfU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xceU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xceU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xcdU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xcdU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xccU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xcbU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xccU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xcbU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xcaU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xcbU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xcaU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc9U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc9U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xc8U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9888_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe6U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe5U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe4U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe5U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe4U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe3U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe4U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe3U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe2U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe2U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe1U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe1U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe0U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xdfU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xe0U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xdfU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xdeU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xdfU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xdeU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xddU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xddU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xdcU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9890_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xfaU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf9U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf8U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf9U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf8U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf7U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf8U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf7U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf6U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf6U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf5U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf5U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf4U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf3U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf4U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf3U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf2U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf3U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf2U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf1U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf1U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0xf0U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9892_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x10eU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x10dU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x10cU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x10dU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x10cU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x10bU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x10cU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x10bU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x10aU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x10aU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x109U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x109U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x108U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x107U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x108U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x107U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x106U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x107U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x106U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x105U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x105U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x104U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9894_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x122U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x121U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x120U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x121U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x120U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x11fU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x120U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x11fU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x11eU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x11eU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x11dU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x11dU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x11cU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x11bU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x11cU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x11bU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x11aU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x11bU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x11aU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x119U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x119U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x118U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9896_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x136U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x135U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x134U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x135U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x134U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x133U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x134U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x133U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x132U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x132U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x131U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x131U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x130U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x12fU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x130U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x12fU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x12eU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x12fU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x12eU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x12dU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x12dU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8517_q[0x12cU])))))));
    }
    if ((8U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9014_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x14U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x13U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x12U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x13U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x12U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x11U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x12U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x11U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x10U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x10U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xfU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xfU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xeU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xdU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xeU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xdU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xcU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xdU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xcU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xbU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xbU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xaU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9016_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x28U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x27U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x26U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x27U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x26U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x25U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x26U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x25U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x24U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x24U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x23U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x23U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x22U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x21U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x22U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x21U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x20U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x21U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x20U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x1fU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x1fU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x1eU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9018_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x3cU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x3bU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x3aU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x3bU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x3aU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x39U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x3aU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x39U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x38U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x38U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x37U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x37U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x36U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x35U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x36U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x35U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x34U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x35U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x34U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x33U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x33U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x32U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9020_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x50U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x4fU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x4eU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x4fU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x4eU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x4dU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x4eU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x4dU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x4cU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x4cU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x4bU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x4bU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x4aU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x49U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x4aU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x49U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x48U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x49U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x48U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x47U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x47U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x46U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9022_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x64U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x63U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x62U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x63U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x62U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x61U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x62U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x61U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x60U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x60U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x5fU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x5fU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x5eU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x5dU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x5eU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x5dU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x5cU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x5dU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x5cU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x5bU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x5bU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x5aU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9024_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x78U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x77U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x76U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x77U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x76U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x75U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x76U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x75U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x74U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x74U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x73U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x73U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x72U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x71U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x72U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x71U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x70U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x71U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x70U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x6fU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x6fU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x6eU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9026_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x8cU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x8bU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x8aU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x8bU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x8aU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x89U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x8aU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x89U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x88U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x88U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x87U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x87U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x86U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x85U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x86U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x85U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x84U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x85U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x84U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x83U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x83U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x82U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9028_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa0U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x9fU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x9eU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x9fU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x9eU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x9dU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x9eU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x9dU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x9cU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x9cU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x9bU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x9bU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x9aU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x99U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x9aU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x99U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x98U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x99U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x98U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x97U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x97U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x96U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9030_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb4U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb3U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb2U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb3U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb2U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb1U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb2U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb1U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb0U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb0U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xafU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xafU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xaeU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xadU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xaeU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xadU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xacU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xadU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xacU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xabU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xabU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xaaU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9032_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc8U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc7U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc6U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc7U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc6U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc5U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc6U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc5U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc4U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc4U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc3U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc3U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc2U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc1U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc2U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc1U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc0U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc1U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc0U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xbfU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xbfU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xbeU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9034_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xdcU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xdbU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xdaU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xdbU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xdaU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd9U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xdaU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd9U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd8U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd8U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd7U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd7U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd6U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd5U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd6U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd5U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd4U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd5U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd4U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd3U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd3U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd2U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9036_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf0U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xefU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xeeU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xefU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xeeU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xedU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xeeU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xedU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xecU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xecU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xebU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xebU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xeaU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe9U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xeaU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe9U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe8U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe9U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe8U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe7U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe7U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe6U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9038_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x104U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x103U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x102U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x103U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x102U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x101U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x102U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x101U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x100U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x100U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xffU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xffU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xfeU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xfdU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xfeU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xfdU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xfcU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xfdU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xfcU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xfbU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xfbU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xfaU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9040_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x118U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x117U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x116U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x117U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x116U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x115U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x116U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x115U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x114U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x114U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x113U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x113U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x112U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x111U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x112U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x111U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x110U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x111U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x110U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x10fU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x10fU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x10eU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9042_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x12cU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x12bU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x12aU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x12bU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x12aU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x129U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x12aU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x129U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x128U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x128U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x127U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x127U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x126U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x125U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x126U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x125U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x124U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x125U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x124U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x123U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x123U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x122U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9044_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x13fU])) 
                                               << 8U) 
                                              | ((QData)((IData)(
                                                                 vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x13eU])) 
                                                 >> 0x18U))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x13fU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x13eU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x13dU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x13eU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x13dU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x13cU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x13cU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x13bU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x13bU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x13aU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x139U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x13aU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x139U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x138U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x139U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x138U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x137U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x137U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x136U])))))));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9014_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xaU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[9U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[8U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[9U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[8U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[7U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[8U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[7U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[6U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[6U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[5U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[5U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[4U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[3U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[4U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[3U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[2U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[3U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[2U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[1U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[1U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9016_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x1eU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x1dU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x1cU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x1dU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x1cU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x1bU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x1cU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x1bU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x1aU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x1aU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x19U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x19U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x18U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x17U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x18U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x17U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x16U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x17U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x16U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x15U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x15U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x14U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9018_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x32U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x31U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x30U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x31U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x30U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x2fU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x30U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x2fU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x2eU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x2eU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x2dU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x2dU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x2cU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x2bU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x2cU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x2bU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x2aU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x2bU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x2aU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x29U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x29U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x28U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9020_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x46U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x45U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x44U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x45U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x44U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x43U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x44U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x43U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x42U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x42U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x41U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x41U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x40U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x3fU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x40U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x3fU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x3eU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x3fU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x3eU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x3dU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x3dU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x3cU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9022_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x5aU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x59U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x58U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x59U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x58U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x57U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x58U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x57U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x56U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x56U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x55U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x55U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x54U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x53U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x54U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x53U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x52U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x53U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x52U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x51U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x51U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x50U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9024_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x6eU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x6dU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x6cU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x6dU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x6cU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x6bU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x6cU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x6bU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x6aU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x6aU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x69U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x69U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x68U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x67U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x68U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x67U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x66U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x67U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x66U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x65U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x65U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x64U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9026_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x82U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x81U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x80U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x81U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x80U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x7fU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x80U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x7fU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x7eU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x7eU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x7dU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x7dU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x7cU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x7bU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x7cU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x7bU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x7aU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x7bU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x7aU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x79U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x79U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x78U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9028_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x96U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x95U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x94U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x95U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x94U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x93U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x94U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x93U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x92U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x92U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x91U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x91U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x90U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x8fU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x90U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x8fU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x8eU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x8fU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x8eU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x8dU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x8dU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x8cU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9030_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xaaU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa9U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa8U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa9U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa8U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa7U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa8U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa7U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa6U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa6U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa5U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa5U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa4U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa3U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa4U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa3U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa2U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa3U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa2U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa1U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa1U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xa0U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9032_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xbeU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xbdU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xbcU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xbdU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xbcU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xbbU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xbcU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xbbU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xbaU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xbaU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb9U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb9U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb8U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb7U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb8U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb7U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb6U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb7U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb6U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb5U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb5U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xb4U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9034_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd2U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd1U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd0U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd1U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd0U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xcfU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xd0U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xcfU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xceU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xceU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xcdU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xcdU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xccU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xcbU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xccU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xcbU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xcaU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xcbU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xcaU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc9U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc9U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xc8U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9036_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe6U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe5U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe4U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe5U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe4U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe3U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe4U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe3U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe2U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe2U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe1U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe1U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe0U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xdfU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xe0U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xdfU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xdeU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xdfU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xdeU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xddU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xddU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xdcU])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9038_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xfaU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf9U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf8U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf9U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf8U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf7U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf8U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf7U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf6U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf6U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf5U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf5U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf4U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf3U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf4U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf3U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf2U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf3U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf2U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf1U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf1U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0xf0U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9040_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x10eU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x10dU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x10cU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x10dU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x10cU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x10bU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x10cU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x10bU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x10aU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x10aU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x109U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x109U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x108U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x107U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x108U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x107U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x106U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x107U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x106U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x105U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x105U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x104U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9042_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x122U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x121U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x120U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x121U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x120U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x11fU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x120U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x11fU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x11eU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x11eU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x11dU])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x11dU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x11cU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x11bU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x11cU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x11bU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x11aU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x11bU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x11aU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x119U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x119U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x118U])))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9044_o 
            = (0xffffffffffULL & ((4U & ((IData)(0xffU) 
                                         - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                   ? ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x136U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x135U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x134U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x135U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x134U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x133U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x134U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x133U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x132U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x132U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x131U])))))
                                   : ((2U & ((IData)(3U) 
                                             - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                       ? ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x131U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x130U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x12fU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x130U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x12fU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x12eU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x12fU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x12eU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x12dU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x12dU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8516_q[0x12cU])))))));
    }
    __Vtemp23[0U] = (IData)((((QData)((IData)(((0x20000U 
                                                & ((IData)(
                                                           (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8524_q 
                                                            >> 0x1dU)) 
                                                   << 0x11U)) 
                                               | (0x1ff80U 
                                                  & ((IData)(
                                                             (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8524_q 
                                                              >> 0x14U)) 
                                                     << 7U))))) 
                              << 0x24U) | (((QData)((IData)(
                                                            ((0x20000U 
                                                              & ((IData)(
                                                                         (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8524_q 
                                                                          >> 0x13U)) 
                                                                 << 0x11U)) 
                                                             | (0x1ff80U 
                                                                & ((IData)(
                                                                           (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8524_q 
                                                                            >> 0xaU)) 
                                                                   << 7U))))) 
                                            << 0x12U) 
                                           | (QData)((IData)(
                                                             ((0x20000U 
                                                               & ((IData)(
                                                                          (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8524_q 
                                                                           >> 9U)) 
                                                                  << 0x11U)) 
                                                              | (0x1ff80U 
                                                                 & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8524_q) 
                                                                    << 7U))))))));
    __Vtemp23[1U] = ((0xe0000000U & ((IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8524_q 
                                              >> 0x1eU)) 
                                     << 0x1dU)) | (IData)(
                                                          ((((QData)((IData)(
                                                                             ((0x20000U 
                                                                               & ((IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8524_q 
                                                                                >> 0x1dU)) 
                                                                                << 0x11U)) 
                                                                              | (0x1ff80U 
                                                                                & ((IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8524_q 
                                                                                >> 0x14U)) 
                                                                                << 7U))))) 
                                                             << 0x24U) 
                                                            | (((QData)((IData)(
                                                                                ((0x20000U 
                                                                                & ((IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8524_q 
                                                                                >> 0x13U)) 
                                                                                << 0x11U)) 
                                                                                | (0x1ff80U 
                                                                                & ((IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8524_q 
                                                                                >> 0xaU)) 
                                                                                << 7U))))) 
                                                                << 0x12U) 
                                                               | (QData)((IData)(
                                                                                ((0x20000U 
                                                                                & ((IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8524_q 
                                                                                >> 9U)) 
                                                                                << 0x11U)) 
                                                                                | (0x1ff80U 
                                                                                & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8524_q) 
                                                                                << 7U))))))) 
                                                           >> 0x20U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4369_o[0U] 
        = __Vtemp23[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4369_o[1U] 
        = __Vtemp23[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4369_o[2U] 
        = (0x3fffffU & ((0x80U & ((IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8524_q 
                                           >> 0x27U)) 
                                  << 7U)) | (0x7fU 
                                             & ((IData)(
                                                        (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8524_q 
                                                         >> 0x1eU)) 
                                                >> 3U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8523_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8522_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4221_o 
        = (0xffU & (((0xffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8544_q) 
                     > (0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8544_q 
                                 >> 8U))) ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8544_q
                     : (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8544_q 
                        >> 8U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8434_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8433_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8430_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8429_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8593_data[0U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram
        [vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2129_o][0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8593_data[1U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram
        [vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2129_o][1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8593_data[2U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram
        [vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2129_o][2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8593_data[3U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram
        [vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2129_o][3U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2656_o 
        = (((6U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q))) 
            << 2U) | (((4U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q))) 
                       << 1U) | (3U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3625_o 
        = ((((5U == (0xfU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q))) 
             | (6U == (0xfU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q)))) 
            << 2U) | (((0xcU == (0xfU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q))) 
                       << 1U) | (4U == (0xfU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3182_o 
        = (((5U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q))) 
            << 2U) | (((4U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q))) 
                       << 1U) | (3U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3335_o 
        = (((5U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q))) 
            << 2U) | (((4U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q))) 
                       << 1U) | (3U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3648_o 
        = (VL_LTS_III(1,32,32, 0U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8479_q))
            ? 0U : ((3U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q)))
                     ? 0U : ((0x10U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q))
                              ? ((0xff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8422_q 
                                               << 0x10U)) 
                                 | ((0xff00U & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8422_q) 
                                    | (0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8422_q 
                                                >> 0x10U))))
                              : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8422_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3573_o 
        = (((5U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q))) 
            << 2U) | (((4U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q))) 
                       << 1U) | (3U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3400_o 
        = (((5U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q))) 
            << 2U) | (((4U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q))) 
                       << 1U) | (3U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8591_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8590_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7921_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7920_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7912_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7911_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8357_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8356_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8049_o;
    __Vdly__synth_top__DOT__ddr__DOT__cnt = (0xfU & 
                                             ((IData)(1U) 
                                              + (IData)(vlTOPp->synth_top__DOT__ddr__DOT__cnt)));
    vlTOPp->synth_top__DOT__ddr__DOT__rdy = (0xdU > (IData)(vlTOPp->synth_top__DOT__ddr__DOT__cnt));
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5986_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6019_o 
            = (0xfffU & ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8257_q)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6020_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8259_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6021_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8261_q;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6019_o = 0U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6020_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8261_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6021_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8263_q;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6246_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8257_q) 
           - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8047_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o 
        = (((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8476_q)) 
            << 2U) | (((3U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8476_q)) 
                       << 1U) | (2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8476_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8159_o 
        = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8158_q) 
            << 0xeU) | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8154_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2269_o 
        = (1U & ((~ (((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q)) 
                      & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2266_o)) 
                     & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q)))) 
                 & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2440_o 
        = (1U & ((~ (((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q)) 
                      & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2437_o)) 
                     & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q)))) 
                 & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2354_o 
        = (1U & ((~ (((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q)) 
                      & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2351_o)) 
                     & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q)))) 
                 & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2524_o 
        = (1U & ((~ (((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q)) 
                      & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2521_o)) 
                     & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q)))) 
                 & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2777_o 
        = ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2763_o)) 
           & VL_GTS_III(1,32,32, 0x2000U, (0x3fffU 
                                           & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2735_o)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7180_o 
        = (0x3ffU & ((IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8514_q 
                              >> 0x14U)) + (IData)(
                                                   (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8514_q 
                                                    >> 0x32U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7162_o 
        = (0x3ffU & ((IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8514_q 
                              >> 0xaU)) + (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8514_q 
                                                   >> 0x28U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7142_o 
        = (0x3ffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8514_q) 
                     + (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8514_q 
                                >> 0x1eU))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7358_o 
        = (0x7ffffU & (((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8554_q[2U] 
                         << 2U) | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8554_q[1U] 
                                   >> 0x1eU)) + ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8554_q[3U] 
                                                  << 7U) 
                                                 | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8554_q[2U] 
                                                    >> 0x19U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7340_o 
        = (0x7ffffU & (((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8554_q[4U] 
                         << 0xcU) | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8554_q[3U] 
                                     >> 0x14U)) + (
                                                   (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8554_q[5U] 
                                                    << 0x11U) 
                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8554_q[4U] 
                                                      >> 0xfU))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7321_o 
        = (0x7ffffU & (((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8554_q[1U] 
                         << 0x18U) | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8554_q[0U] 
                                      >> 8U)) + ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8554_q[2U] 
                                                  << 0x1dU) 
                                                 | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8554_q[1U] 
                                                    >> 3U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9906_o 
        = ((0x80U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
            ? ((0x40U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                ? ((0x20U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                    ? ((0x10U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9896_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9894_o)
                    : ((0x10U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9892_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9890_o))
                : ((0x20U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                    ? ((0x10U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9888_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9886_o)
                    : ((0x10U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9884_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9882_o)))
            : ((0x40U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                ? ((0x20U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                    ? ((0x10U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9880_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9878_o)
                    : ((0x10U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9876_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9874_o))
                : ((0x20U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                    ? ((0x10U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9872_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9870_o)
                    : ((0x10U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q)))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9868_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9866_o))));
    if ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3573_o))) {
        __Vtemp61[0U] = ((0U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q)))
                          ? ((0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U] 
                                             << 0x10U)) 
                             | (0xffffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U]))
                          : ((0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[0U] 
                                             << 0x10U)) 
                             | (0xffffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U])));
        __Vtemp61[1U] = ((0U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q)))
                          ? ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U] 
                                         >> 0x10U)) 
                             | (0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[1U] 
                                               << 0x10U)))
                          : ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[0U] 
                                         >> 0x10U)) 
                             | (0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[1U] 
                                               << 0x10U))));
        __Vtemp61[2U] = ((0U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q)))
                          ? ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[1U] 
                                         >> 0x10U)) 
                             | (0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[2U] 
                                               << 0x10U)))
                          : ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[1U] 
                                         >> 0x10U)) 
                             | (0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[2U] 
                                               << 0x10U))));
        __Vtemp61[3U] = ((0U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q)))
                          ? ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[2U] 
                                         >> 0x10U)) 
                             | (0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[3U] 
                                               << 0x10U)))
                          : ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[2U] 
                                         >> 0x10U)) 
                             | (0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[3U] 
                                               << 0x10U))));
    } else {
        __Vtemp61[0U] = ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3573_o))
                          ? ((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q))
                              ? ((0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U] 
                                                 << 0x10U)) 
                                 | (0xffffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U]))
                              : ((0xffffff00U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[0U] 
                                                 << 8U)) 
                                 | (0xffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U])))
                          : ((0U == (3U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q)))
                              ? ((0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U] 
                                                 << 0x10U)) 
                                 | (0xffffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U]))
                              : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U]));
        __Vtemp61[1U] = ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3573_o))
                          ? ((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q))
                              ? ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U] 
                                             >> 0x10U)) 
                                 | (0xffff0000U & (
                                                   vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[1U] 
                                                   << 0x10U)))
                              : ((0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[0U] 
                                           >> 0x18U)) 
                                 | (0xffffff00U & (
                                                   vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[1U] 
                                                   << 8U))))
                          : ((0U == (3U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q)))
                              ? ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U] 
                                             >> 0x10U)) 
                                 | (0xffff0000U & (
                                                   vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[1U] 
                                                   << 0x10U)))
                              : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[0U]));
        __Vtemp61[2U] = ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3573_o))
                          ? ((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q))
                              ? ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[1U] 
                                             >> 0x10U)) 
                                 | (0xffff0000U & (
                                                   vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[2U] 
                                                   << 0x10U)))
                              : ((0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[1U] 
                                           >> 0x18U)) 
                                 | (0xffffff00U & (
                                                   vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[2U] 
                                                   << 8U))))
                          : ((0U == (3U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q)))
                              ? ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[1U] 
                                             >> 0x10U)) 
                                 | (0xffff0000U & (
                                                   vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[2U] 
                                                   << 0x10U)))
                              : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[1U]));
        __Vtemp61[3U] = ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3573_o))
                          ? ((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q))
                              ? ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[2U] 
                                             >> 0x10U)) 
                                 | (0xffff0000U & (
                                                   vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[3U] 
                                                   << 0x10U)))
                              : ((0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[2U] 
                                           >> 0x18U)) 
                                 | (0xffffff00U & (
                                                   vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[3U] 
                                                   << 8U))))
                          : ((0U == (3U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q)))
                              ? ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[2U] 
                                             >> 0x10U)) 
                                 | (0xffff0000U & (
                                                   vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[3U] 
                                                   << 0x10U)))
                              : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[2U]));
    }
    if ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3573_o))) {
        __Vtemp63[4U] = ((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q))
                          ? (0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[3U] 
                                        >> 0x10U)) : 
                         ((5U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q))
                           ? ((0xff00U & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[4U] 
                                           << 0x18U) 
                                          | (0xffff00U 
                                             & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[3U] 
                                                >> 8U)))) 
                              | (0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[3U] 
                                          >> 0x18U)))
                           : ((0xaU == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q))
                               ? (0xffffU & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[4U] 
                                              << 0x18U) 
                                             | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[3U] 
                                                >> 8U)))
                               : (0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[3U] 
                                             >> 8U)))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[0U] 
            = ((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q))
                ? ((0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U] 
                                   << 0x10U)) | (0xffffU 
                                                 & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U]))
                : ((5U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q))
                    ? ((0xffffff00U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U] 
                                       << 8U)) | (0xffU 
                                                  & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U]))
                    : ((0xaU == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U]
                        : ((0xff000000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[0U] 
                                           << 0x18U)) 
                           | (0xffffffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U])))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[1U] 
            = ((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q))
                ? ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U] 
                               >> 0x10U)) | (0xffff0000U 
                                             & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[1U] 
                                                << 0x10U)))
                : ((5U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q))
                    ? ((0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[0U] 
                                 >> 0x18U)) | (0xffffff00U 
                                               & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[1U] 
                                                  << 8U)))
                    : ((0xaU == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[1U]
                        : ((0xffffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[0U] 
                                         >> 8U)) | 
                           (0xff000000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[1U] 
                                           << 0x18U))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[2U] 
            = ((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q))
                ? ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[1U] 
                               >> 0x10U)) | (0xffff0000U 
                                             & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[2U] 
                                                << 0x10U)))
                : ((5U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q))
                    ? ((0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[1U] 
                                 >> 0x18U)) | (0xffffff00U 
                                               & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[2U] 
                                                  << 8U)))
                    : ((0xaU == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[2U]
                        : ((0xffffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[1U] 
                                         >> 8U)) | 
                           (0xff000000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[2U] 
                                           << 0x18U))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[3U] 
            = ((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q))
                ? ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[2U] 
                               >> 0x10U)) | (0xffff0000U 
                                             & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[3U] 
                                                << 0x10U)))
                : ((5U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q))
                    ? ((0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[2U] 
                                 >> 0x18U)) | (0xffffff00U 
                                               & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[3U] 
                                                  << 8U)))
                    : ((0xaU == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[3U]
                        : ((0xffffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[2U] 
                                         >> 8U)) | 
                           (0xff000000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[3U] 
                                           << 0x18U))))));
    } else {
        __Vtemp63[4U] = ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3573_o))
                          ? ((0U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q)))
                              ? (0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[3U] 
                                            >> 0x10U))
                              : (0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[3U] 
                                            >> 0x10U)))
                          : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3573_o))
                              ? ((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q))
                                  ? (0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[3U] 
                                                >> 0x10U))
                                  : ((0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[3U] 
                                               >> 0x18U)) 
                                     | (0xff00U & (
                                                   vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[4U] 
                                                   << 8U))))
                              : ((0U == (3U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q)))
                                  ? (0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8596_data[3U] 
                                                >> 0x10U))
                                  : (0xffffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[3U]))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[0U] 
            = __Vtemp61[0U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[1U] 
            = __Vtemp61[1U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[2U] 
            = __Vtemp61[2U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[3U] 
            = __Vtemp61[3U];
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
        = __Vtemp63[4U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3412_o 
        = ((((~ ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8400_q) 
                 >> 2U)) & (0U == (0x7fU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8181_q)))) 
            | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8369_q)) 
           & (((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3400_o))
                ? (((0U == (0xfU & ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q)))) 
                    | (5U == (0xfU & ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q))))) 
                   | (0xaU == (0xfU & ((IData)(1U) 
                                       + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q)))))
                : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3400_o))
                    ? (0U == (7U & ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q))))
                    : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3400_o))
                        ? (0U == (0xfU & ((IData)(1U) 
                                          + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q))))
                        : (0U == (3U & ((IData)(1U) 
                                        + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q))))))) 
              & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8193_q)));
    vlTOPp->synth_top__DOT__ddr__DOT__cnt = __Vdly__synth_top__DOT__ddr__DOT__cnt;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8547_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4231_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8082_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8081_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6253_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8257_q) 
           - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8039_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8079_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8078_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8056_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8055_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6172_o 
        = (((VL_LTS_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8257_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8036_q)) 
             & VL_GTES_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8257_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8033_q))) 
            << 0xbU) | ((0x400U & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8307_q) 
                                   >> 1U)) | ((0x7ffffe00U 
                                               & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8000_q) 
                                                   << 9U) 
                                                  & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8307_q) 
                                                     >> 1U))) 
                                              | (0x1ffU 
                                                 & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8307_q) 
                                                    >> 1U)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2682_o 
        = (IData)((0x800U == (0xc00U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8307_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2407_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8112_q) 
           & (IData)((0x400U == (0xc00U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8309_q)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2602_o 
        = ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8103_q)) 
           & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8100_q) 
              & (IData)((0x400U == (0xc00U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8309_q))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2612_o 
        = ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8109_q)) 
           & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8106_q) 
              & (IData)((0x400U == (0xc00U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8309_q))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2491_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8115_q) 
           & (IData)((0x400U == (0xc00U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8309_q)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8410_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5726_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8388_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8387_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8500_q 
        = ((((0x200U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5499_o))
              ? 0U : ((0U != (3U & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5499_o) 
                                    >> 8U))) ? 0xffU
                       : (0xffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5499_o)))) 
            << 0x10U) | ((((0x200U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5481_o))
                            ? 0U : ((0U != (3U & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5481_o) 
                                                  >> 8U)))
                                     ? 0xffU : (0xffU 
                                                & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5481_o)))) 
                          << 8U) | ((0x200U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5461_o))
                                     ? 0U : ((0U != 
                                              (3U & 
                                               ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5461_o) 
                                                >> 8U)))
                                              ? 0xffU
                                              : (0xffU 
                                                 & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5461_o))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8543_q 
        = ((((0x40000U & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5680_o)
              ? 0U : ((0U != (0xfU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5680_o 
                                      >> 0xfU))) ? 0xffU
                       : (0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5680_o 
                                   >> 7U)))) << 0x10U) 
           | ((((0x40000U & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5662_o)
                 ? 0U : ((0U != (0xfU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5662_o 
                                         >> 0xfU)))
                          ? 0xffU : (0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5662_o 
                                              >> 7U)))) 
               << 8U) | ((0x40000U & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5643_o)
                          ? 0U : ((0U != (0xfU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5643_o 
                                                  >> 0xfU)))
                                   ? 0xffU : (0xffU 
                                              & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5643_o 
                                                 >> 7U))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8485_q 
        = ((((1U & (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8488_q 
                            >> 0x32U))) ? 0U : ((1U 
                                                 & (IData)(
                                                           (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8488_q 
                                                            >> 0x32U)))
                                                 ? 0xffU
                                                 : 
                                                (0xffU 
                                                 & (IData)(
                                                           (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8488_q 
                                                            >> 0x2aU))))) 
            << 0x10U) | ((((1U & (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8488_q 
                                          >> 0x21U)))
                            ? 0U : ((1U & (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8488_q 
                                                   >> 0x21U)))
                                     ? 0xffU : (0xffU 
                                                & (IData)(
                                                          (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8488_q 
                                                           >> 0x19U))))) 
                          << 8U) | ((1U & (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8488_q 
                                                   >> 0x10U)))
                                     ? 0U : ((1U & (IData)(
                                                           (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8488_q 
                                                            >> 0x10U)))
                                              ? 0xffU
                                              : (0xffU 
                                                 & (IData)(
                                                           (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8488_q 
                                                            >> 8U)))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8539_q[0U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4315_o[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8539_q[1U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4315_o[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8539_q[2U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4315_o[2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8528_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8527_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8065_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8064_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8085_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8084_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8083_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6190_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8094_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8093_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8059_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8058_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8266_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8265_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6178_o 
        = (((VL_LTES_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8259_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8091_q)) 
             & (VL_GTES_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8259_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8088_q)) 
                & (VL_LTES_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8257_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8042_q)) 
                   & VL_GTES_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8257_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8039_q))))) 
            << 0xbU) | ((0x400U & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8313_q) 
                                   >> 1U)) | ((0x7ffffe00U 
                                               & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8000_q) 
                                                   << 9U) 
                                                  & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8313_q) 
                                                     >> 1U))) 
                                              | (0x1ffU 
                                                 & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8313_q) 
                                                    >> 1U)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8490_q 
        = (((QData)((IData)((0x1ffffU & (((0xffU & 
                                           ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                             << 0x18U) 
                                            | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                               >> 8U))) 
                                          * (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6429_o)) 
                                         + ((0xffU 
                                             & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U]) 
                                            * (0x1ffU 
                                               & ((IData)(0x100U) 
                                                  - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6429_o)))))))) 
            << 0x22U) | (((QData)((IData)((0x1ffffU 
                                           & (((0xffU 
                                                & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U]) 
                                               * (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6429_o)) 
                                              + ((0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                      << 8U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                        >> 0x18U))) 
                                                 * 
                                                 (0x1ffU 
                                                  & ((IData)(0x100U) 
                                                     - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6429_o)))))))) 
                          << 0x11U) | (QData)((IData)(
                                                      (0x1ffffU 
                                                       & (((0xffU 
                                                            & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                                << 8U) 
                                                               | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                                  >> 0x18U))) 
                                                           * (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6429_o)) 
                                                          + 
                                                          ((0xffU 
                                                            & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                                << 0x10U) 
                                                               | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                                  >> 0x10U))) 
                                                           * 
                                                           (0x1ffU 
                                                            & ((IData)(0x100U) 
                                                               - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6429_o))))))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8522_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8521_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3626_o 
        = ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3625_o))
            ? ((0xff0000U & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                              << 0x18U) | (0xff0000U 
                                           & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[3U] 
                                              >> 8U)))) 
               | ((0xff00U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                              << 8U)) | (0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                                                  >> 8U))))
            : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3625_o))
                ? (((0xf80000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                                  << 0x11U)) | (0x70000U 
                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                                                   << 0xcU))) 
                   | ((0xc000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                                  << 0xeU)) | ((0x3800U 
                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                                                   >> 2U)) 
                                               | ((0x600U 
                                                   & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                                                      << 9U)) 
                                                  | ((0x100U 
                                                      & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                                                         >> 7U)) 
                                                     | ((0xf8U 
                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                                                            >> 5U)) 
                                                        | (7U 
                                                           & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                                                              >> 0xaU))))))))
                : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3625_o))
                    ? (((0xf80000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                                      << 0x10U)) | 
                        (0x70000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                                     << 0xbU))) | (
                                                   (0xe000U 
                                                    & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                                                       << 0xdU)) 
                                                   | ((0x1c00U 
                                                       & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                                                          >> 3U)) 
                                                      | ((0x300U 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                                                             << 7U)) 
                                                         | ((0xf8U 
                                                             & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                                                                >> 5U)) 
                                                            | (7U 
                                                               & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                                                                  >> 0xaU)))))))
                    : ((0xff0000U & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                                      << 0x18U) | (0xff0000U 
                                                   & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[3U] 
                                                      >> 8U)))) 
                       | ((0xff00U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                                      << 8U)) | (0xffU 
                                                 & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U] 
                                                    >> 8U)))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4620_o 
        = (0x1fffffU & ((1U & (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8454_q 
                                       >> 0x14U))) ? 
                        ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8454_q) 
                         + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q) 
                            << 2U)) : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8454_q) 
                                       - ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q) 
                                          << 2U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4500_o 
        = (0x1fffffU & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8290_q) 
                         << 8U) - ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q) 
                                   << 8U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4540_o 
        = (0x1fffffU & ((1U & (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8454_q 
                                       >> 0x3eU))) ? 
                        ((IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8454_q 
                                  >> 0x2aU)) + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q) 
                                                << 6U))
                         : ((IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8454_q 
                                     >> 0x2aU)) - ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q) 
                                                   << 6U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4580_o 
        = (0x1fffffU & ((1U & (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8454_q 
                                       >> 0x29U))) ? 
                        ((IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8454_q 
                                  >> 0x15U)) + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q) 
                                                << 4U))
                         : ((IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8454_q 
                                     >> 0x15U)) - ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q) 
                                                   << 4U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3212_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8296_q) 
           - ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q) 
              << 1U));
    vlTOPp->synth_top__DOT__bridge__DOT__wr_go = ((
                                                   (1U 
                                                    == (IData)(vlTOPp->synth_top__DOT__bridge__DOT__state)) 
                                                   & (IData)(vlTOPp->synth_top__DOT__ddr__DOT__rdy)) 
                                                  & (IData)(vlTOPp->synth_top__DOT__ddr__DOT__rdy));
    vlTOPp->synth_top__DOT__bridge__DOT__rd_go = ((2U 
                                                   == (IData)(vlTOPp->synth_top__DOT__bridge__DOT__state)) 
                                                  & (IData)(vlTOPp->synth_top__DOT__ddr__DOT__rdy));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5499_o 
        = (0x3ffU & ((IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8512_q 
                              >> 0x14U)) + (IData)(
                                                   (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8512_q 
                                                    >> 0x32U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5481_o 
        = (0x3ffU & ((IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8512_q 
                              >> 0xaU)) + (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8512_q 
                                                   >> 0x28U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5461_o 
        = (0x3ffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8512_q) 
                     + (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8512_q 
                                >> 0x1eU))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5680_o 
        = (0x7ffffU & (((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8551_q[2U] 
                         << 2U) | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8551_q[1U] 
                                   >> 0x1eU)) + ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8551_q[3U] 
                                                  << 7U) 
                                                 | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8551_q[2U] 
                                                    >> 0x19U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5662_o 
        = (0x7ffffU & (((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8551_q[4U] 
                         << 0xcU) | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8551_q[3U] 
                                     >> 0x14U)) + (
                                                   (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8551_q[5U] 
                                                    << 0x11U) 
                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8551_q[4U] 
                                                      >> 0xfU))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5643_o 
        = (0x7ffffU & (((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8551_q[1U] 
                         << 0x18U) | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8551_q[0U] 
                                      >> 8U)) + ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8551_q[2U] 
                                                  << 0x1dU) 
                                                 | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8551_q[1U] 
                                                    >> 3U))));
    __Vtemp64[0U] = (IData)((((QData)((IData)((0x3ffffU 
                                               & (((((0xffc00U 
                                                      & ((- (IData)(
                                                                    (1U 
                                                                     & (IData)(
                                                                               (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8531_q 
                                                                                >> 0x1dU))))) 
                                                         << 0xaU)) 
                                                     | (0x3ffU 
                                                        & (IData)(
                                                                  (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8531_q 
                                                                   >> 0x14U)))) 
                                                    * 
                                                    ((0xffc00U 
                                                      & ((- (IData)(
                                                                    (1U 
                                                                     & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8549_q) 
                                                                        >> 9U)))) 
                                                         << 0xaU)) 
                                                     | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8549_q))) 
                                                   + 
                                                   (((0xffc00U 
                                                      & ((- (IData)(
                                                                    (1U 
                                                                     & (IData)(
                                                                               (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8534_q 
                                                                                >> 0x1dU))))) 
                                                         << 0xaU)) 
                                                     | (0x3ffU 
                                                        & (IData)(
                                                                  (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8534_q 
                                                                   >> 0x14U)))) 
                                                    * 
                                                    ((0xffc00U 
                                                      & ((- (IData)(
                                                                    (1U 
                                                                     & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8550_q) 
                                                                        >> 9U)))) 
                                                         << 0xaU)) 
                                                     | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8550_q)))) 
                                                  >> 1U)))) 
                              << 0x24U) | (((QData)((IData)(
                                                            (0x3ffffU 
                                                             & (((((0xffc00U 
                                                                    & ((- (IData)(
                                                                                (1U 
                                                                                & (IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8531_q 
                                                                                >> 0x13U))))) 
                                                                       << 0xaU)) 
                                                                   | (0x3ffU 
                                                                      & (IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8531_q 
                                                                                >> 0xaU)))) 
                                                                  * 
                                                                  ((0xffc00U 
                                                                    & ((- (IData)(
                                                                                (1U 
                                                                                & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8549_q) 
                                                                                >> 9U)))) 
                                                                       << 0xaU)) 
                                                                   | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8549_q))) 
                                                                 + 
                                                                 (((0xffc00U 
                                                                    & ((- (IData)(
                                                                                (1U 
                                                                                & (IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8534_q 
                                                                                >> 0x13U))))) 
                                                                       << 0xaU)) 
                                                                   | (0x3ffU 
                                                                      & (IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8534_q 
                                                                                >> 0xaU)))) 
                                                                  * 
                                                                  ((0xffc00U 
                                                                    & ((- (IData)(
                                                                                (1U 
                                                                                & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8550_q) 
                                                                                >> 9U)))) 
                                                                       << 0xaU)) 
                                                                   | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8550_q)))) 
                                                                >> 1U)))) 
                                            << 0x12U) 
                                           | (QData)((IData)(
                                                             (0x3ffffU 
                                                              & (((((0xffc00U 
                                                                     & ((- (IData)(
                                                                                (1U 
                                                                                & (IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8531_q 
                                                                                >> 9U))))) 
                                                                        << 0xaU)) 
                                                                    | (0x3ffU 
                                                                       & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8531_q))) 
                                                                   * 
                                                                   ((0xffc00U 
                                                                     & ((- (IData)(
                                                                                (1U 
                                                                                & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8549_q) 
                                                                                >> 9U)))) 
                                                                        << 0xaU)) 
                                                                    | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8549_q))) 
                                                                  + 
                                                                  (((0xffc00U 
                                                                     & ((- (IData)(
                                                                                (1U 
                                                                                & (IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8534_q 
                                                                                >> 9U))))) 
                                                                        << 0xaU)) 
                                                                    | (0x3ffU 
                                                                       & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8534_q))) 
                                                                   * 
                                                                   ((0xffc00U 
                                                                     & ((- (IData)(
                                                                                (1U 
                                                                                & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8550_q) 
                                                                                >> 9U)))) 
                                                                        << 0xaU)) 
                                                                    | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8550_q)))) 
                                                                 >> 1U)))))));
    __Vtemp64[1U] = ((0xffc00000U & (((((0xffc00U & 
                                         ((- (IData)(
                                                     (1U 
                                                      & (IData)(
                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8531_q 
                                                                 >> 0x27U))))) 
                                          << 0xaU)) 
                                        | (0x3ffU & (IData)(
                                                            (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8531_q 
                                                             >> 0x1eU)))) 
                                       * ((0xffc00U 
                                           & ((- (IData)(
                                                         (1U 
                                                          & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8549_q) 
                                                             >> 9U)))) 
                                              << 0xaU)) 
                                          | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8549_q))) 
                                      + (((0xffc00U 
                                           & ((- (IData)(
                                                         (1U 
                                                          & (IData)(
                                                                    (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8534_q 
                                                                     >> 0x27U))))) 
                                              << 0xaU)) 
                                          | (0x3ffU 
                                             & (IData)(
                                                       (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8534_q 
                                                        >> 0x1eU)))) 
                                         * ((0xffc00U 
                                             & ((- (IData)(
                                                           (1U 
                                                            & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8550_q) 
                                                               >> 9U)))) 
                                                << 0xaU)) 
                                            | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8550_q)))) 
                                     << 0x15U)) | (IData)(
                                                          ((((QData)((IData)(
                                                                             (0x3ffffU 
                                                                              & (((((0xffc00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8531_q 
                                                                                >> 0x1dU))))) 
                                                                                << 0xaU)) 
                                                                                | (0x3ffU 
                                                                                & (IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8531_q 
                                                                                >> 0x14U)))) 
                                                                                * 
                                                                                ((0xffc00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8549_q) 
                                                                                >> 9U)))) 
                                                                                << 0xaU)) 
                                                                                | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8549_q))) 
                                                                                + 
                                                                                (((0xffc00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8534_q 
                                                                                >> 0x1dU))))) 
                                                                                << 0xaU)) 
                                                                                | (0x3ffU 
                                                                                & (IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8534_q 
                                                                                >> 0x14U)))) 
                                                                                * 
                                                                                ((0xffc00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8550_q) 
                                                                                >> 9U)))) 
                                                                                << 0xaU)) 
                                                                                | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8550_q)))) 
                                                                                >> 1U)))) 
                                                             << 0x24U) 
                                                            | (((QData)((IData)(
                                                                                (0x3ffffU 
                                                                                & (((((0xffc00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8531_q 
                                                                                >> 0x13U))))) 
                                                                                << 0xaU)) 
                                                                                | (0x3ffU 
                                                                                & (IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8531_q 
                                                                                >> 0xaU)))) 
                                                                                * 
                                                                                ((0xffc00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8549_q) 
                                                                                >> 9U)))) 
                                                                                << 0xaU)) 
                                                                                | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8549_q))) 
                                                                                + 
                                                                                (((0xffc00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8534_q 
                                                                                >> 0x13U))))) 
                                                                                << 0xaU)) 
                                                                                | (0x3ffU 
                                                                                & (IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8534_q 
                                                                                >> 0xaU)))) 
                                                                                * 
                                                                                ((0xffc00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8550_q) 
                                                                                >> 9U)))) 
                                                                                << 0xaU)) 
                                                                                | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8550_q)))) 
                                                                                >> 1U)))) 
                                                                << 0x12U) 
                                                               | (QData)((IData)(
                                                                                (0x3ffffU 
                                                                                & (((((0xffc00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8531_q 
                                                                                >> 9U))))) 
                                                                                << 0xaU)) 
                                                                                | (0x3ffU 
                                                                                & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8531_q))) 
                                                                                * 
                                                                                ((0xffc00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8549_q) 
                                                                                >> 9U)))) 
                                                                                << 0xaU)) 
                                                                                | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8549_q))) 
                                                                                + 
                                                                                (((0xffc00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (IData)(
                                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8534_q 
                                                                                >> 9U))))) 
                                                                                << 0xaU)) 
                                                                                | (0x3ffU 
                                                                                & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8534_q))) 
                                                                                * 
                                                                                ((0xffc00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8550_q) 
                                                                                >> 9U)))) 
                                                                                << 0xaU)) 
                                                                                | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8550_q)))) 
                                                                                >> 1U)))))) 
                                                           >> 0x20U)));
    __Vtemp64[2U] = (0xffU & (((((0xffc00U & ((- (IData)(
                                                         (1U 
                                                          & (IData)(
                                                                    (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8531_q 
                                                                     >> 0x27U))))) 
                                              << 0xaU)) 
                                 | (0x3ffU & (IData)(
                                                     (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8531_q 
                                                      >> 0x1eU)))) 
                                * ((0xffc00U & ((- (IData)(
                                                           (1U 
                                                            & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8549_q) 
                                                               >> 9U)))) 
                                                << 0xaU)) 
                                   | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8549_q))) 
                               + (((0xffc00U & ((- (IData)(
                                                           (1U 
                                                            & (IData)(
                                                                      (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8534_q 
                                                                       >> 0x27U))))) 
                                                << 0xaU)) 
                                   | (0x3ffU & (IData)(
                                                       (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8534_q 
                                                        >> 0x1eU)))) 
                                  * ((0xffc00U & ((- (IData)(
                                                             (1U 
                                                              & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8550_q) 
                                                                 >> 9U)))) 
                                                  << 0xaU)) 
                                     | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8550_q)))) 
                              >> 0xbU));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4315_o[0U] 
        = __Vtemp64[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4315_o[1U] 
        = __Vtemp64[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4315_o[2U] 
        = __Vtemp64[2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6429_o 
        = (0x1ffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8484_q) 
                     + (1U & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8484_q) 
                              >> 7U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4519_o 
        = (0x1fffffU & ((0x100000U & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4500_o)
                         ? (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4500_o 
                            + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q) 
                               << 7U)) : (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4500_o 
                                          - ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q) 
                                             << 7U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4559_o 
        = (0x1fffffU & ((0x100000U & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4540_o)
                         ? (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4540_o 
                            + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q) 
                               << 5U)) : (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4540_o 
                                          - ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q) 
                                             << 5U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4599_o 
        = (0x1fffffU & ((0x100000U & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4580_o)
                         ? (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4580_o 
                            + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q) 
                               << 3U)) : (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4580_o 
                                          - ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q) 
                                             << 3U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3252_o 
        = ((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8357_q)) 
           & VL_GTS_III(1,32,32, 0x4000U, (0x7fffU 
                                           & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3212_o)));
    vlTOPp->synth_top__DOT__app_en = ((IData)(vlTOPp->synth_top__DOT__bridge__DOT__wr_go) 
                                      | (IData)(vlTOPp->synth_top__DOT__bridge__DOT__rd_go));
    vlTOPp->synth_top__DOT__avl_waitrequest = (1U & 
                                               (~ ((IData)(vlTOPp->synth_top__DOT__bridge__DOT__wr_go) 
                                                   | ((IData)(vlTOPp->synth_top__DOT__bridge__DOT__rd_go) 
                                                      & (0U 
                                                         == (IData)(vlTOPp->synth_top__DOT__bridge__DOT__beat))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4231_o 
        = (0xffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8557_q)
                     ? (((0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8546_q 
                                   >> 0x10U)) > (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4204_o))
                         ? (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8546_q 
                            >> 0x10U) : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4204_o))
                     : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8558_q)
                         ? (((0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8544_q 
                                       >> 0x10U)) > (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4221_o))
                             ? (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8544_q 
                                >> 0x10U) : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4221_o))
                         : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8547_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8078_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6192_o;
    vlTOPp->dbg_o_dcpt = (0xfffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8410_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5726_o 
        = ((((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8417_q))
              ? 0U : (0xfffU & ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8418_q))
                                 ? ((IData)(1U) + (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8410_q 
                                                   >> 0xcU))
                                 : (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8410_q 
                                    >> 0xcU)))) << 0xcU) 
           | (0xfffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8410_q 
                        >> 0xcU)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8488_q 
        = (((QData)((IData)((0x1ffffU & (((0xffU & 
                                           ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[2U] 
                                             << 0x18U) 
                                            | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[1U] 
                                               >> 8U))) 
                                          * (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4741_o)) 
                                         + ((0xffU 
                                             & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[2U]) 
                                            * (0x1ffU 
                                               & ((IData)(0x100U) 
                                                  - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4741_o)))))))) 
            << 0x22U) | (((QData)((IData)((0x1ffffU 
                                           & (((0xffU 
                                                & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[1U]) 
                                               * (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4741_o)) 
                                              + ((0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[2U] 
                                                      << 8U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[1U] 
                                                        >> 0x18U))) 
                                                 * 
                                                 (0x1ffU 
                                                  & ((IData)(0x100U) 
                                                     - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4741_o)))))))) 
                          << 0x11U) | (QData)((IData)(
                                                      (0x1ffffU 
                                                       & (((0xffU 
                                                            & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[1U] 
                                                                << 8U) 
                                                               | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0U] 
                                                                  >> 0x18U))) 
                                                           * (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4741_o)) 
                                                          + 
                                                          ((0xffU 
                                                            & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[2U] 
                                                                << 0x10U) 
                                                               | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[1U] 
                                                                  >> 0x10U))) 
                                                           * 
                                                           (0x1ffU 
                                                            & ((IData)(0x100U) 
                                                               - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4741_o))))))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8527_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8526_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8084_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8071_q)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8077_q)
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8085_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6176_o 
        = (((VL_LTS_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8259_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8094_q)) 
             & VL_LTS_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8257_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8045_q))) 
            << 0xbU) | ((0x400U & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8311_q) 
                                   >> 1U)) | ((0x7ffffe00U 
                                               & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8000_q) 
                                                   << 9U) 
                                                  & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8311_q) 
                                                     >> 1U))) 
                                              | (0x1ffU 
                                                 & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8311_q) 
                                                    >> 1U)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6174_o 
        = (((((VL_GTES_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8257_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8033_q)) 
               & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8259_q) 
                  == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8059_q))) 
              | (VL_LTS_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8259_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8062_q)) 
                 & VL_GTS_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8259_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8059_q)))) 
             | (VL_LTS_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8257_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8033_q)) 
                & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8259_q) 
                   == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8062_q)))) 
            << 0xbU) | ((0x400U & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8309_q) 
                                   >> 1U)) | ((0x7ffffe00U 
                                               & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8000_q) 
                                                   << 9U) 
                                                  & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8309_q) 
                                                     >> 1U))) 
                                              | (0x1ffU 
                                                 & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8309_q) 
                                                    >> 1U)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8265_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6023_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8443_q[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8443_q[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8443_q[2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8521_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8520_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5734_o 
        = (((QData)((IData)(((0x800U & ((~ (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4500_o 
                                            >> 0x14U)) 
                                        << 0xbU)) | 
                             (0x400U & ((~ (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4519_o 
                                            >> 0x14U)) 
                                        << 0xaU))))) 
            << 0x18U) | (QData)((IData)(((0xc00000U 
                                          & ((IData)(
                                                     (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8455_q 
                                                      >> 0x22U)) 
                                             << 0x16U)) 
                                         | ((0x200000U 
                                             & ((~ 
                                                 (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4540_o 
                                                  >> 0x14U)) 
                                                << 0x15U)) 
                                            | ((0x100000U 
                                                & ((~ 
                                                    (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4559_o 
                                                     >> 0x14U)) 
                                                   << 0x14U)) 
                                               | ((0xff000U 
                                                   & ((IData)(
                                                              (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8455_q 
                                                               >> 0x18U)) 
                                                      << 0xcU)) 
                                                  | ((0xf00U 
                                                      & ((IData)(
                                                                 (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8455_q 
                                                                  >> 0x14U)) 
                                                         << 8U)) 
                                                     | ((0x80U 
                                                         & ((~ 
                                                             (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4580_o 
                                                              >> 0x14U)) 
                                                            << 7U)) 
                                                        | ((0x40U 
                                                            & ((~ 
                                                                (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4599_o 
                                                                 >> 0x14U)) 
                                                               << 6U)) 
                                                           | (0x3fU 
                                                              & (IData)(
                                                                        (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8455_q 
                                                                         >> 0xcU)))))))))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3277_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3252_o) 
           | VL_LTS_III(1,32,32, 0U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8357_q)));
    if (((~ (IData)(vlTOPp->synth_top__DOT__avl_waitrequest)) 
         & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7912_q))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2129_o 
            = (0xffU & ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7944_q)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1956_o = 1U;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2129_o 
            = (0xffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7944_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1956_o = 0U;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1979_o 
        = ((~ (IData)(vlTOPp->synth_top__DOT__avl_waitrequest)) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7921_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4741_o 
        = (0x1ffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8482_q) 
                     + (1U & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8482_q) 
                              >> 7U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6192_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8071_q)
            ? 0U : (0xfffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5986_o)
                               ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8078_q)
                               : ((0xfffU != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8078_q))
                                   ? ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8078_q))
                                   : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8078_q)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[1U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[2U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[3U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[3U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[4U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[4U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[5U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[5U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[6U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[7U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[8U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[9U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[9U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0xaU] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0xaU];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0xbU] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0xbU];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0xcU] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0xcU];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0xdU] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0xdU];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0xeU] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0xeU];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0xfU] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0xfU];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0x10U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0x10U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0x11U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0x11U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0x12U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0x12U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0x13U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0x13U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0x14U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0x14U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8526_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8525_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6022_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5986_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8263_q)
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8265_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6004_o 
        = VL_GTES_III(1,32,32, ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8265_q)), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8056_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2685_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8265_q) 
           == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8088_q));
    __Vtemp65[0U] = (IData)((((QData)((IData)((0x7ffffffU 
                                               & ((((0x7fc0000U 
                                                     & ((- (IData)(
                                                                   (1U 
                                                                    & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                                       >> 0x15U)))) 
                                                        << 0x12U)) 
                                                    | (0x3ffffU 
                                                       & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[2U] 
                                                           << 0x1cU) 
                                                          | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                             >> 4U)))) 
                                                   * 
                                                   (0xffU 
                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                        << 8U) 
                                                       | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                          >> 0x18U)))) 
                                                  + 
                                                  (((0x7fc0000U 
                                                     & ((- (IData)(
                                                                   (1U 
                                                                    & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[2U] 
                                                                       >> 7U)))) 
                                                        << 0x12U)) 
                                                    | (0x3ffffU 
                                                       & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[2U] 
                                                           << 0xaU) 
                                                          | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                             >> 0x16U)))) 
                                                   * 
                                                   (0xffU 
                                                    & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U])))))) 
                              << 0x1bU) | (QData)((IData)(
                                                          (0x7ffffffU 
                                                           & ((((0x7fc0000U 
                                                                 & ((- (IData)(
                                                                               (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[0U] 
                                                                                >> 0x11U)))) 
                                                                    << 0x12U)) 
                                                                | (0x3ffffU 
                                                                   & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[0U])) 
                                                               * 
                                                               (0xffU 
                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                                   >> 8U))) 
                                                              + 
                                                              (((0x7fc0000U 
                                                                 & ((- (IData)(
                                                                               (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                                                >> 3U)))) 
                                                                    << 0x12U)) 
                                                                | (0x3ffffU 
                                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                                       << 0xeU) 
                                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[0U] 
                                                                         >> 0x12U)))) 
                                                               * 
                                                               (0xffU 
                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                                    << 0x10U) 
                                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                                      >> 0x10U))))))))));
    __Vtemp65[1U] = ((0xffc00000U & (((((0x7fc0000U 
                                         & ((- (IData)(
                                                       (1U 
                                                        & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[0U] 
                                                           >> 0x11U)))) 
                                            << 0x12U)) 
                                        | (0x3ffffU 
                                           & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[0U])) 
                                       * (0xffU & (
                                                   vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                   >> 0x18U))) 
                                      + (((0x7fc0000U 
                                           & ((- (IData)(
                                                         (1U 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                             >> 3U)))) 
                                              << 0x12U)) 
                                          | (0x3ffffU 
                                             & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                 << 0xeU) 
                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[0U] 
                                                   >> 0x12U)))) 
                                         * (0xffU & 
                                            vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U]))) 
                                     << 0x16U)) | (IData)(
                                                          ((((QData)((IData)(
                                                                             (0x7ffffffU 
                                                                              & ((((0x7fc0000U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                                                >> 0x15U)))) 
                                                                                << 0x12U)) 
                                                                                | (0x3ffffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[2U] 
                                                                                << 0x1cU) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                                                >> 4U)))) 
                                                                                * 
                                                                                (0xffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                                                << 8U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                                                >> 0x18U)))) 
                                                                                + 
                                                                                (((0x7fc0000U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[2U] 
                                                                                >> 7U)))) 
                                                                                << 0x12U)) 
                                                                                | (0x3ffffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[2U] 
                                                                                << 0xaU) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                                                >> 0x16U)))) 
                                                                                * 
                                                                                (0xffU 
                                                                                & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U])))))) 
                                                             << 0x1bU) 
                                                            | (QData)((IData)(
                                                                              (0x7ffffffU 
                                                                               & ((((0x7fc0000U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[0U] 
                                                                                >> 0x11U)))) 
                                                                                << 0x12U)) 
                                                                                | (0x3ffffU 
                                                                                & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[0U])) 
                                                                                * 
                                                                                (0xffU 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                                                >> 8U))) 
                                                                                + 
                                                                                (((0x7fc0000U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                                                >> 3U)))) 
                                                                                << 0x12U)) 
                                                                                | (0x3ffffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                                                << 0xeU) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[0U] 
                                                                                >> 0x12U)))) 
                                                                                * 
                                                                                (0xffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                                                << 0x10U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                                                >> 0x10U))))))))) 
                                                           >> 0x20U)));
    __Vtemp66[2U] = ((0xfffe0000U & (((((0x7fc0000U 
                                         & ((- (IData)(
                                                       (1U 
                                                        & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                           >> 0x15U)))) 
                                            << 0x12U)) 
                                        | (0x3ffffU 
                                           & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[2U] 
                                               << 0x1cU) 
                                              | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                 >> 4U)))) 
                                       * (0xffU & (
                                                   (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                    << 0x18U) 
                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                      >> 8U)))) 
                                      + (((0x7fc0000U 
                                           & ((- (IData)(
                                                         (1U 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[2U] 
                                                             >> 7U)))) 
                                              << 0x12U)) 
                                          | (0x3ffffU 
                                             & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[2U] 
                                                 << 0xaU) 
                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                   >> 0x16U)))) 
                                         * (0xffU & 
                                            ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                              << 0x10U) 
                                             | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                >> 0x10U))))) 
                                     << 0x11U)) | (0x1ffffU 
                                                   & (((((0x7fc0000U 
                                                          & ((- (IData)(
                                                                        (1U 
                                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[0U] 
                                                                            >> 0x11U)))) 
                                                             << 0x12U)) 
                                                         | (0x3ffffU 
                                                            & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[0U])) 
                                                        * 
                                                        (0xffU 
                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                            >> 0x18U))) 
                                                       + 
                                                       (((0x7fc0000U 
                                                          & ((- (IData)(
                                                                        (1U 
                                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                                            >> 3U)))) 
                                                             << 0x12U)) 
                                                         | (0x3ffffU 
                                                            & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                                << 0xeU) 
                                                               | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[0U] 
                                                                  >> 0x12U)))) 
                                                        * 
                                                        (0xffU 
                                                         & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U]))) 
                                                      >> 0xaU)));
    __Vtemp66[3U] = (0xfffU & (((((0x7fc0000U & ((- (IData)(
                                                            (1U 
                                                             & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                                >> 0x15U)))) 
                                                 << 0x12U)) 
                                  | (0x3ffffU & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[2U] 
                                                  << 0x1cU) 
                                                 | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                    >> 4U)))) 
                                 * (0xffU & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                              << 0x18U) 
                                             | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                >> 8U)))) 
                                + (((0x7fc0000U & (
                                                   (- (IData)(
                                                              (1U 
                                                               & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[2U] 
                                                                  >> 7U)))) 
                                                   << 0x12U)) 
                                    | (0x3ffffU & (
                                                   (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[2U] 
                                                    << 0xaU) 
                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                      >> 0x16U)))) 
                                   * (0xffU & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                << 0x10U) 
                                               | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                  >> 0x10U))))) 
                               >> 0xfU));
    __Vtemp68[4U] = ((0xffffff80U & (((((0x7fc0000U 
                                         & ((- (IData)(
                                                       (1U 
                                                        & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                           >> 0x15U)))) 
                                            << 0x12U)) 
                                        | (0x3ffffU 
                                           & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[2U] 
                                               << 0x1cU) 
                                              | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                 >> 4U)))) 
                                       * (0xffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U])) 
                                      + (((0x7fc0000U 
                                           & ((- (IData)(
                                                         (1U 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[2U] 
                                                             >> 7U)))) 
                                              << 0x12U)) 
                                          | (0x3ffffU 
                                             & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[2U] 
                                                 << 0xaU) 
                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                   >> 0x16U)))) 
                                         * (0xffU & 
                                            ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                              << 0x18U) 
                                             | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                >> 8U))))) 
                                     << 7U)) | (0x7fU 
                                                & (((((0x7fc0000U 
                                                       & ((- (IData)(
                                                                     (1U 
                                                                      & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[0U] 
                                                                         >> 0x11U)))) 
                                                          << 0x12U)) 
                                                      | (0x3ffffU 
                                                         & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[0U])) 
                                                     * 
                                                     (0xffU 
                                                      & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                         >> 0x10U))) 
                                                    + 
                                                    (((0x7fc0000U 
                                                       & ((- (IData)(
                                                                     (1U 
                                                                      & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                                         >> 3U)))) 
                                                          << 0x12U)) 
                                                      | (0x3ffffU 
                                                         & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                             << 0xeU) 
                                                            | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[0U] 
                                                               >> 0x12U)))) 
                                                     * 
                                                     (0xffU 
                                                      & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                          << 8U) 
                                                         | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                            >> 0x18U))))) 
                                                   >> 0x14U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7311_o[0U] 
        = __Vtemp65[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7311_o[1U] 
        = __Vtemp65[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7311_o[2U] 
        = __Vtemp66[2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7311_o[3U] 
        = ((0xfffff000U & (((((0x7fc0000U & ((- (IData)(
                                                        (1U 
                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[0U] 
                                                            >> 0x11U)))) 
                                             << 0x12U)) 
                              | (0x3ffffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[0U])) 
                             * (0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                         >> 0x10U))) 
                            + (((0x7fc0000U & ((- (IData)(
                                                          (1U 
                                                           & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                              >> 3U)))) 
                                               << 0x12U)) 
                                | (0x3ffffU & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                << 0xeU) 
                                               | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[0U] 
                                                  >> 0x12U)))) 
                               * (0xffU & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                            << 8U) 
                                           | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                              >> 0x18U))))) 
                           << 0xcU)) | __Vtemp66[3U]);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7311_o[4U] 
        = __Vtemp68[4U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7311_o[5U] 
        = (3U & (((((0x7fc0000U & ((- (IData)((1U & 
                                               (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                >> 0x15U)))) 
                                   << 0x12U)) | (0x3ffffU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[2U] 
                                                     << 0x1cU) 
                                                    | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                       >> 4U)))) 
                   * (0xffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U])) 
                  + (((0x7fc0000U & ((- (IData)((1U 
                                                 & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[2U] 
                                                    >> 7U)))) 
                                     << 0x12U)) | (0x3ffffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[2U] 
                                                       << 0xaU) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8536_q[1U] 
                                                         >> 0x16U)))) 
                     * (0xffU & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                  << 0x18U) | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                               >> 8U))))) 
                 >> 0x19U));
    __Vtemp80[0U] = (IData)((((QData)((IData)((0xffffffU 
                                               & ((0xffffff00U 
                                                   & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U]) 
                                                  | (0xffU 
                                                     & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U]))))) 
                              << 0x18U) | (QData)((IData)(
                                                          (0xffffffU 
                                                           & ((0xffffff00U 
                                                               & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U]) 
                                                              | (0xffU 
                                                                 & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U])))))));
    __Vtemp80[1U] = ((0xffff0000U & ((0xff000000U & 
                                      (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U] 
                                       << 0x10U)) | 
                                     (0xff0000U & (
                                                   vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U] 
                                                   << 0x10U)))) 
                     | (IData)(((((QData)((IData)((0xffffffU 
                                                   & ((0xffffff00U 
                                                       & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U]) 
                                                      | (0xffU 
                                                         & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U]))))) 
                                  << 0x18U) | (QData)((IData)(
                                                              (0xffffffU 
                                                               & ((0xffffff00U 
                                                                   & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U]) 
                                                                  | (0xffU 
                                                                     & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U])))))) 
                                >> 0x20U)));
    if (VL_GTS_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8473_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8275_q))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8443_q[0U] 
            = ((0x800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q))
                ? (IData)((((QData)((IData)((0xffffffU 
                                             & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U] 
                                                 << 8U) 
                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[0U] 
                                                   >> 0x18U))))) 
                            << 0x18U) | (QData)((IData)(
                                                        (0xffffffU 
                                                         & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U] 
                                                             << 8U) 
                                                            | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[0U] 
                                                               >> 0x18U)))))))
                : __Vtemp80[0U]);
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8443_q[1U] 
            = ((0x800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q))
                ? ((0xffff0000U & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U] 
                                    << 0x18U) | (0xff0000U 
                                                 & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[0U] 
                                                    >> 8U)))) 
                   | (IData)(((((QData)((IData)((0xffffffU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U] 
                                                     << 8U) 
                                                    | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[0U] 
                                                       >> 0x18U))))) 
                                << 0x18U) | (QData)((IData)(
                                                            (0xffffffU 
                                                             & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U] 
                                                                 << 8U) 
                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[0U] 
                                                                   >> 0x18U)))))) 
                              >> 0x20U))) : __Vtemp80[1U]);
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8443_q[2U] 
            = ((0x800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q))
                ? ((0xffffff00U & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[2U] 
                                    << 0x18U) | (0xffff00U 
                                                 & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U] 
                                                    >> 8U)))) 
                   | (0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U] 
                               >> 8U))) : ((0xffffff00U 
                                            & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[2U] 
                                                << 0x18U) 
                                               | (0xffff00U 
                                                  & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U] 
                                                     >> 8U)))) 
                                           | (0xffU 
                                              & ((0xffffU 
                                                  & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U] 
                                                     >> 0x10U)) 
                                                 | (0xff0000U 
                                                    & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[1U] 
                                                       << 0x10U))))));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8443_q[0U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6363_o[0U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8443_q[1U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6363_o[1U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8443_q[2U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6363_o[2U];
    }
    VL_EXTEND_WW(120,108, __Vtemp87, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8520_q 
        = ((0U != (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8015_q)))
            ? (((QData)((IData)((0x3ffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9480_o)))) 
                << 0x1eU) | (QData)((IData)(((0x3ff00000U 
                                              & ((IData)(
                                                         (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9480_o 
                                                          >> 0xaU)) 
                                                 << 0x14U)) 
                                             | ((0xffc00U 
                                                 & ((IData)(
                                                            (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9480_o 
                                                             >> 0x14U)) 
                                                    << 0xaU)) 
                                                | (0x3ffU 
                                                   & (IData)(
                                                             (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9480_o 
                                                              >> 0x1eU))))))))
            : ((0x80000U & __Vtemp87[2U]) ? 0x10000000ULL
                : 0x40000ULL));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6023_o 
        = (0xfffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5986_o)
                      ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8265_q)
                      : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6004_o)
                          ? 0U : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8073_q)
                                   ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8059_q)
                                   : ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8265_q))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6190_o 
        = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8075_q) 
            & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8071_q)) 
           | ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5986_o)
               ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8083_q)
               : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6004_o)
                   ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8083_q)
                   : ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8073_q)) 
                      & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8083_q)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2689_o 
        = ((~ ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2685_o) 
               & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2682_o))) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_bibu));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2687_o 
        = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2685_o) 
            & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2682_o))
            ? 2U : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8339_q));
    __Vtemp89[0U] = (IData)((((QData)((IData)((0x7ffffffU 
                                               & ((((0x7fc0000U 
                                                     & ((- (IData)(
                                                                   (1U 
                                                                    & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                                       >> 0x15U)))) 
                                                        << 0x12U)) 
                                                    | (0x3ffffU 
                                                       & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[2U] 
                                                           << 0x1cU) 
                                                          | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                             >> 4U)))) 
                                                   * 
                                                   (0xffU 
                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[1U] 
                                                        << 8U) 
                                                       | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0U] 
                                                          >> 0x18U)))) 
                                                  + 
                                                  (((0x7fc0000U 
                                                     & ((- (IData)(
                                                                   (1U 
                                                                    & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[2U] 
                                                                       >> 7U)))) 
                                                        << 0x12U)) 
                                                    | (0x3ffffU 
                                                       & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[2U] 
                                                           << 0xaU) 
                                                          | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                             >> 0x16U)))) 
                                                   * 
                                                   (0xffU 
                                                    & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0U])))))) 
                              << 0x1bU) | (QData)((IData)(
                                                          (0x7ffffffU 
                                                           & ((((0x7fc0000U 
                                                                 & ((- (IData)(
                                                                               (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[0U] 
                                                                                >> 0x11U)))) 
                                                                    << 0x12U)) 
                                                                | (0x3ffffU 
                                                                   & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[0U])) 
                                                               * 
                                                               (0xffU 
                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[3U] 
                                                                    << 0x18U) 
                                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[2U] 
                                                                      >> 8U)))) 
                                                              + 
                                                              (((0x7fc0000U 
                                                                 & ((- (IData)(
                                                                               (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                                                >> 3U)))) 
                                                                    << 0x12U)) 
                                                                | (0x3ffffU 
                                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                                       << 0xeU) 
                                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[0U] 
                                                                         >> 0x12U)))) 
                                                               * 
                                                               (0xffU 
                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[2U] 
                                                                    << 0x10U) 
                                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[1U] 
                                                                      >> 0x10U))))))))));
    __Vtemp89[1U] = ((0xffc00000U & (((((0x7fc0000U 
                                         & ((- (IData)(
                                                       (1U 
                                                        & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[0U] 
                                                           >> 0x11U)))) 
                                            << 0x12U)) 
                                        | (0x3ffffU 
                                           & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[0U])) 
                                       * (0xffU & (
                                                   (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[3U] 
                                                    << 8U) 
                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[2U] 
                                                      >> 0x18U)))) 
                                      + (((0x7fc0000U 
                                           & ((- (IData)(
                                                         (1U 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                             >> 3U)))) 
                                              << 0x12U)) 
                                          | (0x3ffffU 
                                             & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                 << 0xeU) 
                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[0U] 
                                                   >> 0x12U)))) 
                                         * (0xffU & 
                                            vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[2U]))) 
                                     << 0x16U)) | (IData)(
                                                          ((((QData)((IData)(
                                                                             (0x7ffffffU 
                                                                              & ((((0x7fc0000U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                                                >> 0x15U)))) 
                                                                                << 0x12U)) 
                                                                                | (0x3ffffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[2U] 
                                                                                << 0x1cU) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                                                >> 4U)))) 
                                                                                * 
                                                                                (0xffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[1U] 
                                                                                << 8U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0U] 
                                                                                >> 0x18U)))) 
                                                                                + 
                                                                                (((0x7fc0000U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[2U] 
                                                                                >> 7U)))) 
                                                                                << 0x12U)) 
                                                                                | (0x3ffffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[2U] 
                                                                                << 0xaU) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                                                >> 0x16U)))) 
                                                                                * 
                                                                                (0xffU 
                                                                                & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0U])))))) 
                                                             << 0x1bU) 
                                                            | (QData)((IData)(
                                                                              (0x7ffffffU 
                                                                               & ((((0x7fc0000U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[0U] 
                                                                                >> 0x11U)))) 
                                                                                << 0x12U)) 
                                                                                | (0x3ffffU 
                                                                                & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[0U])) 
                                                                                * 
                                                                                (0xffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[3U] 
                                                                                << 0x18U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[2U] 
                                                                                >> 8U)))) 
                                                                                + 
                                                                                (((0x7fc0000U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                                                >> 3U)))) 
                                                                                << 0x12U)) 
                                                                                | (0x3ffffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                                                << 0xeU) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[0U] 
                                                                                >> 0x12U)))) 
                                                                                * 
                                                                                (0xffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[2U] 
                                                                                << 0x10U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[1U] 
                                                                                >> 0x10U))))))))) 
                                                           >> 0x20U)));
    __Vtemp90[2U] = ((0xfffe0000U & (((((0x7fc0000U 
                                         & ((- (IData)(
                                                       (1U 
                                                        & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                           >> 0x15U)))) 
                                            << 0x12U)) 
                                        | (0x3ffffU 
                                           & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[2U] 
                                               << 0x1cU) 
                                              | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                 >> 4U)))) 
                                       * (0xffU & (
                                                   (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[2U] 
                                                    << 0x18U) 
                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[1U] 
                                                      >> 8U)))) 
                                      + (((0x7fc0000U 
                                           & ((- (IData)(
                                                         (1U 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[2U] 
                                                             >> 7U)))) 
                                              << 0x12U)) 
                                          | (0x3ffffU 
                                             & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[2U] 
                                                 << 0xaU) 
                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                   >> 0x16U)))) 
                                         * (0xffU & 
                                            ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[1U] 
                                              << 0x10U) 
                                             | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0U] 
                                                >> 0x10U))))) 
                                     << 0x11U)) | (0x1ffffU 
                                                   & (((((0x7fc0000U 
                                                          & ((- (IData)(
                                                                        (1U 
                                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[0U] 
                                                                            >> 0x11U)))) 
                                                             << 0x12U)) 
                                                         | (0x3ffffU 
                                                            & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[0U])) 
                                                        * 
                                                        (0xffU 
                                                         & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[3U] 
                                                             << 8U) 
                                                            | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[2U] 
                                                               >> 0x18U)))) 
                                                       + 
                                                       (((0x7fc0000U 
                                                          & ((- (IData)(
                                                                        (1U 
                                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                                            >> 3U)))) 
                                                             << 0x12U)) 
                                                         | (0x3ffffU 
                                                            & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                                << 0xeU) 
                                                               | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[0U] 
                                                                  >> 0x12U)))) 
                                                        * 
                                                        (0xffU 
                                                         & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[2U]))) 
                                                      >> 0xaU)));
    __Vtemp90[3U] = (0xfffU & (((((0x7fc0000U & ((- (IData)(
                                                            (1U 
                                                             & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                                >> 0x15U)))) 
                                                 << 0x12U)) 
                                  | (0x3ffffU & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[2U] 
                                                  << 0x1cU) 
                                                 | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                    >> 4U)))) 
                                 * (0xffU & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[2U] 
                                              << 0x18U) 
                                             | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[1U] 
                                                >> 8U)))) 
                                + (((0x7fc0000U & (
                                                   (- (IData)(
                                                              (1U 
                                                               & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[2U] 
                                                                  >> 7U)))) 
                                                   << 0x12U)) 
                                    | (0x3ffffU & (
                                                   (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[2U] 
                                                    << 0xaU) 
                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                      >> 0x16U)))) 
                                   * (0xffU & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[1U] 
                                                << 0x10U) 
                                               | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0U] 
                                                  >> 0x10U))))) 
                               >> 0xfU));
    __Vtemp91[3U] = ((0xfffff000U & (((((0x7fc0000U 
                                         & ((- (IData)(
                                                       (1U 
                                                        & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[0U] 
                                                           >> 0x11U)))) 
                                            << 0x12U)) 
                                        | (0x3ffffU 
                                           & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[0U])) 
                                       * (0xffU & (
                                                   (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[3U] 
                                                    << 0x10U) 
                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[2U] 
                                                      >> 0x10U)))) 
                                      + (((0x7fc0000U 
                                           & ((- (IData)(
                                                         (1U 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                             >> 3U)))) 
                                              << 0x12U)) 
                                          | (0x3ffffU 
                                             & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                 << 0xeU) 
                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[0U] 
                                                   >> 0x12U)))) 
                                         * (0xffU & 
                                            ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[2U] 
                                              << 8U) 
                                             | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[1U] 
                                                >> 0x18U))))) 
                                     << 0xcU)) | __Vtemp90[3U]);
    __Vtemp92[4U] = ((0xffffff80U & (((((0x7fc0000U 
                                         & ((- (IData)(
                                                       (1U 
                                                        & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                           >> 0x15U)))) 
                                            << 0x12U)) 
                                        | (0x3ffffU 
                                           & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[2U] 
                                               << 0x1cU) 
                                              | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                 >> 4U)))) 
                                       * (0xffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[1U])) 
                                      + (((0x7fc0000U 
                                           & ((- (IData)(
                                                         (1U 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[2U] 
                                                             >> 7U)))) 
                                              << 0x12U)) 
                                          | (0x3ffffU 
                                             & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[2U] 
                                                 << 0xaU) 
                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                   >> 0x16U)))) 
                                         * (0xffU & 
                                            ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[1U] 
                                              << 0x18U) 
                                             | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0U] 
                                                >> 8U))))) 
                                     << 7U)) | (0x7fU 
                                                & (((((0x7fc0000U 
                                                       & ((- (IData)(
                                                                     (1U 
                                                                      & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[0U] 
                                                                         >> 0x11U)))) 
                                                          << 0x12U)) 
                                                      | (0x3ffffU 
                                                         & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[0U])) 
                                                     * 
                                                     (0xffU 
                                                      & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[3U] 
                                                          << 0x10U) 
                                                         | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[2U] 
                                                            >> 0x10U)))) 
                                                    + 
                                                    (((0x7fc0000U 
                                                       & ((- (IData)(
                                                                     (1U 
                                                                      & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                                         >> 3U)))) 
                                                          << 0x12U)) 
                                                      | (0x3ffffU 
                                                         & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                             << 0xeU) 
                                                            | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[0U] 
                                                               >> 0x12U)))) 
                                                     * 
                                                     (0xffU 
                                                      & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[2U] 
                                                          << 8U) 
                                                         | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[1U] 
                                                            >> 0x18U))))) 
                                                   >> 0x14U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5633_o[0U] 
        = __Vtemp89[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5633_o[1U] 
        = __Vtemp89[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5633_o[2U] 
        = __Vtemp90[2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5633_o[3U] 
        = __Vtemp91[3U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5633_o[4U] 
        = __Vtemp92[4U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5633_o[5U] 
        = (3U & (((((0x7fc0000U & ((- (IData)((1U & 
                                               (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                >> 0x15U)))) 
                                   << 0x12U)) | (0x3ffffU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[2U] 
                                                     << 0x1cU) 
                                                    | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                       >> 4U)))) 
                   * (0xffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[1U])) 
                  + (((0x7fc0000U & ((- (IData)((1U 
                                                 & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[2U] 
                                                    >> 7U)))) 
                                     << 0x12U)) | (0x3ffffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[2U] 
                                                       << 0xaU) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8538_q[1U] 
                                                         >> 0x16U)))) 
                     * (0xffU & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[1U] 
                                  << 0x18U) | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0U] 
                                               >> 8U))))) 
                 >> 0x19U));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[3U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[1U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[4U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[2U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[5U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[3U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[4U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[5U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[6U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[9U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[7U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0xaU];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[8U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0xbU];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[9U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0xcU];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0xaU] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0xdU];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0xbU] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0xeU];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0xcU] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0xfU];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0xdU] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0x10U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0xeU] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0x11U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0xfU] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0x12U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0x10U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0x13U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0x11U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[0x14U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0x12U] 
        = (IData)((((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8430_q)) 
                    << 0x18U) | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8426_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0x13U] 
        = ((0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8434_q 
                           << 0x10U)) | (IData)(((((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8430_q)) 
                                                   << 0x18U) 
                                                  | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8426_q))) 
                                                 >> 0x20U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5730_o[0x14U] 
        = ((0xffffff00U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8438_q 
                           << 8U)) | (0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8434_q 
                                                 >> 0x10U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8525_q 
        = ((0U != (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8018_q)))
            ? (((QData)((IData)((0x3ffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9054_o)))) 
                << 0x1eU) | (QData)((IData)(((0x3ff00000U 
                                              & ((IData)(
                                                         (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9054_o 
                                                          >> 0xaU)) 
                                                 << 0x14U)) 
                                             | ((0xffc00U 
                                                 & ((IData)(
                                                            (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9054_o 
                                                             >> 0x14U)) 
                                                    << 0xaU)) 
                                                | (0x3ffU 
                                                   & (IData)(
                                                             (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9054_o 
                                                              >> 0x1eU))))))))
            : ((0x800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q))
                ? 0x10000000ULL : 0x40000ULL));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7432_o[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[1U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7432_o[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[2U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7432_o[2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[3U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7432_o[3U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[4U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7432_o[4U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8275_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8274_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8473_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8472_o;
    if ((0x800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[0U] 
            = (IData)((((QData)((IData)((0xffffffU 
                                         & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[2U] 
                                             << 0x10U) 
                                            | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[1U] 
                                               >> 0x10U))))) 
                        << 0x18U) | (QData)((IData)(
                                                    (0xffffffU 
                                                     & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[0U])))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U] 
            = ((0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[2U] 
                               << 8U)) | (IData)(((
                                                   ((QData)((IData)(
                                                                    (0xffffffU 
                                                                     & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[2U] 
                                                                         << 0x10U) 
                                                                        | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[1U] 
                                                                           >> 0x10U))))) 
                                                    << 0x18U) 
                                                   | (QData)((IData)(
                                                                     (0xffffffU 
                                                                      & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[0U])))) 
                                                  >> 0x20U)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[2U] 
            = (0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[2U] 
                        >> 0x18U));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[0U] 
            = (IData)((0xffffffffffffULL & (((QData)((IData)(
                                                             vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[1U])) 
                                             << 0x20U) 
                                            | (QData)((IData)(
                                                              vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[0U])))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U] 
            = ((0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[2U] 
                               << 8U)) | (IData)(((0xffffffffffffULL 
                                                   & (((QData)((IData)(
                                                                       vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[1U])) 
                                                       << 0x20U) 
                                                      | (QData)((IData)(
                                                                        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[0U])))) 
                                                  >> 0x20U)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[2U] 
            = (0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[2U] 
                        >> 0x18U));
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8015_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8014_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q[0U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5723_o[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q[1U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5723_o[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q[2U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5723_o[2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q[3U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5723_o[3U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9054_o 
        = ((0x80U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
            ? ((0x40U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                ? ((0x20U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                    ? ((0x10U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9044_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9042_o)
                    : ((0x10U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9040_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9038_o))
                : ((0x20U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                    ? ((0x10U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9036_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9034_o)
                    : ((0x10U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9032_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9030_o)))
            : ((0x40U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                ? ((0x20U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                    ? ((0x10U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9028_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9026_o)
                    : ((0x10U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9024_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9022_o))
                : ((0x20U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                    ? ((0x10U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9020_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9018_o)
                    : ((0x10U & ((IData)(0xffU) - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9016_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9014_o))));
    __Vtemp112[1U] = ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                       ? ((0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6290_o 
                                          << 0x10U)) 
                          | (IData)(((((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6292_o)) 
                                       << 0x18U) | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6286_o))) 
                                     >> 0x20U))) : 
                      ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                        ? ((0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6288_o 
                                           << 0x10U)) 
                           | (IData)(((((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6290_o)) 
                                        << 0x18U) | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6292_o))) 
                                      >> 0x20U))) : 
                       ((0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6286_o 
                                        << 0x10U)) 
                        | (IData)(((((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6288_o)) 
                                     << 0x18U) | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6290_o))) 
                                   >> 0x20U)))));
    if ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[0U] 
            = (IData)((((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6286_o)) 
                        << 0x18U) | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6288_o))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[1U] 
            = ((0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6292_o 
                               << 0x10U)) | (IData)(
                                                    ((((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6286_o)) 
                                                       << 0x18U) 
                                                      | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6288_o))) 
                                                     >> 0x20U)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[2U] 
            = ((0xffffff00U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6290_o 
                               << 8U)) | (0xffffU & 
                                          (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6292_o 
                                           >> 0x10U)));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[0U] 
            = ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                ? (IData)((((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6292_o)) 
                            << 0x18U) | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6286_o))))
                : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                    ? (IData)((((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6290_o)) 
                                << 0x18U) | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6292_o))))
                    : (IData)((((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6288_o)) 
                                << 0x18U) | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6290_o))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[1U] 
            = __Vtemp112[1U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[2U] 
            = ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                ? ((0xffffff00U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6288_o 
                                   << 8U)) | (0xffffU 
                                              & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6290_o 
                                                 >> 0x10U)))
                : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6303_o))
                    ? ((0xffffff00U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6286_o 
                                       << 8U)) | (0xffffU 
                                                  & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6288_o 
                                                     >> 0x10U)))
                    : ((0xffffff00U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6292_o 
                                       << 8U)) | (0xffffU 
                                                  & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6286_o 
                                                     >> 0x10U)))));
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4252_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8557_q)
            ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8525_q
            : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8558_q)
                ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8520_q
                : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8530_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8018_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8017_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8283_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5714_o 
        = (((3U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8015_q))) 
            << 2U) | ((((1U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8015_q))) 
                        | (2U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8015_q)))) 
                       << 1U) | (0U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8015_q)))));
    VL_EXTEND_WW(120,108, __Vtemp116, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp119, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp122, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4687_o 
        = (0xffU & ((0x8000U & __Vtemp116[1U]) ? (~ 
                                                  ((__Vtemp119[2U] 
                                                    << 0x18U) 
                                                   | (__Vtemp119[1U] 
                                                      >> 8U)))
                     : ((__Vtemp122[2U] << 0x18U) | 
                        (__Vtemp122[1U] >> 8U))));
    VL_EXTEND_WW(120,108, __Vtemp125, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp128, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp131, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp134, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4907_o 
        = (((QData)((IData)(((0xff800000U & (((0xffU 
                                               & ((__Vtemp128[1U] 
                                                   << 4U) 
                                                  | (__Vtemp128[0U] 
                                                     >> 0x1cU))) 
                                              * (0xffU 
                                                 & ((__Vtemp134[1U] 
                                                     << 4U) 
                                                    | (__Vtemp134[0U] 
                                                       >> 0x1cU)))) 
                                             << 0xfU)) 
                             | ((0x7ff000U & ((((((
                                                   (0x1feU 
                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                        << 0x11U) 
                                                       | (0x1fffeU 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                             >> 0xfU)))) 
                                                   - 
                                                   (0x1feU 
                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                        << 9U) 
                                                       | (0x1feU 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U] 
                                                             >> 0x17U))))) 
                                                  - 
                                                  (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                       << 8U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U] 
                                                         >> 0x18U)))) 
                                                 + 
                                                 (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                      << 0x10U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                        >> 0x10U)))) 
                                                + (0xffU 
                                                   & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U])) 
                                               - (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[9U] 
                                                      << 0x18U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                        >> 8U)))) 
                                              << 0xcU)) 
                                | (0xfffU & (((((0x1feU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[9U] 
                                                     << 0x19U) 
                                                    | (0x1fffffeU 
                                                       & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                          >> 7U)))) 
                                                - (0x3fcU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                       << 0x12U) 
                                                      | (0x3fffcU 
                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                            >> 0xeU))))) 
                                               - (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                      << 0x10U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                        >> 0x10U)))) 
                                              + (0x3fcU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                     << 0xaU) 
                                                    | (0x3fcU 
                                                       & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U] 
                                                          >> 0x16U))))) 
                                             - (0xffU 
                                                & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U]))))))) 
            << 9U) | (QData)((IData)((0x1ffU & ((0xffU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                     << 8U) 
                                                    | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U] 
                                                       >> 0x18U))) 
                                                - (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[9U] 
                                                       << 0x18U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                         >> 8U))))))));
    VL_EXTEND_WW(120,108, __Vtemp137, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp140, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp143, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp146, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4980_o 
        = (((QData)((IData)(((0xff800000U & (((0xffU 
                                               & ((__Vtemp140[1U] 
                                                   << 4U) 
                                                  | (__Vtemp140[0U] 
                                                     >> 0x1cU))) 
                                              * (0xffU 
                                                 & ((__Vtemp146[1U] 
                                                     << 4U) 
                                                    | (__Vtemp146[0U] 
                                                       >> 0x1cU)))) 
                                             << 0xfU)) 
                             | ((0x7ff000U & ((((((
                                                   (0x1feU 
                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                        << 9U) 
                                                       | (0x1feU 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                             >> 0x17U)))) 
                                                   - 
                                                   (0x1feU 
                                                    & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                       << 1U))) 
                                                  - 
                                                  (0xffU 
                                                   & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U])) 
                                                 + 
                                                 (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                      << 8U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                        >> 0x18U)))) 
                                                + (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                       << 0x18U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U] 
                                                         >> 8U)))) 
                                               - (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[9U] 
                                                      << 0x10U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                        >> 0x10U)))) 
                                              << 0xcU)) 
                                | (0xfffU & (((((0x1feU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[9U] 
                                                     << 0x11U) 
                                                    | (0x1fffeU 
                                                       & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                          >> 0xfU)))) 
                                                - (0x3fcU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                       << 0xaU) 
                                                      | (0x3fcU 
                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                            >> 0x16U))))) 
                                               - (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                      << 8U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                        >> 0x18U)))) 
                                              + (0x3fcU 
                                                 & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                    << 2U))) 
                                             - (0xffU 
                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                    << 0x18U) 
                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U] 
                                                      >> 8U))))))))) 
            << 9U) | (QData)((IData)((0x1ffU & ((0xffU 
                                                 & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U]) 
                                                - (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[9U] 
                                                       << 0x10U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                         >> 0x10U))))))));
    VL_EXTEND_WW(120,108, __Vtemp149, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp152, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp155, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp158, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5053_o 
        = (((QData)((IData)(((0xff800000U & (((0xffU 
                                               & ((__Vtemp152[1U] 
                                                   << 4U) 
                                                  | (__Vtemp152[0U] 
                                                     >> 0x1cU))) 
                                              * (0xffU 
                                                 & ((__Vtemp158[1U] 
                                                     << 4U) 
                                                    | (__Vtemp158[0U] 
                                                       >> 0x1cU)))) 
                                             << 0xfU)) 
                             | ((0x7ff000U & ((((((
                                                   (0x1feU 
                                                    & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                       << 1U)) 
                                                   - 
                                                   (0x1feU 
                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                        << 0x19U) 
                                                       | (0x1fffffeU 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                             >> 7U))))) 
                                                  - 
                                                  (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                       << 0x18U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                         >> 8U)))) 
                                                 + 
                                                 (0xffU 
                                                  & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U])) 
                                                + (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                       << 0x10U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U] 
                                                         >> 0x10U)))) 
                                               - (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[9U] 
                                                      << 8U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                        >> 0x18U)))) 
                                              << 0xcU)) 
                                | (0xfffU & (((((0x1feU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[9U] 
                                                     << 9U) 
                                                    | (0x1feU 
                                                       & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                          >> 0x17U)))) 
                                                - (0x3fcU 
                                                   & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                      << 2U))) 
                                               - (0xffU 
                                                  & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U])) 
                                              + (0x3fcU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                     << 0x1aU) 
                                                    | (0x3fffffcU 
                                                       & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                          >> 6U))))) 
                                             - (0xffU 
                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                    << 0x10U) 
                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U] 
                                                      >> 0x10U))))))))) 
            << 9U) | (QData)((IData)((0x1ffU & ((0xffU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                     << 0x18U) 
                                                    | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                       >> 8U))) 
                                                - (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[9U] 
                                                       << 8U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                         >> 0x18U))))))));
    VL_EXTEND_WW(120,108, __Vtemp161, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp164, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp167, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp170, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp173, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp176, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5450_o 
        = (((QData)((IData)((0x3ffU & ((((0xff800U 
                                          & ((- (IData)(
                                                        (1U 
                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[2U] 
                                                            >> 0x1fU)))) 
                                             << 0xbU)) 
                                         | (0x7ffU 
                                            & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[2U] 
                                               >> 0x15U))) 
                                        * (0xffU & 
                                           ((__Vtemp164[1U] 
                                             << 0x10U) 
                                            | (__Vtemp164[0U] 
                                               >> 0x10U)))) 
                                       >> 9U)))) << 0x32U) 
           | (((QData)((IData)((0x3ffU & ((((0xff800U 
                                             & ((- (IData)(
                                                           (1U 
                                                            & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[2U] 
                                                               >> 0x14U)))) 
                                                << 0xbU)) 
                                            | (0x7ffU 
                                               & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[2U] 
                                                  >> 0xaU))) 
                                           * (0xffU 
                                              & ((__Vtemp170[1U] 
                                                  << 0x10U) 
                                                 | (__Vtemp170[0U] 
                                                    >> 0x10U)))) 
                                          >> 9U)))) 
               << 0x28U) | (((QData)((IData)((0x3ffU 
                                              & ((((0xff800U 
                                                    & ((- (IData)(
                                                                  (1U 
                                                                   & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[2U] 
                                                                      >> 9U)))) 
                                                       << 0xbU)) 
                                                   | (0x7ffU 
                                                      & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[2U] 
                                                          << 1U) 
                                                         | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[1U] 
                                                            >> 0x1fU)))) 
                                                  * 
                                                  (0xffU 
                                                   & ((__Vtemp176[1U] 
                                                       << 0x10U) 
                                                      | (__Vtemp176[0U] 
                                                         >> 0x10U)))) 
                                                 >> 9U)))) 
                             << 0x1eU) | (QData)((IData)(
                                                         ((0x3ff00000U 
                                                           & (((((0x200U 
                                                                  & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[0U] 
                                                                     >> 0x11U)) 
                                                                 | (0x1ffU 
                                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[1U] 
                                                                        << 0xeU) 
                                                                       | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[0U] 
                                                                          >> 0x12U)))) 
                                                                + 
                                                                (0xffU 
                                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8503_q[4U] 
                                                                     << 0x1eU) 
                                                                    | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8503_q[3U] 
                                                                       >> 2U)))) 
                                                               + 
                                                               ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[2U] 
                                                                 << 0xcU) 
                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[1U] 
                                                                   >> 0x14U))) 
                                                              << 0x14U)) 
                                                          | ((0xffc00U 
                                                              & (((((0x200U 
                                                                     & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[0U] 
                                                                        >> 8U)) 
                                                                    | (0x1ffU 
                                                                       & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[1U] 
                                                                           << 0x17U) 
                                                                          | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[0U] 
                                                                             >> 9U)))) 
                                                                   + 
                                                                   (0xffU 
                                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8503_q[2U] 
                                                                        << 0xfU) 
                                                                       | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8503_q[1U] 
                                                                          >> 0x11U)))) 
                                                                  + 
                                                                  ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[2U] 
                                                                    << 0x18U) 
                                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[1U] 
                                                                      >> 8U))) 
                                                                 << 0xaU)) 
                                                             | (0x3ffU 
                                                                & ((((0x200U 
                                                                      & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[0U] 
                                                                         << 1U)) 
                                                                     | (0x1ffU 
                                                                        & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[0U])) 
                                                                    + 
                                                                    (0xffU 
                                                                     & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8503_q[0U])) 
                                                                   + 
                                                                   ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[1U] 
                                                                     << 4U) 
                                                                    | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8509_q[0U] 
                                                                       >> 0x1cU)))))))))));
    VL_EXTEND_WW(120,108, __Vtemp179, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5723_o[0U] 
        = ((__Vtemp179[1U] << 0x14U) | (__Vtemp179[0U] 
                                        >> 0xcU));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5723_o[1U] 
        = ((__Vtemp179[2U] << 0x14U) | (__Vtemp179[1U] 
                                        >> 0xcU));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5723_o[2U] 
        = ((0xfff00000U & (__Vtemp179[3U] << 0x14U)) 
           | (__Vtemp179[2U] >> 0xcU));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5723_o[3U] 
        = ((0xfc0U & ((IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8455_q 
                               >> 6U)) << 6U)) | ((0x20U 
                                                   & ((~ 
                                                       (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4620_o 
                                                        >> 0x14U)) 
                                                      << 5U)) 
                                                  | ((0x10U 
                                                      & ((~ 
                                                          (1U 
                                                           & (((0x100000U 
                                                                & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4620_o)
                                                                ? 
                                                               (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4620_o 
                                                                + 
                                                                ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q) 
                                                                 << 1U))
                                                                : 
                                                               (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4620_o 
                                                                - 
                                                                ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q) 
                                                                 << 1U))) 
                                                              >> 0x14U))) 
                                                         << 4U)) 
                                                     | (0xfU 
                                                        & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8455_q)))));
    VL_EXTEND_WW(120,108, __Vtemp187, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n4230_o 
        = (0xffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8557_q)
                     ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8519_q)
                     : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8558_q)
                         ? ((0xfff00000U & (__Vtemp187[3U] 
                                            << 0x14U)) 
                            | (__Vtemp187[2U] >> 0xcU))
                         : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8518_q))));
    VL_EXTEND_WW(120,108, __Vtemp190, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp193, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp196, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp199, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5136_o 
        = (((QData)((IData)(((0xff800000U & (((0xffU 
                                               & ((__Vtemp193[1U] 
                                                   << 4U) 
                                                  | (__Vtemp193[0U] 
                                                     >> 0x1cU))) 
                                              * (0xffU 
                                                 & ((__Vtemp199[1U] 
                                                     << 4U) 
                                                    | (__Vtemp199[0U] 
                                                       >> 0x1cU)))) 
                                             << 0xfU)) 
                             | ((0x7ff000U & ((((((
                                                   (0x1feU 
                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                        << 0x11U) 
                                                       | (0x1fffeU 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                             >> 0xfU)))) 
                                                   - 
                                                   (0x1feU 
                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                        << 9U) 
                                                       | (0x1feU 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U] 
                                                             >> 0x17U))))) 
                                                  - 
                                                  (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                       << 8U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U] 
                                                         >> 0x18U)))) 
                                                 + 
                                                 (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                      << 0x10U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                        >> 0x10U)))) 
                                                + (0xffU 
                                                   & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U])) 
                                               - (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[9U] 
                                                      << 0x18U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                        >> 8U)))) 
                                              << 0xcU)) 
                                | (0xfffU & (((((0x1feU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[9U] 
                                                     << 0x19U) 
                                                    | (0x1fffffeU 
                                                       & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                          >> 7U)))) 
                                                - (0x3fcU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                       << 0x12U) 
                                                      | (0x3fffcU 
                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                            >> 0xeU))))) 
                                               - (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                      << 0x10U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                        >> 0x10U)))) 
                                              + (0x3fcU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                     << 0xaU) 
                                                    | (0x3fcU 
                                                       & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U] 
                                                          >> 0x16U))))) 
                                             - (0xffU 
                                                & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U]))))))) 
            << 9U) | (QData)((IData)((0x1ffU & ((0xffU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                     << 8U) 
                                                    | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U] 
                                                       >> 0x18U))) 
                                                - (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[9U] 
                                                       << 0x18U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                         >> 8U))))))));
    VL_EXTEND_WW(120,108, __Vtemp202, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp205, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp208, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp211, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5209_o 
        = (((QData)((IData)(((0xff800000U & (((0xffU 
                                               & ((__Vtemp205[1U] 
                                                   << 4U) 
                                                  | (__Vtemp205[0U] 
                                                     >> 0x1cU))) 
                                              * (0xffU 
                                                 & ((__Vtemp211[1U] 
                                                     << 4U) 
                                                    | (__Vtemp211[0U] 
                                                       >> 0x1cU)))) 
                                             << 0xfU)) 
                             | ((0x7ff000U & ((((((
                                                   (0x1feU 
                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                        << 9U) 
                                                       | (0x1feU 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                             >> 0x17U)))) 
                                                   - 
                                                   (0x1feU 
                                                    & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                       << 1U))) 
                                                  - 
                                                  (0xffU 
                                                   & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U])) 
                                                 + 
                                                 (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                      << 8U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                        >> 0x18U)))) 
                                                + (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                       << 0x18U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U] 
                                                         >> 8U)))) 
                                               - (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[9U] 
                                                      << 0x10U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                        >> 0x10U)))) 
                                              << 0xcU)) 
                                | (0xfffU & (((((0x1feU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[9U] 
                                                     << 0x11U) 
                                                    | (0x1fffeU 
                                                       & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                          >> 0xfU)))) 
                                                - (0x3fcU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                       << 0xaU) 
                                                      | (0x3fcU 
                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                            >> 0x16U))))) 
                                               - (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                      << 8U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                        >> 0x18U)))) 
                                              + (0x3fcU 
                                                 & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                    << 2U))) 
                                             - (0xffU 
                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                    << 0x18U) 
                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U] 
                                                      >> 8U))))))))) 
            << 9U) | (QData)((IData)((0x1ffU & ((0xffU 
                                                 & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U]) 
                                                - (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[9U] 
                                                       << 0x10U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                         >> 0x10U))))))));
    VL_EXTEND_WW(120,108, __Vtemp214, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp217, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp220, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp223, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5282_o 
        = (((QData)((IData)(((0xff800000U & (((0xffU 
                                               & ((__Vtemp217[1U] 
                                                   << 4U) 
                                                  | (__Vtemp217[0U] 
                                                     >> 0x1cU))) 
                                              * (0xffU 
                                                 & ((__Vtemp223[1U] 
                                                     << 4U) 
                                                    | (__Vtemp223[0U] 
                                                       >> 0x1cU)))) 
                                             << 0xfU)) 
                             | ((0x7ff000U & ((((((
                                                   (0x1feU 
                                                    & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                       << 1U)) 
                                                   - 
                                                   (0x1feU 
                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                        << 0x19U) 
                                                       | (0x1fffffeU 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                             >> 7U))))) 
                                                  - 
                                                  (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                       << 0x18U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                         >> 8U)))) 
                                                 + 
                                                 (0xffU 
                                                  & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U])) 
                                                + (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                       << 0x10U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U] 
                                                         >> 0x10U)))) 
                                               - (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[9U] 
                                                      << 8U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                        >> 0x18U)))) 
                                              << 0xcU)) 
                                | (0xfffU & (((((0x1feU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[9U] 
                                                     << 9U) 
                                                    | (0x1feU 
                                                       & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                          >> 0x17U)))) 
                                                - (0x3fcU 
                                                   & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                      << 2U))) 
                                               - (0xffU 
                                                  & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U])) 
                                              + (0x3fcU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                     << 0x1aU) 
                                                    | (0x3fffffcU 
                                                       & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                          >> 6U))))) 
                                             - (0xffU 
                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                    << 0x10U) 
                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[6U] 
                                                      >> 0x10U))))))))) 
            << 9U) | (QData)((IData)((0x1ffU & ((0xffU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                     << 0x18U) 
                                                    | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                       >> 8U))) 
                                                - (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[9U] 
                                                       << 8U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                         >> 0x18U))))))));
    VL_EXTEND_WW(120,108, __Vtemp226, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp229, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp232, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp235, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp238, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp241, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp244, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp247, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp250, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp253, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp256, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp259, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp262, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp265, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp268, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9440_o 
        = (0xffffffffffULL & ((8U & ((IData)(0xffU) 
                                     - ((0xfff00000U 
                                         & (__Vtemp226[3U] 
                                            << 0x14U)) 
                                        | (__Vtemp226[2U] 
                                           >> 0xcU))))
                               ? ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp229[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp229[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp232[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp232[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp235[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x14U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x13U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x12U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x13U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x12U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x11U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp238[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x12U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x11U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x10U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x10U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xfU])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp241[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp241[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp244[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xfU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xeU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xdU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xeU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xdU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xcU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp247[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xdU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xcU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xbU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xbU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xaU]))))))
                               : ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp250[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp250[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp253[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp253[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp256[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xaU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[9U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[8U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[9U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[8U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[7U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp259[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[8U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[7U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[6U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[6U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[5U])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp262[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp262[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp265[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[5U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[4U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[3U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[4U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[3U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[2U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp268[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[3U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[2U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[1U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[1U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0U]))))))));
    VL_EXTEND_WW(120,108, __Vtemp271, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp274, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp277, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp280, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp283, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp286, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp289, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp292, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp295, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp298, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp301, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp304, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp307, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp310, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp313, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9442_o 
        = (0xffffffffffULL & ((8U & ((IData)(0xffU) 
                                     - ((0xfff00000U 
                                         & (__Vtemp271[3U] 
                                            << 0x14U)) 
                                        | (__Vtemp271[2U] 
                                           >> 0xcU))))
                               ? ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp274[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp274[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp277[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp277[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp280[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x28U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x27U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x26U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x27U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x26U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x25U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp283[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x26U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x25U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x24U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x24U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x23U])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp286[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp286[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp289[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x23U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x22U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x21U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x22U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x21U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x20U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp292[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x21U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x20U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x1fU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x1fU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x1eU]))))))
                               : ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp295[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp295[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp298[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp298[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp301[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x1eU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x1dU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x1cU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x1dU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x1cU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x1bU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp304[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x1cU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x1bU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x1aU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x1aU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x19U])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp307[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp307[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp310[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x19U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x18U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x17U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x18U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x17U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x16U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp313[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x17U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x16U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x15U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x15U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x14U]))))))));
    VL_EXTEND_WW(120,108, __Vtemp316, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp319, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp322, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp325, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp328, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp331, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp334, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp337, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp340, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp343, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp346, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp349, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp352, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp355, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp358, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9444_o 
        = (0xffffffffffULL & ((8U & ((IData)(0xffU) 
                                     - ((0xfff00000U 
                                         & (__Vtemp316[3U] 
                                            << 0x14U)) 
                                        | (__Vtemp316[2U] 
                                           >> 0xcU))))
                               ? ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp319[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp319[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp322[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp322[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp325[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x3cU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x3bU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x3aU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x3bU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x3aU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x39U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp328[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x3aU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x39U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x38U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x38U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x37U])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp331[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp331[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp334[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x37U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x36U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x35U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x36U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x35U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x34U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp337[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x35U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x34U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x33U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x33U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x32U]))))))
                               : ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp340[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp340[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp343[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp343[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp346[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x32U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x31U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x30U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x31U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x30U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x2fU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp349[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x30U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x2fU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x2eU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x2eU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x2dU])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp352[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp352[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp355[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x2dU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x2cU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x2bU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x2cU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x2bU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x2aU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp358[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x2bU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x2aU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x29U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x29U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x28U]))))))));
}
