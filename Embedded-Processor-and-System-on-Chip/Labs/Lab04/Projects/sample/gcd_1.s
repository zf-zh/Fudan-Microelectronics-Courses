
# int gcd_1(int a, int b)
gcd_1:	
start:	addi	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	addi	s0,sp,32
	mv	a5,a0
	mv	a4,a1
	sw	a5,-20(s0)
	mv	a5,a4
	sw	a5,-24(s0)

# if(a==0) return b;
part1:	lw	a5,-20(s0)
	sext.w	a5,a5
	bnez	a5,part2
	lw	a5,-24(s0)
	j	end

# else if(b==0) return a;
part2:	lw	a5,-24(s0)
	sext.w	a5,a5
  	bnez	a5,part3
	lw	a5,-20(s0)
	j	end

# else if(a>b) return gcd_1(a%b,b);
part3:	lw	a4,-20(s0)
	lw	a5,-24(s0)
	sext.w	a4,a4
  	sext.w	a5,a5
	bge	a5,a4,part4
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	remw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,-24(s0)
	mv	a1,a4
	mv	a0,a5
 	jal	ra,gcd_1
	mv	a5,a0
 	j	end

# else return gcd_1(b%a,a);
part4:	lw	a4,-24(s0)
	lw	a5,-20(s0)
	remw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,-20(s0)
	mv	a1,a4
	mv	a0,a5
	jal	ra,gcd_1
	mv	a5,a0

end:	mv	a0,a5
	ld	ra,24(sp)
  	ld	s0,16(sp)
	addi	sp,sp,32
	ret

