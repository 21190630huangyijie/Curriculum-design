#
#  head.s contains the 32-bit startup code.
#  Two L3 task multitasking. The code of tasks are in kernel area, 
#  just like the Linux. The kernel code is located at 0x10000. 
SCRN_SEL	= 0x18
TSS0_SEL	= 0x20
LDT0_SEL	= 0x28
TSS1_SEL	= 0X30
LDT1_SEL	= 0x38
TSS2_SEL = 0x40  # 任务状态段 2, 占 8 Byte
LDT2_SEL = 0x48  # 局部描述符表 2, 占 8 Byte
TSS3_SEL = 0x50  # 任务状态段 3, 占 8 Byte
LDT3_SEL = 0x58  # 局部描述符表 3, 占 8 Byte

#.code32
#.global startup_32
.text
startup_32:
    movl $0x10,%eax
    mov %ax,%ds
#  mov %ax,%es
    lss init_stack,%esp     # init_stack => ss:%esp

## setup base fields of descriptors.
    call setup_idt          # 建立 ldt 表
    call setup_gdt          # 建立 gdt 表
    movl $0x10,%eax         # reload all the segment registers 
    mov %ax,%ds             # after changing gdt. 
    mov %ax,%es
    mov %ax,%fs
    mov %ax,%gs             # 更改 gdt 表后重载所有段寄存器
    lss init_stack,%esp     # init_stack => ss:%esp

## setup up timer 8253 chip. 初始化 8253
    movb $0x36, %al         # 控制字 36H = 00 11 01 10 B
    movl $0x43, %edx        # 控制端口
    outb %al, %dx           # 通道 0, 16 位, 方式 3(方波), 二进制计数
    movl $11930, %eax       # timer frequency 100 HZ 
    movl $0x40, %edx        # 0 号端口
    outb %al, %dx           # 将计数数字写入 8253 (8253 是 16 位的)
    movb %ah, %al           # 老师所说的10Hz, 似乎是不能只用一个通道实现的
    outb %al, %dx           # 因为 119300 > 2^16-1

## setup timer & system call interrupt descriptors. 初始化时钟中断和系统中断
    movl $0x00080000, %eax          # cs = 0x0008
    movw $timer_interrupt, %ax      # %eax 中放时钟中断基址
    movw $0x8E00, %dx               # (?)
    movl $0x08, %ecx                # The PC default timer int. 时钟中断向量号为 08H
    lea idt(,%ecx,8), %esi          # 更改第 8 项中断(每个中断占 8 Byte)
    movl %eax,(%esi) 
    movl %edx,4(%esi)
    movw $system_interrupt, %ax     # 系统中断基址
    movw $0xef00, %dx               # 没有做模式切换, 状态没有从 11B 变为 00B (?)
    movl $0x80, %ecx                # 系统中断向量号为 80H
    lea idt(,%ecx,8), %esi          # 更改系统中断
    movl %eax,(%esi)
    movl %edx,4(%esi)
    movw $keyboard_interrupt, %ax   # 键盘中断基址
    movw $0x8e00, %dx               
    movl $0x09, %ecx                # 键盘中断向量号为 09H
    lea idt(,%ecx,8), %esi          # 更改键盘中断
    movl %eax,(%esi)
    movl %edx,4(%esi)

## unmask the timer interrupt.
##   movl $0x21, %edx
##   inb %dx, %al
##   andb $0xfe, %al
##   outb %al, %dx

## Move to user mode (task 0)  为启动任务 0 做准备
    pushfl                  # eflags 入栈
    andl $0xffffbfff, (%esp) # 置 flag, 中断位清零
    popfl
    movl $TSS0_SEL, %eax
    ltr %ax                 # 加载 TSS
    movl $LDT0_SEL, %eax
    lldt %ax                # 加载 LDT
    movl $0, current        # 准备启动 0
    sti                     # 开中断
    pushl $0x17             # 压 ss
    pushl $init_stack       # 压用户栈, init_stack 成为 task0 的用户栈
    pushfl                  # 压 eflag
    pushl $0x0f             # 压 cs, cs 末 2 位为 11B, 即进入 11 用户级(00 为内核级)
    pushl $task0            # 压 eip
    iret                    # 返回时自动弹出, 进入 task0, 因此 tss0 表内容得以初始化

