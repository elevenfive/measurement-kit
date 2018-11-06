// Part of Measurement Kit <https://measurement-kit.github.io/>.
// Measurement Kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.
#ifndef MEASUREMENT_KIT_COMMON_VERSION_H
#define MEASUREMENT_KIT_COMMON_VERSION_H

// Warning! Autogenerated file; do not edit this file directly as any change
// will be lost when you run `./build/includes` next.

#include <stdint.h>

// Note: we use semantic versioning (see: http://semver.org/)

// MK_VERSION is measurement-kit version according to manual tagging. This is
// updated when we bless a new release. It does not accurately describe a
// development build, for which MK_VERSION_FULL may be better.
#define MK_VERSION "0.9.0-beta"

// MEASUREMENT_KIT_VERSION is a backward compatibility alias for MK_VERSION.
#define MEASUREMENT_KIT_VERSION MK_VERSION

// MK_VERSION_FULL is the version obtained by runnning `git describe --tags`
// as part of the `./autogen.sh` script that prepares a source tarball. If we
// cannot run `git` because we're not in a git repository, then we set this
// variable equal to MK_VERSION.
#define MK_VERSION_FULL "v0.9.0-beta"

// MK_VERSION_MAJOR is the major version number extracted from MK_VERSION_FULL.
#define MK_VERSION_MAJOR 0

// MK_VERSION_MINOR is the minor version number extracted from MK_VERSION_FULL.
#define MK_VERSION_MINOR 9

// MK_VERSION_PATCH is the patch version number extracted from MK_VERSION_FULL.
#define MK_VERSION_PATCH 0

// MK_VERSION_STABLE is 1 if this is a stable release, 0 otherwise.
#define MK_VERSION_STABLE 0

// MK_VERSION_NUMERIC is the numberic representation of MK_VERSION_FULL,
// suitable to test the version of MK inside of headers.
//
// The format is as follows:
//
// ```
//     [0-9]{6}[0-9]{5}[0-9]{5}[0-1]{1}
//       ^^^     ^^^     ^^^     ^^^
//      major   minor   patch   stable
// ```
#define MK_VERSION_NUMERIC 0x00000000009000000LL

#ifdef __cplusplus
extern "C" {
#endif

// mk_version() returns MK_VERSION.
const char *mk_version(void);

// mk_version_full() returns MK_VERSION_FULL.
const char *mk_version_full(void);

// mk_version_major() returns MK_VERSION_MAJOR.
uint64_t mk_version_major(void);

// mk_version_minor() returns MK_VERSION_MINOR.
uint64_t mk_version_minor(void);

// mk_version_patch() returns MK_VERSION_PATCH.
uint64_t mk_version_patch(void);

// mk_version_stable() returns MK_VERSION_STABLE.
uint64_t mk_version_stable(void);

// mk_version_numeric() returns MK_VERSION_NUMERIC.
uint64_t mk_version_numeric(void);

// mk_version_openssl() returns the OpenSSL version we link with.
const char *mk_version_openssl(void);

// mk_openssl_version() is an alias for mk_version_openssl().
const char *mk_openssl_version(void);

// mk_libevent_version() returns the libevent version we link with.
const char *mk_libevent_version(void);

// mk_version_libevent() is an alias for mk_libevent_version().
const char *mk_version_libevent(void);

#ifdef __cplusplus
} // namespace mk
#endif
#endif
