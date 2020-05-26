.globl GetHash
.globl CmpStr

CmpStr:
    mov %rdi, %rax
    mov %rsi, %rdx

    sub %rax, %rdx
    sub $16, %rax
    cmp_loop:
        add $16, %rax
        movdqu	(%rax), %xmm0
        pcmpistri $24, (%rax, %rdx), %xmm0

        ja cmp_loop

    jc exit
    xor	%rax, %rax
    exit:
ret

GetHash:
    movq 8(%rdi), %rcx
    shr $2, %rcx

    mov (%rdi), %rdx

    xor	%rax, %rax

    hash_loop:
         crc32q (%rdx, %rcx, 4), %rax
         loop hash_loop

    crc32q (%rdx), %rax

    and $524287, %rax
retq