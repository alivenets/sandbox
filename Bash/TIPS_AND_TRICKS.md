# Bash Tips and Tricks

## Diff from stdin

```
diff <(cat file1 | sort | uniq) <(cat file2 | sort | uniq)
```

# Squeeze spaces in a file

```
echo "name     = value" | tr -s " " # output: "name = value"
```
