#!/usr/bin/env python

import angr

import claripy

proj = angr.Project('./bins/unbreakable-enterprise-product-activation',
        load_options={"auto_load_libs": False})

input_size = 100;

sym_arg = claripy.BVS("sym_arg", input_size * 8)

argv = ["./bins/unbreakable-enterprise-product-activation", sym_arg]
state = proj.factory.entry_state(args=argv, add_options={angr.options.LAZY_SOLVES})
state.libc.buf_symbolic_bytes=input_size + 1

# add constraints to first few bytes
#state.add_constraints(sym_arg.chop(8)[0] == 'C')
#state.add_constraints(sym_arg.chop(8)[1] == 'T')
#state.add_constraints(sym_arg.chop(8)[2] == 'F')
#state.add_constraints(sym_arg.chop(8)[3] == '{')

sm = proj.factory.simulation_manager(state)

# TODO: what do you want to find?
# use r2, pd @ main and also
# x/100i address in gdb
sm.explore(find=0x0)

if sm.found:
    flag = sm.found[0].solver.eval(sym_arg, cast_to=bytes)
    print(flag)
else:
    print("Failed to find a flag");
