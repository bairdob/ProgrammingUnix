cmd_/home/bair/kernel_practice/practice8/modules.order := {   echo /home/bair/kernel_practice/practice8/pci.ko; :; } | awk '!x[$$0]++' - > /home/bair/kernel_practice/practice8/modules.order
