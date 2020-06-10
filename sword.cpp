#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif

// My macro
#ifndef _LOG_EVERY_STATE

#define LOG_OPTIMAL_ROUTE
#define LOG_STATE_AFTER_EVENT
#define LOG_INDEX_ORDER_1 
#define LOG_INDEX_ORDER_2 
#define LOG_INDEX_ORDER_3 

#else

#define LOG_OPTIMAL_ROUTE \
    printf("\nKnight: %d %d %d %d\n", bestKnight.HP, bestKnight.level, bestKnight.antidote, bestKnight.gil);\
    printf("Report: %d %d %d\n", optimalPetal, win, lose)

#define LOG_STATE_AFTER_EVENT \
    static int once = 1;\
    if (once++ == 1) {\
    printf("\n");\
    printf("Identity:   ---(%s)---\n", (isPaladin) ? "Paladin" : (isDragonKnight) ? "DragonKnight" : (isArthur) ? "Arthur" : (isLancelot) ? "Lancelot" : (isGuinevere) ? "Guinevere" : "Ningen");\
    printf("   Csl   Evt   Code  |    HP/maxHP    lv   atd   gil   | Petal | Psn |  Odin  |  95  |  96  |  97  | Win | Lose |\n");\
    printf("   ------\n"); }\
    printf("   %d     %2d    %2d    |   %3d/%3d    %3d   %3d   %3d   |", currentCastle + 1, i, theEvent, theKnight.HP, maxHP, theKnight.level, theKnight.antidote, theKnight.gil);\
    printf("  %3d  |", nPetal);\
    printf("%3d  |", berryPoison);\
    printf("   %3d  |", metOdin);\
    printf(" %3c  |", (gotPaladin)   ? 'x' : ' ');\
    printf(" %3c  |", (gotLancelot)  ? 'x' : ' ');\
    printf(" %3c  |", (gotGuinevere) ? 'x' : ' ');\
    printf(" %3d |", nWin);\
    printf(" %3d  |", nLose);\
    if (gotExcalibur)       printf("   Ex");\
    if (gotLionHeart)       printf("   LnH");\
    if (gotScarlH)          printf("   Scrl");\
    if (gotMithril)         printf("   Mith");\
    if (hasEternalLove)     printf("   <3");\
    printf("\n"); \
    if (!currentEvent) printf("   ------\n")

#define LOG_INDEX_ORDER_2 \
    printf("Order: %d\n",NewIndex)

#endif


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
bool areFriendlyNumbers(int HP, int gil)
{
    long sum_of_divisors_HP = 0, sum_of_divisors_gil = 0;

    for (int i = 1; i < HP + 1; i++) {
        sum_of_divisors_HP += (HP % i == 0) ? i : 0;
    }

    for (int i = 1; i < gil + 1; i++) {
        sum_of_divisors_gil += (gil % i == 0) ? i : 0;
    }    
    
    if (sum_of_divisors_HP * gil == sum_of_divisors_gil * HP && gil != 0 && HP != 0)
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
int factorial(int n)
{
    if (n == 1) return 1;

    return n * factorial(n - 1);
}

// Contextual functions
bool isDrgKnight(int HP)
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
void loseHP(knight& theKnight, const int& event, const int& levelO)
{
    if (event == 99)
    {
        theKnight.HP = (theKnight.HP < 3) ? 1 : (theKnight.HP / 3);
    }
    else
    {
        float baseDamage[] = { 0.0, 1.0, 1.5, 4.5, 6.5, 8.5 };
        int damage = baseDamage[event] * levelO * 10;
        theKnight.HP -= damage;
    }
}
void levelUp(int& currentLevel, int desiredLevel, int& maxHP)
{
    if (currentLevel == 10) { return; }
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
        berryPoison--;

        if (berryPoison && knight.antidote > 0) {
            knight.antidote--;
            berryPoison = 0;
        }
    }
}
void limit(knight& knight, int& maxHP, int& nPetal)
{
    maxHP = (maxHP > 999) ? 999 : maxHP;
    nPetal = (nPetal > 99) ? 99 : nPetal;
    knight.HP = (knight.HP > maxHP) ? maxHP : knight.HP;
    knight.level = (knight.level > 10) ? 10 : knight.level;
    knight.antidote = (knight.antidote > 99) ? 99 : knight.antidote;
    knight.gil = (knight.gil > 999) ? 999 : knight.gil;
}
void gotoNextChallenge(castle* arrCastle, const int& nCastle, int& currentCastle, int& currentEvent, knight& theKnight, int& maxHP)
{
    if (currentEvent++ == arrCastle[currentCastle].nEvent - 1 || arrCastle[currentCastle].nEvent == 0)
    {
        levelUp(theKnight.level, theKnight.level + 1, maxHP);
        currentCastle = ++currentCastle % nCastle;
        currentEvent = 0;
    }
}
void goodTrade(int& berryPoison, bool isGuinevere, knight& theKnight, int maxHP)
{
    if (berryPoison)
    {
        berryPoison = 0;
    }                
    if (isGuinevere) { theKnight.gil += 50; }
    theKnight.HP = maxHP;
}
void fairTrade(int& berryPoison, knight& theKnight, int maxHP)
{
    if (berryPoison)
    {
        berryPoison = 0;
        theKnight.gil -= 50;
    }                
    if (theKnight.gil > 0)
    {
        theKnight.HP += theKnight.gil;
        theKnight.gil = (theKnight.HP > maxHP) ? (theKnight.HP - maxHP) : 0;
    }
}

