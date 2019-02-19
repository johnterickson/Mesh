// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil -*-
// Copyright 2019 The Heap-Layers and Mesh Authors. All rights reserved.
// Use of this source code is governed by the Apache License,
// Version 2.0, that can be found in the LICENSE file.

#pragma once
#ifndef MESH__ONE_WAY_MMAP_HEAP_H
#define MESH__ONE_WAY_MMAP_HEAP_H

#if defined(_MSC_VER)
#error "TODO"
#include <windows.h>
#else
// UNIX
#include <fcntl.h>
#include <stdlib.h>
#include "mman.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <map>
#endif

#include "common.h"

#ifndef HL_MMAP_PROTECTION_MASK
#error "define HL_MMAP_PROTECTION_MASK before including mmapheap.h"
#endif

#if !defined(MAP_ANONYMOUS) && defined(MAP_ANON)
#define MAP_ANONYMOUS MAP_ANON
#endif

namespace mesh {

// OneWayMmapHeap allocates address space through calls to mmap and
// will never unmap address space.
class OneWayMmapHeap {
private:
  DISALLOW_COPY_AND_ASSIGN(OneWayMmapHeap);

public:
  enum { Alignment = MmapWrapper::Alignment };

  OneWayMmapHeap() {
  }

  inline void *map(size_t sz, int flags, int fd = -1) {
    if (sz == 0)
      return nullptr;

    // Round up to the size of a page.
    sz = (sz + kPageSize - 1) & (size_t) ~(kPageSize - 1);

    void *ptr = mmap(nullptr, sz, HL_MMAP_PROTECTION_MASK, flags, fd, 0);
    if (ptr == MAP_FAILED)
      abort();

    d_assert(reinterpret_cast<size_t>(ptr) % Alignment == 0);

    return ptr;
  }

  inline void *malloc(size_t sz) {
#if defined(_WIN32)
    //TODO: MAP_NORESERVE
    return map(sz, MAP_PRIVATE | MAP_ANONYMOUS, -1);
#else
    return map(sz, MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1);
#endif
  }

  inline size_t getSize(void *ptr) const {
    return 0;
  }

  inline void free(void *ptr) {
  }
};

}  // namespace mesh

#endif  // MESH__ONE_WAY_MMAP_HEAP_H
