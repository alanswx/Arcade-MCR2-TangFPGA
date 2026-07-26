// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsynth_top.h for the primary calling header

#include "Vsynth_top.h"
#include "Vsynth_top__Syms.h"

VL_INLINE_OPT void Vsynth_top::_sequent__TOP__4(Vsynth_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth_top::_sequent__TOP__4\n"); );
    Vsynth_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VlWide<4>/*127:0*/ __Vtemp361;
    VlWide<4>/*127:0*/ __Vtemp364;
    VlWide<4>/*127:0*/ __Vtemp367;
    VlWide<4>/*127:0*/ __Vtemp370;
    VlWide<4>/*127:0*/ __Vtemp373;
    VlWide<4>/*127:0*/ __Vtemp376;
    VlWide<4>/*127:0*/ __Vtemp379;
    VlWide<4>/*127:0*/ __Vtemp382;
    VlWide<4>/*127:0*/ __Vtemp385;
    VlWide<4>/*127:0*/ __Vtemp388;
    VlWide<4>/*127:0*/ __Vtemp391;
    VlWide<4>/*127:0*/ __Vtemp394;
    VlWide<4>/*127:0*/ __Vtemp397;
    VlWide<4>/*127:0*/ __Vtemp400;
    VlWide<4>/*127:0*/ __Vtemp403;
    VlWide<4>/*127:0*/ __Vtemp406;
    VlWide<4>/*127:0*/ __Vtemp409;
    VlWide<4>/*127:0*/ __Vtemp412;
    VlWide<4>/*127:0*/ __Vtemp415;
    VlWide<4>/*127:0*/ __Vtemp418;
    VlWide<4>/*127:0*/ __Vtemp421;
    VlWide<4>/*127:0*/ __Vtemp424;
    VlWide<4>/*127:0*/ __Vtemp427;
    VlWide<4>/*127:0*/ __Vtemp430;
    VlWide<4>/*127:0*/ __Vtemp433;
    VlWide<4>/*127:0*/ __Vtemp436;
    VlWide<4>/*127:0*/ __Vtemp439;
    VlWide<4>/*127:0*/ __Vtemp442;
    VlWide<4>/*127:0*/ __Vtemp445;
    VlWide<4>/*127:0*/ __Vtemp448;
    VlWide<4>/*127:0*/ __Vtemp451;
    VlWide<4>/*127:0*/ __Vtemp454;
    VlWide<4>/*127:0*/ __Vtemp457;
    VlWide<4>/*127:0*/ __Vtemp460;
    VlWide<4>/*127:0*/ __Vtemp463;
    VlWide<4>/*127:0*/ __Vtemp466;
    VlWide<4>/*127:0*/ __Vtemp469;
    VlWide<4>/*127:0*/ __Vtemp472;
    VlWide<4>/*127:0*/ __Vtemp475;
    VlWide<4>/*127:0*/ __Vtemp478;
    VlWide<4>/*127:0*/ __Vtemp481;
    VlWide<4>/*127:0*/ __Vtemp484;
    VlWide<4>/*127:0*/ __Vtemp487;
    VlWide<4>/*127:0*/ __Vtemp490;
    VlWide<4>/*127:0*/ __Vtemp493;
    VlWide<4>/*127:0*/ __Vtemp496;
    VlWide<4>/*127:0*/ __Vtemp499;
    VlWide<4>/*127:0*/ __Vtemp502;
    VlWide<4>/*127:0*/ __Vtemp505;
    VlWide<4>/*127:0*/ __Vtemp508;
    VlWide<4>/*127:0*/ __Vtemp511;
    VlWide<4>/*127:0*/ __Vtemp514;
    VlWide<4>/*127:0*/ __Vtemp517;
    VlWide<4>/*127:0*/ __Vtemp520;
    VlWide<4>/*127:0*/ __Vtemp523;
    VlWide<4>/*127:0*/ __Vtemp526;
    VlWide<4>/*127:0*/ __Vtemp529;
    VlWide<4>/*127:0*/ __Vtemp532;
    VlWide<4>/*127:0*/ __Vtemp535;
    VlWide<4>/*127:0*/ __Vtemp538;
    VlWide<4>/*127:0*/ __Vtemp541;
    VlWide<4>/*127:0*/ __Vtemp544;
    VlWide<4>/*127:0*/ __Vtemp547;
    VlWide<4>/*127:0*/ __Vtemp550;
    VlWide<4>/*127:0*/ __Vtemp553;
    VlWide<4>/*127:0*/ __Vtemp556;
    VlWide<4>/*127:0*/ __Vtemp559;
    VlWide<4>/*127:0*/ __Vtemp562;
    VlWide<4>/*127:0*/ __Vtemp565;
    VlWide<4>/*127:0*/ __Vtemp568;
    VlWide<4>/*127:0*/ __Vtemp571;
    VlWide<4>/*127:0*/ __Vtemp574;
    VlWide<4>/*127:0*/ __Vtemp577;
    VlWide<4>/*127:0*/ __Vtemp580;
    VlWide<4>/*127:0*/ __Vtemp583;
    VlWide<4>/*127:0*/ __Vtemp586;
    VlWide<4>/*127:0*/ __Vtemp589;
    VlWide<4>/*127:0*/ __Vtemp592;
    VlWide<4>/*127:0*/ __Vtemp595;
    VlWide<4>/*127:0*/ __Vtemp598;
    VlWide<4>/*127:0*/ __Vtemp601;
    VlWide<4>/*127:0*/ __Vtemp604;
    VlWide<4>/*127:0*/ __Vtemp607;
    VlWide<4>/*127:0*/ __Vtemp610;
    VlWide<4>/*127:0*/ __Vtemp613;
    VlWide<4>/*127:0*/ __Vtemp616;
    VlWide<4>/*127:0*/ __Vtemp619;
    VlWide<4>/*127:0*/ __Vtemp622;
    VlWide<4>/*127:0*/ __Vtemp625;
    VlWide<4>/*127:0*/ __Vtemp628;
    VlWide<4>/*127:0*/ __Vtemp631;
    VlWide<4>/*127:0*/ __Vtemp634;
    VlWide<4>/*127:0*/ __Vtemp637;
    VlWide<4>/*127:0*/ __Vtemp640;
    VlWide<4>/*127:0*/ __Vtemp643;
    VlWide<4>/*127:0*/ __Vtemp646;
    VlWide<4>/*127:0*/ __Vtemp649;
    VlWide<4>/*127:0*/ __Vtemp652;
    VlWide<4>/*127:0*/ __Vtemp655;
    VlWide<4>/*127:0*/ __Vtemp658;
    VlWide<4>/*127:0*/ __Vtemp661;
    VlWide<4>/*127:0*/ __Vtemp664;
    VlWide<4>/*127:0*/ __Vtemp667;
    VlWide<4>/*127:0*/ __Vtemp670;
    VlWide<4>/*127:0*/ __Vtemp673;
    VlWide<4>/*127:0*/ __Vtemp676;
    VlWide<4>/*127:0*/ __Vtemp679;
    VlWide<4>/*127:0*/ __Vtemp682;
    VlWide<4>/*127:0*/ __Vtemp685;
    VlWide<4>/*127:0*/ __Vtemp688;
    VlWide<4>/*127:0*/ __Vtemp691;
    VlWide<4>/*127:0*/ __Vtemp694;
    VlWide<4>/*127:0*/ __Vtemp697;
    VlWide<4>/*127:0*/ __Vtemp700;
    VlWide<4>/*127:0*/ __Vtemp703;
    VlWide<4>/*127:0*/ __Vtemp706;
    VlWide<4>/*127:0*/ __Vtemp709;
    VlWide<4>/*127:0*/ __Vtemp712;
    VlWide<4>/*127:0*/ __Vtemp715;
    VlWide<4>/*127:0*/ __Vtemp718;
    VlWide<4>/*127:0*/ __Vtemp721;
    VlWide<4>/*127:0*/ __Vtemp724;
    VlWide<4>/*127:0*/ __Vtemp727;
    VlWide<4>/*127:0*/ __Vtemp730;
    VlWide<4>/*127:0*/ __Vtemp733;
    VlWide<4>/*127:0*/ __Vtemp736;
    VlWide<4>/*127:0*/ __Vtemp739;
    VlWide<4>/*127:0*/ __Vtemp742;
    VlWide<4>/*127:0*/ __Vtemp745;
    VlWide<4>/*127:0*/ __Vtemp748;
    VlWide<4>/*127:0*/ __Vtemp751;
    VlWide<4>/*127:0*/ __Vtemp754;
    VlWide<4>/*127:0*/ __Vtemp757;
    VlWide<4>/*127:0*/ __Vtemp760;
    VlWide<4>/*127:0*/ __Vtemp763;
    VlWide<4>/*127:0*/ __Vtemp766;
    VlWide<4>/*127:0*/ __Vtemp769;
    VlWide<4>/*127:0*/ __Vtemp772;
    VlWide<4>/*127:0*/ __Vtemp775;
    VlWide<4>/*127:0*/ __Vtemp778;
    VlWide<4>/*127:0*/ __Vtemp781;
    VlWide<4>/*127:0*/ __Vtemp784;
    VlWide<4>/*127:0*/ __Vtemp787;
    VlWide<4>/*127:0*/ __Vtemp790;
    VlWide<4>/*127:0*/ __Vtemp793;
    VlWide<4>/*127:0*/ __Vtemp796;
    VlWide<4>/*127:0*/ __Vtemp799;
    VlWide<4>/*127:0*/ __Vtemp802;
    VlWide<4>/*127:0*/ __Vtemp805;
    VlWide<4>/*127:0*/ __Vtemp808;
    VlWide<4>/*127:0*/ __Vtemp811;
    VlWide<4>/*127:0*/ __Vtemp814;
    VlWide<4>/*127:0*/ __Vtemp817;
    VlWide<4>/*127:0*/ __Vtemp820;
    VlWide<4>/*127:0*/ __Vtemp823;
    VlWide<4>/*127:0*/ __Vtemp826;
    VlWide<4>/*127:0*/ __Vtemp829;
    VlWide<4>/*127:0*/ __Vtemp832;
    VlWide<4>/*127:0*/ __Vtemp835;
    VlWide<4>/*127:0*/ __Vtemp838;
    VlWide<4>/*127:0*/ __Vtemp841;
    VlWide<4>/*127:0*/ __Vtemp844;
    VlWide<4>/*127:0*/ __Vtemp847;
    VlWide<4>/*127:0*/ __Vtemp850;
    VlWide<4>/*127:0*/ __Vtemp853;
    VlWide<4>/*127:0*/ __Vtemp856;
    VlWide<4>/*127:0*/ __Vtemp859;
    VlWide<4>/*127:0*/ __Vtemp862;
    VlWide<4>/*127:0*/ __Vtemp865;
    VlWide<4>/*127:0*/ __Vtemp868;
    VlWide<4>/*127:0*/ __Vtemp871;
    VlWide<4>/*127:0*/ __Vtemp874;
    VlWide<4>/*127:0*/ __Vtemp877;
    VlWide<4>/*127:0*/ __Vtemp880;
    VlWide<4>/*127:0*/ __Vtemp883;
    VlWide<4>/*127:0*/ __Vtemp886;
    VlWide<4>/*127:0*/ __Vtemp889;
    VlWide<4>/*127:0*/ __Vtemp892;
    VlWide<4>/*127:0*/ __Vtemp895;
    VlWide<4>/*127:0*/ __Vtemp898;
    VlWide<4>/*127:0*/ __Vtemp901;
    VlWide<4>/*127:0*/ __Vtemp904;
    VlWide<4>/*127:0*/ __Vtemp907;
    VlWide<4>/*127:0*/ __Vtemp910;
    VlWide<4>/*127:0*/ __Vtemp913;
    VlWide<4>/*127:0*/ __Vtemp916;
    VlWide<4>/*127:0*/ __Vtemp919;
    VlWide<4>/*127:0*/ __Vtemp922;
    VlWide<4>/*127:0*/ __Vtemp925;
    VlWide<4>/*127:0*/ __Vtemp928;
    VlWide<4>/*127:0*/ __Vtemp931;
    VlWide<4>/*127:0*/ __Vtemp934;
    VlWide<4>/*127:0*/ __Vtemp937;
    VlWide<4>/*127:0*/ __Vtemp940;
    VlWide<4>/*127:0*/ __Vtemp943;
    VlWide<4>/*127:0*/ __Vtemp948;
    VlWide<4>/*127:0*/ __Vtemp951;
    VlWide<4>/*127:0*/ __Vtemp954;
    VlWide<4>/*127:0*/ __Vtemp957;
    VlWide<4>/*127:0*/ __Vtemp960;
    VlWide<4>/*127:0*/ __Vtemp963;
    VlWide<4>/*127:0*/ __Vtemp966;
    VlWide<4>/*127:0*/ __Vtemp969;
    VlWide<4>/*127:0*/ __Vtemp972;
    VlWide<4>/*127:0*/ __Vtemp975;
    VlWide<4>/*127:0*/ __Vtemp978;
    VlWide<4>/*127:0*/ __Vtemp981;
    VlWide<4>/*127:0*/ __Vtemp984;
    VlWide<4>/*127:0*/ __Vtemp987;
    VlWide<4>/*127:0*/ __Vtemp990;
    VlWide<3>/*95:0*/ __Vtemp1005;
    VlWide<3>/*95:0*/ __Vtemp1013;
    VlWide<3>/*95:0*/ __Vtemp1025;
    VlWide<3>/*95:0*/ __Vtemp1027;
    VlWide<4>/*127:0*/ __Vtemp1029;
    VlWide<4>/*127:0*/ __Vtemp1032;
    VlWide<4>/*127:0*/ __Vtemp1035;
    VlWide<4>/*127:0*/ __Vtemp1038;
    VlWide<4>/*127:0*/ __Vtemp1041;
    VlWide<4>/*127:0*/ __Vtemp1044;
    VlWide<3>/*95:0*/ __Vtemp1046;
    VlWide<3>/*95:0*/ __Vtemp1047;
    VlWide<3>/*95:0*/ __Vtemp1051;
    VlWide<3>/*95:0*/ __Vtemp1052;
    // Body
    VL_EXTEND_WW(120,108, __Vtemp361, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp364, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp367, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp370, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp373, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp376, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp379, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp382, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp385, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp388, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp391, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp394, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp397, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp400, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp403, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9446_o 
        = (0xffffffffffULL & ((8U & ((IData)(0xffU) 
                                     - ((0xfff00000U 
                                         & (__Vtemp361[3U] 
                                            << 0x14U)) 
                                        | (__Vtemp361[2U] 
                                           >> 0xcU))))
                               ? ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp364[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp364[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp367[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp367[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp370[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x50U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x4fU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x4eU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x4fU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x4eU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x4dU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp373[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x4eU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x4dU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x4cU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x4cU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x4bU])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp376[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp376[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp379[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x4bU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x4aU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x49U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x4aU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x49U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x48U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp382[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x49U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x48U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x47U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x47U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x46U]))))))
                               : ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp385[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp385[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp388[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp388[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp391[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x46U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x45U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x44U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x45U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x44U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x43U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp394[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x44U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x43U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x42U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x42U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x41U])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp397[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp397[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp400[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x41U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x40U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x3fU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x40U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x3fU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x3eU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp403[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x3fU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x3eU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x3dU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x3dU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x3cU]))))))));
    VL_EXTEND_WW(120,108, __Vtemp406, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp409, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp412, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp415, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp418, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp421, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp424, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp427, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp430, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp433, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp436, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp439, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp442, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp445, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp448, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9448_o 
        = (0xffffffffffULL & ((8U & ((IData)(0xffU) 
                                     - ((0xfff00000U 
                                         & (__Vtemp406[3U] 
                                            << 0x14U)) 
                                        | (__Vtemp406[2U] 
                                           >> 0xcU))))
                               ? ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp409[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp409[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp412[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp412[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp415[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x64U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x63U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x62U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x63U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x62U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x61U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp418[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x62U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x61U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x60U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x60U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x5fU])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp421[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp421[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp424[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x5fU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x5eU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x5dU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x5eU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x5dU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x5cU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp427[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x5dU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x5cU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x5bU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x5bU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x5aU]))))))
                               : ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp430[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp430[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp433[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp433[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp436[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x5aU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x59U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x58U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x59U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x58U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x57U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp439[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x58U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x57U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x56U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x56U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x55U])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp442[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp442[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp445[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x55U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x54U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x53U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x54U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x53U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x52U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp448[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x53U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x52U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x51U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x51U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x50U]))))))));
    VL_EXTEND_WW(120,108, __Vtemp451, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp454, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp457, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp460, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp463, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp466, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp469, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp472, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp475, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp478, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp481, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp484, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp487, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp490, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp493, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9450_o 
        = (0xffffffffffULL & ((8U & ((IData)(0xffU) 
                                     - ((0xfff00000U 
                                         & (__Vtemp451[3U] 
                                            << 0x14U)) 
                                        | (__Vtemp451[2U] 
                                           >> 0xcU))))
                               ? ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp454[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp454[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp457[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp457[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp460[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x78U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x77U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x76U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x77U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x76U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x75U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp463[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x76U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x75U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x74U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x74U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x73U])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp466[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp466[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp469[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x73U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x72U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x71U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x72U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x71U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x70U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp472[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x71U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x70U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x6fU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x6fU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x6eU]))))))
                               : ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp475[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp475[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp478[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp478[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp481[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x6eU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x6dU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x6cU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x6dU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x6cU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x6bU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp484[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x6cU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x6bU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x6aU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x6aU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x69U])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp487[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp487[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp490[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x69U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x68U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x67U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x68U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x67U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x66U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp493[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x67U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x66U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x65U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x65U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x64U]))))))));
    VL_EXTEND_WW(120,108, __Vtemp496, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp499, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp502, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp505, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp508, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp511, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp514, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp517, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp520, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp523, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp526, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp529, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp532, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp535, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp538, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9452_o 
        = (0xffffffffffULL & ((8U & ((IData)(0xffU) 
                                     - ((0xfff00000U 
                                         & (__Vtemp496[3U] 
                                            << 0x14U)) 
                                        | (__Vtemp496[2U] 
                                           >> 0xcU))))
                               ? ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp499[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp499[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp502[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp502[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp505[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x8cU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x8bU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x8aU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x8bU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x8aU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x89U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp508[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x8aU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x89U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x88U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x88U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x87U])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp511[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp511[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp514[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x87U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x86U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x85U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x86U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x85U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x84U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp517[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x85U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x84U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x83U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x83U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x82U]))))))
                               : ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp520[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp520[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp523[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp523[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp526[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x82U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x81U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x80U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x81U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x80U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x7fU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp529[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x80U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x7fU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x7eU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x7eU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x7dU])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp532[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp532[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp535[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x7dU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x7cU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x7bU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x7cU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x7bU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x7aU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp538[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x7bU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x7aU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x79U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x79U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x78U]))))))));
    VL_EXTEND_WW(120,108, __Vtemp541, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp544, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp547, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp550, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp553, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp556, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp559, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp562, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp565, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp568, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp571, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp574, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp577, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp580, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp583, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9454_o 
        = (0xffffffffffULL & ((8U & ((IData)(0xffU) 
                                     - ((0xfff00000U 
                                         & (__Vtemp541[3U] 
                                            << 0x14U)) 
                                        | (__Vtemp541[2U] 
                                           >> 0xcU))))
                               ? ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp544[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp544[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp547[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp547[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp550[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa0U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x9fU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x9eU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x9fU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x9eU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x9dU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp553[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x9eU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x9dU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x9cU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x9cU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x9bU])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp556[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp556[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp559[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x9bU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x9aU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x99U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x9aU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x99U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x98U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp562[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x99U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x98U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x97U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x97U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x96U]))))))
                               : ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp565[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp565[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp568[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp568[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp571[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x96U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x95U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x94U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x95U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x94U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x93U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp574[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x94U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x93U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x92U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x92U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x91U])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp577[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp577[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp580[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x91U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x90U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x8fU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x90U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x8fU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x8eU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp583[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x8fU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x8eU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x8dU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x8dU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x8cU]))))))));
    VL_EXTEND_WW(120,108, __Vtemp586, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp589, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp592, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp595, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp598, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp601, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp604, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp607, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp610, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp613, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp616, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp619, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp622, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp625, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp628, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9456_o 
        = (0xffffffffffULL & ((8U & ((IData)(0xffU) 
                                     - ((0xfff00000U 
                                         & (__Vtemp586[3U] 
                                            << 0x14U)) 
                                        | (__Vtemp586[2U] 
                                           >> 0xcU))))
                               ? ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp589[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp589[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp592[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp592[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp595[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb4U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb3U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb2U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb3U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb2U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb1U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp598[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb2U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb1U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb0U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb0U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xafU])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp601[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp601[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp604[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xafU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xaeU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xadU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xaeU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xadU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xacU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp607[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xadU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xacU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xabU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xabU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xaaU]))))))
                               : ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp610[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp610[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp613[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp613[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp616[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xaaU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa9U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa8U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa9U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa8U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa7U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp619[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa8U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa7U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa6U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa6U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa5U])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp622[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp622[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp625[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa5U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa4U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa3U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa4U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa3U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa2U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp628[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa3U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa2U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa1U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa1U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xa0U]))))))));
    VL_EXTEND_WW(120,108, __Vtemp631, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp634, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp637, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp640, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp643, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp646, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp649, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp652, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp655, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp658, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp661, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp664, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp667, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp670, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp673, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9458_o 
        = (0xffffffffffULL & ((8U & ((IData)(0xffU) 
                                     - ((0xfff00000U 
                                         & (__Vtemp631[3U] 
                                            << 0x14U)) 
                                        | (__Vtemp631[2U] 
                                           >> 0xcU))))
                               ? ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp634[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp634[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp637[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp637[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp640[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc8U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc7U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc6U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc7U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc6U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc5U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp643[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc6U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc5U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc4U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc4U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc3U])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp646[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp646[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp649[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc3U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc2U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc1U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc2U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc1U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc0U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp652[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc1U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc0U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xbfU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xbfU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xbeU]))))))
                               : ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp655[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp655[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp658[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp658[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp661[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xbeU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xbdU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xbcU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xbdU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xbcU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xbbU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp664[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xbcU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xbbU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xbaU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xbaU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb9U])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp667[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp667[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp670[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb9U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb8U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb7U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb8U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb7U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb6U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp673[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb7U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb6U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb5U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb5U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xb4U]))))))));
    VL_EXTEND_WW(120,108, __Vtemp676, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp679, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp682, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp685, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp688, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp691, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp694, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp697, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp700, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp703, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp706, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp709, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp712, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp715, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp718, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9460_o 
        = (0xffffffffffULL & ((8U & ((IData)(0xffU) 
                                     - ((0xfff00000U 
                                         & (__Vtemp676[3U] 
                                            << 0x14U)) 
                                        | (__Vtemp676[2U] 
                                           >> 0xcU))))
                               ? ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp679[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp679[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp682[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp682[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp685[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xdcU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xdbU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xdaU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xdbU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xdaU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd9U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp688[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xdaU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd9U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd8U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd8U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd7U])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp691[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp691[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp694[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd7U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd6U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd5U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd6U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd5U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd4U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp697[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd5U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd4U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd3U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd3U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd2U]))))))
                               : ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp700[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp700[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp703[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp703[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp706[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd2U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd1U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd0U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd1U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd0U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xcfU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp709[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xd0U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xcfU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xceU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xceU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xcdU])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp712[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp712[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp715[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xcdU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xccU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xcbU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xccU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xcbU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xcaU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp718[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xcbU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xcaU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc9U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc9U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xc8U]))))))));
    VL_EXTEND_WW(120,108, __Vtemp721, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp724, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp727, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp730, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp733, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp736, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp739, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp742, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp745, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp748, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp751, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp754, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp757, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp760, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp763, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9462_o 
        = (0xffffffffffULL & ((8U & ((IData)(0xffU) 
                                     - ((0xfff00000U 
                                         & (__Vtemp721[3U] 
                                            << 0x14U)) 
                                        | (__Vtemp721[2U] 
                                           >> 0xcU))))
                               ? ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp724[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp724[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp727[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp727[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp730[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf0U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xefU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xeeU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xefU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xeeU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xedU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp733[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xeeU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xedU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xecU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xecU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xebU])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp736[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp736[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp739[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xebU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xeaU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe9U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xeaU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe9U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe8U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp742[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe9U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe8U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe7U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe7U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe6U]))))))
                               : ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp745[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp745[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp748[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp748[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp751[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe6U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe5U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe4U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe5U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe4U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe3U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp754[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe4U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe3U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe2U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe2U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe1U])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp757[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp757[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp760[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe1U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe0U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xdfU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xe0U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xdfU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xdeU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp763[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xdfU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xdeU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xddU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xddU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xdcU]))))))));
    VL_EXTEND_WW(120,108, __Vtemp766, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp769, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp772, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp775, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp778, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp781, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp784, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp787, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp790, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp793, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp796, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp799, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp802, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp805, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp808, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9464_o 
        = (0xffffffffffULL & ((8U & ((IData)(0xffU) 
                                     - ((0xfff00000U 
                                         & (__Vtemp766[3U] 
                                            << 0x14U)) 
                                        | (__Vtemp766[2U] 
                                           >> 0xcU))))
                               ? ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp769[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp769[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp772[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp772[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp775[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x104U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x103U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x102U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x103U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x102U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x101U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp778[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x102U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x101U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x100U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x100U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xffU])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp781[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp781[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp784[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xffU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xfeU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xfdU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xfeU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xfdU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xfcU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp787[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xfdU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xfcU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xfbU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xfbU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xfaU]))))))
                               : ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp790[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp790[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp793[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp793[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp796[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xfaU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf9U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf8U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf9U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf8U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf7U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp799[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf8U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf7U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf6U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf6U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf5U])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp802[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp802[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp805[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf5U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf4U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf3U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf4U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf3U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf2U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp808[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf3U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf2U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf1U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf1U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0xf0U]))))))));
    VL_EXTEND_WW(120,108, __Vtemp811, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp814, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp817, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp820, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp823, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp826, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp829, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp832, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp835, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp838, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp841, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp844, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp847, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp850, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp853, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9466_o 
        = (0xffffffffffULL & ((8U & ((IData)(0xffU) 
                                     - ((0xfff00000U 
                                         & (__Vtemp811[3U] 
                                            << 0x14U)) 
                                        | (__Vtemp811[2U] 
                                           >> 0xcU))))
                               ? ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp814[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp814[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp817[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp817[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp820[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x118U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x117U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x116U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x117U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x116U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x115U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp823[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x116U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x115U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x114U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x114U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x113U])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp826[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp826[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp829[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x113U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x112U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x111U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x112U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x111U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x110U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp832[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x111U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x110U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x10fU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x10fU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x10eU]))))))
                               : ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp835[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp835[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp838[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp838[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp841[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x10eU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x10dU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x10cU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x10dU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x10cU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x10bU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp844[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x10cU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x10bU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x10aU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x10aU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x109U])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp847[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp847[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp850[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x109U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x108U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x107U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x108U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x107U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x106U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp853[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x107U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x106U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x105U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x105U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x104U]))))))));
    VL_EXTEND_WW(120,108, __Vtemp856, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp859, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp862, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp865, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp868, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp871, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp874, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp877, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp880, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp883, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp886, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp889, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp892, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp895, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp898, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9468_o 
        = (0xffffffffffULL & ((8U & ((IData)(0xffU) 
                                     - ((0xfff00000U 
                                         & (__Vtemp856[3U] 
                                            << 0x14U)) 
                                        | (__Vtemp856[2U] 
                                           >> 0xcU))))
                               ? ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp859[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp859[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp862[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp862[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp865[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x12cU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x12bU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x12aU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x12bU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x12aU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x129U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp868[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x12aU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x129U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x128U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x128U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x127U])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp871[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp871[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp874[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x127U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x126U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x125U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x126U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x125U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x124U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp877[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x125U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x124U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x123U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x123U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x122U]))))))
                               : ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp880[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp880[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp883[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp883[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp886[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x122U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x121U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x120U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x121U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x120U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x11fU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp889[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x120U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x11fU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x11eU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x11eU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x11dU])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp892[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp892[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp895[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x11dU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x11cU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x11bU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x11cU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x11bU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x11aU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp898[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x11bU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x11aU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x119U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x119U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x118U]))))))));
    VL_EXTEND_WW(120,108, __Vtemp901, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp904, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp907, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp910, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp913, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp916, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp919, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp922, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp925, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp928, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp931, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp934, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp937, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp940, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp943, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9470_o 
        = (0xffffffffffULL & ((8U & ((IData)(0xffU) 
                                     - ((0xfff00000U 
                                         & (__Vtemp901[3U] 
                                            << 0x14U)) 
                                        | (__Vtemp901[2U] 
                                           >> 0xcU))))
                               ? ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp904[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp904[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp907[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp907[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp910[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x13fU])) 
                                               << 8U) 
                                              | ((QData)((IData)(
                                                                 vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x13eU])) 
                                                 >> 0x18U))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x13fU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x13eU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x13dU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp913[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x13eU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x13dU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x13cU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x13cU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x13bU])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp916[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp916[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp919[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x13bU])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x13aU])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x139U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x13aU])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x139U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x138U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp922[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x139U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x138U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x137U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x137U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x136U]))))))
                               : ((4U & ((IData)(0xffU) 
                                         - ((0xfff00000U 
                                             & (__Vtemp925[3U] 
                                                << 0x14U)) 
                                            | (__Vtemp925[2U] 
                                               >> 0xcU))))
                                   ? ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp928[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp928[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp931[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x136U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x135U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x134U])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x135U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x134U])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x133U])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp934[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x134U])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x133U])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x132U])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x132U])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x131U])))))
                                   : ((2U & ((IData)(3U) 
                                             - ((0xfff00000U 
                                                 & (__Vtemp937[3U] 
                                                    << 0x14U)) 
                                                | (__Vtemp937[2U] 
                                                   >> 0xcU))))
                                       ? ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp940[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x131U])) 
                                               << 0x28U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x130U])) 
                                                  << 8U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x12fU])) 
                                                    >> 0x18U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x130U])) 
                                               << 0x30U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x12fU])) 
                                                  << 0x10U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x12eU])) 
                                                    >> 0x10U))))
                                       : ((1U & ((IData)(1U) 
                                                 - 
                                                 (__Vtemp943[2U] 
                                                  >> 0xcU)))
                                           ? (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x12fU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x12eU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x12dU])) 
                                                    >> 8U)))
                                           : (((QData)((IData)(
                                                               vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x12dU])) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8515_q[0x12cU]))))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[0U] 
        = (IData)(((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5136_o 
                    << 8U) | (QData)((IData)((0xffU 
                                              & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                  << 0x10U) 
                                                 | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                    >> 0x10U)))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[1U] 
        = ((0xfffe0000U & ((IData)(((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5209_o 
                                     << 8U) | (QData)((IData)(
                                                              (0xffU 
                                                               & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                                   << 8U) 
                                                                  | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                                     >> 0x18U))))))) 
                           << 0x11U)) | (IData)((((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5136_o 
                                                   << 8U) 
                                                  | (QData)((IData)(
                                                                    (0xffU 
                                                                     & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                                         << 0x10U) 
                                                                        | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                                           >> 0x10U)))))) 
                                                 >> 0x20U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[2U] 
        = ((0x1ffffU & ((IData)(((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5209_o 
                                  << 8U) | (QData)((IData)(
                                                           (0xffU 
                                                            & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                                << 8U) 
                                                               | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                                  >> 0x18U))))))) 
                        >> 0xfU)) | (0xfffe0000U & 
                                     ((IData)((((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5209_o 
                                                 << 8U) 
                                                | (QData)((IData)(
                                                                  (0xffU 
                                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                                       << 8U) 
                                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                                         >> 0x18U)))))) 
                                               >> 0x20U)) 
                                      << 0x11U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[3U] 
        = ((0xfffffffcU & ((IData)(((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5282_o 
                                     << 8U) | (QData)((IData)(
                                                              (0xffU 
                                                               & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U]))))) 
                           << 2U)) | (0x1ffffU & ((IData)(
                                                          (((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5209_o 
                                                             << 8U) 
                                                            | (QData)((IData)(
                                                                              (0xffU 
                                                                               & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U] 
                                                                                << 8U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[7U] 
                                                                                >> 0x18U)))))) 
                                                           >> 0x20U)) 
                                                  >> 0xfU)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[4U] 
        = ((3U & ((IData)(((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5282_o 
                            << 8U) | (QData)((IData)(
                                                     (0xffU 
                                                      & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U]))))) 
                  >> 0x1eU)) | (0xfffffffcU & ((IData)(
                                                       (((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5282_o 
                                                          << 8U) 
                                                         | (QData)((IData)(
                                                                           (0xffU 
                                                                            & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8439_q[8U])))) 
                                                        >> 0x20U)) 
                                               << 2U)));
    VL_EXTEND_WW(120,108, __Vtemp948, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp951, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp954, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp957, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp960, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp963, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp966, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp969, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp972, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp975, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp978, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp981, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp984, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp987, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp990, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9480_o 
        = ((0x80U & ((IData)(0xffU) - ((0xfff00000U 
                                        & (__Vtemp948[3U] 
                                           << 0x14U)) 
                                       | (__Vtemp948[2U] 
                                          >> 0xcU))))
            ? ((0x40U & ((IData)(0xffU) - ((0xfff00000U 
                                            & (__Vtemp951[3U] 
                                               << 0x14U)) 
                                           | (__Vtemp951[2U] 
                                              >> 0xcU))))
                ? ((0x20U & ((IData)(0xffU) - ((0xfff00000U 
                                                & (__Vtemp954[3U] 
                                                   << 0x14U)) 
                                               | (__Vtemp954[2U] 
                                                  >> 0xcU))))
                    ? ((0x10U & ((IData)(0xffU) - (
                                                   (0xfff00000U 
                                                    & (__Vtemp957[3U] 
                                                       << 0x14U)) 
                                                   | (__Vtemp957[2U] 
                                                      >> 0xcU))))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9470_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9468_o)
                    : ((0x10U & ((IData)(0xffU) - (
                                                   (0xfff00000U 
                                                    & (__Vtemp960[3U] 
                                                       << 0x14U)) 
                                                   | (__Vtemp960[2U] 
                                                      >> 0xcU))))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9466_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9464_o))
                : ((0x20U & ((IData)(0xffU) - ((0xfff00000U 
                                                & (__Vtemp963[3U] 
                                                   << 0x14U)) 
                                               | (__Vtemp963[2U] 
                                                  >> 0xcU))))
                    ? ((0x10U & ((IData)(0xffU) - (
                                                   (0xfff00000U 
                                                    & (__Vtemp966[3U] 
                                                       << 0x14U)) 
                                                   | (__Vtemp966[2U] 
                                                      >> 0xcU))))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9462_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9460_o)
                    : ((0x10U & ((IData)(0xffU) - (
                                                   (0xfff00000U 
                                                    & (__Vtemp969[3U] 
                                                       << 0x14U)) 
                                                   | (__Vtemp969[2U] 
                                                      >> 0xcU))))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9458_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9456_o)))
            : ((0x40U & ((IData)(0xffU) - ((0xfff00000U 
                                            & (__Vtemp972[3U] 
                                               << 0x14U)) 
                                           | (__Vtemp972[2U] 
                                              >> 0xcU))))
                ? ((0x20U & ((IData)(0xffU) - ((0xfff00000U 
                                                & (__Vtemp975[3U] 
                                                   << 0x14U)) 
                                               | (__Vtemp975[2U] 
                                                  >> 0xcU))))
                    ? ((0x10U & ((IData)(0xffU) - (
                                                   (0xfff00000U 
                                                    & (__Vtemp978[3U] 
                                                       << 0x14U)) 
                                                   | (__Vtemp978[2U] 
                                                      >> 0xcU))))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9454_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9452_o)
                    : ((0x10U & ((IData)(0xffU) - (
                                                   (0xfff00000U 
                                                    & (__Vtemp981[3U] 
                                                       << 0x14U)) 
                                                   | (__Vtemp981[2U] 
                                                      >> 0xcU))))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9450_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9448_o))
                : ((0x20U & ((IData)(0xffU) - ((0xfff00000U 
                                                & (__Vtemp984[3U] 
                                                   << 0x14U)) 
                                               | (__Vtemp984[2U] 
                                                  >> 0xcU))))
                    ? ((0x10U & ((IData)(0xffU) - (
                                                   (0xfff00000U 
                                                    & (__Vtemp987[3U] 
                                                       << 0x14U)) 
                                                   | (__Vtemp987[2U] 
                                                      >> 0xcU))))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9446_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9444_o)
                    : ((0x10U & ((IData)(0xffU) - (
                                                   (0xfff00000U 
                                                    & (__Vtemp990[3U] 
                                                       << 0x14U)) 
                                                   | (__Vtemp990[2U] 
                                                      >> 0xcU))))
                        ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9442_o
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n9440_o))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7401_o 
        = (((3U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8018_q))) 
            << 2U) | ((((1U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8018_q))) 
                        | (2U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8018_q)))) 
                       << 1U) | (0U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8018_q)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6378_o 
        = (0xffU & ((0x800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q))
                     ? (~ ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                           >> 4U)) : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                      >> 4U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6593_o 
        = (((QData)((IData)(((0xff800000U & (((0xffU 
                                               & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                                  >> 4U)) 
                                              * (0xffU 
                                                 & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                                    >> 4U))) 
                                             << 0xfU)) 
                             | ((0x7ff000U & ((((((
                                                   (0x1feU 
                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                        << 0x11U) 
                                                       | (0x1fffeU 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                             >> 0xfU)))) 
                                                   - 
                                                   (0x1feU 
                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                        << 9U) 
                                                       | (0x1feU 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                             >> 0x17U))))) 
                                                  - 
                                                  (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                       << 8U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                         >> 0x18U)))) 
                                                 + 
                                                 (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                      << 0x10U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                        >> 0x10U)))) 
                                                + (0xffU 
                                                   & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U])) 
                                               - (0xffU 
                                                  & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                     >> 8U))) 
                                              << 0xcU)) 
                                | (0xfffU & (((((0x1feU 
                                                 & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                    >> 7U)) 
                                                - (0x3fcU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                       << 0x12U) 
                                                      | (0x3fffcU 
                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                            >> 0xeU))))) 
                                               - (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                      << 0x10U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                        >> 0x10U)))) 
                                              + (0x3fcU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                     << 0xaU) 
                                                    | (0x3fcU 
                                                       & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                          >> 0x16U))))) 
                                             - (0xffU 
                                                & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U]))))))) 
            << 9U) | (QData)((IData)((0x1ffU & ((0xffU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                     << 8U) 
                                                    | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                       >> 0x18U))) 
                                                - (0xffU 
                                                   & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                      >> 8U)))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6666_o 
        = (((QData)((IData)(((0xff800000U & (((0xffU 
                                               & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                                  >> 4U)) 
                                              * (0xffU 
                                                 & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                                    >> 4U))) 
                                             << 0xfU)) 
                             | ((0x7ff000U & ((((((
                                                   (0x1feU 
                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                        << 9U) 
                                                       | (0x1feU 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                             >> 0x17U)))) 
                                                   - 
                                                   (0x1feU 
                                                    & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                       << 1U))) 
                                                  - 
                                                  (0xffU 
                                                   & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U])) 
                                                 + 
                                                 (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                      << 8U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                        >> 0x18U)))) 
                                                + (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                       << 0x18U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                         >> 8U)))) 
                                               - (0xffU 
                                                  & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                     >> 0x10U))) 
                                              << 0xcU)) 
                                | (0xfffU & (((((0x1feU 
                                                 & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                    >> 0xfU)) 
                                                - (0x3fcU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                       << 0xaU) 
                                                      | (0x3fcU 
                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                            >> 0x16U))))) 
                                               - (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                      << 8U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                        >> 0x18U)))) 
                                              + (0x3fcU 
                                                 & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                    << 2U))) 
                                             - (0xffU 
                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                    << 0x18U) 
                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                      >> 8U))))))))) 
            << 9U) | (QData)((IData)((0x1ffU & ((0xffU 
                                                 & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U]) 
                                                - (0xffU 
                                                   & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                      >> 0x10U)))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6739_o 
        = (((QData)((IData)(((0xff800000U & (((0xffU 
                                               & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                                  >> 4U)) 
                                              * (0xffU 
                                                 & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                                    >> 4U))) 
                                             << 0xfU)) 
                             | ((0x7ff000U & ((((((
                                                   (0x1feU 
                                                    & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                       << 1U)) 
                                                   - 
                                                   (0x1feU 
                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                        << 0x19U) 
                                                       | (0x1fffffeU 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                             >> 7U))))) 
                                                  - 
                                                  (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                       << 0x18U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                         >> 8U)))) 
                                                 + 
                                                 (0xffU 
                                                  & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U])) 
                                                + (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                       << 0x10U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                         >> 0x10U)))) 
                                               - (0xffU 
                                                  & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                     >> 0x18U))) 
                                              << 0xcU)) 
                                | (0xfffU & (((((0x1feU 
                                                 & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                    >> 0x17U)) 
                                                - (0x3fcU 
                                                   & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                      << 2U))) 
                                               - (0xffU 
                                                  & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U])) 
                                              + (0x3fcU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                     << 0x1aU) 
                                                    | (0x3fffffcU 
                                                       & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                          >> 6U))))) 
                                             - (0xffU 
                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                    << 0x10U) 
                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                      >> 0x10U))))))))) 
            << 9U) | (QData)((IData)((0x1ffU & ((0xffU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                     << 0x18U) 
                                                    | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                       >> 8U))) 
                                                - (0xffU 
                                                   & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                      >> 0x18U)))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7132_o 
        = (((QData)((IData)((0x3ffU & ((((0xff800U 
                                          & ((- (IData)(
                                                        (1U 
                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[2U] 
                                                            >> 0x1fU)))) 
                                             << 0xbU)) 
                                         | (0x7ffU 
                                            & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[2U] 
                                               >> 0x15U))) 
                                        * (0xffU & 
                                           ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                            >> 4U))) 
                                       >> 9U)))) << 0x32U) 
           | (((QData)((IData)((0x3ffU & ((((0xff800U 
                                             & ((- (IData)(
                                                           (1U 
                                                            & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[2U] 
                                                               >> 0x14U)))) 
                                                << 0xbU)) 
                                            | (0x7ffU 
                                               & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[2U] 
                                                  >> 0xaU))) 
                                           * (0xffU 
                                              & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                                 >> 4U))) 
                                          >> 9U)))) 
               << 0x28U) | (((QData)((IData)((0x3ffU 
                                              & ((((0xff800U 
                                                    & ((- (IData)(
                                                                  (1U 
                                                                   & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[2U] 
                                                                      >> 9U)))) 
                                                       << 0xbU)) 
                                                   | (0x7ffU 
                                                      & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[2U] 
                                                          << 1U) 
                                                         | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[1U] 
                                                            >> 0x1fU)))) 
                                                  * 
                                                  (0xffU 
                                                   & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                                      >> 4U))) 
                                                 >> 9U)))) 
                             << 0x1eU) | (QData)((IData)(
                                                         ((0x3ff00000U 
                                                           & (((((0x200U 
                                                                  & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[0U] 
                                                                     >> 0x11U)) 
                                                                 | (0x1ffU 
                                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[1U] 
                                                                        << 0xeU) 
                                                                       | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[0U] 
                                                                          >> 0x12U)))) 
                                                                + 
                                                                (0xffU 
                                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8506_q[4U] 
                                                                     << 0x1eU) 
                                                                    | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8506_q[3U] 
                                                                       >> 2U)))) 
                                                               + 
                                                               ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[2U] 
                                                                 << 0xcU) 
                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[1U] 
                                                                   >> 0x14U))) 
                                                              << 0x14U)) 
                                                          | ((0xffc00U 
                                                              & (((((0x200U 
                                                                     & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[0U] 
                                                                        >> 8U)) 
                                                                    | (0x1ffU 
                                                                       & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[1U] 
                                                                           << 0x17U) 
                                                                          | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[0U] 
                                                                             >> 9U)))) 
                                                                   + 
                                                                   (0xffU 
                                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8506_q[2U] 
                                                                        << 0xfU) 
                                                                       | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8506_q[1U] 
                                                                          >> 0x11U)))) 
                                                                  + 
                                                                  ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[2U] 
                                                                    << 0x18U) 
                                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[1U] 
                                                                      >> 8U))) 
                                                                 << 0xaU)) 
                                                             | (0x3ffU 
                                                                & ((((0x200U 
                                                                      & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[0U] 
                                                                         << 1U)) 
                                                                     | (0x1ffU 
                                                                        & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[0U])) 
                                                                    + 
                                                                    (0xffU 
                                                                     & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8506_q[0U])) 
                                                                   + 
                                                                   ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[1U] 
                                                                     << 4U) 
                                                                    | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8511_q[0U] 
                                                                       >> 0x1cU)))))))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7432_o[0U] 
        = ((0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[1U] 
                           << 8U)) | ((0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U] 
                                                >> 0x18U)) 
                                      | (0xff00U & 
                                         (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[1U] 
                                          << 8U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7432_o[1U] 
        = ((0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[2U] 
                           << 8U)) | ((0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[1U] 
                                                >> 0x18U)) 
                                      | (0xff00U & 
                                         (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[2U] 
                                          << 8U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7432_o[2U] 
        = ((0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[3U] 
                           << 8U)) | ((0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[2U] 
                                                >> 0x18U)) 
                                      | (0xff00U & 
                                         (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[3U] 
                                          << 8U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7432_o[3U] 
        = ((0xff000000U & (((0x800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q))
                             ? ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[1U] 
                                 << 8U) | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[0U] 
                                           >> 0x18U))
                             : ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[2U] 
                                 << 0x10U) | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[1U] 
                                              >> 0x10U))) 
                           << 0x18U)) | (0xffffffU 
                                         & ((0xff0000U 
                                             & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[4U] 
                                                << 8U)) 
                                            | ((0xffU 
                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[3U] 
                                                   >> 0x18U)) 
                                               | (0xff00U 
                                                  & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[4U] 
                                                     << 8U))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7432_o[4U] 
        = (0xffffU & (((0x800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q))
                        ? ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[1U] 
                            << 8U) | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[0U] 
                                      >> 0x18U)) : 
                       ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[2U] 
                         << 0x10U) | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6304_o[1U] 
                                      >> 0x10U))) >> 8U));
    __Vtemp1005[0U] = (IData)((((QData)((IData)((0xffffffU 
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
    __Vtemp1005[1U] = ((0xffff0000U & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U] 
                                        << 0x18U) | 
                                       (0xff0000U & 
                                        (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[0U] 
                                         >> 8U)))) 
                       | (IData)(((((QData)((IData)(
                                                    (0xffffffU 
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
    if ((0x800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q))) {
        __Vtemp1013[1U] = __Vtemp1005[1U];
        __Vtemp1025[1U] = ((0xffff0000U & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U] 
                                            << 0x18U) 
                                           | (0xff0000U 
                                              & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[0U] 
                                                 >> 8U)))) 
                           | (IData)(((((QData)((IData)(
                                                        (0xffffffU 
                                                         & ((0xffffff00U 
                                                             & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U]) 
                                                            | (0xffU 
                                                               & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U]))))) 
                                        << 0x18U) | (QData)((IData)(
                                                                    (0xffffffU 
                                                                     & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[0U])))) 
                                      >> 0x20U)));
    } else {
        __Vtemp1013[1U] = ((0xffff0000U & ((0xff000000U 
                                            & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U] 
                                               << 0x10U)) 
                                           | (0xff0000U 
                                              & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U] 
                                                 << 0x10U)))) 
                           | (IData)(((((QData)((IData)(
                                                        (0xffffffU 
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
                                      >> 0x20U)));
        __Vtemp1025[1U] = ((0xffff0000U & ((0xff000000U 
                                            & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U] 
                                               << 0x10U)) 
                                           | (0xff0000U 
                                              & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U] 
                                                 << 0x10U)))) 
                           | (IData)(((0xffffffffffffULL 
                                       & (((QData)((IData)(
                                                           vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U])) 
                                           << 0x20U) 
                                          | (QData)((IData)(
                                                            vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[0U])))) 
                                      >> 0x20U)));
    }
    if (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8473_q) 
         == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8275_q))) {
        __Vtemp1027[0U] = ((0x800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q))
                            ? __Vtemp1005[0U] : (IData)(
                                                        (((QData)((IData)(
                                                                          (0xffffffU 
                                                                           & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U] 
                                                                               << 8U) 
                                                                              | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[0U] 
                                                                                >> 0x18U))))) 
                                                          << 0x18U) 
                                                         | (QData)((IData)(
                                                                           (0xffffffU 
                                                                            & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U] 
                                                                                << 8U) 
                                                                               | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[0U] 
                                                                                >> 0x18U))))))));
        __Vtemp1027[2U] = ((0x800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q))
                            ? ((0xffffff00U & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[2U] 
                                                << 0x18U) 
                                               | (0xffff00U 
                                                  & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U] 
                                                     >> 8U)))) 
                               | (0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U] 
                                           >> 8U)))
                            : ((0xffffff00U & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[2U] 
                                                << 0x18U) 
                                               | (0xffff00U 
                                                  & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U] 
                                                     >> 8U)))) 
                               | (0xffU & ((0xffffU 
                                            & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U] 
                                               >> 0x10U)) 
                                           | (0xff0000U 
                                              & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[1U] 
                                                 << 0x10U))))));
    } else {
        __Vtemp1027[0U] = ((0x800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q))
                            ? (IData)((((QData)((IData)(
                                                        (0xffffffU 
                                                         & ((0xffffff00U 
                                                             & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U]) 
                                                            | (0xffU 
                                                               & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U]))))) 
                                        << 0x18U) | (QData)((IData)(
                                                                    (0xffffffU 
                                                                     & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[0U])))))
                            : (IData)((0xffffffffffffULL 
                                       & (((QData)((IData)(
                                                           vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U])) 
                                           << 0x20U) 
                                          | (QData)((IData)(
                                                            vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[0U]))))));
        __Vtemp1027[2U] = ((0x800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q))
                            ? ((0xffffff00U & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[2U] 
                                                << 0x18U) 
                                               | (0xffff00U 
                                                  & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U] 
                                                     >> 8U)))) 
                               | (0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U] 
                                           >> 8U)))
                            : ((0xffffff00U & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[2U] 
                                                << 0x18U) 
                                               | (0xffff00U 
                                                  & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8445_q[1U] 
                                                     >> 8U)))) 
                               | (0xffU & ((0xffffU 
                                            & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[0U] 
                                               >> 0x10U)) 
                                           | (0xff0000U 
                                              & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8448_q[1U] 
                                                 << 0x10U))))));
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6363_o[0U] 
        = __Vtemp1027[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6363_o[1U] 
        = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8473_q) 
            == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8275_q))
            ? __Vtemp1013[1U] : __Vtemp1025[1U]);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6363_o[2U] 
        = __Vtemp1027[2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6819_o 
        = (((QData)((IData)(((0xff800000U & (((0xffU 
                                               & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                                  >> 4U)) 
                                              * (0xffU 
                                                 & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                                    >> 4U))) 
                                             << 0xfU)) 
                             | ((0x7ff000U & ((((((
                                                   (0x1feU 
                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                        << 0x11U) 
                                                       | (0x1fffeU 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                             >> 0xfU)))) 
                                                   - 
                                                   (0x1feU 
                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                        << 9U) 
                                                       | (0x1feU 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                             >> 0x17U))))) 
                                                  - 
                                                  (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                       << 8U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                         >> 0x18U)))) 
                                                 + 
                                                 (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                      << 0x10U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                        >> 0x10U)))) 
                                                + (0xffU 
                                                   & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U])) 
                                               - (0xffU 
                                                  & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                     >> 8U))) 
                                              << 0xcU)) 
                                | (0xfffU & (((((0x1feU 
                                                 & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                    >> 7U)) 
                                                - (0x3fcU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                       << 0x12U) 
                                                      | (0x3fffcU 
                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                            >> 0xeU))))) 
                                               - (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                      << 0x10U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                        >> 0x10U)))) 
                                              + (0x3fcU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                     << 0xaU) 
                                                    | (0x3fcU 
                                                       & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                          >> 0x16U))))) 
                                             - (0xffU 
                                                & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U]))))))) 
            << 9U) | (QData)((IData)((0x1ffU & ((0xffU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                     << 8U) 
                                                    | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                       >> 0x18U))) 
                                                - (0xffU 
                                                   & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                      >> 8U)))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6892_o 
        = (((QData)((IData)(((0xff800000U & (((0xffU 
                                               & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                                  >> 4U)) 
                                              * (0xffU 
                                                 & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                                    >> 4U))) 
                                             << 0xfU)) 
                             | ((0x7ff000U & ((((((
                                                   (0x1feU 
                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                        << 9U) 
                                                       | (0x1feU 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                             >> 0x17U)))) 
                                                   - 
                                                   (0x1feU 
                                                    & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                       << 1U))) 
                                                  - 
                                                  (0xffU 
                                                   & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U])) 
                                                 + 
                                                 (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                      << 8U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                        >> 0x18U)))) 
                                                + (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                       << 0x18U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                         >> 8U)))) 
                                               - (0xffU 
                                                  & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                     >> 0x10U))) 
                                              << 0xcU)) 
                                | (0xfffU & (((((0x1feU 
                                                 & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                    >> 0xfU)) 
                                                - (0x3fcU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                       << 0xaU) 
                                                      | (0x3fcU 
                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                            >> 0x16U))))) 
                                               - (0xffU 
                                                  & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                      << 8U) 
                                                     | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                        >> 0x18U)))) 
                                              + (0x3fcU 
                                                 & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                    << 2U))) 
                                             - (0xffU 
                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                    << 0x18U) 
                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                      >> 8U))))))))) 
            << 9U) | (QData)((IData)((0x1ffU & ((0xffU 
                                                 & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U]) 
                                                - (0xffU 
                                                   & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                      >> 0x10U)))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6965_o 
        = (((QData)((IData)(((0xff800000U & (((0xffU 
                                               & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                                  >> 4U)) 
                                              * (0xffU 
                                                 & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                                    >> 4U))) 
                                             << 0xfU)) 
                             | ((0x7ff000U & ((((((
                                                   (0x1feU 
                                                    & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                       << 1U)) 
                                                   - 
                                                   (0x1feU 
                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                        << 0x19U) 
                                                       | (0x1fffffeU 
                                                          & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                             >> 7U))))) 
                                                  - 
                                                  (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                       << 0x18U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                         >> 8U)))) 
                                                 + 
                                                 (0xffU 
                                                  & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U])) 
                                                + (0xffU 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                       << 0x10U) 
                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                         >> 0x10U)))) 
                                               - (0xffU 
                                                  & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                     >> 0x18U))) 
                                              << 0xcU)) 
                                | (0xfffU & (((((0x1feU 
                                                 & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                    >> 0x17U)) 
                                                - (0x3fcU 
                                                   & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                      << 2U))) 
                                               - (0xffU 
                                                  & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U])) 
                                              + (0x3fcU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                     << 0x1aU) 
                                                    | (0x3fffffcU 
                                                       & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                          >> 6U))))) 
                                             - (0xffU 
                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                    << 0x10U) 
                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[0U] 
                                                      >> 0x10U))))))))) 
            << 9U) | (QData)((IData)((0x1ffU & ((0xffU 
                                                 & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                     << 0x18U) 
                                                    | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                       >> 8U))) 
                                                - (0xffU 
                                                   & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                      >> 0x18U)))))));
    VL_EXTEND_WW(120,108, __Vtemp1029, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp1032, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp1035, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp1038, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp1041, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    VL_EXTEND_WW(120,108, __Vtemp1044, vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8285_q);
    __Vtemp1046[0U] = (IData)((((QData)((IData)((0xfffU 
                                                 & ((((0x1ff000U 
                                                       & ((- (IData)(
                                                                     (1U 
                                                                      & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[3U] 
                                                                         >> 0x1eU)))) 
                                                          << 0xcU)) 
                                                      | (0xfffU 
                                                         & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[4U] 
                                                             << 0xdU) 
                                                            | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[3U] 
                                                               >> 0x13U)))) 
                                                     * 
                                                     ((0x1ffe00U 
                                                       & ((- (IData)(
                                                                     (1U 
                                                                      & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[4U] 
                                                                         >> 0x12U)))) 
                                                          << 9U)) 
                                                      | (0x1ffU 
                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[4U] 
                                                            >> 0xaU)))) 
                                                    >> 8U)))) 
                                << 0x33U) | (((QData)((IData)(
                                                              (0xfffU 
                                                               & ((((0x1ff000U 
                                                                     & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[2U] 
                                                                                >> 0xdU)))) 
                                                                        << 0xcU)) 
                                                                    | (0xfffU 
                                                                       & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[3U] 
                                                                           << 0x1eU) 
                                                                          | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[2U] 
                                                                             >> 2U)))) 
                                                                   * 
                                                                   ((0x1ffe00U 
                                                                     & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[3U] 
                                                                                >> 1U)))) 
                                                                        << 9U)) 
                                                                    | (0x1ffU 
                                                                       & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[3U] 
                                                                           << 7U) 
                                                                          | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[2U] 
                                                                             >> 0x19U))))) 
                                                                  >> 8U)))) 
                                              << 0x27U) 
                                             | (((QData)((IData)(
                                                                 (0xfffU 
                                                                  & ((((0x1ff000U 
                                                                        & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[0U] 
                                                                                >> 0x1cU)))) 
                                                                           << 0xcU)) 
                                                                       | (0xfffU 
                                                                          & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[1U] 
                                                                              << 0xfU) 
                                                                             | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[0U] 
                                                                                >> 0x11U)))) 
                                                                      * 
                                                                      ((0x1ffe00U 
                                                                        & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[1U] 
                                                                                >> 0x10U)))) 
                                                                           << 9U)) 
                                                                       | (0x1ffU 
                                                                          & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[2U] 
                                                                              << 0x18U) 
                                                                             | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[1U] 
                                                                                >> 8U))))) 
                                                                     >> 8U)))) 
                                                 << 0x1bU) 
                                                | (QData)((IData)(
                                                                  ((0x7fc0000U 
                                                                    & ((((0x3fe00U 
                                                                          & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[3U] 
                                                                                >> 0x12U)))) 
                                                                             << 9U)) 
                                                                         | (0x1ffU 
                                                                            & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[4U] 
                                                                                << 0x16U) 
                                                                               | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[3U] 
                                                                                >> 0xaU)))) 
                                                                        * 
                                                                        (0xffU 
                                                                         & ((__Vtemp1032[1U] 
                                                                             << 4U) 
                                                                            | (__Vtemp1032[0U] 
                                                                               >> 0x1cU)))) 
                                                                       << 9U)) 
                                                                   | ((0x3fe00U 
                                                                       & (((0x3fe00U 
                                                                            & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[2U] 
                                                                                >> 1U)))) 
                                                                               << 9U)) 
                                                                           | (0x1ffU 
                                                                              & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[2U] 
                                                                                << 7U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[1U] 
                                                                                >> 0x19U)))) 
                                                                          * 
                                                                          (0xffU 
                                                                           & ((__Vtemp1038[1U] 
                                                                               << 4U) 
                                                                              | (__Vtemp1038[0U] 
                                                                                >> 0x1cU))))) 
                                                                      | (0x1ffU 
                                                                         & ((((0x3fe00U 
                                                                               & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[0U] 
                                                                                >> 0x10U)))) 
                                                                                << 9U)) 
                                                                              | (0x1ffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[1U] 
                                                                                << 0x18U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[0U] 
                                                                                >> 8U)))) 
                                                                             * 
                                                                             (0xffU 
                                                                              & ((__Vtemp1044[1U] 
                                                                                << 4U) 
                                                                                | (__Vtemp1044[0U] 
                                                                                >> 0x1cU)))) 
                                                                            >> 9U))))))))));
    __Vtemp1046[1U] = ((0x80000000U & ((((0xff800U 
                                          & ((- (IData)(
                                                        (1U 
                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[1U] 
                                                            >> 7U)))) 
                                             << 0xbU)) 
                                         | (0x7ffU 
                                            & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[1U] 
                                                << 3U) 
                                               | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[0U] 
                                                  >> 0x1dU)))) 
                                        * ((0xffe00U 
                                            & ((- (IData)(
                                                          (1U 
                                                           & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[1U] 
                                                              >> 0x10U)))) 
                                               << 9U)) 
                                           | (0x1ffU 
                                              & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[2U] 
                                                  << 0x18U) 
                                                 | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[1U] 
                                                    >> 8U))))) 
                                       << 0x17U)) | (IData)(
                                                            ((((QData)((IData)(
                                                                               (0xfffU 
                                                                                & ((((0x1ff000U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[3U] 
                                                                                >> 0x1eU)))) 
                                                                                << 0xcU)) 
                                                                                | (0xfffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[4U] 
                                                                                << 0xdU) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[3U] 
                                                                                >> 0x13U)))) 
                                                                                * 
                                                                                ((0x1ffe00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[4U] 
                                                                                >> 0x12U)))) 
                                                                                << 9U)) 
                                                                                | (0x1ffU 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[4U] 
                                                                                >> 0xaU)))) 
                                                                                >> 8U)))) 
                                                               << 0x33U) 
                                                              | (((QData)((IData)(
                                                                                (0xfffU 
                                                                                & ((((0x1ff000U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[2U] 
                                                                                >> 0xdU)))) 
                                                                                << 0xcU)) 
                                                                                | (0xfffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[3U] 
                                                                                << 0x1eU) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[2U] 
                                                                                >> 2U)))) 
                                                                                * 
                                                                                ((0x1ffe00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[3U] 
                                                                                >> 1U)))) 
                                                                                << 9U)) 
                                                                                | (0x1ffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[3U] 
                                                                                << 7U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[2U] 
                                                                                >> 0x19U))))) 
                                                                                >> 8U)))) 
                                                                  << 0x27U) 
                                                                 | (((QData)((IData)(
                                                                                (0xfffU 
                                                                                & ((((0x1ff000U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[0U] 
                                                                                >> 0x1cU)))) 
                                                                                << 0xcU)) 
                                                                                | (0xfffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[1U] 
                                                                                << 0xfU) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[0U] 
                                                                                >> 0x11U)))) 
                                                                                * 
                                                                                ((0x1ffe00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[1U] 
                                                                                >> 0x10U)))) 
                                                                                << 9U)) 
                                                                                | (0x1ffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[2U] 
                                                                                << 0x18U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[1U] 
                                                                                >> 8U))))) 
                                                                                >> 8U)))) 
                                                                     << 0x1bU) 
                                                                    | (QData)((IData)(
                                                                                ((0x7fc0000U 
                                                                                & ((((0x3fe00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[3U] 
                                                                                >> 0x12U)))) 
                                                                                << 9U)) 
                                                                                | (0x1ffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[4U] 
                                                                                << 0x16U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[3U] 
                                                                                >> 0xaU)))) 
                                                                                * 
                                                                                (0xffU 
                                                                                & ((__Vtemp1032[1U] 
                                                                                << 4U) 
                                                                                | (__Vtemp1032[0U] 
                                                                                >> 0x1cU)))) 
                                                                                << 9U)) 
                                                                                | ((0x3fe00U 
                                                                                & (((0x3fe00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[2U] 
                                                                                >> 1U)))) 
                                                                                << 9U)) 
                                                                                | (0x1ffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[2U] 
                                                                                << 7U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[1U] 
                                                                                >> 0x19U)))) 
                                                                                * 
                                                                                (0xffU 
                                                                                & ((__Vtemp1038[1U] 
                                                                                << 4U) 
                                                                                | (__Vtemp1038[0U] 
                                                                                >> 0x1cU))))) 
                                                                                | (0x1ffU 
                                                                                & ((((0x3fe00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[0U] 
                                                                                >> 0x10U)))) 
                                                                                << 9U)) 
                                                                                | (0x1ffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[1U] 
                                                                                << 0x18U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[0U] 
                                                                                >> 8U)))) 
                                                                                * 
                                                                                (0xffU 
                                                                                & ((__Vtemp1044[1U] 
                                                                                << 4U) 
                                                                                | (__Vtemp1044[0U] 
                                                                                >> 0x1cU)))) 
                                                                                >> 9U))))))))) 
                                                             >> 0x20U)));
    __Vtemp1047[2U] = ((0x1ffc00U & ((((0xff800U & 
                                        ((- (IData)(
                                                    (1U 
                                                     & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[2U] 
                                                        >> 0x18U)))) 
                                         << 0xbU)) 
                                       | (0x7ffU & 
                                          ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[3U] 
                                            << 0x12U) 
                                           | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[2U] 
                                              >> 0xeU)))) 
                                      * ((0xffe00U 
                                          & ((- (IData)(
                                                        (1U 
                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[3U] 
                                                            >> 1U)))) 
                                             << 9U)) 
                                         | (0x1ffU 
                                            & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[3U] 
                                                << 7U) 
                                               | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[2U] 
                                                  >> 0x19U))))) 
                                     << 2U)) | (0x3ffU 
                                                & ((((0xff800U 
                                                      & ((- (IData)(
                                                                    (1U 
                                                                     & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[1U] 
                                                                        >> 7U)))) 
                                                         << 0xbU)) 
                                                     | (0x7ffU 
                                                        & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[1U] 
                                                            << 3U) 
                                                           | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[0U] 
                                                              >> 0x1dU)))) 
                                                    * 
                                                    ((0xffe00U 
                                                      & ((- (IData)(
                                                                    (1U 
                                                                     & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[1U] 
                                                                        >> 0x10U)))) 
                                                         << 9U)) 
                                                     | (0x1ffU 
                                                        & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[2U] 
                                                            << 0x18U) 
                                                           | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[1U] 
                                                              >> 8U))))) 
                                                   >> 9U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5380_o[0U] 
        = __Vtemp1046[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5380_o[1U] 
        = __Vtemp1046[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5380_o[2U] 
        = ((0xffe00000U & ((((0xff800U & ((- (IData)(
                                                     (1U 
                                                      & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[4U] 
                                                         >> 9U)))) 
                                          << 0xbU)) 
                             | (0x7ffU & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[4U] 
                                           << 1U) | 
                                          (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[3U] 
                                           >> 0x1fU)))) 
                            * ((0xffe00U & ((- (IData)(
                                                       (1U 
                                                        & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[4U] 
                                                           >> 0x12U)))) 
                                            << 9U)) 
                               | (0x1ffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n5284_o[4U] 
                                            >> 0xaU)))) 
                           << 0xdU)) | __Vtemp1047[2U]);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[0U] 
        = (IData)(((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6819_o 
                    << 8U) | (QData)((IData)((0xffU 
                                              & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                  << 0x10U) 
                                                 | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                    >> 0x10U)))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[1U] 
        = ((0xfffe0000U & ((IData)(((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6892_o 
                                     << 8U) | (QData)((IData)(
                                                              (0xffU 
                                                               & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                                   << 8U) 
                                                                  | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                                     >> 0x18U))))))) 
                           << 0x11U)) | (IData)((((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6819_o 
                                                   << 8U) 
                                                  | (QData)((IData)(
                                                                    (0xffU 
                                                                     & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                                         << 0x10U) 
                                                                        | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                                           >> 0x10U)))))) 
                                                 >> 0x20U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[2U] 
        = ((0x1ffffU & ((IData)(((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6892_o 
                                  << 8U) | (QData)((IData)(
                                                           (0xffU 
                                                            & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                                << 8U) 
                                                               | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                                  >> 0x18U))))))) 
                        >> 0xfU)) | (0xfffe0000U & 
                                     ((IData)((((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6892_o 
                                                 << 8U) 
                                                | (QData)((IData)(
                                                                  (0xffU 
                                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                                       << 8U) 
                                                                      | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                                         >> 0x18U)))))) 
                                               >> 0x20U)) 
                                      << 0x11U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[3U] 
        = ((0xfffffffcU & ((IData)(((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6965_o 
                                     << 8U) | (QData)((IData)(
                                                              (0xffU 
                                                               & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U]))))) 
                           << 2U)) | (0x1ffffU & ((IData)(
                                                          (((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6892_o 
                                                             << 8U) 
                                                            | (QData)((IData)(
                                                                              (0xffU 
                                                                               & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U] 
                                                                                << 8U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[1U] 
                                                                                >> 0x18U)))))) 
                                                           >> 0x20U)) 
                                                  >> 0xfU)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[4U] 
        = ((3U & ((IData)(((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6965_o 
                            << 8U) | (QData)((IData)(
                                                     (0xffU 
                                                      & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U]))))) 
                  >> 0x1eU)) | (0xfffffffcU & ((IData)(
                                                       (((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6965_o 
                                                          << 8U) 
                                                         | (QData)((IData)(
                                                                           (0xffU 
                                                                            & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8441_q[2U])))) 
                                                        >> 0x20U)) 
                                               << 2U)));
    __Vtemp1051[0U] = (IData)((((QData)((IData)((0xfffU 
                                                 & ((((0x1ff000U 
                                                       & ((- (IData)(
                                                                     (1U 
                                                                      & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[3U] 
                                                                         >> 0x1eU)))) 
                                                          << 0xcU)) 
                                                      | (0xfffU 
                                                         & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[4U] 
                                                             << 0xdU) 
                                                            | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[3U] 
                                                               >> 0x13U)))) 
                                                     * 
                                                     ((0x1ffe00U 
                                                       & ((- (IData)(
                                                                     (1U 
                                                                      & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[4U] 
                                                                         >> 0x12U)))) 
                                                          << 9U)) 
                                                      | (0x1ffU 
                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[4U] 
                                                            >> 0xaU)))) 
                                                    >> 8U)))) 
                                << 0x33U) | (((QData)((IData)(
                                                              (0xfffU 
                                                               & ((((0x1ff000U 
                                                                     & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[2U] 
                                                                                >> 0xdU)))) 
                                                                        << 0xcU)) 
                                                                    | (0xfffU 
                                                                       & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[3U] 
                                                                           << 0x1eU) 
                                                                          | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[2U] 
                                                                             >> 2U)))) 
                                                                   * 
                                                                   ((0x1ffe00U 
                                                                     & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[3U] 
                                                                                >> 1U)))) 
                                                                        << 9U)) 
                                                                    | (0x1ffU 
                                                                       & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[3U] 
                                                                           << 7U) 
                                                                          | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[2U] 
                                                                             >> 0x19U))))) 
                                                                  >> 8U)))) 
                                              << 0x27U) 
                                             | (((QData)((IData)(
                                                                 (0xfffU 
                                                                  & ((((0x1ff000U 
                                                                        & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[0U] 
                                                                                >> 0x1cU)))) 
                                                                           << 0xcU)) 
                                                                       | (0xfffU 
                                                                          & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[1U] 
                                                                              << 0xfU) 
                                                                             | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[0U] 
                                                                                >> 0x11U)))) 
                                                                      * 
                                                                      ((0x1ffe00U 
                                                                        & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[1U] 
                                                                                >> 0x10U)))) 
                                                                           << 9U)) 
                                                                       | (0x1ffU 
                                                                          & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[2U] 
                                                                              << 0x18U) 
                                                                             | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[1U] 
                                                                                >> 8U))))) 
                                                                     >> 8U)))) 
                                                 << 0x1bU) 
                                                | (QData)((IData)(
                                                                  ((0x7fc0000U 
                                                                    & ((((0x3fe00U 
                                                                          & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[3U] 
                                                                                >> 0x12U)))) 
                                                                             << 9U)) 
                                                                         | (0x1ffU 
                                                                            & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[4U] 
                                                                                << 0x16U) 
                                                                               | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[3U] 
                                                                                >> 0xaU)))) 
                                                                        * 
                                                                        (0xffU 
                                                                         & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                                                            >> 4U))) 
                                                                       << 9U)) 
                                                                   | ((0x3fe00U 
                                                                       & (((0x3fe00U 
                                                                            & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[2U] 
                                                                                >> 1U)))) 
                                                                               << 9U)) 
                                                                           | (0x1ffU 
                                                                              & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[2U] 
                                                                                << 7U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[1U] 
                                                                                >> 0x19U)))) 
                                                                          * 
                                                                          (0xffU 
                                                                           & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                                                              >> 4U)))) 
                                                                      | (0x1ffU 
                                                                         & ((((0x3fe00U 
                                                                               & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[0U] 
                                                                                >> 0x10U)))) 
                                                                                << 9U)) 
                                                                              | (0x1ffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[1U] 
                                                                                << 0x18U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[0U] 
                                                                                >> 8U)))) 
                                                                             * 
                                                                             (0xffU 
                                                                              & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                                                                >> 4U))) 
                                                                            >> 9U))))))))));
    __Vtemp1051[1U] = ((0x80000000U & ((((0xff800U 
                                          & ((- (IData)(
                                                        (1U 
                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[1U] 
                                                            >> 7U)))) 
                                             << 0xbU)) 
                                         | (0x7ffU 
                                            & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[1U] 
                                                << 3U) 
                                               | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[0U] 
                                                  >> 0x1dU)))) 
                                        * ((0xffe00U 
                                            & ((- (IData)(
                                                          (1U 
                                                           & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[1U] 
                                                              >> 0x10U)))) 
                                               << 9U)) 
                                           | (0x1ffU 
                                              & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[2U] 
                                                  << 0x18U) 
                                                 | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[1U] 
                                                    >> 8U))))) 
                                       << 0x17U)) | (IData)(
                                                            ((((QData)((IData)(
                                                                               (0xfffU 
                                                                                & ((((0x1ff000U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[3U] 
                                                                                >> 0x1eU)))) 
                                                                                << 0xcU)) 
                                                                                | (0xfffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[4U] 
                                                                                << 0xdU) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[3U] 
                                                                                >> 0x13U)))) 
                                                                                * 
                                                                                ((0x1ffe00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[4U] 
                                                                                >> 0x12U)))) 
                                                                                << 9U)) 
                                                                                | (0x1ffU 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[4U] 
                                                                                >> 0xaU)))) 
                                                                                >> 8U)))) 
                                                               << 0x33U) 
                                                              | (((QData)((IData)(
                                                                                (0xfffU 
                                                                                & ((((0x1ff000U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[2U] 
                                                                                >> 0xdU)))) 
                                                                                << 0xcU)) 
                                                                                | (0xfffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[3U] 
                                                                                << 0x1eU) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[2U] 
                                                                                >> 2U)))) 
                                                                                * 
                                                                                ((0x1ffe00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[3U] 
                                                                                >> 1U)))) 
                                                                                << 9U)) 
                                                                                | (0x1ffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[3U] 
                                                                                << 7U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[2U] 
                                                                                >> 0x19U))))) 
                                                                                >> 8U)))) 
                                                                  << 0x27U) 
                                                                 | (((QData)((IData)(
                                                                                (0xfffU 
                                                                                & ((((0x1ff000U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[0U] 
                                                                                >> 0x1cU)))) 
                                                                                << 0xcU)) 
                                                                                | (0xfffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[1U] 
                                                                                << 0xfU) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[0U] 
                                                                                >> 0x11U)))) 
                                                                                * 
                                                                                ((0x1ffe00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[1U] 
                                                                                >> 0x10U)))) 
                                                                                << 9U)) 
                                                                                | (0x1ffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[2U] 
                                                                                << 0x18U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[1U] 
                                                                                >> 8U))))) 
                                                                                >> 8U)))) 
                                                                     << 0x1bU) 
                                                                    | (QData)((IData)(
                                                                                ((0x7fc0000U 
                                                                                & ((((0x3fe00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[3U] 
                                                                                >> 0x12U)))) 
                                                                                << 9U)) 
                                                                                | (0x1ffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[4U] 
                                                                                << 0x16U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[3U] 
                                                                                >> 0xaU)))) 
                                                                                * 
                                                                                (0xffU 
                                                                                & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                                                                >> 4U))) 
                                                                                << 9U)) 
                                                                                | ((0x3fe00U 
                                                                                & (((0x3fe00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[2U] 
                                                                                >> 1U)))) 
                                                                                << 9U)) 
                                                                                | (0x1ffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[2U] 
                                                                                << 7U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[1U] 
                                                                                >> 0x19U)))) 
                                                                                * 
                                                                                (0xffU 
                                                                                & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                                                                >> 4U)))) 
                                                                                | (0x1ffU 
                                                                                & ((((0x3fe00U 
                                                                                & ((- (IData)(
                                                                                (1U 
                                                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[0U] 
                                                                                >> 0x10U)))) 
                                                                                << 9U)) 
                                                                                | (0x1ffU 
                                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[1U] 
                                                                                << 0x18U) 
                                                                                | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[0U] 
                                                                                >> 8U)))) 
                                                                                * 
                                                                                (0xffU 
                                                                                & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8284_q) 
                                                                                >> 4U))) 
                                                                                >> 9U))))))))) 
                                                             >> 0x20U)));
    __Vtemp1052[2U] = ((0x1ffc00U & ((((0xff800U & 
                                        ((- (IData)(
                                                    (1U 
                                                     & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[2U] 
                                                        >> 0x18U)))) 
                                         << 0xbU)) 
                                       | (0x7ffU & 
                                          ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[3U] 
                                            << 0x12U) 
                                           | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[2U] 
                                              >> 0xeU)))) 
                                      * ((0xffe00U 
                                          & ((- (IData)(
                                                        (1U 
                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[3U] 
                                                            >> 1U)))) 
                                             << 9U)) 
                                         | (0x1ffU 
                                            & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[3U] 
                                                << 7U) 
                                               | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[2U] 
                                                  >> 0x19U))))) 
                                     << 2U)) | (0x3ffU 
                                                & ((((0xff800U 
                                                      & ((- (IData)(
                                                                    (1U 
                                                                     & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[1U] 
                                                                        >> 7U)))) 
                                                         << 0xbU)) 
                                                     | (0x7ffU 
                                                        & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[1U] 
                                                            << 3U) 
                                                           | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[0U] 
                                                              >> 0x1dU)))) 
                                                    * 
                                                    ((0xffe00U 
                                                      & ((- (IData)(
                                                                    (1U 
                                                                     & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[1U] 
                                                                        >> 0x10U)))) 
                                                         << 9U)) 
                                                     | (0x1ffU 
                                                        & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[2U] 
                                                            << 0x18U) 
                                                           | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[1U] 
                                                              >> 8U))))) 
                                                   >> 9U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7063_o[0U] 
        = __Vtemp1051[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7063_o[1U] 
        = __Vtemp1051[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7063_o[2U] 
        = ((0xffe00000U & ((((0xff800U & ((- (IData)(
                                                     (1U 
                                                      & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[4U] 
                                                         >> 9U)))) 
                                          << 0xbU)) 
                             | (0x7ffU & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[4U] 
                                           << 1U) | 
                                          (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[3U] 
                                           >> 0x1fU)))) 
                            * ((0xffe00U & ((- (IData)(
                                                       (1U 
                                                        & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[4U] 
                                                           >> 0x12U)))) 
                                            << 9U)) 
                               | (0x1ffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n6967_o[4U] 
                                            >> 0xaU)))) 
                           << 0xdU)) | __Vtemp1052[2U]);
}