// Mode-dependent fuctions
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
void makePermutation(int* srcArray, int* desArray, int leftValue, int rightValue, int& pmtCount)
{
    if (leftValue == rightValue)
    {
        int startPoint = (rightValue + 1) * pmtCount;
        for (int i = startPoint; i < startPoint + rightValue + 1; i++)
        {
            desArray[i] = srcArray[i % (rightValue + 1)];
        }
        pmtCount++;
    }
    else
    {
        for (int i = leftValue; i <= rightValue; i++)
        {
            swap(srcArray + leftValue, srcArray + i);
            makePermutation(srcArray, desArray, leftValue + 1, rightValue, pmtCount);

            // Backtrack ?
            swap(srcArray + leftValue, srcArray + i);
        }
    } 
}
void saveOptimalRoute(int bFlag, int petal, knight& bestKnight, const knight& theKnight, report& bestReport, int win, int lose)
{
    static int optimalPetal = 0;
    if (bFlag)
    {
        if (petal > optimalPetal)
        {
            optimalPetal = petal;

            bestReport.nPetal   = petal;
            bestReport.nWin     = win;
            bestReport.nLose   = lose;

            bestKnight = theKnight;

            LOG_OPTIMAL_ROUTE;
        }
    }
}

// Calculate and return "corresponding" bFlag, along with nWin and nLose
void process1(knight& theKnight, castle arrCastle[], int nCastle, int mode, int& nPetal, int& bFlag, int& nWin, int& nLose)
{
    bFlag = 0;
    nWin = 0;
    nLose = 0;

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
    bool isDragonKnight = isDrgKnight(theKnight.HP);

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
    int metOdin = 0;
    int metNina = 0;

    while (nPetal || isArthur)
    {
        // BEFORE EVENTS
        if (arrCastle[currentCastle].nEvent == 0) {
            gotoNextChallenge(arrCastle, nCastle, currentCastle, currentEvent, theKnight, maxHP);
            continue;
        }

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
            }
            else
            {
                nLose++;
                if ( !(gotMithril || isGuinevere) ) 
                { 
                    loseHP(theKnight, theEvent, levelO);
                }
            }
            if (berryPoison) 
            {
                loseHP(theKnight, theEvent, levelO);
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
            }
            else
            {
                nLose++;
                if ( !(gotMithril || isGuinevere && theEvent == 2) ) 
                { 
                    loseHP(theKnight, theEvent, levelO);
                }
            }
            if (berryPoison) 
            { 
                loseHP(theKnight, theEvent, levelO);
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
                if ( !(isPaladin || isDragonKnight) ) 
                { 
                    berryPoison = 6; 
                }
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
            if (!metNina)
            {
                metNina = 6; 
                if (areFriendlyNumbers(theKnight.HP, theKnight.gil))
                {
                    goodTrade(berryPoison, isGuinevere, theKnight, maxHP);
                    gotLionHeart = 6;
                }
                else if (gotScarlH || isGuinevere || isPaladin)
                {
                    goodTrade(berryPoison, isGuinevere, theKnight, maxHP);
                }
                else if (theKnight.gil >= 50)
                {
                    fairTrade(berryPoison, theKnight, maxHP);
                }
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

            if (theKnight.level >= levelO || gotLionHeart || hasEternalLove || isDragonKnight && metOdin)
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

        limit(theKnight, maxHP, nPetal);
        gotoNextChallenge(arrCastle, nCastle, currentCastle, currentEvent, theKnight, maxHP);
        limit(theKnight, maxHP, nPetal);
        
        LOG_STATE_AFTER_EVENT;
    }
}
void process2(knight& theKnight, castle arrCastle[], int nCastle, int mode, int& nPetal, int& bFlag, int& nWin, int& nLose)
{
    // Main idea: Go through every possible route and select the optimal result

    // Create an array of PERMUTED INDEX
    // Ex: 2 castles: { 0,1,  1,0 }                                         nPerm = 2
    //     3 castles: { 0,1,2,  0,2,1,  1,0,2,  1,2,0,  2,0,1,  2,1,0 }     nPerm = 6

    int castleIdx[] = { 0, 1, 2, 3, 4 };                                // List of possible indexes
    int* arrPermCastleIdx = new int[ nCastle * factorial(nCastle) ];    // A permuted array of indexes
    int nPerm = 0;                                                      //  = factorial(nCastle)
    
    makePermutation(castleIdx, arrPermCastleIdx, 0, nCastle - 1, nPerm);

    // Save the best stat a.k.a optimal stat
    report bestReport;
    {
        bestReport.nPetal = 0;
        bestReport.nWin = 0;
        bestReport.nLose = 0;
    }
    knight bestKnight = theKnight;  
    
    // Because we will be modifying these
    knight originalKnight = theKnight; 
    int originalPetal = nPetal;

    // Jump through routes and record optimal result to bestKnight and bestReport
    for (int currentRoute = 0; currentRoute < nPerm; currentRoute++) 
    {
        castle* tempCastle = new castle[nCastle];

        for (int Index = 0; Index < nCastle; Index++) 
        {
            // Copy -> Make event happen in order
            // Ex: tempCastle[0] -> arrCastle[2]
            //     tempCastle[1] -> arrCastle[0]
            //     tempCastle[2] -> arrCastle[1]

            int NewIndex =  arrPermCastleIdx[currentRoute * nCastle + Index];
            tempCastle[Index] = arrCastle[NewIndex];
            
            LOG_INDEX_ORDER_2;
        }

        // Fresh start for each route
        theKnight = originalKnight;
        nPetal = originalPetal;

        // Save route with max nPetal left into bestKnight and bestReport
        process1(theKnight, tempCastle, nCastle, mode, nPetal, bFlag, nWin, nLose);
        saveOptimalRoute(bFlag, nPetal, bestKnight, theKnight, bestReport, nWin, nLose);
        
        delete[] tempCastle;
    }

    // Synchronize with best result
    bFlag = bestReport.nPetal;
    theKnight = bestKnight;
    nPetal  = bestReport.nPetal;
    nWin    = bestReport.nWin;
    nLose   = bestReport.nLose;

    delete[] arrPermCastleIdx;
}

// Make a report
report* walkthrough (knight& theKnight, castle arrCastle[], int nCastle, int mode, int nPetal)
{
    report* pReturn;
    int bFlag;
    //fighting for the existence of mankind here

    int nWin = 0;
    int nLose = 0;

    if (mode == 0 || mode == 1) {
        process1(theKnight, arrCastle, nCastle, mode, nPetal, bFlag, nWin, nLose);
    }
    else if (mode == 2) {
        process2(theKnight, arrCastle, nCastle, mode, nPetal, bFlag, nWin, nLose);
    }
    
    // success or failure?	
    pReturn = (bFlag) ? new report : NULL;
    if (pReturn)
    {
        pReturn->nPetal = nPetal;
        pReturn->nWin   = nWin;
        pReturn->nLose  = nLose;
    }
    return pReturn;
}
