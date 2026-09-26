// 36 x 18 mm plate
// Thickness: 1 mm
// Center hole: 5.5 x 5.5 mm

difference() {

    // Main rectangle
    cube([36, 18, 1]);

    // Centered 5.5 x 5.5 mm hole
    translate([
        (36 - 5.5) / 2,
        (18 - 5.5) / 2,
        -1
    ])
    cube([5.5, 5.5, 3]);
}
