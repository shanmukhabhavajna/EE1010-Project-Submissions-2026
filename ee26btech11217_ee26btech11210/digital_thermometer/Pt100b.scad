// ============================================
// PT100 THERMOMETER ENCLOSURE
// Dimensions in mm
// ============================================

length = 140;
width  = 100;
height = 70;

wall   = 3;
bottom = 3;

// ============================================
// LCD HEADER-PIN SLOT — FRONT WALL
// ============================================

lcd_width  = 48;
lcd_height = 2.5;
lcd_x = (length - lcd_width)/2;
lcd_z = 35;

// ============================================
// USB HOLE — RIGHT WALL
// Near the Arduino
// ============================================

usb_width  = 14.5;
usb_height = 8;
usb_y = 75;
usb_z = 20;

// ============================================
// POTENTIOMETER HOLE — RIGHT WALL
// Near the perfboard
// Diameter = 4 mm (0.4 cm)
// ============================================

pot_diameter = 4;
pot_y = 20;
pot_z = 20;

// ============================================
// PT100 HOLE — BOTTOM
// ============================================

pt100_diameter = 5.5;

// ============================================
// BOX WITH ALL OPENINGS
// ============================================

difference() {
    // Outer box
    cube([length, width, height]);

    // Hollow interior — open top
    translate([wall, wall, bottom])
        cube([
            length - 2*wall,
            width - 2*wall,
            height
        ]);

    // LCD header-pin slot — front wall
    translate([lcd_x, -0.1, lcd_z])
        cube([
            lcd_width,
            wall + 0.2,
            lcd_height
        ]);

    // USB opening — right wall, near Arduino
    translate([
        length - wall - 0.1,
        usb_y,
        usb_z
    ])
        cube([
            wall + 0.2,
            usb_width,
            usb_height
        ]);

    // Potentiometer hole — right wall, near perfboard
    translate([
        length - wall - 0.1,
        pot_y,
        pot_z
    ])
        rotate([0, 90, 0])
            cylinder(
                d = pot_diameter,
                h = wall + 0.2,
                $fn = 64
            );

    // PT100 hole — bottom centre
    translate([
        length/2,
        width/2,
        -1
    ])
        cylinder(
            d = pt100_diameter,
            h = bottom + 2,
            $fn = 64
        );
}

// ============================================
// PERFBOARD SUPPORTS — FRONT INNER WALL
// Perfboard: 70 x 50 mm
// ============================================

translate([(length-70)/2, wall, 8])
    cube([3, 5, 50]);

translate([(length-70)/2+67, wall, 8])
    cube([3, 5, 50]);

// ============================================
// ARDUINO SUPPORT — BACK INNER WALL
// Arduino frame: 125 x 65 mm
// ============================================

translate([
    (length-125)/2,
    width-wall-3,
    3
])
    cube([125, 3, 5]);