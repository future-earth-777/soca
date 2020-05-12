/*
 * (C) Copyright 2017-2020 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include "soca/Geometry/Geometry.h"

// -----------------------------------------------------------------------------
namespace soca {
  // -----------------------------------------------------------------------------
  Geometry::Geometry(const eckit::Configuration & conf,
                     const eckit::mpi::Comm & comm)
    : comm_(comm),
      atmconf_(conf),
      initatm_(initAtm(conf)),
      fmsinput_(comm, conf) {
    const eckit::Configuration * configc = &conf;
    fmsinput_.updateNameList();
    soca_geo_setup_f90(keyGeom_, &configc, &comm);
  }
  // -----------------------------------------------------------------------------
  Geometry::Geometry(const Geometry & other)
    : comm_(other.comm_),
      atmconf_(other.atmconf_),
      initatm_(initAtm(other.atmconf_)),
      fmsinput_(other.fmsinput_) {
    const int key_geo = other.keyGeom_;
    soca_geo_clone_f90(key_geo, keyGeom_);
  }
  // -----------------------------------------------------------------------------
  Geometry::~Geometry() {
    soca_geo_delete_f90(keyGeom_);
  }
  // -----------------------------------------------------------------------------
  void Geometry::gridgen() const {
    soca_geo_gridgen_f90(keyGeom_);
  }
  // -----------------------------------------------------------------------------
  GeometryIterator Geometry::begin() const {
    // return start of the geometry on this mpi tile
    int ist, iend, jst, jend;
    soca_geo_start_end_f90(keyGeom_, ist, iend, jst, jend);
    return GeometryIterator(*this, ist, jst);
  }
  // -----------------------------------------------------------------------------
  GeometryIterator Geometry::end() const {
    // return end of the geometry on this mpi tile
    // decided to return index out of bounds for the iterator loops to work
    return GeometryIterator(*this, -1, -1);
  }
  // -----------------------------------------------------------------------------
  void Geometry::print(std::ostream & os) const {
    // TODO(Travis): Implement this correctly.
  }
  // -----------------------------------------------------------------------------
}  // namespace soca
