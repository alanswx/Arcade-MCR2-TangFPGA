// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsynth_top.h for the primary calling header

#include "Vsynth_top.h"
#include "Vsynth_top__Syms.h"

VL_INLINE_OPT void Vsynth_top::_sequent__TOP__13(Vsynth_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth_top::_sequent__TOP__13\n"); );
    Vsynth_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8214_q) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8096_o 
            = (0x3fU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8464_q)
                         ? 0U : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8467_q)
                                  ? ((0xcU == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8097_q))
                                      ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8097_q)
                                      : ((IData)(1U) 
                                         + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8097_q)))
                                  : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8097_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8466_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8464_q) 
               | ((~ ((0xcU == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8097_q)) 
                      & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8467_q))) 
                  & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8467_q)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8460_o 
            = (0x1ffffffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8464_q)
                              ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8299_q) 
                                 << 0xcU) : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8467_q)
                                              ? ((0x1fff000U 
                                                  & (((0x1000000U 
                                                       & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8461_q)
                                                       ? 
                                                      ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8461_q 
                                                        >> 0xbU) 
                                                       + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8458_q))
                                                       : 
                                                      ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8461_q 
                                                        >> 0xbU) 
                                                       - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8458_q))) 
                                                     << 0xcU)) 
                                                 | ((0xffeU 
                                                     & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8461_q 
                                                        << 1U)) 
                                                    | (1U 
                                                       & (~ 
                                                          (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8461_q 
                                                           >> 0x18U)))))
                                              : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8299_q) 
                                                 << 0xcU))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8457_o 
            = (0x1fffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8053_q) 
                          << 1U));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8283_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8464_q)
                ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q)
                : (((0xcU == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8097_q)) 
                    & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8467_q))
                    ? ((0xffeU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8461_q 
                                  << 1U)) | (1U & (~ 
                                                   (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8461_q 
                                                    >> 0x18U))))
                    : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q)));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8096_o 
            = (0x3fU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8097_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8466_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8467_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8460_o 
            = (0x1ffffffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8461_q);
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8457_o 
            = (0x1fffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8458_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8283_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o 
        = (1U & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7988_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o 
        = (1U & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8214_q)));
}

VL_INLINE_OPT void Vsynth_top::_sequent__TOP__14(Vsynth_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth_top::_sequent__TOP__14\n"); );
    Vsynth_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7653_o 
        = (1U & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1405_o)
                  ? (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7654_q))
                  : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7654_q)));
}

