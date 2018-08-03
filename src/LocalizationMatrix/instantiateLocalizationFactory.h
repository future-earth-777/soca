/*
 * (C) Copyright 2009-2016 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#ifndef SOCA_MODEL_INSTANTIATESOCALOCALIZATIONFACTORY_H_
#define SOCA_MODEL_INSTANTIATESOCALOCALIZATIONFACTORY_H_

#include "oops/interface/LocalizationBase.h"
#include "src/LocalizationMatrix/LocalizationMatrix.h"
#include "src/Traits.h"

namespace soca {

void instantiateLocalizationFactory() {
  // static oops::LocalizationMaker;//<Traits, LocalizationMatrix> makerSeaIceFraction_("SeaIceFraction");
}

}  // namespace soca

#endif  // SOCA_MODEL_INSTANTIATESOCALOCALIZATIONFACTORY_H_