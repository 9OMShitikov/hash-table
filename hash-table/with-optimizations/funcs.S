.globl GetHash
GetHash:
    movq 8(%rdi), %rcx
    shr $2, %rcx

    mov (%rdi), %rdx

    movq $0, %rax

    hash_loop:
         crc32q (%rdx, %rcx, 4), %rax
         loop hash_loop

    crc32q (%rdx), %rax

    and $524287, %rax
retq