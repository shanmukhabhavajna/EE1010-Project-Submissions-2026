// ==========================================
// TRANSFORMER + PERFBOARD BOX
// All dimensions in mm
// ==========================================

$fn = 64;

// ==========================================
// MAIN DIMENSIONS
// ==========================================

wall = 5;

// Lower section
lower_inner_w = 52;
lower_inner_d = 52;
lower_h = 50;

lower_outer_w = lower_inner_w + 2*wall; // 62
lower_outer_d = lower_inner_d + 2*wall; // 62

// Upper section
upper_inner_w = 72;
upper_inner_d = 52;

upper_outer_w = upper_inner_w + 2*wall; // 82
upper_outer_d = upper_inner_d + 2*wall; // 62

upper_h = 10;


// ==========================================
// SLIDING RAILS
// ==========================================

rail_width = 4;
rail_height = 2;
rail_z = 56;


// ==========================================
// MAIN BODY
// ==========================================

difference() {

    // ======================================
    // OUTER BODY
    // ======================================

    union() {

        // Lower section
        cube([
            lower_outer_w,
            lower_outer_d,
            lower_h
        ]);

        // Upper expanded section
        translate([
            (lower_outer_w - upper_outer_w)/2,
            0,
            lower_h
        ])
        cube([
            upper_outer_w,
            upper_outer_d,
            upper_h
        ]);

        // ----------------------------------
        // LEFT SLIDING RAIL
        // ----------------------------------

        translate([
            (lower_outer_w - upper_outer_w)/2 + wall,
            0,
            rail_z
        ])
        cube([
            rail_width,
            upper_outer_d,
            rail_height
        ]);

        // ----------------------------------
        // RIGHT SLIDING RAIL
        // ----------------------------------

        translate([
            (lower_outer_w - upper_outer_w)/2
            + upper_outer_w
            - wall
            - rail_width,
            0,
            rail_z
        ])
        cube([
            rail_width,
            upper_outer_d,
            rail_height
        ]);
    }


    // ======================================
    // LOWER TRANSFORMER CAVITY
    // ======================================

    translate([
        wall,
        wall,
        wall
    ])
    cube([
        lower_inner_w,
        lower_inner_d,
        lower_h + 1
    ]);


    // ======================================
    // UPPER OPENING
    // ======================================

    translate([
        (lower_outer_w - upper_inner_w)/2,
        wall,
        lower_h
    ])
    cube([
        upper_inner_w,
        upper_inner_d,
        upper_h + 1
    ]);


    // ======================================
    // LOWER HOLE
    // 38 x 18 mm
    // ======================================

    lower_hole_w = 38;
    lower_hole_h = 18;

    translate([
        (lower_outer_w - lower_hole_w)/2,
        -1,
        15
    ])
    cube([
        lower_hole_w,
        wall + 2,
        lower_hole_h
    ]);


    // ======================================
    // UPPER HOLE
    // 14.5 x 7 mm
    // ======================================

    upper_hole_w = 14.5;
    upper_hole_h = 7;

    translate([
        (upper_outer_w - upper_hole_w)/2
        + (lower_outer_w - upper_outer_w)/2,
        -1,
        lower_h + 2
    ])
    cube([
        upper_hole_w,
        wall + 2,
        upper_hole_h
    ]);
}
