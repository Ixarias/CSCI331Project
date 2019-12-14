	
	@ECHO OFF
	::Launch the program
	ECHO Running test script file...

	TITLE testScript
	SET /p userPath=Enter path of TestDocument file    ::user enters path of TestDocument location
	ECHO This is the directory you chose %userPath%
	cd %userPath%	::program displays what the user entered location was
	PAUSE
	ECHO These are the files in current directory
	DIR		::displays what is currently in the user picked directory
	PAUSE

	
	ECHO running TestDocument.cpp program...

	gcc TestDocument.cpp -o ssclass.exe		::compiling the TestDocument
	ssclass.exe		::executing the compiled TestDocument

	PAUSE

	::start of test which determines if the program can find the Northernmost, Southernmost, Easternmost, and Westernmost zip code in the state provided 
	ECHO opening file and populating...
	0
	ECHO population complete...
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
	ECHO running state zip direction search...
	9
	N
	TX
	ECHO running state zip direction search...
	9
	W
	AZ
	ECHO running state zip direction search...
	9
	W
	NV
	PAUSE

	::start of a test which displays the record/s with the matching zip code provided by the user
	ECHO running zip search...
	6
	1001
	ECHO running zip search...
	6
	1075
	ECHO running zip search...
	6
	62447
	ECHO running zip search...
	6
	78650
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
