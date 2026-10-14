// Host lookups by name and address, which wasi-libc lacks. gethostbyname
// resolves IPv4 addresses through the kernel's getaddrinfo. The root has no
// services database, so service lookups find nothing and callers use numeric
// ports.

#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

int h_errno;

struct hostent *gethostbyname(const char *name)
{
	static struct in_addr addr;
	static char *addrs[2] = {(char *)&addr, 0};
	static char *aliases[1];
	static char hname[NI_MAXHOST + 1];
	static struct hostent h = {hname, aliases, AF_INET, sizeof(addr), addrs};
	struct addrinfo hints = {.ai_family = AF_INET}, *res;

	if (getaddrinfo(name, 0, &hints, &res) != 0) {
		h_errno = HOST_NOT_FOUND;
		return 0;
	}
	addr = ((struct sockaddr_in *)res->ai_addr)->sin_addr;
	freeaddrinfo(res);
	strncpy(hname, name, NI_MAXHOST);
	return &h;
}

struct hostent *gethostbyaddr(const void *addr, socklen_t len, int family)
{
	h_errno = HOST_NOT_FOUND;
	return 0;
}

const char *hstrerror(int err)
{
	switch (err) {
	case HOST_NOT_FOUND: return "Unknown host";
	case TRY_AGAIN: return "Host name lookup failure";
	case NO_RECOVERY: return "Unknown server error";
	case NO_DATA: return "No address associated with name";
	}
	return "Unknown error";
}

struct servent *getservbyname(const char *name, const char *proto)
{
	return 0;
}

struct servent *getservbyport(int port, const char *proto)
{
	return 0;
}
