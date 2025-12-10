#include <string>
#include <sstream>
#include "editor.h"
#include "resource.h"
#include "stats.h"
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
	/*
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

	int goldRate = 95;
	int silverRate = 87;
	int regRate = 77;
	int gkRate = 77;
	int reqNumGold = 2;
	int reqNumSilver = 2;

	int goldForm = 8;
	int silverForm = 8;
	int regForm = 4;
	int gkForm = 8;

	int goldIR = 1; //Injury resistance
	int silverIR = 1;
	int regIR = 1;

	int silverDP = 5;
	int silverOP = 0;
	int silverST = 0;
	int silverS = -5;
	int goldS = -5;
	int goldEP = -5;
	int goldBW = -5;
	int goldST = 2;
	int goldSP = -2;
	int nmGCCR = 0;
	int nmGCR = 0;
	int nmOFLLBK = 0;
	int nmOP = 8;
	int nmF = 8;
	int nmLWP = 0;
	int nmLOP = 0;
	int nmBC = 5;
	int nmCle = 5;
	int nmD = 0;
	int nmKP = 5;
	int nmBW = 8;
	int nmDP = 10;
	int nmEP = 8;
	int nmST = -5;
	int nmCov = -5;
	int nmR = 0;
	int nmCat = 5;
	int nmBodC = 5;
	int nmJ = 5;
	int nmBase = 0;
	int nmBCDP = 0;

	int freeAPositions = 2;
	*/
	int regSkillCardsMin = 3;
	int medalSkillCardsMin = 3;
	/*
	int regSkillCardsMax = 5;
	int medalSkillCardsMax = 5;

	int trickCards = 5;

	int regCOM = 1;
	int silverCOM = 1;
	int goldCOM = 1;
	*/
	int maxCOM = 5;

	int gk = 2;

	//int nmAllowedHeight = 191;
	//int silverAllowedHeight = 182;
	//int goldAllowedHeight = 179;

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
	
	/*
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
	*/
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
	int numBuff = 0;
    int numSilver = 0;
    int numGold = 0;
    //Count of height brackets
	int numGiga = 0;
    int numGiant = 0;
    int numTall = 0;
    int numMid = 0;
    int numManlet = 0;
    //bool usingRed = true;
	//buff positions used
	int buffPosition1 = -1;
	int buffPosition2 = -1;
	int buffPosition3 = -1;

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
		bool hasTrickCom = false;
		int targetRate = 0;
		int rating = player.clearing; //this needs to be a stat that isn't changed from base rates


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

		/*if (player.play_style == 1)
		{
			errorTot++;
			errorMsg << _T("Goal Poacher playstyle may not be used with any player; ");
		}*/

		//No B positions allowed
		/*if (countB > 0)
		{
			errorTot++;
			errorMsg << _T("No B positions allowed; ");
		}*/

		//Count cards
		int numTrick = 0;
		int numTrickCom = 0;
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
		int targetDrib = 0;
		int targetGk = 0;
		int targetFinish = 0;
		int targetLowpass = 0;
		int targetLoftpass = 0;
		int targetHeader = 0;
		int targetSwerve = 0;
		int targetCatching = 0;
		int targetClearing = 0;
		int targetReflex = 0;
		int targetBody_ctrl = 0;
		int targetPhys_cont = 0;
		int targetKick_pwr = 0;
		int targetExp_pwr = 0;
		int targetBall_ctrl = 0;
		int targetBall_win = 0;
		int targetJump = 0;
		int targetCover = 0;
		int targetPlace_kick = 0;
		int targetStamina = 0;
		int targetSpeed = 0;
		int targetAtk = 0;
		int targetDef = 0;
		int targetTight_pos = 0;
		int targetAggres = 0;



		int freeAPositions = 0;
		int allowedHeight = 0;

		if(pesVersion==19) totalSkills =39;
		else if(pesVersion>19) totalSkills =41;
		else totalSkills =28;
        for(int jj=0;jj< totalSkills;jj++)
        {
			if (jj == 21 && player.play_skill[jj] == 0) //player does not have malicia
			{
				errorTot++;
				errorMsg << _T("The Malicia card is required; ");
			}
            if(player.play_skill[jj])
            {
                cardCount++;
				//Captain gets free captaincy card and stat bonus
				if (jj == 25 && player.id == gteams[teamSel].players[gteams[teamSel].captain_ind])
				{
					cardMod += 1;
					//targetRate += captainStatBonus;
					isCaptain = true;
				}
				//buffed players can take one touch pass and weighted pass for free
				if ((jj == 12 || jj == 13) && player.height == buffed::height)
				{
					hasTrick = true;
					numTrick++;
				}
                //Trick cards may be free, count number
                if(jj<6 || jj == 9 || jj==11|| jj == 21 || jj==28 || jj==29 || jj==30 || jj==34 )
				{
                    hasTrick = true;
					numTrick++;
				}
				else
				{
					numSkill++;
				}

				//Track Back not allowed with CF, AMF or CMF
				/*if (jj == 23 && (player.play_pos[0] == 2 || player.play_pos[6] == 2 || player.play_pos[11] == 2 || player.play_pos[10] == 2))
				{
					errorTot++;
					errorMsg << _T("Can't use Track Back card on player with A positions on CF, CMF, LB or RB; ");
				}

				if (jj == 19)
				{
					errorTot++;
					errorMsg << _T("Long Throw card is not allowed; ");
				}*/
            }
        }
		for (int jj = 0;jj < 7;jj++)
		{
			if (player.com_style[jj])
			{
				numCom++;
				if (jj ==3 || jj == 6) //incisive run and long ranger are free
				{
					hasTrickCom = true;
					numTrickCom++;
				}
			}
		}

		if (player.id == gteams[teamSel].players[gteams[teamSel].captain_ind] && !isCaptain)
		{
			//cardMod++;
			//targetRate += captainStatBonus;
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
		if(player.height==nm::height || player.height==nm::gk_height) //Regular player
        {
			using namespace nm; // all values pulling from the nm namespace
			numReg++;
			targetRate += base_stat;
			cardMin = regSkillCardsMin;

			weakFoot = weak_foot_usage;



			//set the targets to the namespace values. note some of these are 0 as they should be base rate
			targetDrib = dribbling;
			targetGk = gk_awareness;
			targetFinish = finishing;
			targetLowpass = low_pass;
			targetLoftpass = lofted_pass;
			targetHeader = header;
			targetSwerve = curl;
			targetCatching = catching;
			targetClearing = clearing;
			targetReflex = reflexes;
			targetBody_ctrl = balance;
			targetPhys_cont = physical_contact;
			targetKick_pwr = kicking_power;
			targetExp_pwr = acceleration;
			targetBall_ctrl = ball_control;
			targetBall_win = ball_winning;
			targetJump = jump;
			targetCover = gk_reach;
			targetPlace_kick = place_kicking;
			targetStamina = stamina;
			targetSpeed = speed;
			targetAtk = offensive_awareness;
			targetDef = defensive_awareness;
			targetTight_pos = tight_possession;
			targetAggres = aggression;
			//fix all the 0 values and make them the base rate
			if (targetDrib == 0)
			{
				targetDrib = base_stat;
			}
			if (targetGk == 0)
			{
				targetGk = base_stat;
			}
			if (targetFinish == 0)
			{
				targetFinish = base_stat;
			}
			if (targetLowpass == 0)
			{
				targetLowpass = base_stat;
			}
			if (targetLoftpass == 0)
			{
				targetLoftpass = base_stat;
			}
			if (targetHeader == 0)
			{
				targetHeader = base_stat;
			}
			if (targetSwerve == 0)
			{
				targetSwerve = base_stat;
			}
			if (targetCatching == 0)
			{
				targetCatching = base_stat;
			}
			if (targetClearing == 0)
			{
				targetClearing = base_stat;
			}
			if (targetReflex == 0)
			{
				targetReflex = base_stat;
			}
			if (targetBody_ctrl == 0)
			{
				targetBody_ctrl = base_stat;
			}
			if (targetPhys_cont == 0)
			{
				targetPhys_cont = base_stat;
			}
			if (targetKick_pwr == 0)
			{
				targetKick_pwr = base_stat;
			}
			if (targetExp_pwr == 0)
			{
				targetExp_pwr = base_stat;
			}
			if (targetBall_ctrl == 0)
			{
				targetBall_ctrl = base_stat;
			}
			if (targetBall_win == 0)
			{
				targetBall_win = base_stat;
			}
			if (targetJump == 0)
			{
				targetJump = base_stat;
			}
			if (targetCover == 0)
			{
				targetCover = base_stat;
			}
			if (targetPlace_kick == 0)
			{
				targetPlace_kick = base_stat;
			}
			if (targetStamina == 0)
			{
				targetStamina = base_stat;
			}
			if (targetSpeed == 0)
			{
				targetSpeed = base_stat;
			}
			if (targetAtk == 0)
			{
				targetAtk = base_stat;
			}
			if (targetDef == 0)
			{
				targetDef = base_stat;
			}
			if (targetTight_pos == 0)
			{
				targetTight_pos = base_stat;
			}
			if (targetAggres == 0)
			{
				targetAggres = base_stat;
			}

			freeAPositions = free_a;

			allowedHeight = height;
			if (player.reg_pos == 0) //player is a gk, use gk height
			{
				allowedHeight = gk_height;
			}

			if (isCaptain)
			{
				errorTot++;
				errorMsg << _T("Regulars can't be captain; ");
			}

			if (player.reg_pos == 0 && player.form + 1 != gk_form)
			{
				errorTot++;
				errorMsg << _T("Form is ") << player.form + 1 << _T(", should be ") << gk_form << _T("; ");
			}
            else if(player.reg_pos != 0 && player.form+1 != form)
			{
                errorTot++;
				errorMsg << _T("Form is ") << player.form+1 << _T(", should be ") << form << _T("; ");
			}
			

			/*if (countA > 1)
			{
				errorTot++;
				errorMsg << _T("Only 1 A position for non-medals;");
			}*/

			//cardMod += min(nm::free_coms, numCom-numTrickCom); 
			cardMod += numTrick;
			cardLimit = skills + cardMod;
			freeCOMs = nm::free_coms;

			/*if (numCom > regCOM)
			{
				errorTot++;
				errorMsg << _T("Has ") << numCom << _T(" COM playing styles, should be no more than ") << regCOM << _T("; ");
			}*/

			if (player.injury + 1 != injury_resistance)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury + 1 << _T(", should be ") << injury_resistance << _T("; ");
			}

			/*if (player.reg_pos == 6 || player.reg_pos == 7 || player.reg_pos == 9 || player.reg_pos == 10)
			{
				NMWMFBuffed = true;
				numNMWMFBuffEligible++;
				heightMod += regWMFHeightBonus;
				targetRate += regWMFStatBonus;
			}*/
		}
		/* Buffed */
		else if (player.height == buffed::height) //buffed player
		{
			using namespace buffed; // all values pulling from the buffed namespace
			numBuff++;
			targetRate += base_stat;
			cardMin = regSkillCardsMin;

			weakFoot = weak_foot_usage;
			if (player.play_pos[10]==2||player.play_pos[11]==2||player.play_pos[6] == 2||player.play_pos[5]==2) //playable at LB, RB, CMF, or DMF
			{
				weakFoot = weak_foot_usage_debuff;
			}

			//set the targets to the namespace values. note some of these are 0 as they should be base rate
			targetDrib = dribbling;
			targetGk = gk_awareness;
			targetFinish = finishing;
			targetLowpass = low_pass;
			targetLoftpass = lofted_pass;
			targetHeader = header;
			targetSwerve = curl;
			targetCatching = catching;
			targetClearing = clearing;
			targetReflex = reflexes;
			targetBody_ctrl = balance;
			targetPhys_cont = physical_contact;
			targetKick_pwr = kicking_power;
			targetExp_pwr = acceleration;
			targetBall_ctrl = ball_control;
			targetBall_win = ball_winning;
			targetJump = jump;
			targetCover = gk_reach;
			targetPlace_kick = place_kicking;
			targetStamina = stamina;
			targetSpeed = speed;
			targetAtk = offensive_awareness;
			targetDef = defensive_awareness;
			targetTight_pos = tight_possession;
			targetAggres = aggression;
			//fix all the 0 values and make them the base rate
			if (targetDrib == 0)
			{
				targetDrib = base_stat;
			}
			if (targetGk == 0)
			{
				targetGk = base_stat;
			}
			if (targetFinish == 0)
			{
				targetFinish = base_stat;
			}
			if (targetLowpass == 0)
			{
				targetLowpass = base_stat;
			}
			if (targetLoftpass == 0)
			{
				targetLoftpass = base_stat;
			}
			if (targetHeader == 0)
			{
				targetHeader = base_stat;
			}
			if (targetSwerve == 0)
			{
				targetSwerve = base_stat;
			}
			if (targetCatching == 0)
			{
				targetCatching = base_stat;
			}
			if (targetClearing == 0)
			{
				targetClearing = base_stat;
			}
			if (targetReflex == 0)
			{
				targetReflex = base_stat;
			}
			if (targetBody_ctrl == 0)
			{
				targetBody_ctrl = base_stat;
			}
			if (targetPhys_cont == 0)
			{
				targetPhys_cont = base_stat;
			}
			if (targetKick_pwr == 0)
			{
				targetKick_pwr = base_stat;
			}
			if (targetExp_pwr == 0)
			{
				targetExp_pwr = base_stat;
			}
			if (targetBall_ctrl == 0)
			{
				targetBall_ctrl = base_stat;
			}
			if (targetBall_win == 0)
			{
				targetBall_win = base_stat;
			}
			if (targetJump == 0)
			{
				targetJump = base_stat;
			}
			if (targetCover == 0)
			{
				targetCover = base_stat;
			}
			if (targetPlace_kick == 0)
			{
				targetPlace_kick = base_stat;
			}
			if (targetStamina == 0)
			{
				targetStamina = base_stat;
			}
			if (targetSpeed == 0)
			{
				targetSpeed = base_stat;
			}
			if (targetAtk == 0)
			{
				targetAtk = base_stat;
			}
			if (targetDef == 0)
			{
				targetDef = base_stat;
			}
			if (targetTight_pos == 0)
			{
				targetTight_pos = base_stat;
			}
			if (targetAggres == 0)
			{
				targetAggres = base_stat;
			}

			freeAPositions = free_a;

			allowedHeight = height;
			if (buffPosition1 == -1)
			{
				buffPosition1 = player.reg_pos;
			}
			else if (buffPosition1!=player.reg_pos && buffPosition2 == -1)
			{
				buffPosition2 = player.reg_pos;
			}
			else if (player.reg_pos != buffPosition1 && player.reg_pos != buffPosition2 && buffPosition3 == -1)
			{
				buffPosition3 = player.reg_pos;
				//this will output a team level error later
			}

			if (isCaptain)
			{
				errorTot++;
				errorMsg << _T("Regulars can't be captain; ");
			}

			if (player.reg_pos == 0 || player.reg_pos == 1 || player.reg_pos == 9 || player.reg_pos == 10 || player.reg_pos == 12)
			{
				errorTot++;
				errorMsg << _T("Only LB, RB, DMF, LMF, RMF, CMF, AMF, or SS registered position players can be buffed; ");
			}
			if (player.play_pos[9] == 2)
			{
				errorTot++;
				errorMsg << _T("Buffed players may not have an A-position at CB; ");
			}
			else if (player.reg_pos != 0 && player.form + 1 != form)
			{
				errorTot++;
				errorMsg << _T("Form is ") << player.form + 1 << _T(", should be ") << form << _T("; ");
			}


			/*if (countA > 1)
			{
				errorTot++;
				errorMsg << _T("Only 1 A position for non-medals;");
			}*/

			//cardMod += min(buffed::free_coms, numCom-numTrickCom);
			cardMod += numTrick;
			cardLimit = skills + cardMod;
			freeCOMs = buffed::free_coms;

			/*if (numCom > regCOM)
			{
				errorTot++;
				errorMsg << _T("Has ") << numCom << _T(" COM playing styles, should be no more than ") << regCOM << _T("; ");
			}*/

			if (player.injury + 1 != injury_resistance)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury + 1 << _T(", should be ") << injury_resistance << _T("; ");
			}

			/*if (player.reg_pos == 6 || player.reg_pos == 7 || player.reg_pos == 9 || player.reg_pos == 10)
			{
				NMWMFBuffed = true;
				numNMWMFBuffEligible++;
				heightMod += regWMFHeightBonus;
				targetRate += regWMFStatBonus;
			}*/
		}
		/* SILVER */
        else if(player.height == silver::height) //Silver player
        {
			using namespace silver; //all stats pulled from silver namespace
			isSilver = true;
            numSilver++;
			targetRate += base_stat;
			cardMin = medalSkillCardsMin;

			weakFoot = weak_foot_usage;

			//set the targets to the namespace values. note some of these are 0 as they should be base rate
			targetDrib = dribbling;
			targetGk = gk_awareness;
			targetFinish = finishing;
			targetLowpass = low_pass;
			targetLoftpass = lofted_pass;
			targetHeader = header;
			targetSwerve = curl;
			targetCatching = catching;
			targetClearing = clearing;
			targetReflex = reflexes;
			targetBody_ctrl = balance;
			targetPhys_cont = physical_contact;
			targetKick_pwr = kicking_power;
			targetExp_pwr = acceleration;
			targetBall_ctrl = ball_control;
			targetBall_win = ball_winning;
			targetJump = jump;
			targetCover = gk_reach;
			targetPlace_kick = place_kicking;
			targetStamina = stamina;
			targetSpeed = speed;
			targetAtk = offensive_awareness;
			targetDef = defensive_awareness;
			targetTight_pos = tight_possession;
			targetAggres = aggression;
			//fix all the 0 values and make them the base rate
			if (targetDrib == 0)
			{
				targetDrib = base_stat;
			}
			if (targetGk == 0)
			{
				targetGk = base_stat;
			}
			if (targetFinish == 0)
			{
				targetFinish = base_stat;
			}
			if (targetLowpass == 0)
			{
				targetLowpass = base_stat;
			}
			if (targetLoftpass == 0)
			{
				targetLoftpass = base_stat;
			}
			if (targetHeader == 0)
			{
				targetHeader = base_stat;
			}
			if (targetSwerve == 0)
			{
				targetSwerve = base_stat;
			}
			if (targetCatching == 0)
			{
				targetCatching = base_stat;
			}
			if (targetClearing == 0)
			{
				targetClearing = base_stat;
			}
			if (targetReflex == 0)
			{
				targetReflex = base_stat;
			}
			if (targetBody_ctrl == 0)
			{
				targetBody_ctrl = base_stat;
			}
			if (targetPhys_cont == 0)
			{
				targetPhys_cont = base_stat;
			}
			if (targetKick_pwr == 0)
			{
				targetKick_pwr = base_stat;
			}
			if (targetExp_pwr == 0)
			{
				targetExp_pwr = base_stat;
			}
			if (targetBall_ctrl == 0)
			{
				targetBall_ctrl = base_stat;
			}
			if (targetBall_win == 0)
			{
				targetBall_win = base_stat;
			}
			if (targetJump == 0)
			{
				targetJump = base_stat;
			}
			if (targetCover == 0)
			{
				targetCover = base_stat;
			}
			if (targetPlace_kick == 0)
			{
				targetPlace_kick = base_stat;
			}
			if (targetStamina == 0)
			{
				targetStamina = base_stat;
			}
			if (targetSpeed == 0)
			{
				targetSpeed = base_stat;
			}
			if (targetAtk == 0)
			{
				targetAtk = base_stat;
			}
			if (targetDef == 0)
			{
				targetDef = base_stat;
			}
			if (targetTight_pos == 0)
			{
				targetTight_pos = base_stat;
			}
			if (targetAggres == 0)
			{
				targetAggres = base_stat;
			}

			freeAPositions = free_a;

			allowedHeight = height;

            if(numSilver > silver::count)
			{
                errorTot++;
				errorMsg << _T("Too many Silver medals; ");
			}
            if(player.form+1 != form)
			{
                errorTot++;
				errorMsg << _T("Form is ") << player.form+1 << _T(", should be ") << form << _T("; ");
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

			cardMod += numTrick;
			//cardMod += min(free_coms, numCom-numTrickCom); 
			cardLimit = skills + cardMod; 
			freeCOMs = silver::free_coms;

			/*if (numCom > silverCOM)
			{
				errorTot++;
				errorMsg << _T("Has ") << numCom << _T(" COM playing styles, should be no more than ") << silverCOM << _T("; ");
			}*/

			if(player.injury+1 != injury_resistance)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury+1 << _T(", should be ") << injury_resistance << _T("; ");
			}

			/*if (player.reg_pos == 9 || player.reg_pos == 10)
			{
				heightMod += silverWFHeightBonus;
				targetRate += silverWFStatBonus;
			}*/

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
        else if (player.height == gold::height) //Gold player
        {
			using namespace gold;
			isGold = true;
            numGold++;
			targetRate += base_stat;
			cardMin = medalSkillCardsMin;

			weakFoot = weak_foot_usage;

            if(numGold > gold::count)
			{
                errorTot++;
				errorMsg << _T("Too many Gold medals; ");
			}
            if(player.form+1 != form)
			{
                errorTot++;
				errorMsg << _T("Form is ") << player.form+1 << _T(", should be ") << form << _T("; ");
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
			//set the targets to the namespace values. note some of these are 0 as they should be base rate
			targetDrib = dribbling;
			targetGk = gk_awareness;
			targetFinish = finishing;
			targetLowpass = low_pass;
			targetLoftpass = lofted_pass;
			targetHeader = header;
			targetSwerve = curl;
			targetCatching = catching;
			targetClearing = clearing;
			targetReflex = reflexes;
			targetBody_ctrl = balance;
			targetPhys_cont = physical_contact;
			targetKick_pwr = kicking_power;
			targetExp_pwr = acceleration;
			targetBall_ctrl = ball_control;
			targetBall_win = ball_winning;
			targetJump = jump;
			targetCover = gk_reach;
			targetPlace_kick = place_kicking;
			targetStamina = stamina;
			targetSpeed = speed;
			targetAtk = offensive_awareness;
			targetDef = defensive_awareness;
			targetTight_pos = tight_possession;
			targetAggres = aggression;
			//fix all the 0 values and make them the base rate
			if (targetDrib == 0)
			{
				targetDrib = base_stat;
			}
			if (targetGk == 0)
			{
				targetGk = base_stat;
			}
			if (targetFinish == 0)
			{
				targetFinish = base_stat;
			}
			if (targetLowpass == 0)
			{
				targetLowpass = base_stat;
			}
			if (targetLoftpass == 0)
			{
				targetLoftpass = base_stat;
			}
			if (targetHeader == 0)
			{
				targetHeader = base_stat;
			}
			if (targetSwerve == 0)
			{
				targetSwerve = base_stat;
			}
			if (targetCatching == 0)
			{
				targetCatching = base_stat;
			}
			if (targetClearing == 0)
			{
				targetClearing = base_stat;
			}
			if (targetReflex == 0)
			{
				targetReflex = base_stat;
			}
			if (targetBody_ctrl == 0)
			{
				targetBody_ctrl = base_stat;
			}
			if (targetPhys_cont == 0)
			{
				targetPhys_cont = base_stat;
			}
			if (targetKick_pwr == 0)
			{
				targetKick_pwr = base_stat;
			}
			if (targetExp_pwr == 0)
			{
				targetExp_pwr = base_stat;
			}
			if (targetBall_ctrl == 0)
			{
				targetBall_ctrl = base_stat;
			}
			if (targetBall_win == 0)
			{
				targetBall_win = base_stat;
			}
			if (targetJump == 0)
			{
				targetJump = base_stat;
			}
			if (targetCover == 0)
			{
				targetCover = base_stat;
			}
			if (targetPlace_kick == 0)
			{
				targetPlace_kick = base_stat;
			}
			if (targetStamina == 0)
			{
				targetStamina = base_stat;
			}
			if (targetSpeed == 0)
			{
				targetSpeed = base_stat;
			}
			if (targetAtk == 0)
			{
				targetAtk = base_stat;
			}
			if (targetDef == 0)
			{
				targetDef = base_stat;
			}
			if (targetTight_pos == 0)
			{
				targetTight_pos = base_stat;
			}
			if (targetAggres == 0)
			{
				targetAggres = base_stat;
			}

			freeAPositions = free_a;

			allowedHeight = height;
			
			cardMod += numTrick;
			//cardMod += min(free_coms, numCom-numTrickCom); 
			cardLimit = skills + cardMod; 
			freeCOMs = gold::free_coms;

			/*if (numCom > goldCOM)
			{
				errorTot++;
				errorMsg << _T("Has ") << numCom << _T(" COM playing styles, should be no more than ") << goldCOM << _T("; ");
			}*/
            
			if(player.injury+1 > injury_resistance)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury+1 << _T(", should be ") << injury_resistance << _T("; ");
			}

			/*if (player.reg_pos == 12 && player.play_style == 13)
			{
				heightMod += medalCFTHeightBonus;
				if (player.play_style == 13)
				{
					medalCFTBuff = true;
				}
			}*/
		}
		else
		{
			errorTot++;
			errorMsg << _T("Illegal Ability scores, this player's height does not match any available player types; "); //mentions that height is what is being checked
			//spit out whatever errors were already found, but target scores can't be set, so quit out of this player to avoid useless error outputs
			errorMsg << _T("\r\n");
			msgOut += _T("\t");
			msgOut += errorMsg.str();
			continue;
		}

		if (player.height != allowedHeight)
		{
			errorTot++;
			errorMsg << _T("Wrong height, allowed height is: ") << allowedHeight << _T("; ");
		}

		int neutralModHeight = player.height - heightMod;
		//int debuffedModHeight = player.height - heightMod + regWMFHeightBonus;
		int confirmedNMWMFBuff = false;


		/*if (medalCFTBuff)
		{
			weakFoot = medalCFTFootedness;
		}*/

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

		//Check player skill card count
		if (cardCount - numTrick > cardLimit - numTrick) //don't include trick cards in either count
		{
			errorTot++;
			errorMsg << _T("Has ") << cardCount - numTrick<< _T(" non-free skill cards, only allowed ") << cardLimit - numTrick<< _T("; ");
		}
		//Check player com style count
		if ((numCom - numTrickCom) > (freeCOMs + max(0,(cardLimit - cardCount)))) //unused skill cards can be exchanged for com styles, don't include free com styles
		{
			errorTot++;
			errorMsg << _T("Has ") << numCom - numTrickCom << _T(" non-free COM styles, only allowed ") << freeCOMs + max(0, (cardLimit - cardCount)) << _T(". Remove non-free skill cards to add COM styles; ");
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

		if (countA > freeAPositions + max(0, cardLimit - cardCount - max(0, ((numCom - numTrickCom) - freeCOMs))))
		{
			if (usingNMWMFAPos)
			{
				if (countA > freeAPositions + max(0, cardLimit - cardCount) + 1)
				{
					errorTot++;
					errorMsg << _T("Has ") << countA << _T(" A positions, only allowed ") << freeAPositions + max(0, cardLimit - cardCount) + 1 << _T(". Remove cards to add A position slots; ");
				}
			}
			else if (countA > freeAPositions + max(0, cardLimit - cardCount - max(0,((numCom-numTrickCom)-freeCOMs))))
			{
				if (max(0, ((numCom - numTrickCom) - freeCOMs)) == 0) //hasn't exchanged any skill cards for com styles
				{
					errorTot++;
					errorMsg << _T("Has ") << countA << _T(" A positions, only allowed ") << freeAPositions + max(0, cardLimit - cardCount - max(0, ((numCom - numTrickCom) - freeCOMs))) << _T(". Remove non-free skill cards to add A position slots; ");
				}
				else //exchanged at least 1 skill card for a com style
				{
					errorTot++;
					errorMsg << _T("Has ") << countA << _T(" A positions, only allowed ") << freeAPositions + max(0, cardLimit - cardCount - max(0, ((numCom - numTrickCom) - freeCOMs))) << _T(". Remove non-free skill cards or up to ") << (numCom - numTrickCom) - freeCOMs << _T(" non-free COM style(s) to add A position slots; ");
				}
			}
		}

		if (player.reg_pos == 0 || cardsSwappedForAPositions < 0)
		{
			cardsSwappedForAPositions = 0;
		}


		if (cardCount - numTrick < cardMin - cardsSwappedForAPositions)
		{
			errorTot++;
			errorMsg << _T("Has ") << cardCount - numTrick << _T(" skill cards, must have at least ") << cardMin - cardsSwappedForAPositions << _T("; ");
			//errorMsg << cardCount << min(freeCOMs, numCom) << numTrick;
		}

		//Check PES skill card limit of 10
		//21 apparently can load over 10 cards, limit is set at 11 now.
		if (cardCount > 11)
		{
			errorTot++;
			errorMsg << _T("Has ") << cardCount << _T(" skill cards, only allowed 11; ");
		}

		//Check COM hard cap
		if (numCom > maxCOM)
		{
			errorTot++;
			errorMsg << _T("Has ") << numCom << _T(" COM playing styles, limit is 5; ");
		}

		/*if (NMWMFBuffed && !confirmedNMWMFBuff) {
			targetRate -= regWMFStatBonus;
		}
		*/
		//Check player overall rating
		if (rating != targetRate)
		{
			errorTot++;
			errorMsg << _T("Illegal Ability scores; ");
		}

		//Check individual skill ratings

		if(player.drib != targetDrib)
        {
            errorTot++;
			errorMsg << _T("Dribbling is ") << player.drib << _T(", should be ") << targetDrib << _T("; ");
        }
        if(player.gk != targetGk)
        {
            errorTot++;
			errorMsg << _T("Goalkeeping is ") << player.gk << _T(", should be ") << targetGk << _T("; ");
        }
        if(player.finish != targetFinish)
		{
            errorTot++;
			errorMsg << _T("Finishing is ") << player.finish << _T(", should be ") << targetFinish << _T("; ");
        }
        if(player.lowpass != targetLowpass)
		{
            errorTot++;
			errorMsg << _T("Low Pass is ") << player.lowpass << _T(", should be ") << targetLowpass << _T("; ");
        }
        if(player.loftpass != targetLoftpass)
		{
            errorTot++;
			errorMsg << _T("Lofted Pass is ") << player.loftpass << _T(", should be ") << targetLoftpass << _T("; ");
        }
        if(player.header != targetHeader)
		{
            errorTot++;
			errorMsg << _T("Header is ") << player.header << _T(", should be ") << targetHeader << _T("; ");
        }
        if(player.swerve != targetSwerve)
		{
            errorTot++;
			errorMsg << _T("Swerve is ") << player.swerve << _T(", should be ") << targetSwerve << _T("; ");
        }
        if(player.catching != targetCatching)
		{
            errorTot++;
			errorMsg << _T("Catching is ") << player.catching << _T(", should be ") << targetCatching << _T("; ");
        }
        if(player.clearing != targetClearing)
		{
            errorTot++;
			errorMsg << _T("Clearing is ") << player.clearing << _T(", should be ") << targetClearing << _T("; ");
        }
        if(player.reflex != targetReflex)
		{
            errorTot++;
			errorMsg << _T("Reflexes is ") << player.reflex << _T(", should be ") << targetReflex << _T("; ");
        }
        if(player.body_ctrl != targetBody_ctrl)
		{
            errorTot++;
			errorMsg << _T("Body Control is ") << player.body_ctrl << _T(", should be ") << targetBody_ctrl << _T("; ");
        }
        if(player.phys_cont != targetPhys_cont && pesVersion!=16) //Not in 16
		{
            errorTot++;
			errorMsg << _T("Physical Contact is ") << player.phys_cont << _T(", should be ") << targetPhys_cont << _T("; ");
        }
        if(player.kick_pwr != targetKick_pwr)
		{
            errorTot++;
			errorMsg << _T("Kicking Power is ") << player.kick_pwr << _T(", should be ") << targetKick_pwr << _T("; ");
        }
        if(player.exp_pwr != targetExp_pwr)
		{
            errorTot++;
			errorMsg << _T("Explosive Power is ") << player.exp_pwr << _T(", should be ") << targetExp_pwr << _T("; ");
        }
        if(player.ball_ctrl != targetBall_ctrl)
		{
            errorTot++;
			errorMsg << _T("Ball Control is ") << player.ball_ctrl << _T(", should be ") << targetBall_ctrl << _T("; ");
        }
        if(player.ball_win != targetBall_win)
		{
            errorTot++;
			errorMsg << _T("Ball winning is ") << player.ball_win << _T(", should be ") << targetBall_win << _T("; ");
        }
        if(player.jump != targetJump)
		{
            errorTot++;
			errorMsg << _T("Jump is ") << player.jump << _T(", should be ") << targetJump << _T("; ");
        }
        if(player.cover != targetCover) 
		{
            errorTot++;
			errorMsg << _T("Coverage is ") << player.cover << _T(", should be ") << targetCover << _T("; ");
        }
        if(player.place_kick != targetPlace_kick)
		{
            errorTot++;
			errorMsg << _T("Place Kicking is ") << player.place_kick << _T(", should be ") << targetPlace_kick << _T("; ");
        }
        if(player.stamina != targetStamina)
		{
            errorTot++;
			errorMsg << _T("Stamina is ") << player.stamina << _T(", should be ") << targetStamina << _T("; ");
        }
        if(player.speed != targetSpeed)
		{
            errorTot++;
			errorMsg << _T("Speed is ") << player.speed << _T(", should be ") << targetSpeed << _T("; ");
        }
        if(player.atk != targetAtk)
		{
            errorTot++;
			errorMsg << _T("Attacking Prowess is ") << player.atk << _T(", should be ") << targetAtk << _T("; ");
        }
        if(player.def != targetDef)
		{
            errorTot++;
			errorMsg << _T("Defensive Prowess is ") << player.def << _T(", should be ") << targetDef << _T("; ");
        }
		if(pesVersion>19 && player.tight_pos != targetTight_pos)
		{
            errorTot++;
			errorMsg << _T("Tight Possession is ") << player.tight_pos << _T(", should be ") << targetTight_pos << _T("; ");
        }
		if(pesVersion>19 && player.aggres != targetAggres)
		{
            errorTot++;
			errorMsg << _T("Aggression is ") << player.aggres << _T(", should be ") << targetAggres << _T("; ");
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
	/*if (numNMWMFBuffed > maxNumNMWMFBuffed)
	{
		errorTot += numNMWMFBuffed - maxNumNMWMFBuffed;
		errorMsg << _T("Has ") << numNMWMFBuffed << _T("/") << maxNumNMWMFBuffed << _T(" buffed LWF, RWF, LMF, RMF non-medals; ");
	}
	*/
	/*if (numNMWMFBuffed < maxNumNMWMFBuffed && numNMWMFBuffed < numNMWMFBuffEligible)
	{
		errorTot += numNMWMFBuffEligible - numNMWMFBuffed;
		errorMsg << _T("Has ") << numNMWMFBuffed << _T("/") << maxNumNMWMFBuffed << _T(" buffed LWF, RWF, LMF, RMF non-medals, missing ") << numNMWMFBuffEligible - numNMWMFBuffed << _T(" buffed non-medals. Check the height or stats of LWF, RWF, LMF, RMF non-medals.");
	}*/
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
    if(numReg != nm::count)
    {
        errorTot++;
        errorMsg << _T("Number of Regular players is ") << numReg << _T(", should be ") << nm::count << _T("; ");
    }
	if (numBuff != buffed::count)
	{
		errorTot++;
		errorMsg << _T("Number of Buffed players is ") << numBuff << _T(", should be ") << buffed::count << _T("; ");
	}
    if(numSilver != silver::count)
    {
        errorTot++;
        errorMsg << _T("Number of Silver medals is ") << numSilver << _T(", should be ") << silver::count << _T("; ");
    }
    if(numGold != gold::count)
    {
        errorTot++;
        errorMsg << _T("Number of Gold medals is ") << numGold << _T(", should be ") << gold::count << _T("; ");
    }
	if (buffPosition3 != -1)
	{
		errorTot++;
		errorMsg << _T("Too many registered positions with buffed players. Maximum is 2; ");
	}
	//check that there are no nonbuffed nonmedal players in registered positions that are buffed
	for (int ii = 0; ii < gteams[teamSel].num_on_team; ii++)
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
		if ((player.reg_pos == buffPosition1 || player.reg_pos == buffPosition2) && player.height==nm::height)
		{
			errorTot++;
			errorMsg << _T("Player ") << player.name << _T(" has the same registererd position as a buffed player, but isn't a buffed non-medal; ");
		}

	}
	if (pesVersion == 16)
	{
		for(int ii=0; ii<11; ii++)
		{ if(gteams[teamSel].ManMarking1[ii] != 255)
			{
				errorTot++;
				errorMsg << _T("Man marking is set up on preset 1; ");
				break;

			}
		}
		for(int ii=0; ii<11; ii++)
		{ if(gteams[teamSel].ManMarking2[ii] != 255)
			{
				errorTot++;
				errorMsg << _T("Man marking is set up on preset 2; ");
				break;

			}
		}
		for(int ii=0; ii<11; ii++)
		{ if(gteams[teamSel].ManMarking3[ii] != 255)
			{
				errorTot++;
				errorMsg << _T("Man marking is set up on preset 3; ");
				break;

			}
		}
		if(gteams[teamSel].AutoSub!=0)
			{
				errorTot++;
				errorMsg << _T("Auto subs are on; ");
			}
		if(gteams[teamSel].AutoOffside!=0)
			{
				errorTot++;
				errorMsg << _T("Auto offside trap is on; ");
			}
		if(gteams[teamSel].AutoPresetTactics!=0)
			{
				errorTot++;
				errorMsg << _T("Auto change preset tactics is on; ");
			}
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
