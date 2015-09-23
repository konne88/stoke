  .text
  .globl wmemchr
  .type wmemchr, @function

#! file-offset 0x1841a0
#! rip-offset  0x1441a0
#! capacity    192 bytes

# Text                      #  Line  RIP       Bytes  Opcode              
.wmemchr:                   #        0x1441a0  0      OPC=<label>         
  movl $0x40, %eax          #  1     0x1441a0  5      OPC=movl_r32_imm32  
  xorl %ecx, %ecx           #  2     0x1441a5  2      OPC=xorl_r32_r32    
  testl %edx, %edx          #  3     0x1441a7  2      OPC=testl_r32_r32   
  je .L_1441e0              #  4     0x1441a9  2      OPC=je_label        
  movl %edi, %eax           #  5     0x1441ab  2      OPC=movl_r32_r32    
  cmpl %esi, (%r15,%rax,1)  #  6     0x1441ad  4      OPC=cmpl_m32_r32    
  jne .L_1441e0             #  7     0x1441b1  2      OPC=jne_label       
  nop                       #  8     0x1441b3  1      OPC=nop             
  nop                       #  9     0x1441b4  1      OPC=nop             
  nop                       #  10    0x1441b5  1      OPC=nop             
  nop                       #  11    0x1441b6  1      OPC=nop             
  nop                       #  12    0x1441b7  1      OPC=nop             
  nop                       #  13    0x1441b8  1      OPC=nop             
  nop                       #  14    0x1441b9  1      OPC=nop             
  nop                       #  15    0x1441ba  1      OPC=nop             
  jmpq .L_144240            #  16    0x1441bb  5      OPC=jmpq_label_1    
.L_1441c0:                  #        0x1441c0  0      OPC=<label>         
  addl $0x4, %eax           #  17    0x1441c0  6      OPC=addl_r32_imm32  
  cmpl %esi, (%r15,%rax,1)  #  18    0x1441c6  4      OPC=cmpl_m32_r32    
  je .L_144240              #  19    0x1441ca  2      OPC=je_label        
  nop                       #  20    0x1441cc  1      OPC=nop             
  nop                       #  21    0x1441cd  1      OPC=nop             
  nop                       #  22    0x1441ce  1      OPC=nop             
  nop                       #  23    0x1441cf  1      OPC=nop             
  nop                       #  24    0x1441d0  1      OPC=nop             
  nop                       #  25    0x1441d1  1      OPC=nop             
  nop                       #  26    0x1441d2  1      OPC=nop             
  nop                       #  27    0x1441d3  1      OPC=nop             
  nop                       #  28    0x1441d4  1      OPC=nop             
  nop                       #  29    0x1441d5  1      OPC=nop             
  nop                       #  30    0x1441d6  1      OPC=nop             
  nop                       #  31    0x1441d7  1      OPC=nop             
  nop                       #  32    0x1441d8  1      OPC=nop             
  nop                       #  33    0x1441d9  1      OPC=nop             
  nop                       #  34    0x1441da  1      OPC=nop             
  nop                       #  35    0x1441db  1      OPC=nop             
  nop                       #  36    0x1441dc  1      OPC=nop             
  nop                       #  37    0x1441dd  1      OPC=nop             
  nop                       #  38    0x1441de  1      OPC=nop             
  nop                       #  39    0x1441df  1      OPC=nop             
.L_1441e0:                  #        0x1441e0  0      OPC=<label>         
  addl $0x1, %ecx           #  40    0x1441e0  6      OPC=addl_r32_imm32  
  cmpl %ecx, %edx           #  41    0x1441e6  2      OPC=cmpl_r32_r32    
  ja .L_1441c0              #  42    0x1441e8  2      OPC=ja_label        
  nop                       #  43    0x1441ea  1      OPC=nop             
  nop                       #  44    0x1441eb  1      OPC=nop             
  nop                       #  45    0x1441ec  1      OPC=nop             
  nop                       #  46    0x1441ed  1      OPC=nop             
  nop                       #  47    0x1441ee  1      OPC=nop             
  nop                       #  48    0x1441ef  1      OPC=nop             
  nop                       #  49    0x1441f0  1      OPC=nop             
  nop                       #  50    0x1441f1  1      OPC=nop             
  nop                       #  51    0x1441f2  1      OPC=nop             
  nop                       #  52    0x1441f3  1      OPC=nop             
  nop                       #  53    0x1441f4  1      OPC=nop             
  nop                       #  54    0x1441f5  1      OPC=nop             
