## Generating RCT TV from MC Simulated Samples
Use make to compile the tvgen script to take a TTree with crystal information and generate an RCT TV.

The input root file is created using CMSSW Offline code that can be found here: [CrystalAnalyzer](https://github.com/ekoenig4/CrystalAnalyzer).

Follow the instructions to generate an output.root file and move that to the tvgen area.

The TTree in the output file carries et, ieta, and iphi information for each crystal in an event. 

To generate tv from this root file:
````
cmsenv
make
./tvgen output.root test_tv_in.txt
````
This script will then generate a number of tv from every event in the root file in the form.

test_tv_in_{ievent}_{pos,neg}{iphisection}.txt.

I recommend putting these files in a separate directory since there is a lot of them (i.e. ./tvgen output.root data/test_tv_in.txt).

This script makes a tv for each RCT section in the event and normalizes the et for each RCT section to a specified number (50 GeV at the moment).

The normalizing function can be changed inside the tvgen.cpp::process_card() method.

The normalizing function makes it so the highest et in the card is always 50 to assure that there are significant energy deposits in each card.
