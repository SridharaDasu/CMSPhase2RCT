#!/bin/sh

make || exit -1

generate() {
    ./tvgen $d/output_*.root rawdata/${sample}_tv_in.txt
    tar -czvf zipdata/${sample}_tv_in.tar.gz rawdata/${sample}_tv_in*
}
plot() {
    files=(rawdata/${sample}_tv_in*)
    if [[ ! -e "${files[0]}" ]]; then
	echo data/${sample}_tv_in.txt not found
	return
    fi
    python parsetv/visualize.py -i rawdata/${sample}_tv_in* -w visualize/${sample}_tv_plots.root

    if [[ -e dump_tfile ]]; then
	# Personal script for dumping tfile contents into pdf
	# /afs/hep.wisc.edu/home/ekoenig4/bin/dump_tfile
	dump_tfile visualize/${sample}_tv_plots.root -o ~/public_html/Trigger/MC_RCT_TV/${sample}_tv_plots.pdf -n 2
    fi
}

for d in $(cat datasets.txt); do
    echo $d
    sample=$(echo $d | python -c "print \"$d\".split(\"/\")[8].split(\"_\")[3].split(\"-\")[0]")
    # generate
    plot
done 
