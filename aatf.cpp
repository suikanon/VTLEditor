#include <string>
#include <sstream>
#include "editor.h"
#include "resource.h"
#ifndef UNICODE  
  typedef std::string tstring; 
  typedef std::stringstream tstringstream;
#else
  typedef std::wstring tstring; 
  typedef std::wstringstream tstringstream;
#endif

void aatf_single(HWND hAatfbox, int pesVersion, int teamSel, player_entry* gplayers, team_entry* gteams, int gnum_players)
{
	player_entry player;
	tstring msgOut;
	msgOut+=_T("Team: ");
	msgOut+=gteams[teamSel].name;
	msgOut+=_T("\r\n");

	//Settings
	int manletBonus = 0;
	int silverManletBonus = 0;
	int goldGiantPen = 0;
	int silverGiantPen = 0;

	int goldRate = 99;
	int silverRate = 93;
	int regRate = 77;
	int gkRate = 77;
	int reqNumGold = 2;
	int reqNumSilver = 3;

	int goldForm = 8;
	int silverForm = 6;
	int regForm = 2;

	int goldIR = 1; //Injury resistence
	int silverIR = 1;
	int regIR = 1;

	int gkSkillCards = 3;
	int regSkillCards = 9;
	int silverSkillCards = 9;
	int goldSkillCards = 8;

	int gkTrickCards = 0;
	int regTrickCards = 99;
	int silverTrickCards = 99;
	int goldTrickCards = 99;

	int regCOM = 2;
	int silverCOM = 2;
	int goldCOM = 2;

	int greenGiant = 5;
	int greenTall = 5;
	int greenMid = 7;
	int greenManlet = 6;

	int redGiant = 0;
	int redTall = 10;
	int redMid = 7;
	int redManlet = 6;

	int heightGiant = 181;
	int heightTall = 181;
	int heightTallGK = 181;
	int heightMid = 181;
	int heightManlet = 181;

	int numGK = 0;
    //Count of player ratings
    int numReg = 0;
    int numSilver = 0;
    int numGold = 0;
    //Count of height brackets
    int numGiant = 0;
    int numTall = 0;
    int numMid = 0;
    int numManlet = 0;
    bool usingRed = false;
    
    int errorTot = 0;
	for(int ii=0; ii<gteams[teamSel].num_on_team; ii++)
	{
		//Find each player on team
		for(int jj=0; jj<gnum_players; jj++)
		{
			if(gplayers[jj].id == gteams[teamSel].players[ii])
			{
				player = gplayers[jj];
				break;
			}
		}

		msgOut+=_T("\x2022 Checking ");
		msgOut+=player.name;
		msgOut+=_T("\r\n");

		tstringstream errorMsg;

		int cardCount = 0;
        int cardMod = 0;
		int cardLimit = 0;
        bool hasTrick = false;
		int targetRate = 0, targetRate2 = 0;
		int rating = player.place_kick;
		/*int rating = player.drib;
        rating = max(player.gk, rating);
        rating = max(player.finish, rating);
        rating = max(player.lowpass, rating);
        rating = max(player.loftpass, rating);
        rating = max(player.header, rating);
        rating = max(player.swerve, rating);
        rating = max(player.catching, rating);
        rating = max(player.clearing, rating);
        rating = max(player.reflex, rating);
        rating = max(player.body_ctrl, rating);
        if(pesVersion!=16) rating = max(player.phys_cont, rating); //Not in 16
        rating = max(player.kick_pwr, rating);
        rating = max(player.exp_pwr, rating);
        rating = max(player.ball_ctrl, rating);
        rating = max(player.ball_win, rating);
        rating = max(player.jump, rating);
        rating = max(player.cover, rating);
        rating = max(player.place_kick, rating);
        rating = max(player.stamina, rating);
        rating = max(player.speed, rating);
		if(pesVersion>19) rating = max(player.aggres, rating);*/

		/*if(player.injury+1 > 3)
		{
			errorTot++;
            errorMsg << _T("Injury resist is ") << player.injury+1 << _T(", cannot exceed 3; ");
		}*/

		//Check if registered pos has playable set to A
        if(player.reg_pos == 12 && player.play_pos[0] != 2)
		{
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 11 && player.play_pos[1] != 2)
		{
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 10 && player.play_pos[3] != 2)
		{
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 9 && player.play_pos[2] != 2)
        {
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 8 && player.play_pos[4] != 2)
        {
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 7 && player.play_pos[8] != 2)
        {
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 6 && player.play_pos[7] != 2)
        {
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 5 && player.play_pos[6] != 2)
        {
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 4 && player.play_pos[5] != 2)
        {
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 3 && player.play_pos[11] != 2)
        {
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 2 && player.play_pos[10] != 2)
        {
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 1 && player.play_pos[9] != 2)
        {
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 0)
        {
            numGK++;
            if(player.play_pos[12] != 2)
			{
                errorTot++;
				errorMsg << _T("Doesn't have A in registered position; ");
			}
        }

		if(player.reg_pos != 0 && player.play_pos[0] == 0)
		{
            errorTot++;
			errorMsg << _T("Can't have C position; ");
		}
        else if(player.reg_pos != 0 && player.play_pos[1] == 0)
		{
            errorTot++;
			errorMsg << _T("Can't have C position; ");
		}
        else if(player.reg_pos != 0 &&  player.play_pos[3] == 0)
		{
            errorTot++;
			errorMsg << _T("Can't have C position; ");
		}
        else if(player.reg_pos != 0 && player.play_pos[2] == 0)
        {
            errorTot++;
			errorMsg << _T("Can't have C position; ");
		}
        else if(player.reg_pos != 0 && player.play_pos[4] == 0)
        {
            errorTot++;
			errorMsg << _T("Can't have C position; ");
		}
        else if(player.reg_pos != 0 && player.play_pos[8] == 0)
        {
            errorTot++;
			errorMsg << _T("Can't have C position; ");
		}
        else if(player.reg_pos != 0 && player.play_pos[7] == 0)
        {
            errorTot++;
			errorMsg << _T("Can't have C position; ");
		}
        else if(player.reg_pos != 0 && player.play_pos[6] == 0)
        {
            errorTot++;
			errorMsg << _T("Can't have C position; ");
		}
        else if(player.reg_pos != 0 && player.play_pos[5] == 0)
        {
            errorTot++;
			errorMsg << _T("Can't have C position; ");
		}
        else if(player.reg_pos != 0 && player.play_pos[11] == 0)
        {
            errorTot++;
			errorMsg << _T("Can't have C position; ");
		}
        else if(player.reg_pos != 0 && player.play_pos[10] == 0)
        {
            errorTot++;
			errorMsg << _T("Can't have C position; ");
		}
        else if(player.reg_pos != 0 && player.play_pos[9] == 0)
        {
            errorTot++;
			errorMsg << _T("Can't have C position; ");
		}

		//Count A positions
        int countA = 0;
		int countB = 0;
        for(int jj=0;jj<13;jj++)
        {
            if(player.play_pos[jj] == 2)
				countA++;
			if(player.play_pos[jj] == 1)
				countB++;
        }

		/*if (countA < 3 && player.reg_pos != 0)
		{
			errorTot++;
			errorMsg << _T("Needs at least two second A positions; ");
		}*/
		if (countA >= 2 && player.reg_pos == 0)
		{
			errorTot++;
			errorMsg << _T("GK doesn't get second A positions; ");
		}
		if (countB > 0 && player.reg_pos == 0)
		{
			errorTot++;
			errorMsg << _T("GK doesn't get B positions; ");
		}
        //If more than 1 A, 1 card less for each
        if(countA >= 1)
        {
            if(player.play_pos[12] != 0 && player.reg_pos != 0) //Can't have GK as second A
			{
                errorTot++;
				errorMsg << _T("Has GK as second position; ");
			}
			if (countA > 1)
			{
				cardMod -= (countA - 1);
			}
        }

		//Count cards
		int numTrick = 0;
		int numCom = 0;
		int numSkill;
		if(pesVersion==19) numSkill=39;
		else if(pesVersion>19) numSkill=41;
		else numSkill=28;
        for(int jj=0;jj<numSkill;jj++)
        {
            if(player.play_skill[jj])
            {
                cardCount++;
                //Captain gets free captaincy card
				if(jj==25 && player.id == gteams[teamSel].players[gteams[teamSel].captain_ind])
                    cardMod++;
                //Trick cards may be free, count number
                if(jj<6 || jj==9 || jj== 10 ||jj==16 || jj==21 || jj==28 || jj==29 || jj==30 || jj==34)
				{
                    hasTrick = true;
					numTrick++;
				}
				/*if (jj == 36)
				{
					errorTot++;
					errorMsg << _T("Remove illegal card (Penality Specialist); ");
				}
				if (jj == 38)
				{
					errorTot++;
					errorMsg << _T("Remove illegal card (Interception); ");
				}*/
            }
        }
		//another free capitan card
		if (player.id == gteams[teamSel].players[gteams[teamSel].captain_ind])
			cardMod++;

		for(int jj=0;jj<7;jj++)
        {
            if(player.com_style[jj])
			{
				cardCount++;
				numCom++;
			}
		}

        if(player.height == 181)
            numTall++;
        //else if(player.height == 186 && player.reg_pos == 0) //GK
        //    numTall++;
        else
		{
            errorTot++;
			errorMsg << _T("Illegal height (") << player.height << _T(" cm); ");
		}

		if(player.age<15 || player.age>50)
		{
			errorTot++;
			errorMsg << _T("Age out of range (15,50); ");
		}

		if(player.weight<max(30,player.height-129) || player.weight>(player.height-81))
		{
			errorTot++;
			errorMsg << _T("Weight out of range (") << max(30,player.height-129) << _T(",") << player.height-81 << _T("); ");
		}

		/* REGULAR */
		if(rating < silverRate-silverGiantPen) //Regular player
        {
            numReg++;
			targetRate = regRate;
			targetRate2 = regRate;
			if(player.reg_pos == 0) //GK target rate is 77
            {
				targetRate = gkRate;
				targetRate2 = gkRate;
			}


			if(player.weak_use+1 != 4)
			{
				errorTot++;
				errorMsg << _T("Weak foot usage should be 4; ");
			}
			if(player.weak_acc+1 != 4)
			{
				errorTot++;
				errorMsg << _T("Weak foot accuracy should be 4; ");
			}


            if(player.form+1 != regForm)
			{
                errorTot++;
				errorMsg << _T("Form is ") << player.form+1 << _T(", should be ") << regForm << _T("; ");
			}
			
            if(player.reg_pos == 0) //GK gets 2 cards
            {
				cardMod += min(gkTrickCards, numTrick); //1 free tricks
				cardLimit = gkSkillCards + cardMod;
                if(cardCount > cardLimit)
				{
                    errorTot++;
					errorMsg << _T("Has ") << cardCount << _T(" cards, only allowed ") << cardLimit << _T("; ");
				}
				/*if (player.height > heightMid && player.height < heightTallGK)
				{
                    errorTot++;
					errorMsg << _T("GKs in this bracket must be ") << heightTallGK << _T("cm; ");
				}*/
            }
            else
			{
				cardMod += min(regCOM, numCom); //free COM styles
				cardMod += min(regTrickCards, numTrick); //2 free tricks
				cardMod += min(1, (countA - 1)); //1 free A-position
				cardLimit = regSkillCards + cardMod; //3 skill cards
				if(cardCount > cardLimit)
				{
					errorTot++;
					errorMsg << _T("Has ") << cardCount << _T(" cards, only allowed ") << cardLimit << _T("; ");
				}
			}
            
            /*if (rating != targetRate)
            {
                if(rating == targetRate+manletBonus && player.height <= heightManlet)
				{
                    usingRed = true;
					targetRate += manletBonus;
					targetRate2 += manletBonus;
				}
				else
				{
                    errorTot++;
					errorMsg << _T("Illegal Ability scores; ");
				}
            }
			*/
		if(player.injury+1 > regIR)
		{
			errorTot++;
			errorMsg << _T("Injury resist is ") << player.injury+1 << _T(", should be ") << regIR << _T("; ");
		}
		}
		/* SILVER */
        else if(rating < goldRate-goldGiantPen) //Silver player
        {
            numSilver++;
			targetRate = silverRate;
			targetRate2 = silverRate;

			if(player.weak_use+1 != 4)
			{
				errorTot++;
				errorMsg << _T("Weak foot usage is not 4; ");
			}
			if(player.weak_acc+1 != 4)
			{
				errorTot++;
				errorMsg << _T("Weak foot accuracy is not 4; ");
			}
            if(numSilver > reqNumSilver)
			{
                errorTot++;
				errorMsg << _T("Too many Silver medals; ");
			}
            if(player.form+1 != silverForm)
			{
                errorTot++;
				errorMsg << _T("Form is ") << player.form+1 << _T(", should be ") << silverForm << _T("; ");
			}
            if(player.reg_pos == 0) //Medals can't be GK
			{
                errorTot++;
				errorMsg << _T("Medals cannot play as GK; ");
			}
			if(player.height == heightGiant) //HA get penalty
			{
				targetRate -= silverGiantPen;
				targetRate2 -= silverGiantPen;
			}
			else if(player.height <= heightManlet && rating == targetRate + silverManletBonus)
            {
				usingRed = true;
				targetRate += silverManletBonus;
				targetRate2 += silverManletBonus;
			}
            cardMod += min(silverTrickCards, numTrick); //3 free tricks
			cardMod += min(silverCOM, numCom); //free COM
			cardMod += min(1, (countA - 1)); //1 free A-position
			cardLimit = silverSkillCards + cardMod; //4 skill cards
            if(cardCount > cardLimit)
			{
                errorTot++;
				errorMsg << _T("Has ") << cardCount << _T(" cards, only allowed ") << cardLimit << _T("; ");
			}
            /*if (rating != targetRate)
			{
                errorTot++;
				errorMsg << _T("Illegal Ability scores; ");
			}*/
			if(player.injury+1 > silverIR)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury+1 << _T(", should be ") << silverIR << _T("; ");
			}
        }
		/* GOLD */
        else //rating == 99 //Gold player
        {
            numGold++;
			targetRate = goldRate;
			targetRate2 = goldRate;

			if(player.weak_use+1 != 4)
			{
				errorTot++;
				errorMsg << _T("Weak foot usage is not 4; ");
			}
			if(player.weak_acc+1 != 4)
			{
				errorTot++;
				errorMsg << _T("Weak foot accuracy is not 4; ");
			}

            if(numGold > reqNumGold)
			{
                errorTot++;
				errorMsg << _T("Too many Gold medals; ");
			}
            if(player.form+1 != goldForm)
			{
                errorTot++;
				errorMsg << _T("Form is ") << player.form+1 << _T(", should be ") << goldForm << _T("; ");
			}
            if(player.reg_pos == 0) //Medals can't be GK
			{
                errorTot++;
				errorMsg << _T("Medals cannot play as GK; ");
			}
			if(player.height == heightGiant) //Medal HA penalty
			{
				targetRate -= goldGiantPen;
				targetRate2 -= goldGiantPen;
			}
			
            cardMod += min(goldTrickCards, numTrick); //4 free tricks
			cardMod += min(goldCOM, numCom); //free COMs
			cardLimit = goldSkillCards + cardMod; //5 skill cards
            if(cardCount > cardLimit)
			{
                errorTot++;
				errorMsg << _T("Has ") << cardCount << _T(" cards, only allowed ") << cardLimit << _T("; ");
			}
            /*if (rating != targetRate)
			{
                errorTot++;
				errorMsg << _T("Illegal Ability scores; ");
			}*/

			if(player.injury+1 > goldIR)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury+1 << _T(", should be ") << goldIR << _T("; ");
			}
		}

		//Check PES skill card limit of 10
		if(cardCount-numCom > 10)
		{
            errorTot++;
			errorMsg << _T("Has ") << cardCount-numCom << _T(" skill cards, PES limit is 10, please swap to COM cards or trade for additional A positions; ");
		}

		//Has at least 6 cards
		if (cardCount < 6 && player.reg_pos != 0)
		{
			errorTot++;
			errorMsg << _T("Has ") << cardCount<< _T(" cards, needs 6 at minimum (Com Styles count towards this) ; ");
		}

		//GK has cards
		if (cardCount < 1 && player.reg_pos == 0)
		{
			errorTot++;
			errorMsg << _T("Has ") << cardCount << _T(" cards, hey you can add more, dummy ; ");
		}

		int ismedal = 0;


		if (targetRate == 93)
			{
				ismedal = 1;
			}
		else if (targetRate == 99)
		{
			ismedal = 2;
		}
		/*
		if((player.atk > 98 && ismedal == 1) || (player.atk > 94 && ismedal == 0))
		{
            errorTot++;
			errorMsg << _T("Attacking Prowess is ") << player.atk << _T(", should be ") << targetRate << _T(" or less; ");
  	  	}
		if(player.ball_ctrl != targetRate && (ismedal == 0 && player.ball_ctrl != 89))
		{
            errorTot++;
			errorMsg << _T("Ball Control is ") << player.ball_ctrl << _T(", should be ") << targetRate << _T("; ");
        }
		if(player.drib != targetRate && (ismedal == 0 && player.drib != 89))
        {
            errorTot++;
			errorMsg << _T("Dribbling is ") << player.drib << _T(", should be ") << targetRate << _T("; ");
        }
		if(player.lowpass != targetRate && (ismedal == 0 && player.lowpass != 85))
		{
            errorTot++;
			errorMsg << _T("Low Pass is ") << player.lowpass << _T(", should be ") << targetRate << _T("; ");
        }
		if(player.finish != targetRate2 && ((ismedal == 1 && player.finish != 98) || (ismedal == 0 && player.finish != 97)))
		{
            errorTot++;
			errorMsg << _T("Finishing is ") << player.finish << _T(", should be ") << targetRate2 << _T("; ");
        }
		if(player.swerve != targetRate && ((ismedal == 1 && player.swerve != 98) || (ismedal == 0 && player.swerve != 97)))
		{
            errorTot++;
			errorMsg << _T("Swerve is ") << player.swerve << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.header != targetRate2 && (ismedal == 0 && player.header != 82))
		{
            errorTot++;
			errorMsg << _T("Header is ") << player.header << _T(", should be ") << targetRate2 << _T("; ");
        }
        if((player.def > 88 && ismedal == 1) || (player.def > 72 && ismedal == 0))
		{
            errorTot++;
			errorMsg << _T("Defensive Prowess is ") << player.def << _T(", should be ") << targetRate << _T(" or less; ");
        }
		if(player.ball_win != targetRate && ((ismedal == 0 && player.ball_win != 66) || (ismedal == 1 && player.ball_win != 88)))
		{
            errorTot++;
			errorMsg << _T("Ball winning is ") << player.ball_win << _T(", should be ") << targetRate << _T("; ");
        }
		if(player.kick_pwr != targetRate && (ismedal == 0 && player.kick_pwr != 85))
		{
            errorTot++;
			errorMsg << _T("Kicking Power is ") << player.kick_pwr << _T(", should be ") << targetRate << _T("; ");
        }
		if(player.speed != targetRate && ((ismedal == 1 && player.speed != 95) || (ismedal == 0 && player.speed != 82)))
		{
            errorTot++;
			errorMsg << _T("Speed is ") << player.speed << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.exp_pwr != targetRate && (ismedal == 0 && player.exp_pwr != 72))
		{
            errorTot++;
			errorMsg << _T("Explosive Power is ") << player.exp_pwr << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.body_ctrl != targetRate && (ismedal == 0 && player.body_ctrl != 86))
		{
            errorTot++;
			errorMsg << _T("Body Control is ") << player.body_ctrl << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.phys_cont != targetRate && pesVersion!=16 && (ismedal == 0 && player.phys_cont != 73)) //Not in 16
		{
            errorTot++;
			errorMsg << _T("Physical Contact is ") << player.phys_cont << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.jump != targetRate && player.jump != 77)
		{
            errorTot++;
			errorMsg << _T("Jump is ") << player.jump << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.stamina != targetRate && (ismedal == 0 && player.stamina != 66))
		{
            errorTot++;
			errorMsg << _T("Stamina is ") << player.stamina << _T(", should be ") << targetRate << _T("; ");
        }
		if((player.gk > 40 && ismedal == 2) || (player.gk > 40 && ismedal == 1) || (player.gk > 77 && ismedal == 0))
		{
            errorTot++;
			errorMsg << _T("Goalkeeping is ") << player.gk << _T(", should be ") << targetRate << _T(" or less; ");
        }
		if((player.catching > 40 && ismedal == 2) || (player.catching > 40 && ismedal == 1) || (player.catching > 72 && ismedal == 0))
		{
            errorTot++;
			errorMsg << _T("Catching is ") << player.catching << _T(", should be ") << targetRate << _T(" or less; ");
        }		
		if((player.clearing > 40 && ismedal == 2) || (player.clearing > 40 && ismedal == 1) || (player.clearing > 77 && ismedal == 0))
		{
            errorTot++;
			errorMsg << _T("Clearing is ") << player.clearing << _T(", should be ") << targetRate << _T(" or less; ");
        }		
		if((player.reflex > 40 && ismedal == 2) || (player.reflex > 40 && ismedal == 1) || (player.reflex > 77 && ismedal == 0))
		{
            errorTot++;
			errorMsg << _T("Reflex is ") << player.reflex << _T(", should be ") << targetRate << _T(" or less; ");
        }	
		if((player.cover > 40 && ismedal == 2) || (player.cover > 40 && ismedal == 1) || (player.cover > 77 && ismedal == 0))
		{
            errorTot++;
			errorMsg << _T("Coverage is ") << player.cover << _T(", should be ") << targetRate << _T(" or less; ");
        }	
		*/
		
		if(player.drib != targetRate && (ismedal == 0 && player.drib != 89))
        {
            errorTot++;
			errorMsg << _T("Dribbling is ") << player.drib << _T(", should be 89; ");
        }
        if(player.gk != targetRate && player.gk != 40)
        {
            errorTot++;
			errorMsg << _T("Goalkeeping is ") << player.gk << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.finish != targetRate2 && ((ismedal == 1 && player.finish != 98) || (ismedal == 0 && player.finish != 97)))
		{
            errorTot++;
			errorMsg << _T("Finishing is ") << player.finish << _T(", should be 97; ");
        }
        if(player.lowpass != targetRate && (ismedal == 0 && player.lowpass != 85))
		{
            errorTot++;
			errorMsg << _T("Low Pass is ") << player.lowpass << _T(", should be 85; ");
        }
        if(player.loftpass != targetRate && (ismedal == 0 && player.loftpass != 85))
		{
            errorTot++;
			errorMsg << _T("Lofted Pass is ") << player.loftpass << _T(", should be 85; ");
        }
        if(player.header != targetRate2 && (ismedal == 0 && player.header != 82))
		{
            errorTot++;
			errorMsg << _T("Header is ") << player.header << _T(", should be 82; ");
        }
        if(player.swerve != targetRate && ((ismedal == 1 && player.swerve != 98) || (ismedal == 0 && player.swerve != 97)))
		{
            errorTot++;
			errorMsg << _T("Swerve is ") << player.swerve << _T(", should be 97; ");
        }
        if(player.catching != targetRate && (((ismedal != 0 && player.catching != 40))))
		{
            errorTot++;
			errorMsg << _T("Catching is ") << player.catching << _T(", should be 40 for medals, 77 for non medals; ") << targetRate << _T("; ");
        }
        if(player.clearing != targetRate && (((ismedal == 0 && player.clearing != 72) ||  (ismedal != 0 && player.clearing != 40))))
		{
            errorTot++;
			errorMsg << _T("Clearing is ") << player.clearing << _T(", should be 40 for medals, 72 for non medals; ");
        }
        if(player.reflex != targetRate && (((ismedal != 0 && player.reflex != 40))))
		{
            errorTot++;
			errorMsg << _T("Reflexes is ") << player.reflex << _T(", should be 40 for medals, 77 for non medals; ");
        }
        if(player.body_ctrl != targetRate && ((ismedal == 1 && player.body_ctrl != 88) || (ismedal == 0 && player.body_ctrl != 86)))
		{
            errorTot++;
			errorMsg << _T("Body Control is ") << player.body_ctrl << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.phys_cont != targetRate && pesVersion!=16 && (ismedal == 0 && player.phys_cont != 73)) //Not in 16
		{
            errorTot++;
			errorMsg << _T("Physical Contact is ") << player.phys_cont << _T(", should be 73; ");
        }
        if(player.kick_pwr != targetRate && (ismedal == 0 && player.kick_pwr != 85))
		{
            errorTot++;
			errorMsg << _T("Kicking Power is ") << player.kick_pwr << _T(", should be 85; ");
        }
        if(player.exp_pwr != targetRate && (ismedal == 0 && player.exp_pwr != 72))
		{
            errorTot++;
			errorMsg << _T("Explosive Power is ") << player.exp_pwr << _T(", should be 72; ");
        }
        if(player.ball_ctrl != targetRate && (ismedal == 0 && player.ball_ctrl != 89))
		{
            errorTot++;
			errorMsg << _T("Ball Control is ") << player.ball_ctrl << _T(", should be 89; ");
        }
        if(player.ball_win != targetRate && ((ismedal == 0 && player.ball_win != 66) || (ismedal == 1 && player.ball_win != 91)))
		{
            errorTot++;
			errorMsg << _T("Ball winning is ") << player.ball_win << _T(", should be 66 for non medals 91 for silver medals; ");
        }
        if(player.jump != targetRate && player.jump != 77)
		{
            errorTot++;
			errorMsg << _T("Jump is ") << player.jump << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.cover != targetRate && (ismedal != 0 && player.cover != 40))
		{
            errorTot++;
			errorMsg << _T("Coverage is ") << player.cover << _T(", should be 40 for medals, 77 for non medals; ");
        }
        if(player.place_kick != targetRate)
		{
            errorTot++;
			errorMsg << _T("Place Kicking is ") << player.place_kick << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.stamina != targetRate && (ismedal == 0 && player.stamina != 66))
		{
            errorTot++;
			errorMsg << _T("Stamina is ") << player.stamina << _T(", should be 66; ");
        }
        if(player.speed != targetRate && ((ismedal == 1 && player.speed != 95) || (ismedal == 0 && player.speed != 82)))
		{
            errorTot++;
			errorMsg << _T("Speed is ") << player.speed << _T(", should be 82 for non medals, 95 for silvers; ");
        }
		if((player.atk != 98 && ismedal == 1) || (player.atk != 94 && ismedal == 0))
		{
            errorTot++;
			errorMsg << _T("Attacking Prowess is ") << player.atk << _T(", should be 94 for non medals, 98 for silvers; ");
        }
        if((player.def != 99 && ismedal == 2) || (player.def != 91 && ismedal == 1) || (player.def != 72 && ismedal == 0))
		{
            errorTot++;
			errorMsg << _T("Defensive Prowess is ") << player.def << _T(", should be 72 for non medals, 91 for silvers; ");
        }
		if(pesVersion>19 && player.tight_pos != targetRate && player.tight_pos != 77)
		{
            errorTot++;
			errorMsg << _T("Tight Possession is ") << player.tight_pos << _T(", should be ") << targetRate << _T("; ");
        }
		if(pesVersion>19 && player.aggres != targetRate && player.aggres != 77)
		{
            errorTot++;
			errorMsg << _T("Aggression is ") << player.aggres << _T(", should be ") << targetRate << _T("; ");
        }
		if(errorMsg.rdbuf()->in_avail())
		{
			errorMsg << _T("\r\n");
			msgOut+=_T("\t");
			msgOut+=errorMsg.str();
		}
	}
	//Team level errors
	int diff;
	tstringstream errorMsg;
    //Check heights

	msgOut+=_T("Checking heights...\r\n");
	if (numTall != 23)
	{
		errorTot += 1;
		errorMsg << _T("Has ") << 23 - numTall << _T(" incorect height players (181cm for all); ");
	}
        
    
	if(errorMsg.rdbuf()->in_avail())
	{
		errorMsg << _T("\r\n");
		msgOut+=errorMsg.str();
		errorMsg.clear();
		errorMsg.str(tstring());
	}
    
    //Check ability stats
    if(numReg != (23-reqNumSilver-reqNumGold))
    {
        errorTot++;
        errorMsg << _T("Number of Regular players is ") << numReg << _T(", should be ") << 23-reqNumSilver-reqNumGold << _T("; ");
    }
    if(numSilver != reqNumSilver)
    {
        errorTot++;
        errorMsg << _T("Number of Silver medals is ") << numSilver << _T(", should be ") << reqNumSilver << _T("; ");
    }
    if(numGold != reqNumGold)
    {
        errorTot++;
        errorMsg << _T("Number of Gold medals is ") << numGold << _T(", should be ") << reqNumGold << _T("; ");
    }
	if(errorMsg.rdbuf()->in_avail())
		errorMsg << _T("\r\n");
	errorMsg << _T("\r\nErrors: ") << errorTot << _T("\r\n");
	msgOut+=errorMsg.str();

	SetWindowText(GetDlgItem(hAatfbox, IDT_AATFOUT), msgOut.c_str());
	if(errorTot)
		SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM) _T("PRESS ALL THE BUTTONS"));
	else
		SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM) _T("Engineer Gaming!"));
}
