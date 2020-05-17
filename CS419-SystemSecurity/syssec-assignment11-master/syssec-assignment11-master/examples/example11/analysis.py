#!/usr/bin/env python

import angr

p = angr.Project("./example11")

state = p.factory.entry_state()

sm = p.factory.simulation_manager(state)

"""
       ,==< 0x004006b7      7505           jne 0x4006be
       ||   0x004006b9      e849ffffff     call sym.bug                ; example11.c:19             bug();
"""
sm.explore(find=0x4006b9, avoid=[0x4006be])

s = sm.found[0]

print(s.posix.dumps(1))
print(s.posix.dumps(0))
