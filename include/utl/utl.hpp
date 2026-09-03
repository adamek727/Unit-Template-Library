/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

// https://www.nist.gov/pml/owm/metric-si/si-units

#include "base/all.hpp"
#include "derived/all.hpp"
#include "base/constants.hpp"
#include "operators.hpp"
#include "literals.hpp"
#include "math.hpp"

namespace utl {

    // Constants

    constexpr Frequency<double> cesium_hyperfine_freq_d(CAESIUM_HYPERFINE_FREQ_VALUE);
    constexpr Frequency<float> cesium_hyperfine_freq_f(static_cast<float>(CAESIUM_HYPERFINE_FREQ_VALUE));

    constexpr Velocity<double> speed_of_light_d(SPEED_OF_LIGHT_IN_VACUUM_VALUE);
    constexpr Velocity<float> speed_of_light_f(static_cast<float>(SPEED_OF_LIGHT_IN_VACUUM_VALUE));

    constexpr ElectricCharge<float> elementary_charge_f(static_cast<float>(ELEMENTARY_CHARGE_VALUE));
    constexpr ElectricCharge<double> elementary_charge_d(ELEMENTARY_CHARGE_VALUE);

    constexpr MulBaseUnits<float, Energy<float>, Time<float>> planck_constant_f(static_cast<float>(PLANCK_CONSTANT_VALUE));
    constexpr MulBaseUnits<double, Energy<double>, Time<double>> planck_constant_d(PLANCK_CONSTANT_VALUE);

    [[deprecated("use planck_constant_f")]] constexpr auto planc_constant_f = planck_constant_f;
    [[deprecated("use planck_constant_d")]] constexpr auto planc_constant_d = planck_constant_d;

    constexpr DivBaseUnits<float, Energy<float>, ThermodynamicTemperature<float>> boltzmann_constant_f(static_cast<float>(BOLTZMANN_CONSTANT_VALUE));
    constexpr DivBaseUnits<double, Energy<double>, ThermodynamicTemperature<double>> boltzmann_constant_d(
        BOLTZMANN_CONSTANT_VALUE);

    constexpr InvBaseUnit<float, AmountOfSubstance<float>> avogadro_constant_f(static_cast<float>(AVOGADRO_CONSTANT_VALUE));
    constexpr InvBaseUnit<double, AmountOfSubstance<double>> avogadro_constant_d(AVOGADRO_CONSTANT_VALUE);

    constexpr DivBaseUnits<float, LuminousFlux<float>, Power<float>> luminous_efficacy_f(static_cast<float>(LUMINOUS_EFFICACY_VALUE));
    constexpr DivBaseUnits<double, LuminousFlux<double>, Power<double>> luminous_efficacy_d(LUMINOUS_EFFICACY_VALUE);

    // Base Units

    using AmountOfSubstance_f = AmountOfSubstance<float>;
    using AmountOfSubstance_d = AmountOfSubstance<double>;

    using ElectricCurrent_f = ElectricCurrent<float>;
    using ElectricCurrent_d = ElectricCurrent<double>;

    using Length_f = Length<float>;
    using Length_d = Length<double>;

    using LuminousIntensity_f = LuminousIntensity<float>;
    using LuminousIntensity_d = LuminousIntensity<double>;

    using Mass_f = Mass<float>;
    using Mass_d = Mass<double>;

    using ThermodynamicTemperature_f = ThermodynamicTemperature<float>;
    using ThermodynamicTemperature_d = ThermodynamicTemperature<double>;

    using Time_f = Time<float>;
    using Time_d = Time<double>;

    // Derived Units

    using AbsorbedDose_f = AbsorbedDose<float>;
    using AbsorbedDose_d = AbsorbedDose<double>;

    using Acceleration_f = Acceleration<float>;
    using Acceleration_d = Acceleration<double>;

    using Activity_f = Activity<float>;
    using Activity_d = Activity<double>;

    using Angle_f = Angle<float>;
    using Angle_d = Angle<double>;

    using Area_f = Area<float>;
    using Area_d = Area<double>;

    using Capacitance_f = Capacitance<float>;
    using Capacitance_d = Capacitance<double>;

    using CatalyticActivity_f = CatalyticActivity<float>;
    using CatalyticActivity_d = CatalyticActivity<double>;

    using Conductance_f = Conductance<float>;
    using Conductance_d = Conductance<double>;

    using DoseEquivalent_f = DoseEquivalent<float>;
    using DoseEquivalent_d = DoseEquivalent<double>;

    using ElectricCharge_f = ElectricCharge<float>;
    using ElectricCharge_d = ElectricCharge<double>;

    using Energy_f = Energy<float>;
    using Energy_d = Energy<double>;

    using Force_f = Force<float>;
    using Force_d = Force<double>;

    using Frequency_f = Frequency<float>;
    using Frequency_d = Frequency<double>;

    using Illuminance_f = Illuminance<float>;
    using Illuminance_d = Illuminance<double>;

    using Inductance_f = Inductance<float>;
    using Inductance_d = Inductance<double>;

    using LuminousFlux_f = LuminousFlux<float>;
    using LuminousFlux_d = LuminousFlux<double>;

    using MagneticFlux_f = MagneticFlux<float>;
    using MagneticFlux_d = MagneticFlux<double>;

    using MagneticFluxDensity_f = MagneticFluxDensity<float>;
    using MagneticFluxDensity_d = MagneticFluxDensity<double>;

    using Power_f = Power<float>;
    using Power_d = Power<double>;

    using Pressure_f = Pressure<float>;
    using Pressure_d = Pressure<double>;

    using Resistance_f = Resistance<float>;
    using Resistance_d = Resistance<double>;

    using SolidAngle_f = SolidAngle<float>;
    using SolidAngle_d = SolidAngle<double>;

    using Velocity_f = Velocity<float>;
    using Velocity_d = Velocity<double>;

    using Voltage_f = Voltage<float>;
    using Voltage_d = Voltage<double>;

    using Volume_f = Volume<float>;
    using Volume_d = Volume<double>;

} // namespace utl
