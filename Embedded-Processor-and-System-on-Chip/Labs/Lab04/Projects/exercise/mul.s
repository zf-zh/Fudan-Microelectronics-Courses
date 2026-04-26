	.text
	.globl	mymul
	.type	mymul,@function
mymul:
	addi	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	addi	s0,sp,32

	# Your code here
	# Begin my code
	mv	a2,x0		# Initialize a2

mymul_loop:
	beqz	a1,mymul_end	# Finished if a1 is 0
	andi	t0,a1,1		# LSB of a1
	beqz	t0,mymul_skip	# Skip the addition if 0

mymul_add:
	addw	a2,a2,a0	# Add to the result

mymul_skip:
	slliw	a0,a0,1		# Multiply by 2
	srliw	a1,a1,1		# Next bit
	j	mymul_loop	# Jump back

mymul_end:
	mv	a0,a2		# Return value
	# End my code

	ld	ra,24(sp)
	ld	s0,16(sp)
	addi	sp,sp,32
	ret

