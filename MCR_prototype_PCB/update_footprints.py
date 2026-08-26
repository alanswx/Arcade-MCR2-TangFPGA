import os
import re

folder = r"C:\Users\Effie Trinket\.gemini\antigravity\scratch\MCR_PRoject\MCR_prototype_PCB"
sch_files = [os.path.join(folder, f) for f in os.listdir(folder) if f.endswith('.kicad_sch')]

mapping = {
    "74AHC165": "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm",
    "74HC595": "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm",
    "ULN2803CDWR": "Package_SO:SOIC-18W_7.5x11.6mm_P1.27mm",
    "THS7374": "Package_SO:TSSOP-14_4.4x5mm_P0.65mm",
    "ADS7830": "Package_SO:TSSOP-16_4.4x5mm_P0.65mm",
    "LM2596T-5": "Package_TO_SOT_THT:TO-220-5_P3.4x3.7mm_StaggerOdd_Lead3.8mm_Vertical",
    "LM2596T-3.3": "Package_TO_SOT_THT:TO-220-5_P3.4x3.7mm_StaggerOdd_Lead3.8mm_Vertical",
    "SRV05-4": "Package_TO_SOT_SMD:SOT-23-6",
    "BAT54S": "Package_TO_SOT_SMD:SOT-23",
    "1N5824": "Diode_THT:D_DO-201AD_P15.24mm_Horizontal",
    "1N5822": "Diode_THT:D_DO-201AD_P15.24mm_Horizontal",
    "LED": "LED_SMD:LED_0805_2012Metric",
    "33 uH": "Inductor_SMD:L_Bourns_SRR1260",
    "680 uF": "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm",
    "220 uF": "Capacitor_THT:CP_Radial_D8.0mm_P3.50mm",
    "22 uF": "Capacitor_SMD:C_1210_3225Metric",
    "0.01 uF": "Capacitor_SMD:C_0805_2012Metric",
    "0.1 uF": "Capacitor_SMD:C_0805_2012Metric",
    "C_Small_US": "Capacitor_SMD:C_0805_2012Metric",
    "SW_DIP_x08": "Button_Switch_THT:SW_DIP_SPSTx08_Slide_9.78x22.5mm_W7.62mm_P2.54mm",
    "15 kHz Select": "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical",
    "Composite Sync Select": "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical",
    "Vertical Sync Inactive select": "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical",
    "Conn_02x20_Odd_Even": "Connector_PinSocket_2.54mm:PinSocket_2x20_P2.54mm_Vertical",
    "Conn_01x20_Pin": "Connector_PinHeader_2.54mm:PinHeader_1x20_P2.54mm_Horizontal",
    "Conn_01x09_Pin": "Connector_PinHeader_2.54mm:PinHeader_1x09_P2.54mm_Horizontal",
    "Conn_01x19_Pin": "Connector_PinHeader_2.54mm:PinHeader_1x19_P2.54mm_Horizontal",
    "Conn_01x23_Pin": "Connector_PinHeader_2.54mm:PinHeader_1x23_P2.54mm_Horizontal",
    "Conn_01x10_Pin": "Connector_PinHeader_2.54mm:PinHeader_1x10_P2.54mm_Horizontal",
    "DE15_Socket_HighDensity": "Connector_Dsub:DSUB-15-HD_Socket_Horizontal_P2.29x1.90mm_EdgePinOffset3.03mm_Housed_MountingHolesOffset4.94mm",
    "4.7k ohm": "Resistor_THT:R_Array_SIP9",
}

updated_total = 0

for filepath in sch_files:
    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()

    lib_pos = content.find('(lib_symbols')
    if lib_pos != -1:
        depth = 0
        end_pos = lib_pos
        for i in range(lib_pos, len(content)):
            if content[i] == '(': depth += 1
            elif content[i] == ')':
                depth -= 1
                if depth == 0:
                    end_pos = i
                    break
        head = content[:end_pos+1]
        tail = content[end_pos+1:]
    else:
        head = ""
        tail = content

    new_tail = []
    idx = 0
    while True:
        pos = tail.find('(symbol', idx)
        if pos == -1:
            new_tail.append(tail[idx:])
            break
        if pos > 0 and tail[pos-1] not in ('\n', '\r', '\t', ' ', '('):
            new_tail.append(tail[idx:pos+7])
            idx = pos + 7
            continue
        
        new_tail.append(tail[idx:pos])
        depth = 0
        block_end = pos
        for i in range(pos, len(tail)):
            if tail[i] == '(': depth += 1
            elif tail[i] == ')':
                depth -= 1
                if depth == 0:
                    block_end = i
                    break
        
        block = tail[pos:block_end+1]
        
        ref_m = re.search(r'\(property\s+"Reference"\s+"([^"]+)"', block)
        val_m = re.search(r'\(property\s+"Value"\s+"([^"]+)"', block)
        fp_m = re.search(r'\(property\s+"Footprint"\s+"([^"]*)"', block)
        
        if ref_m and val_m:
            ref = ref_m.group(1)
            val = val_m.group(1)
            curr_fp = fp_m.group(1) if fp_m else ""
            
            if not ref.startswith('#'):
                target_fp = mapping.get(val, "")
                if not target_fp:
                    pfx = re.match(r'([A-Za-z]+)', ref).group(1) if re.match(r'([A-Za-z]+)', ref) else ''
                    if pfx == 'R': target_fp = "Resistor_SMD:R_0805_2012Metric"
                    elif pfx == 'C': target_fp = "Capacitor_SMD:C_0805_2012Metric"
                    elif pfx == 'RN': target_fp = "Resistor_THT:R_Array_SIP9"
                
                if target_fp:
                    block = re.sub(r'\(property\s+"Footprint"\s+"[^"]*"', f'(property "Footprint" "{target_fp}"', block, count=1)
                    if target_fp != curr_fp:
                        updated_total += 1

        new_tail.append(block)
        idx = block_end + 1

    new_tail_str = "".join(new_tail)
    if head + new_tail_str != content:
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(head + new_tail_str)
        print(f"Updated footprints in {os.path.basename(filepath)}")

print(f"\nTotal footprint changes made: {updated_total}")

