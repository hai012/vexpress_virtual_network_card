.section .text

.global get_ttbr0_el1
get_ttbr0_el1:
	mrs x0, ttbr0_el1
	ret


.global get_ttbr1_el1
get_ttbr1_el1:
	mrs x0, ttbr1_el1
	ret
