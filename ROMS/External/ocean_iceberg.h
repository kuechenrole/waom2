!
!  ROMS/TOMS Standard Input parameters.
!
!svn $Id$
!========================================================= Hernan G. Arango ===
!  Copyright (c) 2002-2013 The ROMS/TOMS Group                                !
!    Licensed under a MIT/X style license                                     !
!    See License_ROMS.txt                                                     !
!==============================================================================
!                                                                             !
! Input parameters can be entered in ANY order, provided that the parameter   !
! KEYWORD (usually, upper case) is typed correctly followed by "="  or "=="   !
! symbols. Any comment lines are allowed and must begin with an exclamation   !
! mark (!) in column one.  Comments may  appear to the right of a parameter   !
! specification to improve documentation.  Comments will be ignored  during   !
! reading.  Blank lines are also allowed and ignored. Continuation lines in   !
! a parameter specification are allowed and must be preceded by a backslash   !
! (\).  In some instances, more than one value is required for a parameter.   !
! If fewer values are provided, the  last value  is assigned for the entire   !
! parameter array.  The multiplication symbol (*),  without blank spaces in   !
! between, is allowed for a parameter specification.  For example, in a two   !
! grids nested application:                                                   !
!                                                                             !
!    AKT_BAK == 2*1.0d-6  2*5.0d-6              ! m2/s                        !
!                                                                             !
! indicates that the first two entries of array AKT_BAK,  in fortran column-  !
! major order, will have the same value of "1.0d-6" for grid 1,  whereas the  !
! next two entries will have the same value of "5.0d-6" for grid 2.           !
!                                                                             !
! In multiple levels of nesting and/or multiple connected domains  step-ups,  !
! "Ngrids" entries are expected for some of these parameters.  In such case,  !
! the order of the entries for a parameter is extremely important.  It  must  !
! follow the same order (1:Ngrids) as in the state variable declaration. The  !
! USER may follow the above guidelines for specifying his/her values.  These  !
! parameters are marked by "==" plural symbol after the KEYWORD.              !
!                                                                             !
! Multiple NetCDF files are allowed for input field(s).  This is useful when  !
! splitting input data (climatology,  boundary,  forcing)  time records into  !
! several files (say monthly, annual, etc). In this case, each multiple file  !
! entry line needs to be ended by the vertical bar (|) symbol. For example:   !
!                                                                             !
!    NFFILES == 8                          ! number of forcing files          !
!                                                                             !
!    FRCNAME == my_rivers.nc      \                                           !
!               my_tides.nc       \                                           !
!               my_lwrad_year1.nc |                                           !
!               my_lwrad_year2.nc \                                           !
!               my_swrad_year1.nc |                                           !
!               my_swrad_year2.nc \                                           !
!               my_winds_year1.nc |                                           !
!               my_winds_year2.nc \                                           !
!               my_Pair_year1.nc  |                                           !
!               my_Pair_year2.nc  \                                           !
!               my_Qair_year1.nc  |                                           !
!               my_Qair_year2.nc  \                                           !
!               my_Tair_year1.nc  |                                           !
!               my_Tair_year2.nc                                              !
!                                                                             !
! Notice that NFFILES is 8 and not 14. There are 8 uniquely different fields  !
! in the file list,  we  DO NOT  count file entries followed by the vertical  !
! bar symbol.  This is because  multiple file  entries are processed in ROMS  !
! with derived type structures.                                               !
!                                                                             !
!==============================================================================
!
! Application title.

       TITLE = Tall Isolated Seamount Test

! C-preprocessing Flag.

    MyAppCPP = SEAMOUNT

! Input variable information file name.  This file needs to be processed
! first so all information arrays can be initialized properly.

     VARNAME = ROMS/External/varinfo.dat

! Number of nested grids.

      Ngrids =  1

! Number of grid nesting layers.  This parameter is used to allow refinement
! and composite grid combinations.

  NestLayers =  1

! Number of grids in each nesting layer [1:NestLayers].

GridsInLayer =  1

! Grid dimension parameters. See notes below in the Glossary for how to set
! these parameters correctly.

          Lm == 49            ! Number of I-direction INTERIOR RHO-points
          Mm == 48            ! Number of J-direction INTERIOR RHO-points
           N == 13            ! Number of vertical levels

        Nbed =  0             ! Number of sediment bed layers

         NAT =  1             ! Number of active tracers (usually, 2)
         NPT =  0             ! Number of inactive passive tracers
         NCS =  0             ! Number of cohesive (mud) sediment tracers
         NNS =  0             ! Number of non-cohesive (sand) sediment tracers

! Domain decomposition parameters for serial, distributed-memory or
! shared-memory configurations used to determine tile horizontal range
! indices (Istr,Iend) and (Jstr,Jend), [1:Ngrids].

      NtileI == 2                               ! I-direction partition
      NtileJ == 2                               ! J-direction partition

! Set lateral boundary conditions keyword. Notice that a value is expected
! for each boundary segment per nested grid for each state variable.
!
! Each tracer variable requires [1:4,1:NAT+NPT,Ngrids] values. Otherwise,
! [1:4,1:Ngrids] values are expected for other variables. The boundary
! order is: 1=west, 2=south, 3=east, and 4=north. That is, anticlockwise
! starting at the western boundary.
!
! The keyword is case insensitive and usually has three characters. However,
! it is possible to have compound keywords, if applicable. For example, the
! keyword "RadNud" implies radiation boundary condition with nudging. This
! combination is usually used in active/passive radiation conditions.
!
!   Keyword    Lateral Boundary Condition Type
!
!   Cha        Chapman_implicit (free-surface)
!   Che        Chapman_explicit (free-surface)
!   Cla        Clamped
!   Clo        Closed
!   Fla        Flather (2D momentum)                  _____N_____     j=Mm
!   Gra        Gradient                              |     4     |
!   Nes        Nested (refinement)                   |           |
!   Nud        Nudging                             1 W           E 3
!   Per        Periodic                              |           |
!   Rad        Radiation                             |_____S_____|
!   Red        Reduced Physics (2D momentum)               2          j=1
!   Shc        Shchepetkin (2D momentum)            i=1         i=Lm
!
!                   W       S       E       N
!                   e       o       a       o
!                   s       u       s       r
!                   t       t       t       t
!                           h               h
!
!                   1       2       3       4

!   LBC(isFsur) ==   Per     Clo     Per     Clo         ! free-surface
!   LBC(isUbar) ==   Per     Clo     Per     Clo         ! 2D U-momentum
!   LBC(isVbar) ==   Per     Clo     Per     Clo         ! 2D V-momentum
!   LBC(isUvel) ==   Per     Clo     Per     Clo         ! 3D U-momentum
!   LBC(isVvel) ==   Per     Clo     Per     Clo         ! 3D V-momentum
!   LBC(isMtke) ==   Per     Clo     Per     Clo         ! mixing TKE

!   LBC(isTvar) ==   Per     Clo     Per     Clo         ! temperature

   LBC(isFsur) ==   Clo     Clo     Clo     Clo         ! free-surface
   LBC(isUbar) ==   Clo     Clo     Clo     Clo         ! 2D U-momentum
   LBC(isVbar) ==   Clo     Clo     Clo     Clo         ! 2D V-momentum
   LBC(isUvel) ==   Clo     Clo     Clo     Clo         ! 3D U-momentum
   LBC(isVvel) ==   Clo     Clo     Clo     Clo         ! 3D V-momentum
   LBC(isMtke) ==   Clo     Clo     Clo     Clo         ! mixing TKE

   LBC(isTvar) ==   Clo     Clo     Clo     Clo        ! temperature
!                    Clo     Clo     Clo     Clo         ! salinity



! Adjoint-based algorithms can have different lateral boundary
! conditions keywords.

ad_LBC(isFsur) ==   Per     Clo     Per     Clo         ! free-surface
ad_LBC(isUbar) ==   Per     Clo     Per     Clo         ! 2D U-momentum
ad_LBC(isVbar) ==   Per     Clo     Per     Clo         ! 2D U-momentum
ad_LBC(isUvel) ==   Per     Clo     Per     Clo         ! 3D U-momentum
ad_LBC(isVvel) ==   Per     Clo     Per     Clo         ! 3D V-momentum
ad_LBC(isMtke) ==   Per     Clo     Per     Clo         ! mixing TKE

ad_LBC(isTvar) ==   Per     Clo     Per     Clo         ! temperature

! Set lateral open boundary edge volume conservation switch for
! nonlinear model and adjoint-based algorithms. Usually activated
! with radiation boundary conditions to enforce global mass
! conservation, except if tidal forcing enabled. [1:Ngrids].

   VolCons(west)  ==  F                            ! western  boundary
   VolCons(east)  ==  F                            ! eastern  boundary
   VolCons(south) ==  F                            ! southern boundary
   VolCons(north) ==  F                            ! northern boundary

ad_VolCons(west)  ==  F                            ! western  boundary
ad_VolCons(east)  ==  F                            ! eastern  boundary
ad_VolCons(south) ==  F                            ! southern boundary
ad_VolCons(north) ==  F                            ! northern boundary

! Time-Stepping parameters.

      NTIMES == 259200
          DT == 60.0d0
     NDTFAST == 20

! Model iteration loops parameters.

       ERstr =  1
       ERend =  1
      Nouter =  1
      Ninner =  1
  Nintervals =  1

! Number of eigenvalues (NEV) and eigenvectors (NCV) to compute for the
! Lanczos/Arnoldi problem in the Generalized Stability Theory (GST)
! analysis. NCV must be greater than NEV (see documentation below).

         NEV =  2                               ! Number of eigenvalues
         NCV =  10                              ! Number of eigenvectors

! Input/Output parameters.

       NRREC == 0
   LcycleRST == T
        NRST == 14400
        NSTA == 1
        NFLT == 1
       NINFO == 1

! Output history, average, diagnostic files parameters.

     LDEFOUT == T
        NHIS == 1440
     NDEFHIS == 0
      NTSAVG == 1
        NAVG == 14400
     NDEFAVG == 0
      NTSDIA == 1
        NDIA == 1440
     NDEFDIA == 0

! Output tangent linear and adjoint models parameters.

   LcycleTLM == F
        NTLM == 1440
     NDEFTLM == 0
   LcycleADJ == F
        NADJ == 1440
     NDEFADJ == 0
        NSFF == 1440
        NOBC == 1440

! GST output and check pointing restart parameters.

   LmultiGST =  F                               ! one eigenvector per file
     LrstGST =  F                               ! GST restart switch
  MaxIterGST =  500                             ! maximum number of iterations
        NGST =  10                              ! check pointing interval

! Relative accuracy of the Ritz values computed in the GST analysis.

    Ritz_tol =  1.0d-15

! Harmonic/biharmonic horizontal diffusion of tracer for nonlinear model
! and adjoint-based algorithms: [1:NAT+NPT,Ngrids].

        TNU2 == 0.0d0  0.0d0                    ! m2/s
        TNU4 == 2*0.0d0                         ! m4/s

     ad_TNU2 == 0.0d0  0.0d0                    ! m2/s
     ad_TNU4 == 0.0d0  0.0d0                    ! m4/s

! Harmonic/biharmonic, horizontal viscosity coefficient for nonlinear model
! and adjoint-based algorithms: [Ngrids].

       VISC2 == 0.0d0                           ! m2/s
       VISC4 == 0.0d0                           ! m4/s

    ad_VISC2 == 0.0d0                           ! m2/s
    ad_VISC4 == 0.0d0                           ! m4/s

! Vertical mixing coefficients for tracers in nonlinear model and
! basic state scale factor in adjoint-based algorithms: [1:NAT+NPT,Ngrids]

     AKT_BAK == 1.0d-6 1.0d-6                   ! m2/s

  ad_AKT_fac == 1.0d0  1.0d0                    ! nondimensional

! Vertical mixing coefficient for momentum for nonlinear model and
! basic state scale factor in adjoint-based algorithms: [Ngrids].

     AKV_BAK == 1.0d-5                          ! m2/s

  ad_AKV_fac == 1.0d0                           ! nondimensional

! Turbulent closure parameters.

     AKK_BAK == 5.0d-6                          ! m2/s
     AKP_BAK == 5.0d-6                          ! m2/s
      TKENU2 == 0.0d0                           ! m2/s
      TKENU4 == 0.0d0                           ! m4/s

! Generic length-scale turbulence closure parameters.

       GLS_P == 3.0d0                           ! K-epsilon
       GLS_M == 1.5d0
       GLS_N == -1.0d0
    GLS_Kmin == 7.6d-6
    GLS_Pmin == 1.0d-12

    GLS_CMU0 == 0.5477d0
      GLS_C1 == 1.44d0
      GLS_C2 == 1.92d0
     GLS_C3M == -0.4d0
     GLS_C3P == 1.0d0
    GLS_SIGK == 1.0d0
    GLS_SIGP == 1.30d0

