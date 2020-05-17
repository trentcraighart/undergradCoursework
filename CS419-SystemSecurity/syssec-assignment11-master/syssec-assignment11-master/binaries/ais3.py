#!/usr/bin/env python

import angr
import claripy
p = angr.Project("./bins/ais3_crackme")

flag_size = 100  # set as enough
sym_arg = claripy.BVS("sym_arg", flag_size * 8) # * 8 bcz it counts bits
argv = ["./bins/ais3_crackme", sym_arg]

state = p.factory.entry_state(args=argv, add_options={angr.options.LAZY_SOLVES})

sm = p.factory.simulation_manager(state)

sm.explore(find=0x400602)

if sm.found:
    flag = sm.found[0].solver.eval(sym_arg, cast_to=bytes)
    print(flag)
else:
    print("Failed to find a flag");
