// getnameinfo, which wasi-libc lacks. The kernel has no resolver, so hosts
// and services are always numeric, and NI_NAMEREQD fails.

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

int getnameinfo(const struct sockaddr *sa, socklen_t sl, char *host, socklen_t hostlen,
	char *serv, socklen_t servlen, int flags)
{
	const void *addr;
	int port;

	switch (sa->sa_family) {
	case AF_INET:
		if (sl < sizeof(struct sockaddr_in)) return EAI_FAMILY;
		addr = &((const struct sockaddr_in *)sa)->sin_addr;
		port = ntohs(((const struct sockaddr_in *)sa)->sin_port);
		break;
	case AF_INET6:
		if (sl < sizeof(struct sockaddr_in6)) return EAI_FAMILY;
		addr = &((const struct sockaddr_in6 *)sa)->sin6_addr;
		port = ntohs(((const struct sockaddr_in6 *)sa)->sin6_port);
		break;
	default:
		return EAI_FAMILY;
	}

	if (host && hostlen) {
		if (flags & NI_NAMEREQD) return EAI_NONAME;
		if (!inet_ntop(sa->sa_family, addr, host, hostlen)) return EAI_OVERFLOW;
	}
	if (serv && servlen && snprintf(serv, servlen, "%d", port) >= (int)servlen)
		return EAI_OVERFLOW;
	return 0;
}
