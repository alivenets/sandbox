#!/bin/bash -e

# Filter git commit log using grep
git log --pretty=oneline --grep="UBUNTU:" --all-match -F --no-merges $@
