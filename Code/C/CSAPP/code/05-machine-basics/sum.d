
sum:     file format elf64-x86-64


Disassembly of section .init:

0000000000400428 <_init>:
  400428:	48 83 ec 08          	sub    $0x8,%rsp
  40042c:	e8 7b 00 00 00       	callq  4004ac <call_gmon_start>
  400431:	48 83 c4 08          	add    $0x8,%rsp
  400435:	c3                   	retq   

Disassembly of section .plt:

0000000000400440 <__libc_start_main@plt-0x10>:
  400440:	ff 35 aa 0b 20 00    	pushq  0x200baa(%rip)        # 600ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
  400446:	ff 25 ac 0b 20 00    	jmpq   *0x200bac(%rip)        # 600ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
  40044c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400450 <__libc_start_main@plt>:
  400450:	ff 25 aa 0b 20 00    	jmpq   *0x200baa(%rip)        # 601000 <_GLOBAL_OFFSET_TABLE_+0x18>
  400456:	68 00 00 00 00       	pushq  $0x0
  40045b:	e9 e0 ff ff ff       	jmpq   400440 <_init+0x18>

0000000000400460 <strtol@plt>:
  400460:	ff 25 a2 0b 20 00    	jmpq   *0x200ba2(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x20>
  400466:	68 01 00 00 00       	pushq  $0x1
  40046b:	e9 d0 ff ff ff       	jmpq   400440 <_init+0x18>

0000000000400470 <__printf_chk@plt>:
  400470:	ff 25 9a 0b 20 00    	jmpq   *0x200b9a(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x28>
  400476:	68 02 00 00 00       	pushq  $0x2
  40047b:	e9 c0 ff ff ff       	jmpq   400440 <_init+0x18>

Disassembly of section .text:

0000000000400480 <_start>:
  400480:	31 ed                	xor    %ebp,%ebp
  400482:	49 89 d1             	mov    %rdx,%r9
  400485:	5e                   	pop    %rsi
  400486:	48 89 e2             	mov    %rsp,%rdx
  400489:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  40048d:	50                   	push   %rax
  40048e:	54                   	push   %rsp
  40048f:	49 c7 c0 b0 06 40 00 	mov    $0x4006b0,%r8
  400496:	48 c7 c1 20 06 40 00 	mov    $0x400620,%rcx
  40049d:	48 c7 c7 a3 05 40 00 	mov    $0x4005a3,%rdi
  4004a4:	e8 a7 ff ff ff       	callq  400450 <__libc_start_main@plt>
  4004a9:	f4                   	hlt    
  4004aa:	90                   	nop
  4004ab:	90                   	nop

00000000004004ac <call_gmon_start>:
  4004ac:	48 83 ec 08          	sub    $0x8,%rsp
  4004b0:	48 8b 05 29 0b 20 00 	mov    0x200b29(%rip),%rax        # 600fe0 <_DYNAMIC+0x1d0>
  4004b7:	48 85 c0             	test   %rax,%rax
  4004ba:	74 02                	je     4004be <call_gmon_start+0x12>
  4004bc:	ff d0                	callq  *%rax
  4004be:	48 83 c4 08          	add    $0x8,%rsp
  4004c2:	c3                   	retq   
  4004c3:	90                   	nop
  4004c4:	90                   	nop
  4004c5:	90                   	nop
  4004c6:	90                   	nop
  4004c7:	90                   	nop
  4004c8:	90                   	nop
  4004c9:	90                   	nop
  4004ca:	90                   	nop
  4004cb:	90                   	nop
  4004cc:	90                   	nop
  4004cd:	90                   	nop
  4004ce:	90                   	nop
  4004cf:	90                   	nop

00000000004004d0 <deregister_tm_clones>:
  4004d0:	b8 2f 10 60 00       	mov    $0x60102f,%eax
  4004d5:	55                   	push   %rbp
  4004d6:	48 2d 28 10 60 00    	sub    $0x601028,%rax
  4004dc:	48 83 f8 0e          	cmp    $0xe,%rax
  4004e0:	48 89 e5             	mov    %rsp,%rbp
  4004e3:	77 02                	ja     4004e7 <deregister_tm_clones+0x17>
  4004e5:	5d                   	pop    %rbp
  4004e6:	c3                   	retq   
  4004e7:	b8 00 00 00 00       	mov    $0x0,%eax
  4004ec:	48 85 c0             	test   %rax,%rax
  4004ef:	74 f4                	je     4004e5 <deregister_tm_clones+0x15>
  4004f1:	5d                   	pop    %rbp
  4004f2:	bf 28 10 60 00       	mov    $0x601028,%edi
  4004f7:	ff e0                	jmpq   *%rax
  4004f9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400500 <register_tm_clones>:
  400500:	b8 28 10 60 00       	mov    $0x601028,%eax
  400505:	55                   	push   %rbp
  400506:	48 2d 28 10 60 00    	sub    $0x601028,%rax
  40050c:	48 c1 f8 03          	sar    $0x3,%rax
  400510:	48 89 e5             	mov    %rsp,%rbp
  400513:	48 89 c2             	mov    %rax,%rdx
  400516:	48 c1 ea 3f          	shr    $0x3f,%rdx
  40051a:	48 01 d0             	add    %rdx,%rax
  40051d:	48 d1 f8             	sar    %rax
  400520:	75 02                	jne    400524 <register_tm_clones+0x24>
  400522:	5d                   	pop    %rbp
  400523:	c3                   	retq   
  400524:	ba 00 00 00 00       	mov    $0x0,%edx
  400529:	48 85 d2             	test   %rdx,%rdx
  40052c:	74 f4                	je     400522 <register_tm_clones+0x22>
  40052e:	5d                   	pop    %rbp
  40052f:	48 89 c6             	mov    %rax,%rsi
  400532:	bf 28 10 60 00       	mov    $0x601028,%edi
  400537:	ff e2                	jmpq   *%rdx
  400539:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400540 <__do_global_dtors_aux>:
  400540:	80 3d e1 0a 20 00 00 	cmpb   $0x0,0x200ae1(%rip)        # 601028 <__bss_start>
  400547:	75 11                	jne    40055a <__do_global_dtors_aux+0x1a>
  400549:	55                   	push   %rbp
  40054a:	48 89 e5             	mov    %rsp,%rbp
  40054d:	e8 7e ff ff ff       	callq  4004d0 <deregister_tm_clones>
  400552:	5d                   	pop    %rbp
  400553:	c6 05 ce 0a 20 00 01 	movb   $0x1,0x200ace(%rip)        # 601028 <__bss_start>
  40055a:	f3 c3                	repz retq 
  40055c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400560 <frame_dummy>:
  400560:	48 83 3d a0 08 20 00 	cmpq   $0x0,0x2008a0(%rip)        # 600e08 <__JCR_END__>
  400567:	00 
  400568:	74 1e                	je     400588 <frame_dummy+0x28>
  40056a:	b8 00 00 00 00       	mov    $0x0,%eax
  40056f:	48 85 c0             	test   %rax,%rax
  400572:	74 14                	je     400588 <frame_dummy+0x28>
  400574:	55                   	push   %rbp
  400575:	bf 08 0e 60 00       	mov    $0x600e08,%edi
  40057a:	48 89 e5             	mov    %rsp,%rbp
  40057d:	ff d0                	callq  *%rax
  40057f:	5d                   	pop    %rbp
  400580:	e9 7b ff ff ff       	jmpq   400500 <register_tm_clones>
  400585:	0f 1f 00             	nopl   (%rax)
  400588:	e9 73 ff ff ff       	jmpq   400500 <register_tm_clones>
  40058d:	90                   	nop
  40058e:	90                   	nop
  40058f:	90                   	nop

0000000000400590 <plus>:
  400590:	48 8d 04 37          	lea    (%rdi,%rsi,1),%rax
  400594:	c3                   	retq   

0000000000400595 <sumstore>:
  400595:	53                   	push   %rbx
  400596:	48 89 d3             	mov    %rdx,%rbx
  400599:	e8 f2 ff ff ff       	callq  400590 <plus>
  40059e:	48 89 03             	mov    %rax,(%rbx)
  4005a1:	5b                   	pop    %rbx
  4005a2:	c3                   	retq   

00000000004005a3 <main>:
  4005a3:	55                   	push   %rbp
  4005a4:	53                   	push   %rbx
  4005a5:	48 83 ec 18          	sub    $0x18,%rsp
  4005a9:	48 89 f5             	mov    %rsi,%rbp
  4005ac:	48 8b 7e 08          	mov    0x8(%rsi),%rdi
  4005b0:	ba 0a 00 00 00       	mov    $0xa,%edx
  4005b5:	be 00 00 00 00       	mov    $0x0,%esi
  4005ba:	e8 a1 fe ff ff       	callq  400460 <strtol@plt>
  4005bf:	48 63 d8             	movslq %eax,%rbx
  4005c2:	48 8b 7d 10          	mov    0x10(%rbp),%rdi
  4005c6:	ba 0a 00 00 00       	mov    $0xa,%edx
  4005cb:	be 00 00 00 00       	mov    $0x0,%esi
  4005d0:	e8 8b fe ff ff       	callq  400460 <strtol@plt>
  4005d5:	48 63 e8             	movslq %eax,%rbp
  4005d8:	48 8d 54 24 08       	lea    0x8(%rsp),%rdx
  4005dd:	48 89 ee             	mov    %rbp,%rsi
  4005e0:	48 89 df             	mov    %rbx,%rdi
  4005e3:	e8 ad ff ff ff       	callq  400595 <sumstore>
  4005e8:	4c 8b 44 24 08       	mov    0x8(%rsp),%r8
  4005ed:	48 89 e9             	mov    %rbp,%rcx
  4005f0:	48 89 da             	mov    %rbx,%rdx
  4005f3:	be c4 06 40 00       	mov    $0x4006c4,%esi
  4005f8:	bf 01 00 00 00       	mov    $0x1,%edi
  4005fd:	b8 00 00 00 00       	mov    $0x0,%eax
  400602:	e8 69 fe ff ff       	callq  400470 <__printf_chk@plt>
  400607:	b8 00 00 00 00       	mov    $0x0,%eax
  40060c:	48 83 c4 18          	add    $0x18,%rsp
  400610:	5b                   	pop    %rbx
  400611:	5d                   	pop    %rbp
  400612:	c3                   	retq   
  400613:	90                   	nop
  400614:	90                   	nop
  400615:	90                   	nop
  400616:	90                   	nop
  400617:	90                   	nop
  400618:	90                   	nop
  400619:	90                   	nop
  40061a:	90                   	nop
  40061b:	90                   	nop
  40061c:	90                   	nop
  40061d:	90                   	nop
  40061e:	90                   	nop
  40061f:	90                   	nop

0000000000400620 <__libc_csu_init>:
  400620:	48 89 6c 24 d8       	mov    %rbp,-0x28(%rsp)
  400625:	4c 89 64 24 e0       	mov    %r12,-0x20(%rsp)
  40062a:	48 8d 2d cf 07 20 00 	lea    0x2007cf(%rip),%rbp        # 600e00 <__init_array_end>
  400631:	4c 8d 25 c0 07 20 00 	lea    0x2007c0(%rip),%r12        # 600df8 <__frame_dummy_init_array_entry>
  400638:	4c 89 6c 24 e8       	mov    %r13,-0x18(%rsp)
  40063d:	4c 89 74 24 f0       	mov    %r14,-0x10(%rsp)
  400642:	4c 89 7c 24 f8       	mov    %r15,-0x8(%rsp)
  400647:	48 89 5c 24 d0       	mov    %rbx,-0x30(%rsp)
  40064c:	48 83 ec 38          	sub    $0x38,%rsp
  400650:	4c 29 e5             	sub    %r12,%rbp
  400653:	41 89 fd             	mov    %edi,%r13d
  400656:	49 89 f6             	mov    %rsi,%r14
  400659:	48 c1 fd 03          	sar    $0x3,%rbp
  40065d:	49 89 d7             	mov    %rdx,%r15
  400660:	e8 c3 fd ff ff       	callq  400428 <_init>
  400665:	48 85 ed             	test   %rbp,%rbp
  400668:	74 1c                	je     400686 <__libc_csu_init+0x66>
  40066a:	31 db                	xor    %ebx,%ebx
  40066c:	0f 1f 40 00          	nopl   0x0(%rax)
  400670:	4c 89 fa             	mov    %r15,%rdx
  400673:	4c 89 f6             	mov    %r14,%rsi
  400676:	44 89 ef             	mov    %r13d,%edi
  400679:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40067d:	48 83 c3 01          	add    $0x1,%rbx
  400681:	48 39 eb             	cmp    %rbp,%rbx
  400684:	75 ea                	jne    400670 <__libc_csu_init+0x50>
  400686:	48 8b 5c 24 08       	mov    0x8(%rsp),%rbx
  40068b:	48 8b 6c 24 10       	mov    0x10(%rsp),%rbp
  400690:	4c 8b 64 24 18       	mov    0x18(%rsp),%r12
  400695:	4c 8b 6c 24 20       	mov    0x20(%rsp),%r13
  40069a:	4c 8b 74 24 28       	mov    0x28(%rsp),%r14
  40069f:	4c 8b 7c 24 30       	mov    0x30(%rsp),%r15
  4006a4:	48 83 c4 38          	add    $0x38,%rsp
  4006a8:	c3                   	retq   
  4006a9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000004006b0 <__libc_csu_fini>:
  4006b0:	f3 c3                	repz retq 
  4006b2:	90                   	nop
  4006b3:	90                   	nop

Disassembly of section .fini:

00000000004006b4 <_fini>:
  4006b4:	48 83 ec 08          	sub    $0x8,%rsp
  4006b8:	48 83 c4 08          	add    $0x8,%rsp
  4006bc:	c3                   	retq   
