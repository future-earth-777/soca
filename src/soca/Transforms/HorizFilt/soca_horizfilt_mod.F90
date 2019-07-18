! (C) Copyright 2017- UCAR.
!
! This software is licensed under the terms of the Apache Licence Version 2.0
! which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.

!> Structure holding configuration variables for the 3d error
!! horizfilt matrices of the SOCA analysis.

module soca_horizfilt_mod
  use config_mod
  use iso_c_binding
  use kinds
  use oobump_mod, only: bump_read_conf
  use soca_fields
  use soca_geom_mod_c
  use soca_geom_mod, only : soca_geom
  use soca_utils
  use type_bump
  use type_nam
  use random_mod
  use variables_mod

  implicit none

  private
  public :: soca_horizfilt_setup, soca_horizfilt_delete, soca_horizfilt_mult
  
  !> Fortran derived type to hold configuration data for horizfilt
  type, public :: soca_horizfilt_type
     type(soca_field),         pointer :: bkg            !< Background field (or first guess)
     type(oops_vars)                   :: vars           !< Apply filtering to vars
     real(kind=kind_real), allocatable :: wgh(:,:)       !< Filtering weight     
     integer :: isc, iec, jsc, jec  !< indices of compute domain
     integer :: isd, ied, jsd, jed  !< indices of data domain     
   contains
     procedure :: setup => soca_horizfilt_setup
     procedure :: delete => soca_horizfilt_delete
     procedure :: mult => soca_horizfilt_mult
  end type soca_horizfilt_type

  ! ------------------------------------------------------------------------------
contains
  ! ------------------------------------------------------------------------------

  !> Setup for the horizfilt operator

  subroutine soca_horizfilt_setup(self, c_conf, geom, bkg, vars)
    class(soca_horizfilt_type), intent(inout) :: self   !< The horizfilt structure
    type(c_ptr),                   intent(in) :: c_conf !< The configuration
    type(soca_geom),               intent(in) :: geom   !< Geometry
    type(soca_field),      target, intent(in) :: bkg    !< Background
    type(oops_vars),               intent(in) :: vars   !< List of variables
    
    character(len=3)  :: domain
    integer :: isc, iec, jsc, jec, i, j, ivar
    logical :: init_seaice, init_ocean
    
    ! Setup list of variables to apply filtering on
    self%vars = vars
    
    ! Associate background
    self%bkg => bkg

    ! Indices for compute/data domain
    self%isd = geom%isd ;  self%ied = geom%ied ; self%jsd = geom%jsd; self%jed = geom%jed
    self%isc = geom%isc ;  self%iec = geom%iec ; self%jsc = geom%jsc; self%jec = geom%jec

    ! Allocate and compute filtering weights
    allocate(self%wgh(self%isd:self%ied,self%jsd:self%jed))
    self%wgh = 1.0_kind_real
    
  end subroutine soca_horizfilt_setup

  ! ------------------------------------------------------------------------------

  !> Delete horizfilt

  subroutine soca_horizfilt_delete(self)
    class(soca_horizfilt_type), intent(inout) :: self       !< The horizfilt structure

    deallocate(self%wgh)
    nullify(self%bkg)
    
  end subroutine soca_horizfilt_delete

  ! ------------------------------------------------------------------------------

  subroutine soca_horizfilt_mult(self, dx)
    class(soca_horizfilt_type), intent(inout) :: self !< The horizfilt structure
    type(soca_field),           intent(inout) :: dx   !< Input: Increment
                                                      !< Output: C dx

    real(kind=kind_real), allocatable :: dx2d(:,:)

    allocate(dx2d(self%isd:self%ied,self%jsd:self%jed))
    call soca_filt2d(self, dx2d)
    
  end subroutine soca_horizfilt_mult

  ! ------------------------------------------------------------------------------

  subroutine soca_filt2d(self, dx)
    class(soca_horizfilt_type),           intent(in) :: self     
    real(kind=kind_real), allocatable, intent(inout) :: dx(:,:)

    integer :: i, j
    real(kind=kind_real) :: sum_wgh

    ! 9-point weighted average
    do i = self%isc, self%iec
       do j = self%jsc, self%jec
          dx(i,j) = &
          &self%wgh(i-1,j+1)*dx(i-1,j+1) + self%wgh(i,j+1)*dx(i,j+1) + self%wgh(i+1,j+1)*dx(i+1,j+1) + &
          &self%wgh(i-1,j)*dx(i-1,j)     + self%wgh(i,j)*dx(i,j)     + self%wgh(i+1,j)*dx(i+1,j)     + &
          &self%wgh(i-1,j-1)*dx(i-1,j-1) + self%wgh(i,j-1)*dx(i,j-1) + self%wgh(i+1,j-1)*dx(i+1,j-1)

          sum_wgh = &
          &self%wgh(i-1,j+1) + self%wgh(i,j+1) + self%wgh(i+1,j+1) + &
          &self%wgh(i-1,j)   + self%wgh(i,j)   + self%wgh(i+1,j)   + &
          &self%wgh(i-1,j-1) + self%wgh(i,j-1) + self%wgh(i+1,j-1)

          dx(i,j) = dx(i,j)/sum_wgh
       end do
    end do
    
    ! Fill halo
    
  end subroutine soca_filt2d

  
end module soca_horizfilt_mod
