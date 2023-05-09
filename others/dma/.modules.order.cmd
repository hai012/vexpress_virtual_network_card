cmd_/mnt/samba/petalinux/zcu102/work/dma/modules.order := {   echo /mnt/samba/petalinux/zcu102/work/dma/dma_copy_test.ko; :; } | awk '!x[$$0]++' - > /mnt/samba/petalinux/zcu102/work/dma/modules.order
