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

