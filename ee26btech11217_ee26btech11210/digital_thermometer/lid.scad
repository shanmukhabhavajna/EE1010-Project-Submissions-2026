// ============================================
// SLIDING LID — PT100 THERMOMETER
// All dimensions in mm
// ============================================

length = 140;
width  = 100;
wall   = 3;

// LID DIMENSIONS
lid_thickness = 7;
lid_overhang  = 2;

// FEMALE RAIL DIMENSIONS
groove_width = 3;
groove_depth = 5;
clearance    = 0.3;

// ============================================
// LID WITH FEMALE GROOVES
// ============================================

difference() {

    // Main lid plate
    translate([-lid_overhang, 0, 0])
        cube([
            length + 2*lid_overhang,
            width,
            lid_thickness
        ]);

    // Left female groove
    translate([
        -lid_overhang - 0.1,
        0,
        lid_thickness - groove_depth
    ])
        cube([
            wall + clearance + 0.1,
            width,
            groove_depth + 0.1
        ]);

    // Right female groove
    translate([
        length - wall - clearance,
        0,
        lid_thickness - groove_depth
    ])
        cube([
            wall + clearance + 0.1,
            width,
            groove_depth + 0.1
        ]);
}