/****************************************/
setup_gdt:
    lgdt lgdt_opcode        # 加载 GDT
    ret

setup_idt:
    lea ignore_int,%edx     # 哑中断基址 => %edx
    movl $0x00080000,%eax   # cs = 0x0008
    movw %dx,%ax            # selector = 0x0008 = cs
    movw $0x8E00,%dx        # interrupt gate - dpl=0, present
    lea idt,%edi            # 中断向量表基址 => %edi
    mov $256,%ecx           # 循环次数
rp_sidt:                    # %eax 中放了 cs:哑中断基址
    movl %eax,(%edi)        # 将哑中断门描述符存入表中
    movl %edx,4(%edi)
    addl $8,%edi
    dec %ecx
    jne rp_sidt             # 将 256 个中断全部置为哑中断
    lidt lidt_opcode        # 加载中断描述符表寄存器值
    ret

## -----------------------------------
write_char:
    push %gs                # 保存现场
    pushl %ebx
##   pushl %eax
    mov $SCRN_SEL, %ebx     # 显存的段选择子
    mov %bx, %gs            # 放入 %gs
    mov scr_loc, %bx        # %bx 中放光标位移(其实是偏移)
    shl $1, %ebx            # 左移, 写高字节(高字节表示 ASCII 码值)
    movb %al, %gs:(%ebx)    # 将 %al 的内容写到光标处
    shr $1, %ebx            # 右移恢复
    incl %ebx               # 指针后移
    cmpl $2000, %ebx        # 与 2000 相比
    jb 2f                   # 如果 ebx < 2000, 则跳转到 2f
    call roll_screen
    movl $1920, %ebx        # 最下面一行的行首
2:  movl %ebx, scr_loc      # 直接将 ebx 赋值给 scr_loc, 返回
##   popl %eax
    popl %ebx               # 恢复现场
    pop %gs
    ret

.align 2
roll_screen:
    # ebx >= 2000 时, 将屏幕上的字符向上滚动
    push %ds
    mov $SCRN_SEL, %ebx     # 获取显存段地址(0xb8000)
    mov %bx, %ds
    mov %bx, %es
    movl $160, %ebx
    movl %ebx, %esi         # DS:esi (源地址)
    movl $0, %ebx
    movl %ebx, %edi         # ES:edi (目的地址)
    
    movl $1920, %ecx        # 循环次数
    cld                     # 清除增量位(向后移动, 即 si = si + 2, di = di + 2)
    rep 
    movsw                   # 使用 rep 指令前缀, 用 movw 搬动字符
    # 将最下面一行清空
    movl $80, %ecx
    pushl %eax
    movl $0x0700, %eax      # 背景色黑, 前景色白, 字符为 00H
    cld
    rep
    stosw                   # 将 ax 寄存器的内容送到 di 指向的单元中
    popl %eax
    pop %ds
    ret

/***********************************************/
/* This is the default interrupt "handler" :-) */
.align 2
ignore_int:                 # 哑中断
    push %ds                # 保护现场
    pushl %eax
    movl $0x10, %eax
    mov %ax, %ds            # 使用 gdt 表的第 2 项
    movl $67, %eax          # print 'C'
    call write_char         # 调用 write_char
    popl %eax               # 恢复现场
    pop %ds
    iret

/* Timer interrupt handler */ 
.align 2
timer_interrupt:        # 时钟中断 (TODO)
    push %ds
    pushl %eax          # 保护现场
    movl $0x10, %eax
    mov %ax, %ds        # 使用 gdt 表的第 2 项
    movb $0x20, %al     # 8259A
    outb %al, $0x20     # 恢复中断

    movl $0, %eax       # 将 key_en 与 false 比较
    cmpl %eax, key_en   # 若相等，则使用默认的轮流调度
    jne 5f              # 否则使得某个进程单独被调度（跳出时钟中断处理程序）

    movl $0, %eax
    cmpl %eax, current  # 判断当前进程是否为 0
    je 1f               # 为 0 则跳到 1 处, 切换为进程 1

    movl $1, %eax
    cmpl %eax, current  # 判断当前进程是否为 1
    je 2f               # 为 1 则跳到 2 处, 切换为进程 2

    movl $2, %eax
    cmpl %eax, current  # 判断当前进程是否为 2
    je 3f               # 为 2 则跳到 3 处, 切换为进程 3

    movl $3, %eax
    cmpl %eax, current  # 判断当前进程是否为 3
    je 4f               # 为 3 则跳到 4 处, 切换为进程 0

