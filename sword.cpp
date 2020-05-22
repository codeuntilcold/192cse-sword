#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif

////////////////// USER DEFINED /////////////////
#define LOG(x) std::cout << x << std::endl

void statLimit(knight& knight, int& maxHP)
{
    maxHP = (maxHP > 999) ? 999 : maxHP;
    knight.HP = (knight.HP > maxHP) ? maxHP : knight.HP;
    knight.level = (knight.level > 10) ? 10 : knight.level;
    knight.antidote = (knight.antidote > 99) ? 99 : knight.antidote;   // NOT GIVEN ?
    knight.gil = (knight.gil > 999) ? 999 : knight.gil;
}

bool areFriendlyNumbers(const int& HP, const int& gil)
{
    float HP_abd;
    float gil_abd;

    for (int i = 1; i < HP + 1; i++)
        HP_abd = (HP % i == 0) ? (HP_abd + i) : HP_abd;
    HP_abd = HP_abd / HP;

    for (int i = 1; i < gil + 1; i++)
        gil_abd = (gil % i == 0) ? (gil_abd + i) : gil_abd;
    gil_abd = gil_abd / gil;

    if (HP_abd == gil_abd) 
        return true;
    else 
        return false;
}

bool isPrime(const int& HP)
{
    if (HP == 1) { 
        return false; 
    }
	for (int itr = 2; itr < HP / 2 + 1; itr++) { 
		if (HP % itr == 0) { 
			return false; 
		} 
	}
    return true;
}

bool isSumOfPtgTriple(const int& HP)
{
    if (HP % 2 == 0 && HP != 888) {				// Sum of Pythagorean triples is always even
        for (int x = 1; x < HP / 3 + 1; x++) {
            for (int y = x + 1; y < HP - x + 1; y++) {
                int z = HP - x - y;

                if (x*x + y*y == z*z) { return true; }
            }
        }
    }
    return false;
}

int healthLoss(const int& event, const int& levelO)
{
    float baseDamage;
    switch (event)
    {
    case 1: baseDamage = 1; break;
    case 2:	baseDamage = 1.5; break;
    case 3:	baseDamage = 4.5; break;
    case 4:	baseDamage = 6.5; break;
    case 5:	baseDamage = 8.5; break;
    }
    int damage = baseDamage * levelO * 10;
    return damage;
}

int levelUp(int& currentLevel, int desiredLevel, int& maxHP)
{
    maxHP += (desiredLevel - currentLevel) * 100;
    currentLevel = desiredLevel;
}

void heal(knight& knight, const int& maxHP, int& berryPoison)
{
    if (knight.HP < 1)
    {
        callPhoenix(knight, maxHP);
        berryPoison = 0;
    }
    if (berryPoison)
    {
        if (knight.antidote > 0) {
            knight.antidote--;
            berryPoison = 0;
        }
        else {
            berryPoison--;
        } 
    }
}


