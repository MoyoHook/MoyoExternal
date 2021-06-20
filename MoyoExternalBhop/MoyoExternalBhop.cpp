// MoyoExternalBhop.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <Windows.h>
#include <iostream>
#include "MemMan.h"

MemMan MemClass;

int main()
{
    float version = 0.1;

    std::cout << "  __  __                   ____  _                 \n |  \\/  | ___  _   _  ___ | __ )| |__   ___  _ __  \n | |\\/| |/ _ \\| | | |/ _ \\|  _ \\| '_ \\ / _ \\| '_ \\ \n | |  | | (_) | |_| | (_) | |_) | | | | (_) | |_) |\n |_|  |_|\\___/ \\__, |\\___/|____/|_| |_|\\___/| .__/ \n               |___/                        |_|    \n--------------------------------------------------\nversion: " << version << std::endl;
    
    std::cout << "\n[+] getting CSGO Process..." << std::endl;

    DWORD process, client, localPlayer;
    BYTE flag;

    //offsets
    DWORD dwLocalPlayer = 0xD892CC;
    DWORD dwForceJump = 0x524BF4C;
    DWORD m_fFlags = 0x104;

    try {
        process = MemClass.getProcess("csgo.exe");
        client = MemClass.getModule(process, "client.dll");
    }
    catch(const std::exception& e){
        std::cout << "[!] ERROR: " << e.what() << std::endl;
    }

    if (client == NULL) {
        std::cout << "[!] CSGO process not found!" << std::endl;
    }
    else {
        std::cout << "[+] Process found! Address: " << std::hex << client << std::endl;
        localPlayer = MemClass.readMem<DWORD>(client + dwLocalPlayer);
        if (localPlayer == NULL) {
            std::cout << "[+] Can't find Local Player. Waiting for gamestatus update..." << std::endl;
            while (localPlayer == NULL)
            {
                localPlayer = MemClass.readMem<DWORD>(client + dwLocalPlayer);
            }
        }
        std::cout << "[+] Local Player Address: " << std::hex << localPlayer << std::endl;

        //loop
        while (true)
        {
            if (GetAsyncKeyState(VK_INSERT)) {
                localPlayer = MemClass.readMem<DWORD>(client + dwLocalPlayer);
                std::cout << "[+] New Player Address: " << std::hex << localPlayer << std::endl;
                while (GetAsyncKeyState(VK_INSERT)){}
            }
            flag = MemClass.readMem<BYTE>(localPlayer + m_fFlags);
            if (GetAsyncKeyState(VK_SPACE) && flag & (1 << 0)) {
                MemClass.writeMem<DWORD>(client + dwForceJump, 6);
            }

            Sleep(1);
        }

    }

}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