.wmemchr:                   #        0x1441f6  0      OPC=<label>         
  andl $0x0, %eax           #  55    0x1441f6  3      OPC=andl_r32_imm8   
  nop                       #  56    0x1441f9  1      OPC=nop             
  nop                       #  57    0x1441fa  1      OPC=nop             
  nop                       #  58    0x1441fb  1      OPC=nop             
  nop                       #  59    0x1441fc  1      OPC=nop             
  nop                       #  60    0x1441fd  1      OPC=nop             
  nop                       #  61    0x1441fe  1      OPC=nop             
  nop                       #  62    0x1441ff  1      OPC=nop             
  nop                       #  63    0x144200  1      OPC=nop             
  nop                       #  64    0x144201  1      OPC=nop             
  nop                       #  65    0x144202  1      OPC=nop             
  nop                       #  66    0x144203  1      OPC=nop             
  nop                       #  67    0x144204  1      OPC=nop             
  nop                       #  68    0x144205  1      OPC=nop             
  nop                       #  69    0x144206  1      OPC=nop             
  nop                       #  70    0x144207  1      OPC=nop             
  nop                       #  71    0x144208  1      OPC=nop             
  nop                       #  72    0x144209  1      OPC=nop             
  nop                       #  73    0x14420a  1      OPC=nop             
  nop                       #  74    0x14420b  1      OPC=nop             
  nop                       #  75    0x14420c  1      OPC=nop             
  nop                       #  76    0x14420d  1      OPC=nop             
  nop                       #  77    0x14420e  1      OPC=nop             
  nop                       #  78    0x14420f  1      OPC=nop             
  nop                       #  79    0x144210  1      OPC=nop             
  nop                       #  80    0x144211  1      OPC=nop             
  nop                       #  81    0x144212  1      OPC=nop             
  nop                       #  82    0x144213  1      OPC=nop             
  nop                       #  83    0x144214  1      OPC=nop             
  nop                       #  84    0x144215  1      OPC=nop             
  nop                       #  85    0x144216  1      OPC=nop             
  nop                       #  86    0x144217  1      OPC=nop             
  nop                       #  87    0x144218  1      OPC=nop             
  nop                       #  88    0x144219  1      OPC=nop             
  nop                       #  89    0x14421a  1      OPC=nop             
  nop                       #  90    0x14421b  1      OPC=nop             
  nop                       #  91    0x14421c  1      OPC=nop             
.wmemchr:                   #        0x14421d  0      OPC=<label>         
  nop                       #  92    0x14421d  1      OPC=nop             
  nop                       #  93    0x14421e  1      OPC=nop             
  nop                       #  94    0x14421f  1      OPC=nop             
  nop                       #  95    0x144220  1      OPC=nop             
  nop                       #  96    0x144221  1      OPC=nop             
  nop                       #  97    0x144222  1      OPC=nop             
  nop                       #  98    0x144223  1      OPC=nop             
  nop                       #  99    0x144224  1      OPC=nop             
  nop                       #  100   0x144225  1      OPC=nop             
  nop                       #  101   0x144226  1      OPC=nop             
  nop                       #  102   0x144227  1      OPC=nop             
  popq %r11                 #  103   0x144228  2      OPC=popq_r64_1      
  andl $0xe0, %r11d         #  104   0x14422a  4      OPC=andl_r32_imm8   
  addq %r15, %r11           #  105   0x14422e  3      OPC=addq_r64_r64    
  jmpq %r11                 #  106   0x144231  3      OPC=jmpq_r64        
  nop                       #  107   0x144234  1      OPC=nop             
  nop                       #  108   0x144235  1      OPC=nop             
  nop                       #  109   0x144236  1      OPC=nop             
  nop                       #  110   0x144237  1      OPC=nop             
  nop                       #  111   0x144238  1      OPC=nop             
  nop                       #  112   0x144239  1      OPC=nop             
  nop                       #  113   0x14423a  1      OPC=nop             
  nop                       #  114   0x14423b  1      OPC=nop             
  nop                       #  115   0x14423c  1      OPC=nop             
  nop                       #  116   0x14423d  1      OPC=nop             
  nop                       #  117   0x14423e  1      OPC=nop             
  nop                       #  118   0x14423f  1      OPC=nop             
.L_144240:                  #        0x144240  0      OPC=<label>         
  nop                       #  119   0x144240  1      OPC=nop             
  nop                       #  120   0x144241  1      OPC=nop             
  nop                       #  121   0x144242  1      OPC=nop             
  nop                       #  122   0x144243  1      OPC=nop             
  nop                       #  123   0x144244  1      OPC=nop             
  nop                       #  124   0x144245  1      OPC=nop             
  nop                       #  125   0x144246  1      OPC=nop             
  nop                       #  126   0x144247  1      OPC=nop             
  nop                       #  127   0x144248  1      OPC=nop             
  nop                       #  128   0x144249  1      OPC=nop             
  nop                       #  129   0x14424a  1      OPC=nop             
  nop                       #  130   0x14424b  1      OPC=nop             
  nop                       #  131   0x14424c  1      OPC=nop             
  nop                       #  132   0x14424d  1      OPC=nop             
  nop                       #  133   0x14424e  1      OPC=nop             
  nop                       #  134   0x14424f  1      OPC=nop             
  nop                       #  135   0x144250  1      OPC=nop             
  nop                       #  136   0x144251  1      OPC=nop             
  popq %r11                 #  137   0x144252  2      OPC=popq_r64_1      
  andl $0xe0, %r11d         #  138   0x144254  4      OPC=andl_r32_imm8   
  addq %r15, %r11           #  139   0x144258  3      OPC=addq_r64_r64    
  jmpq %r11                 #  140   0x14425b  3      OPC=jmpq_r64        
                                                                          
.size wmemchr, .-wmemchr
