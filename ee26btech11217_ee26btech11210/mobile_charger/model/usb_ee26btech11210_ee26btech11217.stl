// ==========================================
// HOLLOW CUBOID
// INNER dimensions: 14 x 15 x 6.5 mm
// Wall thickness: 2 mm
// All dimensions in mm
// ==========================================

$fn = 64;

// ==========================================
// INNER DIMENSIONS
// ==========================================

inner_length = 14;
inner_depth  = 15;
inner_height = 6.5;

wall = 2;


// ==========================================
// OUTER DIMENSIONS
// ==========================================

outer_length = inner_length + 2*wall; // 18
outer_depth  = inner_depth + 2*wall;  // 19
outer_height = inner_height + 2*wall; // 10.5


// ==========================================
// HOLE DIMENSIONS
// ==========================================

hole_width  = 8;
hole_height = 5;


// ==========================================
// MAIN CUBOID
// ==========================================

difference() {

    // Outer cuboid
    cube([
        outer_length,
        outer_depth,
        outer_height
    ]);


    // ======================================
    // INTERNAL CAVITY
    // ======================================

    translate([
        wall,
        wall,
        wall
    ])
    cube([
        inner_length,
        inner_depth,
        inner_height
    ]);


    // ======================================
    // 8 x 5 mm HOLE
    // ON 14 x 6.5 mm FACE
    // ======================================

    translate([
        wall + (inner_length - hole_width)/2,
        -1,
        wall + (inner_height - hole_height)/2
    ])
    cube([
        hole_width,
        wall + 2,
        hole_height
    ]);


    // ======================================
    // OPPOSITE 14 x 6.5 mm FACE OPEN
    // ======================================

    translate([
        wall,
        outer_depth - wall - 1,
        wall
    ])
    cube([
        inner_length,
        wall + 2,
        inner_height
    ]);
}
