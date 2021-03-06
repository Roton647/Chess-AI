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
const float xMovementconst = 6.35*(360/(4.05*PI));
const float yMovementconst = 6.35*(360/(3.05*PI));
const int XYPower = 15;
int checkButtonPres = 20;
void xMovement(float oldX, float newX, bool reset)
{
	int Negative = 1;
	float XChange = newX-oldX;
	if(XChange<0)
	{
		Negative = -1;
		XChange *= Negative;
	}
	if(reset)
	{
			nMotorEncoder[motorD] = 0;
	}
	motor[motorD] = XYPower*Negative;
	while(abs(nMotorEncoder[motorD])<abs(newX*xMovementconst))
	{
		displayBigTextLine(1,"%d",nMotorEncoder[motorD]);
		displayBigTextLine(3,"%f",newX*xMovementconst);
	}
	motor[motorD] = 0;

}
void yMovement(float oldY, float newY, bool reset)
{
	int Negative = 1;
	float YChange = newY-oldY;
	if(YChange<0)
	{
		Negative = -1;
		YChange *= Negative;
	}
	if(reset)
	{
		nMotorEncoder[motorA] = 0;
	}
	motor[motorA] = XYPower*Negative;
	while(abs(nMotorEncoder[motorA])<abs(newY*yMovementconst))
	{
				displayBigTextLine(1,"%f",nMotorEncoder[motorA]);
		displayBigTextLine(3,"%f",newY*yMovementconst);
	}
	displayBigTextLine(7,"%f",nMotorEncoder[motorA]);
	motor[motorA] = 0;
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
	//displayBigTextLine(2,"Scanning In Proccess, Beep Boop");
	Piece.WhitePiece = 16;

		//yMovement(0,7/6.35,0);
		//xMovement(0,-3.5/6.35,0);
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
		xMovement(0,7,1);
		wait1Msec(1000);
		getColorRGB(S3,Piece.RookCol[0],Piece.RookCol[1],Piece.RookCol[2]);
		wait1Msec(1000);
		yMovement(0,1,1);
		wait1Msec(1000);
		getColorRGB(S3,Piece.KnightCol[0], Piece.KnightCol[1], Piece.KnightCol[2]);
	wait1Msec(1000);
		yMovement(1,2,0);
	wait1Msec(1000);
		getColorRGB(S3,Piece.BishopCol[0],Piece.BishopCol[1],Piece.BishopCol[2]);
	wait1Msec(1000);
	yMovement(2,3,0);
	wait1Msec(1000);
		getColorRGB(S3,Piece.QueenCol[0],Piece.QueenCol[1],Piece.QueenCol[2]);
	wait1Msec(1000);
		yMovement(3,4,0);
		wait1Msec(1000);
		getColorRGB(S3,Piece.KingCol[0],Piece.KingCol[1],Piece.KingCol[2]);
		wait1Msec(1000);
		xMovement(7,6,0);
		wait1Msec(1000);
		getColorRGB(S3,Piece.PawnCol[0],Piece.PawnCol[1],Piece.PawnCol[2]);
		wait1Msec(1000);
		xMovement(6,0,0);//Rest the shit
		yMovement(4,0,0);
	}
	else
	{
		nMotorEncoder[motorA] = 0;
		nMotorEncoder[motorD] = 0;
		int TotalPiece = 0;
		for(int i = 0; i< 8&&TotalPiece<Piece.WhitePiece; i++)
		{
			if(i > 0)
			{
				xMovement(i-1, i,0);
			}
			for(int inc = 0; inc< 8&&TotalPiece<Piece.WhitePiece; inc++)
			{
				if(inc > 0)
				{
					yMovement(inc-1, inc, 0);
				}
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



}