! Constants used in surface turbulent kinetic energy flux computation.

  CHARNOK_ALPHA == 1400.0d0         ! Charnok surface roughness
 ZOS_HSIG_ALPHA == 0.5d0            ! roughness from wave amplitude
       SZ_ALPHA == 0.25d0           ! roughness from wave dissipation
      CRGBAN_CW == 100.0d0          ! Craig and Banner wave breaking

! Constants used in momentum stress computation.

        RDRG == 3.0d-04                    ! m/s
       RDRG2 == 3.0d-03                    ! nondimensional
         Zob == 0.02d0                     ! m
         Zos == 0.02d0                     ! m

! Height (m) of atmospheric measurements for Bulk fluxes parameterization.

      BLK_ZQ == 10.0d0                     ! air humidity
      BLK_ZT == 10.0d0                     ! air temperature
      BLK_ZW == 10.0d0                     ! winds

! Minimum depth for wetting and drying.

       DCRIT == 0.10d0                     ! m

! Various parameters.

       WTYPE == 1
     LEVSFRC == 15
     LEVBFRC == 1

! Set vertical, terrain-following coordinates transformation equation and
! stretching function (see below for details), [1:Ngrids].

  Vtransform == 2                          ! transformation equation
 Vstretching == 4                          ! stretching function

! Vertical S-coordinates parameters (see below for details), [1:Ngrids].

     THETA_S == 6.5d0                      ! surface stretching parameter
     THETA_B == 2.0d0                      ! bottom  stretching parameter
      TCLINE == 100.0d0                    ! critical depth (m)

! Mean Density and Brunt-Vaisala frequency.

        RHO0 =  1025.0d0                   ! kg/m3
     BVF_BAK =  1.0d-5                     ! 1/s2

! Time-stamp assigned for model initialization, reference time
! origin for tidal forcing, and model reference time for output
! NetCDF units attribute.

      DSTART =  0.0d0                      ! days
  TIDE_START =  0.0d0                      ! days
    TIME_REF =  0.0d0                      ! yyyymmdd.dd

! Nudging/relaxation time scales, inverse scales will be computed
! internally, [1:Ngrids].

       TNUDG == 2*0.0d0                    ! days
       ZNUDG == 0.0d0                      ! days
      M2NUDG == 0.0d0                      ! days
      M3NUDG == 0.0d0                      ! days

! Factor between passive (outflow) and active (inflow) open boundary
! conditions, [1:Ngrids]. If OBCFAC > 1, nudging on inflow is stronger
! than on outflow (recommended).

      OBCFAC == 0.0d0                      ! nondimensional

! Linear equation of State parameters:

          R0 ==  1027.0d0                  ! kg/m3
          T0 == 10.0d0                     ! Celsius
          S0 == 32.0d0                     ! nondimensional
       TCOEF == 1.7d-4                     ! 1/Celsius
       SCOEF == 7.6d-4                     ! nondimensional

! Slipperiness parameter: 1.0 (free slip) or -1.0 (no slip)

      GAMMA2 == -1.0d0

! Logical switches (TRUE/FALSE) to specify which variables to process for
! tracers climatology: [1:NAT+NPT,Ngrids]. See glossary below for details.

  LtracerCLM == T T                        ! temperature, salinity, inert

! Logical switches (TRUE/FALSE) to specify which variables to consider on
! tracers point Sources/Sinks (like river runoff): [1:NAT+NPT,Ngrids].
! See glossary below for details.

  LtracerSrc == T T                        ! temperature, salinity, inert

! Starting (DstrS) and ending (DendS) day for adjoint sensitivity forcing.
! DstrS must be less or equal to DendS. If both values are zero, their
! values are reset internally to the full range of the adjoint integration.

       DstrS == 0.0d0                      ! starting day
       DendS == 0.0d0                      ! ending day

! Starting and ending vertical levels of the 3D adjoint state variables
! whose sensitivity is required.

       KstrS == 1                          ! starting level
       KendS == 1                          ! ending level

! Logical switches (TRUE/FALSE) to specify the adjoint state variables
! whose sensitivity is required.

Lstate(isFsur) == F                        ! free-surface
Lstate(isUbar) == F                        ! 2D U-momentum
Lstate(isVbar) == F                        ! 2D V-momentum
Lstate(isUvel) == F                        ! 3D U-momentum
Lstate(isVvel) == F                        ! 3D V-momentum

Lstate(isTvar) == F F                      ! NT tracers

! Logical switches (TRUE/FALSE) to specify the state variables for
! which Forcing Singular Vectors or Stochastic Optimals is required.

Fstate(isFsur) == F                        ! free-surface
Fstate(isUbar) == F                        ! 2D U-momentum
Fstate(isVbar) == F                        ! 2D V-momentum
Fstate(isUvel) == F                        ! 3D U-momentum
Fstate(isVvel) == F                        ! 3D V-momentum
Fstate(isTvar) == F F                      ! NT tracers

Fstate(isUstr) == T                        ! surface U-stress
Fstate(isVstr) == T                        ! surface V-stress
Fstate(isTsur) == F F                      ! NT surface tracers flux

! Stochastic Optimals time decorrelation scale (days) assumed for
! red noise processes.

      SO_decay == 2.0d0                    ! days

! Stochastic Optimals surface forcing standard deviation for
! dimensionalization.

SO_sdev(isFsur) == 1.0d0                   ! free-surface
SO_sdev(isUbar) == 1.0d0                   ! 2D U-momentum
SO_sdev(isVbar) == 1.0d0                   ! 2D V-momentum
SO_sdev(isUvel) == 1.0d0                   ! 3D U-momentum
SO_sdev(isVvel) == 1.0d0                   ! 3D V-momentum
SO_sdev(isTvar) == 1.0d0 1.0d0             ! NT tracers

SO_sdev(isUstr) == 1.0d0                   ! surface U-stress
SO_sdev(isVstr) == 1.0d0                   ! surface V-stress
SO_sdev(isTsur) == 1.0d0 1.0d0             ! NT surface tracers flux

! Logical switches (TRUE/FALSE) to activate writing of fields into
! HISTORY output file.

Hout(idUvel) == T       ! u                  3D U-velocity
Hout(idVvel) == T       ! v                  3D V-velocity
Hout(idu3dE) == F       ! u_eastward         3D U-eastward  at RHO-points
Hout(idv3dN) == F       ! v_northward        3D V-northward at RHO-points
Hout(idWvel) == T       ! w                  3D W-velocity
Hout(idOvel) == T       ! omega              omega vertical velocity
Hout(idUbar) == T       ! ubar               2D U-velocity
Hout(idVbar) == T       ! vbar               2D V-velocity
Hout(idu2dE) == F       ! ubar_eastward      2D U-eastward  at RHO-points
Hout(idv2dN) == F       ! vbar_northward     2D V-northward at RHO-points
Hout(idFsur) == T       ! zeta               free-surface
Hout(idBath) == T       ! bath               time-dependent bathymetry

Hout(idTvar) == T F     ! temp, salt         temperature and salinity

Hout(idUsms) == F       ! sustr              surface U-stress
Hout(idVsms) == F       ! svstr              surface V-stress
Hout(idUbms) == F       ! bustr              bottom U-stress
Hout(idVbms) == F       ! bvstr              bottom V-stress

Hout(idUbrs) == F       ! bustrc             bottom U-current stress
Hout(idVbrs) == F       ! bvstrc             bottom V-current stress
Hout(idUbws) == F       ! bustrw             bottom U-wave stress
Hout(idVbws) == F       ! bvstrw             bottom V-wave stress
Hout(idUbcs) == F       ! bustrcwmax         bottom max wave-current U-stress
Hout(idVbcs) == F       ! bvstrcwmax         bottom max wave-current V-stress

Hout(idUbot) == F       ! Ubot               bed wave orbital U-velocity
Hout(idVbot) == F       ! Vbot               bed wave orbital V-velocity
Hout(idUbur) == F       ! Ur                 bottom U-velocity above bed
Hout(idVbvr) == F       ! Vr                 bottom V-velocity above bed

Hout(idW2xx) == F       ! Sxx_bar            2D radiation stress, Sxx component
Hout(idW2xy) == F       ! Sxy_bar            2D radiation stress, Sxy component
Hout(idW2yy) == F       ! Syy_bar            2D radiation stress, Syy component
Hout(idU2rs) == F       ! Ubar_Rstress       2D radiation U-stress
Hout(idV2rs) == F       ! Vbar_Rstress       2D radiation V-stress
Hout(idU2Sd) == F       ! ubar_stokes        2D U-Stokes velocity
Hout(idV2Sd) == F       ! vbar_stokes        2D V-Stokes velocity

Hout(idW3xx) == F       ! Sxx                3D radiation stress, Sxx component
Hout(idW3xy) == F       ! Sxy                3D radiation stress, Sxy component
Hout(idW3yy) == F       ! Syy                3D radiation stress, Syy component
Hout(idW3zx) == F       ! Szx                3D radiation stress, Szx component
Hout(idW3zy) == F       ! Szy                3D radiation stress, Szy component
Hout(idU3rs) == F       ! u_Rstress          3D U-radiation stress
Hout(idV3rs) == F       ! v_Rstress          3D V-radiation stress
Hout(idU3Sd) == F       ! u_stokes           3D U-Stokes velocity
Hout(idV3Sd) == F       ! v_stokes           3D V-Stokes velocity

Hout(idWamp) == F       ! Hwave              wave height
Hout(idWlen) == F       ! Lwave              wave length
Hout(idWdir) == F       ! Dwave              wave direction
Hout(idWptp) == F       ! Pwave_top          wave surface period
Hout(idWpbt) == F       ! Pwave_bot          wave bottom period
Hout(idWorb) == F       ! Ub_swan            wave bottom orbital velocity
Hout(idWdis) == F       ! Wave_dissip        wave dissipation

Hout(idPair) == F       ! Pair               surface air pressure
Hout(idUair) == F       ! Uair               surface U-wind component
Hout(idVair) == F       ! Vair               surface V-wind component

Hout(idTsur) == F F     ! shflux, ssflux     surface net heat and salt flux
Hout(idLhea) == F       ! latent             latent heat flux
Hout(idShea) == F       ! sensible           sensible heat flux
Hout(idLrad) == F       ! lwrad              longwave radiation flux
Hout(idSrad) == F       ! swrad              shortwave radiation flux
Hout(idEmPf) == F       ! EminusP            E-P flux
Hout(idevap) == F       ! evaporation        evaporation rate
Hout(idrain) == F       ! rain               precipitation rate

Hout(idDano) == F       ! rho                density anomaly
Hout(idVvis) == F       ! AKv                vertical viscosity
Hout(idTdif) == F       ! AKt                vertical T-diffusion
Hout(idSdif) == F       ! AKs                vertical Salinity diffusion
Hout(idHsbl) == F       ! Hsbl               depth of surface boundary layer
Hout(idHbbl) == F       ! Hbbl               depth of bottom boundary layer
Hout(idMtke) == F       ! tke                turbulent kinetic energy
Hout(idMtls) == F       ! gls                turbulent length scale

! Logical switches (TRUE/FALSE) to activate writing of extra inert passive
! tracers other than biological and sediment tracers. An inert passive tracer
! is one that it is only advected and diffused. Other processes are ignored.
! These tracers include, for example, dyes, pollutants, oil spills, etc.
! NPT values are expected. However, these switches can be activated using
! compact parameter specification.

 Hout(inert) == T       ! dye_01, ...        inert passive tracers

! Logical switches (TRUE/FALSE) to activate writing of exposed sediment
! layer properties into HISTORY output file.  Currently, MBOTP properties
! are expected for the bottom boundary layer and/or sediment models:
!
! idBott( 1=isd50)   grain_diameter          mean grain diameter
! idBott( 2=idens)   grain_density           mean grain density
! idBott( 3=iwsed)   settling_vel            mean settling velocity
! idBott( 4=itauc)   erosion_stress          critical erosion stress
! idBott( 5=irlen)   ripple_length           ripple length
! idBott( 6=irhgt)   ripple_height           ripple height
! idBott( 7=ibwav)   bed_wave_amp            wave excursion amplitude
! idBott( 8=izdef)   Zo_def                  default bottom roughness
! idBott( 9=izapp)   Zo_app                  apparent bottom roughness
! idBott(10=izNik)   Zo_Nik                  Nikuradse bottom roughness
! idBott(11=izbio)   Zo_bio                  biological bottom roughness
! idBott(12=izbfm)   Zo_bedform              bed form bottom roughness
! idBott(13=izbld)   Zo_bedload              bed load bottom roughness
! idBott(14=izwbl)   Zo_wbl                  wave bottom roughness
! idBott(15=iactv)   active_layer_thickness  active layer thickness
! idBott(16=ishgt)   saltation               saltation height
!
!                                 1 1 1 1 1 1 1
!               1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6

Hout(idBott) == T T T T T T T T T F F F F F F F

! Logical switches (TRUE/FALSE) to activate writing of time-averaged
! fields into AVERAGE output file.

