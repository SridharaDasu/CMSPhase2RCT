from .InputTV import *
from .OutputTV import *
from argparse import ArgumentParser

parser = ArgumentParser()
parser.add_argument("-i","--input",type=InputTV,nargs="+",default=[])
parser.add_argument("-o","--output",type=OutputTV,nargs="+",default=[])
parser.add_argument("-w","--write",default="tv_plots.root")
args = parser.parse_args()
