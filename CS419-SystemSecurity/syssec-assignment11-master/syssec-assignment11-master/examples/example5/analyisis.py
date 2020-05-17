#!/usr/bin/env python

import angr

p = angr.Project("./example5")

state = p.factory.entry_state()

sm = p.factory.simulation_manager(state)


sm.explore(find=[0x004006f9], avoid=[0x00400680, 0x00400697, 0x004006ae, ])


s = sm.found[0]


print(s.posix.dumps(1))
print(s.posix.dumps(0))
