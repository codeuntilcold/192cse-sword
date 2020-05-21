#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif

////////////////// USER DEFINED /////////////////
#define LOG(x) std::cout << x << std::endl

enum Drop { LionHeart = 8 };

bool areFriendlyNumbers(int HP, int gil)
{
    float HP_abd;
    float gil_abd;

    for (int i = 1; i < HP + 1; i++)
        HP_abd = (HP % i == 0) ? (HP_abd + i) : HP_abd;
    HP_abd = HP_abd / HP;

    for (int i = 1; i < gil + 1; i++)
        gil_abd = (gil % i == 0) ? (gil_abd + i) : gil_abd;
    gil_abd = gil_abd / gil;

    if (HP_abd == gil_abd) { return true; }
    else return false;
}

report* walkthrough (knight& theKnight, castle arrCastle[], int nCastle, int mode, int nPetal)
{
    report* pReturn;
    int bFlag;
    //fighting for the existence of mankind here

    int maxHP = theKnight.HP;

    int currentCastle = 0;
    int currentEvent = 0;

    int thisEvent = 0;
    int i = 0;
    int levelO = 0, b = 0;

    int nWin = 0;
    int nLose = 0;

    // Bunch of flags
    bool gotPaladin = false;
    bool gotLancelot = false;
    bool gotGuinevere = false;
    bool gotExcalibur = false;
    bool beatUltimecia = false;

    int berryPoison = 0;
    int gotLionHeart = 0;
    

    while (nPetal)
    {
        // BEFORE EVENTS
        thisEvent = arrCastle[currentCastle].arrEvent[currentEvent];
        i = currentEvent + 1;

        b = i % 10;
		levelO = (i > 6) ? (b > 5 ? b : 5) : b;


        // DURING EVENTS
        switch (thisEvent)
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
            if (gotPaladin && gotLancelot && gotPaladin) { gotExcalibur = true; }
        break;
        case 99:    // ULTIMECIA
            if (gotExcalibur || gotLionHeart) 
            { 
                nWin++;
                beatUltimecia = true;

                if (berryPoison) { theKnight.HP = (theKnight.HP < 3) ? 1 : (theKnight.HP / 3); }
            }
            else
            {
                nLose++;
                theKnight.HP = (theKnight.HP < 3) ? 1 : (theKnight.HP / 3);
            }  
        break;
        
        case 1:     // GIL FARM
        case 2:
        case 3:
        case 4:
        case 5:
            if (theKnight.level > levelO && gotExcalibur || gotLionHeart)
            {
                nWin++;

                switch (thisEvent)
                {
                case 1: theKnight.gil += 100; break;
                case 2: theKnight.gil += 150; break;
                case 3: theKnight.gil += 450; break;
                case 4: theKnight.gil += 650; break;
                case 5: theKnight.gil += 850; break;
                }

                if (berryPoison)
                {
                    float baseDamage;
                    switch (thisEvent)
                    {
                    case 1: baseDamage = 1; break;
                    case 2:	baseDamage = 1.5; break;
                    case 3:	baseDamage = 4.5; break;
                    case 4:	baseDamage = 6.5; break;
                    case 5:	baseDamage = 8.5; break;
                    }
                    
                    int damage = baseDamage * levelO * 10;
                    theKnight.HP -= damage;
                }
            }
            else
            {
                nLose++;

                float baseDamage;
				switch (thisEvent)
				{
				case 1: baseDamage = 1; break;
				case 2:	baseDamage = 1.5; break;
				case 3:	baseDamage = 4.5; break;
				case 4:	baseDamage = 6.5; break;
				case 5:	baseDamage = 8.5; break;
				}
				
				int damage = baseDamage * levelO * 10;
				theKnight.HP -= damage;
            }
        break;

        case 6:     // TORNBERRY
            if (berryPoison) { break; }

            if (theKnight.level > levelO && gotExcalibur || gotLionHeart)
            {
                nWin++;
                theKnight.level++;
            }
            else
            {
                nLose++;
                berryPoison = 6;
            }
        break;

        case 7:     // QUEEN OF CARDS
            if (theKnight.level > levelO && gotExcalibur || gotLionHeart)
            {
                nWin++;
                theKnight.gil *= 2;
            }
            else
            {
                nLose++;
                theKnight.gil /= 2;
            }  
        break;
        
        case 8:     // NINA DE RINGS
            if (!areFriendlyNumbers(theKnight.HP, theKnight.gil))
            {   
                if (theKnight.gil < 50) { break; }
                else
                {
                    if (berryPoison) { theKnight.gil -= 50; berryPoison = 0; }

                    if (theKnight.gil > 0)
                    {
                        theKnight.HP = theKnight.HP + theKnight.gil;
                        theKnight.gil = (theKnight.HP > maxHP) ? (theKnight.HP - maxHP) : 0;
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
        break;
        
        case 10:    // ANTIDOTE
        break;
        
        case 11:    // ODIN
        break;
        
        case 12:    // MERLIN
        break;
        
        case 13:    // OMEGA WEAPON
        break;
        
        case 14:    // HADES
        break;
        
        case 15:    // SCARLET HAKAMA
        break;
        
        case 16:    // LOCKED DOOR
        break;
        }   // END EVENT

        // AFTER EVENTS

        nPetal--;

        if (gotLionHeart) { gotLionHeart--; }

        if (beatUltimecia) { bFlag = 1; break; }

        if (currentEvent++ == arrCastle[currentCastle].nEvent - 1)
        {
            theKnight.level++;
            maxHP += 100;

            currentCastle++;
            currentEvent = 0;
        }

        if (currentCastle == nCastle)
        {
            currentCastle = 0;
            currentEvent = 0;
        }


        if (theKnight.HP < 1)
        {
            callPhoenix(theKnight, maxHP);
            berryPoison = 0;
        }

        if (berryPoison)
        {
            if (theKnight.antidote > 0)
            {
                theKnight.antidote--;
                berryPoison = 0;
            }
            else
            {
                berryPoison--;
            } 
        }

        maxHP = (maxHP > 999) ? 999 : maxHP;
        theKnight.HP = (theKnight.HP > maxHP) ? maxHP : theKnight.HP;
        theKnight.level = (theKnight.level > 10) ? 10 : theKnight.level;





        //if (--nPetal == 0) { break; }

    }


    // success or failure?	
    pReturn = (bFlag) ? new report : NULL;


    pReturn->nPetal = nPetal;
    pReturn->nWin = nWin;
    pReturn->nLose = nLose;

    return pReturn;
}