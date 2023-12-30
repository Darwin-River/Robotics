The Line Racer robot chassis can be printed with PLA using the OpenSCAD code provided below.

Since OpenSCAD is a paremetric modeling system, chassis dimensions can easily be scaled and adjusted by changing the parameters at the start of the porgram.

The [OpenSCAD Cheat Sheet](https://openscad.org/cheatsheet/index.html) is a great way to learn the simple modeling language that was used to build this chasis.

You can download the sofware for free at [OpenSCAD.org](https://openscad.org/) 

```
// All measurements are given in mm.
cbLength = 55;
cbWidth = 2.2;
cbHeight = 58;

servoLength = 23;
servoWidth = 12.5;
servoHeight = 17.5;

servoWireWidth = 4.6;
servoTerminalWidth = 10;
servoTabThickness = 2.55;
servoTabLength = 32.25;

batteryLength = 63;
batteryWidth =17;
batteryHeight = 58.0;

marbleDiameter = 16.6;
marbleOffset = 7;

baseLength = batteryLength+15;
baseHeight = baseLength;
baseWidth = servoTabLength;

$fn = 50; // Set the number of polygon faces.

rotate([-90,0,0]) difference() {
    ​union() {
        base();
        //translate([0,-baseWidth/2,16]) sphere(8);
        translate([baseLength/2-20,baseWidth/2-8,baseHeight]) rotate([0,0,0]) hardPoint();
        translate([-baseLength/2+20,baseWidth/2-8,baseHeight]) rotate([0,0,0]) hardPoint();
        translate([0,baseWidth/2-8,baseHeight]) rotate([0,0,0]) hardPoint();
    }

    translate([0,-baseWidth/2+5,baseHeight/2+servoTerminalWidth/2+5]) rotate([90,0,0]) cbCutout();
    ​translate([-baseLength/2,0,baseHeight/2]) 
        rotate([0,90,0]) rotate([0,0,-90]) servoCutout();
    translate([baseLength/2,0,baseHeight/2]) 
        rotate([0,-90,0]) rotate([0,0,-90]) servoCutout();
    translate([0,baseWidth/2,baseHeight/2]) rotate([90,0,0]) flagpoleCutout();
    translate([0,-baseWidth/2+12,batteryWidth/2+5]) rotate([-90,0,0]) batteryCutout();
    translate([0,marbleDiameter/2-marbleOffset-baseWidth/2,marbleDiameter/2+2]) marbleCutout();
}

module base() {
    translate([0,0,baseHeight/2])
        cube([baseLength, baseWidth, baseHeight], true);
}

module cbCutout() {
    margin = 5.5;
    doubleMargin = margin * 2;
    componentsWidth = 28;
    solderClearance = 3;
    translate([0, 0, -cbHeight/2]) union() {
        cube([cbLength, cbWidth, cbHeight], true);
        translate([0, componentsWidth/2-solderClearance,0])
            cube([cbLength-doubleMargin, componentsWidth, cbHeight], true);
    }
}

module servoCutout() {
    wireClearance = 2;
    cylinderLength = 50;
    translate([0, 0, servoHeight/2 + servoTabThickness])
    union() {
        cube([servoLength, servoWidth, servoHeight], true);
        translate([-wireClearance,0,0]) cube([servoLength, servoWireWidth, servoHeight], true);
        translate([0,0,-(servoHeight+servoTabThickness)/2])
            cube([servoTabLength, servoWidth, servoTabThickness], true);
        translate([-cylinderLength/2+servoLength/2,0,servoHeight/2])
            rotate([0,90,0])
                cylinder(h=cylinderLength, r=servoTerminalWidth/2, center=true);
    }
}  

module batteryCutout() {
    translate([0,0,batteryHeight/2])
        cube([batteryLength,batteryWidth,batteryHeight], true);
}  

module marbleCutout() {
    translate([0,0,0])
        cube(marbleDiameter + 1,true);
}

module flagpoleCutout() {
    diameter = 3;
    flagpoleDepth = 20;
    cylinder(h=flagpoleDepth*2, r=diameter/2, center=true);
}

module hardPoint() {
    hpHeight = 2;
    hpBottomRad = 7;
    hpTopRad = 3;
    boreDiam =2;
    translate([0,0,hpHeight/2]) difference() {
        cylinder(hpHeight,hpBottomRad,hpTopRad,true);
        cylinder(hpHeight*2,boreDiam/2, true);
    }
}
```
