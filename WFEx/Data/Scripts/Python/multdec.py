import sys
import glob
from subprocess import call
from os import path

Settings = {
    "Program": "luadec",
    "Decompiler": "-dis",
    "LASM_IN": "D:\.reversing\WFEx\Data\Scripts\Bytecode\*.bin",
    "LASM_OUT": "D:\.reversing\WFEx\Data\Scripts\LASM\\"
}

if __name__ == "__main__":

    lasm_in = glob.glob(Settings["LASM_IN"])
    print "Directory contains {} files.".format(len(lasm_in))
    if (len(lasm_in) < 1):
        print "Exiting."
        sys.exit(0)

    
    for luac in lasm_in:
        call_string = [Settings["Program"], Settings["Decompiler"]]
        call_string.append(luac)

        wo_ext = Settings["LASM_OUT"] + path.basename(luac).replace('bin', 'lasm')
        lasm_export = open(wo_ext, "w")
        call(call_string, stdout=lasm_export)
        lasm_export.close()


    print "Decompiling ended."