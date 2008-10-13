// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*- 
// vim: ts=8 sw=2 smarttab
/*
 * Ceph - scalable distributed file system
 *
 * Copyright (C) 2004-2006 Sage Weil <sage@newdream.net>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software 
 * Foundation.  See file COPYING.
 * 
 */

#ifndef __EPURGE_H
#define __EPURGE_H

#include "config.h"
#include "include/types.h"

class EPurgeFinish : public LogEvent {
 protected:
  inodeno_t ino;
  off_t newsize, oldsize;

 public:
  EPurgeFinish(inodeno_t i, off_t ns, off_t os) : 
	LogEvent(EVENT_PURGEFINISH),
	ino(i), newsize(ns), oldsize(os) { }
  EPurgeFinish() : LogEvent(EVENT_PURGEFINISH) { }
  
  void print(ostream& out) {
    out << "purgefinish " << ino << " " << oldsize << " ->" << newsize;
  }

  void encode(bufferlist &bl) const {
    ::encode(ino, bl);
    ::encode(newsize, bl);
    ::encode(oldsize, bl);
  }
  void decode(bufferlist::iterator &bl) {
    ::decode(ino, bl);
    ::decode(newsize, bl);
    ::decode(oldsize, bl);
  }
  
  void update_segment();
  void replay(MDS *mds);
};

#endif
