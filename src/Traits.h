/*
 * (C) Copyright 2017 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef SOCA_MODEL_SOCATRAITS_H_
#define SOCA_MODEL_SOCATRAITS_H_

#include <string>

#include "src/ModelBias.h"
#include "src/ModelBiasIncrement.h"
#include "src/ModelBiasCovariance.h"
#include "src/Geometry/Geometry.h"
#include "src/Increment/Increment.h"
#include "src/LocalizationMatrix/LocalizationMatrix.h"
#include "src/Model/Model.h"
#include "src/State/State.h"
#include "src/Covariance/ErrorCovariance.h"
#include "src/GetValuesTraj/GetValuesTraj.h"

#include "ufo/GeoVaLs.h"
#include "ioda/Locations.h"
#include "ioda/ObsSpace.h"
#include "ioda/ObsVector.h"
#include "ufo/ObsBias.h"
#include "ufo/ObsBiasIncrement.h"
#include "ufo/ObsCheck.h"
#include "ufo/ObsBiasCovariance.h"
#include "ufo/ObsOperator.h"
#include "ufo/LinearObsOperator.h"

namespace soca {

struct Traits {
  static std::string name() {return "SOCA";}
  static std::string nameCovar() {return "SocaError";}
  
  typedef soca::Geometry            Geometry;
  typedef soca::State               State;
  typedef soca::Model               Model;
  typedef soca::Increment           Increment;
  typedef soca::ErrorCovariance     Covariance;
  typedef soca::GetValuesTraj       InterpolatorTraj;
  
  typedef soca::ModelBias           ModelAuxControl;
  typedef soca::ModelBiasIncrement  ModelAuxIncrement;
  typedef soca::ModelBiasCovariance ModelAuxCovariance;
  typedef soca::LocalizationMatrix  LocalizationMatrix;  

  //typedef soca::ObsBiasCovariance     ObsAuxCovariance;
  
  typedef ufo::ObsBias              ObsAuxControl;
  typedef ufo::ObsBiasIncrement     ObsAuxIncrement;
  typedef ufo::ObsBiasCovariance    ObsAuxCovariance;
  typedef ufo::ObsCheck             ObsCheck;
  typedef ufo::ObsOperator          ObsOperator;
  typedef ufo::LinearObsOperator    LinearObsOperator;
  typedef ufo::GeoVaLs              GeoVaLs;
  typedef ioda::Locations           Locations;
  typedef ioda::ObsSpace             ObsSpace;
  typedef ioda::ObsVector            ObsVector;
};

}  // namespace soca

#endif  // SOCA_MODEL_SOCATRAITS_H_