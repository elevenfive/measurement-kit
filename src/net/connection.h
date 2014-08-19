/*-
 * This file is part of Libight <https://libight.github.io/>.
 *
 * Libight is free software. See AUTHORS and LICENSE for more
 * information on the copying conditions.
 */

#ifndef LIBIGHT_CONNECTION_H
# define LIBIGHT_CONNECTION_H
# ifdef __cplusplus

#include "src/common/poller.h"

struct bufferevent;
struct evbuffer;

struct IghtStringVector;
struct IghtProtocol;

class IghtConnection {

	long long filedesc;
	bufferevent *bev;
	IghtProtocol *protocol;
	evbuffer *readbuf;
	unsigned int closing;
	unsigned int connecting;
	unsigned int reading;
	char *address;
	char *port;
	IghtStringVector *addrlist;
	char *family;
	IghtStringVector *pflist;
	unsigned int must_resolve_ipv4;
	unsigned int must_resolve_ipv6;
	IghtDelayedCall start_connect;

	IghtConnection(void);

	// Private destructor because destruction may be delayed
	~IghtConnection(void);

	// Libevent callbacks
	static void handle_read(bufferevent *, void *);
	static void handle_write(bufferevent *, void *);
	static void handle_event(bufferevent *, short, void *);

	// Functions used by connect_hostname()
	void connect_next(void);
	static void handle_resolve(int, char, int, int,
	    void *, void *);
	static void resolve(void *);

    public:
	static IghtConnection *attach(IghtProtocol *, long long);

	static IghtConnection *connect(IghtProtocol *, const char *,
	    const char *, const char *);

	static IghtConnection *connect_hostname(IghtProtocol *, const char *,
	    const char *, const char *);

	IghtProtocol *get_protocol(void);

	int set_timeout(double);
	int clear_timeout(void);

	int start_tls(unsigned int);

	int write_from(evbuffer *);

	int enable_read(void);
	int disable_read(void);

	void close(void);
};

# endif  /* __cplusplus */
#endif  /* LIBIGHT_CONNECTION_H */
