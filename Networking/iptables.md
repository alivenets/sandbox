# Set up port forwarding for local addresses ONLY

```
  # sysctl -w net.ipv4.conf.lxcbr0.route_localnet=1
  # -A POSTROUTING -m addrtype --src-type LOCAL -d 10.1.10.2/32 -p tcp -m tcp --dport 5678 -j MASQUERADE
  # -A OUTPUT -m addrtype --src-type LOCAL --dst-type LOCAL -p tcp --dport 5678 -j DNAT --to-destination 10.1.10.2:5678
```