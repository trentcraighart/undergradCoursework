#!/usr/bin/env python

import angr

p = angr.Project("./example10")

state = p.factory.entry_state()

sm = p.factory.simulation_manager(state)

sm.explore(find=[0x00400663], avoid=[0x400668])


s = sm.found[0]


print(s.posix.dumps(1))
print(s.posix.dumps(0))
