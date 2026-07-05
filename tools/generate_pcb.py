import pcbnew
import sys
import os

def generate_board():
    print("Initializing KiCad board generation with net connections...")
    board = pcbnew.BOARD()

    # Define board dimensions: 120mm x 100mm (values in micrometers -> nanometers)
    width = 120.0
    height = 100.0
    margin = 5.0

    # Draw PCB Edge Outline on the Edge.Cuts layer
    edge_layer = board.GetLayerID("Edge.Cuts")
    
    # Coordinates in nanometers (1mm = 1,000,000 nm)
    x_min, y_min = int(margin * 1000000), int(margin * 1000000)
    x_max, y_max = int((width + margin) * 1000000), int((height + margin) * 1000000)

    corners = [
        pcbnew.VECTOR2I(x_min, y_min),
        pcbnew.VECTOR2I(x_max, y_min),
        pcbnew.VECTOR2I(x_max, y_max),
        pcbnew.VECTOR2I(x_min, y_max)
    ]

    for i in range(4):
        p1 = corners[i]
        p2 = corners[(i + 1) % 4]
        seg = pcbnew.PCB_SHAPE(board)
        seg.SetShape(pcbnew.SHAPE_T_SEGMENT)
        seg.SetStart(p1)
        seg.SetEnd(p2)
        seg.SetLayer(edge_layer)
        board.Add(seg)

    print("PCB Edge Outline drawn successfully!")

    # Dict to keep track of placed footprints for net connection
    placed_footprints = {}

    # Helper function to place footprints from standard library path
    def place_component(reference, value, lib_name, footprint_name, x_mm, y_mm, rotation_deg=0):
        lib_path = f"/Applications/KiCad/KiCad.app/Contents/SharedSupport/footprints/{lib_name}.pretty"
        
        # Load footprint
        fp = pcbnew.FootprintLoad(lib_path, footprint_name)
        if not fp:
            print(f"Error: Could not load footprint {footprint_name} from {lib_path}")
            sys.exit(1)
            
        fp.SetReference(reference)
        fp.SetValue(value)
        
        # Position (convert mm to nanometers)
        pos = pcbnew.VECTOR2I(int(x_mm * 1000000), int(y_mm * 1000000))
        fp.SetPosition(pos)
        
        if rotation_deg != 0:
            fp.SetOrientation(pcbnew.EDA_ANGLE(rotation_deg, pcbnew.DEGREES_T))
            
        board.Add(fp)
        placed_footprints[reference] = fp
        print(f"Placed {reference} ({value}) at X={x_mm}mm, Y={y_mm}mm")

    # --- Place Components ---
    # 1. Tang Console Host Sockets (2x20 Pin Headers spaced 50mm apart)
    place_component("JP1", "Tang_2x20_H1", "Connector_PinHeader_2.54mm", "PinHeader_2x20_P2.54mm_Vertical", 65.0, 45.0)
    place_component("JP2", "Tang_2x20_H2", "Connector_PinHeader_2.54mm", "PinHeader_2x20_P2.54mm_Vertical", 65.0, 65.0)

    # 2. MCR Top Connectors (Controls, Coin, Video, Power)
    place_component("J2", "MCR_P1_Controls", "Connector_PinHeader_2.54mm", "PinHeader_1x15_P2.54mm_Vertical", 20.0, 12.0)
    place_component("J3", "MCR_System_Coin", "Connector_PinHeader_2.54mm", "PinHeader_1x05_P2.54mm_Vertical", 55.0, 12.0)
    place_component("J_VID", "MCR_Video_Out", "Connector_PinHeader_2.54mm", "PinHeader_1x09_P2.54mm_Vertical", 85.0, 12.0)
    place_component("P_IN", "Power_+12V_GND", "Connector_PinHeader_2.54mm", "PinHeader_1x02_P2.54mm_Vertical", 115.0, 12.0)

    # 3. MCR Bottom Connectors (P2 Controls, Spinners, DIP Switches)
    place_component("J5", "MCR_P2_Controls", "Connector_PinHeader_2.54mm", "PinHeader_1x19_P2.54mm_Vertical", 25.0, 93.0)
    place_component("J4", "MCR_Opt_X_Dial", "Connector_PinHeader_2.54mm", "PinHeader_1x10_P2.54mm_Vertical", 75.0, 93.0)
    
    # 4. DIP Switch Blocks
    place_component("SW1", "Game_Selector", "Button_Switch_THT", "SW_DIP_SPSTx08_Slide_9.78x22.5mm_W7.62mm_P2.54mm", 100.0, 93.0)
    place_component("SW2", "Cabinet_Options", "Button_Switch_THT", "SW_DIP_SPSTx08_Slide_9.78x22.5mm_W7.62mm_P2.54mm", 115.0, 93.0)

    # --- Draw Electrical Wires (Ratsnest Connectivity) ---
    print("Defining and routing electrical nets...")
    
    # Net connections mapping: (NetName, Component1Ref, Pad1Number, Component2Ref, Pad2Number)
    connections = [
        ("BTN_LEFT",    "JP1", "1",  "J2", "1"),
        ("BTN_RIGHT",   "JP1", "2",  "J2", "2"),
        ("BTN_FIRE",    "JP1", "3",  "J2", "5"),
        ("BTN_SHIELD",  "JP1", "4",  "J2", "6"),
        ("BTN_START",   "JP1", "5",  "J3", "3"),
        ("BTN_COIN",    "JP1", "6",  "J3", "1"),
        ("BTN_SERVICE", "JP1", "7",  "J3", "2"),
        ("BTN_TILT",    "JP1", "8",  "J3", "5"),
        
        ("CAB_R0",      "JP1", "9",  "J_VID", "1"),
        ("CAB_G0",      "JP1", "12", "J_VID", "3"),
        ("CAB_B0",      "JP1", "15", "J_VID", "5"),
        ("CAB_HS",      "JP1", "18", "J_VID", "8"),
        ("CAB_VS",      "JP1", "19", "J_VID", "9"),
        
        # SW1 Game Selector DIPs (SW1 pads 1-8 are switches, 9-16 are ground)
        ("GAME_SEL0",   "JP1", "23", "SW1", "1"),
        ("GAME_SEL1",   "JP1", "24", "SW1", "2"),
        ("GAME_SEL2",   "JP1", "25", "SW1", "3"),
        ("GAME_SEL3",   "JP1", "26", "SW1", "4"),
        ("GAME_SEL4",   "JP1", "27", "SW1", "5"),
        ("GAME_SEL5",   "JP1", "28", "SW1", "6"),
        ("GAME_SEL6",   "JP1", "29", "SW1", "7"),
        ("GAME_SEL7",   "JP1", "30", "SW1", "8"),

        # SW2 Game Options DIPs
        ("GAME_OPT0",   "JP1", "31", "SW2", "1"),
        ("GAME_OPT1",   "JP1", "32", "SW2", "2"),
        ("GAME_OPT2",   "JP1", "33", "SW2", "3"),
        ("GAME_OPT3",   "JP1", "34", "SW2", "4"),
        ("GAME_OPT4",   "JP1", "35", "SW2", "5"),
        ("GAME_OPT5",   "JP1", "36", "SW2", "6"),
        ("GAME_OPT6",   "JP1", "37", "SW2", "7"),
        ("GAME_OPT7",   "JP1", "38", "SW2", "8"),
        
        # Ground signals
        ("GND",         "J2", "13",  "P_IN", "2"),
        ("GND",         "J4", "10",  "P_IN", "2"),
        ("GND",         "J_VID", "2", "P_IN", "2"),
        ("GND",         "J_VID", "4", "P_IN", "2"),
        ("GND",         "J_VID", "6", "P_IN", "2"),
        
        # 12V Power In
        ("12V_POWER",   "P_IN", "1",  "JP1", "40"), # Map power to the header pin
    ]

    for net_name, ref1, pad1, ref2, pad2 in connections:
        # Resolve or create the net
        net = board.FindNet(net_name)
        if not net:
            net = pcbnew.NETINFO_ITEM(board, net_name)
            board.Add(net)
            
        # Connect Pad 1
        fp1 = placed_footprints.get(ref1)
        if fp1:
            p_obj1 = fp1.FindPadByNumber(pad1)
            if p_obj1:
                p_obj1.SetNet(net)
                
        # Connect Pad 2
        fp2 = placed_footprints.get(ref2)
        if fp2:
            p_obj2 = fp2.FindPadByNumber(pad2)
            if p_obj2:
                p_obj2.SetNet(net)

    # Save board to file
    output_filename = "mcr_shield.kicad_pcb"
    pcbnew.SaveBoard(output_filename, board)
    print(f"KiCad board saved successfully as: {os.path.abspath(output_filename)}")

if __name__ == "__main__":
    generate_board()
