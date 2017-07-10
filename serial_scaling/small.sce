# Scenario name: Monodomain (1D) solver testing
# Date: 22.6.17
# Author: Benjamin Maier
# dihu-stuttgart/iron version: d71fbb84d163d5505e0eb6d23d1339cc55f14360
# dihu-stuttgart/iron-examples version: a2e8742e1173dd8da93ac19a395371cd261201b8
#
# Designated number of Processors: 1
# Estimated run time (walltime): (varying)
#
# Scenario file for cuboid example
#
# Comment (sub-)lines start with # or !
# Specify assignments as Variable=Value, logical values as `T` or `F`.
# Variables are case-insensitive, whitespace between specifiers is ignored.
# Pass this file's name to cuboid as command argument. It must end in .sce and can be mixed with the usual arguments which are:
# ./cuboid <input folder> <X> <Y> <Z> <F> <A> <ODESolverId> <MonodomainSolverId> <MonodomainPreconditionerId>
# where X,Y,Z = NumberGlobal{X,Y,Z}Elements, A = NumberOfElementsInAtomicPortionPerDomain, F = NumberOfInSeriesFibres
# Command line arguments can also be an assignment, like `DebuggingOutput=T` or `X=1`.
# The command line arguments are processed in the order they occur, when this file appears, all its assignments are parsed.
# Therefore values can be overwritten when the filename is the first argument.

# ------------- discretization ----------------
# orientation: X = Xi1 = length, Y = Xi2 = width, Z = Xi3 = height
# fibres are parallel to X axis

# ----- this will be overridden by command arguments -------------
NumberGlobalXElements = 3       # number of finite elasticty elements in x-direction, alias x
NumberGlobalYElements = 4       # number of finite elasticty elements in y-direction, alias y
NumberGlobalZElements = 1       # number of finite elasticty elements in z-direction, alias z

NumberOfNodesInXi1 = 31         # number of bioelectric nodes per 3D FE element in direction of fibre (X direction), alias xi1
NumberOfNodesInXi2 = 2          # number of fibres per FE element in Y direction, alias xi2
NumberOfNodesInXi3 = 3          # number of fibres per FE element in Z direction, alias xi3

NumberOfInSeriesFibres = 1      # number of fibres that are in a series and mechanically connected. This is not completely tested, set to 1, alias f
NumberOfElementsInAtomicPortionPerDomain = 1    # defines unsplittable blocks of 3D FE elements for the decomposition on multiple processes, alias a

# ------------- debugging --------------------
OutputTimeStepStride = 10       # write output *.exnode files every nth timestep
EnableExportEMG = F             # if EMG should be output
DebuggingOutput = F
DebuggingOnlyRunShortPartOfSimulation = F    # abort simulation after first stimulation

# ------------- numerics -------------------
TimeStop = 3.0                  # total simulated time
ODETimeStep = 0.0001            # timestep size for 0D problem
PDETimeStep = 0.005    ! 0.005 # timestep size for 1D problem
ElasticityTimeStep = 0.10000000001  # timestep size for 3D problem

# solvers
ODESolverId = 1                 # 0D problem, ODE solver type: 1=explicit Euler, 2=BDF
MonodomainSolverId = 2          # 1D problem, solver
MonodomainPreconditionerId = 1  # 1D problem, preconditioner

# ODESolverId
# 1 explicit Euler (default)
# 2 BDF

# MonodomainSolverId
# 1 SOLVER_DIRECT_LU
# 2 SOLVER_ITERATIVE_GMRES (default)
# 3 SOLVER_ITERATIVE_CONJUGATE_GRADIENT
# 4 SOLVER_ITERATIVE_CONJGRAD_SQUARED

# MonodomainPreconditionerId
# 1 NO_PRECONDITIONER (default)
# 2 JACOBI_PRECONDITIONER
# 3 BLOCK_JACOBI_PRECONDITIONER
# 4 SOR_PRECONDITIONER
# 5 INCOMPLETE_CHOLESKY_PRECONDITIONER
# 6 INCOMPLETE_LU_PRECONDITIONER
# 7 ADDITIVE_SCHWARZ_PRECONDITIONER

NewtonMaximumNumberOfIterations = 500         # 3D solver maximum number of iterations
ElasticityLoopMaximumNumberOfIterations = 5   # number of load increments in pre-stretch simulation
NewtonTolerance = 1.E-8                       # abs. and rel. tolerance of 3D problem newton solver

# ------------- physical parameters ------------------

StimValue = 20000.0             # current value with which fibres are stimulated

# physical dimension
PhysicalLength = 3.0
PhysicalWidth = 3.0
PhysicalHeight = 1.5

OldTomoMechanics = T            # whether to use the old mechanical description of Thomas Heidlauf that works also in parallel
PMax = 7.5            ! N/cm^2        
Conductivity = 0.5
Am = 1.0
CmFast = 1.0
CmSlow = 1.0
Vmax = -0.02
InitialStretch = 1.0   ! 1.2

# -------------- input files --------------------------
InputDirectory = input                        # directory where all input files are found, relative to working directory
FiringTimesFile = MU_firing_times_10s.txt     # file that contains the time steps (rows) for each fibre (columns) when the fibre is stimulated (value 1 else 0)
InnervationZoneFile = innervation_zone_18.txt # the position of the neuromuscular junction for each fibre
FibreDistributionFile = MU_fibre_distribution_4050.txt    # the motor unit number distribution for the fibres
CellMLModelFilename = standard                # the CELLML model file (XML), "standard" gets replaced by the actual standard file, depending on OldTomoMechanics
