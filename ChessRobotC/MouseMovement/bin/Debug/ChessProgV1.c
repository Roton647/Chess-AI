#include "PC_FileIO.c"

typedef struct
{
	int RookCol[3];
	int PawnCol[3];
	int KingCol[3];
	int QueenCol[3];
	int BishopCol[3];
	int KnightCol[3];
	int WhitePiece;
	int CurColour[3];
	char whitecoords[8][8];
}ColourValue;
const int Tol = 20;
const float xMovementconst = 6.35*(360/(4*PI));
const float yMovementconst = 6.35*(360/(3.5*PI));
const int XYPower = 10;
const int ClawPower = 5;
int checkButtonPress(bool difficulty)
{
	while(!getButtonPress(buttonAny))
	{}
	int Check = 0;
	if(getButtonPress(buttonLeft))
	{
		Check = 1;
		displayString(1,"left button clicked");
	}

	else if(getButtonPress(buttonUp)&&!difficulty)
	{
		Check = 0;
		displayString(1,"up button clicked");
	}

	else if(getButtonPress(buttonRight))
	{
		Check = 2;
		displayString(1,"right button clicked");

	}
	else
	{
		Check = 4;
		displayString(1,"No greast am");
	}
	while(getButtonPress(buttonAny))
	{}
	return Check;
}
void countdown()
{
	time1[T2] = 0;
	int TimeCalc = 0;
	while(time1[T2]<5000)
	{
		TimeCalc = 5000 - time1[T2];
		if(TimeCalc % 1000 == 0)
		{
			displayBigTextLine(1, "%d SECONDS",TimeCalc/1000.0);
		}
	}
}

void xMovement(float oldX, float newX)
{
	int Negative = 1;
	int XChange = newX-oldX;
	if(XChange<0)
	{
		Negative = -1;
		XChange *= Negative;
	}
	nMotorEncoder[motorD] = 0;
	motor[motorD] = XYPower*Negative;
	while(abs(nMotorEncoder[motorD])<XChange*xMovementconst)
	{}
	motor[motorD] = 0;


	// d
}
void yMovement(float oldY, float newY)
{
	int Negative = 1;
	int YChange = newY-oldY;
	if(YChange<0)
	{
		Negative = -1;
		YChange *= Negative;
	}
	nMotorEncoder[motorA] = 0;
	motor[motorA] = XYPower*Negative;
	while(abs(nMotorEncoder[motorA])<YChange*yMovementconst)
	{}
	motor[motorD] = 0;
}
void placePiece(bool pickup)
{
	//test
}
void movement(int oldX, int oldY, int newX, int newY)
{
	//jj
}
bool isColor(int Chosen, ColourValue & Piece, int Red, int Green, int Blue)
{
	// Pawn = 1, Rook = 2, Knight = 3, Bishop = 4, King = 5 , Queen = 6
	if(Chosen == 1)
	{
		return (abs(Piece.PawnCol[0]-Red)<Tol&&abs(Piece.PawnCol[1]-Green)<Tol && abs(Piece.PawnCol[2]-Blue)<Tol);
	}
	else if(Chosen == 2)
	{
		return (abs(Piece.RookCol[0]-Red)<Tol&&abs(Piece.RookCol[1]-Green)<Tol && abs(Piece.RookCol[2]-Blue)<Tol);
	}
	else if(Chosen == 3)
	{
		return (abs(Piece.KnightCol[0]-Red)<Tol&&abs(Piece.KnightCol[1]-Green)<Tol && abs(Piece.KnightCol[2]-Blue)<Tol);
	}
	else if(Chosen == 4)
	{
		return (abs(Piece.BishopCol[0]-Red)<Tol&&abs(Piece.BishopCol[1]-Green)<Tol && abs(Piece.BishopCol[2]-Blue)<Tol);
	}
	else if(Chosen == 5)
	{
		return (abs(Piece.KingCol[0]-Red)<Tol&&abs(Piece.KingCol[1]-Green)<Tol && abs(Piece.KingCol[2]-Blue)<Tol);
	}
	else if(Chosen == 6)
	{
		return (abs(Piece.QueenCol[0]-Red)<Tol&&abs(Piece.QueenCol[1]-Green)<Tol && abs(Piece.QueenCol[2]-Blue)<Tol);
	}
	return false;

}

