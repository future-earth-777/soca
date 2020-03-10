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
#include "soca/Transforms/HorizFilt/HorizFilt.h"
#include "soca/Transforms/HorizFilt/HorizFiltFortran.h"

#include "eckit/config/Configuration.h"

#include "oops/util/abor1_cpp.h"
#include "oops/util/Logger.h"

namespace soca {
  // -----------------------------------------------------------------------------
  HorizFilt::HorizFilt(const State & bkg,
                 const State & traj,
                 const Geometry & geom,
                 const eckit::Configuration & conf):
    geom_(new Geometry(geom)), vars_(conf), traj_(traj) {
    soca_horizfilt_setup_f90(ftn_,
                             &conf,
                             geom_->toFortran(),
                             traj_.fields().toFortran(),
                             vars_);

    // Get number of iterations
    niter_ = conf.getInt("niter");
  }
  // -----------------------------------------------------------------------------
  HorizFilt::~HorizFilt() {
    soca_horizfilt_delete_f90(ftn_);
  }
  // -----------------------------------------------------------------------------
  void HorizFilt::multiply(const Increment & dxin, Increment & dxout) const {
    dxout = dxin;
    Increment dx_tmp(dxin);
    for (unsigned int iter = 0; iter < niter_; ++iter) {
      dx_tmp = dxout;
      soca_horizfilt_mult_f90(ftn_,
                              dx_tmp.fields().toFortran(),
                              dxout.fields().toFortran());
    }
  }
  // -----------------------------------------------------------------------------
  void HorizFilt::multiplyInverse(const Increment & dxin, Increment & dxout)
    const {
    dxout = dxin;
  }
  // -----------------------------------------------------------------------------
  void HorizFilt::multiplyAD(const Increment & dxin, Increment & dxout) const {
    dxout = dxin;
    Increment dx_tmp(dxin);
    for (unsigned int iter = 0; iter < niter_; ++iter) {
      dx_tmp = dxout;
      soca_horizfilt_multad_f90(ftn_,
                                dx_tmp.fields().toFortran(),
                                dxout.fields().toFortran());
    }
  }
  // -----------------------------------------------------------------------------
  void HorizFilt::multiplyInverseAD(const Increment & dxin, Increment & dxout)
    const {
    dxout = dxin;
  }
  // -----------------------------------------------------------------------------
  void HorizFilt::print(std::ostream & os) const {
    os << "SOCA HorizFilt";
  }
  // -----------------------------------------------------------------------------
}  // namespace soca
