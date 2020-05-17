#!/usr/bin/env python

import angr

p = angr.Project("./bins/r200")

state = p.factory.entry_state()

sm = p.factory.simulation_manager(state)

# TODO: which address do you want to hit or avoid?
# Use gdb or r2 to figure this out!
# Hint: on r2, you may use pd @ main to disassemble some functions
#       also use pd @ sym.verify, etc..
sm.explore(find=0x00400936, avoid=[0x00400947])

s = sm.found[0]

print(s.posix.dumps(1))
print(s.posix.dumps(0))
