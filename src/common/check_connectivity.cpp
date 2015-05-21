/*-
 * This file is part of Libight <https://libight.github.io/>.
 *
 * Libight is free software. See AUTHORS and LICENSE for more
 * information on the copying conditions.
 */

#include <stdexcept>
#include <new>

#include <event2/event.h>
#include <event2/dns.h>

#include <ight/common/check_connectivity.hpp>
#include <ight/common/log.hpp>

using namespace ight::common::check_connectivity;

void
Network::cleanup(void)  // Idempotent cleanup function
{
    if (dnsbase != NULL) {
        evdns_base_free(dnsbase, 0);
        dnsbase = NULL;
    }
    if (evbase != NULL) {
        event_base_free(evbase);
        evbase = NULL;
    }
}

void
Network::dns_callback(int result, char type, int count, int ttl,
                      void *addresses, void *opaque)
{
    auto that = static_cast<Network *>(opaque);

    // Suppress "unused variable" warnings
    (void) type;
    (void) count;
    (void) ttl;
    (void) addresses;

    switch (result) {
    case DNS_ERR_NONE:
    case DNS_ERR_FORMAT:
    case DNS_ERR_SERVERFAILED:
    case DNS_ERR_NOTEXIST:
    case DNS_ERR_NOTIMPL:
    case DNS_ERR_REFUSED:
    case DNS_ERR_TRUNCATED:
    case DNS_ERR_NODATA:
        that->is_up = true;
        break;
    default:
        that->is_up = false;
    }

    if (event_base_loopbreak(that->evbase) != 0) {
        throw std::runtime_error("Cannot exit from event loop");
    }
}

Network::Network(void)
{
    if ((evbase = event_base_new()) == NULL) {
        cleanup();
        throw std::bad_alloc();
    }

    if ((dnsbase = evdns_base_new(evbase, 1)) == NULL) {
        cleanup();
        throw std::bad_alloc();
    }

    if (evdns_base_resolve_ipv4(dnsbase, "ebay.com", DNS_QUERY_NO_SEARCH,
                                dns_callback, this) == NULL) {
        cleanup();
        throw std::runtime_error("cannot resolve 'ebay.com'");
    }

    if (event_base_dispatch(evbase) != 0) {
        cleanup();
        throw std::runtime_error("event_base_dispatch() failed");
    }

    cleanup();

    if (!is_up) {
        ight_warn("network is down");
    }
}
