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
	int manletCardBonus = 0;
	int tallCardBonus = 0;

	int maxNumNMWMFBuffed = 0;
	int numNMWMFBuffed = 0;
	int numNMWMFBuffEligible = 0;

	int regWMFStatBonus = 0;
	int silverWFStatBonus = 0;
	int captainStatBonus = 1;

	int nmSilverTallDFBonus = 0;
	int nmManletBEDKSFBonus = 0;

	int regWMFHeightBonus = 0;
	int silverWFHeightBonus = 0;
	int medalCFTFHeightBonus = 0;
	int medalCFTFootedness = 4;
	int medalCFTHeightBonus = 0;

	int gigaFootedness = 4;
	int giantFootedness = 4;

	int goldRate = 97;
	int silverRate = 87;
	int regRate = 77;
	int gkRate = 77;
	int reqNumGold = 2;
	int reqNumSilver = 2;

	int goldForm = 8;
	int silverForm = 8;
	int regForm = 4;
	int gkForm = 7;

	int goldIR = 1; //Injury resistance
	int silverIR = 1;
	int regIR = 1;

	int silverDP = 6;
	int silverOP = 6;
	int silverST = 0;
	int silverS = -3;
	int goldS = -7;
	int goldEP = -3;
	int nmGCCR = 0;
	int nmGCR = 0;
	int nmOFLLBK = 0;
	int nmOP = 11;
	int nmF = 18;
	int nmLWP = 0;
	int nmLOP = 0;
	int nmBC = 5;
	int nmCle = 5;
	int nmD = 5;
	int nmKP = 5;
	int nmBW = 5;
	int nmDP = 8;
	int nmEP = 8;
	int nmST = -5;
	int nmCov = -5;
	int nmR = -5;
	int nmCat = 5;
	int nmBase = 0;
	int nmBCDP = 0;

	int freeAPositions = 3;

	int regSkillCardsMin = 4;
	int medalSkillCardsMin = 4;

	int regSkillCardsMax = 6;
	int medalSkillCardsMax = 6;

	int trickCards = 5;

	int regCOM = 2;
	int silverCOM = 2;
	int goldCOM = 1;

	int maxCOM = 5;

	int gk = 2;

	int nmAllowedHeight = 189;
	int silverAllowedHeight = 185;
	int goldAllowedHeight = 183;

	/*int giga = 2;
	int giant = 7;
	int tall = 8;
	int manlet = 6;

	int maxHeight = 210;
	int heightGiga = 200;
	int heightGiant = 187;
	int heightTall = 180;
	int heightTallGK = 184;
	int heightManlet = 175;*/
	

	int manletBonus0 = 0;
	int manletBonus1 = 0;
	int tallBonus = 0;
	int tallFDBonus = 0;
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

	/*int greenGiga = 3;
	int greenGiant = 6;
	int greenTall = 4;
	int greenMid = 5;
	int greenManlet = 5;

	int redGiga = 0;
	int redGiant = 0;
	int redTall = 10;
	int redMid = 7;
	int redManlet = 6;*/

	//int heightMid = 170;

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
		int rating = player.jump;
        /*rating = max(player.gk, rating);
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

		/*if (countB > 0 && player.reg_pos != 0 && player.play_pos[12] == 1)
		{
			errorTot++;
			errorMsg << _T("No B position GK allowed on non-GKs; ");
		}

		if (countB + countA != 12 && player.reg_pos != 0)
		{
			errorTot++;
			errorMsg << _T("No C position allowed on outfielders outside of GK position; ");
		}*/

		if (countB > 0)
		{
			errorTot++;
			errorMsg << _T("No B position allowed; ");
		}

		//if (player.play_style == 2 && player.play_pos[1] == 2)
		//{
		//	errorTot++;
		//	errorMsg << _T("Dummy Runner playstyle may not be used with player with A position in SS; ");
		//}

		if (player.play_style == 1)
		{
			errorTot++;
			errorMsg << _T("Goal Poacher playstyle may not be used with any player; ");
		}

		//No B positions allowed
		/*if (countB > 0)
		{
			errorTot++;
			errorMsg << _T("No B positions allowed; ");
		}*/

		//Count cards
		int numTrick = 0;
		int numCom = 0;
		int numSkill = 0;
		bool isCaptain = false;
		int freeCOMs = 0;
		int totalSkills;
		bool NMWMFBuffed = false;
		bool medalCFTBuff = false;
		bool isSilver = false;
		bool isGold = false;
		int DFBonus = 0;
		int BEDKSFBonus = 0;
		int DPBonus = 0;
		int GCCRBonus = 0;
		int GCRBonus = 0;
		int FBonus = 0;
		int FDBonus = 0;
		//int OFLLBKBonus = 0;
		int baseBonus = 0;
		int BCDPBonus = 0;
		int SBonus = 0;
		int OPBonus = 0;
		int LWPBonus = 0;
		int LOPBonus = 0;
		int BCBonus = 0;
		int KPBonus = 0;
		int STBonus = 0;
		int EPBonus = 0;
		int CleBonus = 0;
		int DBonus = 0;
		int CovBonus = 0;
		int RBonus = 0;
		int BWBonus = 0;
		int CatBonus = 0;

		int allowedHeight = 0;

		if(pesVersion==19) totalSkills =39;
		else if(pesVersion>19) totalSkills =41;
		else totalSkills =28;
        for(int jj=0;jj< totalSkills;jj++)
        {
            if(player.play_skill[jj])
            {
                cardCount++;
				//Captain gets free captaincy card and stat bonus
				if (jj == 25 && player.id == gteams[teamSel].players[gteams[teamSel].captain_ind])
				{
					cardMod += 2;
					targetRate += captainStatBonus;
					isCaptain = true;
				}
                //Trick cards may be free, count number
                if(jj<6 || jj == 9 || jj == 21 || jj==28 || jj==29 || jj==30 || jj==34 || jj == 11 || jj == 12)
				{
                    hasTrick = true;
					numTrick++;
				}
				else
				{
					numSkill++;
				}

				//Track Back not allowed with CF, AMF or CMF
				if (jj == 23 && (player.play_pos[6] == 2 || player.play_pos[11] == 2 || player.play_pos[10] == 2 || player.play_pos[0] == 2))
				{
					errorTot++;
					errorMsg << _T("Can't use Track Back card on player with A positions on CF, CMF, LB or RB; ");
				}

				if (jj == 19)
				{
					errorTot++;
					errorMsg << _T("Long Throw card is not allowed; ");
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

		if (player.id == gteams[teamSel].players[gteams[teamSel].captain_ind] && !isCaptain)
		{
			cardMod++;
			targetRate += captainStatBonus;
			isCaptain = true;
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

			GCCRBonus += nmGCCR;
			GCRBonus += nmGCR;
			baseBonus += nmBase;
			//OFLLBKBonus += nmOFLLBK;

			FBonus += nmF;
			OPBonus += nmOP;
			LWPBonus += nmLWP;
			LOPBonus += nmLOP;
			BCBonus += nmBC;
			KPBonus += nmKP;
			DPBonus += nmDP;
			CleBonus += nmCle;
			DBonus += nmD;
			EPBonus += nmEP;
			STBonus += nmST;
			CovBonus += nmCov;
			RBonus += nmR;
			BWBonus += nmBW;
			CatBonus += nmCat;

			allowedHeight = nmAllowedHeight;

			if (isCaptain)
			{
				errorTot++;
				errorMsg << _T("Regulars can't be captain; ");
			}

			if (player.reg_pos == 0 && player.form + 1 != gkForm)
			{
				errorTot++;
				errorMsg << _T("Form is ") << player.form + 1 << _T(", should be ") << gkForm << _T("; ");
			}
            else if(player.reg_pos != 0 && player.form+1 != regForm)
			{
                errorTot++;
				errorMsg << _T("Form is ") << player.form+1 << _T(", should be ") << regForm << _T("; ");
			}
			

			/*if (countA > 1)
			{
				errorTot++;
				errorMsg << _T("Only 1 A position for non-medals;");
			}*/

			cardMod += min(regCOM, numCom); //1 free COM styles
			cardMod += numTrick;
			cardLimit = regSkillCardsMax + cardMod; //5 skill cards
			freeCOMs = regCOM;

			/*if (numCom > regCOM)
			{
				errorTot++;
				errorMsg << _T("Has ") << numCom << _T(" COM playing styles, should be no more than ") << regCOM << _T("; ");
			}*/

			if (player.injury + 1 != regIR)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury + 1 << _T(", should be ") << regIR << _T("; ");
			}

			if (player.reg_pos == 6 || player.reg_pos == 7 || player.reg_pos == 9 || player.reg_pos == 10)
			{
				NMWMFBuffed = true;
				numNMWMFBuffEligible++;
				heightMod += regWMFHeightBonus;
				targetRate += regWMFStatBonus;
			}
		}
		/* SILVER */
        else if(rating < goldRate-goldGiantPen) //Silver player
        {
			isSilver = true;
            numSilver++;
			targetRate += silverRate;
			cardMin = medalSkillCardsMin;

			weakFoot = 4;

			DPBonus += silverDP;
			OPBonus += silverOP;
			SBonus += silverS;
			STBonus += silverST;

			allowedHeight = silverAllowedHeight;

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

			/*if (countA > 2)
			{
				errorTot++;
				errorMsg << _T("Only 2 A positions for medals;");
			}*/

            cardMod += min(trickCards, numTrick); //5 free tricks
			cardMod += min(silverCOM, numCom); //3 free COM
			cardLimit = medalSkillCardsMax + cardMod; //6 skill cards
			freeCOMs = silverCOM;

			/*if (numCom > silverCOM)
			{
				errorTot++;
				errorMsg << _T("Has ") << numCom << _T(" COM playing styles, should be no more than ") << silverCOM << _T("; ");
			}*/

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

			/*if (player.reg_pos == 12 && (player.play_style == 3 || player.play_style == 13))
			{
				heightMod += medalCFTFHeightBonus;
				if (player.play_style == 13)
				{
					medalCFTBuff = true;
				}
			}*/
        }
		/* GOLD */
        else //rating == 97 //Gold player
        {
			isGold = true;
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

			/*if (countA > 2)
			{
				errorTot++;
				errorMsg << _T("Only 2 A positions for medals;");
			}*/

			SBonus += goldS;
			EPBonus += goldEP;

			
			allowedHeight = goldAllowedHeight;
			
            cardMod += min(trickCards, numTrick); //5 free tricks
			cardMod += min(goldCOM, numCom); //5 free COMs
			cardLimit = medalSkillCardsMax + cardMod; //6 skill cards
			freeCOMs = goldCOM;

			/*if (numCom > goldCOM)
			{
				errorTot++;
				errorMsg << _T("Has ") << numCom << _T(" COM playing styles, should be no more than ") << goldCOM << _T("; ");
			}*/
            
			if(player.injury+1 > goldIR)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury+1 << _T(", should be ") << goldIR << _T("; ");
			}

			if (player.reg_pos == 12 && player.play_style == 13)
			{
				heightMod += medalCFTHeightBonus;
				if (player.play_style == 13)
				{
					medalCFTBuff = true;
				}
			}
		}

		if (player.height != allowedHeight)
		{
			errorTot++;
			errorMsg << _T("Wrong height, allowed height is: ") << allowedHeight << _T("; ");
		}

		int neutralModHeight = player.height - heightMod;
		int debuffedModHeight = player.height - heightMod + regWMFHeightBonus;
		int confirmedNMWMFBuff = false;


		if (medalCFTBuff)
		{
			weakFoot = medalCFTFootedness;
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
		/*errorMsg << _T("Has ") << confirmedNMWMFBuff << (player.reg_pos == 9) << player.play_pos[8];
		errorMsg << _T("Has ") << player.play_pos[0];CF
		errorMsg << _T("Has ") << player.play_pos[1];SS
		errorMsg << _T("Has ") << player.play_pos[2];LWF
		errorMsg << _T("Has ") << player.play_pos[3];RWF
		errorMsg << _T("Has ") << player.play_pos[4];AMF
		errorMsg << _T("Has ") << player.play_pos[5];DMF
		errorMsg << _T("Has ") << player.play_pos[6];CMF
		errorMsg << _T("Has ") << player.play_pos[7];LMF
		errorMsg << _T("Has ") << player.play_pos[8];RMF
		errorMsg << _T("Has ") << player.play_pos[9];CB
		errorMsg << _T("Has ") << player.play_pos[10];LB
		errorMsg << _T("Has ") << player.play_pos[11];RB
		errorMsg << _T("Has ") << player.play_pos[12];GK*/

		int cardsSwappedForAPositions = countA - freeAPositions;
		bool usingNMWMFAPos = confirmedNMWMFBuff && (
			(player.reg_pos == 6 && player.play_pos[2] == 2) ||
			(player.reg_pos == 7 && player.play_pos[3] == 2) ||
			(player.reg_pos == 9 && player.play_pos[7] == 2) ||
			(player.reg_pos == 10 && player.play_pos[8] == 2)
			);

		if (confirmedNMWMFBuff)
		{
			if (player.play_pos[9] == 2 || player.play_pos[10] == 2 || player.play_pos[11] == 2)
			{
				errorTot++;
				errorMsg << _T("No LB, CB or RB A positions for buffed LWF, RWF, LMF, RMF non-medals; ");
			}
		}

		if (usingNMWMFAPos)
		{
			cardsSwappedForAPositions--;
		}

		if (countA > freeAPositions + max(0, cardLimit - cardCount))
		{
			if (usingNMWMFAPos)
			{
				if (countA > freeAPositions + max(0, cardLimit - cardCount) + 1)
				{
					errorTot++;
					errorMsg << _T("Has ") << countA << _T(" A positions, only allowed ") << freeAPositions + max(0, cardLimit - cardCount) + 1 << _T(". Remove cards to add A position slots; ");
				}
			}
			else if (countA > freeAPositions + max(0, cardLimit - cardCount))
			{
				errorTot++;
				errorMsg << _T("Has ") << countA << _T(" A positions, only allowed ") << freeAPositions + max(0, cardLimit - cardCount) << _T(". Remove cards to add A position slots; ");
			}
		}

		if (player.reg_pos == 0 || cardsSwappedForAPositions < 0)
		{
			cardsSwappedForAPositions = 0;
		}


		if (cardCount - min(freeCOMs, numCom) - numTrick < cardMin - cardsSwappedForAPositions)
		{
			errorTot++;
			errorMsg << _T("Has ") << cardCount - min(freeCOMs, numCom) - numTrick << _T(" skill cards, must have at least ") << cardMin - cardsSwappedForAPositions << _T("; ");
		}

		//Check PES skill card limit of 10
		if (cardCount - numCom > 10)
		{
			errorTot++;
			errorMsg << _T("Has ") << cardCount - numCom << _T(" skill cards, PES limit is 10; ");
		}

		//Check COM hard cap
		if (numCom > maxCOM)
		{
			errorTot++;
			errorMsg << _T("Has ") << numCom << _T(" COM playing styles, limit is 5; ");
		}

		if (NMWMFBuffed && !confirmedNMWMFBuff) {
			targetRate -= regWMFStatBonus;
		}

		//Check player overall rating
		if (rating != targetRate)
		{
			errorTot++;
			errorMsg << _T("Illegal Ability scores; ");
		}

		//Check individual skill ratings

		if(player.drib != targetRate + FDBonus + BEDKSFBonus + baseBonus + DBonus)
        {
            errorTot++;
			errorMsg << _T("Dribbling is ") << player.drib << _T(", should be ") << targetRate + FDBonus + BEDKSFBonus + baseBonus + DBonus << _T("; ");
        }
        if(player.gk != targetRate + GCCRBonus + GCRBonus)
        {
            errorTot++;
			errorMsg << _T("Goalkeeping is ") << player.gk << _T(", should be ") << targetRate + GCCRBonus + GCRBonus << _T("; ");
        }
        if(player.finish != targetRate + FBonus + FDBonus + BEDKSFBonus)
		{
            errorTot++;
			errorMsg << _T("Finishing is ") << player.finish << _T(", should be ") << targetRate + FBonus + FDBonus + BEDKSFBonus << _T("; ");
        }
        if(player.lowpass != targetRate + LWPBonus)
		{
            errorTot++;
			errorMsg << _T("Low Pass is ") << player.lowpass << _T(", should be ") << targetRate + LWPBonus << _T("; ");
        }
        if(player.loftpass != targetRate + LOPBonus)
		{
            errorTot++;
			errorMsg << _T("Lofted Pass is ") << player.loftpass << _T(", should be ") << targetRate + LOPBonus << _T("; ");
        }
        if(player.header != targetRate + baseBonus)
		{
            errorTot++;
			errorMsg << _T("Header is ") << player.header << _T(", should be ") << targetRate + baseBonus << _T("; ");
        }
        if(player.swerve != targetRate + SBonus)
		{
            errorTot++;
			errorMsg << _T("Swerve is ") << player.swerve << _T(", should be ") << targetRate + SBonus << _T("; ");
        }
        if(player.catching != targetRate + GCCRBonus + GCRBonus + CatBonus)
		{
            errorTot++;
			errorMsg << _T("Catching is ") << player.catching << _T(", should be ") << targetRate + GCCRBonus + GCRBonus + CatBonus << _T("; ");
        }
        if(player.clearing != targetRate + GCCRBonus + GCRBonus + baseBonus + CleBonus)
		{
            errorTot++;
			errorMsg << _T("Clearing is ") << player.clearing << _T(", should be ") << targetRate + GCCRBonus + GCRBonus + baseBonus + CleBonus << _T("; ");
        }
        if(player.reflex != targetRate + GCCRBonus + baseBonus + RBonus)
		{
            errorTot++;
			errorMsg << _T("Reflexes is ") << player.reflex << _T(", should be ") << targetRate + GCCRBonus + baseBonus + RBonus << _T("; ");
        }
        if(player.body_ctrl != targetRate + BCDPBonus)
		{
            errorTot++;
			errorMsg << _T("Body Control is ") << player.body_ctrl << _T(", should be ") << targetRate + BCDPBonus << _T("; ");
        }
        if(player.phys_cont != targetRate && pesVersion!=16) //Not in 16
		{
            errorTot++;
			errorMsg << _T("Physical Contact is ") << player.phys_cont << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.kick_pwr != targetRate + baseBonus + KPBonus)
		{
            errorTot++;
			errorMsg << _T("Kicking Power is ") << player.kick_pwr << _T(", should be ") << targetRate + baseBonus + KPBonus << _T("; ");
        }
        if(player.exp_pwr != targetRate + BEDKSFBonus + baseBonus + EPBonus)
		{
            errorTot++;
			errorMsg << _T("Explosive Power is ") << player.exp_pwr << _T(", should be ") << targetRate + BEDKSFBonus + baseBonus + EPBonus << _T("; ");
        }
        if(player.ball_ctrl != targetRate + baseBonus + BCBonus)
		{
            errorTot++;
			errorMsg << _T("Ball Control is ") << player.ball_ctrl << _T(", should be ") << targetRate + baseBonus + BCBonus << _T("; ");
        }
        if(player.ball_win != targetRate + baseBonus + BWBonus)
		{
            errorTot++;
			errorMsg << _T("Ball winning is ") << player.ball_win << _T(", should be ") << targetRate + baseBonus + BWBonus << _T("; ");
        }
        if(player.jump != targetRate + baseBonus)
		{
            errorTot++;
			errorMsg << _T("Jump is ") << player.jump << _T(", should be ") << targetRate + baseBonus << _T("; ");
        }
        if(player.cover != targetRate + CovBonus)
		{
            errorTot++;
			errorMsg << _T("Coverage is ") << player.cover << _T(", should be ") << targetRate + CovBonus << _T("; ");
        }
        if(player.place_kick != targetRate + baseBonus)
		{
            errorTot++;
			errorMsg << _T("Place Kicking is ") << player.place_kick << _T(", should be ") << targetRate + baseBonus << _T("; ");
        }
        if(player.stamina != targetRate + baseBonus + STBonus)
		{
            errorTot++;
			errorMsg << _T("Stamina is ") << player.stamina << _T(", should be ") << targetRate + baseBonus + STBonus << _T("; ");
        }
        if(player.speed != targetRate + BEDKSFBonus + baseBonus)
		{
            errorTot++;
			errorMsg << _T("Speed is ") << player.speed << _T(", should be ") << targetRate + BEDKSFBonus + baseBonus << _T("; ");
        }
        if(player.atk != targetRate + OPBonus)
		{
            errorTot++;
			errorMsg << _T("Attacking Prowess is ") << player.atk << _T(", should be ") << targetRate + OPBonus << _T("; ");
        }
        if(player.def != targetRate + DPBonus + BCDPBonus)
		{
            errorTot++;
			errorMsg << _T("Defensive Prowess is ") << player.def << _T(", should be ") << targetRate + DPBonus + BCDPBonus << _T("; ");
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
	if (numNMWMFBuffed > maxNumNMWMFBuffed) 
	{
		errorTot += numNMWMFBuffed - maxNumNMWMFBuffed;
		errorMsg << _T("Has ") << numNMWMFBuffed << _T("/") << maxNumNMWMFBuffed << _T(" buffed LWF, RWF, LMF, RMF non-medals; ");
	}
	
	if (numNMWMFBuffed < maxNumNMWMFBuffed && numNMWMFBuffed < numNMWMFBuffEligible)
	{
		errorTot += numNMWMFBuffEligible - numNMWMFBuffed;
		errorMsg << _T("Has ") << numNMWMFBuffed << _T("/") << maxNumNMWMFBuffed << _T(" buffed LWF, RWF, LMF, RMF non-medals, missing ") << numNMWMFBuffEligible - numNMWMFBuffed << _T(" buffed non-medals. Check the height or stats of LWF, RWF, LMF, RMF non-medals.");
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
		SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM) _T("KWAB"));
	else
		SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM) _T("Your oshi is proud of you"));
}