VL_INLINE_OPT void Vsynth_top::_sequent__TOP__5(Vsynth_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth_top::_sequent__TOP__5\n"); );
    Vsynth_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7654_q 
        = ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7653_o));
}

VL_INLINE_OPT void Vsynth_top::_sequent__TOP__6(Vsynth_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth_top::_sequent__TOP__6\n"); );
    Vsynth_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*1:0*/ __Vdly__synth_top__DOT__src__DOT__clkdiv;
    CData/*7:0*/ __Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram__v0;
    CData/*0:0*/ __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram__v0;
    SData/*9:0*/ __Vdly__synth_top__DOT__src__DOT__hcnt;
    VlWide<4>/*127:0*/ __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram__v0;
    VlWide<4>/*127:0*/ __Vtemp1069;
    VlWide<4>/*127:0*/ __Vtemp1100;
    // Body
    __Vdly__synth_top__DOT__src__DOT__clkdiv = vlTOPp->synth_top__DOT__src__DOT__clkdiv;
    __Vdly__synth_top__DOT__src__DOT__hcnt = vlTOPp->synth_top__DOT__src__DOT__hcnt;
    __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram__v0 = 0U;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7664_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7663_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7706_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7705_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7652_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n14071_o;
    __Vdly__synth_top__DOT__src__DOT__clkdiv = (3U 
                                                & ((IData)(1U) 
                                                   + (IData)(vlTOPp->synth_top__DOT__src__DOT__clkdiv)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7636_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7635_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7900_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7899_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7896_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7895_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7892_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7891_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7888_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7887_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7880_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7879_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7876_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7875_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7872_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7871_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7848_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7847_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7844_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7843_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7840_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7839_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7761_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7760_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7757_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7756_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7680_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7679_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7676_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7675_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7672_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7671_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7668_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7667_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7782_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7781_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7697_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7696_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7533_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7532_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7709_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7708_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8496_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8495_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7860_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7859_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7766_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7765_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7737_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7736_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7733_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7732_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7793_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7792_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7567_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7566_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7563_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7562_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7785_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7784_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7750_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7749_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7660_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7659_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7644_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7643_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7524_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7523_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7543_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7542_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7819_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7818_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7590_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7589_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7539_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7538_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7904_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7903_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7559_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7558_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7551_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7550_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7624_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7623_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7555_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7554_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7594_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7593_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7789_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7788_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7723_q[0U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7722_o[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7723_q[1U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7722_o[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7723_q[2U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7722_o[2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7723_q[3U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7722_o[3U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7616_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7615_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7583_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7582_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7521_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7520_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7613_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7612_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7657_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7656_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7602_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7601_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7648_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7647_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7864_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7863_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7753_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7752_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7832_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7831_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7575_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7574_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7808_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7807_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7770_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7769_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7579_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7578_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7587_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7586_o;
    if (vlTOPp->reset_na) {
        if ((1U & (IData)(vlTOPp->synth_top__DOT__src__DOT__clkdiv))) {
            vlTOPp->synth_top__DOT__p_vs = (1U & (~ 
                                                  ((0x1e9U 
                                                    <= (IData)(vlTOPp->synth_top__DOT__src__DOT__vcnt)) 
                                                   & (0x1ebU 
                                                      > (IData)(vlTOPp->synth_top__DOT__src__DOT__vcnt)))));
        }
    } else {
        vlTOPp->synth_top__DOT__p_vs = 1U;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7797_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7796_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7726_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7800_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7799_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7686_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7685_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7683_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7682_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7640_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7639_o;
    if (vlTOPp->reset_na) {
        if ((1U & (IData)(vlTOPp->synth_top__DOT__src__DOT__clkdiv))) {
            vlTOPp->synth_top__DOT__p_de = ((0x200U 
                                             > (IData)(vlTOPp->synth_top__DOT__src__DOT__hcnt)) 
                                            & (0x1e0U 
                                               > (IData)(vlTOPp->synth_top__DOT__src__DOT__vcnt)));
        }
    } else {
        vlTOPp->synth_top__DOT__p_de = 0U;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7816_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7815_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7632_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7631_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7884_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7883_o;
    if (vlTOPp->reset_na) {
        if ((1U & (IData)(vlTOPp->synth_top__DOT__src__DOT__clkdiv))) {
            vlTOPp->synth_top__DOT__p_b = (((0x200U 
                                             > (IData)(vlTOPp->synth_top__DOT__src__DOT__hcnt)) 
                                            & (0x1e0U 
                                               > (IData)(vlTOPp->synth_top__DOT__src__DOT__vcnt)))
                                            ? (0xffU 
                                               & vlTOPp->synth_top__DOT__src__DOT__pat)
                                            : 0U);
        }
    } else {
        vlTOPp->synth_top__DOT__p_b = 0U;
    }
    if (vlTOPp->reset_na) {
        if ((1U & (IData)(vlTOPp->synth_top__DOT__src__DOT__clkdiv))) {
            vlTOPp->synth_top__DOT__p_g = (0xffU & 
                                           ((((0x200U 
                                               > (IData)(vlTOPp->synth_top__DOT__src__DOT__hcnt)) 
                                              & (0x1e0U 
                                                 > (IData)(vlTOPp->synth_top__DOT__src__DOT__vcnt)))
                                              ? vlTOPp->synth_top__DOT__src__DOT__pat
                                              : 0U) 
                                            >> 8U));
        }
    } else {
        vlTOPp->synth_top__DOT__p_g = 0U;
    }
    if (vlTOPp->reset_na) {
        if ((1U & (IData)(vlTOPp->synth_top__DOT__src__DOT__clkdiv))) {
            vlTOPp->synth_top__DOT__p_r = (0xffU & 
                                           ((((0x200U 
                                               > (IData)(vlTOPp->synth_top__DOT__src__DOT__hcnt)) 
                                              & (0x1e0U 
                                                 > (IData)(vlTOPp->synth_top__DOT__src__DOT__vcnt)))
                                              ? vlTOPp->synth_top__DOT__src__DOT__pat
                                              : 0U) 
                                            >> 0x10U));
        }
    } else {
        vlTOPp->synth_top__DOT__p_r = 0U;
    }
    if ((((IData)(vlTOPp->synth_top__DOT__src__DOT__clkdiv) 
          & (0x279U == (IData)(vlTOPp->synth_top__DOT__src__DOT__hcnt))) 
         & (0x20cU == (IData)(vlTOPp->synth_top__DOT__src__DOT__vcnt)))) {
        vlTOPp->synth_top__DOT__src__DOT__frame = (0x3ffU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->synth_top__DOT__src__DOT__frame)));
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7620_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7619_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7908_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7907_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7812_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7811_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7856_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7855_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7852_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7851_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7693_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7692_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7571_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7570_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7700_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7699_o;
    if ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n960_o))) {
        __Vtemp1069[0U] = ((0xff000000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
                                           << 0x18U)) 
                           | ((0xff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
                                            << 8U)) 
                              | (0xff00U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
                                            >> 8U))));
        __Vtemp1069[1U] = ((0xffffffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[0U]) 
                           | (0xff000000U & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[0U]));
        __Vtemp1069[2U] = ((0xffffffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[1U]) 
                           | (0xff000000U & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[1U]));
    } else {
        __Vtemp1069[0U] = ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n960_o))
                            ? ((0xff000000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[0U] 
                                               << 0x18U)) 
                               | ((0xff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
                                                << 0x10U)) 
                                  | ((0xff00U & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q) 
                                     | (0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
                                                 >> 0x10U)))))
                            : ((0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[0U] 
                                               << 0x10U)) 
                               | ((0xe000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
                                              << 3U)) 
                                  | ((0x1f00U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
                                                 << 5U)) 
                                     | ((0xf8U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
                                                  >> 0x10U)) 
                                        | (7U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
                                                 >> 0xdU)))))));
        __Vtemp1069[1U] = ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n960_o))
                            ? ((0xffffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[0U] 
                                             >> 8U)) 
                               | (0xff000000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[1U] 
                                                 << 0x18U)))
                            : ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[0U] 
                                           >> 0x10U)) 
                               | (0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[1U] 
                                                 << 0x10U))));
        __Vtemp1069[2U] = ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n960_o))
                            ? ((0xffffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[1U] 
                                             >> 8U)) 
                               | (0xff000000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[2U] 
                                                 << 0x18U)))
                            : ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[1U] 
                                           >> 0x10U)) 
                               | (0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[2U] 
                                                 << 0x10U))));
    }
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7718_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7720_q[0U] 
            = __Vtemp1069[0U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7720_q[1U] 
            = __Vtemp1069[1U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7720_q[2U] 
            = __Vtemp1069[2U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7720_q[3U] 
            = ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n960_o))
                ? (0xffffffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[2U])
                : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n960_o))
                    ? (0xffffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[2U] 
                                    >> 8U)) : ((0xffffU 
                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[2U] 
                                                   >> 0x10U)) 
                                               | (0xff0000U 
                                                  & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[3U] 
                                                     << 0x10U)))));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7720_q[0U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[0U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7720_q[1U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[1U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7720_q[2U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[2U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7720_q[3U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[3U];
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7703_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7702_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7804_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7803_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7775_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7774_o;
    if (vlTOPp->reset_na) {
        if ((1U & (IData)(vlTOPp->synth_top__DOT__src__DOT__clkdiv))) {
            __Vdly__synth_top__DOT__src__DOT__hcnt 
                = (0x3ffU & ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__src__DOT__hcnt)));
            if ((0x279U == (IData)(vlTOPp->synth_top__DOT__src__DOT__hcnt))) {
                vlTOPp->synth_top__DOT__src__DOT__vcnt 
                    = ((0x20cU == (IData)(vlTOPp->synth_top__DOT__src__DOT__vcnt))
                        ? 0U : (0x3ffU & ((IData)(1U) 
                                          + (IData)(vlTOPp->synth_top__DOT__src__DOT__vcnt))));
                __Vdly__synth_top__DOT__src__DOT__hcnt = 0U;
            }
        }
    } else {
        vlTOPp->synth_top__DOT__src__DOT__vcnt = 0U;
        __Vdly__synth_top__DOT__src__DOT__hcnt = 0U;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7779_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7778_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7606_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7605_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7598_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7597_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7689_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7688_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7527_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7526_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7716_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7715_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7547_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7546_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7713_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7712_o;
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7609_q) {
        __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram__v0[0U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[0U];
        __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram__v0[1U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[1U];
        __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram__v0[2U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[2U];
        __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram__v0[3U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[3U];
        __Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram__v0 = 1U;
        __Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram__v0 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7744_q;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7536_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7535_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7529_o;
    vlTOPp->synth_top__DOT__src__DOT__clkdiv = __Vdly__synth_top__DOT__src__DOT__clkdiv;
    vlTOPp->synth_top__DOT__src__DOT__hcnt = __Vdly__synth_top__DOT__src__DOT__hcnt;
    if (__Vdlyvset__synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram__v0) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram[__Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram__v0][0U] 
            = __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram__v0[0U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram[__Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram__v0][1U] 
            = __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram__v0[1U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram[__Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram__v0][2U] 
            = __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram__v0[2U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram[__Vdlyvdim0__synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram__v0][3U] 
            = __Vdlyvval__synth_top__DOT__dut__DOT__u_ascal__DOT__i_dpram__v0[3U];
    }
    vlTOPp->dbg_i_himax = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7563_q;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n424_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7587_q) 
           == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7579_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n646_o 
        = (0x1ffU & ((0xffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7797_q) 
                               >> 4U)) + (1U & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7797_q) 
                                                >> 0xbU))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n831_o 
        = (0x1ffU & ((0xffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7800_q) 
                               >> 4U)) + (1U & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7800_q) 
                                                >> 0xbU))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1405_o 
        = ((5U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7686_q)) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7683_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n574_o[0U] 
        = (IData)((0xffffffffffffULL & (((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7856_q)) 
                                         << 0x18U) 
                                        | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7856_q)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n574_o[1U] 
        = ((0xffff0000U & ((IData)((0xffffffffffffULL 
                                    & (((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7852_q)) 
                                        << 0x18U) | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7852_q))))) 
                           << 0x10U)) | (IData)(((0xffffffffffffULL 
                                                  & (((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7856_q)) 
                                                      << 0x18U) 
                                                     | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7856_q)))) 
                                                 >> 0x20U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n574_o[2U] 
        = ((0xffffU & ((IData)((0xffffffffffffULL & 
                                (((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7852_q)) 
                                  << 0x18U) | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7852_q))))) 
                       >> 0x10U)) | (0xffff0000U & 
                                     ((IData)(((0xffffffffffffULL 
                                                & (((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7852_q)) 
                                                    << 0x18U) 
                                                   | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7852_q)))) 
                                               >> 0x20U)) 
                                      << 0x10U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n632_o[0U] 
        = (IData)((0xffffffffffffULL & (((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7856_q)) 
                                         << 0x18U) 
                                        | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7856_q)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n632_o[1U] 
        = ((0xffff0000U & ((IData)((0xffffffffffffULL 
                                    & (((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7852_q)) 
                                        << 0x18U) | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7852_q))))) 
                           << 0x10U)) | (IData)(((0xffffffffffffULL 
                                                  & (((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7856_q)) 
                                                      << 0x18U) 
                                                     | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7856_q)))) 
                                                 >> 0x20U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n632_o[2U] 
        = ((0xffffU & ((IData)((0xffffffffffffULL & 
                                (((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7852_q)) 
                                  << 0x18U) | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7852_q))))) 
                       >> 0x10U)) | (0xffff0000U & 
                                     ((IData)(((0xffffffffffffULL 
                                                & (((QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7852_q)) 
                                                    << 0x18U) 
                                                   | (QData)((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7852_q)))) 
                                               >> 0x20U)) 
                                      << 0x10U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n925_o 
        = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7908_q) 
            & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7884_q)) 
           | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7693_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[0U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7720_q[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[1U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7720_q[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[2U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7720_q[2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[3U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7720_q[3U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7867_o;
    vlTOPp->synth_top__DOT__src__DOT__band = ((0x50U 
                                               > (IData)(vlTOPp->synth_top__DOT__src__DOT__vcnt))
                                               ? 0U
                                               : ((0xa0U 
                                                   > (IData)(vlTOPp->synth_top__DOT__src__DOT__vcnt))
                                                   ? 1U
                                                   : 
                                                  ((0xf0U 
                                                    > (IData)(vlTOPp->synth_top__DOT__src__DOT__vcnt))
                                                    ? 2U
                                                    : 
                                                   ((0x140U 
                                                     > (IData)(vlTOPp->synth_top__DOT__src__DOT__vcnt))
                                                     ? 3U
                                                     : 
                                                    ((0x190U 
                                                      > (IData)(vlTOPp->synth_top__DOT__src__DOT__vcnt))
                                                      ? 4U
                                                      : 5U)))));
    vlTOPp->synth_top__DOT__src__DOT__in_hatch = ((0U 
                                                   == 
                                                   (0x1fU 
                                                    & (IData)(vlTOPp->synth_top__DOT__src__DOT__hcnt))) 
                                                  | (0U 
                                                     == 
                                                     (0x1fU 
                                                      & (IData)(vlTOPp->synth_top__DOT__src__DOT__vcnt))));
    vlTOPp->__Vtableidx1 = (7U & ((IData)(vlTOPp->synth_top__DOT__src__DOT__hcnt) 
                                  >> 6U));
    vlTOPp->synth_top__DOT__src__DOT__bar_rgb = vlTOPp->__Vtable1_synth_top__DOT__src__DOT__bar_rgb
        [vlTOPp->__Vtableidx1];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n374_o 
        = VL_LTS_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7779_q), 
                     ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7575_q) 
                      << 1U));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n397_o 
        = VL_LTS_III(1,32,32, ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7808_q) 
                               + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7779_q) 
                                  << 1U)), ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7571_q) 
                                            << 1U));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1660_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7816_q)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7779_q)
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7571_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n960_o 
        = (((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7598_q)) 
            << 1U) | (1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7598_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1037_o 
        = (((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7598_q)) 
            << 1U) | (1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7598_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1081_o 
        = (((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7598_q)) 
            << 1U) | (1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7598_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n252_o 
        = ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7620_q)) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7527_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n186_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7606_q) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7527_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n530_o 
        = (0x1ffffU & ((0x10000U & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7789_q)
                        ? (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7789_q 
                           + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7547_q) 
                              << 2U)) : (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7789_q 
                                         - ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7547_q) 
                                            << 2U))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n452_o 
        = VL_LTS_III(1,32,32, ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7804_q) 
                               + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7775_q) 
                                  << 1U)), ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7547_q) 
                                            << 1U));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1658_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7812_q)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7775_q)
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7547_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n492_o 
        = (0x1ffffU & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7804_q) 
                        << 4U) - ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7547_q) 
                                  << 4U)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7609_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7608_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[0U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7746_o[0U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[1U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7746_o[1U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[2U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7746_o[2U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[3U] 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7746_o[3U];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7744_q 
        = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7743_o;
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1336_o 
        = ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7536_q)) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7700_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1258_o 
        = ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7536_q)) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7703_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1282_o 
        = ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7536_q)) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7689_q));
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7832_q) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n875_o 
            = (((QData)((IData)((0x1ffffU & ((0xffU 
                                              & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7864_q 
                                                 >> 0x10U)) 
                                             * (0x1ffU 
                                                & ((IData)(0x100U) 
                                                   - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n831_o))))))) 
                << 0x22U) | (((QData)((IData)((0x1ffffU 
                                               & ((0xffU 
                                                   & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7864_q 
                                                      >> 8U)) 
                                                  * 
                                                  (0x1ffU 
                                                   & ((IData)(0x100U) 
                                                      - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n831_o))))))) 
                              << 0x11U) | (QData)((IData)(
                                                          (0x1ffffU 
                                                           & ((0xffU 
                                                               & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7864_q) 
                                                              * 
                                                              (0x1ffU 
                                                               & ((IData)(0x100U) 
                                                                  - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n831_o)))))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n689_o 
            = (((QData)((IData)((0x1ffffU & (((0xffU 
                                               & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n632_o[2U] 
                                                   << 0x18U) 
                                                  | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n632_o[1U] 
                                                     >> 8U))) 
                                              * (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n646_o)) 
                                             + ((0xffU 
                                                 & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n632_o[2U]) 
                                                * (0x1ffU 
                                                   & ((IData)(0x100U) 
                                                      - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n646_o)))))))) 
                << 0x22U) | (((QData)((IData)((0x1ffffU 
                                               & (((0xffU 
                                                    & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n632_o[1U]) 
                                                   * (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n646_o)) 
                                                  + 
                                                  ((0xffU 
                                                    & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n632_o[2U] 
                                                        << 8U) 
                                                       | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n632_o[1U] 
                                                          >> 0x18U))) 
                                                   * 
                                                   (0x1ffU 
                                                    & ((IData)(0x100U) 
                                                       - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n646_o)))))))) 
                              << 0x11U) | (QData)((IData)(
                                                          (0x1ffffU 
                                                           & (((0xffU 
                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n632_o[1U] 
                                                                    << 8U) 
                                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n632_o[0U] 
                                                                      >> 0x18U))) 
                                                               * (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n646_o)) 
                                                              + 
                                                              ((0xffU 
                                                                & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n632_o[2U] 
                                                                    << 0x10U) 
                                                                   | (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n632_o[1U] 
                                                                      >> 0x10U))) 
                                                               * 
                                                               (0x1ffU 
                                                                & ((IData)(0x100U) 
                                                                   - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n646_o))))))))));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n875_o 
            = ((0x800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7800_q))
                ? 0ULL : (((QData)((IData)((0xff00U 
                                            & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7864_q 
                                               >> 8U)))) 
                           << 0x22U) | (((QData)((IData)(
                                                         (0xff00U 
                                                          & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7864_q))) 
                                         << 0x11U) 
                                        | (QData)((IData)(
                                                          (0xff00U 
                                                           & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7864_q 
                                                              << 8U)))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n689_o 
            = ((0x800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7797_q))
                ? (((QData)((IData)((0xff00U & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n574_o[1U]))) 
                    << 0x22U) | (((QData)((IData)((0xff00U 
                                                   & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n574_o[1U] 
                                                      << 8U)))) 
                                  << 0x11U) | (QData)((IData)(
                                                              (0xff00U 
                                                               & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n574_o[1U] 
                                                                   << 0x10U) 
                                                                  | (0xff00U 
                                                                     & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n574_o[0U] 
                                                                        >> 0x10U))))))))
                : (((QData)((IData)((0xff00U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n574_o[2U] 
                                                << 8U)))) 
                    << 0x22U) | (((QData)((IData)((0xff00U 
                                                   & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n574_o[2U] 
                                                       << 0x10U) 
                                                      | (0xff00U 
                                                         & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n574_o[1U] 
                                                            >> 0x10U)))))) 
                                  << 0x11U) | (QData)((IData)(
                                                              (0xff00U 
                                                               & ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n574_o[2U] 
                                                                   << 0x18U) 
                                                                  | (0xffff00U 
                                                                     & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n574_o[1U] 
                                                                        >> 8U)))))))));
    }
    vlTOPp->synth_top__DOT__src__DOT__pat = (0xffffffU 
                                             & ((4U 
                                                 & (IData)(vlTOPp->synth_top__DOT__src__DOT__band))
                                                 ? 
                                                ((2U 
                                                  & (IData)(vlTOPp->synth_top__DOT__src__DOT__band))
                                                  ? 
                                                 ((IData)(vlTOPp->synth_top__DOT__src__DOT__in_hatch)
                                                   ? 0xff00U
                                                   : 0x101010U)
                                                  : 
                                                 ((1U 
                                                   & (IData)(vlTOPp->synth_top__DOT__src__DOT__band))
                                                   ? 
                                                  ((IData)(vlTOPp->synth_top__DOT__src__DOT__in_hatch)
                                                    ? 0xff00U
                                                    : 0x101010U)
                                                   : 
                                                  ((1U 
                                                    & ((IData)(vlTOPp->synth_top__DOT__src__DOT__hcnt) 
                                                       ^ (IData)(vlTOPp->synth_top__DOT__src__DOT__vcnt)))
                                                    ? 0xffffffU
                                                    : 0U)))
                                                 : 
                                                ((2U 
                                                  & (IData)(vlTOPp->synth_top__DOT__src__DOT__band))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(vlTOPp->synth_top__DOT__src__DOT__band))
                                                   ? 
                                                  ((0xff0000U 
                                                    & ((IData)(vlTOPp->synth_top__DOT__src__DOT__hcnt) 
                                                       << 0xfU)) 
                                                   | ((0xff00U 
                                                       & ((IData)(vlTOPp->synth_top__DOT__src__DOT__hcnt) 
                                                          << 7U)) 
                                                      | (0xffU 
                                                         & ((IData)(vlTOPp->synth_top__DOT__src__DOT__hcnt) 
                                                            >> 1U))))
                                                   : 
                                                  ((1U 
                                                    & (IData)(vlTOPp->synth_top__DOT__src__DOT__vcnt))
                                                    ? 0xffffffU
                                                    : 0U))
                                                  : 
                                                 ((1U 
                                                   & (IData)(vlTOPp->synth_top__DOT__src__DOT__band))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(vlTOPp->synth_top__DOT__src__DOT__hcnt))
                                                    ? 0xffffffU
                                                    : 0U)
                                                   : vlTOPp->synth_top__DOT__src__DOT__bar_rgb))));
    if ((((IData)(vlTOPp->synth_top__DOT__src__DOT__hcnt) 
          >= (0x1feU & ((IData)(vlTOPp->synth_top__DOT__src__DOT__frame) 
                        << 1U))) & ((IData)(vlTOPp->synth_top__DOT__src__DOT__hcnt) 
                                    < (0x3ffU & ((IData)(8U) 
                                                 + 
                                                 (0x1feU 
                                                  & ((IData)(vlTOPp->synth_top__DOT__src__DOT__frame) 
                                                     << 1U))))))) {
        vlTOPp->synth_top__DOT__src__DOT__pat = 0xff8000U;
    }
    if (((((0U == (IData)(vlTOPp->synth_top__DOT__src__DOT__hcnt)) 
           | (0x1ffU == (IData)(vlTOPp->synth_top__DOT__src__DOT__hcnt))) 
          | (0U == (IData)(vlTOPp->synth_top__DOT__src__DOT__vcnt))) 
         | (0x1dfU == (IData)(vlTOPp->synth_top__DOT__src__DOT__vcnt)))) {
        vlTOPp->synth_top__DOT__src__DOT__pat = 0xffffffU;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1083_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7770_q) 
           & ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1081_o))
               ? (3U == (3U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q)))
               : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1081_o))
                   ? (((5U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q)) 
                       | (0xaU == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q))) 
                      | (0xfU == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q)))
                   : (7U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q))))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n511_o 
        = (0x1ffffU & ((0x10000U & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n492_o)
                        ? (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n492_o 
                           + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7547_q) 
                              << 3U)) : (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n492_o 
                                         - ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7547_q) 
                                            << 3U))));
    if ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1037_o))) {
        __Vtemp1100[0U] = ((5U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q))
                            ? ((0xffffff00U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[0U] 
                                               << 8U)) 
                               | (0xffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q))
                            : ((0xaU == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q))
                                ? ((0xffff0000U & (
                                                   vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[0U] 
                                                   << 0x10U)) 
                                   | ((0xff00U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
                                                  << 8U)) 
                                      | (0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
                                                  >> 8U))))
                                : ((0xfU == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q))
                                    ? ((0xff000000U 
                                        & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[0U] 
                                           << 0x18U)) 
                                       | ((0xff0000U 
                                           & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
                                              << 0x10U)) 
                                          | ((0xff00U 
                                              & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q) 
                                             | (0xffU 
                                                & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
                                                   >> 0x10U)))))
                                    : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[0U])));
        __Vtemp1100[1U] = ((5U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q))
                            ? ((0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[0U] 
                                         >> 0x18U)) 
                               | (0xffffff00U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[1U] 
                                                 << 8U)))
                            : ((0xaU == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q))
                                ? ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[0U] 
                                               >> 0x10U)) 
                                   | (0xffff0000U & 
                                      (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[1U] 
                                       << 0x10U))) : 
                               ((0xfU == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q))
                                 ? ((0xffffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[0U] 
                                                  >> 8U)) 
                                    | (0xff000000U 
                                       & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[1U] 
                                          << 0x18U)))
                                 : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[1U])));
        __Vtemp1100[2U] = ((5U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q))
                            ? ((0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[1U] 
                                         >> 0x18U)) 
                               | (0xffffff00U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[2U] 
                                                 << 8U)))
                            : ((0xaU == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q))
                                ? ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[1U] 
                                               >> 0x10U)) 
                                   | (0xffff0000U & 
                                      (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[2U] 
                                       << 0x10U))) : 
                               ((0xfU == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q))
                                 ? ((0xffffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[1U] 
                                                  >> 8U)) 
                                    | (0xff000000U 
                                       & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[2U] 
                                          << 0x18U)))
                                 : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[2U])));
        __Vtemp1100[3U] = ((5U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q))
                            ? ((0xffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[2U] 
                                         >> 0x18U)) 
                               | (0xffffff00U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[3U] 
                                                 << 8U)))
                            : ((0xaU == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q))
                                ? ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[2U] 
                                               >> 0x10U)) 
                                   | (0xffff0000U & 
                                      (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[3U] 
                                       << 0x10U))) : 
                               ((0xfU == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q))
                                 ? ((0xffffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[2U] 
                                                  >> 8U)) 
                                    | (0xff000000U 
                                       & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[3U] 
                                          << 0x18U)))
                                 : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[3U])));
    } else {
        __Vtemp1100[0U] = ((7U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q)))
                            ? ((0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[0U] 
                                               << 0x10U)) 
                               | ((0xe000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
                                              << 3U)) 
                                  | ((0x1f00U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
                                                 << 5U)) 
                                     | ((0xf8U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
                                                  >> 0x10U)) 
                                        | (7U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
                                                 >> 0xdU))))))
                            : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[0U]);
        __Vtemp1100[1U] = ((7U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q)))
                            ? ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[0U] 
                                           >> 0x10U)) 
                               | (0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[1U] 
                                                 << 0x10U)))
                            : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[1U]);
        __Vtemp1100[2U] = ((7U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q)))
                            ? ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[1U] 
                                           >> 0x10U)) 
                               | (0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[2U] 
                                                 << 0x10U)))
                            : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[2U]);
        __Vtemp1100[3U] = ((7U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q)))
                            ? ((0xffffU & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[2U] 
                                           >> 0x10U)) 
                               | (0xffff0000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[3U] 
                                                 << 0x10U)))
                            : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[3U]);
    }
    if ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1037_o))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1038_o[0U] 
            = ((3U == (3U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q)))
                ? ((0xff000000U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
                                   << 0x18U)) | ((0xff0000U 
                                                  & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
                                                     << 8U)) 
                                                 | (0xff00U 
                                                    & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q 
                                                       >> 8U))))
                : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[0U]);
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1038_o[1U] 
            = ((3U == (3U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q)))
                ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[0U]
                : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[1U]);
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1038_o[2U] 
            = ((3U == (3U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q)))
                ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[1U]
                : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[2U]);
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1038_o[3U] 
            = ((3U == (3U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q)))
                ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__i_shift[2U]
                : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[3U]);
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1038_o[0U] 
            = __Vtemp1100[0U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1038_o[1U] 
            = __Vtemp1100[1U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1038_o[2U] 
            = __Vtemp1100[2U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1038_o[3U] 
            = __Vtemp1100[3U];
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1345_o 
        = (VL_LTS_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7716_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7713_q)) 
           & (0x7fU != (0x7fU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7744_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1298_o 
        = (VL_LTS_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7716_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7713_q)) 
           & (0x7fU == (0x7fU & ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7744_q)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1326_o 
        = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1298_o) 
            & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1282_o))
            ? ((IData)(0x800U) + vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7753_q)
            : (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n186_o) 
                & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q))
                ? 0U : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7753_q));
}

