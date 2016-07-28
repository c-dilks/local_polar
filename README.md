ZDC polarimetry data
--------------------

* Create a directory for the dataset you want to look at
  - then cd into it, and run `ln -s ../scripts/* ./` to symlink the scripts
    and this readme

* Obtain run-by-run ZDC polarimetry data
  - [2011](http://online.star.bnl.gov/scaler2011/polarimetry/asym/runs.txt)
  - [2012](http://online.star.bnl.gov/scaler2012/polarimetry/asym/runs.txt)
  - [2013](http://online.star.bnl.gov/scaler2013/polarimetry/asym/runs.txt)
  - [2015](http://online.star.bnl.gov/scaler2015/polarimetry/asym/runs.txt)
  - (or from zdc polarimetry pages.. are these different files? should we just
     use both of them?.. not sure, but there aren't many runs here which intersect
     with the set of runs which I'm analysing)
    - [2011](http://online.star.bnl.gov/zdc2011/asym/runs.txt)
    - [2012](http://online.star.bnl.gov/zdc2012/asym/runs.txt)
    - [2013](http://online.star.bnl.gov/zdc2013/asym/runs.txt)
    - [2015](http://online.star.bnl.gov/zdc2015/asym/runs.txt)
  - save it to `zdc_pol_table.txt` (`curl [URL] > zdc_pol_table.txt`)

* copy or symlink `goodruns.dat` from `trgmon` repository

* create `run_type` file with the following info:
  - `year` `sqrt(s)` `polarisation`
  - example: `13 510 L` for run13 pp510 longitudinal
  - this annoyance is needed to set the scales on the plots in `DrawPlots.C`

* Execute `FormatPolTable` to omit text columns from `zdc_pol_table.txt` in a new, 
  formatted file, `zdc_pol_table_formatted.txt`
  - there is a filter which only chooses runs in `goodruns.dat`

* Execute `BuildRunTree.C` to build a TTree, saved to `poltr.root`

* Execute `DrawPlots.C`