1:  
    movl $1, current    # 设置进程为 1
    ljmp $TSS1_SEL, $0  # 跳转到进程 1, 存下当前快照
    jmp 5f
2:  
    movl $2, current    # 设置进程为 2
    ljmp $TSS2_SEL, $0  # 跳转到进程 2, 存下当前快照
    jmp 5f
3:  
    movl $3, current    # 设置进程为 3
    ljmp $TSS3_SEL, $0  # 跳转到进程 3, 存下当前快照
    jmp 5f
4:  
    movl $0, current    # 设置进程为 0
    ljmp $TSS0_SEL, $0  # 跳转到进程 0, 存下当前快照
5:  
    popl %eax           # 恢复现场
    pop %ds
    iret

/* system call handler */
.align 2
system_interrupt:       # 系统中断
    push %ds            # 保护现场
    pushl %edx
    pushl %ecx
    pushl %ebx
    pushl %eax
    movl $0x10, %edx
    mov %dx, %ds        # 使用 gdt 表的第 2 项
    cli                 # 关中断
    call write_char     # 写字符
    sti                 # 开中断
    popl %eax           # 恢复现场
    popl %ebx
    popl %ecx
    popl %edx
    pop %ds
    iret

## 键盘中断
.align 2
keyboard_interrupt:
    pushl %edx          # 保护现场
    pushl %ecx
    pushl %ebx
    pushl %eax
    push %ds
    push %es

    movl $0x10, %eax    # 将 ds, es 设置为内核数据段
    mov %ax, %ds
    mov %ax, %es

    movb $0x20, %al     # 发出 8259 中断结束信号
    outb %al, $0x20

    xorb %al, %al       # 清除标志位
    inb $0x60, %al      # 读取端口
    cmpb $0x1e, %al     # 与 A 的键码比较
    je 1f
    cmpb $0x30, %al     # 与 B 的键码比较
    je 2f
    cmpb $0x20, %al     # 与 D 的键码比较
    je 3f
    cmpb $0x12, %al     # 与 E 的键码比较
    je 4f
    cmpb $0x2e, %al     # 与 C 的键码比较
    je 5f
    jmp 6f              # 这句非常迷惑，但相当关键，相当于 switch 中的 default
    # 作用是在默认情况下直接退出键盘中断处理程序，否则会默认继续执行下面的程序
1:
    call set_e0         # 切换到进程 0
    jmp 6f
2:
    call set_e1         # 切换到进程 1
    jmp 6f
3:
    call set_e2         # 切换到进程 2
    jmp 6f
4:
    call set_e3         # 切换到进程 3
    jmp 6f
5:  
    call set_cl         # 切换回分时调度
6:
    pop %es             # 恢复现场
    pop %ds
    popl %eax
    popl %ebx
    popl %ecx
    popl %edx
    iret

## 处理键盘按下后的程序
## 注意：当前的进程为 0 时，不能重新调度为进程 0
## 也就是说，不用 ljmp 指令来使得进程重新跳回自己

.align 8
set_e0:
    movl $1, key_en     # 强制进入键盘中断
    cmpl $0, current    # 判断当前进程是否为 0
    je 1f               # 若是，则无需进行进程调度
    movl $0, current    # 指定当前进程为 0
    ljmp $TSS0_SEL, $0  # 调度到进程 0
1:  ret

.align 8
set_e1:
    movl $1, key_en     # 强制进入键盘中断
    cmpl $1, current    # 判断当前进程是否为 1
    je 1f               # 若是，则无需进行进程调度
    movl $1, current    # 指定当前进程为 1
    ljmp $TSS1_SEL, $0  # 调度到进程 1
