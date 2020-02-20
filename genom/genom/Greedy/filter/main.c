#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "assemblage.h"
#include "Menu.h"
#include "Recherche.h"
#include "motdepass.h"

void fullscreen(){
keybd_event(VK_MENU,0x38,0,0);
keybd_event(VK_RETURN,0x1c,0,0);
keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

int main(){
    fullscreen();
    welcome();
    motDePasse();
    menu();
    return 0;
}