VL_INLINE_OPT void Vsynth_top::_sequent__TOP__7(Vsynth_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth_top::_sequent__TOP__7\n"); );
    Vsynth_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7762_q 
        = (1U & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n114_o)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o 
        = (1U & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7762_q)));
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7762_q) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7781_o 
            = (0x1fffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7571_q) 
                          << 1U));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7615_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7613_q) 
               | ((~ ((6U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7819_q)) 
                      & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7616_q))) 
                  & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7616_q)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7818_o 
            = (0x3fU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7613_q)
                         ? 0U : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7616_q)
                                  ? ((6U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7819_q))
                                      ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7819_q)
                                      : ((IData)(1U) 
                                         + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7819_q)))
                                  : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7819_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7784_o 
            = (0x1ffffffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7613_q)
                              ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7808_q) 
                                 << 0xcU) : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7616_q)
                                              ? ((0x1fff000U 
                                                  & (((0x1000000U 
                                                       & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7785_q)
                                                       ? 
                                                      ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7785_q 
                                                        >> 0xbU) 
                                                       + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7782_q))
                                                       : 
                                                      ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7785_q 
                                                        >> 0xbU) 
                                                       - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7782_q))) 
                                                     << 0xcU)) 
                                                 | ((0xffeU 
                                                     & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7785_q 
                                                        << 1U)) 
                                                    | (1U 
                                                       & (~ 
                                                          (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7785_q 
                                                           >> 0x18U)))))
                                              : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7808_q) 
                                                 << 0xcU))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7799_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7613_q)
                ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7800_q)
                : (((6U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7819_q)) 
                    & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7616_q))
                    ? ((0xf80U & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7785_q 
                                  << 7U)) | (0x40U 
                                             & ((~ 
                                                 (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7785_q 
                                                  >> 0x18U)) 
                                                << 6U)))
                    : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7800_q)));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7781_o 
            = (0x1fffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7782_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7615_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7616_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7818_o 
            = (0x3fU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7819_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7784_o 
            = (0x1ffffffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7785_q);
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7799_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7800_q;
    }
}

