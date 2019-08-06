/*
 * (C) Copyright 2017-2018  UCAR.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include "soca/Transforms/BkgErr/BkgErr.h"

#include <ostream>
#include <string>

#include "oops/util/Logger.h"
#include "eckit/config/Configuration.h"
#include "BkgErrFortran.h"
#include "soca/Increment/Increment.h"
#include "soca/State/State.h"
#include "soca/Geometry/Geometry.h"

using oops::Log;

namespace soca {
  // -----------------------------------------------------------------------------
  BkgErr::BkgErr(const State & bkg,
                 const State & traj,
                 const Geometry & geom,
                 const eckit::Configuration & conf): traj_(traj) {
    const eckit::Configuration * configc = &conf;
    soca_bkgerr_setup_f90(keyFtnConfig_, &configc, traj_.fields().toFortran());
  }
  // -----------------------------------------------------------------------------
  BkgErr::~BkgErr() {
    soca_bkgerr_delete_f90(keyFtnConfig_);
  }
  // -----------------------------------------------------------------------------
  void BkgErr::multiply(const Increment & dxa, Increment & dxm) const {
    // dxm = K dxa
    soca_bkgerr_mult_f90(keyFtnConfig_,
                         dxa.fields().toFortran(),
                         dxm.fields().toFortran());
  }
  // -----------------------------------------------------------------------------
  void BkgErr::multiplyInverse(const Increment & dxm, Increment & dxa) const {
    dxa = dxm;
  }
  // -----------------------------------------------------------------------------
  void BkgErr::multiplyAD(const Increment & dxm, Increment & dxa) const {
    // dxa = K^T dxm
    soca_bkgerr_mult_f90(keyFtnConfig_,
                         dxm.fields().toFortran(),
                         dxa.fields().toFortran());
  }
  // -----------------------------------------------------------------------------
  void BkgErr::multiplyInverseAD(const Increment & dxa, Increment & dxm) const {
    dxm = dxa;
  }
  // -----------------------------------------------------------------------------
  void BkgErr::print(std::ostream & os) const {
    os << "SOCA change variable";
  }
  // -----------------------------------------------------------------------------
}  // namespace soca