report* walkthrough (knight& theKnight, castle arrCastle[], int nCastle, int mode, int nPetal)
{
    report* pReturn;
    int bFlag;
    //fighting for the existence of mankind here

    bFlag = 0;
    int maxHP = theKnight.HP;

    int currentCastle = 0;
    int currentEvent = 0;

    int theEvent = 0;
    int i = 0;
    int levelO = 0, b = 0;

    int nWin = 0;
    int nLose = 0;

    // Bunch of flags
    bool gotPaladin = false;
    bool gotLancelot = false;
    bool gotGuinevere = false;
    bool gotExcalibur = false;
    bool gotMithril = false;
    bool gotScarlH = false;

    bool beatOmg = false;
    bool odinKilled = false;

    int berryPoison = 0;
    int metNina = 0;
    int gotLionHeart = 0;
    int metOdin = 0;

    bool isArthur = (theKnight.HP == 999) ? true : false;
    bool isLancelot = (theKnight.HP == 888) ? true : false; 
    bool isGuinevere = (theKnight.HP == 777) ? true : false; 
    bool isPaladin = isPrime(theKnight.HP);
    bool isDragonKnight = isSumOfPtgTriple(theKnight.HP);

    
    if (isLancelot) { gotLancelot = true; }
    if (isGuinevere) { gotGuinevere = true; }
    if (isPaladin) { gotPaladin = true; }


    while (nPetal || isArthur)
    {
        // BEFORE EVENTS
        theEvent = arrCastle[currentCastle].arrEvent[currentEvent];
        i = currentEvent + 1;

        b = i % 10;
		levelO = (i > 6) ? (b > 5 ? b : 5) : b;

        bool normalWin = theKnight.level > levelO && gotExcalibur || gotLionHeart || metOdin || isArthur || isLancelot;
        bool eternalLove = gotLancelot && gotGuinevere && !gotExcalibur || (isArthur || isLancelot) && gotGuinevere || isGuinevere && gotLancelot;

        // DURING EVENTS
        switch (theEvent)
        {
        case 95:    // PALADIN SHIELD
            gotPaladin = true;
        break;
        case 96:    // LANCELOT SPEAR
            gotLancelot = true;
        break;
        case 97:    // GUINEVERE'S HAIR
            gotGuinevere = true;
        break;
        case 98:    // EXCALIBUR
            if (gotPaladin && gotLancelot && gotPaladin || isArthur) { gotExcalibur = true; }
        break;
        case 99:    // ULTIMECIA
            if (gotExcalibur || gotLionHeart) 
            { 
                nWin++;
                bFlag = 1;
                if (berryPoison) 
                { 
                    theKnight.HP = (theKnight.HP < 3) ? 1 : (theKnight.HP / 3); 
                }
            }
            else
            {
                nLose++;
                if ( !(gotMithril || isGuinevere) ) 
                { 
                    theKnight.HP = (theKnight.HP < 3) ? 1 : (theKnight.HP / 3); 
                };
            }
        break;
        
        case 1:     // GIL FARM
        case 2:
        case 3:
        case 4:
        case 5:
            if (normalWin || isPaladin)
            {
                nWin++;
                switch (theEvent)
                {
                case 1: theKnight.gil += 100; break;
                case 2: theKnight.gil += 150; break;    // FEMALE AMAZON WARRIOR
                case 3: theKnight.gil += 450; break;
                case 4: theKnight.gil += 650; break;
                case 5: theKnight.gil += 850; break;
                }
                if (berryPoison) 
                { 
                    theKnight.HP -= healthLoss(theEvent, levelO); 
                }
            }
            else
            {
                nLose++;
                if ( !(gotMithril || isGuinevere && theEvent == 2) ) 
                { 
                    theKnight.HP -= healthLoss(theEvent, levelO); 
                }
            }
        break;

        case 6:     // TORNBERRY
            if (berryPoison) { break; }

            if (normalWin)
            {
                nWin++;
                levelUp(theKnight.level, theKnight.level + 1, maxHP);
            }
            else
            {
                nLose++;
                if ( !(isPaladin || isDragonKnight) ) { berryPoison = 6; }
            }
        break;

        case 7:     // QUEEN OF CARDS
            if (normalWin)
            {
                nWin++;
                theKnight.gil *= 2;
            }
            else
            {
                nLose++;
                if ( !(gotScarlH || isGuinevere) ) { theKnight.gil /= 2; }
            }  
        break;
        
        case 8:     // NINA DE RINGS
            if (!metNina) { metNina = 6; }

            if ( !areFriendlyNumbers(theKnight.HP, theKnight.gil) )
            {   
                if (theKnight.gil < 50) { break; }
                else
                {
                    if (berryPoison) 
                    { 
                        if ( !(gotScarlH || isGuinevere || isPaladin) ) { theKnight.gil -= 50; } 
                        berryPoison = 0; 
                    }

                    if (theKnight.gil > 0)
                    {
                        theKnight.HP = theKnight.HP + theKnight.gil;
                        if ( !(gotScarlH || isPaladin) ) 
                        {
                            theKnight.gil = (theKnight.HP > maxHP) ? (theKnight.HP - maxHP) : 0;
                            if (isGuinevere) { theKnight.gil += 50; }
                        }
                    }
                }
            }
            else
            {
                berryPoison = 0;
                theKnight.HP = maxHP;
                gotLionHeart = 6;
            }
        break;
        
        case 9:     // DURIAN
            berryPoison = 0;
            theKnight.HP = maxHP;
            nPetal = (nPetal + 5 > 99 || gotScarlH) ? 99 : (nPetal + 5);
        break;
        
        case 10:    // ANTIDOTE
            theKnight.antidote++;
        break;
        
        case 11:    // ODIN
            if ( !(metOdin || odinKilled) ) { metOdin = 6; }
        break;
        
        case 12:    // MERLIN
            berryPoison = 0;
            levelUp(theKnight.level, theKnight.level + 1, maxHP);
            theKnight.HP = maxHP;
        break;
        
        case 13:    // OMEGA WEAPON
            if (beatOmg) { break; }

            if (theKnight.level == 10 && gotExcalibur || isDragonKnight && gotLionHeart)
            {
                nWin++;
                levelUp(theKnight.level, 10, maxHP);
                theKnight.gil = 999;
                beatOmg = true;
            }
            else
            {
                nLose++;
                if (!gotMithril) { theKnight.HP = 0; }
            }
        break;
        
        case 14:    // HADES
            if (metOdin && !isDragonKnight) { metOdin = 0; odinKilled = true; }

            if (theKnight.level >= levelO || gotLionHeart)
            {
                nWin++;
                gotMithril = true;
            }
            else
            {
                nLose++;
                if (!gotMithril) { theKnight.HP = 0; }
            }
        break;
        
        case 15:    // SCARLET HAKAMA
            gotScarlH = true;
        break;
        
        case 16:    // LOCKED DOOR
            if ( !(theKnight.level > i % 10 || isLancelot || isDragonKnight) )
            {
                currentEvent = arrCastle[currentCastle].nEvent - 1;
            }
        break;
        }   // END EVENT

        // AFTER EVENTS
        if (nPetal) { nPetal--; }
        if (gotLionHeart && !isPaladin) { gotLionHeart--; }
        if (metNina) { metNina--; }
        if (metOdin) { metOdin--; }

        if (bFlag) { break; }

        if (currentEvent++ == arrCastle[currentCastle].nEvent - 1)
        {
            levelUp(theKnight.level, theKnight.level + 1, maxHP);
            currentCastle = ++currentCastle % nCastle;
            currentEvent = 0;
        }

        heal(theKnight, maxHP, berryPoison);
        statLimit(theKnight, maxHP);
    }

    // success or failure?	
    pReturn = (bFlag) ? new report : NULL;

    if (bFlag)
    {
        pReturn->nPetal = nPetal;
        pReturn->nWin = nWin;
        pReturn->nLose = nLose;
    }
    return pReturn;
}
