/*
 * (C) Copyright 2017-2018  UCAR.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include "src/BalanceOperators/Kst.h"

#include <ostream>
#include <string>

#include "oops/util/Logger.h"
#include "eckit/config/Configuration.h"
#include "src/Geometry/Geometry.h"
#include "src/Increment/Increment.h"
#include "src/State/State.h"

using oops::Log;

namespace soca {
// -----------------------------------------------------------------------------
Kst::Kst(const eckit::Configuration &) {}
// -----------------------------------------------------------------------------
Kst::~Kst() {}
// -----------------------------------------------------------------------------
void Kst::linearize(const State & traj, const Geometry & geom) {
  traj_.reset(new State(traj));
  geom_.reset(new Geometry(geom));  
  Log::trace() << "Trajectory for Kst: " << traj <<std::endl;
  Log::trace() << "Geometry for Kst: " << geom <<std::endl;
}
// -----------------------------------------------------------------------------
void Kst::multiply(const Increment & dxa, Increment & dxm) const {
  Log::trace() << "Trajectory key for Kst: " << traj_->fields().toFortran() <<std::endl;
  Log::trace() << "Geometry key for Kst: " << geom_->toFortran() <<std::endl;  
  dxm = dxa;
}
// -----------------------------------------------------------------------------
void Kst::multiplyInverse(const Increment & dxm, Increment & dxa) const {
  dxa = dxm;
}
// -----------------------------------------------------------------------------
void Kst::multiplyAD(const Increment & dxm, Increment & dxa) const {
  Log::trace() << "Trajectory key for Kst: " << traj_->fields().toFortran() <<std::endl;
  Log::trace() << "Geometry key for KTst: " << geom_->toFortran() <<std::endl;  
  dxa = dxm;
}
// -----------------------------------------------------------------------------
void Kst::multiplyInverseAD(const Increment & dxa, Increment & dxm) const {
  dxm = dxa;
}
// -----------------------------------------------------------------------------
void Kst::print(std::ostream & os) const {
  os << "SOCA change variable";
}
// -----------------------------------------------------------------------------
}  // namespace soca
