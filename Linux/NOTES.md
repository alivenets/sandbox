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
