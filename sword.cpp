#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif

////////////////// USER DEFINED ///////////////// HAS OTHER LOGGING THAT NEEDS DELETION /////////////////////////////////


// Mathematics functions
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void sortWithHash(int* array, int size)
{
    if (size == 1) {
        return;
    }
    for (int i = 0; i < size - 1; i++) {
        if ( hash(array[i]) > hash(array[i + 1]) ) 
        {
            swap(array + i, array + i + 1);
        }
    }
    sortWithHash(array, size - 1);
}

int GCD(int a, int b)
{
    if (b == 0)
        return a;
    else
        return GCD(b, a % b);
}
bool areFriendlyNumbers(int HP, int gil)
{
    double sod_HP = 0, sod_gil = 0;

    for (int i = 1; i < HP + 1; i++) {
        sod_HP = (HP % i == 0) ? (sod_HP + i) : sod_HP;
    }
    sod_HP /= HP;

    for (int i = 1; i < gil + 1; i++) {
        sod_gil = (gil % i == 0) ? (sod_gil + i) : sod_gil;
    }    
    sod_gil /= gil;
    
    if (sod_HP == sod_gil)
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


// Contextual functions
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
void healUp(knight& knight, const int& maxHP, int& berryPoison)
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
void limit(knight& knight, int& maxHP, int& nPetal)
{
    maxHP = (maxHP > 999) ? 999 : maxHP;
    nPetal = (nPetal > 99) ? 99 : nPetal;
    knight.HP = (knight.HP > maxHP) ? maxHP : knight.HP;
    knight.level = (knight.level > 10) ? 10 : knight.level;
    knight.antidote = (knight.antidote > 99) ? 99 : knight.antidote;   // NOT GIVEN ?
    knight.gil = (knight.gil > 999) ? 999 : knight.gil;
}

void nextChallenge(castle arrCastle[], const int& nCastle, int& currentCastle, int& currentEvent, knight& theKnight, int& maxHP)
{
    if (currentEvent++ == arrCastle[currentCastle].nEvent - 1)
    {
        levelUp(theKnight.level, theKnight.level + 1, maxHP);
        currentCastle = ++currentCastle % nCastle;
        currentEvent = 0;
    }
}


// Mode dependent fuctions
void pickOrMiss(const int& mode, int* & pick, const int& treasure, bool& gotPaladin, bool& gotLancelot, bool& gotGuinevere)
{
    if (mode == 0 || mode == 2 || mode == 1 && *pick == treasure) {
        switch (treasure)
        {
        case 95: gotPaladin = true   ; break;
        case 96: gotLancelot = true  ; break;
        case 97: gotGuinevere = true ; break;
        }
        pick++;
    }
}
void skipIfHaveItem(int* & mustPick, bool gotPaladin, bool gotLancelot, bool gotGuinevere)
{
    if (*mustPick == 95 && gotPaladin) { mustPick++; }
    else if (*mustPick == 96 && gotLancelot) { mustPick++; }
    else if (*mustPick == 97 && gotGuinevere) { mustPick++; }
}


void process(knight& theKnight, castle arrCastle[], int nCastle, int mode, int& nPetal, int& bFlag, int& nWin, int& nLose)
{
    int maxHP = theKnight.HP;
    int currentCastle   = 0;
    int currentEvent    = 0;

    int theEvent = 0;
    int i = 0;
    int levelO = 0, b = 0;

    ////////////////////////////////////// TOO MANY FLAGS //////////////////////////////////////////

    // For mode 1
    int mustHaveTreasure[] = { 95, 96, 97 };
    sortWithHash(mustHaveTreasure, 3);
        // for (int itr = 0; itr < 3; itr++)
        //     LOG("Must pick treasure " << mustHaveTreasure[itr]);
    int* mustPick = mustHaveTreasure;

    // Identity flags
    bool isArthur       = (theKnight.HP == 999) ? true : false; 
    bool isLancelot     = (theKnight.HP == 888) ? true : false; 
    bool isGuinevere    = (theKnight.HP == 777) ? true : false; 
    bool isPaladin      = isPrime(theKnight.HP);
    bool isDragonKnight = isSumOfPtgTriple(theKnight.HP);

    // One time flags
    bool gotPaladin     = isPaladin;
    bool gotLancelot    = isLancelot;
    bool gotGuinevere   = isGuinevere;
    bool gotExcalibur   = false;
    bool gotMithril     = false;
    bool gotScarlH      = false;

    bool beatOmg    = false;
    bool killedOdin = false;

    // Count down flags
    int berryPoison  = 0;
    int gotLionHeart = 0;
    int metNina = 0;
    int metOdin = 0;

    while (nPetal || isArthur)
    {
        // BEFORE EVENTS
        theEvent = arrCastle[currentCastle].arrEvent[currentEvent];
        i = currentEvent + 1;

        b = i % 10;
		levelO = (i > 6) ? (b > 5 ? b : 5) : b;

        bool normalWin = theKnight.level >= levelO || gotLionHeart || metOdin || isArthur || isLancelot;
        bool hasEternalLove = gotLancelot && gotGuinevere && !gotExcalibur 
                            || (isArthur || isLancelot) && gotGuinevere 
                            || isGuinevere && gotLancelot;

        
        if (mode == 1) { skipIfHaveItem(mustPick, gotPaladin, gotLancelot, gotGuinevere); }

        // DURING EVENTS
        switch (theEvent)
        {
        case 95:    // PALADIN SHIELD
        case 96:    // LANCELOT SPEAR
        case 97:    // GUINEVERE HAIR
            pickOrMiss(mode, mustPick, theEvent, gotPaladin, gotLancelot, gotGuinevere);
        break;
        
        case 98:    // EXCALIBUR
            if (gotPaladin && gotLancelot && gotGuinevere || isArthur) { gotExcalibur = true; }
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
                }
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
                int bonusGil[] = { 0, 100, 150, 450, 650, 850 };
                theKnight.gil += bonusGil[theEvent];
                
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
                if (theKnight.gil < 50) { 
                    break; 
                }
                else {
                    if (berryPoison) 
                    { 
                        berryPoison = 0; 
                        if ( !(gotScarlH || isGuinevere || isPaladin) ) { theKnight.gil -= 50; } 
                    }

                    if (theKnight.gil > 0)
                    {
                        theKnight.HP = theKnight.HP + theKnight.gil;
                        if (isGuinevere) { theKnight.gil += 50; }
                        
                        if ( !(gotScarlH || isGuinevere ||isPaladin) ) 
                        {
                            theKnight.gil = (theKnight.HP > maxHP) ? (theKnight.HP - maxHP) : 0;
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
            if ( !(metOdin || killedOdin) ) { metOdin = 6; }
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
            if (metOdin && !isDragonKnight) { metOdin = 0; killedOdin = true; }

            if (theKnight.level >= levelO || gotLionHeart || hasEternalLove)
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
        if (gotLionHeart && !isPaladin) { gotLionHeart--; }
        if (metNina) { metNina--; }
        if (metOdin) { metOdin--; }
        if (mustPick > mustHaveTreasure + 2) { mustPick = mustHaveTreasure + 2; }

        healUp(theKnight, maxHP, berryPoison);

        if (nPetal) { nPetal--; }
        if (bFlag) { break; }

        nextChallenge(arrCastle, nCastle, currentCastle, currentEvent, theKnight, maxHP);
        limit(theKnight, maxHP, nPetal);

///////////////////////////////////////////////////////////////////////////// LOGGING
static int once = 1;
if (once++ == 1) {
printf("\n");
printf("Identity:   Paladin %d   DragonKnight %d \n", isPaladin, isDragonKnight);
printf("   Csl   Evt   Code  |    HP    lv   atd   gil   |  Petal  |  Psn  |  Odin  |  95  |  96  |  97  | Win | Lose |\n"); 
printf("   ------\n"); }
printf("   %d     %2d    %2d    |   %3d   %3d   %3d   %3d   |", currentCastle + 1, i, theEvent, theKnight.HP, theKnight.level, theKnight.antidote, theKnight.gil);
printf("   %3d   |", nPetal);
printf("   %3d |", berryPoison);
printf("   %3d  |", metOdin);
printf(" %3c  |", (gotPaladin)   ? 'x' : ' ');
printf(" %3c  |", (gotLancelot)  ? 'x' : ' ');
printf(" %3c  |", (gotGuinevere) ? 'x' : ' ');
printf(" %3d  |", nWin);
printf(" %3d  |", nLose);
if (gotExcalibur)       printf("   Ex");
if (gotLionHeart)       printf("   LnHrt: %d", gotLionHeart);
if (gotScarlH)          printf("   Scrl");
if (gotMithril)         printf("   Mith");
if (hasEternalLove)     printf("   <3");
// if (killedOdin)         printf("   Odin-X");
// if (beatOmg)            printf("   OMG-X");
printf("\n");
if (!currentEvent) 
printf("   ------\n");
///////////////////////////////////////////////////////////////////////////////////////////////
        
        
    }
}




report* walkthrough (knight& theKnight, castle arrCastle[], int nCastle, int mode, int nPetal)
{
    report* pReturn;
    int bFlag;
    //fighting for the existence of mankind here

    bFlag = 0;
    int nWin  = 0;
    int nLose = 0;

    process(theKnight, arrCastle, nCastle, mode, nPetal, bFlag, nWin, nLose);

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


