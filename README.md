# performance

This repo contains input files for different scenarios and scripts for measurement and plotting.
Also results of earlier runs are archived.

A template scenario file is the top-level `default.sce` which should always contain the default values for all available variables. The scenario files should work with the lastest versions of branch `stable` in dihu-stuttgart/iron and dihu-stuttgart/iron-examples.

The scripts may need the following environment variables:

    OPENCMISS_REL_DIR    // path to the directory where ./cuboid is build
    OPENCMISS_INPUT_DIR  // path to the 'input' folder of cuboid, where all input files are located
    OPENCMISS_SCE_FILE   // path + filename of a scenario.sce file (can be empty)

Each scenario should have its own folder. Generated output files should be named `<name>.csv`.
To run a scenario, simply start the 'run.sh' file in the folder. To plot the results, eventually adjust plot title and `filename` variable in `plot.py`. Then run `./plot.py` or `./plot.py n` for only console output of the data.

To abort a running script, press CTRL+Z, then execute `kill %%`.
