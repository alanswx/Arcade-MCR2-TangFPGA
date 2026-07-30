// Lower-case port wrapper around fx68k, for VHDL instantiation on Gowin.
// Added 2026-07-30 (local, not upstream).
//
// Two separate GowinSynthesis problems make the upstream arrangement -
// `use work.fx68k.all` + a COMPONENT declaration in a package also named
// `fx68k` - unusable:
//
//   ERROR (EX4806) Primary unit of binding component 'fx68k' is not an entity
//     The package and the SystemVerilog module share the name `fx68k`, and the
//     binder resolves the component to the PACKAGE.
//   ERROR (EX4968) Cannot find port 'extreset' on cell 'fx68k'
//     Mixed-language port matching is CASE SENSITIVE here, and VHDL folds
//     identifiers to lower case, so `extReset`/`enPhi1`/`iEdb`/`eab` never
//     match.
//
// So: a wrapper whose ports are already lower case, with a name that does not
// collide with any package, instantiated from VHDL by direct entity
// instantiation (`entity work.fx68k_lc`) - the same mechanism mcr2.vhd uses to
// reach dpram.sv. No functional change; it is a pure rename layer.
module fx68k_lc(
    input         clk,
    input         extreset,
    input         pwrup,
    input         enphi1,
    input         enphi2,

    output        erwn,
    output        asn,
    output        ldsn,
    output        udsn,
    output        e,
    output        vman,
    output        fc0,
    output        fc1,
    output        fc2,
    output        bgn,
    output        oresetn,
    output        ohaltedn,
    input         dtackn,
    input         vpan,
    input         berrn,
    input         brn,
    input         bgackn,
    input         ipl0n,
    input         ipl1n,
    input         ipl2n,
    input  [15:0] iedb,
    output [15:0] oedb,
    output [23:1] eab
);

fx68k core (
    .clk(clk),
    .extReset(extreset),
    .pwrUp(pwrup),
    .enPhi1(enphi1),
    .enPhi2(enphi2),
    .eRWn(erwn),
    .ASn(asn),
    .LDSn(ldsn),
    .UDSn(udsn),
    .E(e),
    .VMAn(vman),
    .FC0(fc0),
    .FC1(fc1),
    .FC2(fc2),
    .BGn(bgn),
    .oRESETn(oresetn),
    .oHALTEDn(ohaltedn),
    .DTACKn(dtackn),
    .VPAn(vpan),
    .BERRn(berrn),
    .BRn(brn),
    .BGACKn(bgackn),
    .IPL0n(ipl0n),
    .IPL1n(ipl1n),
    .IPL2n(ipl2n),
    .iEdb(iedb),
    .oEdb(oedb),
    .eab(eab)
);

endmodule
