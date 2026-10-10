"""Minimal Python bootstrap for the upstream Python-backed Sensible Lang compiler."""
import argparse,os,runpy,sys
from pathlib import Path
ROOT=Path(__file__).resolve().parent
sys.path.insert(0,str(ROOT/'vendor'))
from mylang.compiler import translate

def build():
    for path in [*ROOT.glob('*.mylang'),*(ROOT/'tests').glob('*.mylang')]:
        result=translate(path.read_text(encoding='utf-8'))
        output=path.with_suffix('.py');code='# Generated from '+path.name+'. Edit the .mylang source.\n'+result.code
        compile(code,str(output),'exec')
        if not output.exists() or output.read_text()!=code:
            temporary=output.with_suffix('.py.next');temporary.write_text(code);temporary.replace(output)

if __name__=='__main__':
    parser=argparse.ArgumentParser();parser.add_argument('--build-only',action='store_true');parser.add_argument('--entry',default='app.py');options,args=parser.parse_known_args()
    build()
    if not options.build_only:
        sys.path.insert(0,str(ROOT));os.chdir(ROOT);entry=ROOT/options.entry;sys.argv=[str(entry),*args];runpy.run_path(str(entry),run_name='__main__')
