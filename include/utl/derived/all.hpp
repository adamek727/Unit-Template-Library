/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "absorbed_dose.hpp"  // gray [Gy] (J/kg)
#include "activity.hpp"  // becquerel [Bq] (1/s)
#include "capacitance.hpp"  // farad [F] (C/V)
#include "catalytic_activity.hpp"  // katal [kat] (mol/s)
#include "conductance.hpp"  // siemens [S] (1/Ohm)
#include "dose_equivalent.hpp"  // sievert [Sv] (J/kg)
#include "electric_charge.hpp"  // coulomb [C] (A*s)
#include "energy.hpp"  // joule [J] (N*m)
#include "force.hpp"  // newton [N] kg*m/s^2
#include "frequency.hpp"  // hertz [Hz] (1/s)
#include "illuminance.hpp"  // lux [ls] (lm/m^2)
#include "inductance.hpp"  // henry [H] (Wb/A)
#include "luminous_flux.hpp"  // lumen [lm] (cd*sr)
#include "magnetic_flux.hpp"  // weber [Wb] (V*s)
#include "magnetic_flux_density.hpp"  // tesla [T] (Wb/m^2)
#include "power.hpp"  // watt [W] (J/s)
#include "pressure.hpp"  // pascal [Pa] (N/m^2)
#include "resistance.hpp"  // ohm [Ohm] (V/A)
#include "voltage.hpp"  // volt [V] (W/A)

#include "angle.hpp"  // radian [rad]
#include "solid_angle.hpp"  // steradian [sr]

// coherent derived units in terms of base units
#include "area.hpp"  // m^2
#include "volume.hpp"  // m^3
#include "velocity.hpp"  // m/s
#include "acceleration.hpp"  // m/s^2

// TODO:
//#include "vergence.hpp"  // 1/m
//#include "density.hpp"  // kg/m^3
//#include "surface_density.hpp"  // kg/m^2
//#include "specific_volume.hpp"  // m^3/kg
//#include "current_density.hpp"  // A/m^2
//#include "magnetic_filed_strength.hpp"  // A/m
//#include "concentration.hpp"  // mol/m^3
//#include "mass_concentration.hpp"  // kg/m^3
//#include "luminance.hpp"  // cd/m^2