1:  ret

.align 8
set_e2:
    movl $1, key_en     # 强制进入键盘中断
    cmpl $2, current    # 判断当前进程是否为 2
    je 1f               # 若是，则无需进行进程调度
    movl $2, current    # 指定当前进程为 2
    ljmp $TSS2_SEL, $0  # 调度到进程 2
1:  ret

.align 8
set_e3:
    movl $1, key_en     # 强制进入键盘中断
    cmpl $3, current    # 判断当前进程是否为 3
    je 1f               # 若是，则无需进行进程调度
    movl $3, current    # 指定当前进程为 3
    ljmp $TSS3_SEL, $0  # 调度到进程 3
1:  ret

.align 8
set_cl:
    movl $0, key_en     # 强制退出键盘中断
    ret

/*********************************************/
current:.long 0         # 当前进程
scr_loc:.long 0         # 光标位置
key_en:.long 0          # 处于键盘中断对应的进程中

.align 2
lidt_opcode:
    .word 256*8-1       # idt contains 256 entries 256 个中断入口
    .long idt       # This will be rewrite by code. 
lgdt_opcode:
    .word (end_gdt-gdt)-1   # so does gdt 
    .long gdt       # This will be rewrite by code.

    .align 8
idt:    .fill 256,8,0       # idt is uninitialized 256 个中断

gdt:    .quad 0x0000000000000000    # NULL descriptor           # 第 0 号不用
    .quad 0x00c09a00000007ff        # 8Mb 0x08, base = 0x00000  # 第 1 号只读代码段
    .quad 0x00c09200000007ff        # 8Mb 0x10                  # 第 2 号可读可写数据段
    .quad 0x00c0920b80000002        # screen 0x18 - for display # 第 3 号为显存

    .word 0x0068, tss0, 0xe900, 0x0 # TSS0 descr 0x20
    .word 0x0040, ldt0, 0xe200, 0x0 # LDT0 descr 0x28
    .word 0x0068, tss1, 0xe900, 0x0 # TSS1 descr 0x30
    .word 0x0040, ldt1, 0xe200, 0x0 # LDT1 descr 0x38
    .word 0x0068, tss2, 0xe900, 0x0 # TSS2 descr 0x40
    .word 0x0040, ldt2, 0xe200, 0x0 # LDT2 descr 0x48
    .word 0x0068, tss3, 0xe900, 0x0 # TSS2 descr 0x50
    .word 0x0040, ldt3, 0xe200, 0x0 # LDT2 descr 0x58
end_gdt:
    .fill 128,4,0
init_stack:                         # Will be used as user stack for task0.
    .long init_stack
    .word 0x10

/*************************************/
.align 8
ldt0:   .quad 0x0000000000000000    # 0 号不用
    .quad 0x00c0fa00000003ff        # 0x0f, base = 0x00000, 1 号只读
    .quad 0x00c0f200000003ff        # 0x17                  2 号可读可写

tss0:   .long 0                 /* back link */
    .long krn_stk0, 0x10        /* esp0, ss0 */
    .long 0, 0, 0, 0, 0         /* esp1, ss1, esp2, ss2, cr3 */
    .long 0, 0, 0, 0, 0         /* eip, eflags, eax, ecx, edx */
    .long 0, 0, 0, 0, 0         /* ebx esp, ebp, esi, edi */
    .long 0, 0, 0, 0, 0, 0      /* es, cs, ss, ds, fs, gs */
    .long LDT0_SEL, 0x8000000   /* ldt 段选择符, trace bitmap */

    .fill 128,4,0
krn_stk0:
##   .long 0

/************************************/
.align 8
ldt1:   .quad 0x0000000000000000    # 0 号不用
    .quad 0x00c0fa00000003ff        # 0x0f, base = 0x00000, 1 号只读
    .quad 0x00c0f200000003ff        # 0x17                  2 号可读可写

