
client_dynamic:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__@Base>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	ret    

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 72 2f 00 00    	push   0x2f72(%rip)        # 3f98 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 73 2f 00 00 	bnd jmp *0x2f73(%rip)        # 3fa0 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nopl   (%rax)
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	push   $0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    103f:	90                   	nop
    1040:	f3 0f 1e fa          	endbr64 
    1044:	68 01 00 00 00       	push   $0x1
    1049:	f2 e9 d1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    104f:	90                   	nop
    1050:	f3 0f 1e fa          	endbr64 
    1054:	68 02 00 00 00       	push   $0x2
    1059:	f2 e9 c1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    105f:	90                   	nop
    1060:	f3 0f 1e fa          	endbr64 
    1064:	68 03 00 00 00       	push   $0x3
    1069:	f2 e9 b1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    106f:	90                   	nop
    1070:	f3 0f 1e fa          	endbr64 
    1074:	68 04 00 00 00       	push   $0x4
    1079:	f2 e9 a1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    107f:	90                   	nop
    1080:	f3 0f 1e fa          	endbr64 
    1084:	68 05 00 00 00       	push   $0x5
    1089:	f2 e9 91 ff ff ff    	bnd jmp 1020 <_init+0x20>
    108f:	90                   	nop

Disassembly of section .plt.got:

