ZDC polarimetry data
--------------------

* Obtain run-by-run ZDC polarimetry data
  - [2011](http://online.star.bnl.gov/scaler2011/polarimetry/asym/runs.txt)
  - [2012](http://online.star.bnl.gov/scaler2012/polarimetry/asym/runs.txt)
  - [2013](http://online.star.bnl.gov/scaler2013/polarimetry/asym/runs.txt)
  - save it to `zdc_pol_table.txt`

* copy or symlink `goodruns.dat` from scalers directory

* create `run_type` file with the following info:
  - `year` `sqrt(s)` `polarisation`
  - example: `13 510 L` for run13 pp510 longitudinal
  - this annoyance is needed to set the scales on the plots in `DrawPlots.C`

* Execute `FormatPolTable` to omit text columns from `zdc_pol_table.txt` in a new, 
  formatted file, `zdc_pol_table_formatted.txt`
  - there is a filter which only chooses runs in `goodruns.dat`

* Execute `BuildRunTree.C` to build a TTree, saved to `poltr.root`

* Execute `DrawPlots.C`
