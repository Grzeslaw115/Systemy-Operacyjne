
client_shared:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d1 2f 00 00 	mov    0x2fd1(%rip),%rax        # 3fe0 <__gmon_start__@Base>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	ret    

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 8a 2f 00 00    	push   0x2f8a(%rip)        # 3fb0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 8b 2f 00 00 	bnd jmp *0x2f8b(%rip)        # 3fb8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nopl   (%rax)
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	push   $0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    103f:	90                   	nop
    1040:	f3 0f 1e fa          	endbr64 
    1044:	68 01 00 00 00       	push   $0x1
    1049:	f2 e9 d1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    104f:	90                   	nop

Disassembly of section .plt.got:

0000000000001050 <__cxa_finalize@plt>:
    1050:	f3 0f 1e fa          	endbr64 
    1054:	f2 ff 25 9d 2f 00 00 	bnd jmp *0x2f9d(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    105b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001060 <__stack_chk_fail@plt>:
    1060:	f3 0f 1e fa          	endbr64 
    1064:	f2 ff 25 55 2f 00 00 	bnd jmp *0x2f55(%rip)        # 3fc0 <__stack_chk_fail@GLIBC_2.4>
    106b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001070 <printf@plt>:
    1070:	f3 0f 1e fa          	endbr64 
    1074:	f2 ff 25 4d 2f 00 00 	bnd jmp *0x2f4d(%rip)        # 3fc8 <printf@GLIBC_2.2.5>
    107b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

0000000000001080 <_start>:
    1080:	f3 0f 1e fa          	endbr64 
    1084:	31 ed                	xor    %ebp,%ebp
    1086:	49 89 d1             	mov    %rdx,%r9
    1089:	5e                   	pop    %rsi
    108a:	48 89 e2             	mov    %rsp,%rdx
    108d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    1091:	50                   	push   %rax
    1092:	54                   	push   %rsp
    1093:	45 31 c0             	xor    %r8d,%r8d
    1096:	31 c9                	xor    %ecx,%ecx
    1098:	48 8d 3d 8a 01 00 00 	lea    0x18a(%rip),%rdi        # 1229 <main>
    109f:	ff 15 2b 2f 00 00    	call   *0x2f2b(%rip)        # 3fd0 <__libc_start_main@GLIBC_2.34>
    10a5:	f4                   	hlt    
    10a6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    10ad:	00 00 00 

00000000000010b0 <deregister_tm_clones>:
    10b0:	48 8d 3d 59 2f 00 00 	lea    0x2f59(%rip),%rdi        # 4010 <__TMC_END__>
    10b7:	48 8d 05 52 2f 00 00 	lea    0x2f52(%rip),%rax        # 4010 <__TMC_END__>
    10be:	48 39 f8             	cmp    %rdi,%rax
    10c1:	74 15                	je     10d8 <deregister_tm_clones+0x28>
    10c3:	48 8b 05 0e 2f 00 00 	mov    0x2f0e(%rip),%rax        # 3fd8 <_ITM_deregisterTMCloneTable@Base>
    10ca:	48 85 c0             	test   %rax,%rax
    10cd:	74 09                	je     10d8 <deregister_tm_clones+0x28>
    10cf:	ff e0                	jmp    *%rax
    10d1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    10d8:	c3                   	ret    
    10d9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000010e0 <register_tm_clones>:
    10e0:	48 8d 3d 29 2f 00 00 	lea    0x2f29(%rip),%rdi        # 4010 <__TMC_END__>
    10e7:	48 8d 35 22 2f 00 00 	lea    0x2f22(%rip),%rsi        # 4010 <__TMC_END__>
    10ee:	48 29 fe             	sub    %rdi,%rsi
    10f1:	48 89 f0             	mov    %rsi,%rax
    10f4:	48 c1 ee 3f          	shr    $0x3f,%rsi
    10f8:	48 c1 f8 03          	sar    $0x3,%rax
    10fc:	48 01 c6             	add    %rax,%rsi
    10ff:	48 d1 fe             	sar    %rsi
    1102:	74 14                	je     1118 <register_tm_clones+0x38>
    1104:	48 8b 05 e5 2e 00 00 	mov    0x2ee5(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable@Base>
    110b:	48 85 c0             	test   %rax,%rax
    110e:	74 08                	je     1118 <register_tm_clones+0x38>
    1110:	ff e0                	jmp    *%rax
    1112:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1118:	c3                   	ret    
    1119:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001120 <__do_global_dtors_aux>:
    1120:	f3 0f 1e fa          	endbr64 
    1124:	80 3d e5 2e 00 00 00 	cmpb   $0x0,0x2ee5(%rip)        # 4010 <__TMC_END__>
    112b:	75 2b                	jne    1158 <__do_global_dtors_aux+0x38>
    112d:	55                   	push   %rbp
    112e:	48 83 3d c2 2e 00 00 	cmpq   $0x0,0x2ec2(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1135:	00 
    1136:	48 89 e5             	mov    %rsp,%rbp
    1139:	74 0c                	je     1147 <__do_global_dtors_aux+0x27>
    113b:	48 8b 3d c6 2e 00 00 	mov    0x2ec6(%rip),%rdi        # 4008 <__dso_handle>
    1142:	e8 09 ff ff ff       	call   1050 <__cxa_finalize@plt>
    1147:	e8 64 ff ff ff       	call   10b0 <deregister_tm_clones>
    114c:	c6 05 bd 2e 00 00 01 	movb   $0x1,0x2ebd(%rip)        # 4010 <__TMC_END__>
    1153:	5d                   	pop    %rbp
    1154:	c3                   	ret    
    1155:	0f 1f 00             	nopl   (%rax)
    1158:	c3                   	ret    
    1159:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001160 <frame_dummy>:
    1160:	f3 0f 1e fa          	endbr64 
    1164:	e9 77 ff ff ff       	jmp    10e0 <register_tm_clones>

0000000000001169 <testNumbers>:
    1169:	f3 0f 1e fa          	endbr64 
    116d:	55                   	push   %rbp
    116e:	48 89 e5             	mov    %rsp,%rbp
    1171:	48 83 ec 30          	sub    $0x30,%rsp
    1175:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    1179:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
    117d:	89 55 dc             	mov    %edx,-0x24(%rbp)
    1180:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%rbp)
    1187:	e9 8d 00 00 00       	jmp    1219 <testNumbers+0xb0>
    118c:	8b 45 f8             	mov    -0x8(%rbp),%eax
    118f:	48 98                	cltq   
    1191:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
    1198:	00 
    1199:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    119d:	48 01 d0             	add    %rdx,%rax
    11a0:	8b 00                	mov    (%rax),%eax
    11a2:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
    11a6:	be e8 03 00 00       	mov    $0x3e8,%esi
    11ab:	89 c7                	mov    %eax,%edi
    11ad:	ff d2                	call   *%rdx
    11af:	89 45 fc             	mov    %eax,-0x4(%rbp)
    11b2:	83 7d fc ff          	cmpl   $0xffffffff,-0x4(%rbp)
    11b6:	74 31                	je     11e9 <testNumbers+0x80>
    11b8:	8b 45 f8             	mov    -0x8(%rbp),%eax
    11bb:	48 98                	cltq   
    11bd:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
    11c4:	00 
    11c5:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    11c9:	48 01 d0             	add    %rdx,%rax
    11cc:	8b 00                	mov    (%rax),%eax
    11ce:	8b 55 fc             	mov    -0x4(%rbp),%edx
    11d1:	89 c6                	mov    %eax,%esi
    11d3:	48 8d 05 2e 0e 00 00 	lea    0xe2e(%rip),%rax        # 2008 <_IO_stdin_used+0x8>
    11da:	48 89 c7             	mov    %rax,%rdi
    11dd:	b8 00 00 00 00       	mov    $0x0,%eax
    11e2:	e8 89 fe ff ff       	call   1070 <printf@plt>
    11e7:	eb 2c                	jmp    1215 <testNumbers+0xac>
    11e9:	8b 45 f8             	mov    -0x8(%rbp),%eax
    11ec:	48 98                	cltq   
    11ee:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
    11f5:	00 
    11f6:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    11fa:	48 01 d0             	add    %rdx,%rax
    11fd:	8b 00                	mov    (%rax),%eax
    11ff:	89 c6                	mov    %eax,%esi
    1201:	48 8d 05 30 0e 00 00 	lea    0xe30(%rip),%rax        # 2038 <_IO_stdin_used+0x38>
    1208:	48 89 c7             	mov    %rax,%rdi
    120b:	b8 00 00 00 00       	mov    $0x0,%eax
    1210:	e8 5b fe ff ff       	call   1070 <printf@plt>
    1215:	83 45 f8 01          	addl   $0x1,-0x8(%rbp)
    1219:	8b 45 f8             	mov    -0x8(%rbp),%eax
    121c:	3b 45 dc             	cmp    -0x24(%rbp),%eax
    121f:	0f 8c 67 ff ff ff    	jl     118c <testNumbers+0x23>
    1225:	90                   	nop
    1226:	90                   	nop
    1227:	c9                   	leave  
    1228:	c3                   	ret    

0000000000001229 <main>:
    1229:	f3 0f 1e fa          	endbr64 
    122d:	55                   	push   %rbp
    122e:	48 89 e5             	mov    %rsp,%rbp
    1231:	48 83 ec 40          	sub    $0x40,%rsp
    1235:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    123c:	00 00 
    123e:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    1242:	31 c0                	xor    %eax,%eax
    1244:	c7 45 d0 14 00 00 00 	movl   $0x14,-0x30(%rbp)
    124b:	c7 45 d4 0e 00 00 00 	movl   $0xe,-0x2c(%rbp)
    1252:	c7 45 d8 1f 00 00 00 	movl   $0x1f,-0x28(%rbp)
    1259:	c7 45 dc 0c 00 00 00 	movl   $0xc,-0x24(%rbp)
    1260:	c7 45 e0 11 00 00 00 	movl   $0x11,-0x20(%rbp)
    1267:	c7 45 e4 15 00 00 00 	movl   $0x15,-0x1c(%rbp)
    126e:	c7 45 e8 1e 00 00 00 	movl   $0x1e,-0x18(%rbp)
    1275:	c7 45 ec 01 00 00 00 	movl   $0x1,-0x14(%rbp)
    127c:	c7 45 f0 19 00 00 00 	movl   $0x19,-0x10(%rbp)
    1283:	c7 45 f4 13 00 00 00 	movl   $0x13,-0xc(%rbp)
    128a:	c7 45 cc 0a 00 00 00 	movl   $0xa,-0x34(%rbp)
    1291:	8b 55 cc             	mov    -0x34(%rbp),%edx
    1294:	48 8d 45 d0          	lea    -0x30(%rbp),%rax
    1298:	48 89 c6             	mov    %rax,%rsi
    129b:	48 8b 05 46 2d 00 00 	mov    0x2d46(%rip),%rax        # 3fe8 <test_collatz_convergence@Base>
    12a2:	48 89 c7             	mov    %rax,%rdi
    12a5:	e8 bf fe ff ff       	call   1169 <testNumbers>
    12aa:	b8 00 00 00 00       	mov    $0x0,%eax
    12af:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
    12b3:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
    12ba:	00 00 
    12bc:	74 05                	je     12c3 <main+0x9a>
    12be:	e8 9d fd ff ff       	call   1060 <__stack_chk_fail@plt>
    12c3:	c9                   	leave  
    12c4:	c3                   	ret    

Disassembly of section .fini:

00000000000012c8 <_fini>:
    12c8:	f3 0f 1e fa          	endbr64 
    12cc:	48 83 ec 08          	sub    $0x8,%rsp
    12d0:	48 83 c4 08          	add    $0x8,%rsp
    12d4:	c3                   	ret    
