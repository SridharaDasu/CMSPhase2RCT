class OutputTV:
    def __init__(self,fname):
        self.fname = fname
        with open(fname,"r") as f: rawinput = [line.strip() for line in f.readlines() if "#" not in line and any(line.strip())]
        
