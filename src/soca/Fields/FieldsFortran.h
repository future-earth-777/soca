/*
 * (C) Copyright 2019-2020 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef SOCA_FIELDS_FIELDSFORTRAN_H_
#define SOCA_FIELDS_FIELDSFORTRAN_H_

#include "soca/Fields/Fields.h"
#include "soca/Geometry/Geometry.h"
#include "soca/GeometryIterator/GeometryIterator.h"
#include "soca/GetValuesTraj/GetValuesTraj.h"

// Forward declarations
namespace eckit {
  class Configuration;
}

namespace oops {
  class Variables;
}

namespace ufo {
  typedef int F90locs;
  typedef int F90goms;
}

namespace util {
  class DateTime;
  class Duration;
}

namespace soca {

  extern "C" {
    void soca_field_create_f90(Fields::Ftn * &, const Geometry::Ftn * const &,
                               const oops::Variables &);
    void soca_field_delete_f90(Fields::Ftn * &);
    void soca_field_copy_f90(const Fields::Ftn * const &,
                             const Fields::Ftn * const &);
    void soca_field_zero_f90(const Fields::Ftn * const &);
    void soca_field_self_add_f90(const Fields::Ftn * const &,
                                 const Fields::Ftn * const &);
    void soca_field_self_sub_f90(const Fields::Ftn * const &,
                                 const Fields::Ftn * const &);
    void soca_field_self_mul_f90(const Fields::Ftn * const &, const double &);
    void soca_field_axpy_f90(const Fields::Ftn * const &, const double &,
                             const Fields::Ftn * const &);
    void soca_field_dot_prod_f90(const Fields::Ftn * const &,
                                 const Fields::Ftn * const &, double &);
    void soca_field_self_schur_f90(const Fields::Ftn * const &,
                                   const Fields::Ftn * const &);
    void soca_field_random_f90(const Fields::Ftn * const &);
    void soca_field_dirac_f90(const Fields::Ftn * const &,
                              const eckit::Configuration * const *);
    void soca_field_add_incr_f90(const Fields::Ftn * const &,
                                 const Fields::Ftn * const &);
    void soca_field_diff_incr_f90(const Fields::Ftn * const &,
                                  const Fields::Ftn * const &,
                                  const Fields::Ftn * const &);
    void soca_field_change_resol_f90(const Fields::Ftn * const &,
                                     const Fields::Ftn * const &);
    void soca_field_read_file_f90(const Fields::Ftn * const &,
                                  const eckit::Configuration * const *,
                                  util::DateTime * const *);
    void soca_field_write_file_f90(const Fields::Ftn * const &,
                                   const eckit::Configuration * const *,
                                   const util::DateTime * const *);
    void soca_field_interp_nl_f90(const Fields::Ftn * const &,
                                  const ufo::F90locs &,
                                  const oops::Variables &,
                                  const ufo::F90goms &);
    void soca_field_interp_nl_traj_f90(const Fields::Ftn * const &,
                                       const ufo::F90locs &,
                                       const oops::Variables &,
                                       const ufo::F90goms &,
                                       const GetValuesTraj::Ftn * const &);
    void soca_field_interp_tl_f90(const Fields::Ftn * const &,
                                  const ufo::F90locs &,
                                  const oops::Variables &,
                                  const ufo::F90goms &,
                                  const GetValuesTraj::Ftn * const &);
    void soca_field_interp_ad_f90(const Fields::Ftn * const &,
                                  const ufo::F90locs &,
                                  const oops::Variables &,
                                  const ufo::F90goms &,
                                  const GetValuesTraj::Ftn * const &);

    void soca_field_ug_coord_f90(const Fields::Ftn * const &, const int &);
    void soca_field_field_to_ug_f90(const Fields::Ftn * const &,
                                    const int &,
                                    const int &);
    void soca_field_field_from_ug_f90(const Fields::Ftn * const &,
                                      const int &,
                                      const int &);

    void soca_field_gpnorm_f90(const Fields::Ftn * const &,
                               const int &, double &);
    void soca_field_getpoint_f90(const Fields::Ftn * const &,
                                 const GeometryIterator::Ftn * const &,
                                 double &, const int &);
    void soca_field_setpoint_f90(Fields::Ftn * &,
                                 const GeometryIterator::Ftn * const &,
                                 const double &, const int &);
    void soca_field_sizes_f90(const Fields::Ftn * const &, int &, int &, int &,
                              int &, int &, int &);


    void soca_field_rms_f90(const Fields::Ftn * const &, double &);
  }
}  // namespace soca
#endif  // SOCA_FIELDS_FIELDSFORTRAN_H_
