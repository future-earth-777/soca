/*
 * (C) Copyright 2017-2019  UCAR.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef SOCA_HORIZFILT_HORIZFILTFORTRAN_H_
#define SOCA_HORIZFILT_HORIZFILTFORTRAN_H_

#include "soca/Fortran.h"

// Forward declarations
namespace eckit {
  class Configuration;
}

namespace soca {

  extern "C" {
    void soca_horizfilt_setup_f90(F90balopmat &,
                                const eckit::Configuration * const *,
                                const F90flds &);
    void soca_horizfiltdelete_f90(F90balopmat &);
  }
}  // namespace soca

#endif  // SOCA_HORIZFILT_HORIZFILTFORTRAN_H_