Aout(idUvel) == T       ! u                  3D U-velocity
Aout(idVvel) == T       ! v                  3D V-velocity
Aout(idu3dE) == F       ! u_eastward         3D U-eastward  at RHO-points
Aout(idv3dN) == F       ! v_northward        3D V-northward at RHO-points
Aout(idWvel) == T       ! w                  3D W-velocity
Aout(idOvel) == T       ! omega              omega vertical velocity
Aout(idUbar) == T       ! ubar               2D U-velocity
Aout(idVbar) == T       ! vbar               2D V-velocity
Aout(idu2dE) == F       ! ubar_eastward      2D U-eastward  at RHO-points
Aout(idv2dN) == F       ! vbar_northward     2D V-northward at RHO-points
Aout(idFsur) == T       ! zeta               free-surface

Aout(idTvar) == T T     ! temp, salt         temperature and salinity

Aout(idUsms) == F       ! sustr              surface U-stress
Aout(idVsms) == F       ! svstr              surface V-stress
Aout(idUbms) == F       ! bustr              bottom U-stress
Aout(idVbms) == F       ! bvstr              bottom V-stress

Aout(idW2xx) == F       ! Sxx_bar            2D radiation stress, Sxx component
Aout(idW2xy) == F       ! Sxy_bar            2D radiation stress, Sxy component
Aout(idW2yy) == F       ! Syy_bar            2D radiation stress, Syy component
Aout(idU2rs) == F       ! Ubar_Rstress       2D radiation U-stress
Aout(idV2rs) == F       ! Vbar_Rstress       2D radiation V-stress
Aout(idU2Sd) == F       ! ubar_stokes        2D U-Stokes velocity
Aout(idV2Sd) == F       ! vbar_stokes        2D V-Stokes velocity

Aout(idW3xx) == F       ! Sxx                3D radiation stress, Sxx component
Aout(idW3xy) == F       ! Sxy                3D radiation stress, Sxy component
Aout(idW3yy) == F       ! Syy                3D radiation stress, Syy component
Aout(idW3zx) == F       ! Szx                3D radiation stress, Szx component
Aout(idW3zy) == F       ! Szy                3D radiation stress, Szy component
Aout(idU3rs) == F       ! u_Rstress          3D U-radiation stress
Aout(idV3rs) == F       ! v_Rstress          3D V-radiation stress
Aout(idU3Sd) == F       ! u_stokes           3D U-Stokes velocity
Aout(idV3Sd) == F       ! v_stokes           3D V-Stokes velocity

Aout(idPair) == F       ! Pair               surface air pressure
Aout(idUair) == F       ! Uair               surface U-wind component
Aout(idVair) == F       ! Vair               surface V-wind component

Aout(idTsur) == F F     ! shflux, ssflux     surface net heat and salt flux
Aout(idLhea) == F       ! latent             latent heat flux
Aout(idShea) == F       ! sensible           sensible heat flux
Aout(idLrad) == F       ! lwrad              longwave radiation flux
Aout(idSrad) == F       ! swrad              shortwave radiation flux
Aout(idevap) == F       ! evaporation        evaporation rate
Aout(idrain) == F       ! rain               precipitation rate

Aout(idDano) == F       ! rho                density anomaly
Aout(idVvis) == F       ! AKv                vertical viscosity
Aout(idTdif) == F       ! AKt                vertical T-diffusion
Aout(idSdif) == F       ! AKs                vertical Salinity diffusion
Aout(idHsbl) == F       ! Hsbl               depth of surface boundary layer
Aout(idHbbl) == F       ! Hbbl               depth of bottom boundary layer

Aout(id2dRV) == F       ! pvorticity_bar     2D relative vorticity
Aout(id3dRV) == F       ! pvorticity         3D relative vorticity
Aout(id2dPV) == F       ! rvorticity_bar     2D potential vorticity
Aout(id3dPV) == F       ! rvorticity         3D potential vorticity

Aout(idu3dD) == F       ! u_detided          detided 3D U-velocity
Aout(idv3dD) == F       ! v_detided          detided 3D V-velocity
Aout(idu2dD) == F       ! ubar_detided       detided 2D U-velocity
Aout(idv2dD) == F       ! vbar_detided       detided 2D V-velocity
Aout(idFsuD) == F       ! zeta_detided       detided free-surface

Aout(idTrcD) == F F     ! temp_detided, ...  detided temperature and salinity

Aout(idHUav) == F       ! Huon               u-volume flux, Huon
Aout(idHVav) == F       ! Hvom               v-volume flux, Hvom
Aout(idUUav) == F       ! uu                 quadratic <u*u> term
Aout(idUVav) == F       ! uv                 quadratic <u*v> term
Aout(idVVav) == F       ! vv                 quadratic <v*v> term
Aout(idU2av) == F       ! ubar2              quadratic <ubar*ubar> term
Aout(idV2av) == F       ! vbar2              quadratic <vbar*vbar> term
Aout(idZZav) == F       ! zeta2              quadratic <zeta*zeta> term

Aout(idTTav) == F F     ! temp2, ...         quadratic <t*t> tracer terms
Aout(idUTav) == F F     ! utemp, ...         quadratic <u*t> tracer terms
Aout(idVTav) == F F     ! vtemp, ...         quadratic <v*t> tracer terms
Aout(iHUTav) == F F     ! Huontemp, ...      tracer volume flux, <Huon*t>
Aout(iHVTav) == F F     ! Hvomtemp, ...      tracer volume flux, <Hvom*t>

! Logical switches (TRUE/FALSE) to activate writing of extra inert passive
! tracers other than biological and sediment tracers into the AVERAGE file.

 Aout(inert) == T       ! dye_01, ...        inert passive tracers

! Logical switches (TRUE/FALSE) to activate writing of time-averaged,
! 2D momentum (ubar,vbar) diagnostic terms into DIAGNOSTIC output file.

Dout(M2rate) == T       ! ubar_accel, ...    acceleration
Dout(M2pgrd) == T       ! ubar_prsgrd, ...   pressure gradient
Dout(M2fcor) == T       ! ubar_cor, ...      Coriolis force
Dout(M2hadv) == T       ! ubar_hadv, ...     horizontal total advection
Dout(M2xadv) == T       ! ubar_xadv, ...     horizontal XI-advection
Dout(M2yadv) == T       ! ubar_yadv, ...     horizontal ETA-advection
Dout(M2hrad) == T       ! ubar_hrad, ...     horizontal total radiation stress
Dout(M2hvis) == T       ! ubar_hvisc, ...    horizontal total viscosity
Dout(M2xvis) == T       ! ubar_xvisc, ...    horizontal XI-viscosity
Dout(M2yvis) == T       ! ubar_yvisc, ...    horizontal ETA-viscosity
Dout(M2sstr) == T       ! ubar_sstr, ...     surface stress
Dout(M2bstr) == T       ! ubar_bstr, ...     bottom stress

! Logical switches (TRUE/FALSE) to activate writing of time-averaged,
! 3D momentum (u,v) diagnostic terms into DIAGNOSTIC output file.

Dout(M3rate) == T       ! u_accel, ...       acceleration
Dout(M3pgrd) == T       ! u_prsgrd, ...      pressure gradient
Dout(M3fcor) == T       ! u_cor, ...         Coriolis force
Dout(M3hadv) == T       ! u_hadv, ...        horizontal total advection
Dout(M3xadv) == T       ! u_xadv, ...        horizontal XI-advection
Dout(M3yadv) == T       ! u_yadv, ...        horizontal ETA-advection
Dout(M3vadv) == T       ! u_vadv, ...        vertical advection
Dout(M3hrad) == T       ! u_hrad, ...        horizontal total radiation stress
Dout(M3vrad) == T       ! u_vrad, ...        vertical radiation stress
Dout(M3hvis) == T       ! u_hvisc, ...       horizontal total viscosity
Dout(M3xvis) == T       ! u_xvisc, ...       horizontal XI-viscosity
Dout(M3yvis) == T       ! u_yvisc, ...       horizontal ETA-viscosity
Dout(M3vvis) == T       ! u_vvisc, ...       vertical viscosity

! Logical switches (TRUE/FALSE) to activate writing of time-averaged,
! active (temperature and salinity) and passive (inert) tracer diagnostic
! terms into DIAGNOSTIC output file: [1:NAT+NPT,Ngrids].

Dout(iTrate) == T T     ! temp_rate, ...     time rate of change
Dout(iThadv) == T T     ! temp_hadv, ...     horizontal total advection
Dout(iTxadv) == T T     ! temp_xadv, ...     horizontal XI-advection
Dout(iTyadv) == T T     ! temp_yadv, ...     horizontal ETA-advection
Dout(iTvadv) == T T     ! temp_vadv, ...     vertical advection
Dout(iThdif) == T T     ! temp_hdiff, ...    horizontal total diffusion
Dout(iTxdif) == T T     ! temp_xdiff, ...    horizontal XI-diffusion
Dout(iTydif) == T T     ! temp_ydiff, ...    horizontal ETA-diffusion
Dout(iTsdif) == T T     ! temp_sdiff, ...    horizontal S-diffusion
Dout(iTvdif) == T T     ! temp_vdiff, ...    vertical diffusion

! Generic User parameters, [1:NUSER].

       NUSER =  0
        USER =  0.d0

! NetCDF-4/HDF5 compression parameters for output files.

  NC_SHUFFLE =  1                 ! if non-zero, turn on shuffle filter
  NC_DEFLATE =  1                 ! if non-zero, turn on deflate filter
   NC_DLEVEL =  1                 ! deflate level [0-9]

! Input NetCDF file names, [1:Ngrids].

     GRDNAME == ocean_grd.nc
     ININAME == ocean_ini.nc
     ITLNAME == ocean_itl.nc
     IRPNAME == ocean_irp.nc
     IADNAME == ocean_iad.nc
     FWDNAME == ocean_fwd.nc
     ADSNAME == ocean_ads.nc

! Nesting grids connectivity data: contact points information. This
! NetCDF file is special and complex. It is currently generated using
! script "matlab/grid/contact.m" from the Matlab repository.

     NGCNAME =  ocean_ngc.nc

! Input lateral boundary conditions and climatology file names.  The
! USER has the option to split input data time records into several
! NetCDF files (see prologue instructions above). If so, use a single
! line per entry with a vertical bar (|) symbol after each entry,
! except the last one.

     BRYNAME == ocean_bry.nc
     CLMNAME == ocean_clm.nc

! Input forcing NetCDF file name(s).  The USER has the option to enter
! several file names for each nested grid.  For example, the USER may
! have different files for wind products, heat fluxes, rivers, tides,
! etc.  The model will scan the file list and will read the needed data
! from the first file in the list containing the forcing field. Therefore,
! the order of the file names is very important. If using multiple forcing
! files per grid, first enter all the file names for grid 1, then grid 2,
! and so on.  It is also possible to split input data time records into
! several NetCDF files (see prologue instructions above). Use a single line
! per entry with a continuation (\) or vertical bar (|) symbol after each
! entry, except the last one.

     NFFILES == 1                          ! number of unique forcing files

     FRCNAME == ocean_frc.nc               ! forcing file 1, grid 1

! Output NetCDF file names, [1:Ngrids].

     GSTNAME == ocean_gst.nc
     RSTNAME == ocean_rst.nc
     HISNAME == ocean_his.nc
     TLMNAME == ocean_tlm.nc
     TLFNAME == ocean_tlf.nc
     ADJNAME == ocean_adj.nc
     AVGNAME == ocean_avg.nc
     DIANAME == ocean_dia.nc
     STANAME == ocean_sta.nc
     FLTNAME == ocean_flt.nc

! Input ASCII parameter filenames.

     APARNAM =  ROMS/External/s4dvar.in
     SPOSNAM =  ROMS/External/stations.in
     FPOSNAM =  ROMS/External/floats.in
     BPARNAM =  ROMS/External/bio_Fennel.in
     SPARNAM =  ROMS/External/sediment.in
     USRNAME =  ROMS/External/MyFile.dat

!
!  GLOSSARY:
!  =========
!
!------------------------------------------------------------------------------
! Application title (string with a maximum of eighty characters) and
! C-preprocessing flag.
!------------------------------------------------------------------------------
!
!  TITLE       Application title.
!
!  MyAppCPP    Application C-preprocessing option.
!
!------------------------------------------------------------------------------
! Variable information file name (string with a maximum of 256 characters).
!------------------------------------------------------------------------------
!
!  VARNAME     Input/Output variable information file name.  This file needs to
!              be processed first so all information arrays and indices can be
!              initialized properly in "mod_ncparam.F".
!
!------------------------------------------------------------------------------
! Nested grid parameters (processing order of these parameters is important).
!------------------------------------------------------------------------------
!
!  Ngrids      Number of nested grids. It needs to be read at the top of all
!                other parameters in order to allocate all model variables.
!
!  NestLayers  Number of grid nesting layers. It is used to allow applications
!                with both composite and refinement grid combinations, as shown
!                in WikiROMS diagrams for the Refinement and Partial Boundary
!                Composite Sub-Classes. See,
!
!                https://www.myroms.org/wiki/index.php/Nested_Grids
!
!                In non-nesting applications, set NestLayers = 1.
!
! GridsInLayer Number of grids in each nested layer, a vector of size
!                [1:NestLayers]. Notice that,
!
!                SUM(GridsInLayer)    = Ngrids
!                LENGHT(GridsInLayer) = NestLayers
!
!                The order of grids and nesting layers is extremely important.
!                It determines the order of the sequential solution at every
!                sub-time step.  See WikiROMS nesting Sub-Classes diagrams.
!
!                In non-nesting applications, set GridsInLayer = 1.
!
!                NOTE:  In main3d, we use these parameters to determine which
!                ====   grid index, ng, to solve when calling the routines of
!                       the computational kernel:
!
!                  NEST_LAYER : DO nl=1,NestLayers
!                    ...
!                    STEP_LOOP : DO istep=1,Nsteps
!                      ...
!                      DO ig=1,GridsInLayer(nl)
!                        ng=GridNumber(ig,nl)
!                        ...
!                      END DO
!                      ...
!                    END DO STEP_LOOP
!                  END DO NEST_LAYER
!
!                Here, the grid order "ng" for the computations is determined
!                from array "GridNumber", which is computed at initialization
!                in "read_phypar.F". It can be computed on the flight as:
!
!                  ng=Ngrids+1
!                  DO j=NestLayers,nl,-1
!                    DO i=GridsInLayer(j),1,-1
!                      ng=ng-1
!                      IF ((j.eq.nl).and.(i.eq.ig)) EXIT
!                    END DO
!                  END DO
!
!                but it is too inefficient. This information is provided here
!                to help you configure the order of nested grids.
!
!------------------------------------------------------------------------------
! Grid dimension parameters.
!------------------------------------------------------------------------------
!
! These parameters are very important since they determine the grid of the
! application to solve. They need to be read first in order to dynamically
! allocate all model variables.
!
! WARNING: It is trivial and possible to change these dimension parameters in
! -------  idealized applications via analytical expressions.  However, in
! realistic applications any change to these parameters requires redoing all
! input NetCDF files.
!
!  Lm          Number of INTERIOR grid RHO-points in the XI-direction for
!                each nested grid, [1:Ngrids]. If using NetCDF files as
!                input, Lm=xi_rho-2 where "xi_rho" is the NetCDF file
!                dimension of RHO-points. Recall that all RHO-point
!                variables have a computational I-range of [0:Lm+1].
!
!  Mm          Number of INTERIOR grid RHO-points in the ETA-direction for
!                each nested grid, [1:Ngrids]. If using NetCDF files as
!                input, Mm=eta_rho-2 where "eta_rho" is the NetCDF file
!                dimension of RHO-points. Recall that all RHO-point
!                variables have a computational J-range of [0:Mm+1].
!
!  N           Number of vertical terrain-following levels at RHO-points,
!                [1:Ngrids].
!
!  Nbed        Number of sediment bed layers, [1:Ngrids]. This parameter
!                is only relevant if CPP option SEDIMENT is activated.
!
!                Mm+1  ___________________                _______  Kw = N
!                     |                   |              |       |
!                  Mm |   _____________   |              |       | Kr = N
!                     |  |             |  |              |_______|
!                     |  |             |  |              |       |
!                  Jr |  |             |  |              |       |
!                     |  |             |  |              |_______|
!                     |  |             |  |              |       |
!                   1 |  |_____________|  |              |       |
!                     |                   |              |_______|
!                   0 |___________________|              |       |
!                              Ir                        |       | 1
!                     0  1            Lm  Lm+1    h(i,j) |_______|
!                                                        ::::::::: 0
!                                                        :::::::::
!                                                        ::::::::: Nbed-1
!                                                        ::::::::: Nbed
!
!  NAT         Number of active tracer type variables. Usually, NAT=2 for
!                potential temperature and salinity.
!
!  NPT         Number of inert (dyes, age, etc) passive tracer type variables
!                to advect and diffuse only. This parameter is only relevant
!                if CPP option T_PASSIVE is activated.
!
!  NCS         Number of cohesive (mud) sediment tracer type variables. This
!                parameter is only relevant if CPP option SEDIMENT is
!                activated.
!
!  NNS         Number of non-cohesive (sand) sediment tracer type variables.
!                This parameter is only relevant if CPP option SEDIMENT is
!                activated.
!
!              The total number of sediment tracers is NST=NCS+NNS.  Notice
!              that NST must be greater than zero (NST>0).
!
!------------------------------------------------------------------------------
! Domain tile partition parameters.
!------------------------------------------------------------------------------
!
! Model tile decomposition parameters for serial and parallel configurations
! which are used to determine tile horizontal range indices (Istr,Iend) and
! (Jstr,Jend). In some computers, it is advantageous to have tile partitions
! in serial applications.
!
!  NtileI      Number of domain partitions in the I-direction (XI-coordinate).
!              It must be equal to or greater than one.
!
!  NtileJ      Number of domain partitions in the J-direction (ETA-coordinate).
!              It must be equal to or greater than one.
!
!  WARNING:    In shared-memory (OpenMP), the product of NtileI and NtileJ must
!              be a MULTIPLE of the number of parallel threads specified with
!              the OpenMP environmental variable OMP_NUM_THREADS.
!
!              In distributed-memory (MPI), the product of NtileI and NtileJ
!              must be EQUAL to the number of parallel nodes specified during
!              execution with the "mprun" or "mpirun" command.
!
!------------------------------------------------------------------------------
! Lateral boundary conditions parameters.
!------------------------------------------------------------------------------
!
! The lateral boundary conditions are now specified with logical switches
! instead of CPP flags to allow nested grid configurations. Their values are
! loaded into structured array:
!
!    LBC(1:4, nLBCvar, Ngrids)
!
! where 1:4 are the number of boundary edges, nLBCvar are the number LBC state
! variables, and Ngrids is the number of nested grids. For Example, to apply
! gradient boundary conditions we use:
!
!    LBC(iwest,  isFsur, ng) % gradient
!    LBC(ieast,  ...   , ng) % gradient
!    LBC(isouth, ...   , ng) % gradient
!    LBC(inorth, ...   , ng) % gradient
!
! The lateral boundary conditions are entered with a keyword. This keyword
! is case insensitive and usually has three characters. However, it is
! possible to have compound keywords, if applicable. For example, the
! keyword "RadNud" implies radiation boundary condition with nudging. This
! combination is usually used in active/passive radiation conditions.
!
!   Keyword    Lateral Boundary Condition Type
!
!   Cha        Chapman_implicit (free-surface only)
!   Che        Chapman_explicit (free-surface only)
!   Cla        Clamped
!   Clo        Closed
!   Fla        Flather (2D momentum only)             _____N_____     j=Mm
!   Gra        Gradient                              |     4     |
!   Nes        Nested (refinement only)              |           |
!   Nud        Nudging                             1 W           E 3
!   Per        Periodic                              |           |
!   Rad        Radiation                             |_____S_____|
!   Red        Reduced Physics (2D momentum only)          2          j=1
!   Shc        Shchepetkin (2D momentum only)       i=1         i=Lm
!
!  LBC(isFsur) Free-surface,  [1:4, Ngrids] values are expected.
!  LBC(isUbar) 2D U-momentum, [1:4, Ngrids] values are expected.
!  LBC(isVbar) 2D V-momentum, [1:4, Ngrids] values are expected.
!  LBC(isUvel) 3D U-momentum, [1:4, Ngrids] values are expected.
!  LBC(isVvel) 3D V-momentum, [1:4, Ngrids] values are expected.
!  LBC(isMtke) Mixing TKE,    [1:4, Ngrids] values are expected.
!  LBC(isTvar) Tracers,       [1:4, 1:NAT+NPT, Ngrids] values are expected.
!
! Similarly, the adjoint-based algorithms (ADM, TLM, RPM) can have different
! lateral boundary conditions keywords:
!
!  ad_LBC(isFsur) Free-surface,  [1:4, Ngrids] values are expected.
!  ad_LBC(isUbar) 2D U-momentum, [1:4, Ngrids] values are expected.
!  ad_LBC(isVbar) 2D V-momentum, [1:4, Ngrids] values are expected.
!  ad_LBC(isUvel) 3D U-momentum, [1:4, Ngrids] values are expected.
!  ad_LBC(isVvel) 3D V-momentum, [1:4, Ngrids] values are expected.
!  ad_LBC(isMtke) Mixing TKE,    [1:4, Ngrids] values are expected.
!  ad_LBC(isTvar) Tracers,       [1:4, 1:NAT+NPT, Ngrids] values are expected.
!
! Lateral open boundary edge volume conservation switch for nonlinear model
! and adjoint-based algorithm. Usually activated with radiation boundary
! conditions to enforce global mass conservation. Notice that these switches
! should not be activated if tidal forcing enabled, [1:Ngrids] values are
! expected.
!
!  VolCons(west)       Western  boundary volume conservation switch.
!  VolCons(east)       Eastern  boundary volume conservation switch.
!  VolCons(south)      Southern boundary volume conservation switch.
!  VolCons(north)      Northern boundary volume conservation switch.
!
!  ad_VolCons(west)    Western  boundary volume conservation switch.
!  ad_VolCons(east)    Eastern  boundary volume conservation switch.
!  ad_VolCons(south)   Southern boundary volume conservation switch.
!  ad_VolCons(north)   Northern boundary volume conservation switch.
!
!------------------------------------------------------------------------------
! Time-Stepping parameters.
!------------------------------------------------------------------------------
!
!  NTIMES      Total number time-steps in current run.  If 3D configuration,
!              NTIMES is the total of baroclinic time-steps.  If only 2D
!              configuration, NTIMES is the total of barotropic time-steps.
!
!  DT          Time-Step size in seconds.  If 3D configuration, DT is the
!              size of the baroclinic time-step.  If only 2D configuration,
!              DT is the size of the barotropic time-step.
!
!  NDTFAST     Number of barotropic time-steps between each baroclinic time
!              step. If only 2D configuration, NDTFAST should be unity since
!              there is no need to split time-stepping.
!
!------------------------------------------------------------------------------
! Model iteration loops parameters.
!------------------------------------------------------------------------------
!
!  ERstr       Starting ensemble run (perturbation or iteration) number.
!
!  ERend       Ending   ensemble run (perturbation or iteration) number.
!
!  Nouter      Maximum number of 4DVAR outer loop iterations.
!
!  Ninner      Maximum number of 4DVAR inner loop iterations.
!
!  Nintervals  Number of time interval divisions for Stochastic Optimals
!              computations. It must be a multiple of NTIMES. The tangent
!              linear model (TLM) and the adjoint model (ADM) are integrated
!              forward and backward at different intervals.  For example,
!              if Nintervals=3,
!
!              1               NTIMES/3         2*NTIMES/3           NTIMES
!              +..................+..................+..................+
!              <========================================================> (1)
!                                 <=====================================> (2)
!                                                    <==================> (3)
!
!              In the first iteration (1), the TLM is integrated forward from
!              1 to NTIMES and the ADM is integrated backward from NTIMES to 1.
!              In the second iteration (2), the TLM is integrated forward from
!              NTIMES/3 to NTIMES and the ADM is integrated backward from
!              NTIMES to NTIMES/3. And so on.
!
!------------------------------------------------------------------------------
!  Eigenproblem parameters.
!------------------------------------------------------------------------------
!
!  NEV         Number of eigenvalues to compute for the Lanczos/Arnoldi
!              problem.  Notice that the model memory requirement increases
!              substantially as NEV increases.  The GST requires NEV+1
!              copies of the model state vector.  The memory requirements
!              are decreased in distributed-memory applications.
!
!  NCV         Number of eigenvectors to compute for the Lanczos/Arnoldi
!              problem. NCV must be greater than NEV.
!
!  At present, there is no a-priori analysis to guide the selection of NCV
!  relative to NEV.  The only formal requirement is that NCV > NEV. However
!  in optimal perturbations, it is recommended to have NCV greater than or
!  equal to 2*NEV. In Finite Time Eigenmodes (FTE) and Adjoint Finite Time
!  Eigenmodes (AFTE) the requirement is to have NCV greater than or equal to
!  2*NEV+1.
!
!  The efficiency of calculations depends critically on the combination of
!  NEV and NCV.  If NEV is large (greater than 10 say), you can use NCV=2*NEV+1
!  but for NEV small (less than 6) it will be inefficient to use NCV=2*NEV+1.
!  In complicated applications, you can start with NEV=2 and NCV=10. Otherwise,
!  it will iterate for a very long time.
!
!------------------------------------------------------------------------------
! Input/Output parameters.
!------------------------------------------------------------------------------
!
!  NRREC       Switch to indicate re-start from a previous solution.  Use
!              NRREC=0 for new solutions. In a re-start solution, NRREC
!              is the time index of the re-start NetCDF file assigned for
!              initialization.  If NRREC is negative (say NRREC=-1), the
!              model will re-start from the most recent time record. That
!              is, the initialization record is assigned internally.
!              Notice that it is also possible to re-start from a history
!              or time-averaged NetCDF file.  If a history file is used
!              for re-start, it must contains all the necessary primitive
!              variables at all levels.
!
!  LcycleRST   Logical switch (T/F) used to recycle time records in output
!              re-start file.  If TRUE,  only the latest two re-start time
!              records are maintained.  If FALSE, all re-start fields are
!              saved every NRST time-steps without recycling.  The re-start
!              fields are written at all levels in double precision.
!
!  NRST        Number of time-steps between writing of re-start fields.
!
!  NSTA        Number of time-steps between writing data into stations file.
!              Station data is written at all levels.
!
!  NFLT        Number of time-steps between writing data into floats file.
!
!  NINFO       Number of time-steps between print of single line information
!              to standard output.  It also determines the interval between
!              computation of global energy diagnostics.
!
!------------------------------------------------------------------------------
!  Output history and average files parameters.
!------------------------------------------------------------------------------
!
!  LDEFOUT     Logical switch (T/F) used to create new output files when
!              initializing from a re-start file, abs(NRREC) > 0.  If TRUE
!              and applicable, a new history, average, diagnostic and
!              station files are created during the initialization stage.
!              If FALSE and applicable, data is appended to existing
!              history, average, diagnostic and station files.  See also
!              parameters NDEFHIS, NDEFAVG and NDEFDIA below.
!
!  NHIS        Number of time-steps between writing fields into history file.
!
!  NDEFHIS     Number of time-steps between the creation of new history file.
!              If NDEFHIS=0, the model will only process one history file.
!              This feature is useful for long simulations when history files
!              get too large; it creates a new file every NDEFHIS time-steps.
!
!  NTSAVG      Starting time-step for the accumulation of output time-averaged
!              data.
!
!  NAVG        Number of time-steps between writing time-averaged data
!              into averages file.  Averaged date is written for all fields.
!
!  NDEFAVG     Number of time-steps between the creation of new average
!              file.  If NDEFAVG=0, the model will only process one average
!              file.  This feature is useful for long simulations when
!              average files get too large; it creates a new file every
!              NDEFAVG time-steps.
!
!  NTSDIA      Starting time-step for the accumulation of output time-averaged
!              diagnostics data.
!
!  NDIA        Number of time-steps between writing time-averaged diagnostics
!              data into diagnostics file.  Averaged date is written for all
!              fields.
!
!  NDEFDIA     Number of time-steps between the creation of new time-averaged
!              diagnostics file.  If NDEFDIA=0, the model will only process one
!              diagnostics file.  This feature is useful for long simulations
!              when diagnostics files get too large; it creates a new file
!              every NDEFDIA time-steps.
!
!------------------------------------------------------------------------------
!  Output tangent linear and adjoint model parameters.
!------------------------------------------------------------------------------
!
!  LcycleTLM   Logical switch (T/F) used to recycle time records in output
!              tangent linear file.  If TRUE, only the latest two time
!              records are maintained.  If FALSE, all tangent linear fields
!              are saved every NTLM time-steps without recycling.
!
!  NTLM        Number of time-steps between writing fields into tangent linear
!              model file.
!
!  NDEFTLM     Number of time-steps between the creation of new tangent linear
!              file. If NDEFTLM=0, the model will only process one tangent
!              linear file. This feature is useful for long simulations when
!              output NetCDF files get too large; it creates a new file every
!              NDEFTLM time-steps.
!
!  LcycleADJ   Logical switch (T/F) used to recycle time records in output
!              adjoint file.  If TRUE, only the latest two time records are
!              maintained.  If FALSE, all tangent linear fields re saved
!              every NADJ time-steps without recycling.
!
!  NADJ        Number of time-steps between writing fields into adjoint model
!              file.
!
!  NDEFADJ     Number of time-steps between the creation of new adjoint file.
!              If NDEFADJ=0, the model will only process one adjoint file.
!              This feature is useful for long simulations when output NetCDF
!              files get too large; it creates a new file every NDEFADJ
!              time-steps.
!
!  NSFF        Number of time-steps between 4DVAR adjustment of surface forcing
!              fluxes. In strong constraint 4DVAR, it is possible to adjust
!              surface forcing at other time intervals in addition to initial
!              time.  This parameter is used to store the appropriate number
!              of surface forcing records in the output history NetCDF files:
!              1+NTIMES/NSFF records. NSFF must be a factor of NTIMES or
!              greater than NTIMES. If NSFF > NTIMES, only one record is
!              stored in the NetCDF files and the adjustment is for constant
!              forcing with constant correction. This parameter is only
!              relevant in 4DVAR when activating either ADJUST_STFLUX or
!              ADJUST_WSTRESS.
!
!  NOBC        Number of time-steps between 4DVAR adjustment of open boundary
!              fields. In strong constraint 4DVAR, it is possible to adjust
!              open boundaries at other time intervals in addition to initial
!              time.  This parameter is used to store the appropriate number
!              of open boundary records in the output history NetCDF files:
!              1+NTIMES/NOBC records. NOBC must be a factor of NTIMES or
!              greater than NTIMES. If NOBC > NTIMES, only one record is
!              stored in the NetCDF files and the adjustment is for constant
!              forcing with constant correction. This parameter is only
!              relevant in 4DVAR when activating ADJUST_BOUNDARY.
!
!------------------------------------------------------------------------------
!  Generalized Stability Theory (GST) analysis parameters.
!------------------------------------------------------------------------------
!
!  LmultiGST   Logical switch (TRUE/FALSE) to write out one GST analysis
!              eigenvector per history file.
!
!  LrstGST     Logical switch (TRUE/FALSE) to restart GST analysis. If TRUE,
!              the check pointing data is read in from the GST restart NetCDF
!              file.  If FALSE and applicable, the check pointing GST data is
!              saved and overwritten every NGST iterations of the algorithm.
!
!  MaxIterGST  Maximum number of GST algorithm iterations.
!
!  NGST        Number of GST iterations between storing of check pointing
!              data into NetCDF file. The restart data is always saved if
!              MaxIterGST is reached without convergence. It is also saved
!              when convergence is achieved. It is always a good idea to
!              save the check pointing data at regular intervals so there
!              is a mechanism to recover from an unexpected interruption
!              in this very expensive computation. The check pointing data
!              can be used also to recompute the Ritz vectors by changing
!              some of the parameters, like convergence criteria (Ritz_tol)
!              and number of Arnoldi iterations (iparam(3)).
!
!  Ritz_tol    Relative accuracy of the Ritz values computed in the GST
!              analysis.
!
!------------------------------------------------------------------------------
! Harmonic/Biharmonic horizontal diffusion for active tracers.
!------------------------------------------------------------------------------
!
!  TNU2        Nonlinear model lateral, harmonic, constant, mixing
!              coefficient (m2/s) for active (NAT) and inert (NPT) tracer
!              variables. If variable horizontal diffusion is activated,
!              TNU2 is the mixing coefficient for the largest grid-cell
!              in the domain.
!
!  TNU4        Nonlinear model lateral, biharmonic, constant, mixing
!              coefficient (m4/s) for active (NAT) and inert (NPT) tracer
!              variables. If variable horizontal diffusion is activated,
!              TNU4 is the mixing coefficient for the largest grid-cell
!              in the domain.
!
!  ad_TNU2     Adjoint-based algorithms lateral, harmonic, constant, mixing
!              coefficient (m2/s) for active (NAT) and inert (NPT) tracer
!              variables. If variable horizontal diffusion is activated,
!              ad_TNU2 is the mixing coefficient for the largest grid-cell
!              in the domain. In some applications, a larger value than
!              that used in the nonlinear model (basic state) is necessary
!              for stability.
!
!  ad_TNU4     Adjoint-based algorithms lateral, biharmonic, constant, mixing
!              coefficient (m4/s) for active (NAT) and inert (NPT) tracer
!              variables. If variable horizontal diffusion is activated,
!              ad_TNU4 is the mixing coefficient for the largest grid-cell
!              in the domain. In some applications, a larger value than
!              that used in the nonlinear model (basic state) is necessary
!              for stability.
!
!------------------------------------------------------------------------------
! Harmonic/biharmonic horizontal viscosity coefficients.
!------------------------------------------------------------------------------
!
!  VISC2       Nonlinear model lateral, harmonic, constant, mixing
!              coefficient (m2/s) for momentum. If variable horizontal
!              viscosity is activated, UVNU2 is the mixing coefficient
!              for the largest grid-cell in the domain.
!
!  VISC4       Nonlinear model lateral, biharmonic, constant mixing
!              coefficient (m4/s) for momentum. If variable horizontal
!              viscosity is activated, UVNU4 is the mixing coefficient
!              for the largest grid-cell in the domain.
!
!  ad_VISC2    Adjoint-based algorithms lateral, harmonic, constant, mixing
!              coefficient (m2/s) for momentum. If variable horizontal
!              viscosity is activated, ad_UVNU2 is the mixing coefficient
!              for the largest grid-cell in the domain. In some applications,
!              a larger value than that used in the nonlinear model (basic
!              state) is necessary for stability.
!
!  ad_VISC4    Adjoint-based algorithms lateral, biharmonic, constant mixing
!              coefficient (m4/s) for momentum. If variable horizontal
!              viscosity is activated, ad_UVNU4 is the mixing coefficient
!              for the largest grid-cell in the domain. In some applications,
!              a larger value than that used in the nonlinear model (basic
!              state) is necessary for stability.
!
!------------------------------------------------------------------------------
! Vertical mixing coefficients for active tracers.
!------------------------------------------------------------------------------
!
!  AKT_BAK     Background vertical mixing coefficient (m2/s) for active
!              (NAT) and inert (NPT) tracer variables.
!
!  ad_AKT_fac  Adjoint-based algorithms vertical mixing, basic state, scale
!              factor (nondimensional) for active (NAT) and inert (NPT)
!              tracer variables. In some applications, a smaller/larger
!              values of vertical mixing are necessary for stability. It
!              is only used when FORWARD_MIXING is activated.
!
!------------------------------------------------------------------------------
! Vertical mixing coefficient for momentum.
!------------------------------------------------------------------------------
!
!  AKV_BAK     Background vertical mixing coefficient (m2/s) for momentum.
!
!  ad_AKV_fac  Adjoint-based algorithms vertical mixing, basic state, scale
!              factor (nondimensional) for momentum. In some applications,
!              a smaller/larger values of vertical mixing are necessary for
!              stability. It is only used when FORWARD_MIXING is activated.
!
!------------------------------------------------------------------------------
! Turbulent closure parameters.
!------------------------------------------------------------------------------
!
!  AKK_BAK     Background vertical mixing coefficient (m2/s) for turbulent
!              kinetic energy.
!
!  AKP_BAK     Background vertical mixing coefficient (m2/s) for turbulent
!              generic statistical field, "psi".
!
!  TKENU2      Lateral, harmonic, constant, mixing coefficient (m2/s) for
!              turbulent closure variables.
!
!  TKENU4      Lateral, biharmonic, constant mixing coefficient (m4/s) for
!              turbulent closure variables.
!
!------------------------------------------------------------------------------
! Generic length-scale turbulence closure parameters.
!------------------------------------------------------------------------------
!
!  GLS_P       Stability exponent (non-dimensional).
!
!  GLS_M       Turbulent kinetic energy exponent (non-dimensional).
!
!  GLS_N       Turbulent length scale exponent (non-dimensional).
!
!  GLS_Kmin    Minimum value of specific turbulent kinetic energy
!
!  GLS_Pmin    Minimum Value of dissipation.
!
! Closure independent constraint parameters (non-dimensional):
!
!  GLS_CMU0    Stability coefficient.
!
!  GLS_C1      Shear production coefficient.
!
!  GLS_C2      Dissipation coefficient.
!
!  GLS_C3M     Buoyancy production coefficient (minus).
!
!  GLS_C3P     Buoyancy production coefficient (plus).
!
!  GLS_SIGK    Constant Schmidt number (non-dimensional) for turbulent
!              kinetic energy diffusivity.
!
!  GLS_SIGP    Constant Schmidt number (non-dimensional) for turbulent
!              generic statistical field, "psi".
!
! Suggested values for various parameterizations:
!
!              k-kl         k-epsilon    k-omega      gen
!
!      GLS_P = 0.d0          3.0d0       -1.0d0        2.0d0
!      GLS_M = 1.d0          1.5d0        0.5d0        1.0d0
!      GLS_N = 1.d0         -1.0d0       -1.0d0       -0.67d0
!   GLS_Kmin = 5.0d-6        7.6d-6       7.6d-6       1.0d-8
!   GLS_Pmin = 5.0d-6        1.0d-12      1.0d-12      1.0d-8
!
!   GLS_CMU0 = 0.5544d0      0.5477d0     0.5477d0     0.5544d0
!     GLS_C1 = 0.9d0         1.44d0       0.555d0      1.00d0
!     GLS_C2 = 0.52d0        1.92d0       0.833d0      1.22d0
!    GLS_C3M = 2.5d0        -0.4d0       -0.6d0        0.1d0
!    GLS_C3P = 1.0d0         1.0d0        1.0d0        1.0d0
!   GLS_SIGK = 1.96d0        1.0d0        2.0d0        0.8d0
!   GLS_SIGP = 1.96d0        1.30d0       2.0d0        1.07d0
!
!------------------------------------------------------------------------------
! Constants used in the various formulations of surface turbulent kinetic
! energy flux in the GLS.
!------------------------------------------------------------------------------
!
!  CHARNOK_ALPHA   Charnok surface roughness,
!                    Zos:   (charnok_alpha * u_star**2) / g
!
!  ZOS_HSIG_ALPHA  Roughness from wave amplitude,
!                    Zos:   zos_hsig_alpha * Hsig
!
!  SZ_ALPHA        Surface flux from wave dissipation,
!                    flux:  dt * sz_alpha * Wave_dissip
!
!  CRGBAN_CW       Surface flux due to Craig and Banner wave breaking,
!                    flux:  dt * crgban_cw * u_star**3
!
!------------------------------------------------------------------------------
! Constants used in the computation of momentum stress.
!------------------------------------------------------------------------------
!
!  RDRG        Linear bottom drag coefficient (m/s).
!
!  RDRG2       Quadratic bottom drag coefficient.
!
!  Zob         Bottom roughness (m).
!
!  Zos         Surface roughness (m).
!
!------------------------------------------------------------------------------
! Height of atmospheric measurements for bulk fluxes parameterization.
!------------------------------------------------------------------------------
!
!  BLK_ZQ      Height (m) of surface air humidity measurement. Usually,
!                recorded at 10 m.
!
!  BLK_ZT      Height (m) of surface air temperature measurement. Usually,
!                recorded at 2 or 10 m.
!
!  BLK_ZW      Height (m) of surface winds measurement. Usually, recorded
!                at 10 m.
!
!------------------------------------------------------------------------------
! Wetting and drying parameters.
!------------------------------------------------------------------------------
!
!  DCRIT       Minimum depth (m) for wetting and drying.
!
!------------------------------------------------------------------------------
! Jerlow Water type.
!------------------------------------------------------------------------------
!
!  WTYPE       Jerlov water type: an integer value from 1 to 5.
!
!------------------------------------------------------------------------------
! Body-force parameters. Used when CPP option BODYFORCE is activated.
!------------------------------------------------------------------------------
!
!  LEVSFRC     Deepest level to apply surface momentum stress as a body-force.
!
!  LEVBFRC     Shallowest level to apply bottom momentum stress as a body-force.
!
!------------------------------------------------------------------------------
! Vertical S-coordinates parameters.
!------------------------------------------------------------------------------
!
! The parameters below must be consistent in all input fields associated with
! the vertical grid.  The same vertical grid transformation (depths) needs to
! be used when preparing initial conditions, boundary conditions, climatology,
! observations, and so on. Please check:
!
!   https://www.myroms.org/wiki/index.php/Vertical_S-coordinate
!
! for details, rules and examples.
!
!
!  Vtransform  Vertical transformation equation:
!
!                (1) Original formulation (Shchepetkin and McWilliams, 2005),
!                    Vtransform=1 (In ROMS since 1999)
!
!                      z(x,y,s,t)=Zo(x,y,s)+zeta(x,y,t)*[1+Zo(x,y,s)/h(x,y)]
!
!                    where
!
!                      Zo(x,y,s)=hc*s+[h(x,y)-hc]*C(s)
!
!                (2) Improved formulation (A. Shchepetkin, 2005),
!                    Vtransform=2
!
!                      z(x,y,s,t)=zeta(x,y,t)*[zeta(x,y,t)+h(x,y)]*Zo(x,y,s)
!
!                    where
!
!                      Zo(x,y,s)=[hc*s(k)+h(x,y)*C(k)]/[hc+h(x,y)]
!
!                    The true sigma-coordinate system is recovered as hc goes
!                    to INFINITY. This is useful when configuring applications
!                    with flat bathymetry and uniform level thickness.
!                    Practically, you can achieve this by setting:
!
!                      THETA_S = 0.0d0
!                      THETA_B = 0.0d0
!                      TCLINE  = 1.0d+17       (a large number)
!
!
!  Vstretching Vertical stretching function, C(s):
!
!                (1) Original function (Song and Haidvogel, 1994),
!                    Vstretching=1
!
!                    C(s)=(1-theta_b)*[SINH(s*theta_s)/SINH(theta_s)]+
!                         theta_b*[-0.5+0.5*TANH(theta_s*(s+0.5))/
!                                           TANH(0.5*theta_s)]
!
!                (2) A. Shchepetkin (2005) function,
!                    Vstretching=2
!
!                      C(s)=Cweight*Csur(s)+(1-Cweight)*Cbot(s)
!
!                    where
!
!                      Csur(s)=[1-COSH(theta_s*s)]/[COSH(theta_s)-1]
!
!                      Cbot(s)=-1+[1-SINH(theta_b*(s+1))]/SINH(theta_b)
!
!                      Cweight=(s+1)**alpha*
!                              (1+(alpha/beta)*(1-(s+1)**beta))
!
!                (3) R. Geyer function for shallow sediment applications,
!                    Vstretching=3
!
!                      C(s)=Cweight*Cbot(s)+(1-Cweight)*Csur(s)
!
!                    where
!
!                      Csur(s)=-LOG(COSH(Hscale*ABS(s)** alpha))/
!                               LOG(COSH(Hscale))
!
!                      Cbot(s)= LOG(COSH(Hscale*(s+1)** beta))/
!                               LOG(COSH(Hscale))-1
!
!                      Cweight=0.5*(1-TANH(Hscale*(s+0.5))
!
!                (4) A. Shchepetkin (2010) improved double stretching function,
!                    Vstretching=4
!
!                      C(s)=[1-COSH(theta_s*s)]/[COSH(theta_s)-1]
!
!                    with bottom refinement
!
!                      C(s)=[EXP(theta_b*C(s))-1]/[1-EXP(-theta_b)]
!
!                    The resulting double transformation is continuous with
!                    respect control parameters theta_s and theta_b with a
!                    meaningful range of:
!
!                      0 <  theta_s <= 10.0
!                      0 <= theta_b <=  4.0
!
!              Many other stretching functions (Vstretching>4) are possible
!              provided that:
!
!                * C(s) is a dimensionless, nonlinear, monotonic function.
!                * C(s) is a continuous differentiable function, or
!                  a differentiable piecewise function with smooth transition.
!                * The stretching vertical coordinate ,s, is constrained
!                  between -1 <= s <= 0, with s=0 corresponding to the
!                  free-surface and s=-1 corresponding to the bathymetry.
!                * Similarly, the stretching function, C(s), is constrained
!                  between -1 <= C(s) <= 0, with C(0)=0 corresponding to the
!                  free-surface and C(-1)=-1 corresponding to the bathymetry.
!
!              These functions are coded in routine "Utility/set_scoord.F".
!
! Due to its functionality and properties, the default and recommended vertical
! coordinates transformation is:
!
!              Vtransform  = 2
!              Vstretching = 4
!
!
!  THETA_S     S-coordinate surface control parameter. The range of optimal
!              values depends on the vertical stretching function, C(s).
!
!  THETA_B     S-coordinate bottom  control parameter. The range of optimal
!              values depends on the vertical stretching function, C(s).
!
!  TCLINE      Critical depth (hc) in meters (positive) controlling the
!              stretching. It can be interpreted as the width of surface or
!              bottom boundary layer in which higher vertical resolution
!              (levels) is required during stretching.
!
!------------------------------------------------------------------------------
! Mean Density and background Brunt-Vaisala frequency.
!------------------------------------------------------------------------------
!
!  RHO0        Mean density (Kg/m3) used when the Boussinesq approximation
!              is inferred.
!
!  BVF_BAK     Background Brunt-Vaisala frequency squared (1/s2). Typical
!              values for the ocean range (as a function of depth) from
!              1.0E-4 to 1.0E-6.
!
!------------------------------------------------------------------------------
! Time Stamps.
!------------------------------------------------------------------------------
!
!  DSTART      Time stamp assigned to model initialization (days).  Usually
!              a Calendar linear coordinate, like modified Julian Day.  For
!              Example:
!
!                       Julian Day = 1  for  Nov 25, 0:0:0 4713 BCE
!              modified Julian Day = 1  for  May 24, 0:0:0 1968  CE GMT
!
!              It is called truncated or modified Julian day because an offset
!              of 2440000 needs to be added.
!
!  TIDE_START  Reference time origin for tidal forcing (days). This is the
!              time used when processing input tidal model data. It is needed
!              in routine "set_tides" to compute the correct phase lag with
!              respect ROMS/TOMS initialization time.
!
!  TIME_REF    Reference time (yyyymmdd.f) used to compute relative time:
!              elapsed time interval since reference-time.  The "units"
!              attribute takes the form "time-unit since reference-time".
!              This parameter also provides information about the calendar
!              used:
!
!              If TIME_REF = -2, model time and DSTART are in modified Julian
!              days units.  The "units" attribute is:
!
!                      'time-units since 1968-05-23 00:00:00 GMT'
!
!              If TIME_REF = -1, model time and DSTART are in a calendar
!              with 360 days in every year (30 days each month).  The "units"
!              attribute is:
!
!                      'time-units since 0001-01-01 00:00:00'
!
!              If TIME_REF = 0, model time and DSTART are in a common year
!              calendar with 365.25 days.  The "units" attribute is:
!
!                      'time-units since 0001-01-01 00:00:00'
!
!              If TIME_REF > 0, model time and DSTART are the elapsed time
!              units since specified reference time.  For example,
!              TIME_REF=20020115.5 will yield the following attribute:
!
!                      'time-units since 2002-01-15 12:00:00'
!
!------------------------------------------------------------------------------
! Nudging/relaxation time scales, inverse scales will be computed internally.
!------------------------------------------------------------------------------
!
! When passive/active open boundary conditions are activated, these nudging
! values correspond to the passive (outflow) nudging time scales.
!
!  TNUDG       Nudging time scale (days) for active tracer variables.
!              (1:NAT+NPT,1:Ngrids) values are expected.
!
!  ZNUDG       Nudging time scale (days) for free-surface.
!
!  M2NUDG      Nudging time scale (days) for 2D momentum.
!
!  M3NUDG      Nudging time scale (days) for 3D momentum.
!
!  OBCFAC      Factor between passive (outflow) and active (inflow) open
!              boundary conditions.  The nudging time scales for the
!              active (inflow) conditions are obtained by multiplying
!              the passive values by OBCFAC. If OBCFAC > 1, nudging on
!              inflow is stronger than on outflow (recommended).
!
!------------------------------------------------------------------------------
! Linear equation of State parameters.
!------------------------------------------------------------------------------
!
! Ignoring pressure, the linear equation of state is:
!
!              rho(:,:,:) = R0 - R0 * TCOEF * (t(:,:,:,:,itemp) - T0)
!                              + R0 * SCOEF * (t(:,:,:,:,isalt) - S0)
!
!              Typical values:     R0 = 1027.0  kg/m3
!                                  T0 = 10.0    Celsius
!                                  S0 = 35.0    nondimensional
!                               TCOEF = 1.7d-4  1/Celsius
!                               SCOEF = 7.6d-4  1/nondimensional
!
!              Notice that salinity has NO UNITS, it is nondimensional. Many
!              people use PSU (Practical Salinity Unit).  However, salinity
!              has always been defined as a conductivity ratio and does not
!              have physical units. For details, check the following forum
!              post:  www.myroms.org/forum/viewtopic.php?f=30&t=294
!
!  R0          Background density value (Kg/m3) used in Linear Equation of
!              State.
!
!  T0          Background potential temperature (Celsius) constant.
!
!  S0          Background salinity (nondimensional) constant.
!
!  TCOEF       Thermal expansion coefficient in Linear Equation of State.
!
!  SCOEF       Saline contraction coefficient in Linear Equation of State.
!
!------------------------------------------------------------------------------
! Slipperiness parameter.
!------------------------------------------------------------------------------
!
!  GAMMA2      Slipperiness variable, either 1.0 (free slip) or -1.0 (no slip).
!
!------------------------------------------------------------------------------
!  Tracer climatology processing switches.
!------------------------------------------------------------------------------
!
!  LtracerCLM  Logical switches (T/F) to specify which tracer variables
!              to consider when the option TCLIMATOLOGY is activated. Only
!              NAT active tracers (temperature, salinity) and NPT inert
!              tracers need to be specified here:
!
!                LtracerCLM(itemp,ng)     for temperature (itemp=1)
!                LtracerCLM(isalt,ng)     for salinity    (isalt=2)
!                LtracerCLM(NAT+1,ng)     for inert tracer 1
!                ...                      ...
!                LtracerCLM(NAT+NPT,ng)   for inert tracer NPT
!
!              Other biological and sediment tracers switches are specified in
!              their respective input scripts.
!
!              Recall that TCLIMATOLOGY is usually activated to nudge to
!              tracer climatology (TLCM_NUDGING).  The purpose of these
!              switches is to control which climatology tracer fields
!              (specially passive tracers) needs to be processed.  So we
!              may reduce the memory allocation for such array.
!
!------------------------------------------------------------------------------
!  Tracer point Sources/Sink sources switches.
!------------------------------------------------------------------------------
!
!  LtracerSrc  Logical switches (T/F) to specify which tracer variables
!              to consider when the option TS_PSOURCE is activated. Only
!              NAT active tracers (temperature, salinity) and NPT inert
!              tracers need to be specified here:
!
!                LtracerSrc(itemp,ng)     for temperature (itemp=1)
!                LtracerSrc(isalt,ng)     for salinity    (isalt=2)
!                LtracerSrc(NAT+1,ng)     for inert tracer 1
!                ...                      ...
!                LtracerSrc(NAT+NPT,ng)   for inert tracer NPT
!
!              Other biological and sediment tracers switches are specified in
!              their respective input scripts.
!
!              Recall that TS_PSOURCE is usually activated to add river runoff
!              as a point source. At minimum, it is necessary to specify both
!              temperature and salinity for all rivers.  The other tracers are
!              optional.
!
!              This logical switch REPLACES and ELIMINATES the need to have
!              or read the variable "river_flag(river)" in the input rivers
!              forcing NetCDF file:
!
!                double river_flag(river)
!                        river_flag:long_name = "river runoff tracer flag"
!                        river_flag:option_0 = "all tracers are off"
!                        river_flag:option_1 = "only temperature"
!                        river_flag:option_2 = "only salinity"
!                        river_flag:option_3 = "both temperature and salinity"
!                        river_flag:units = "nondimensional"
!
!              This logic was too cumbersome and complicated when additional
!              tracers are considered. However, this change is backward
!              compatible.
!
!              The LtracerSrc switch will be used to activate the reading of
!              respective tracer variable from input river forcing NetCDF
!              file. If you want to add other tracer variables (other than
!              temperature and salinity) as a source for a particular river(s),
!              you just need to specify such values on those river(s). Then,
!              set the values to ZERO on the other river(s) that do NOT
!              require such river forcing for that tracer. Recall that you
!              need to specify the tracer values for all rivers, even if
!              their values are zero.
!
!------------------------------------------------------------------------------
!  Adjoint sensitivity parameters.
!------------------------------------------------------------------------------
!
!  DstrS       Starting day for adjoint sensitivity forcing.
!
!  DendS       Ending   day for adjoint sensitivity forcing.
!
!              The adjoint forcing is applied at every time step according to
!              desired state functional stored in the adjoint sensitivity
!              NetCDF file. DstrS must be less than or equal to DendS. If both
!              values are zero, their values are reset internally to the full
!              range of the adjoint integration.
!
!  KstrS       Starting vertical level of the 3D adjoint state variables whose
!                sensitivity is required.
!  KendS       Ending   vertical level of the 3D adjoint state variables whose
!                sensitivity is required.
!
!  Lstate      Logical switches (TRUE/FALSE) to specify the adjoint state
!                variables whose sensitivity is required.
!
!                Lstate(isFsur):   Free-surface
!                Lstate(isUbar):   2D U-momentum
!                Lstate(isVbar):   2D V-momentum
!                Lstate(isUvel):   3D U-momentum
!                Lstate(isVvel):   3D V-momentum
!                Lstate(isTvar):   Traces (NT values expected)
!
!------------------------------------------------------------------------------
!  Forcing Singular Vectors or Stochastic Optimals parameters.
!------------------------------------------------------------------------------
!
!  Fstate      Logical switches (TRUE/FALSE) to specify state variables for
!                which Forcing Singular Vectors or Stochastic Optimals is
!                required.
!
!                Fstate(isFsur):   Free-surface
!                Fstate(isUbar):   2D U-momentum
!                Fstate(isVbar):   2D V-momentum
!                Fstate(isUvel):   3D U-momentum
!                Fstate(isVvel):   3D V-momentum
!                Fstate(isTvar):   Traces (NT values expected)
!
!                Fstate(isUstr):   surface U-stress
!                Fstate(isVstr):   surface V-stress
!                Fstate(isTsur):   surface tracers flux (NT values expected)
!
!  SO_decay    Stochastic Optimals time decorrelation scale (days) assumed
!                for red noise processes.
!
!  SO_sdev     Stochastic Optimals surface forcing standard deviation for
!                dimensionalization.
!
!                SO_sdev(isFsur):  Free-surface
!                SO_sdev(isUbar):  2D U-momentum
!                SO_sdev(isVbar):  2D V-momentum
!                SO_sdev(isUvel):  3D U-momentum
!                SO_sdev(isVvel):  3D V-momentum
!                SO_sdev(isTvar):  Traces (NT values expected)
!
!                SO_sdev(isUstr):  surface U-stress
!                SO_sdev(isVstr):  surface V-stress
!                SO_sdev(isTsur):  surface tracer flux (NT values expected)
!
!------------------------------------------------------------------------------
! Logical switches (T/F) to activate writing of instantaneous fields into
! HISTORY file.
!------------------------------------------------------------------------------
!
!  Hout(idUvel)  Write out 3D U-velocity component.
!  Hout(idVvel)  Write out 3D V-velocity component.
!  Hout(idu3dE)  Write out 3D Eastward  velocity component at RHO-points.
!  Hout(idv3dN)  Write out 3D Northward velocity component at RHO-points.
!  Hout(idWvel)  Write out 3D W-velocity component.
!  Hout(idOvel)  Write out 3D omega vertical velocity.
!  Hout(idUbar)  Write out 2D U-velocity component.
!  Hout(idVbar)  Write out 2D V-velocity component.
!  Hout(idu2dE)  Write out 2D Eastward  velocity component at RHO-points.
!  Hout(idv2dN)  Write out 2D Northward velocity component at RHO-points.
!  Hout(idFsur)  Write out free-surface.
!  Hout(idBath)  Write out time-dependent bathymetry.
!
!  Hout(idTvar)  Write out active (NAT) tracers: temperature and salinity.
!
!  Hout(idUsms)  Write out surface U-momentum stress.
!  Hout(idVsms)  Write out surface V-momentum stress.
!  Hout(idUbms)  Write out bottom  U-momentum stress.
!  Hout(idVbms)  Write out bottom  V-momentum stress.
!
!  Hout(idUbrs)  Write out current-induced, U-momentum stress.
!  Hout(idVbrs)  Write out current-induced, V-momentum stress.
!  Hout(idUbws)  Write out wind-induced, bottom U-wave stress.
!  Hout(idVbws)  Write out wind-induced, bottom V-wave stress.
!  Hout(idUbcs)  Write out bottom maximum wave and current U-stress.
!  Hout(idVbcs)  Write out bottom maximum wave and current V-stress.
!
!  Hout(idUbot)  Write out wind-induced, bed wave orbital U-velocity.
!  Hout(idVbot)  Write out wind-induced, bed wave orbital V-velocity.
!  Hout(idUbur)  Write out bottom U-velocity above bed.
!  Hout(idVbvr)  Write out bottom V-velocity above bed.
!
!  Hout(idW2xx)  Write out 2D radiation stress, Sxx component.
!  Hout(idW2xy)  Write out 2D radiation stress, Sxy component.
!  Hout(idW2yy)  Write out 2D radiation stress, Syy component.
!  Hout(idU2rs)  Write out 2D U-radiation stress.
!  Hout(idV2rs)  Write out 2D V-radiation stress.
!  Hout(idU2Sd)  Write out 2D U-Stokes velocity.
!  Hout(idV2Sd)  Write out 2D V-Stokes velocity.
!
!  Hout(idW3xx)  Write out 3D radiation stress, Sxx component.
!  Hout(idW3xy)  Write out 3D radiation stress, Sxy component.
!  Hout(idW3yy)  Write out 3D radiation stress, Syy component.
!  Hout(idW3zx)  Write out 3D radiation stress, Szx component.
!  Hout(idW3zy)  Write out 3D radiation stress, Szy component.
!  Hout(idU3rs)  Write out 3D U-radiation stress.
!  Hout(idV3rs)  Write out 3D V-radiation stress.
!  Hout(idU3Sd)  Write out 3D U-Stokes velocity.
!  Hout(idV3Sd)  Write out 3D V-Stokes velocity.
!
!  Hout(idWamp)  Write out wave height.
!  Hout(idWlen)  Write out wave length.
!  Hout(idWdir)  Write out wave direction.
!  Hout(idWptp)  Write out wave surface period.
!  Hout(idWpbt)  Write out wave bottom period.
!  Hout(idWorb)  Write out wave bottom orbital velocity.
!  Hout(idWdis)  Write out wave dissipation.
!
!  Hout(idPair)  Write out surface air pressure.
!  Hout(idUair)  Write out surface U-wind component.
!  Hout(idVair)  Write out surface V-wind component.
!
!  Hout(idTsur)  Write out surface net heat and salt flux
!  Hout(idLhea)  Write out latent heat flux.
!  Hout(idShea)  Write out sensible heat flux.
!  Hout(idLrad)  Write out long-wave radiation flux.
!  Hout(idSrad)  Write out short-wave radiation flux.
!  Hout(idEmPf)  Write out E-P flux.
!  Hout(idevap)  Write out evaporation rate.
!  Hout(idrain)  Write out precipitation rate.
!
!  Hout(idDano)  Write out density anomaly.
!  Hout(idVvis)  Write out vertical viscosity coefficient.
!  Hout(idTdif)  Write out vertical diffusion coefficient of temperature.
!  Hout(idSdif)  Write out vertical diffusion coefficient of salinity.
!  Hout(idHsbl)  Write out depth of oceanic surface boundary layer.
!  Hout(idHbbl)  Write out depth of oceanic bottom boundary layer.
!  Hout(idMtke)  Write out turbulent kinetic energy.
!  Hout(idMtls)  Write out turbulent kinetic energy times length scale.
!
!  Hout(inert)   Write out extra inert passive tracers.
!
!  Hout(idBott)  Write out exposed sediment layer properties, 1:MBOTP.
!
!------------------------------------------------------------------------------
! Logical switches (T/F) to activate writing of time-averaged fields into
! AVERAGE file.
!------------------------------------------------------------------------------
!
!  Aout(idUvel)  Write out 3D U-velocity component.
!  Aout(idVvel)  Write out 3D V-velocity component.
!  Aout(idu3dE)  Write out 3D Eastward  velocity component at RHO-points.
!  Aout(idv3dN)  Write out 3D Northward velocity component at RHO-points.
!  Aout(idWvel)  Write out 3D W-velocity component.
!  Aout(idOvel)  Write out 3D omega vertical velocity.
!  Aout(idUbar)  Write out 2D U-velocity component.
!  Aout(idVbar)  Write out 2D V-velocity component.
!  Aout(idu2dE)  Write out 2D Eastward  velocity component at RHO-points.
!  Aout(idv2dN)  Write out 2D Northward velocity component at RHO-points.
!  Aout(idFsur)  Write out free-surface.
!
!  Aout(idTvar)  Write out active (NAT) tracers: temperature and salinity.
!
!  Aout(idUsms)  Write out surface U-momentum stress.
!  Aout(idVsms)  Write out surface V-momentum stress.
!  Aout(idUbms)  Write out bottom  U-momentum stress.
!  Aout(idVbms)  Write out bottom  V-momentum stress.
!
!  Aout(idW2xx)  Write out 2D radiation stress, Sxx component.
!  Aout(idW2xy)  Write out 2D radiation stress, Sxy component.
!  Aout(idW2yy)  Write out 2D radiation stress, Syy component.
!  Aout(idU2rs)  Write out 2D U-radiation stress.
!  Aout(idV2rs)  Write out 2D V-radiation stress.
!  Aout(idU2Sd)  Write out 2D U-Stokes velocity.
!  Aout(idV2Sd)  Write out 2D V-Stokes velocity.
!
!  Aout(idW3xx)  Write out 3D radiation stress, Sxx component.
!  Aout(idW3xy)  Write out 3D radiation stress, Sxy component.
!  Aout(idW3yy)  Write out 3D radiation stress, Syy component.
!  Aout(idW3zx)  Write out 3D radiation stress, Szx component.
!  Aout(idW3zy)  Write out 3D radiation stress, Szy component.
!  Aout(idU3rs)  Write out 3D U-radiation stress.
!  Aout(idV3rs)  Write out 3D V-radiation stress.
!  Aout(idU3Sd)  Write out 3D U-Stokes velocity.
!  Aout(idV3Sd)  Write out 3D V-Stokes velocity.
!
!  Aout(idPair)  Write out surface air pressure.
!  Aout(idUair)  Write out surface U-wind component.
!  Aout(idVair)  Write out surface V-wind component.
!
!  Aout(idTsur)  Write out surface net heat and salt flux
!  Aout(idLhea)  Write out latent heat flux.
!  Aout(idShea)  Write out sensible heat flux.
!  Aout(idLrad)  Write out long-wave radiation flux.
!  Aout(idSrad)  Write out short-wave radiation flux.
!  Aout(idevap)  Write out evaporation rate.
!  Aout(idrain)  Write out precipitation rate.
!
!  Aout(idDano)  Write out density anomaly.
!  Aout(idVvis)  Write out vertical viscosity coefficient.
!  Aout(idTdif)  Write out vertical diffusion coefficient of temperature.
!  Aout(idSdif)  Write out vertical diffusion coefficient of salinity.
!  Aout(idHsbl)  Write out depth of oceanic surface boundary layer.
!  Aout(idHbbl)  Write out depth of oceanic bottom boundary layer.
!
!  Aout(id2dRV)  Write out 2D relative vorticity (vertically integrated).
!  Aout(id3dRV)  Write out 3D relative vorticity.
!  Aout(id2dPV)  Write out 2D potential vorticity (shallow water).
!  Aout(id3dPV)  Write out 3D potential vorticity.
!
!  Aout(idu3dD)  Write out detided 3D U-velocity.
!  Aout(idv3dD)  Write out detided 3D V-velocity.
!  Aout(idu2dD)  Write out detided 2D U-velocity.
!  Aout(idv2dD)  Write out detided 2D V-velocity.
!  Aout(idFsuD)  Write out detided free-surface
!
!  Aout(idTrcD)  Write out detided temperature and salinity.
!
!  Aout(idHUav)  Write out u-volume flux, Huon.
!  Aout(idHVav)  Write out v-volume flux, Hvom.
!  Aout(idUUav)  Write out quadratic <u*u> term.
!  Aout(idUVav)  Write out quadratic <u*v> term.
!  Aout(idVVav)  Write out quadratic <v*v> term.
!  Aout(idU2av)  Write out quadratic <ubar*ubar> term.
!  Aout(idV2av)  Write out quadratic <vbar*vbar> term.
!  Aout(idZZav)  Write out quadratic <zeta*zeta> term.
!
!  Aout(idTTav)  Write out quadratic <t*t> active and inert tracers terms.
!  Aout(idUTav)  Write out quadratic <u*t> active and inert tracers terms.
!  Aout(idVTav)  Write out quadratic <v*t> active and inert tracers terms.
!  Aout(iHUTav)  Write out active and inert tracer u-volume flux, <Huon*t>.
!  Aout(iHVTav)  Write out active and inert tracer v-volume flux, <Hvom*t>.
!
!  Aout(inert)   Write out extra inert passive tracers.
!
!------------------------------------------------------------------------------
! Logical switches (T/F) to activate writing of time-averaged fields into
! DIAGNOSTIC file.
!------------------------------------------------------------------------------
!
! Time-averaged, 2D momentum (ubar,vbar) diagnostic terms:
! (if DIAGNOSTICS_UV)
!
! Dout(M2rate)   Write out acceleration.
! Dout(M2pgrd)   Write out pressure gradient.
! Dout(M2fcor)   Write out Coriolis force, if UV_COR.
! Dout(M2hadv)   Write out horizontal total advection, if UV_ADV.
! Dout(M2xadv)   Write out horizontal  XI-advection, if UV_ADV.
! Dout(M2yadv)   Write out horizontal ETA-advection, if UV_ADV.
! Dout(M2hrad)   Write out horizontal total radiation stress, NEARSHORE_MELLOR.
! Dout(M2hvis)   Write out horizontal total viscosity, if UV_VIS2 or UV_VIS4.
! Dout(M2xvis)   Write out horizontal  XI-viscosity, if UV_VIS2 or UV_VIS4.
! Dout(M2yvis)   Write out horizontal ETA-viscosity, if UV_VIS2 or UV_VIS4.
! Dout(M2sstr)   Write out surface stress.
! Dout(M2bstr)   Write out bottom stress
!
! Time-averaged, 3D momentum (u,v) diagnostic terms:
! (if SOLVE3D and DIAGNOSTICS_UV)
!
! Dout(M3rate)   Write out acceleration.
! Dout(M3pgrd)   Write out pressure gradient.
! Dout(M3fcor)   Write out Coriolis force, if UV_COR.
! Dout(M3hadv)   Write out horizontal total advection, if UV_ADV.
! Dout(M3xadv)   Write out horizontal  XI-advection, if UV_ADV.
! Dout(M3yadv)   Write out horizontal ETA-advection, if UV_ADV.
! Dout(M3hrad)   Write out horizontal total radiation stress, NEARSHORE_MELLOR.
! Dout(M3vrad)   Write out vertical radiation stress, if NEARSHORE_MELLOR.
! Dout(M3hvis)   Write out horizontal total viscosity, if UV_VIS2 or UV_VIS4.
! Dout(M3xvis)   Write out horizontal  XI-viscosity, if UV_VIS2 or UV_VIS4.
! Dout(M3yvis)   Write out horizontal ETA-viscosity, if UV_VIS2 or UV_VIS4.
! Dout(M3yvis)   Write out horizontal ETA-viscosity, if UV_VIS2 or UV_VIS4.
! Dout(M3vvis)   Write out vertical viscosity.
!
! Time-averaged, active (temperature and salinity) and passive (inert) tracer
! diagnostic terms, [1:NAT+NPT,Ngrids] values expected:
! (if SOLVE3D and DIAGNOSTICS_TS)
!
! Dout(iTrate)   Write out time rate of change.
! Dout(iThadv)   Write out horizontal total advection.
! Dout(iTxadv)   Write out horizontal  XI-advection.
! Dout(iTyadv)   Write out horizontal ETA-advection.
! Dout(iTvadv)   Write out vertical advection.
! Dout(iThdif)   Write out horizontal total diffusion, if TS_DIF2 or TS_DIF4.
! Dout(iTxdif)   Write out horizonta1  XI-diffusion, if TS_DIF2 or TS_DIF4.
! Dout(iTydif)   Write out horizontal ETA-diffusion, if TS_DIF2 or TS_DIF4.
! Dout(iTsdif)   Write out horizontal   S-diffusion, if TS_DIF2 or TS_DIF4 and
!                  rotated tensor (MIX_GEO_TS or MIX_ISO_TS).
! Dout(iTvdif)   Write out vertical diffusion.
!
!------------------------------------------------------------------------------
! Generic User parameters.
!------------------------------------------------------------------------------
!
!  NUSER       Number of User parameters to consider (integer).
!  USER        Vector containing user parameters (real array). This array
!                is used with the SANITY_CHECK to test the correctness of
!                the tangent linear adjoint models.  It contains information
!                of the model variable and grid point to perturb:
!
!                INT(user(1)):  tangent state variable to perturb
!                INT(user(2)):  adjoint state variable to perturb
!                               [isFsur=1] free-surface
!                               [isUbar=2] 2D U-momentum
!                               [isVbar=3] 2D V-momentum
!                               [isUvel=4] 3D U-momentum
!                               [isVvel=5] 3D V-momentum
!                               [isTvar=6] First tracer (temperature)
!                               [   ...  ]
!                               [isTvar=?] Last tracer
!
!                INT(user(3)):  I-index of tangent variable to perturb
!                INT(user(4)):  I-index of adjoint variable to perturb
!                INT(user(5)):  J-index of tangent variable to perturb
!                INT(user(6)):  J-index of adjoint variable to perturb
!                INT(user(7)):  K-index of tangent variable to perturb, if 3D
!                INT(user(8)):  K-index of adjoint variable to perturb, if 3D
!
!                Set tangent and adjoint parameters to the same values
!                if perturbing and reporting the same variable.
!
!------------------------------------------------------------------------------
! I/O NetCDF files parameters.
!------------------------------------------------------------------------------
!
! NetCDF-4/HDF5 compression parameters for output files. This capability
! is used when both HDF5 and DEFLATE C-preprocessing options are
! activated. The user needs to compile with the NetCDF-4/HDF5 and MPI
! libraries. File deflation cannot be used in parallel I/O for writing
! because the compression makes it impossible for the HDF5 library
! to exactly map the data to the disk location.  For more information,
! check NetCDF official website: www.unidata.ucar.edu/software/netcdf.
!
! NC_SHUFFLE    Shuffle filter integer flag. If non-zero, turn on shuffle
!                 filter.
!
! NC_DEFLATE    Deflate filter integer flag, If non-zero, turn on deflate
!                 filter at the level specified by the NC_DLEVEL parameter.
!
! NC_DLEVEL     Deflate filter level parameter (integer). If NC_DEFLATE is
!                 non-zero, set the deflate level to this value. Must be
!                 between 0 and 9.
!
!------------------------------------------------------------------------------
! Input/output NetCDF file names (string with a maximum of 256 characters).
!------------------------------------------------------------------------------
!
! Input file names:
!
!  GRDNAME     Input grid file name.
!
!  ININAME     Input nonlinear initial conditions file name. It can be a
!                re-start file.
!  ITLNAME     Input tangent linear model initial conditions file name.
!  IRPNAME     Input representer model initial conditions file name.
!  IADNAME     Input adjoint model initial conditions file name.
!
!  FWDNAME     Input forward solution fields file name.
!  ADSNAME     Input adjoint sensitivity functional file name.
!
! Nesting grids connectivity data:
!
!  NGCNAME     Input nested grids contact points information file name. This
!                NetCDF file is currently generated using script:
!
!                matlab/grid/contact.m
!
!                from the ROMS Matlab repository.  The nesting information
!                is not trivial and this Matlab scripts is quite complex. See
!
!                https://www.myroms.org/wiki/index.php/Nested_Grids
!                https://www.myroms.org/wiki/index.php/Grid_Processing_Scripts
!
!                for more information.
!
! Input lateral boundary conditions and climatology file names:
!
!  BRYNAME     Input open boundary data file name(s) per nested grid.
!  CLMNAME     Input climatology fields file name(s) per nested grid
!
!  The USER has the option to split input data time records into several
!  NetCDF files, as many as required. If so, use a single line per entry
!  with a vertical bar (|) symbol after each entry, except the last one:
!
!    BRYNAME == my_bry_year1.nc |
!               my_bry_year2.nc
!
!    CLMNAME == my_clm_year1.nc |
!               my_clm_year2.nc
!
! Input forcing file(s) name:
!
!  NFFILES     Number of unique forcing files per nested grid.
!  FRCNAME     Input forcing fields file name per nested grid.
!
!  The USER has the option to enter several file names for forcing fields
!  and/or split input data time records for each nested grid. For example,
!  the USER may have different files for wind products, heat fluxes, rivers,
!  tides, etc.  The model will scan the file list and will read the needed
!  data from the first file in the list containing the forcing field.
!  Therefore, the order of the file names is very important. It is also
!  possible to split input data time records into several NetCDF files.
!
!  Use a single line per entry with a continuation (\) or vertical bar (|)
!  symbol after each entry, except the last one:
!
!    NFFILES == 8                          ! number of unique forcing files
!
!    FRCNAME == my_rivers.nc      \        ! river forcing
!               my_tides.nc       \        ! tidal forcing
!               my_lwrad_year1.nc |        ! net longwave radiation flux
!               my_lwrad_year2.nc \
!               my_swrad_year1.nc |        ! solar shortwave radiation flux
!               my_swrad_year2.nc \
!               my_winds_year1.nc |        ! surface winds
!               my_winds_year2.nc \
!               my_Pair_year1.nc  |        ! surface air pressure
!               my_Pair_year2.nc  \
!               my_Qair_year1.nc  |        ! surface air relative humidity
!               my_Qair_year2.nc  \
!               my_Tair_year1.nc  |        ! surface air temperature
!               my_Tair_year2.nc
!
! Output file names:
!
!  GSTNAME     Output GST analysis re-start file name.
!  RSTNAME     Output re-start file name.
!  HISNAME     Output history file name.
!  TLFNAME     Output impulse forcing for tangent linear (TLM and RPM) models.
!  TLMNAME     Output tangent linear file name.
!  ADJNAME     Output adjoint file name.
!  AVGNAME     Output averages file name.
!  DIANAME     Output diagnostics file name.
!  STANAME     Output stations file name.
!  FLTNAME     Output floats file name.
!
!------------------------------------------------------------------------------
! Input ASCII parameters file names.
!------------------------------------------------------------------------------
!
!  APARNAM     Input assimilation parameters file name.
!  SPOSNAM     Input stations positions file name.
!  FPOSNAM     Input initial drifters positions file name.
!  BPARNAM     Input biological parameters file name.
!  SPARNAM     Input sediment transport parameters file name.
!  USRNAME     USER's input generic file name.
!
