cmd_/home/bair/kernel_practice/practice8/pci.mod := printf '%s\n'   pci.o | awk '!x[$$0]++ { print("/home/bair/kernel_practice/practice8/"$$0) }' > /home/bair/kernel_practice/practice8/pci.mod