void Vsynth_top::_eval(Vsynth_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth_top::_eval\n"); );
    Vsynth_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((((IData)(vlTOPp->o_clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__o_clk))) 
         | ((IData)(vlTOPp->__VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n114_o) 
            & (~ (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n114_o))))) {
        vlTOPp->_sequent__TOP__2(vlSymsp);
    }
    if (((IData)(vlTOPp->o_clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__o_clk)))) {
        vlTOPp->_sequent__TOP__3(vlSymsp);
        vlTOPp->_sequent__TOP__4(vlSymsp);
    }
    if ((((IData)(vlTOPp->i_clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__i_clk))) 
         | ((IData)(vlTOPp->__VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o) 
            & (~ (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o))))) {
        vlTOPp->_sequent__TOP__5(vlSymsp);
    }
    if (((IData)(vlTOPp->i_clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__i_clk)))) {
        vlTOPp->_sequent__TOP__6(vlSymsp);
    }
    if ((((IData)(vlTOPp->i_clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__i_clk))) 
         | ((IData)(vlTOPp->__VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n114_o) 
            & (~ (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n114_o))))) {
        vlTOPp->_sequent__TOP__7(vlSymsp);
    }
    if ((((IData)(vlTOPp->o_clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__o_clk))) 
         | ((IData)(vlTOPp->__VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o) 
            & (~ (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o))))) {
        vlTOPp->_sequent__TOP__8(vlSymsp);
    }
    if ((((IData)(vlTOPp->o_clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__o_clk))) 
         | ((IData)(vlTOPp->__VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o) 
            & (~ (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o))))) {
        vlTOPp->_sequent__TOP__9(vlSymsp);
    }
    vlTOPp->_combo__TOP__12(vlSymsp);
    if ((((IData)(vlTOPp->o_clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__o_clk))) 
         | ((IData)(vlTOPp->__VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n114_o) 
            & (~ (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n114_o))))) {
        vlTOPp->_sequent__TOP__13(vlSymsp);
    }
    if ((((IData)(vlTOPp->i_clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__i_clk))) 
         | ((IData)(vlTOPp->__VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o) 
            & (~ (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o))))) {
        vlTOPp->_sequent__TOP__14(vlSymsp);
    }
    // Final
    vlTOPp->__Vclklast__TOP__o_clk = vlTOPp->o_clk;
    vlTOPp->__Vclklast__TOP____VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n114_o 
        = vlTOPp->__VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n114_o;
    vlTOPp->__Vclklast__TOP__i_clk = vlTOPp->i_clk;
    vlTOPp->__Vclklast__TOP____VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o 
        = vlTOPp->__VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o;
    vlTOPp->__Vclklast__TOP____VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o 
        = vlTOPp->__VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o;
    vlTOPp->__Vclklast__TOP____VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o 
        = vlTOPp->__VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o;
    vlTOPp->__VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n114_o 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n114_o;
    vlTOPp->__VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o;
    vlTOPp->__VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o;
    vlTOPp->__VinpClk__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o;
}

VL_INLINE_OPT QData Vsynth_top::_change_request(Vsynth_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth_top::_change_request\n"); );
    Vsynth_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vsynth_top::_change_request_1(Vsynth_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth_top::_change_request_1\n"); );
    Vsynth_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    __req |= ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n114_o ^ vlTOPp->__Vchglast__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n114_o)
         | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o ^ vlTOPp->__Vchglast__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)
         | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o ^ vlTOPp->__Vchglast__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o)
         | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o ^ vlTOPp->__Vchglast__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o));
    VL_DEBUG_IF( if(__req && ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n114_o ^ vlTOPp->__Vchglast__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n114_o))) VL_DBG_MSGF("        CHANGE: ../ascal_gw_synth480.v:463: synth_top.dut.u_ascal.n114_o\n"); );
    VL_DEBUG_IF( if(__req && ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o ^ vlTOPp->__Vchglast__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o))) VL_DBG_MSGF("        CHANGE: ../ascal_gw_synth480.v:466: synth_top.dut.u_ascal.n136_o\n"); );
    VL_DEBUG_IF( if(__req && ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o ^ vlTOPp->__Vchglast__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o))) VL_DBG_MSGF("        CHANGE: ../ascal_gw_synth480.v:1277: synth_top.dut.u_ascal.n1742_o\n"); );
    VL_DEBUG_IF( if(__req && ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o ^ vlTOPp->__Vchglast__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o))) VL_DBG_MSGF("        CHANGE: ../ascal_gw_synth480.v:1464: synth_top.dut.u_ascal.n2219_o\n"); );
    // Final
    vlTOPp->__Vchglast__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n114_o 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n114_o;
    vlTOPp->__Vchglast__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o;
    vlTOPp->__Vchglast__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o;
    vlTOPp->__Vchglast__TOP__synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o;
    return __req;
}

#ifdef VL_DEBUG
void Vsynth_top::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth_top::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((i_clk & 0xfeU))) {
        Verilated::overWidthError("i_clk");}
    if (VL_UNLIKELY((o_clk & 0xfeU))) {
        Verilated::overWidthError("o_clk");}
    if (VL_UNLIKELY((reset_na & 0xfeU))) {
        Verilated::overWidthError("reset_na");}
}
#endif  // VL_DEBUG
