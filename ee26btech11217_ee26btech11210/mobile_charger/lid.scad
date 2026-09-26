// ==========================================
// SLIDING LID
// Matched to transformer_box.scad
// All dimensions in mm
// ==========================================

$fn = 64;


// ==========================================
// DIMENSIONS
// ==========================================

box_w = 82;
box_d = 62;

lid_thickness = 3;

clearance = 0.4;

rail_width = 4;
rail_height = 2;


// ==========================================
// LID SIZE
// ==========================================

lid_w = box_w - 1;
lid_d = box_d - 1;


// ==========================================
// LID WITH SIDE GROOVES
// ==========================================

difference() {

    // Main lid
    cube([
        lid_w,
        lid_d,
        lid_thickness
    ]);


    // ======================================
    // LEFT GROOVE
    // ======================================

    translate([
        5 - clearance,
        -1,
        -0.01
    ])
    cube([
        rail_width + clearance*2,
        lid_d + 2,
        rail_height + 0.01
    ]);


    // ======================================
    // RIGHT GROOVE
    // ======================================

    translate([
        lid_w - 5 - rail_width - clearance,
        -1,
        -0.01
    ])
    cube([
        rail_width + clearance*2,
        lid_d + 2,
        rail_height + 0.01
    ]);
}


// ==========================================
// PULL TAB
// ==========================================

translate([
    (lid_w - 20)/2,
    lid_d,
    0
])
cube([
    20,
    8,
    lid_thickness
]);