VL_INLINE_OPT void Vsynth_top::_sequent__TOP__8(Vsynth_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth_top::_sequent__TOP__8\n"); );
    Vsynth_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7968_q 
        = ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o)) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2014_o));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7967_q 
        = ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o)) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7966_o));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7934_q 
        = ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o)) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1926_o));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7935_q 
        = ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o)) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1923_o));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7909_q 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o)
            ? 0U : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1994_o));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7966_o 
        = (1U & (((0x7eU == (0x7fU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7947_q))) 
                  & (IData)(vlTOPp->synth_top__DOT__app_rd_data_valid))
                  ? (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7967_q))
                  : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7967_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1926_o 
        = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7934_q) 
            | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7930_q)) 
           & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7938_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1923_o 
        = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7935_q) 
            | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7933_q)) 
           & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7941_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o 
        = (((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7909_q)) 
            << 2U) | (((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7909_q)) 
                       << 1U) | (0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7909_q))));
    if ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2014_o 
            = (1U & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1979_o)
                      ? (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7968_q))
                      : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7968_q)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1994_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1979_o)
                ? 0U : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7909_q));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2014_o 
            = (1U & ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o))
                      ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7968_q)
                      : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o)) 
                         & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7968_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1994_o 
            = ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o))
                ? (((0x7fU == (0x7fU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7944_q))) 
                    & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1956_o))
                    ? 0U : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7909_q))
                : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o))
                    ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7935_q)
                        ? 1U : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7934_q)
                                 ? 2U : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7909_q)))
                    : 0U));
    }
}

