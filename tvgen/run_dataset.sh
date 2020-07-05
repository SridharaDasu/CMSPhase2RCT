#!/bin/sh

generate() {
    ./tvgen $d/output_1.root data/${sample}_tv_in.txt
}
plot() {
    files=(data/${sample}_tv_in*)
    if [[ ! -e "${files[0]}" ]]; then
	echo data/${sample}_tv_in.txt not found
	return
    fi
    python parsetv/visualize.py -i data/${sample}_tv_in* -o visualize/${sample}_tv_plots.root
    dump_tfile visualize/${sample}_tv_plots.root -o ~/public_html/Trigger/MC_RCT_TV/${sample}_tv_plots.pdf
}

for d in $(cat datasets.txt); do
    echo $d
    sample=$(echo $d | python -c "print \"$d\".split(\"/\")[8].split(\"_\")[3].split(\"-\")[0]")
    # generate
    plot
done 