void scanBoard(bool initial, ColourValue & Piece)
{
	displayBigTextLine(2,"Scanning In Proccess, Beep Boop");
	Piece.WhitePiece = 16;
	xMovement(0,7.25/6.35);
	yMovement(0,-2.5/6.35);
	if(initial)
	{
		for(int i = 0; i< 6; i++)
		{
			for(int inc = 0; inc<8; inc++)
			{
				Piece.whitecoords[i][inc] = ' ';
			}
		}
		for(int i = 0; i<8; i++)
		{
			Piece.whitecoords[6][i] = 'P';
		}
		Piece.whitecoords[7][0] = 'R';
		Piece.whitecoords[7][1] = 'H';
		Piece.whitecoords[7][2] = 'B';
		Piece.whitecoords[7][3] = 'Q';
		Piece.whitecoords[7][4] = 'K';
		Piece.whitecoords[7][5] = 'B';
		Piece.whitecoords[7][6] = 'H';
		Piece.whitecoords[7][7] = 'R';
		Piece.WhitePiece = 16;
		xMovement(0,7);
		wait1Msec(250);
		getColorRGB(S3,Piece.RookCol[0],Piece.RookCol[1],Piece.RookCol[2]);
		wait1Msec(250);
		yMovement(0,1);
		wait1Msec(250);
		getColorRGB(S3,Piece.KnightCol[0], Piece.KnightCol[1], Piece.KnightCol[2]);
		wait1Msec(250);
		yMovement(1,2);
		wait1Msec(250);
		getColorRGB(S3,Piece.BishopCol[0],Piece.BishopCol[1],Piece.BishopCol[2]);
		wait1Msec(250);
		yMovement(2,3);
		wait1Msec(250);
		getColorRGB(S3,Piece.QueenCol[0],Piece.QueenCol[1],Piece.QueenCol[2]);
		wait1Msec(250);
		yMovement(3,4);
		wait1Msec(250);
		getColorRGB(S3,Piece.KingCol[0],Piece.KingCol[1],Piece.KingCol[2]);
		wait1Msec(250);
		xMovement(7,6);
		wait1Msec(250);
		getColorRGB(S3,Piece.PawnCol[0],Piece.PawnCol[1],Piece.PawnCol[2]);
		xMovement(6,0);//Rest the shit
		yMovement(4,0);
	}
	else
	{
		int TotalPiece = 0;
		for(int i = 0; i< 8&&TotalPiece<Piece.WhitePiece; i++)
		{
			if(i > 0)
			{
				xMovement(i-1, i);
			}
			for(int inc = 0; inc< 8&&TotalPiece<Piece.WhitePiece; inc++)
			{
				if(inc > 0)
				{
					yMovement(inc-1, inc);
				}
				string Chosen = "Rook";
				int Red = 0, Green = 0, Blue = 0;
				wait1Msec(300);
				getColorRGB(S3,Red,Green,Blue);
				if(isColor(2,Piece,Red,Green,Blue))
				{
					TotalPiece++;
					Piece.whitecoords[i][inc] = 'R';
				}
				else if(isColor(1,Piece,Red,Green,Blue))
				{
					TotalPiece++;
					Piece.whitecoords[i][inc] = 'P';
				}
				else if(isColor(3,Piece,Red,Green,Blue))
				{
					TotalPiece++;
					Piece.whitecoords[i][inc] = 'H';
				}
				else if(isColor(4,Piece,Red,Green,Blue))
				{
					TotalPiece++;
					Piece.whitecoords[i][inc] = 'B';
				}
				else if(isColor(6,Piece,Red,Green,Blue))
				{
					TotalPiece++;
					Piece.whitecoords[i][inc] = 'Q';
				}
				else if(isColor(5,Piece,Red,Green,Blue))
				{
					TotalPiece++;
					Piece.whitecoords[i][inc] = 'K';
				}


			}

		}
	}
}



task main()
{
	SensorType[S2] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S2] = modeEV3Color_Ambient;
	wait1Msec(50);
	const int Time = 15*60*1000;
	int Timer = 4;
	int Difficulty  = 4;

	ColourValue CurrentStuff;
	while(Timer == 4)
	{
		displayTextLine(2,"Enter the Timer Setting, Up for no limit, Left for 15 minutes, and Right for 30 minutes");
		Timer = checkButtonPress(false);
	}
	Timer *= Time;//add in the check for infinite
	displayTextLine(2,"Enter the Difficulty Setting, Left for beginner, Right for Regular");
	while (Difficulty == 4)
	{
		displayString(2,"Enter the Timer Setting, Up for no limit, Left for 15 minutes, and Right for 30 minutes");
		Difficulty = checkButtonPress(true);
	}
	eraseDisplay();
	scanBoard(true, CurrentStuff);





	/*wait1Msec(500);
	string s = "";
	while(s!=""||s=="")
	{
	TFileHandle fin;
	bool fileOkay = openReadPC(fin, "chessmove.txt");
	readTextPC(fin, s);
	displayString(1,s);
	closeFilePC(fin);
	}
	displayString(1,s);
	*/

}
