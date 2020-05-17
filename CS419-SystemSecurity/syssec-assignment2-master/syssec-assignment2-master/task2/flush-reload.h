#ifndef __FLUSH_RELOAD_H__
#define __FLUSH_RELOAD_H__

#pragma once

#include "cache.h"

void flush(volatile l1_entire_blocks*);
void reload(volatile l1_entire_blocks*);
void your_answer(char*);

#endif
