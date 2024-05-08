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

	//============================
	//Settings
	int manletCardBonus = 2;
	int tallCardBonus = 1;

	int regWMFStatBonus = 6;
	int silverWFStatBonus = 3;
	int captainStatBonus = 2;

	int regWMFHeightBonus = 7;
	int silverWFHeightBonus = 3;
	int medalCFTFHeightBonus = 5;

	int goldRate = 97;
	int silverRate = 87;
	int regRate = 77;
	int gkRate = 77;
	int reqNumGold = 2;
	int reqNumSilver = 2;

	int goldForm = 8;
	int silverForm = 8;
	int regForm = 4;

	int goldIR = 1; //Injury resistance
	int silverIR = 1;
	int regIR = 1;

	int regSkillCardsMin = 3;
	int medalSkillCardsMin = 4;

	int regSkillCardsMax = 5;
	int medalSkillCardsMax = 6;

	int trickCards = 5;

	int regCOM = 1;
	int silverCOM = 3;
	int goldCOM = 5;

	int maxCOM = 5;

	int gk = 2;
	int giga = 2;
	int giant = 7;
	int tall = 8;
	int manlet = 6;

	int heightGiga = 205;
	int heightGiant = 191;
	int heightTall = 181;
	int heightTallGK = 185;
	int heightManlet = 170;
	

	int manletBonus = 5;
	int silverManletBonus = 0;
	int goldManletBonus = 0;
	int silverGiantPen = 0;
	int goldGiantPen = 0;

	int gkSkillCards = 2;

	int regSkillCards = 4;
	int silverSkillCards = 5;
	int goldSkillCards = 6;

	int gkTrickCards = 0;
	int regTrickCards = 2;
	int silverTrickCards = 3;
	int goldTrickCards = 3;

	int greenGiga = 3;
	int greenGiant = 6;
	int greenTall = 4;
	int greenMid = 5;
	int greenManlet = 5;

	int redGiga = 0;
	int redGiant = 0;
	int redTall = 10;
	int redMid = 7;
	int redManlet = 6;

	int heightMid = 170;

	//============================

	int numGK = 0;
    //Count of player ratings
    int numReg = 0;
    int numSilver = 0;
    int numGold = 0;
    //Count of height brackets
	int numGiga = 0;
    int numGiant = 0;
    int numTall = 0;
    int numMid = 0;
    int numManlet = 0;
    //bool usingRed = true;

	//Run through all players once to determine height system
	/*for (int ii = 0; ii < gteams[teamSel].num_on_team; ii++)
	{
		//Find each player on team
		for (int jj = 0; jj < gnum_players; jj++)
		{
			if (gplayers[jj].id == gteams[teamSel].players[ii])
			{
				player = gplayers[jj];
				break;
			}
		}
		//If any player is in the green height brackets, team is on Green height system and we can halt
		if (player.height >= heightGiant)
		{
			usingRed = false;
			break;
		}
	}*/
    
	//Now check each player for errors
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
		int cardMin = 41;
		int cardLimit = 0;
		int heightMod = 0;
		int weakFoot = 2;
        bool hasTrick = false;
		int targetRate = 0;
		int rating = player.drib;
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
		if(pesVersion>19) rating = max(player.aggres, rating);

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

		//Count A positions
		int countA = 0;
		for (int jj = 0; jj < 13; jj++)
		{
			if (player.play_pos[jj] == 2)
				countA++;
		}

		//Count B positions
		int countB = 0;
		for (int jj = 0; jj < 13; jj++)
		{
			if (player.play_pos[jj] == 1)
				countB++;
		}

		//Can't have GK as second A
        if(countA > 1)
        {
            if(player.play_pos[12] == 2) 
			{
                errorTot++;
				errorMsg << _T("Has GK as second A position; ");
			}
        }

		//No B positions allowed
		if (countB > 0)
		{
			errorTot++;
			errorMsg << _T("No B positions allowed; ");
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
				//Captain gets free captaincy card and stat bonus
				if (jj == 25 && player.id == gteams[teamSel].players[gteams[teamSel].captain_ind])
				{
					cardMod++;
					targetRate += captainStatBonus;
				}
                //Trick cards may be free, count number
                if(jj<6 || jj == 9 || jj==16 || jj == 21 || jj==28 || jj==29 || jj==30 || jj==34)
				{
                    hasTrick = true;
					numTrick++;
				}
            }
        }
		for(int jj=0;jj<7;jj++)
        {
            if(player.com_style[jj])
			{
				cardCount++;
				numCom++;
			}
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
			targetRate += regRate;
			cardMin = regSkillCardsMin;

			weakFoot = 4;

            if(player.form+1 != regForm)
			{
                errorTot++;
				errorMsg << _T("Form is ") << player.form+1 << _T(", should be ") << regForm << _T("; ");
			}
			
            if(player.reg_pos == 0) //GK cannot be in the manlet height bracket
            {
				if (player.height == heightManlet)
				{
					errorTot++;
					errorMsg << _T("GKs cannot be in this height bracket;");
				}
            }

			if (countA > 1)
			{
				errorTot++;
				errorMsg << _T("Only 1 A position for non-medals;");
			}

			cardMod += regCOM; //1 free COM styles
			cardMod += min(trickCards, numTrick); //5 free tricks
			cardLimit = regSkillCardsMax + cardMod; //5 skill cards
            
			if (numCom > regCOM)
			{
				errorTot++;
				errorMsg << _T("Has ") << numCom << _T(" COM playing styles, should be no more than ") << regCOM << _T("; ");
			}

			if (player.injury + 1 != regIR)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury + 1 << _T(", should be ") << regIR << _T("; ");
			}

			if (player.reg_pos == 6 || player.reg_pos == 7 || player.reg_pos == 9 || player.reg_pos == 10)
			{
				heightMod += regWMFHeightBonus;
				targetRate += regWMFStatBonus;
			}
		}
		/* SILVER */
        else if(rating < goldRate-goldGiantPen) //Silver player
        {
            numSilver++;
			targetRate += silverRate;
			cardMin = medalSkillCardsMin;

			weakFoot = 4;

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

			if (countA > 2)
			{
				errorTot++;
				errorMsg << _T("Only 2 A positions for medals;");
			}

            cardMod += min(trickCards, numTrick); //5 free tricks
			cardMod += silverCOM; //3 free COM
			cardLimit = medalSkillCardsMax + cardMod; //6 skill cards

			if (numCom > silverCOM)
			{
				errorTot++;
				errorMsg << _T("Has ") << numCom << _T(" COM playing styles, should be no more than ") << silverCOM << _T("; ");
			}

			if(player.injury+1 != silverIR)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury+1 << _T(", should be ") << silverIR << _T("; ");
			}

			if (player.reg_pos == 9 || player.reg_pos == 10)
			{
				heightMod += silverWFHeightBonus;
				targetRate += silverWFStatBonus;
			}

			if (player.reg_pos == 12 && (player.play_style == 3 || player.play_style == 13))
			{
				heightMod += medalCFTFHeightBonus;
			}
        }
		/* GOLD */
        else //rating == 97 //Gold player
        {
            numGold++;
			targetRate += goldRate;
			cardMin = medalSkillCardsMin;

			weakFoot = 4;

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

			if (countA > 2)
			{
				errorTot++;
				errorMsg << _T("Only 2 A positions for medals;");
			}
			
            cardMod += min(trickCards, numTrick); //5 free tricks
			cardMod += goldCOM; //5 free COMs
			cardLimit = medalSkillCardsMax + cardMod; //6 skill cards

			if (numCom > goldCOM)
			{
				errorTot++;
				errorMsg << _T("Has ") << numCom << _T(" COM playing styles, should be no more than ") << goldCOM << _T("; ");
			}
            
			if(player.injury+1 > goldIR)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury+1 << _T(", should be ") << goldIR << _T("; ");
			}

			if (player.reg_pos == 12 && (player.play_style == 3 || player.play_style == 13))
			{
				heightMod += medalCFTFHeightBonus;
			}
		}

		//Check player height
		if ((player.height - heightMod) == heightManlet)
		{
			numManlet++;
			cardLimit += manletCardBonus; //Manlets get two bonus cards
		}
		else if ((player.height - heightMod) == heightTall)
		{
			numTall++;
			cardLimit += tallCardBonus; //Talls get one bonus card
			if (player.reg_pos == 0)
			{
				errorTot++;
				errorMsg << _T("GK in the ") << heightTall << _T(" cm bracket should have their height increased to ") << heightTallGK << _T(" cm; ");
			}
		}
		else if ((player.height - heightMod) == heightTallGK && player.reg_pos == 0) //GK
		{
			numTall++;
			cardLimit += tallCardBonus; //Talls get one bonus card
		}
		else if ((player.height - heightMod) == heightGiant)
		{
			numGiant++;
			weakFoot = 2;
		}
		else if ((player.height - heightMod) == heightGiga)
		{
			numGiga++;
			weakFoot = 2;
		}
		else
		{
			errorTot++;
			errorMsg << _T("Illegal height (") << player.height << _T(" cm); ");
		}

		//Check weak foot ratings
		if (player.weak_use + 1 != weakFoot)
		{
			errorTot++;
			errorMsg << _T("Weak foot usage > ") << weakFoot << _T("; ");
		}
		if (player.weak_acc + 1 != weakFoot)
		{
			errorTot++;
			errorMsg << _T("Weak foot accuracy > ") << weakFoot << _T("; ");
		}

		//Check player card count
		if (cardCount > cardLimit)
		{
			errorTot++;
			errorMsg << _T("Has ") << cardCount << _T(" cards, only allowed ") << cardLimit << _T("; ");
		}

		if (cardCount - numCom < cardMin)
		{
			errorTot++;
			errorMsg << _T("Has ") << cardCount - numCom << _T(" skill cards, must have at least ") << cardMin << _T("; ");
		}

		//Check PES skill card limit of 10
		if (cardCount - numCom > 10)
		{
			errorTot++;
			errorMsg << _T("Has ") << cardCount - numCom << _T(" skill cards, PES limit is 10; ");
		}

		//Check PES skill card limit of 10
		if (numCom > maxCOM)
		{
			errorTot++;
			errorMsg << _T("Has ") << numCom << _T(" COM playing styles, limit is 5; ");
		}

		//Check player overall rating
		if (rating != targetRate)
		{
			errorTot++;
			errorMsg << _T("Illegal Ability scores; ");
		}

		//Check individual skill ratings
		if(player.drib != targetRate)
        {
            errorTot++;
			errorMsg << _T("Dribbling is ") << player.drib << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.gk != targetRate)
        {
            errorTot++;
			errorMsg << _T("Goalkeeping is ") << player.gk << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.finish != targetRate)
		{
            errorTot++;
			errorMsg << _T("Finishing is ") << player.finish << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.lowpass != targetRate)
		{
            errorTot++;
			errorMsg << _T("Low Pass is ") << player.lowpass << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.loftpass != targetRate)
		{
            errorTot++;
			errorMsg << _T("Lofted Pass is ") << player.loftpass << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.header != targetRate)
		{
            errorTot++;
			errorMsg << _T("Header is ") << player.header << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.swerve != targetRate)
		{
            errorTot++;
			errorMsg << _T("Swerve is ") << player.swerve << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.catching != targetRate)
		{
            errorTot++;
			errorMsg << _T("Catching is ") << player.catching << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.clearing != targetRate)
		{
            errorTot++;
			errorMsg << _T("Clearing is ") << player.clearing << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.reflex != targetRate)
		{
            errorTot++;
			errorMsg << _T("Reflexes is ") << player.reflex << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.body_ctrl != targetRate)
		{
            errorTot++;
			errorMsg << _T("Body Control is ") << player.body_ctrl << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.phys_cont != targetRate && pesVersion!=16) //Not in 16
		{
            errorTot++;
			errorMsg << _T("Physical Contact is ") << player.phys_cont << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.kick_pwr != targetRate)
		{
            errorTot++;
			errorMsg << _T("Kicking Power is ") << player.kick_pwr << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.exp_pwr != targetRate)
		{
            errorTot++;
			errorMsg << _T("Explosive Power is ") << player.exp_pwr << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.ball_ctrl != targetRate)
		{
            errorTot++;
			errorMsg << _T("Ball Control is ") << player.ball_ctrl << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.ball_win != targetRate)
		{
            errorTot++;
			errorMsg << _T("Ball winning is ") << player.ball_win << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.jump != targetRate)
		{
            errorTot++;
			errorMsg << _T("Jump is ") << player.jump << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.cover != targetRate)
		{
            errorTot++;
			errorMsg << _T("Coverage is ") << player.cover << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.place_kick != targetRate)
		{
            errorTot++;
			errorMsg << _T("Place Kicking is ") << player.place_kick << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.stamina != targetRate)
		{
            errorTot++;
			errorMsg << _T("Stamina is ") << player.stamina << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.speed != targetRate)
		{
            errorTot++;
			errorMsg << _T("Speed is ") << player.speed << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.atk != targetRate)
		{
            errorTot++;
			errorMsg << _T("Attacking Prowess is ") << player.atk << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.def != targetRate)
		{
            errorTot++;
			errorMsg << _T("Defensive Prowess is ") << player.def << _T(", should be ") << targetRate << _T("; ");
        }
		if(pesVersion>19 && player.tight_pos != targetRate)
		{
            errorTot++;
			errorMsg << _T("Tight Possession is ") << player.tight_pos << _T(", should be ") << targetRate << _T("; ");
        }
		if(pesVersion>19 && player.aggres != targetRate)
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
    
	msgOut+=_T("Checking for team-level errors.\r\n");
	if (diff = giga - numGiga)
	{
		if (diff > 0)
		{
			errorTot += diff;
		}
		else
		{
			errorTot -= diff;
		}
		errorMsg << _T("Has ") << numGiga << _T("/") << giga << _T(" ") << heightGiga << _T("cm players; ");
	}
    if(diff = giant - numGiant)
    {
        if(diff>0)
        {
            errorTot += diff;
        }
        else
        {
            errorTot -= diff;
        }
		errorMsg << _T("Has ") << numGiant << _T("/") << giant << _T(" ") << heightGiant << _T("cm players; ");
    }
    if(diff = tall - numTall)
    {
        if(diff>0)
        {
            errorTot += diff;
        }
        else
        {
            errorTot -= diff;
        }
		errorMsg << _T("Has ") << numTall << _T("/") << tall << _T(" ") << heightTall << _T("/") << heightTallGK << _T("cm players; ");
    }
	if (diff = manlet - numManlet)
	{
		if (diff > 0)
		{
			errorTot += diff;
		}
		else
		{
			errorTot -= diff;
		}
		errorMsg << _T("Has ") << numManlet << _T("/") << manlet << _T(" ") << heightManlet << _T("cm players; ");
	}
	if (diff = gk - numGK)
	{
		if (diff > 0)
		{
			errorTot += diff;
		}
		else
		{
			errorTot -= diff;
		}
		errorMsg << _T("Has ") << numGK << _T("/") << gk << _T(" GKs; ");
	}
    

  //  else //Using Red height system
  //  {
		//msgOut+=_T("Using Red height system\r\n");
		//if (diff = numGiga)
		//{
		//	errorTot += diff;
		//	errorMsg << _T("Has ") << numGiga << _T("/") << redGiga << _T(" ") << heightGiga << _T("cm players; ");
		//}
  //      if(diff = numGiant)
  //      {
  //          errorTot += diff;
		//	errorMsg << _T("Has ") << numGiant << _T("/") << redGiant << _T(" ") << heightGiant << _T("cm players; ");
  //      }
  //      if(diff = redTall - numTall)
  //      {
  //          if(diff>0)
  //          {
  //              errorTot += diff;
  //          }
  //          else
  //          {
  //              errorTot -= diff;
  //          }
		//	errorMsg << _T("Has ") << numTall << _T("/") << redTall << _T(" ") << heightTall << _T("/") << heightTallGK << _T("cm players; ");
  //      }
  //      if(diff = redMid - numMid)
  //      {
  //          if(diff>0)
  //          {
  //              errorTot += diff;
  //          }
  //          else
  //          {
  //              errorTot -= diff;
  //          }
		//	errorMsg << _T("Has ") << numMid << _T("/") << redMid << _T(" ") << heightMid << _T("cm players; ");
  //      }
  //      if(diff = redManlet - numManlet)
  //      {
  //          if(diff>0)
  //          {
  //              errorTot += diff;
  //          }
  //          else
  //          {
  //              errorTot -= diff;
  //          }
		//	errorMsg << _T("Has ") << numManlet << _T("/") << redManlet << _T(" ") << heightManlet << _T("cm players; ");
  //      }
  //  }
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
		SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM) _T("You are a sussy baka."));
	else
		SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM) _T("Straight bussin fr fr"));
}
