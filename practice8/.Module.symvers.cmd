cmd_/home/bair/kernel_practice/practice8/Module.symvers := sed 's/ko$$/o/' /home/bair/kernel_practice/practice8/modules.order | scripts/mod/modpost -m -a  -o /home/bair/kernel_practice/practice8/Module.symvers -e -i Module.symvers   -T -
