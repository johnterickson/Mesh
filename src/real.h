// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil -*-
// Copyright 2019 The Mesh Authors. All rights reserved.
// Use of this source code is governed by the Apache License,
// Version 2.0, that can be found in the LICENSE file.

#include <pthread.h>
#include <signal.h>

#ifdef __linux__
#include <sys/epoll.h>
#endif

#pragma once
#ifndef MESH__REAL_H
#define MESH__REAL_H

#define DECLARE_REAL(name) extern decltype(::name) *name

namespace mesh {
namespace real {
void init();

#ifdef __linux__
DECLARE_REAL(epoll_pwait);
DECLARE_REAL(epoll_wait);
#endif

DECLARE_REAL(pthread_create);

#if defined(_WIN32)
//hmm
#else
DECLARE_REAL(sigaction);
DECLARE_REAL(sigprocmask);
#endif
}  // namespace real
}  // namespace mesh

#endif  // MESH__REAL_H
