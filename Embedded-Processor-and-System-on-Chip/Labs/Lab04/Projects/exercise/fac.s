	.text
	.globl	myfac
	.type	myfac,@function	
myfac:
	addi	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	addi	s0,sp,32
	
	# Your code here
	# Begin my code
	beqz	a0,myfac_base	# Base case
	mv	s0,a0		# Store a0 to s0

myfac_recur:
	addi	a0,a0,-1
	jal	ra,myfac
	mv	a1,s0
	jal	ra,mymul
	j	myfac_end

myfac_base:
	li	a0,1		# 0! = 1

myfac_end:
	# End my code

	ld	ra,24(sp)
	ld	s0,16(sp)
	addi	sp,sp,32
	ret

