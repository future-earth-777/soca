! (C) Copyright 2017-2020 UCAR
!
! This software is licensed under the terms of the Apache Licence Version 2.0
! which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.

!> Handle fields for the model

module soca_grid2grid_mod

  use kinds, only: kind_real
  use horiz_interp_mod, only: horiz_interp_type, horiz_interp_new

  implicit none

  !private
  public
  !public :: soca_grid2grid_type

  type :: soca_grid2grid_type
     type(horiz_interp_type) :: Interp
   contains
     procedure :: init => soca_grid2grid_init
     !procedure :: fwd => soca_grid2grid_fwd
     !procedure :: end => soca_grid2grid_end

  end type soca_grid2grid_type

  ! ------------------------------------------------------------------------------
contains
  ! ------------------------------------------------------------------------------

  ! ------------------------------------------------------------------------------
  !> Setup grid2grid object
  subroutine soca_grid2grid_init(self, loni, lati, lono, lato)
    class(soca_grid2grid_type), intent(out) :: self
    real(kind_real),             intent(in) :: loni(:,:)
    real(kind_real),             intent(in) :: lati(:,:)
    real(kind_real),             intent(in) :: lono(:,:)
    real(kind_real),             intent(in) :: lato(:,:)

    call horiz_interp_new(self%Interp, loni, lati, lono, lato)

  end subroutine soca_grid2grid_init

end module soca_grid2grid_mod
