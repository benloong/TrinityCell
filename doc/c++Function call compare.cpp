void Func()
{
003049C0  push        ebp  
003049C1  mov         ebp,esp  
003049C3  sub         esp,0C0h  
003049C9  push        ebx  
003049CA  push        esi  
003049CB  push        edi  
003049CC  lea         edi,[ebp-0C0h]  
003049D2  mov         ecx,30h  
003049D7  mov         eax,0CCCCCCCCh  
003049DC  rep stos    dword ptr es:[edi]  
}
{
	Func();
00A17301  call        Func (0A11302h)  
}
////////////////////////////////////////////////////////////////
class Derived : public Base {
public:
	virtual void Func() {
00304A30  push        ebp  
00304A31  mov         ebp,esp  
00304A33  sub         esp,0CCh  
00304A39  push        ebx  
00304A3A  push        esi  
00304A3B  push        edi  
00304A3C  push        ecx  
00304A3D  lea         edi,[ebp-0CCh]  
00304A43  mov         ecx,33h  
00304A48  mov         eax,0CCCCCCCCh  
00304A4D  rep stos    dword ptr es:[edi]  
00304A4F  pop         ecx  
00304A50  mov         dword ptr [this],ecx  
	}
};
{
	pBase->Func();
00A1703E  mov         eax,dword ptr [pBase]  
00A17041  mov         edx,dword ptr [eax]  
00A17043  mov         esi,esp  
00A17045  mov         ecx,dword ptr [pBase]  
00A17048  mov         eax,dword ptr [edx]  
00A1704A  call        eax  
00A1704C  cmp         esi,esp  
00A1704E  call        __RTC_CheckEsp (0A1141Fh)  
}
//////////////////////////////////////////////////////////////////


 push        ebp  
 mov         ebp,esp  
 sub         esp,0CCh  
 push        ebx  
 push        esi  
 push        edi  
 push        ecx  
 lea         edi,[ebp-0CCh]  
 mov         ecx,33h  
 mov         eax,0CCCCCCCCh  
 rep stos    dword ptr es:[edi]  
 pop         ecx  
 mov         dword ptr [this],ecx  
 mov         eax,dword ptr [this]  
 cmp         dword ptr [eax+10h],0  
 jne         std::_Func_class<void,std::_Nil,std::_Nil,std::_Nil,std::_Nil,std::_Nil,std::_Nil,std::_Nil>::operator()+3Bh (030466Bh)  
 mov         esi,esp  

{
bindFunc();
00A17129  lea         ecx,[bindFunc]  
00A1712C  call        std::_Func_class<void,std::_Nil,std::_Nil,std::_Nil,std::_Nil,std::_Nil,std::_Nil,std::_Nil>::operator() (0A113BBh)  
}
////////////////////////////////////////////////////////////////////
 push        ebp  
 mov         ebp,esp  
 sub         esp,0CCh  
 push        ebx  
 push        esi  
 push        edi  
 push        ecx  
 lea         edi,[ebp-0CCh]  
 mov         ecx,33h  
 mov         eax,0CCCCCCCCh  
 rep stos    dword ptr es:[edi]  
 pop         ecx  
 mov         dword ptr [this],ecx  
{
lambdaFunc();
00A17215  lea         ecx,[lambdaFunc]  
00A17218  call        <lambda_4abcbc6e615c0df5bf5b7879b30c2c83>::operator() (0A145F0h)  
}


//release mode

	{
		pBase->Func();
00F81330  mov         edx,dword ptr [esi]  
00F81332  mov         ecx,esi  
00F81334  call        dword ptr [edx]  
00F81336  dec         edi  
00F81337  jne         wmain+0B0h (0F81330h)  
	}

	{
		bindFunc();
012D13A0  mov         ecx,dword ptr [esp+2Ch]  
012D13A4  test        ecx,ecx  
012D13A6  je          wmain+264h (012D14E4h)  
012D13AC  mov         eax,dword ptr [ecx]  
012D13AE  call        dword ptr [eax+8]  
	for (unsigned int i = 0; i < max_loop; i++)
012D13B1  inc         esi  
012D13B2  cmp         esi,10000h  
012D13B8  jb          wmain+120h (012D13A0h)  
	}