0000000000001090 <__cxa_finalize@plt>:
    1090:	f3 0f 1e fa          	endbr64 
    1094:	f2 ff 25 5d 2f 00 00 	bnd jmp *0x2f5d(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    109b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

00000000000010a0 <puts@plt>:
    10a0:	f3 0f 1e fa          	endbr64 
    10a4:	f2 ff 25 fd 2e 00 00 	bnd jmp *0x2efd(%rip)        # 3fa8 <puts@GLIBC_2.2.5>
    10ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010b0 <__stack_chk_fail@plt>:
    10b0:	f3 0f 1e fa          	endbr64 
    10b4:	f2 ff 25 f5 2e 00 00 	bnd jmp *0x2ef5(%rip)        # 3fb0 <__stack_chk_fail@GLIBC_2.4>
    10bb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010c0 <printf@plt>:
    10c0:	f3 0f 1e fa          	endbr64 
    10c4:	f2 ff 25 ed 2e 00 00 	bnd jmp *0x2eed(%rip)        # 3fb8 <printf@GLIBC_2.2.5>
    10cb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010d0 <dlopen@plt>:
    10d0:	f3 0f 1e fa          	endbr64 
    10d4:	f2 ff 25 e5 2e 00 00 	bnd jmp *0x2ee5(%rip)        # 3fc0 <dlopen@GLIBC_2.34>
    10db:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010e0 <dlsym@plt>:
    10e0:	f3 0f 1e fa          	endbr64 
    10e4:	f2 ff 25 dd 2e 00 00 	bnd jmp *0x2edd(%rip)        # 3fc8 <dlsym@GLIBC_2.34>
    10eb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010f0 <dlclose@plt>:
    10f0:	f3 0f 1e fa          	endbr64 
    10f4:	f2 ff 25 d5 2e 00 00 	bnd jmp *0x2ed5(%rip)        # 3fd0 <dlclose@GLIBC_2.34>
    10fb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

0000000000001100 <_start>:
    1100:	f3 0f 1e fa          	endbr64 
    1104:	31 ed                	xor    %ebp,%ebp
    1106:	49 89 d1             	mov    %rdx,%r9
    1109:	5e                   	pop    %rsi
    110a:	48 89 e2             	mov    %rsp,%rdx
    110d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    1111:	50                   	push   %rax
    1112:	54                   	push   %rsp
    1113:	45 31 c0             	xor    %r8d,%r8d
    1116:	31 c9                	xor    %ecx,%ecx
    1118:	48 8d 3d 8a 01 00 00 	lea    0x18a(%rip),%rdi        # 12a9 <main>
    111f:	ff 15 b3 2e 00 00    	call   *0x2eb3(%rip)        # 3fd8 <__libc_start_main@GLIBC_2.34>
    1125:	f4                   	hlt    
    1126:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    112d:	00 00 00 

0000000000001130 <deregister_tm_clones>:
    1130:	48 8d 3d d9 2e 00 00 	lea    0x2ed9(%rip),%rdi        # 4010 <__TMC_END__>
    1137:	48 8d 05 d2 2e 00 00 	lea    0x2ed2(%rip),%rax        # 4010 <__TMC_END__>
    113e:	48 39 f8             	cmp    %rdi,%rax
    1141:	74 15                	je     1158 <deregister_tm_clones+0x28>
    1143:	48 8b 05 96 2e 00 00 	mov    0x2e96(%rip),%rax        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
    114a:	48 85 c0             	test   %rax,%rax
    114d:	74 09                	je     1158 <deregister_tm_clones+0x28>
    114f:	ff e0                	jmp    *%rax
    1151:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1158:	c3                   	ret    
    1159:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001160 <register_tm_clones>:
    1160:	48 8d 3d a9 2e 00 00 	lea    0x2ea9(%rip),%rdi        # 4010 <__TMC_END__>
    1167:	48 8d 35 a2 2e 00 00 	lea    0x2ea2(%rip),%rsi        # 4010 <__TMC_END__>
    116e:	48 29 fe             	sub    %rdi,%rsi
    1171:	48 89 f0             	mov    %rsi,%rax
    1174:	48 c1 ee 3f          	shr    $0x3f,%rsi
    1178:	48 c1 f8 03          	sar    $0x3,%rax
    117c:	48 01 c6             	add    %rax,%rsi
    117f:	48 d1 fe             	sar    %rsi
    1182:	74 14                	je     1198 <register_tm_clones+0x38>
    1184:	48 8b 05 65 2e 00 00 	mov    0x2e65(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable@Base>
    118b:	48 85 c0             	test   %rax,%rax
    118e:	74 08                	je     1198 <register_tm_clones+0x38>
    1190:	ff e0                	jmp    *%rax
    1192:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1198:	c3                   	ret    
    1199:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000011a0 <__do_global_dtors_aux>:
    11a0:	f3 0f 1e fa          	endbr64 
    11a4:	80 3d 65 2e 00 00 00 	cmpb   $0x0,0x2e65(%rip)        # 4010 <__TMC_END__>
    11ab:	75 2b                	jne    11d8 <__do_global_dtors_aux+0x38>
    11ad:	55                   	push   %rbp
    11ae:	48 83 3d 42 2e 00 00 	cmpq   $0x0,0x2e42(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    11b5:	00 
    11b6:	48 89 e5             	mov    %rsp,%rbp
    11b9:	74 0c                	je     11c7 <__do_global_dtors_aux+0x27>
    11bb:	48 8b 3d 46 2e 00 00 	mov    0x2e46(%rip),%rdi        # 4008 <__dso_handle>
    11c2:	e8 c9 fe ff ff       	call   1090 <__cxa_finalize@plt>
    11c7:	e8 64 ff ff ff       	call   1130 <deregister_tm_clones>
    11cc:	c6 05 3d 2e 00 00 01 	movb   $0x1,0x2e3d(%rip)        # 4010 <__TMC_END__>
    11d3:	5d                   	pop    %rbp
    11d4:	c3                   	ret    
    11d5:	0f 1f 00             	nopl   (%rax)
    11d8:	c3                   	ret    
    11d9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000011e0 <frame_dummy>:
    11e0:	f3 0f 1e fa          	endbr64 
    11e4:	e9 77 ff ff ff       	jmp    1160 <register_tm_clones>

00000000000011e9 <testNumbers>:
    11e9:	f3 0f 1e fa          	endbr64 
    11ed:	55                   	push   %rbp
    11ee:	48 89 e5             	mov    %rsp,%rbp
    11f1:	48 83 ec 30          	sub    $0x30,%rsp
    11f5:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    11f9:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
    11fd:	89 55 dc             	mov    %edx,-0x24(%rbp)
    1200:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%rbp)
    1207:	e9 8d 00 00 00       	jmp    1299 <testNumbers+0xb0>
    120c:	8b 45 f8             	mov    -0x8(%rbp),%eax
    120f:	48 98                	cltq   
    1211:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
    1218:	00 
    1219:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    121d:	48 01 d0             	add    %rdx,%rax
    1220:	8b 00                	mov    (%rax),%eax
    1222:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
    1226:	be e8 03 00 00       	mov    $0x3e8,%esi
    122b:	89 c7                	mov    %eax,%edi
    122d:	ff d2                	call   *%rdx
    122f:	89 45 fc             	mov    %eax,-0x4(%rbp)
    1232:	83 7d fc ff          	cmpl   $0xffffffff,-0x4(%rbp)
    1236:	74 31                	je     1269 <testNumbers+0x80>
    1238:	8b 45 f8             	mov    -0x8(%rbp),%eax
    123b:	48 98                	cltq   
    123d:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
    1244:	00 
    1245:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    1249:	48 01 d0             	add    %rdx,%rax
    124c:	8b 00                	mov    (%rax),%eax
    124e:	8b 55 fc             	mov    -0x4(%rbp),%edx
    1251:	89 c6                	mov    %eax,%esi
    1253:	48 8d 05 ae 0d 00 00 	lea    0xdae(%rip),%rax        # 2008 <_IO_stdin_used+0x8>
    125a:	48 89 c7             	mov    %rax,%rdi
    125d:	b8 00 00 00 00       	mov    $0x0,%eax
    1262:	e8 59 fe ff ff       	call   10c0 <printf@plt>
    1267:	eb 2c                	jmp    1295 <testNumbers+0xac>
    1269:	8b 45 f8             	mov    -0x8(%rbp),%eax
    126c:	48 98                	cltq   
    126e:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
    1275:	00 
    1276:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    127a:	48 01 d0             	add    %rdx,%rax
    127d:	8b 00                	mov    (%rax),%eax
    127f:	89 c6                	mov    %eax,%esi
    1281:	48 8d 05 b0 0d 00 00 	lea    0xdb0(%rip),%rax        # 2038 <_IO_stdin_used+0x38>
    1288:	48 89 c7             	mov    %rax,%rdi
    128b:	b8 00 00 00 00       	mov    $0x0,%eax
    1290:	e8 2b fe ff ff       	call   10c0 <printf@plt>
    1295:	83 45 f8 01          	addl   $0x1,-0x8(%rbp)
    1299:	8b 45 f8             	mov    -0x8(%rbp),%eax
    129c:	3b 45 dc             	cmp    -0x24(%rbp),%eax
    129f:	0f 8c 67 ff ff ff    	jl     120c <testNumbers+0x23>
    12a5:	90                   	nop
    12a6:	90                   	nop
    12a7:	c9                   	leave  
    12a8:	c3                   	ret    

00000000000012a9 <main>:
    12a9:	f3 0f 1e fa          	endbr64 
    12ad:	55                   	push   %rbp
    12ae:	48 89 e5             	mov    %rsp,%rbp
    12b1:	48 83 ec 50          	sub    $0x50,%rsp
    12b5:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    12bc:	00 00 
    12be:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    12c2:	31 c0                	xor    %eax,%eax
    12c4:	c7 45 d0 14 00 00 00 	movl   $0x14,-0x30(%rbp)
    12cb:	c7 45 d4 0e 00 00 00 	movl   $0xe,-0x2c(%rbp)
    12d2:	c7 45 d8 1f 00 00 00 	movl   $0x1f,-0x28(%rbp)
    12d9:	c7 45 dc 0c 00 00 00 	movl   $0xc,-0x24(%rbp)
    12e0:	c7 45 e0 11 00 00 00 	movl   $0x11,-0x20(%rbp)
    12e7:	c7 45 e4 15 00 00 00 	movl   $0x15,-0x1c(%rbp)
    12ee:	c7 45 e8 1e 00 00 00 	movl   $0x1e,-0x18(%rbp)
    12f5:	c7 45 ec 01 00 00 00 	movl   $0x1,-0x14(%rbp)
    12fc:	c7 45 f0 19 00 00 00 	movl   $0x19,-0x10(%rbp)
    1303:	c7 45 f4 13 00 00 00 	movl   $0x13,-0xc(%rbp)
    130a:	c7 45 bc 0a 00 00 00 	movl   $0xa,-0x44(%rbp)
    1311:	be 01 00 00 00       	mov    $0x1,%esi
    1316:	48 8d 05 58 0d 00 00 	lea    0xd58(%rip),%rax        # 2075 <_IO_stdin_used+0x75>
    131d:	48 89 c7             	mov    %rax,%rdi
    1320:	e8 ab fd ff ff       	call   10d0 <dlopen@plt>
    1325:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
    1329:	48 83 7d c0 00       	cmpq   $0x0,-0x40(%rbp)
    132e:	75 16                	jne    1346 <main+0x9d>
    1330:	48 8d 05 51 0d 00 00 	lea    0xd51(%rip),%rax        # 2088 <_IO_stdin_used+0x88>
    1337:	48 89 c7             	mov    %rax,%rdi
    133a:	e8 61 fd ff ff       	call   10a0 <puts@plt>
    133f:	b8 01 00 00 00       	mov    $0x1,%eax
    1344:	eb 6a                	jmp    13b0 <main+0x107>
    1346:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
    134a:	48 8d 15 5a 0d 00 00 	lea    0xd5a(%rip),%rdx        # 20ab <_IO_stdin_used+0xab>
    1351:	48 89 d6             	mov    %rdx,%rsi
    1354:	48 89 c7             	mov    %rax,%rdi
    1357:	e8 84 fd ff ff       	call   10e0 <dlsym@plt>
    135c:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
    1360:	48 83 7d c8 00       	cmpq   $0x0,-0x38(%rbp)
    1365:	75 22                	jne    1389 <main+0xe0>
    1367:	48 8d 05 5a 0d 00 00 	lea    0xd5a(%rip),%rax        # 20c8 <_IO_stdin_used+0xc8>
    136e:	48 89 c7             	mov    %rax,%rdi
    1371:	e8 2a fd ff ff       	call   10a0 <puts@plt>
    1376:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
    137a:	48 89 c7             	mov    %rax,%rdi
    137d:	e8 6e fd ff ff       	call   10f0 <dlclose@plt>
    1382:	b8 01 00 00 00       	mov    $0x1,%eax
    1387:	eb 27                	jmp    13b0 <main+0x107>
    1389:	8b 55 bc             	mov    -0x44(%rbp),%edx
    138c:	48 8d 4d d0          	lea    -0x30(%rbp),%rcx
    1390:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    1394:	48 89 ce             	mov    %rcx,%rsi
    1397:	48 89 c7             	mov    %rax,%rdi
    139a:	e8 4a fe ff ff       	call   11e9 <testNumbers>
    139f:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
    13a3:	48 89 c7             	mov    %rax,%rdi
    13a6:	e8 45 fd ff ff       	call   10f0 <dlclose@plt>
    13ab:	b8 00 00 00 00       	mov    $0x0,%eax
    13b0:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
    13b4:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
    13bb:	00 00 
    13bd:	74 05                	je     13c4 <main+0x11b>
    13bf:	e8 ec fc ff ff       	call   10b0 <__stack_chk_fail@plt>
    13c4:	c9                   	leave  
    13c5:	c3                   	ret    

Disassembly of section .fini:

00000000000013c8 <_fini>:
    13c8:	f3 0f 1e fa          	endbr64 
    13cc:	48 83 ec 08          	sub    $0x8,%rsp
    13d0:	48 83 c4 08          	add    $0x8,%rsp
    13d4:	c3                   	ret    