VL_INLINE_OPT void Vsynth_top::_sequent__TOP__9(Vsynth_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth_top::_sequent__TOP__9\n"); );
    Vsynth_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8328_q 
        = ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2923_o));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8330_q 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)
            ? 0U : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3687_o));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8316_q 
        = ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2914_o));
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8329_q = 0U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8131_q = 0U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8132_q = 0U;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8329_q 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3673_o;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8131_q 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2903_o;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8132_q 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3440_o;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3054_o 
        = ((~ ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8159_o) 
               >> 0xeU)) & VL_LTS_III(1,32,32, 0U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8330_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2691_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2682_o) 
           | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8316_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2814_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8175_q) 
           & VL_GTS_III(1,32,32, 2U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8329_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o 
        = (((3U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8131_q)) 
            << 3U) | (((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8131_q)) 
                       << 2U) | (((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8131_q)) 
                                  << 1U) | (0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8131_q)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o 
        = (((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8132_q)) 
            << 2U) | (((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8132_q)) 
                       << 1U) | (0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8132_q))));
    vlTOPp->__Vtableidx5 = ((0x20U & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2814_o)
                                        ? (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8328_q))
                                        : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8328_q)) 
                                      << 5U)) | (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8328_q) 
                                                  << 4U) 
                                                 | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2923_o 
        = vlTOPp->__Vtable5_synth_top__DOT__dut__DOT__u_ascal__DOT__n2923_o
        [vlTOPp->__Vtableidx5];
    vlTOPp->__Vtableidx4 = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8324_q) 
                             << 4U) | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2921_o 
        = vlTOPp->__Vtable4_synth_top__DOT__dut__DOT__u_ascal__DOT__n2921_o
        [vlTOPp->__Vtableidx4];
    vlTOPp->__Vtableidx12 = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__scalaire_off_v) 
                              << 4U) | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2954_o 
        = vlTOPp->__Vtable12_synth_top__DOT__dut__DOT__u_ascal__DOT__n2954_o
        [vlTOPp->__Vtableidx12];
    vlTOPp->__Vtableidx9 = (((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8336_q)) 
                             << 5U) | (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__scalaire_prim_v) 
                                        << 4U) | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2944_o 
        = vlTOPp->__Vtable9_synth_top__DOT__dut__DOT__u_ascal__DOT__n2944_o
        [vlTOPp->__Vtableidx9];
    vlTOPp->__Vtableidx11 = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_bibu) 
                              << 5U) | (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__scalaire_bib_v) 
                                         << 4U) | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2948_o 
        = vlTOPp->__Vtable11_synth_top__DOT__dut__DOT__u_ascal__DOT__n2948_o
        [vlTOPp->__Vtableidx11];
    vlTOPp->__Vtableidx10 = ((((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8336_q) 
                               == ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8333_q) 
                                   - (IData)(1U))) 
                              << 5U) | (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__scalaire_last_v) 
                                         << 4U) | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2946_o 
        = vlTOPp->__Vtable10_synth_top__DOT__dut__DOT__u_ascal__DOT__n2946_o
        [vlTOPp->__Vtableidx10];
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2941_o 
        = (IData)(((4U == (0xfU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))) 
                   & (1U == (1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2814_o)))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2903_o 
        = ((8U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
            ? ((4U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                ? 0U : ((2U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                         ? 0U : ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                  ? 0U : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8138_q)
                                           ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2883_o)
                                               ? 2U
                                               : 0U)
                                           : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8131_q)))))
            : ((4U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                ? ((2U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                    ? 0U : ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                             ? 0U : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2814_o)
                                      ? 3U : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8131_q))))
                : ((2U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                    ? ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                        ? 0U : ((1U & ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2777_o)) 
                                       | VL_LTS_III(1,32,32, 0U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8339_q))))
                                 ? ((((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8321_q) 
                                      & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8453_q)) 
                                     | VL_LTS_III(1,32,32, 0U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8339_q)))
                                     ? 2U : 0U) : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8131_q)))
                    : ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                        ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8316_q)
                            ? 1U : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8131_q))
                        : 0U))));
    vlTOPp->__Vtableidx3 = ((((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8321_q) 
                              | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2777_o)) 
                             << 5U) | (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8321_q) 
                                        << 4U) | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2917_o 
        = vlTOPp->__Vtable3_synth_top__DOT__dut__DOT__u_ascal__DOT__n2917_o
        [vlTOPp->__Vtableidx3];
    vlTOPp->__Vtableidx8 = ((0xc0U & ((((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8324_q) 
                                        & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2777_o))
                                        ? ((IData)(1U) 
                                           + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8476_q))
                                        : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2763_o)
                                            ? 1U : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8476_q))) 
                                      << 6U)) | (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8476_q) 
                                                  << 4U) 
                                                 | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2938_o 
        = vlTOPp->__Vtable8_synth_top__DOT__dut__DOT__u_ascal__DOT__n2938_o
        [vlTOPp->__Vtableidx8];
    vlTOPp->__Vtableidx2 = ((((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8316_q)) 
                              & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2691_o)) 
                             << 5U) | (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2691_o) 
                                        << 4U) | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2914_o 
        = vlTOPp->__Vtable2_synth_top__DOT__dut__DOT__u_ascal__DOT__n2914_o
        [vlTOPp->__Vtableidx2];
    vlTOPp->__Vtableidx7 = ((0x20U & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2814_o)
                                        ? (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__o_bibu))
                                        : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2689_o)) 
                                      << 5U)) | (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2689_o) 
                                                  << 4U) 
                                                 | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2930_o 
        = vlTOPp->__Vtable7_synth_top__DOT__dut__DOT__u_ascal__DOT__n2930_o
        [vlTOPp->__Vtableidx7];
    vlTOPp->__Vtableidx6 = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2687_o) 
                             << 6U) | ((0x30U & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8138_q)
                                                   ? 
                                                  ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2883_o)
                                                    ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2687_o)
                                                    : 
                                                   (VL_LTES_III(1,32,32, 1U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8339_q))
                                                     ? 
                                                    ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8339_q) 
                                                     - (IData)(1U))
                                                     : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2687_o)))
                                                   : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2687_o)) 
                                                 << 4U)) 
                                       | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2928_o 
        = vlTOPp->__Vtable6_synth_top__DOT__dut__DOT__u_ascal__DOT__n2928_o
        [vlTOPp->__Vtableidx6];
    if ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3440_o 
            = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3412_o) 
                & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3277_o))
                ? 0U : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8132_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3447_o 
            = (0xffU & ((((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3335_o))
                           ? (((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q)) 
                               | (5U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q))) 
                              | (0xaU == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q)))
                           : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3335_o))
                               ? (0U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q)))
                               : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3335_o))
                                   ? (0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q))
                                   : (0U == (3U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q)))))) 
                         & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3277_o))
                         ? ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8181_q))
                         : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8181_q)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o 
            = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3277_o) 
                & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3412_o)) 
               & 1U);
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3440_o 
            = ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                ? ((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8135_q))
                    ? 2U : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8132_q))
                : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                    ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3054_o)
                        ? ((((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q) 
                             >> 2U) & VL_LTS_III(1,32,32, 0U, 
                                                 (0xfU 
                                                  & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8406_q) 
                                                     >> 8U))))
                            ? 1U : 2U) : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8132_q))
                    : 0U));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3447_o 
            = (0xffU & ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                         ? (((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3182_o))
                              ? (((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q)) 
                                  | (5U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q))) 
                                 | (0xaU == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q)))
                              : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3182_o))
                                  ? (0U == (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q)))
                                  : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3182_o))
                                      ? (0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q))
                                      : (0U == (3U 
                                                & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q))))))
                             ? ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8181_q))
                             : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8181_q))
                         : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                             ? ((4U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8403_q))
                                 ? 0x80U : 0U) : 0U)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o = 0U;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3673_o 
        = (3U & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2941_o) 
                  & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o)))
                  ? ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8329_q))
                  : (((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2941_o)) 
                      & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o))
                      ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8329_q) 
                         - (IData)(1U)) : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8329_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3687_o 
        = (3U & (((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8147_q)) 
                  & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o))
                  ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8330_q) 
                     - (IData)(1U)) : (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8147_q) 
                                        & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o)))
                                        ? ((IData)(1U) 
                                           + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8330_q))
                                        : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8330_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3707_o 
        = ((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8329_q)) 
           | ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o) 
              & (1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8329_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3717_o 
        = (((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o)) 
            & (1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8329_q))) 
           | ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o) 
              & (2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8329_q))));
}

