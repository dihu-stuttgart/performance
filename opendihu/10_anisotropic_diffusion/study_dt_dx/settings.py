# Anisotropic Diffusion 2D
# parameters: [<scenario_name> [<dt> [<dx>]]]

import sys, os

# parse command line options (scenario name)
scenario_name = ""
if len(sys.argv) <= 2:
  scenario_name = ""

dt = 1e-3
dx = 0.6
if len(sys.argv) >= 2+1:
  scenario_name = sys.argv[0]

if len(sys.argv) >= 2+2:
  dt = float(sys.argv[1])

if len(sys.argv) >= 2+3:
  dx = float(sys.argv[2])

prefactor = 0.01      # this is realistic (diffusion prefactor = Conductivity/(Am*Cm))
n = (int)(3.2/dx)    # number of elements in transversal direction

# number of elements
nx = 3*n
ny = n
nz = n

# number of nodes
mx = nx+1
my = ny+1
mz = nz+1

# initial values
initial_values = {}
k_begin = int(0.4*mz)
k_end = max(k_begin+2, int(0.6*mz))
j_begin = int(0.2*my)
j_end = max(j_begin+2, int(0.4*my))
i_begin = int(0.5*mx)
i_end = max(i_begin+2, int(0.8*mx))

for k in range(k_begin, k_end):
  for j in range(j_begin, j_end):
    for i in range(i_begin,i_end):
      index = k*mx*my + j*mx + i
      initial_values[index] = 100.0

print("dt: {}, dx: {}, n: {}, {} nodes in total, {} initial values".format(dt, dx, n, mx*my*mz, len(initial_values)))

config = {
  "solverStructureDiagramFile":     "solver_structure.txt",     # output file of a diagram that shows data connection between solvers
  "mappingsBetweenMeshesLogFile":  "",
  "scenarioName": scenario_name,
  "Solvers": {
    "linearSolver":
    {
      "solverType":         "gamg",
      "preconditionerType": "none",
      "gamgType":           "agg",
      "cycleType":          "cycleV",
      "nLevels":            25,
      
      "relativeTolerance":  1e-15,
      "absoluteTolerance":  1e-10,         # 1e-10 absolute tolerance of the residual    
      "maxIterations":      1e5,
      "dumpFormat":         "ascii",
      "dumpFilename":       "",
      
    }
  },
  "ImplicitEuler": {
    "initialValues":                initial_values,
    "timeStepWidth":                1e-3,
    "logTimeStepWidthAsKey":        "dt",
    "durationLogKey":               "duration_implicit_euler",
    "endTime":                      5.0,
    "checkForNanInf":               True,
    "solverName":                   "linearSolver",
    "timeStepOutputInterval":       100,
    "nAdditionalFieldVariables":    0,
    "inputMeshIsGlobal":            True,
    "dirichletBoundaryConditions":  {},
    
    "FiniteElementMethod" : {
      "nElements":        [3*n,n,n],
      "inputMeshIsGlobal": True,
      "physicalExtent":   [9.6, 3.2, 3.2],
      "solverName":       "linearSolver",
      "prefactor":        prefactor,
      "diffusionTensor":  [
        0.2, 0.2,  0,
        0.2, 1.0,  0,
        0,   0,    1,
      ],
    },
    
    "OutputWriter" : [
      #{"format": "Paraview", "outputInterval": 100, "filename": "out/out_diffusion3d", "fixedFormat": False, "combineFiles": True, "binary": False, "onlyNodalValues": True, "fileNumbering": "incremental"}
      {"format": "PythonFile", "outputInterval": 100, "filename": "out/out_diffusion3d", "fixedFormat": False, "combineFiles": True, "binary": False, "onlyNodalValues": True, "fileNumbering": "incremental"}
    ]
  },
}
