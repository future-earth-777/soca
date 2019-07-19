/*
 * (C) Copyright 2017-2018  UCAR.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include "soca/Transforms/HorizFilt/HorizFilt.h"

#include <ostream>
#include <string>

#include "oops/util/Logger.h"
#include "eckit/config/Configuration.h"
#include "soca/Increment/Increment.h"
#include "soca/State/State.h"
#include "soca/Geometry/Geometry.h"

namespace soca {
  // -----------------------------------------------------------------------------
  HorizFilt::HorizFilt(const State & bkg,
                 const State & traj,
                 const Geometry & geom,
                 const eckit::Configuration & conf):
    vars_(conf) {
    soca_horizfilt_setup_f90();
  }
  // -----------------------------------------------------------------------------
  HorizFilt::~HorizFilt() {
  }
  // -----------------------------------------------------------------------------
  void HorizFilt::multiply(const Increment & dxa, Increment & dxm) const {
    dxm = dxa;
  }
  // -----------------------------------------------------------------------------
  void HorizFilt::multiplyInverse(const Increment & dxm, Increment & dxa)
    const {
    dxa = dxm;
  }
  // -----------------------------------------------------------------------------
  void HorizFilt::multiplyAD(const Increment & dxm, Increment & dxa) const {
    dxa = dxm;
  }
  // -----------------------------------------------------------------------------
  void HorizFilt::multiplyInverseAD(const Increment & dxa, Increment & dxm)
    const {
    dxm = dxa;
  }
  // -----------------------------------------------------------------------------
  void HorizFilt::print(std::ostream & os) const {
    os << "SOCA change variable";
  }
  // -----------------------------------------------------------------------------
}  // namespace soca
