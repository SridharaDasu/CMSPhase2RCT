## Generating RCT TV from MC Simulated Samples
Use make to compile the tvgen script to take a TTree with crystal information and generate an RCT TV.

The input root file is created using CMSSW Offline code that can be found here: [CrystalAnalyzer](https://github.com/ekoenig4/CrystalAnalyzer).

Follow the instructions to generate an output.root file and move that to the tvgen area.

The TTree in the output file carries et, ieta, and iphi information for each crystal in an event.

The datasets.txt file holds hdfs paths to already created files that can be used to make new tv.

To generate tv from this root file:
````
cmsenv
make
./tvgen output*.root test_tv_in.txt
````
This script will then generate a number of tv from every event in the root file in the form.

test_tv_in_{itv}.txt.

I recommend putting these files in a separate directory since there is a lot of them (i.e. ./tvgen output.root data/test_tv_in.txt).

This script makes a tv for each RCT section in the event.

Any number of root files can be passed into the script with the final argument being the tv vector name.

## Visualizing TV
Once a tv is created the parsetv project is used to make plots to be able to visualize the signiture.
````
python parsetv/visualize.py -i path/to/tv -w tv_plot_output.root
````
Any number of tv can be passed to parsetv/visualize.py with the -i option.

All plots will be put inside the tv_plot_output.root file (name specified by -w option)

## Already made TV
A large number of TV have already been made using the root files in datasets.txt

They can be found in the zipdata/ directory as .tar.gz files, to unzip them run
````
tar -zxvf zipdata/zipped_tv_in.tar.gz
````
