	
	@ECHO OFF
	::Launch the program
	ECHO Running test script file.....

	TITLE testScript
	SET /p userPath=Enter path of TestDocument file 
	ECHO This is the directory you chose %userPath%
	cd %userPath%
	PAUSE
	ECHO These are the files in current directory
	DIR
	PAUSE


	ECHO running TestDocument.cpp program......

	gcc TestDocument.cpp -o ssclass.exe
	ssclass.exe

	PAUSE

	ECHO opening file and populating...
	0


	ECHO running state zip direction search...
	9
	E
	MN


	ECHO running state zip direction search...
	9
	N
	MN
	

	ECHO running state zip direction search...
	9
	S
	MN


	ECHO running state zip direction search...
	9
	W
	MN

	PAUSE



	@ECHO ON
	::Open file

	::Insert  
	::Remove 
	::Modify  
	::Display recrod
	::Display feild in record
	::Verify
	::Run Test Sequence
	::Search state 
	::Quit
