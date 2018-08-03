/*
 * (C) Copyright 2017 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef SOCA_MODEL_SOCAMODEL_H_
#define SOCA_MODEL_SOCAMODEL_H_

#include <ostream>
#include <string>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include "src/Fortran.h"
#include "src/Geometry/Geometry.h"
#include "oops/util/Duration.h"
#include "oops/util/ObjectCounter.h"
#include "oops/util/Printable.h"

// Forward declarations
namespace eckit {
  class Configuration;
}

namespace soca {
  //class F90traj;
  class ModelBias;
  class Fields;
  class State;

// -----------------------------------------------------------------------------
/// SOCA model definition.
/*!
 *  SOCA nonlinear model definition and configuration parameters.
 */

class Model: public util::Printable,
               private boost::noncopyable,
               private util::ObjectCounter<Model> {
 public:
  static const std::string classname() {return "soca::Model";}

  Model(const Geometry &, const eckit::Configuration &);
  ~Model();

/// Prepare model integration
  void initialize(State &) const;

/// Model integration
  void step(State &, const ModelBias &) const;
  int saveTrajectory(State &, const ModelBias &) const;

/// Finish model integration
  void finalize(State &) const;

/// Utilities
  const util::Duration & timeResolution() const {return tstep_;}

 private:
  void print(std::ostream &) const;
  int keyConfig_;
  util::Duration tstep_;
  const Geometry geom_;
};
// -----------------------------------------------------------------------------

}  // namespace soca
#endif  // SOCA_MODEL_SOCAMODEL_H_