tss1:   .long 0                         /* back link */
    .long krn_stk1, 0x10                /* esp0, ss0 */
    .long 0, 0, 0, 0, 0                 /* esp1, ss1, esp2, ss2, cr3 */
    .long task1, 0x200                  /* eip, eflags */
    .long 0, 0, 0, 0                    /* eax, ecx, edx, ebx */
    .long usr_stk1, 0, 0, 0             /* esp, ebp, esi, edi */
    .long 0x17,0x0f,0x17,0x17,0x17,0x17 /* es, cs, ss, ds, fs, gs */
    .long LDT1_SEL, 0x8000000           /* ldt 段选择符, trace bitmap */

    .fill 128,4,0
krn_stk1:

/************************************/
.align 8
ldt2:   .quad 0x0000000000000000    # 0 号不用
    .quad 0x00c0fa00000003ff        # 0x0f, base = 0x00000, 1 号只读
    .quad 0x00c0f200000003ff        # 0x17                  2 号可读可写

tss2:   .long 0                         /* back link */
    .long krn_stk2, 0x10                /* esp0, ss0 */
    .long 0, 0, 0, 0, 0                 /* esp1, ss1, esp2, ss2, cr3 */
    .long task2, 0x200                  /* eip, eflags */
    .long 0, 0, 0, 0                    /* eax, ecx, edx, ebx */
    .long usr_stk2, 0, 0, 0             /* esp, ebp, esi, edi */
    .long 0x17,0x0f,0x17,0x17,0x17,0x17 /* es, cs, ss, ds, fs, gs */
    .long LDT2_SEL, 0x8000000           /* ldt 段选择符, trace bitmap */

    .fill 128,4,0
krn_stk2:

/************************************/
.align 8
ldt3:   .quad 0x0000000000000000    # 0 号不用
    .quad 0x00c0fa00000003ff        # 0x0f, base = 0x00000, 1 号只读
    .quad 0x00c0f200000003ff        # 0x17                  2 号可读可写

tss3:   .long 0                         /* back link */
    .long krn_stk3, 0x10                /* esp0, ss0 */
    .long 0, 0, 0, 0, 0                 /* esp1, ss1, esp2, ss2, cr3 */
    .long task3, 0x200                  /* eip, eflags */
    .long 0, 0, 0, 0                    /* eax, ecx, edx, ebx */
    .long usr_stk3, 0, 0, 0             /* esp, ebp, esi, edi */
    .long 0x17,0x0f,0x17,0x17,0x17,0x17 /* es, cs, ss, ds, fs, gs */
    .long LDT3_SEL, 0x8000000           /* ldt 段选择符, trace bitmap */

    .fill 128,4,0
krn_stk3:

/************************************/
task0:
    movl $0x17, %eax
    movw %ax, %ds               # 使用 ldt 表的第 2 项
    mov $65, %al                # %al 中放入 A 的 ASCII 码
    int $0x80                   # 调用系统中断, 输出字符
    movl $0x7ffff, %ecx
1:  loop 1b                     # 延迟
    jmp task0 

task1:
    movl $0x17, %eax
    movw %ax, %ds               # 使用 ldt 表的第 2 项
    mov $66, %al                # %al 中放入 B 的 ASCII 码
    int $0x80                   # 调用系统中断, 输出字符
    movl $0x7ffff, %ecx
1:  loop 1b                     # 延迟
    jmp task1

task2:
    movl $0x17, %eax
    movw %ax, %ds               # 使用 ldt 表的第 2 项
    mov $68, %al                # %al 中放入 D 的 ASCII 码
    int $0x80                   # 调用系统中断, 输出字符
    movl $0x7ffff, %ecx
1:  loop 1b                     # 延迟
    jmp task2

task3:
    movl $0x17, %eax
    movw %ax, %ds               # 使用 ldt 表的第 2 项
    mov $69, %al                # %al 中放入 E 的 ASCII 码
    int $0x80                   # 调用系统中断, 输出字符
    movl $0x7ffff, %ecx
1:  loop 1b                     # 延迟
    jmp task3

    .fill 128,4,0 
usr_stk1:
    .fill 128,4,0 
usr_stk2:
    .fill 128,4,0 
usr_stk3:
