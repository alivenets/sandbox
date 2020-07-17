# NetworkManager and auto-generation of /etc/resolv.conf

For NetworkManager working in VM, it may auto-generated /etc/resolv.conf and override provided DNS nameserver addresses.

To disable it, check `/etc/NetworkManager/NetworkManager.conf`:

```
dns=default # should be "default". Missing line also means "default"
[global-dns-domain-*]
servers=8.8.4.4 # This should re REMOVED
```

Link to config description: https://developer.gnome.org/NetworkManager/stable/NetworkManager.conf.html

# Ignore host verification via SSH

Put the following lines into `~/.ssh/config`:

```
Host 192.168.7.2
    UserKnownHostsFile /dev/null
    StrictHostKeyChecking no
```

# Go back to previous branch

`git checkout -`

# `kill(-1)`

Do not forget that `kill(-1)` kills ALL process which it is allowed to kill. It is written in `kill(2)` manual.

# AppArmor: enable debug

```
# Kernel configuration: CONFIG_SECURITY_APPARMOR_DEBUG=y
# run-time in userspace:
$ echo Y > /sys/modules/apparmor/parameters/debug
```

# Virtualbox and vboxsf

When using VirtualBox and vboxsf filesystem driver, unexpected issues may happen. So, when debugging the code working natively or in Docker and not working in Virtualbox, try to check these things:

1. SSH agent forwarding
2. Synced directories (Volumes in docker, shared folders in VirtualBox)
3. Environment variables
4. Directories created in vboxsf synced directory

vboxsf has some limitations. Known ones are: unsupported inotify, etc.

# D-Bus debugging with root

Sometimes, when debugging D-Bus connection with root, the message of access denied may appear, even if service is running under root user.
That may happen if there is no policy for this bus for the root user.
So, to fix it, place the policy file for the bus into `/etc/dbus-1/system.d` or `/etc/dbus-1/session.d` directory.

# Import custom CA certificate

```
cp foo.crt /usr/local/share/ca-certificates/foo.crt
sudo update-ca-certificates
```

# D-Bus and UID processing

D-Bus has external authentication mechanism (AUTH EXTERNAL), which processes UID of the process sent by D-Bus client (https://dbus.freedesktop.org/doc/dbus-specification.html#auth-protocol)

In D-Bus server implementation (e.g. `dbus-daemon`), there is the following process:

1. Server receives AUTH request, then responds with `EXTERNAL` mechanism and asks for UID
2. Client send its UID (which is process effective UID)
3. Server checks in user database (which is basically the cache of `/etc/passwd` and `/etc/group`) to extract user credentials.
4. Server checks with bus policy if this user is allowed to manipulate this bus

The user configuration is static. That means, that the authentication is using only predefined configuration from `/etc`,
hence there is no chance to use effective process GID and supplementary groups which are set in runtime. Only UID matters.
