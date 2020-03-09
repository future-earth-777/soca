/*
 * (C) Copyright 2017-2020  UCAR.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include <ostream>
#include <string>

#include "soca/Fields/Fields.h"
#include "soca/Geometry/Geometry.h"
#include "soca/Increment/Increment.h"
#include "soca/State/State.h"
#include "soca/Transforms/BkgErr/BkgErr.h"
#include "soca/Transforms/BkgErr/BkgErrFortran.h"

#include "eckit/config/Configuration.h"

#include "oops/util/Logger.h"

using oops::Log;

namespace soca {
  // -----------------------------------------------------------------------------
  BkgErr::BkgErr(const State & bkg,
                 const State & traj,
                 const Geometry & geom,
                 const eckit::Configuration & conf): traj_(traj) {
    const eckit::Configuration * configc = &conf;
    soca_bkgerr_setup_f90(ftn_, &configc, traj_.fields().toFortran());
  }
  // -----------------------------------------------------------------------------
  BkgErr::~BkgErr() {
    soca_bkgerr_delete_f90(ftn_);
  }
  // -----------------------------------------------------------------------------
  void BkgErr::multiply(const Increment & dxa, Increment & dxm) const {
    // dxm = K dxa
    soca_bkgerr_mult_f90(ftn_,
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
    soca_bkgerr_mult_f90(ftn_,
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
