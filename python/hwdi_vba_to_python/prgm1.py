def Target355mm( ZFKC, ZFO, TKC):
        Factor = 21 + (1/3)
	ZFKCFt = ZFKC.replace(' ', '')
	ZFKCFtnew = ZFKCFt[0:4]
	print ZFKCFtnew
	ZFKCFr = ZFKC.replace(' ', '')
	ZFKCFrnew = ZFKCFr[6:8]
	print ZFKCFrnew 
	ZF = (int(ZFKCFtnew) * Factor) + int(ZFKCFrnew)
	print ZF
	
	ZFOFt = ZFO.replace(' ', '')
	ZFOFtnew = ZFOFt[0:4]
	print ZFOFtnew
	ZFOFr = ZFO.replace(' ', '')
	ZFOFrnew = ZFOFr[6:8]
	print ZFOFtnew
	ZFD = (int(ZFOFtnew) * Factor) + int(ZFOFrnew)
	print ZFD	
	
	TKCFt = 0
        TKCFr = 0
        TF = 0	
	
	if len(TKC) > 20:
		TKCFt = TKC.replace(' ', '')
		TKCFtnew = TKCFt[12:16]
		print TKCFtnew
		TKCFr = TKC.replace(' ', '')
		TKCFrnew = TKCFr[17:19]
		print TKCFrnew
		TF = (int(TKCFtnew) * Factor) + int(TKCFrnew)
		#print TF
	else:
		TKCFt = TKC.replace(' ', '') 
                TKCFtnew = TKCFt[0:4]
		print TKCFtnew 
                TKCFr = TKC.replace(' ', '') 
                TKCFrnew = TKCFr[6:8]   
		print TKCFtnew		
		TF = (int(TKCFtnew) * Factor) + int(TKCFrnew)
		print TF
	
	return abs(TF - ZF + ZFD) 

Target355mm("19 23 4932T","19 23 4932","192838 2385 2893")