VL_INLINE_OPT void Vsynth_top::_combo__TOP__12(Vsynth_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth_top::_combo__TOP__12\n"); );
    Vsynth_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8377_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8378_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8374_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8375_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8350_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8351_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8347_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8348_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8206_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8207_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8186_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8187_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8035_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8036_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8203_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8204_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8044_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8045_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8380_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8381_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8061_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8062_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8005_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8006_q) 
               & 1U);
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8280_o 
            = (0x7fffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8281_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8152_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8153_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8146_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8147_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8143_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8144_q;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8377_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8375_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8374_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8372_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8350_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8348_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8347_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8345_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8206_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8204_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8186_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8184_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8035_o = 0x2f0U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8203_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8201_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8044_o = 0x280U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8380_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8378_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8061_o = 0x1ecU;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8005_o = 0U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8280_o 
            = (0x7fffU & ((IData)(0x7ffU) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8278_q)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8152_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8150_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8146_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8150_q) 
               ^ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8153_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8143_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8141_q;
    }
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7923_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7924_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7926_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7927_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7929_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7930_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7917_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7918_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7996_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7997_q) 
               & 1U);
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7970_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7971_q;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7923_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8327_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7926_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7924_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7929_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7924_q) 
               ^ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7927_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7917_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7915_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7996_o = 0U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7970_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8163_q;
    }
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8041_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8042_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8032_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8033_q;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8041_o = 0x27fU;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8032_o = 0x290U;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7957_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7958_q)
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8178_q));
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8371_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8372_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8209_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8210_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8070_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8071_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8168_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8169_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8090_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8091_q;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8371_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8363_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8209_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8207_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8070_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8068_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8168_o 
            = (0x3800U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8281_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8090_o = 0x1dfU;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7932_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7933_q)
            : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7915_q) 
               ^ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7918_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8212_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8213_q)
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8210_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7999_o 
        = (1U & ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)) 
                 | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8000_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8137_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8138_q)
            : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8141_q) 
               ^ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8144_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7993_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7994_q)
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7991_q));
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8353_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8354_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8011_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8012_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8029_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8030_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8332_o 
            = (0x1fU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8333_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8102_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8103_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8108_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8109_q;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8353_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8351_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8011_o = 2U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8029_o = 0x320U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8332_o 
            = (0x1fU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8281_q) 
                        >> 0xbU));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8102_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8100_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8108_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8106_q;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8162_o 
        = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8172_q) 
            & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)))
            ? ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8339_q))
                ? (0x7fffffffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8336_q) 
                                  << 0xbU)) : ((1U 
                                                == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8339_q))
                                                ? (
                                                   (0x7fffffffU 
                                                    & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8336_q) 
                                                       << 0xbU)) 
                                                   + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8169_q))
                                                : (0x7fffffffU 
                                                   & (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8166_q 
                                                      + 
                                                      ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8336_q) 
                                                       << 0xbU)))))
            : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8163_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8002_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8174_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8175_q)
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8172_q));
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7977_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7978_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7983_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7984_q;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7977_o 
            = (((~ (((1U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q)) 
                     & (2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q))) 
                    & (1U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q)))) 
                & (1U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q)))
                ? 0U : ((((1U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q)) 
                          & (2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q))) 
                         & (1U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q)))
                         ? 0x1000000U : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q))
                                          ? 0x800000U
                                          : 0U)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7983_o 
            = (((~ (((1U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q)) 
                     & (2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q))) 
                    & (1U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q)))) 
                & (1U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q)))
                ? 0U : ((((1U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q)) 
                          & (2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q))) 
                         & (1U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q)))
                         ? 0x1000000U : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q))
                                          ? 0x800000U
                                          : 0U)));
    }
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8087_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8088_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8052_o 
            = (0xfffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8053_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8452_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8453_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8344_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8345_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8183_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8184_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8020_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8021_q;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8087_o = 0U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8052_o 
            = (0xfffU & ((IData)(1U) + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8091_q) 
                                        - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8088_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8452_o 
            = (VL_GTES_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8261_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8088_q)) 
               & VL_LTS_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8261_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8091_q)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8344_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8183_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8181_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8020_o = 5U;
    }
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7980_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7981_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7986_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7987_q;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7980_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7997_q)
                ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1832_o)
                    ? 0U : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7981_q)
                : (((~ (((1U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q)) 
                         & (2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q))) 
                        & (1U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q)))) 
                    & (1U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q)))
                    ? 0U : ((((1U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q)) 
                              & (2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q))) 
                             & (1U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q)))
                             ? 0x1000000U : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q))
                                              ? 0x800000U
                                              : 0U))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7986_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7997_q)
                ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1832_o)
                    ? 0U : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7987_q)
                : (((~ (((1U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8130_q)) 
                         & (2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8130_q))) 
                        & (1U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8130_q)))) 
                    & (1U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8130_q)))
                    ? 0U : ((((1U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8130_q)) 
                              & (2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8130_q))) 
                             & (1U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8130_q)))
                             ? 0x1000000U : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8130_q))
                                              ? 0x800000U
                                              : 0U))));
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8384_o 
        = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8172_q) 
            & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)))
            ? ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8339_q))
                ? 0xfU : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8339_q))
                           ? 4U : ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3038_o))
                                    ? 4U : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3038_o))
                                             ? 2U : 
                                            ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3038_o))
                                              ? 1U : 8U)))))
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8385_q));
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8067_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8068_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8277_o 
            = (0x7fffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8278_q));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8067_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2321_o) 
               | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2236_o));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8277_o 
            = (0x7fffU & ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2656_o))
                           ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8269_q) 
                              << 2U) : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2656_o))
                                         ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8269_q) 
                                            << 1U) : 
                                        ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2656_o))
                                          ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8269_q)
                                          : ((IData)(3U) 
                                             * (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8269_q))))));
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8425_o 
        = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8213_q) 
            & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)))
            ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8381_q)
                ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8426_q
                : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3648_o)
            : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8426_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8038_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8039_q)
            : 0U);
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7964_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7965_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7960_o[0U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7961_q[0U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7960_o[1U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7961_q[1U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7960_o[2U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7961_q[2U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7960_o[3U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7961_q[3U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7946_o 
            = (0xffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7947_q));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7964_o 
            = vlTOPp->synth_top__DOT__app_rd_data_valid;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7960_o[0U] 
            = vlTOPp->synth_top__DOT__app_rd_data[0U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7960_o[1U] 
            = vlTOPp->synth_top__DOT__app_rd_data[1U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7960_o[2U] 
            = vlTOPp->synth_top__DOT__app_rd_data[2U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7960_o[3U] 
            = vlTOPp->synth_top__DOT__app_rd_data[3U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7946_o 
            = (0xffU & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7994_q) 
                         & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7991_q)))
                         ? 0xffU : ((IData)(vlTOPp->synth_top__DOT__app_rd_data_valid)
                                     ? ((IData)(1U) 
                                        + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7947_q))
                                     : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7947_q))));
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8189_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8190_q)
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8187_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7990_o 
        = (1U & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o)
                  ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7991_q)
                  : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8309_q) 
                     >> 0xbU)));
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8120_o 
            = (3U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8123_o 
            = (3U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8120_o 
            = (3U & ((8U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8012_q))
                      ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2236_o)
                          ? (((~ (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2269_o) 
                                   & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2293_o)) 
                                  & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2269_o))) 
                              & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2269_o))
                              ? 1U : ((((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2269_o) 
                                        & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2293_o)) 
                                       & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2269_o))
                                       ? 0U : ((((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q)) 
                                                 & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2266_o)) 
                                                & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q)))
                                                ? 2U
                                                : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q)
                                                    ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q)
                                                    : 0U))))
                          : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q))
                      : 0U));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8123_o 
            = (3U & ((8U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8012_q))
                      ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8118_q)
                          ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2321_o)
                              ? (((~ (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2354_o) 
                                       & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2378_o)) 
                                      & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2354_o))) 
                                  & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2354_o))
                                  ? 1U : ((((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2354_o) 
                                            & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2378_o)) 
                                           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2354_o))
                                           ? 0U : (
                                                   (((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q)) 
                                                     & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2351_o)) 
                                                    & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q)))
                                                    ? 2U
                                                    : 
                                                   ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q)
                                                     ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q)
                                                     : 0U))))
                              : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q))
                          : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q))
                      : 0U));
    }
    if (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8213_q) 
         & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8437_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8434_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8429_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8360_q)
                ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3648_o
                : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8426_q);
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8433_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8360_q)
                ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3648_o
                : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8430_q);
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8437_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8438_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8429_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8430_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8433_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8434_q;
    }
    if (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8210_q) 
         & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8197_o[0U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[0U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8197_o[1U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[1U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8197_o[2U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[2U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8197_o[3U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[3U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8197_o[4U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3574_o[4U];
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8197_o[0U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[0U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8197_o[1U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[1U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8197_o[2U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[2U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8197_o[3U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[3U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8197_o[4U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8198_q[4U];
    }
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8049_o 
            = (0xfffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8292_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8293_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8111_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8112_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8126_o 
            = (3U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8478_o 
            = (3U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8479_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8114_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8115_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8129_o 
            = (3U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8130_q));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8049_o 
            = (0xfffU & ((IData)(1U) + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8042_q) 
                                        - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8039_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8292_o 
            = (0x1fffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q) 
                          + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8269_q)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8111_o 
            = ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2602_o)) 
               & ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2407_o)) 
                  & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2236_o) 
                     | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8112_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8126_o 
            = (3U & ((8U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8012_q))
                      ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2602_o)
                          ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q)
                          : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2407_o)
                              ? (((~ (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2440_o) 
                                       & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2464_o)) 
                                      & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2440_o))) 
                                  & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2440_o))
                                  ? 1U : ((((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2440_o) 
                                            & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2464_o)) 
                                           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2440_o))
                                           ? 0U : (
                                                   (((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q)) 
                                                     & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2437_o)) 
                                                    & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q)))
                                                    ? 2U
                                                    : 
                                                   ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q)
                                                     ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q)
                                                     : 0U))))
                              : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q)))
                      : 0U));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8478_o 
            = (3U & ((VL_LTS_III(1,32,32, 0U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8479_q)) 
                      & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2491_o))
                      ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8479_q) 
                         - (IData)(1U)) : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8479_q)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8114_o 
            = ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2612_o)) 
               & ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2491_o)) 
                  & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2321_o) 
                     | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8115_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8129_o 
            = (3U & ((8U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8012_q))
                      ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8118_q)
                          ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2612_o)
                              ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8124_q)
                              : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2491_o)
                                  ? (((~ (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2524_o) 
                                           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2548_o)) 
                                          & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2524_o))) 
                                      & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2524_o))
                                      ? 1U : ((((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2524_o) 
                                                & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2548_o)) 
                                               & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2524_o))
                                               ? 0U
                                               : ((
                                                   ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q)) 
                                                    & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2521_o)) 
                                                   & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q)))
                                                   ? 2U
                                                   : 
                                                  ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8003_q)
                                                    ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8130_q)
                                                    : 0U))))
                                  : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8130_q)))
                          : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q))
                      : 0U));
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8421_o 
        = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8210_q) 
            & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)))
            ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3626_o
            : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8422_q);
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8081_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8082_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8055_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8056_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8064_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8065_q) 
               & 1U);
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8093_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8094_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8058_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8059_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8304_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8305_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8177_o 
            = (1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8178_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8165_o 
            = (0xffffffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8166_q);
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8014_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8015_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8017_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8018_q;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8081_o = 0U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8055_o = 0x20dU;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8064_o = 0U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8093_o = 0x1e0U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8058_o = 0x1eaU;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8304_o 
            = (0x1fffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8053_q) 
                          - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8275_q)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8177_o 
            = (1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8473_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8165_o 
            = (0xffffffU & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8006_q) 
                             & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8118_q))
                             ? ((1U & ((2U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q))
                                        ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8009_q) 
                                           >> 2U) : 
                                       ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8127_q))
                                         ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8009_q) 
                                            >> 1U) : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8009_q))))
                                 ? ((0xffeU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8473_q)) 
                                    * (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8169_q))
                                 : (((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8473_q)) 
                                     | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8178_q))
                                     ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8473_q) 
                                        * (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8169_q))
                                     : (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8473_q) 
                                         - (IData)(1U)) 
                                        * (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8169_q))))
                             : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8473_q) 
                                * (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8169_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8014_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8012_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8017_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8012_q;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7914_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7915_q)
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7654_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8008_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8009_q)
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7652_q));
    if (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7933_q) 
         & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o)))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7974_o 
            = (0x7fffffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7757_q);
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7950_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7676_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7954_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7668_q;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7974_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7975_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7950_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7951_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7954_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7955_q;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7708_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7709_q)
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7706_q));
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8105_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8106_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8099_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8100_q;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8105_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7737_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8099_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7733_q;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7523_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7524_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7589_o 
        = (1U & ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)) 
                 | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7590_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7538_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7539_q));
    if (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7657_q) 
         & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7671_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7664_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7679_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7660_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7760_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7750_q;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7671_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7672_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7679_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7680_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7760_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7761_q;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7520_o 
        = (1U & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)
                  ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7521_q)
                  : (~ (IData)(vlTOPp->synth_top__DOT__p_vs))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8117_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8118_q)
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7640_q));
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7532_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7533_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7702_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7703_q) 
               & 1U);
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7705_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7706_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7526_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7527_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7535_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7536_q) 
               & 1U);
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7529_o 
            = (1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7532_o 
            = (((IData)(vlTOPp->synth_top__DOT__p_b) 
                << 0x10U) | (((IData)(vlTOPp->synth_top__DOT__p_g) 
                              << 8U) | (IData)(vlTOPp->synth_top__DOT__p_r)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7702_o = 0U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7705_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7703_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7526_o 
            = vlTOPp->synth_top__DOT__p_de;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7535_o = 0U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7529_o 
            = (1U & (IData)(vlTOPp->synth_top__DOT__src__DOT__clkdiv));
    }
    if (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q) 
         & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7550_o = 0U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7578_o = 0U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7593_o = 2U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7597_o = 1U;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7635_o = 0U;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7550_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7551_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7578_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7579_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7593_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7594_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7597_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7598_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7635_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7636_q;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7811_o 
        = ((~ ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q) 
               & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)))) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7812_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7815_o 
        = ((~ ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q) 
               & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)))) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7816_q));
    if (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q) 
         & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7612_o 
            = (0x10U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7632_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7619_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7527_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7623_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7521_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7639_o 
            = VL_LTS_III(1,32,32, 0U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7636_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7696_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7693_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7778_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8053_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7831_o 
            = (0U != (7U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7594_q)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7839_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7533_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7843_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7840_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7847_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7844_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7851_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7848_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7855_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7852_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7859_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7856_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7871_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7766_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7875_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7872_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7879_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7876_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7883_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7880_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7887_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7602_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7891_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7888_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7895_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7892_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7899_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7896_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7903_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7900_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7907_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7904_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7546_o 
            = (0xfffU & ((IData)(1U) + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7555_q) 
                                        - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7551_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7554_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7590_q)
                ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7563_q)
                : 0U);
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7574_o 
            = (0xfffU & ((IData)(1U) + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7583_q) 
                                        - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7579_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7631_o 
            = (0x1fU & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7620_q) 
                         & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7527_q)))
                         ? 0U : (VL_GTS_III(1,32,32, 0x12U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7632_q))
                                  ? ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7632_q))
                                  : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7632_q))));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7612_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7613_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7619_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7620_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7623_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7624_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7639_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7640_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7696_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7697_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7778_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7779_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7831_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7832_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7839_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7840_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7843_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7844_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7847_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7848_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7851_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7852_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7855_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7856_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7859_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7860_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7871_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7872_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7875_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7876_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7879_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7880_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7883_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7884_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7887_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7888_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7891_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7892_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7895_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7896_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7899_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7900_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7903_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7904_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7907_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7908_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7546_o 
            = (0xfffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7547_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7554_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7555_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7574_o 
            = (0xfffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7575_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7631_o 
            = (0x1fU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7632_q));
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7699_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7700_q)
            : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q) 
               & ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7693_q)) 
                  & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7697_q))));
    if (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q) 
         & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7863_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7812_q)
                ? ((((1U & (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8496_q 
                                    >> 0x32U))) ? 0U
                      : ((1U & (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8496_q 
                                        >> 0x32U)))
                          ? 0xffU : (0xffU & (IData)(
                                                     (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8496_q 
                                                      >> 0x2aU))))) 
                    << 0x10U) | ((((1U & (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8496_q 
                                                  >> 0x21U)))
                                    ? 0U : ((1U & (IData)(
                                                          (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8496_q 
                                                           >> 0x21U)))
                                             ? 0xffU
                                             : (0xffU 
                                                & (IData)(
                                                          (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8496_q 
                                                           >> 0x19U))))) 
                                  << 8U) | ((1U & (IData)(
                                                          (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8496_q 
                                                           >> 0x10U)))
                                             ? 0U : 
                                            ((1U & (IData)(
                                                           (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8496_q 
                                                            >> 0x10U)))
                                              ? 0xffU
                                              : (0xffU 
                                                 & (IData)(
                                                           (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8496_q 
                                                            >> 8U)))))))
                : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7860_q);
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7732_o 
            = (1U & ((~ (IData)(vlTOPp->synth_top__DOT__p_vs)) 
                     & (((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7640_q)) 
                         | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7648_q)) 
                        | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7539_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7736_o 
            = (1U & ((~ (IData)(vlTOPp->synth_top__DOT__p_vs)) 
                     & (((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7640_q)) 
                         | (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7648_q))) 
                        | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7539_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7582_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7590_q)
                ? ((((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7640_q)) 
                     | (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7524_q))) 
                    & ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7624_q)) 
                       & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7521_q)))
                    ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7567_q)
                    : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7583_q))
                : ((((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7640_q)) 
                     | (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7524_q))) 
                    & ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7624_q)) 
                       & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7521_q)))
                    ? 0U : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7583_q)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7601_o 
            = (VL_LTES_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7587_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7583_q)) 
               & (VL_GTES_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7587_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7579_q)) 
                  & (VL_LTES_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7559_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7555_q)) 
                     & VL_GTES_III(1,32,32, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7559_q), (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7551_q)))));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7863_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7864_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7732_o 
            = (1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7733_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7736_o 
            = (1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7737_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7582_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7583_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7601_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7602_q;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7561_o 
        = ((((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7620_q) 
             & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7527_q))) 
            & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q)) 
           & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7646_o 
        = ((((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7620_q)) 
             & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7527_q)) 
            & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q)) 
           & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7806_o 
        = (((0x10U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7632_q)) 
            & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q)) 
           & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7774_o 
        = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q) 
            & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)))
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8050_q)
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7775_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7685_o 
        = (7U & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)
                  ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7686_q)
                  : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1405_o)
                      ? 0U : (VL_GTS_III(1,32,32, 5U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7686_q))
                               ? ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7686_q))
                               : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7686_q)))));
    if (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1405_o) 
         & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7667_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7672_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7675_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7680_q;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7667_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7668_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7675_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7676_q;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7682_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7683_q)
            : ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1405_o)) 
               & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7657_q) 
                  | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7683_q))));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7756_o 
        = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1405_o) 
            & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)))
            ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7761_q
            : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7757_q);
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7718_o 
        = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n925_o) 
            & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q)) 
           & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)));
    if (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q) 
         & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7726_o 
            = (0xfU & ((0x11U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7632_q))
                        ? 0U : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n925_o)
                                 ? ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q))
                                 : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7643_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7640_q) 
               & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n374_o));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7570_o 
            = (0xfffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7640_q)
                          ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n374_o)
                              ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7575_q)
                              : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7575_q) 
                                 << 1U)) : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7575_q)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7769_o 
            = (1U & ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7816_q)) 
                     | ((0x10U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7632_q))
                         ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n424_o) 
                            | (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n397_o)))
                         : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7770_q))));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7726_o 
            = (0xfU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7727_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7643_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7644_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7570_o 
            = (0xfffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7571_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7769_o 
            = (1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7770_q));
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8274_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8275_q)
            : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2491_o)
                ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1660_o)
                : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8275_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7558_o 
        = (0xfffU & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q) 
                      & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)))
                      ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n252_o)
                          ? 0U : ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7559_q)))
                      : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7559_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7565_o 
        = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n252_o) 
            & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q)) 
           & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)));
    if (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q) 
         & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7586_o 
            = (0xfffU & ((0x10U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7632_q))
                          ? ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7587_q))
                          : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n186_o)
                              ? 0U : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7587_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7605_o 
            = ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n186_o)) 
               & (((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7624_q)) 
                   & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7521_q)) 
                  | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7606_q)));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7586_o 
            = (0xfffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7587_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7605_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7606_q;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7662_o 
        = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n186_o) 
            & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q)) 
           & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7650_o 
        = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n186_o) 
            & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q)) 
           & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)));
    if (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q) 
         & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7796_o 
            = ((0xc00U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7793_q)) 
               | ((0x200U & ((~ (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n530_o 
                                 >> 0x10U)) << 9U)) 
                  | ((0x100U & ((~ (1U & (((0x10000U 
                                            & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n530_o)
                                            ? (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n530_o 
                                               + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7547_q) 
                                                  << 1U))
                                            : (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n530_o 
                                               - ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7547_q) 
                                                  << 1U))) 
                                          >> 0x10U))) 
                                << 8U)) | (0xffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7793_q)))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7765_o 
            = (1U & ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7812_q)) 
                     | ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7602_q)
                         ? (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n452_o))
                         : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7766_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7803_o 
            = (0x1fffU & ((0x10U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7632_q))
                           ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7547_q) 
                              - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7775_q))
                           : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7602_q)
                               ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n452_o)
                                   ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7804_q) 
                                      + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7775_q) 
                                         << 1U)) : 
                                  (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7804_q) 
                                    + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7775_q) 
                                       << 1U)) - ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7547_q) 
                                                  << 1U)))
                               : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7804_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7712_o 
            = (0x1fU & (((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7598_q)) 
                         | (3U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7598_q)))
                         ? (((IData)(0x7ffU) + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1658_o) 
                                                << 1U)) 
                            >> 0xbU) : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7598_q))
                                         ? (((IData)(0x7ffU) 
                                             + ((IData)(3U) 
                                                * (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1658_o))) 
                                            >> 0xbU)
                                         : (((IData)(0x7ffU) 
                                             + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1658_o) 
                                                << 2U)) 
                                            >> 0xbU))));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7796_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7797_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7765_o 
            = (1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7766_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7803_o 
            = (0x1fffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7804_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7712_o 
            = (0x1fU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7713_q));
    }
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7722_o[0U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7723_q[0U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7722_o[1U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7723_q[1U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7722_o[2U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7723_q[2U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7722_o[3U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7723_q[3U];
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7722_o[0U] 
            = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7775_q) 
                << 0x10U) | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7779_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7722_o[1U] 
            = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1660_o) 
                << 0x10U) | (0xffffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7713_q) 
                                        << 0xbU)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7722_o[2U] 
            = (IData)((((QData)((IData)((0x1000800U 
                                         | ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7598_q) 
                                            << 0x10U)))) 
                        << 0x20U) | (QData)((IData)(
                                                    (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7543_q) 
                                                      << 0x15U) 
                                                     | ((0x100000U 
                                                         & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7594_q) 
                                                            << 0x11U)) 
                                                        | (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7816_q) 
                                                            << 0x13U) 
                                                           | (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7812_q) 
                                                               << 0x12U) 
                                                              | (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7648_q) 
                                                                  << 0x11U) 
                                                                 | (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7640_q) 
                                                                     << 0x10U) 
                                                                    | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1658_o)))))))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7722_o[3U] 
            = (IData)(((((QData)((IData)((0x1000800U 
                                          | ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7598_q) 
                                             << 0x10U)))) 
                         << 0x20U) | (QData)((IData)(
                                                     (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7543_q) 
                                                       << 0x15U) 
                                                      | ((0x100000U 
                                                          & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7594_q) 
                                                             << 0x11U)) 
                                                         | (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7816_q) 
                                                             << 0x13U) 
                                                            | (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7812_q) 
                                                                << 0x12U) 
                                                               | (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7648_q) 
                                                                   << 0x11U) 
                                                                  | (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7640_q) 
                                                                      << 0x10U) 
                                                                     | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1658_o)))))))))) 
                       >> 0x20U));
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8268_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8269_q)
            : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2491_o)
                ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1658_o)
                : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8269_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7542_o 
        = (7U & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1258_o) 
                  & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)))
                  ? ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7543_q))
                  : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7543_q)));
    if (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q) 
         & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8495_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n689_o;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7867_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7816_q)
                ? ((((1U & (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n875_o 
                                    >> 0x32U))) ? 0U
                      : ((1U & (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n875_o 
                                        >> 0x32U)))
                          ? 0xffU : (0xffU & (IData)(
                                                     (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n875_o 
                                                      >> 0x2aU))))) 
                    << 0x10U) | ((((1U & (IData)((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n875_o 
                                                  >> 0x21U)))
                                    ? 0U : ((1U & (IData)(
                                                          (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n875_o 
                                                           >> 0x21U)))
                                             ? 0xffU
                                             : (0xffU 
                                                & (IData)(
                                                          (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n875_o 
                                                           >> 0x19U))))) 
                                  << 8U) | ((1U & (IData)(
                                                          (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n875_o 
                                                           >> 0x10U)))
                                             ? 0U : 
                                            ((1U & (IData)(
                                                           (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n875_o 
                                                            >> 0x10U)))
                                              ? 0xffU
                                              : (0xffU 
                                                 & (IData)(
                                                           (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n875_o 
                                                            >> 8U)))))))
                : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7864_q);
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8495_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8496_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7867_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7868_q;
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7688_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7689_q)
            : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q) 
               & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n925_o) 
                  & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1083_o))));
    if (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q) 
         & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o)))) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7692_o 
            = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7770_q) 
                & ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7904_q)) 
                   & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7908_q))) 
               | ((~ ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1083_o) 
                      & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n925_o))) 
                  & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7693_q)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7788_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n511_o;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7792_o 
            = ((0x800U & ((~ (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n492_o 
                              >> 0x10U)) << 0xbU)) 
               | (0x400U & ((~ (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n511_o 
                                >> 0x10U)) << 0xaU)));
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7692_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7693_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7788_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7789_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7792_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7793_q;
    }
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n136_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7608_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7609_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7743_o 
            = (0xffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7744_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7746_o[0U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[0U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7746_o[1U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[1U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7746_o[2U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[2U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7746_o[3U] 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[3U];
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7656_o 
            = (1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7657_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7659_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7660_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7715_o 
            = (0x1fU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7716_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7749_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7750_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7752_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7753_q;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7608_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1282_o) 
               | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1258_o));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7743_o 
            = (0xffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1282_o)
                         ? ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7744_q))
                         : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7709_q)
                             ? 0x7fU : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1258_o)
                                         ? 0U : (((0x11U 
                                                   == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7632_q)) 
                                                  & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q))
                                                  ? 0xffU
                                                  : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7744_q))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7746_o[0U] 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1258_o)
                ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7723_q[0U]
                : (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n925_o) 
                    & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q))
                    ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1038_o[0U]
                    : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[0U]));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7746_o[1U] 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1258_o)
                ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7723_q[1U]
                : (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n925_o) 
                    & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q))
                    ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1038_o[1U]
                    : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[1U]));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7746_o[2U] 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1258_o)
                ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7723_q[2U]
                : (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n925_o) 
                    & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q))
                    ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1038_o[2U]
                    : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[2U]));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7746_o[3U] 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1258_o)
                ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7723_q[3U]
                : (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n925_o) 
                    & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q))
                    ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1038_o[3U]
                    : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7747_q[3U]));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7656_o 
            = (1U & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1345_o) 
                      & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1336_o))
                      ? (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7536_q))
                      : (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1298_o) 
                          & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1282_o))
                          ? (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7536_q))
                          : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1258_o) 
                             & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7536_q))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7659_o 
            = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1345_o) 
                & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1336_o))
                ? (0U != ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7744_q) 
                          >> 7U)) : (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1298_o) 
                                      & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1282_o))
                                      ? (0U != (((IData)(1U) 
                                                 + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7744_q)) 
                                                >> 7U))
                                      : ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1258_o)) 
                                         & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7660_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7715_o 
            = (0x1fU & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1345_o) 
                         & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1336_o))
                         ? ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7716_q))
                         : (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1298_o) 
                             & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1282_o))
                             ? ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7716_q))
                             : (((0x10U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7632_q)) 
                                 & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7530_q))
                                 ? 0U : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7716_q)))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7749_o 
            = (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1345_o) 
                & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1336_o))
                ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7753_q
                : (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1298_o) 
                    & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1282_o))
                    ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7753_q
                    : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1258_o)
                        ? 0U : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7750_q)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7752_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1336_o)
                ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1345_o)
                    ? (((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7644_q)) 
                        & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7640_q))
                        ? (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7753_q 
                           + (0x7fffffffU & (((IData)(1U) 
                                              + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7713_q)) 
                                             << 0xbU)))
                        : ((IData)(0x800U) + vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7753_q))
                    : (((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7644_q)) 
                        & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7640_q))
                        ? (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7753_q 
                           + (0x7fffffffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7713_q) 
                                             << 0xbU)))
                        : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1326_o))
                : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1326_o);
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n114_o 
        = (1U & (~ (IData)(vlTOPp->reset_na)));
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8140_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8141_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8149_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8150_q;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8140_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7968_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8149_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7967_q;
    }
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1742_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7940_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7941_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7937_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7938_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8590_o 
            = (0x1ffffffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8591_q);
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7920_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7921_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7911_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7912_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7943_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7944_q;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7940_o 
            = ((4U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o)) 
               & ((2U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o)) 
                  & ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o)) 
                     & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7935_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7937_o 
            = ((4U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o)) 
               & ((2U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o)) 
                  & ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o)) 
                     & ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7935_q)) 
                        & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7934_q)))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8590_o 
            = (0x1ffffffU & ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o))
                              ? (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7958_q)
                                   ? (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7971_q 
                                      + vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7987_q)
                                   : (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7971_q 
                                      + vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7981_q)) 
                                 >> 4U) : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o))
                                            ? vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8591_q
                                            : ((1U 
                                                == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o))
                                                ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7935_q)
                                                    ? 
                                                   ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7955_q)
                                                     ? 
                                                    ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7975_q 
                                                      >> 4U) 
                                                     + 
                                                     (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7984_q 
                                                      >> 4U))
                                                     : 
                                                    ((vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7975_q 
                                                      >> 4U) 
                                                     + 
                                                     (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7978_q 
                                                      >> 4U)))
                                                    : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8591_q)
                                                : 0U))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7920_o 
            = ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o)) 
               & (~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1979_o)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7911_o 
            = ((4U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o)) 
               & ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o)) 
                  & ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1956_o)) 
                     | (0x7fU != (0x7fU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7944_q))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7943_o 
            = ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o))
                ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2129_o)
                : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o))
                    ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2129_o)
                    : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n1990_o))
                        ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7935_q)
                            ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7951_q)
                                ? 0x80U : 0U) : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2129_o))
                        : 0U)));
    }
    if (vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2219_o) {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8326_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8327_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8171_o 
            = (1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8172_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8335_o 
            = (0x1fU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8336_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8298_o 
            = (0x3fffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8299_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8463_o 
            = (1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8464_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8472_o 
            = (0xfffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8473_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8301_o 
            = (0x3fffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8302_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8134_o 
            = (0xfU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8135_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8412_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8413_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8359_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8360_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8271_o 
            = (0xfffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8272_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8356_o 
            = (3U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8357_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8415_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8416_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8289_o 
            = (0x3fffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8290_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8295_o 
            = (0x3fffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8296_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8387_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8388_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8469_o 
            = (0xfffU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8470_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8362_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8363_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8200_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8201_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8192_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8193_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8341_o 
            = (0xfU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8365_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8366_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8368_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8369_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8323_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8324_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8320_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8321_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8475_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8476_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8338_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8339_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8180_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8181_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8396_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8399_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8400_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8402_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8403_q;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8405_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8406_q;
    } else {
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8326_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8328_q) 
               & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8000_q));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8171_o 
            = (1U & (IData)((4U == (0xfU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o)))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8335_o 
            = (0x1fU & ((8U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                         ? ((4U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                             ? 0U : ((2U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                      ? 0U : ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                               ? 0U
                                               : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8138_q)
                                                   ? 
                                                  ((IData)(1U) 
                                                   + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8336_q))
                                                   : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8336_q)))))
                         : ((4U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                             ? ((2U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                 ? 0U : ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                          ? 0U : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8336_q)))
                             : ((2U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                 ? 0U : ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                          ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8336_q)
                                          : 0U)))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8298_o 
            = (0x3fffU & ((8U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                           ? ((4U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                               ? 0U : ((2U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                        ? 0U : ((1U 
                                                 & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                                 ? 0U
                                                 : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8299_q))))
                           : ((4U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                               ? ((2U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                   ? 0U : ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                            ? 0U : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8299_q)))
                               : ((2U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                   ? ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                       ? 0U : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2763_o)
                                                ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8305_q)
                                                : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8324_q)
                                                    ? 
                                                   (VL_LTES_III(1,32,32, 0x2000U, 
                                                                (0x3fffU 
                                                                 & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2735_o))
                                                     ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8302_q)
                                                     : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2735_o)
                                                    : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8299_q))))
                                   : ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                       ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8299_q)
                                       : 0U)))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8463_o 
            = (1U & (IData)(((2U == (0xfU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))) 
                             & (0U == (1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2777_o))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8472_o 
            = (0xfffU & ((8U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                          ? ((4U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                              ? 0U : ((2U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                       ? 0U : ((1U 
                                                & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                                ? 0U
                                                : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8473_q))))
                          : ((4U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                              ? ((2U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                  ? 0U : ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                           ? 0U : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8473_q)))
                              : ((2U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                  ? ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                      ? 0U : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2777_o)
                                               ? ((IData)(1U) 
                                                  + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8473_q))
                                               : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2763_o)
                                                   ? 1U
                                                   : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8473_q))))
                                  : ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                      ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8473_q)
                                      : 0U)))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8301_o 
            = (0x3fffU & ((8U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                           ? ((4U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                               ? 0U : ((2U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                        ? 0U : ((1U 
                                                 & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                                 ? 0U
                                                 : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8302_q))))
                           : ((4U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                               ? ((2U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                   ? 0U : ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                            ? 0U : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8302_q)))
                               : ((2U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                   ? ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                       ? 0U : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2763_o)
                                                ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8305_q) 
                                                   + 
                                                   ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8275_q) 
                                                    << 1U))
                                                : (
                                                   VL_LTES_III(1,32,32, 0x2000U, 
                                                               (0x3fffU 
                                                                & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2735_o))
                                                    ? 
                                                   (0x1fffU 
                                                    & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8302_q) 
                                                       + 
                                                       ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8275_q) 
                                                        << 1U)))
                                                    : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2735_o)))
                                   : ((1U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2901_o))
                                       ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8302_q)
                                       : 0U)))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8134_o 
            = (0xfU & ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                        ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8135_q)
                        : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                            ? (VL_LTS_III(1,32,32, 0U, (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8135_q))
                                ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8135_q) 
                                   - (IData)(1U)) : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8135_q))
                            : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                                ? (VL_LTS_III(1,32,32, 0U, 
                                              (0xfU 
                                               & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8406_q) 
                                                  >> 8U)))
                                    ? (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8406_q) 
                                        >> 8U) - (IData)(1U))
                                    : 0U) : 0U))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8412_o 
            = ((4U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o)) 
               & ((2U != (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o)) 
                  & ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o)) 
                     & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q) 
                        >> 2U))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8359_o 
            = ((~ ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8360_q) 
                   & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8213_q))) 
               & ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                   ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8360_q)
                   : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                       ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8360_q)
                       : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o)) 
                          & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q) 
                              >> 2U) | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8360_q))))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8271_o 
            = (0xfffU & ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                          ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8272_q)
                          : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                              ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8272_q)
                              : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                                  ? ((4U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q))
                                      ? (VL_LTES_III(1,32,32, 2U, 
                                                     ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8269_q) 
                                                      + 
                                                      (0xfU 
                                                       & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8406_q) 
                                                          >> 8U))))
                                          ? (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8269_q) 
                                              + (0xfU 
                                                 & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8406_q) 
                                                    >> 8U))) 
                                             - (IData)(2U))
                                          : 0U) : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8272_q))
                                  : 0U))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8356_o 
            = (3U & ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                      ? ((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8357_q))
                          ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8357_q)
                          : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8357_q) 
                             - (IData)(1U))) : ((2U 
                                                 == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                                                 ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8357_q)
                                                 : 
                                                ((1U 
                                                  == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                                                  ? 
                                                 ((4U 
                                                   & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q))
                                                   ? 2U
                                                   : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8357_q))
                                                  : 0U))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8415_o 
            = ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o)) 
               & (0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8357_q)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8289_o 
            = (0x3fffU & ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                           ? ((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8357_q))
                               ? (VL_LTES_III(1,32,32, 0x4000U, 
                                              (0x7fffU 
                                               & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3212_o))
                                   ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8296_q)
                                   : vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3212_o)
                               : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8290_q))
                           : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                               ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8290_q)
                               : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                                   ? ((4U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q))
                                       ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8293_q)
                                       : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8290_q))
                                   : 0U))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8295_o 
            = (0x3fffU & ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                           ? ((0U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8357_q))
                               ? (VL_LTES_III(1,32,32, 0x4000U, 
                                              (0x7fffU 
                                               & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3212_o))
                                   ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8296_q) 
                                      + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8269_q) 
                                         << 1U)) : 
                                  ((0x7fffU & vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3212_o) 
                                   + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8269_q) 
                                      << 1U))) : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8296_q))
                           : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                               ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8296_q)
                               : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                                   ? ((4U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q))
                                       ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8293_q) 
                                          + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8269_q) 
                                             << 1U))
                                       : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8296_q))
                                   : 0U))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8387_o 
            = ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8388_q)
                : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                    ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8388_q)
                    : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                        ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3054_o)
                            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8385_q)
                            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8388_q))
                        : 0U)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8469_o 
            = (0xfffU & ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                          ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3252_o)
                              ? ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8470_q))
                              : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8470_q))
                          : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                              ? ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8470_q))
                              : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                                  ? ((4U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q))
                                      ? 0U : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8470_q))
                                  : 0U))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8362_o 
            = ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3252_o)
                    ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8470_q) 
                       >= (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8272_q))
                    : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8363_q))
                : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                    ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8363_q)
                    : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o)) 
                       & ((~ ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q) 
                              >> 2U)) & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8363_q)))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8200_o 
            = ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3277_o)
                : (2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8192_o 
            = ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                ? (((4U == (0x7fU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8181_q))) 
                    & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3277_o)) 
                   | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8193_q))
                : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o)) 
                   & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8193_q)));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8341_o 
            = (0xfU & ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                        ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3277_o)
                            ? ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q))
                            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q))
                        : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                            ? ((IData)(1U) + (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q))
                            : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                                ? ((4U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q))
                                    ? 0U : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8342_q))
                                : 0U))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8365_o 
            = ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3277_o)
                    ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8363_q)
                    : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8366_q))
                : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                    ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8366_q)
                    : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o)) 
                       & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8366_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8368_o 
            = ((4U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3277_o)
                    ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8366_q)
                    : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8369_q))
                : ((2U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o))
                    ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8369_q)
                    : ((1U == (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3438_o)) 
                       & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8369_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8323_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2921_o;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8320_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2917_o;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8475_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2938_o;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8338_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2928_o;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8180_o 
            = vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3447_o;
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8396_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2941_o)
                ? ((4U & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3707_o)
                            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2944_o)
                            : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o)
                                ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q) 
                                   >> 1U) : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q) 
                                             >> 2U))) 
                          << 2U)) | ((2U & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3707_o)
                                              ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o)
                                                  ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q)
                                                  : 
                                                 ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q) 
                                                  >> 1U))
                                              : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3717_o)
                                                  ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2944_o)
                                                  : 
                                                 ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o)
                                                   ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q)
                                                   : 
                                                  ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q) 
                                                   >> 1U)))) 
                                            << 1U)) 
                                     | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2944_o)))
                : ((6U & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o)
                            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q)
                            : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q) 
                               >> 1U)) << 1U)) | (1U 
                                                  & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8397_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8399_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2941_o)
                ? ((4U & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3707_o)
                            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2946_o)
                            : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o)
                                ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8400_q) 
                                   >> 1U) : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8400_q) 
                                             >> 2U))) 
                          << 2U)) | ((2U & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3707_o)
                                              ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o)
                                                  ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8400_q)
                                                  : 
                                                 ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8400_q) 
                                                  >> 1U))
                                              : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3717_o)
                                                  ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2946_o)
                                                  : 
                                                 ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o)
                                                   ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8400_q)
                                                   : 
                                                  ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8400_q) 
                                                   >> 1U)))) 
                                            << 1U)) 
                                     | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2946_o)))
                : ((6U & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o)
                            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8400_q)
                            : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8400_q) 
                               >> 1U)) << 1U)) | (1U 
                                                  & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8400_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8402_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2941_o)
                ? ((4U & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3707_o)
                            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2948_o)
                            : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o)
                                ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8403_q) 
                                   >> 1U) : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8403_q) 
                                             >> 2U))) 
                          << 2U)) | ((2U & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3707_o)
                                              ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o)
                                                  ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8403_q)
                                                  : 
                                                 ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8403_q) 
                                                  >> 1U))
                                              : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3717_o)
                                                  ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2948_o)
                                                  : 
                                                 ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o)
                                                   ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8403_q)
                                                   : 
                                                  ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8403_q) 
                                                   >> 1U)))) 
                                            << 1U)) 
                                     | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2948_o)))
                : ((6U & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o)
                            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8403_q)
                            : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8403_q) 
                               >> 1U)) << 1U)) | (1U 
                                                  & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8403_q))));
        vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8405_o 
            = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2941_o)
                ? ((0xf00U & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3707_o)
                                ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2954_o)
                                : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o)
                                    ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8406_q) 
                                       >> 4U) : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8406_q) 
                                                 >> 8U))) 
                              << 8U)) | ((0xf0U & (
                                                   ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3707_o)
                                                     ? 
                                                    ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o)
                                                      ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8406_q)
                                                      : 
                                                     ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8406_q) 
                                                      >> 4U))
                                                     : 
                                                    ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3717_o)
                                                      ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2954_o)
                                                      : 
                                                     ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o)
                                                       ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8406_q)
                                                       : 
                                                      ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8406_q) 
                                                       >> 4U)))) 
                                                   << 4U)) 
                                         | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n2954_o)))
                : ((0xff0U & (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n3488_o)
                                ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8406_q)
                                : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8406_q) 
                                   >> 4U)) << 4U)) 
                   | (0xfU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8406_q))));
    }
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7562_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7561_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7559_q)
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7563_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7647_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7646_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7524_q)
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7648_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7807_o 
        = (0x1fffU & ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7806_o)
                       ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n424_o)
                           ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7571_q) 
                              - (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7779_q))
                           : ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n397_o)
                               ? ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7808_q) 
                                  + ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7779_q) 
                                     << 1U)) : (((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7808_q) 
                                                 + 
                                                 ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7779_q) 
                                                  << 1U)) 
                                                - ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7571_q) 
                                                   << 1U))))
                       : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7808_q)));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7566_o 
        = ((IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7565_o)
            ? (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7587_q)
            : (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7567_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7663_o 
        = ((~ (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7662_o)) 
           & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7664_q));
    vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n14071_o 
        = ((4U & ((((IData)((2U == (3U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q)))) 
                    & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7650_o)) 
                   << 2U) | (0xfffffffcU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7652_q)))) 
           | ((2U & ((((IData)((1U == (3U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q)))) 
                       & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7650_o)) 
                      << 1U) | (0xfffffffeU & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7652_q)))) 
              | (1U & (((IData)((0U == (3U & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n8121_q)))) 
                        & (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7650_o)) 
                       | (IData)(vlTOPp->synth_top__DOT__dut__DOT__u_ascal__DOT__n7652_q)))));
}
