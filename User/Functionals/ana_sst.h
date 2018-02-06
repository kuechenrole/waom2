      SUBROUTINE ana_sst (ng, tile, model)
!
!! svn $Id$
!!======================================================================
<<<<<<< HEAD
!! Copyright (c) 2002-2016 The ROMS/TOMS Group                         !
=======
!! Copyright (c) 2002-2013 The ROMS/TOMS Group                         !
>>>>>>> master
!!   Licensed under a MIT/X style license                              !
!!   See License_ROMS.txt                                              !
!=======================================================================
!                                                                      !
<<<<<<< HEAD
!  This subroutine sets sea surface temperature SST (Celsius) using    !
!  analytical expressions. This field is used when surface heat flux   !
!  correction is activated:                                            !
=======
!  This subroutine sets sea surface temperature SST  (Celsius)  and    !
!  surface net heat flux sensitivity dQdSTT to SST using analytical    !
!  expressions.  The forcing dQdSTT is usually computed in units of    !
!  (Watts/m2/degC).  It needs to be scaled to (m/s) by dividing by     !
!  rho0*Cp.  These forcing fields are used  when flux correction is    !
!  activated:                                                          !
>>>>>>> master
!                                                                      !
!       Q_model ~ Q + dQdSST * (T_model - SST)                         !
!                                                                      !
!=======================================================================
!
      USE mod_param
      USE mod_forces
      USE mod_ncparam
!
! Imported variable declarations.
!
      integer, intent(in) :: ng, tile, model

#include "tile.h"
!
      CALL ana_sst_tile (ng, tile, model,                               &
     &                   LBi, UBi, LBj, UBj,                            &
     &                   IminS, ImaxS, JminS, JmaxS,                    &
<<<<<<< HEAD
     &                   FORCES(ng) % sst)
=======
     &                   FORCES(ng) % sst,                              &
     &                   FORCES(ng) % dqdt)
>>>>>>> master
!
! Set analytical header file name used.
!
#ifdef DISTRIBUTE
      IF (Lanafile) THEN
#else
      IF (Lanafile.and.(tile.eq.0)) THEN
#endif
        ANANAME(30)=__FILE__
      END IF

      RETURN
      END SUBROUTINE ana_sst
!
!***********************************************************************
      SUBROUTINE ana_sst_tile (ng, tile, model,                         &
     &                         LBi, UBi, LBj, UBj,                      &
     &                         IminS, ImaxS, JminS, JmaxS,              &
<<<<<<< HEAD
     &                         sst)
=======
     &                         sst, dqdt)
>>>>>>> master
!***********************************************************************
!
      USE mod_param
      USE mod_scalars
!
      USE exchange_2d_mod, ONLY : exchange_r2d_tile
#ifdef DISTRIBUTE
      USE mp_exchange_mod, ONLY : mp_exchange2d
#endif
!
!  Imported variable declarations.
!
      integer, intent(in) :: ng, tile, model
      integer, intent(in) :: LBi, UBi, LBj, UBj
      integer, intent(in) :: IminS, ImaxS, JminS, JmaxS
!
#ifdef ASSUMED_SHAPE
      real(r8), intent(out) :: sst(LBi:,LBj:)
<<<<<<< HEAD
#else
      real(r8), intent(out) :: sst(LBi:UBi,LBj:UBj)
=======
      real(r8), intent(out) :: dqdt(LBi:,LBj:)
#else
      real(r8), intent(out) :: sst(LBi:UBi,LBj:UBj)
      real(r8), intent(out) :: dqdt(LBi:UBi,LBj:UBj)
>>>>>>> master
#endif
!
!  Local variable declarations.
!
      integer :: i, j

#include "set_bounds.h"
!
!-----------------------------------------------------------------------
<<<<<<< HEAD
!  Set sea surface temperature SST (Celsius).
=======
!  Set sea surface temperature (Celsius) and heat flux sensitivity to
!  SST (Watts/m2).
>>>>>>> master
!-----------------------------------------------------------------------
!
#if defined MY_APPLICATION
      DO j=JstrT,JendT
        DO i=IstrT,IendT
          sst(i,j)=???
<<<<<<< HEAD
        END DO
      END DO
#else
      ana_sst.h: no values provided for sst.
=======
          dqdt(i,j)=???
        END DO
      END DO
#else
      ana_sst.h: no values provided for sst and dqdt.
>>>>>>> master
#endif
!
!  Exchange boundary data.
!
      IF (EWperiodic(ng).or.NSperiodic(ng)) THEN
        CALL exchange_r2d_tile (ng, tile,                               &
     &                          LBi, UBi, LBj, UBj,                     &
     &                          sst)
<<<<<<< HEAD
      END IF

#ifdef DISTRIBUTE
      CALL mp_exchange2d (ng, tile, model, 1,                           &
     &                    LBi, UBi, LBj, UBj,                           &
     &                    NghostPoints,                                 &
     &                    EWperiodic(ng), NSperiodic(ng),               &
     &                    sst)
=======
        CALL exchange_r2d_tile (ng, tile,                               &
     &                          LBi, UBi, LBj, UBj,                     &
     &                          dqdt)
      END IF

#ifdef DISTRIBUTE
      CALL mp_exchange2d (ng, tile, model, 2,                           &
     &                    LBi, UBi, LBj, UBj,                           &
     &                    NghostPoints,                                 &
     &                    EWperiodic(ng), NSperiodic(ng),               &
     &                    sst, dqdt)
>>>>>>> master
#endif

      RETURN
      END SUBROUTINE ana_sst_tile
