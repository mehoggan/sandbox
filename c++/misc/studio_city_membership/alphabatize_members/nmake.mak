ListProcess.exe : ListProcess.cpp  
	cl /EHs ListProcess.cpp Tokenizer.cpp
	cl /EHs ListProcess.obj Tokenizer.obj