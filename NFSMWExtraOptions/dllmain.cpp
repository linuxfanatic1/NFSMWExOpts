﻿#include "stdafx.h"
#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include <cstdint>
#include "..\includes\IniReader.h"
#include <math.h>

float heatLevel, gameSpeed, FallingRainSize, RainAmount, RoadReflection, RainIntensity, RainXing, RainFallSpeed, RainGravity, SplashScreenTimeLimit, LowBeamAmount, HighBeamAmount, MaxHeatLevel, MinHeatLevel, copLightsAmount, WorldAnimationSpeed, CarScale;
int hotkeyToggleForceHeat, hotkeyForceHeatLevel, hotkeyToggleCopLights, hotkeyToggleHeadLights, hotkeyCarHack, hotkeyUnlockAllTracks, hotkeyDrunkDriver, randomizeCount;
unsigned char raceType, raceMode,  minLaps, maxLaps, minOpponents, maxOpponents, maxLapsRandomQR, maxOpponentsRandomQR, maxBlacklist, csBlacklist, headLightsMode, lowTraffic, medTraffic, highTraffic;
bool copLightsEnabled, ShowTollbooth, ShowCops, HideOnline, ShowOnlineOpts, removeSceneryGroupDoor, removePlayerBarriers, unfreezeKO, EnablePresetAndDebugCars, EnableCustomizationForAll, AlwaysRain, WindowedMode, SkipMovies, EnableSound, EnableMusic, EnableCameras, nlgzrgnTakeOver, ShowSubs, EnableHeatLevelOverride, UseWSMWSplashBack, CarbonStyleRaceProgress, moreVinyls, eatSomeBurgers, unlockAllTracks, onQuickRaceMenu, ShowChallenge, ShowHiddenTracks, GarageRotate, GarageZoom, GarageShowcase;
DWORD selectedCar, careerCar, raceOptions, Strings, HeatLevelAddr;

DWORD WINAPI Thing(LPVOID);
bool forceHeatLevel = 0, carHackEnabled = 0, once1 = 0, once2 = 0, once3 = 0;

DWORD CameraNamesCodeCaveExit = 0x51C98C;
DWORD HeatLevelsCodeCaveExit = 0x443dc9;
DWORD WideSplashScreenCodeCaveExit = 0x5C46EA;
DWORD WideSplashScreenCodeCave2Exit = 0x5B9630;
DWORD WideSplashScreenCodeCave3Exit = 0x5BC6B1;
DWORD VinylMenuCodeCaveExit = 0x7BC908;
DWORD VinylMenuCodeCaveCall = 0x7BB560;
DWORD VinylMenuCodeCave2Exit = 0x7BD30F;
DWORD VinylMenuCodeCave2ifAbove = 0x7BD210;
DWORD RaceHackTypeCodeCaveExit = 0x5FAA2F;
DWORD RaceHackReplaceCodeCaveExit = 0x601085;
DWORD IconFixCodeCaveExit = 0x56E099;
DWORD LANRaceSelectFixCodeCaveExit = 0x7aa8ed;
DWORD LANRaceModeFixCodeCaveExit = 0x5395a3;
DWORD LANRaceModeFixCodeCave2Exit = 0x535ecb;
DWORD StringReplacementCodeCaveExit = 0x56bbd5;

char* StringBuffer1 = "© 2005 Electronic Arts Inc. All Rights Reserved.^NFSMW Extra Options - © 2016 nlgzrgn. No Rights Reserved.";
DWORD _A7EBC389_New = (DWORD)StringBuffer1;

void __declspec(naked) CameraNamesCodeCave()
{
	_asm
	{
			cmp ecx, 0
			je bumper
			cmp ecx, 1
			je hood
			cmp ecx, 2
			je close
			cmp ecx, 3
			je farcam
			cmp ecx, 4
			je superfar
			cmp ecx, 5
			je drift
			cmp ecx, 6
			je pursuit
			jmp CameraNamesCodeCaveExit

		bumper :
			mov eax, 0xC3E9AE58
			jmp CameraNamesCodeCaveExit

		hood :
			mov eax, 0x414F19D7
			jmp CameraNamesCodeCaveExit

		close :
			mov eax, 0x5AE3441F
			jmp CameraNamesCodeCaveExit

		farcam :
			mov eax, 0x1EA4CEC2
			jmp CameraNamesCodeCaveExit

		superfar :
			mov eax, 0x916039B4
			jmp CameraNamesCodeCaveExit

		drift :
			mov eax, 0xA1211428
			jmp CameraNamesCodeCaveExit

		pursuit :
			mov eax, 0x7448870B
			jmp CameraNamesCodeCaveExit
	}
}

void __declspec(naked) HeatLevelsCodeCave()
{
	_asm
	{
			cmp EnableHeatLevelOverride,1
			jne dontforceMinMaxHeat

		forceMinMaxHeat:
			mov ebx, MaxHeatLevel
			mov [esi + 0xE0], ebx
			mov ebx, MinHeatLevel
			mov [esi + 0xDC], ebx

		dontforceMinMaxHeat:
			mov edx, [esi + 0xE0]
			jmp HeatLevelsCodeCaveExit

	}
}

void __declspec(naked) WideSplashScreenCodeCave()
{
	_asm
	{
			cmp dword ptr ds : [ebx + 0x08], 0x9C8FC0EE // If the texture is demo_splash
			jne continueifnotdemosplash
			mov dword ptr ds : [ebx + 0x58], 0x44558000 // Change 640 to 854
			mov dword ptr ds : [ebx + 0x08], 0x531A68C8 // Replace it with ws_mwsplashback
			mov dword ptr ds : [ebx - 0x04], 0x531A68C8

		continueifnotdemosplash :
			mov eax, [ebx + 0x08]
			mov edx, [esi + 0x0C]
			jmp WideSplashScreenCodeCaveExit
	}
}

void __declspec(naked) WideSplashScreenCodeCave2()
{
	_asm
	{
			cmp ecx, 0x9C8FC0EE
			jne continueifnotdemosplash
			mov ecx, 0x531A68C8

		continueifnotdemosplash :
			mov[eax + 0x34], ecx
			mov[eax + 0x2C], cl
			jmp WideSplashScreenCodeCave2Exit
	}
}

void __declspec(naked) WideSplashScreenCodeCave3()
{
	_asm
	{
			cmp eax, 0x9C8FC0EE
			jne continueifnotdemosplash
			mov eax, 0x531A68C8

		continueifnotdemosplash :
			mov [edx + 0x24], eax
			pop esi
			mov al, 0x01
			jmp WideSplashScreenCodeCave3Exit
	}
}

void __declspec(naked) VinylMenuCodeCave()
{
	_asm
	{
			mov edx, dword ptr ds : [0x905EB0]
			push 0x0000040A
			push 0xB715070A
			push 0x55778E5A
			push edx
			mov ecx, esi
			call VinylMenuCodeCaveCall
			lea eax, [esp + 0x14]
			mov ebp, 0x00000001
			jmp VinylMenuCodeCaveExit
	}
}

void __declspec(naked) VinylMenuCodeCave2()
{
	_asm
	{
				cmp eax,0x06
				ja ifabove

				cmp eax, 0x00
				je stripes
				cmp eax, 0x01
				je raceflags
				cmp eax, 0x02
				je nflags
				cmp eax, 0x03
				je body
				cmp eax, 0x04
				je uniques
				cmp eax, 0x05
				je contest
				cmp eax, 0x06
				je specials
				jmp VinylMenuCodeCave2Exit


			stripes :
				mov dword ptr ds : [edi + 0x15C], 0x1C619FD8
				mov ebp, 0xF7352706
				mov dword ptr ds : [esp + 0x18], 0x00000002
				jmp VinylMenuCodeCave2Exit

			raceflags :
				mov dword ptr ds : [edi + 0x15C], 0x9C1B8935
				mov ebp, 0x1223CC89
				mov dword ptr ds : [esp + 0x18], 0x00000003
				jmp VinylMenuCodeCave2Exit

			nflags :
				mov dword ptr ds : [edi + 0x15C], 0x7956F7B0
				mov ebp, 0xBC44BBCB
				mov dword ptr ds : [esp + 0x18], 0x00000004
				jmp VinylMenuCodeCave2Exit

			body :
				mov dword ptr ds : [edi + 0x15C], 0x2D5BFF0F
				mov ebp, 0x694CA0CA
				mov dword ptr ds : [esp + 0x18], 0x00000005
				jmp VinylMenuCodeCave2Exit

			uniques :
				mov dword ptr ds : [edi + 0x15C], 0x209A9158
				mov ebp, 0x1B3A8DD3
				mov dword ptr ds : [esp + 0x18], 0x00000006
				jmp VinylMenuCodeCave2Exit

			contest :
				mov dword ptr ds : [edi + 0x15C], 0xCD057D21
				mov ebp, 0x1BA508FC
				mov dword ptr ds : [esp + 0x18], 0x00000007
				jmp VinylMenuCodeCave2Exit

			specials :
				mov dword ptr ds : [edi + 0x15C], 0xB715070A
				mov ebp, 0x55778E5A
				mov dword ptr ds : [esp + 0x18], 0x0000008
				jmp VinylMenuCodeCave2Exit

			ifabove:
				jmp VinylMenuCodeCave2ifAbove
	}
	
}

void __declspec(naked) RaceHackTypeCodeCave()
{
	_asm
	{
		    cmp unlockAllTracks, 0x01
			jne originalcode

			cmp onQuickRaceMenu, 0x01
			jne originalcode

			cmp word ptr ds : [eax + 0x04], 0x3931 //Bin19 races (challenge series)
			je disable

			cmp ShowHiddenTracks, 0x01
			jne originalcode

			cmp dword ptr ds : [eax + 0x04], 0x312E3032 //20.1
			je circuit
			cmp dword ptr ds : [eax + 0x04], 0x4C78614D //MaxLoad
			je circuit
			cmp dword ptr ds : [eax + 0x04], 0x322E3032 //20.2
			je sprint
			cmp dword ptr ds : [eax + 0x04], 0x352E3032 //20.5
			je speedtrap
			cmp dword ptr ds : [eax + 0x04], 0x382E3032 //20.8
			je challenge
			jmp originalcode

		disable :
			mov eax, 0xFFFFFFFF
			jmp caveexit

		circuit :
			mov eax, 0x01
			jmp caveexit

		sprint :
			mov eax, 0x00
			jmp caveexit

		speedtrap :
			mov eax, 0x05
			jmp caveexit

		challenge :
			mov eax, 0x08
			jmp caveexit

		originalcode:
			movsx eax, [eax + 0x2B]

		caveexit:
			pop esi
			jmp RaceHackTypeCodeCaveExit

	}
}

void __declspec(naked) RaceHackReplaceCodeCave()
{
	_asm
	{
		    cmp unlockAllTracks,0x01
			jne originalcode
				
			cmp ShowHiddenTracks, 0x01
			jne originalcode

			cmp onQuickRaceMenu,0x01
			jne originalcode

			cmp eax, 0xC277386E
			je id20_1_1
			cmp eax, 0x3F1C4413
			je id20_1_2
			cmp eax, 0xCD554B51
			je id20_2_2
			cmp eax, 0x4947B022
			je id20_5_1
			cmp eax, 0x4B1B5DC1
			je id20_8_1
			cmp eax, 0x8EF7922B
			je id99_1_1
			jmp originalcode

			id20_1_1 :
				mov eax, 0xF984278B
				jmp originalcode

			id20_1_2 :
				mov eax, 0xA137ED5B
				jmp originalcode

			id20_2_2 :
				mov eax, 0xC2AC6CB3
				jmp originalcode

			id20_5_1 :
				mov eax, 0x9C614397
				jmp originalcode

			id20_8_1 :
				mov eax, 0x102E6410
				jmp originalcode

			id99_1_1 :
				mov eax, 0xAE6F0CB0
				jmp originalcode
			
			originalcode:
				mov ecx, dword ptr ds: [0x0091E004]
				jmp RaceHackReplaceCodeCaveExit
	} 
}

void __declspec(naked) IconFixCodeCave()
{
	_asm
	{
		mov eax, 0x9A962438
		cmp ecx, 0x05
		jmp IconFixCodeCaveExit
	}
}

void __declspec(naked) LANRaceSelectFixCodeCave() 
{
	_asm
	{
			cmp ecx,0x04 //Tollbooth
			je fixassprint
			cmp ecx, 0x05 //Speedtrap
			je fixassprint
			cmp ecx,0x08 //Challenge
			je fixassprint
			cmp ecx,0x03 //Knockout
			je fixascircuit
			jmp originalcode

		fixassprint:
			mov ecx,0x00
			jmp originalcode

		fixascircuit:
			mov ecx,0x01
			jmp originalcode

		originalcode:
			mov dword ptr ds: [edx+0x168],ecx
			jmp LANRaceSelectFixCodeCaveExit

	}
}

void __declspec(naked) LANRaceModeFixCodeCave()
{
	_asm
	{
			cmp eax,0x00
			je sprint
			cmp eax,0x01
			je circuit
			cmp eax,0x02
			je drag
			cmp eax,0x03
			je knockout
			cmp eax,0x04
			je tollbooth
			cmp eax,0x05
			je speedtrap
			cmp eax,0x08
			je challenge
			mov ebx, 0x7818F85E // unknown
			mov ebp, 0x9A962438 // challenge icon
			
			jmp LANRaceModeFixCodeCaveExit

			circuit:
				mov ebx, 0x034FA2C1
				mov ebp, 0xE9638D3E
				jmp LANRaceModeFixCodeCaveExit

			sprint :
				mov ebx, 0xB94FD70E
				mov ebp, 0x2521E5EB
				jmp LANRaceModeFixCodeCaveExit
				
			drag :
				mov ebx, 0x6F547E4C
				mov ebp, 0xAAAB31E9
				jmp LANRaceModeFixCodeCaveExit

			knockout :
				mov ebx, 0x4930F5FC
				mov ebp, 0x3A015595
				jmp LANRaceModeFixCodeCaveExit

			tollbooth :
				mov ebx, 0xA15E4505
				mov ebp, 0x1A091045
				jmp LANRaceModeFixCodeCaveExit

			speedtrap :
				mov ebx, 0xEE1EDC76
				mov ebp, 0x66C9A7B6
				jmp LANRaceModeFixCodeCaveExit

			challenge :
				mov ebx, 0x213CC8D1
				mov ebp, 0x9A962438
				jmp LANRaceModeFixCodeCaveExit

	}
}

void __declspec(naked) LANRaceModeFixCodeCave2()
{
	_asm
	{
			
			cmp eax, 0x00
			je sprint
			cmp eax, 0x01
			je circuit
			cmp eax, 0x02
			je drag
			cmp eax, 0x03
			je knockout
			cmp eax, 0x04
			je tollbooth
			cmp eax, 0x05
			je speedtrap
			cmp eax, 0x08
			je challenge
			mov ebp, 0x7818F85E // Unknown
			mov eax, 0x9A962438 // Challenge Icon
			jmp LANRaceModeFixCodeCave2Exit

		circuit :
			mov ebp, 0x034FA2C1
			mov eax, 0xE9638D3E
			jmp LANRaceModeFixCodeCave2Exit

		sprint :
			mov ebp, 0xB94FD70E
			mov eax, 0x2521E5EB
			jmp LANRaceModeFixCodeCave2Exit

		drag :
			mov ebp, 0x6F547E4C
			mov eax, 0xAAAB31E9
			jmp LANRaceModeFixCodeCave2Exit

		knockout :
			mov ebp, 0x4930F5FC
			mov eax, 0x3A015595
			jmp LANRaceModeFixCodeCave2Exit

		tollbooth :
			mov ebp, 0xA15E4505
			mov eax, 0x1A091045
			jmp LANRaceModeFixCodeCave2Exit

		speedtrap :
			mov ebp, 0xEE1EDC76
			mov eax, 0x66C9A7B6
			jmp LANRaceModeFixCodeCave2Exit

		challenge :
			mov ebp, 0x213CC8D1
			mov eax, 0x9A962438
			jmp LANRaceModeFixCodeCave2Exit

	}
}

void __declspec(naked) StringReplacementCodeCave()
{
	_asm
	{
			mov ecx, dword ptr ds: [ebx + eax * 0x08]

			cmp nlgzrgnTakeOver,0x00
			je continuee
			cmp ecx, 0xA7EBC389
			je ReplaceCopyrightString
			// cmp ecx, AnotherStringHashHere
			// je ReplaceAnotherString
			jmp continuee

		ReplaceCopyrightString:
			cmp once1, 0x01
			je continuee

			mov ecx, _A7EBC389_New			
			mov dword ptr [ebx + eax * 0x08 + 0x04], ecx

			mov once1, 0x01
			mov ecx, 0xA7EBC389

		continuee :
			cmp ecx, edx
			jmp StringReplacementCodeCaveExit

	}
}


void Init()
{
	CIniReader iniReader("NFSMWExtraOptionsSettings.ini");

	// Hotkeys
	hotkeyToggleForceHeat = iniReader.ReadInteger("Hotkeys", "HeatLevelHack", 118); //F7
	hotkeyForceHeatLevel = iniReader.ReadInteger("Hotkeys", "ChangeHeatLevel", 48); //0 (Not NUM0)
	hotkeyToggleCopLights = iniReader.ReadInteger("Hotkeys", "CopLights", 79); // O
	hotkeyToggleHeadLights = iniReader.ReadInteger("Hotkeys", "HeadLights", 72); // H
	hotkeyCarHack = iniReader.ReadInteger("Hotkeys", "FreezeCar", 115); //F4
	hotkeyUnlockAllTracks = iniReader.ReadInteger("Hotkeys", "UnlockAllTracks", 116); //F5
	hotkeyDrunkDriver = iniReader.ReadInteger("Hotkeys", "AutoDrive", 117); //F6
	
	// LapControllers
	minLaps = iniReader.ReadInteger("LapControllers", "Minimum", 0);
	maxLaps = iniReader.ReadInteger("LapControllers", "Maximum", 127);
	maxLapsRandomQR = iniReader.ReadInteger("LapControllers", "RandomRace", 127);
	unfreezeKO = iniReader.ReadInteger("LapControllers", "UnfreezeKO", 1) == 1;

	// OpponentControllers
	minOpponents = iniReader.ReadInteger("OpponentControllers", "Minimum", 0);
	maxOpponents = iniReader.ReadInteger("OpponentControllers", "Maximum", 6);
	maxOpponentsRandomQR = iniReader.ReadInteger("OpponentControllers", "RandomRace", 6);

	// TrafficControllers
	lowTraffic = iniReader.ReadInteger("TrafficControllers", "Low", 10);
	medTraffic = iniReader.ReadInteger("TrafficControllers", "Medium", 30);
	highTraffic = iniReader.ReadInteger("TrafficControllers", "High", 50);

	// Menu
	ShowTollbooth = iniReader.ReadInteger("Menu", "ShowTollbooth", 1) == 1;
	ShowChallenge = iniReader.ReadInteger("Menu", "ShowChallenge", 1) == 1;
	ShowCops = iniReader.ReadInteger("Menu", "ShowCops", 1) == 1;
	HideOnline = iniReader.ReadInteger("Menu", "ShowOnline", 0) == 0;
	ShowOnlineOpts = iniReader.ReadInteger("Menu", "ShowOnlineOpts", 0) == 1;
	ShowSubs = iniReader.ReadInteger("Menu", "ShowSubs", 0) == 1;
	EnablePresetAndDebugCars = iniReader.ReadInteger("Menu", "ShowMoreCarCategories", 0) == 1;
	EnableCustomizationForAll = iniReader.ReadInteger("Menu", "ShowAllCustomizationsForAllCars", 1) == 1;
	moreVinyls = iniReader.ReadInteger("Menu", "ShowSpecialVinyls", 1) == 1;
	ShowHiddenTracks = iniReader.ReadInteger("Menu", "ShowHiddenTracks", 1) == 1;
	maxBlacklist = iniReader.ReadInteger("Menu", "MaximumBlacklistRival", 15);
	csBlacklist = iniReader.ReadInteger("Menu", "ChallengeSeriesBlacklist", 19);
	randomizeCount = iniReader.ReadInteger("Menu", "RandomizeCount", 30);
	SplashScreenTimeLimit = iniReader.ReadFloat("Menu", "SplashScreenTimeLimit", 30.0f);
	UseWSMWSplashBack = iniReader.ReadInteger("Menu", "WideSplashScreen", 0) == 1;
	GarageZoom = iniReader.ReadInteger("Menu", "ShowcaseCamInfiniteZoom", 0) == 1;
	GarageRotate = iniReader.ReadInteger("Menu", "ShowcaseCamInfiniteRotation", 0) == 1;
	GarageShowcase = iniReader.ReadInteger("Menu", "ShowcaseCamAlwaysEnable", 0) == 1;
	nlgzrgnTakeOver = iniReader.ReadInteger("Menu", "DisableTakeover", 0) == 0;

	// Gameplay
	EnableCameras = iniReader.ReadInteger("Gameplay", "EnableHiddenCameraModes", 0) == 1;
	gameSpeed = iniReader.ReadFloat("Gameplay", "GameSpeed", 1.0f);
	WorldAnimationSpeed = iniReader.ReadFloat("Gameplay", "WorldAnimationSpeed", 45.0f);
	CarScale = iniReader.ReadFloat("Gameplay", "CarScale", 1.0f);
	copLightsEnabled = iniReader.ReadInteger("Gameplay", "CopLightsMode", 0) == 1;
	copLightsAmount = iniReader.ReadFloat("Gameplay", "CopLightsBrightness", 1.00f);
	headLightsMode = iniReader.ReadInteger("Gameplay", "HeadLightsMode", 2);
	LowBeamAmount = iniReader.ReadFloat("Gameplay", "LowBeamBrightness", 0.75f);
	HighBeamAmount = iniReader.ReadFloat("Gameplay", "HighBeamBrightness", 1.00f);
	removeSceneryGroupDoor = iniReader.ReadInteger("Gameplay", "RemoveOldBridgeBarrier", 0) == 1;
	removePlayerBarriers = iniReader.ReadInteger("Gameplay", "RemoveNeonBarriers", 0) == 1;
	CarbonStyleRaceProgress = iniReader.ReadInteger("Gameplay", "ShowPercentOn1LapRaces", 0) == 1;
	unlockAllTracks = iniReader.ReadInteger("Gameplay", "UnlockAllTracks", 0) == 1;
	eatSomeBurgers = iniReader.ReadInteger("Gameplay", "UnlockBurgerKingChallenge", 0) == 1;

	// Pursuit
	EnableHeatLevelOverride = iniReader.ReadInteger("Pursuit", "HeatLevelOverride", 0) == 1;
	MinHeatLevel = iniReader.ReadFloat("Pursuit", "MinimumHeatLevel", 1.00f);
	MaxHeatLevel = iniReader.ReadFloat("Pursuit", "MaximumHeatLevel", 10.00f);

	// Weather
	AlwaysRain = iniReader.ReadInteger("Weather", "AlwaysRain", 0) == 1;
	RainAmount = iniReader.ReadFloat("Weather", "GeneralRainAmount", 1.0f);
	RoadReflection = iniReader.ReadFloat("Weather", "RoadReflectionAmount", 1.0f);
	FallingRainSize = iniReader.ReadFloat("Weather", "RainSize", 0.01f);
	RainIntensity = iniReader.ReadFloat("Weather", "RainIntensity", 0.45f);
	RainXing = iniReader.ReadFloat("Weather", "RainCrossing", 0.02f);
	RainFallSpeed = iniReader.ReadFloat("Weather", "RainSpeed", 0.03f);
	RainGravity = iniReader.ReadFloat("Weather", "RainGravity", 0.35f);

	// Misc
	WindowedMode = iniReader.ReadInteger("Misc", "WindowedMode", 0) == 1;
	SkipMovies = iniReader.ReadInteger("Misc", "SkipMovies", 0) == 1;
	EnableSound = iniReader.ReadInteger("Misc", "EnableSound", 1) == 1;
	EnableMusic = iniReader.ReadInteger("Misc", "EnableMusic", 1) == 1;
		

	// Limit values to fix increment & decrement behaviour breaking
	if (minLaps < 0 || minLaps > 127) minLaps = 1;
	if (maxLaps < 0 || maxLaps > 127) maxLaps = 8;
	if (maxLapsRandomQR < 0 || maxLapsRandomQR > 127) maxLapsRandomQR = 5;

	if (minOpponents < 0 || minOpponents > 15) minOpponents = 1;
	if (maxOpponents < 0 || maxOpponents > 15) maxOpponents = 3;
	if (maxOpponentsRandomQR < 0 || maxOpponentsRandomQR > 15) maxOpponentsRandomQR = 3;

	if (MaxHeatLevel < 1 || MaxHeatLevel < MinHeatLevel || MaxHeatLevel > 10) MaxHeatLevel = 5;
	if (MinHeatLevel < 1 || MaxHeatLevel < MinHeatLevel || MinHeatLevel > 10) MinHeatLevel = 1;
	if (headLightsMode > 2) headLightsMode = 2;

	if (randomizeCount < 1 || randomizeCount>500) randomizeCount = 30;

	if (lowTraffic < 0 || lowTraffic > 100) lowTraffic = 10;
	if (medTraffic < 0 || medTraffic > 100) medTraffic = 30;
	if (highTraffic < 0 || highTraffic > 100) highTraffic = 50;


	// Remove 1-8 Lap Restriction
	injector::WriteMemory<unsigned char>(0x7AC3EC, minLaps, true); // Decrease lap count min lap controller
	injector::WriteMemory<unsigned char>(0x7AC3F0, maxLaps, true); // Decrease lap count max lap controller
	injector::WriteMemory<unsigned char>(0x7AC405, minLaps, true); // Increase lap count min lap controller
	injector::WriteMemory<unsigned char>(0x7AC401, maxLaps, true); // Increase lap count max lap controller
	// LAN Lobby
	injector::WriteMemory<unsigned char>(0x556bb5, maxLaps, true);
	injector::WriteMemory<unsigned char>(0x556bde, maxLaps, true);
	injector::WriteMemory<unsigned char>(0x556bc4, minLaps, true);
	injector::WriteMemory<unsigned char>(0x556bcf, minLaps, true);

	// Number of bots - Note: 4th and beyond opponents gets bugged cars.
	injector::WriteMemory<unsigned char>(0x7abff9, minOpponents, true); // Decrease opponents count min opponent controller
	injector::WriteMemory<unsigned char>(0x7abffd, maxOpponents + 0x01, true); // Decrease opponents count max opponent controller
	injector::WriteMemory<unsigned char>(0x7ac01a, minOpponents, true); // Increase opponents count min opponent controller
	injector::WriteMemory<unsigned char>(0x7ac00e, maxOpponents + 0x01, true); // Increase opponents count max opponent controller

	// Random Race Laps and Opponents
	injector::WriteMemory<unsigned char>(0x56DCC1, maxOpponentsRandomQR, true); // Random Race Max Opponent Controller
	injector::WriteMemory<unsigned char>(0x56DCE9, maxLapsRandomQR, true); // Random Race Max Lap Controller

	// Traffic Density Controllers (0-100)
	injector::WriteMemory<unsigned char>(0x56dd9E, lowTraffic, true); // Low (10)
	injector::WriteMemory<unsigned char>(0x56dd9A, medTraffic, true); // Medium (30)
	injector::WriteMemory<unsigned char>(0x56dd96, highTraffic, true); // High (50)

	// Blacklist Max Rival Controllers
	if (maxBlacklist == 0) // Unlimited blacklists
	{
		// Enable BL 0 for decrement
		injector::MakeNOP(0x551455, 7, true);
		injector::WriteMemory<unsigned char>(0x551455, 0x31, true);
		injector::WriteMemory<unsigned char>(0x551456, 0xD2, true);

		// Enable BL 0 for increment
		injector::MakeNOP(0x55a571, 7, true);
		injector::WriteMemory<unsigned char>(0x55a571, 0x31, true);
		injector::WriteMemory<unsigned char>(0x55a572, 0xC0, true);

		// Remove Maximum Restriction
		injector::WriteMemory<unsigned char>(0x55a56c, 0xeb, true);

		// Remove Minimum Restriction
		injector::MakeNOP(0x551460, 5, true);
	}

	else // Normal behaviour
	{
		injector::WriteMemory<unsigned char>(0x551461, maxBlacklist, true);
		injector::WriteMemory<unsigned char>(0x551473, maxBlacklist, true);
		injector::WriteMemory<unsigned char>(0x55a555, maxBlacklist, true);
		injector::WriteMemory<unsigned char>(0x55a566, maxBlacklist, true);
	}

	// Remove restrictions for new save games
	if (maxBlacklist != 15)
	{
		injector::MakeNOP(0x55a556, 6, true);
		injector::MakeNOP(0x551433, 6, true);
	}
	
	// Challenge Series Bin
	injector::WriteMemory<unsigned char>(0x7ae969, csBlacklist, true);

	// Fix Unexistent Bin Crash?? (EXPERIMENTAL)
	if (maxBlacklist != 15 || csBlacklist != 19)
	{
		injector::WriteMemory<unsigned char>(0x5e39c6, 0x01, true);
		injector::WriteMemory<unsigned char>(0x5e39c7, 0xC8, true);
	}

	// Race Speed Multiplier
	injector::WriteMemory<float>(0x901B1C, gameSpeed, true);

	// Randomize Count
	injector::WriteMemory<int>(0x7b4648, randomizeCount, true);

	// Unfreeze Lap Count for Lap Knockout
	if (unfreezeKO)
	{
		injector::MakeNOP(0x7acf83, 3, true); // Enable editing of lap count for KO
		injector::MakeNOP(0x7ac04b, 3, true); // Don't change laps when opponent count changed
	}

	// Remove Race Barriers and Locked Areas
	if (removePlayerBarriers)
	{
		injector::WriteMemory<unsigned char>(0x8B282B, 0x4A, true);
		injector::WriteMemory<unsigned char>(0x8B2838, 0x4A, true);
		injector::WriteMemory<unsigned char>(0x8B2844, 0x4A, true);

		// Always show whole map
		injector::MemoryFill(0x89B15D, 0x00, 10, true); 
		injector::WriteMemory<unsigned char>(0x57bf01, 0xEB, true);
		injector::WriteMemory<unsigned char>(0x57bf19, 0xEB, true);
		injector::WriteMemory<unsigned char>(0x57bf5f, 0xEB, true);
		injector::WriteMemory<unsigned char>(0x57bf7c, 0xEB, true);
	}

	// Remove Old Bridge Area Barrier
	if (removeSceneryGroupDoor)
	{
		injector::WriteMemory<unsigned char>(0x8B2817, 0x20, true);
		injector::WriteMemory<unsigned char>(0x8B2810, 0x54, true);
	}

	// Add Tollbooth and Challenge options to quick race menu
	injector::MakeNOP(0x7aa924, 6, true);
	injector::MakeNOP(0x7AA97F, 6, true);
	injector::MakeJMP(0x7aaa5d, 0x7AAAEF, true);
	injector::WriteMemory<DWORD>(0x7AAB1A, 0x213CC8D1, true); // Challenge name hash
	injector::WriteMemory<DWORD>(0x7AAB1F, 0x9A962438, true); // Challenge icon hash
	injector::WriteMemory<unsigned char>(0x7AAB33, 0x08, true); // Challenge game mode
	
	// List all race types on LAN
	injector::MakeNOP(0x7AAB69, 6, true);

	// Fix Crash
	injector::MakeNOP(0x7AA8E7, LANRaceSelectFixCodeCaveExit - 0x7AA8E7, true);
	injector::MakeJMP(0x7AA8E7, LANRaceSelectFixCodeCave, true);

	// Fix Icons and Strings - 1
	injector::MakeNOP(0x539562, LANRaceModeFixCodeCaveExit - 0x539562, true);
	injector::MakeJMP(0x539562, LANRaceModeFixCodeCave, true);

	// Fix Icons and Strings - 2
	injector::MakeNOP(0x535E8A, LANRaceModeFixCodeCave2Exit - 0x535E8A, true);
	injector::MakeJMP(0x535E8A, LANRaceModeFixCodeCave2, true);

	if (!ShowTollbooth) // Remove Tollbooth if the option is 0
	{
		injector::MakeJMP(0x7AAA11, 0x7AAA5D, true);
	}

	if (!ShowChallenge) // Remove Challenge if the option is 0
	{
		injector::MakeJMP(0x7AAAEF, 0x7AAB3B, true);
	}

	// Add Cops option to track options
	if (ShowCops)
	{
		// Add the hidden, not working Track Direction option to menu
		injector::MakeNOP(0x7acb21, 2, true); // Sprint
		injector::MakeNOP(0x7acea1, 2, true); // Lap Knockout
		injector::MakeNOP(0x7ad141, 2, true); // Tollbooth
		injector::MakeNOP(0x7ad359, 2, true); // Speedtrap
		injector::MakeNOP(0x7ac901, 2, true); // Circuit & Challenge

		// Edit cops option instead of not working Track Direction
		injector::WriteMemory<unsigned char>(0x7ac52f, 0x0C, true);
		injector::WriteMemory<unsigned char>(0x7ac544, 0x0C, true);
		injector::WriteMemory<unsigned char>(0x7ac5a9, 0x0C, true);

		// Rename options
		injector::WriteMemory<DWORD>(0x7ac5d6, 0x0013ff94, true); // Change Track Direction string to Cops
		injector::WriteMemory<DWORD>(0x7ac5ba, 0x70DFE5C2, true); // Change Forward string to Off
		injector::WriteMemory<DWORD>(0x7ac5c5, 0x417B2604, true); // Change Backward string to On
	}

	// Remove online option from main menu
	if (HideOnline)
	{
		injector::WriteMemory<unsigned char>(0x5450f9, 0x46, true);
	}
	if (ShowOnlineOpts) injector::MakeNOP(0x5290B2, 2, true); // Show Online Options menu
								
	// Load headlights preferences
	switch (headLightsMode)
	{
	case 0:
		injector::WriteMemory<float>(0x742b94, 0, true); // Left HeadLight
		injector::WriteMemory<float>(0x742bb3, 0, true); // Right HeadLight
		break;
	case 1:
		injector::WriteMemory<float>(0x742b94, LowBeamAmount, true); // Left HeadLight
		injector::WriteMemory<float>(0x742bb3, LowBeamAmount, true); // Right HeadLight
		break;
	case 2: default:
		injector::WriteMemory<float>(0x742b94, HighBeamAmount, true); // Left HeadLight
		injector::WriteMemory<float>(0x742bb3, HighBeamAmount, true); // Right HeadLight
		break;
	}

	// Load cop lights preferences
	if (copLightsEnabled)
	{
		injector::WriteMemory<float>(0x742af9, copLightsAmount, true); // Red Flashing Lights
		injector::WriteMemory<float>(0x742b01, copLightsAmount, true); // Blue Flashing Lights
		injector::WriteMemory<float>(0x742b09, copLightsAmount, true); // White Flashing Lights
	}

	// Add Debug and Preset Categories to Car Select screen
	if (EnablePresetAndDebugCars)
	{
		injector::WriteMemory<unsigned char>(0x7BF9E9, 0x20, true);
		injector::WriteMemory<unsigned char>(0x7BF9FA, 0x20, true);
		// LAN Lobby
		injector::WriteMemory<unsigned char>(0x556787, 0x20, true);
		injector::WriteMemory<unsigned char>(0x5567bd, 0x20, true);
		injector::WriteMemory<unsigned char>(0x5567e7, 0x20, true);
		injector::WriteMemory<unsigned char>(0x556821, 0x20, true);
	}

	// Enable All Customizations For All Cars
	if (EnableCustomizationForAll)
	{
		injector::MakeNOP(0x7BCDD0, 2, true); //My Cars
		injector::MakeNOP(0x7BCE33, 2, true); //Backroom Categories
		injector::MakeNOP(0x7B123D, 2, true); //Backroom HUD Area
		injector::MakeNOP(0x7BFF49, 6, true); //Backroom Menu
		injector::MakeNOP(0x7B92DC, 6, true); //Backroom Parts
		injector::MakeNOP(0x7BC28C, 2, true); //Rim Paint
	}

	// Rain Options
	if (AlwaysRain)
	{
		injector::WriteMemory<unsigned char>(0x9B0A30, 0x01, true);
		injector::WriteMemory<unsigned char>(0x758293, 0xEB, true); // Road Reflection Fix??
	}
	injector::WriteMemory<float>(0x904B38, RoadReflection, true);
	injector::WriteMemory<float>(0x904A90, FallingRainSize, true);
	injector::WriteMemory<float>(0x904A14, RainAmount, true);
	injector::WriteMemory<float>(0x904A94, RainIntensity, true);
	injector::WriteMemory<float>(0x904A24, RainXing, true);
	injector::WriteMemory<float>(0x904A28, RainFallSpeed, true);
	injector::WriteMemory<float>(0x904A2C, RainGravity, true);
	
	// Options from ModLoader
	if (WindowedMode)
	{
		injector::WriteMemory<unsigned char>(0x982BF0, WindowedMode, true);
	}

	if (SkipMovies)
	{
		injector::WriteMemory<unsigned char>(0x926144, SkipMovies, true);
	}

	if (!EnableSound)
	{
		injector::WriteMemory<unsigned char>(0x8F86F8, EnableSound, true);
	}

	if (!EnableMusic)
	{
		injector::WriteMemory<unsigned char>(0x8F86FC, EnableMusic, true);
	}
	
	
	// Enable hidden camera modes
	if (EnableCameras)
	{
		injector::MakeNOP(0x5A38AA, 2, true); // For C key
		injector::MakeNOP(0x51C8D9, 2, true); // Player Options Menu - Increment
		injector::MakeNOP(0x51C8AF, 2, true); // Player Options Menu - Decrement
		injector::MakeNOP(0x51C95F, 0x0051C98C - 0x51C95F, true); // Clean the unused code
		injector::MakeJMP(0x51C95F, CameraNamesCodeCave, true); // Fix Names

		// Rearview Mirror Fix Addition for Widescreen Fix
		injector::MakeNOP(0x595DDD, 2, true);
		injector::MakeNOP(0x595DE2, 2, true);
		injector::MakeNOP(0x595DE7, 2, true);
		injector::MakeNOP(0x595DEC, 2, true);
		injector::WriteMemory<unsigned char>(0x595DF0, 0xFF, true);
	}

	// Splash Screen Time Limit
	injector::WriteMemory<float>(0x8F3CD0, SplashScreenTimeLimit, true);

	// Force Show Subtitles
	if (ShowSubs)
	{
		injector::MakeNOP(0x542dbc, 2, true);
		injector::MakeNOP(0x54ee78, 2, true);
		injector::MakeNOP(0x54f219, 2, true);
	}

	// Heat Level Overrides
	injector::MakeNOP(0x443dc3, HeatLevelsCodeCaveExit - 0x443dc3, true); // Clean the unused code
	injector::MakeJMP(0x443dc3, HeatLevelsCodeCave, true); // Prepare the game for advanced force heat level hack
	
	// Wide Splash Screen
	if (UseWSMWSplashBack) 
	{
		injector::MakeNOP(0x5C46E4, WideSplashScreenCodeCaveExit - 0x5C46E4, true);
		injector::MakeJMP(0x5C46E4, WideSplashScreenCodeCave, true);

		injector::MakeNOP(0x5B962A, WideSplashScreenCodeCave2Exit - 0x5B962A, true);
		injector::MakeJMP(0x5B962A, WideSplashScreenCodeCave2, true);

		injector::MakeNOP(0x5BC6AB, WideSplashScreenCodeCave3Exit - 0x5BC6AB, true);
		injector::MakeJMP(0x5BC6AB, WideSplashScreenCodeCave3, true);
	}

	// Show COMPLETED %x instead of LAP 1/1
	if (CarbonStyleRaceProgress)
	{
		injector::MakeNOP(0x57AA2F, 0x57AA46 - 0x57AA2F, true);
		// call 0x5FAA20 (Just moved this call up)
		injector::WriteMemory<unsigned char>(0x57AA2F, 0xE8, true);
		injector::WriteMemory<unsigned char>(0x57AA2F + 1, 0xEC, true);
		injector::WriteMemory<unsigned char>(0x57AA2F + 2, 0xFF, true);
		injector::WriteMemory<unsigned char>(0x57AA2F + 3, 0x07, true);
		injector::WriteMemory<unsigned char>(0x57AA2F + 4, 0x00, true);
		// cmp dword ptr ds: [esi+0x3C],0x01 (if lap count = 1)
		injector::WriteMemory<unsigned char>(0x57AA2F + 5, 0x83, true);
		injector::WriteMemory<unsigned char>(0x57AA2F + 6, 0x7E, true);
		injector::WriteMemory<unsigned char>(0x57AA2F + 7, 0x3C, true);
		injector::WriteMemory<unsigned char>(0x57AA2F + 8, 0x01, true);
		//je 0x57AA73 (If true, use COMPLETED %)
		injector::WriteMemory<unsigned char>(0x57AA2F + 9, 0x74, true);
		injector::WriteMemory<unsigned char>(0x57AA2F + 10, 0x39, true);
	}

	// Burger King
	if (eatSomeBurgers)
	{
		injector::WriteMemory<unsigned char>(0x576A8D, 0xEB, true);
	}

	// Special Vinyl Category
	if (moreVinyls)
	{
		injector::MakeNOP(0x7BC8FF, VinylMenuCodeCaveExit - 0x7BC8FF, true);
		injector::MakeNOP(0x7BD26F, VinylMenuCodeCave2Exit - 0x7BD26F, true);

		injector::MakeJMP(0x7BC8FF, VinylMenuCodeCave, true);
		injector::MakeJMP(0x7BD26F, VinylMenuCodeCave2, true);

		// Category Fixes
		injector::WriteMemory<unsigned char>(0x7A5208, 0x0A, true);
		injector::WriteMemory<unsigned char>(0x7A5823, 0x0A, true);
		injector::WriteMemory<unsigned char>(0x7AFE90, 0x0A, true);
		injector::WriteMemory<unsigned char>(0x7B600C, 0x0A, true);
		injector::WriteMemory<unsigned char>(0x7B7436, 0x0A, true);
		injector::WriteMemory<unsigned char>(0x7B75A2, 0x0A, true);
		injector::WriteMemory<unsigned char>(0x7BAEC3, 0x0A, true);
		injector::WriteMemory<unsigned char>(0x7BAF10, 0x0A, true);
		injector::WriteMemory<unsigned char>(0x7bca3c, 0x0A, true);
		injector::WriteMemory<unsigned char>(0x7c0ae7, 0x0A, true);
	}

	// Fix (ignore) starting heat level when a challenge executed from quick race screen
	injector::WriteMemory<unsigned char>(0x56DD55, 0xEB, true);

	// Fix 99.1.1
	injector::MemoryFill(0x8A0C60, 0x58, 2, true);

	// Unlock all tracks (Load preference)
	if (unlockAllTracks)
	{
		injector::WriteMemory<unsigned char>(0x7aad6a, 0xB1, true);
		injector::WriteMemory<unsigned char>(0x7aad6b, 0x00, true);
		injector::WriteMemory<unsigned char>(0x7aad6c, 0x90, true);

		injector::WriteMemory<unsigned char>(0x7ba6e0, 18, true);
		injector::WriteMemory<unsigned char>(0x7ba6e4, 17, true);
	}

	// Unlock all tracks (Code caves)
	injector::MakeNOP(0x5FAA2A, RaceHackTypeCodeCaveExit - 0x5FAA2A, true);
	injector::MakeNOP(0x60107F, RaceHackReplaceCodeCaveExit - 0x60107F, true);
	injector::MakeJMP(0x5FAA2A, RaceHackTypeCodeCave, true);
	injector::MakeJMP(0x60107F, RaceHackReplaceCodeCave, true);

	// Fix Challenge icon for race selection screen
	injector::MakeJMP(0x56e094, IconFixCodeCave, true);

	// Fix Invisible Wheels
	injector::WriteMemory<unsigned char>(0x74251D, 0x01, true);

	// Garage Hacks
	if (GarageZoom)
	{
		injector::MakeNOP(0x476B04, 5, true);
		injector::WriteMemory<unsigned char>(0x476B04, 0xB0, true);
		injector::WriteMemory<unsigned char>(0x476B05, 0x01, true);
	}
	if (GarageRotate)
	{
		injector::MakeNOP(0x476AC3, 5, true);
		injector::WriteMemory<unsigned char>(0x476AC3, 0xB0, true);
		injector::WriteMemory<unsigned char>(0x476AC4, 0x01, true);
	}
	if (GarageShowcase)
	{
		injector::MakeNOP(0x7A201B, 5, true);
		injector::WriteMemory<unsigned char>(0x7A201B, 0xB0, true);
		injector::WriteMemory<unsigned char>(0x7A201C, 0x01, true);
	}
	
	// World Animation Speed
	injector::WriteMemory<float>(0x904AEC, WorldAnimationSpeed, true);

	// Fix Split Screen Crash and Black Screen
	injector::WriteMemory<unsigned char>(0x7a3f68, 0x0D, true); // Fix Player 2 Ready control
	injector::WriteMemory<unsigned char>(0x666eb3, 0xEB, true); // Fix loading screen crash
	injector::MakeNOP(0x6cfc03, 2, true); // Fix black screen??

	// String Replacement
	injector::MakeJMP(0x56bbd0, StringReplacementCodeCave, true);

	// Car size hack
	injector::WriteMemory<float>(0x737870, CarScale, true); // Length
	injector::WriteMemory<float>(0x7378A2, CarScale, true); // Width
	injector::WriteMemory<float>(0x7378D4, CarScale, true); // Height

	// Other Things
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Thing, NULL, 0, NULL);
}

DWORD WINAPI Thing(LPVOID)
{
	while (true)
	{
		Sleep(1);

		raceOptions = *(DWORD*)0x91CF90; // Race Options Pointer (Thanks to samfednik)
		HeatLevelAddr = (*(DWORD*)0x934CF4) + 0x14; // Heat Level Pointer

		//Advanced Force Heat Level
		if ((GetAsyncKeyState(hotkeyToggleForceHeat) & 1)) //When pressed "Toggle Force Heat"
		{
			forceHeatLevel = !forceHeatLevel; // Toggle option
			if (forceHeatLevel)
			{
				EnableHeatLevelOverride = 1;
				heatLevel = MinHeatLevel-1;
			}
			else
			{
				// Re-read the override boolean from config file
				CIniReader iniReader("NFSMWExtraOptionsSettings.ini");
				EnableHeatLevelOverride = iniReader.ReadInteger("Pursuit", "HeatLevelOverride", 1) == 1;
			}

			while ((GetAsyncKeyState(hotkeyToggleForceHeat) & 0x8000) > 0) { Sleep(0); }
		}

		if ((GetAsyncKeyState(hotkeyForceHeatLevel) & 1)) //When pressed "Forced Heat Level"
		{
			if (forceHeatLevel && HeatLevelAddr)
			{
				heatLevel = (int)(floorf(heatLevel) - floorf(MinHeatLevel) + 1) % (int)(floorf(MaxHeatLevel) - floorf(MinHeatLevel) + 1) + MinHeatLevel;

				injector::WriteMemory<float>(HeatLevelAddr, heatLevel - 0.005f, true); //Change it and leave .005 for make increment happen
			}
			
			while ((GetAsyncKeyState(hotkeyForceHeatLevel) & 0x8000) > 0) { Sleep(0); }
		}
		

		// Cop Lights
		if ((GetAsyncKeyState(hotkeyToggleCopLights) & 1)) // When pressed "Toggle Police Lights" key
		{
			copLightsEnabled = !copLightsEnabled;
			CIniReader iniReader("NFSMWExtraOptionsSettings.ini");
			iniReader.WriteInteger("Gameplay", "CopLightsMode", copLightsEnabled);

			if (copLightsEnabled) // Enable cop lights - more proper method
			{
				injector::WriteMemory<float>(0x742af9, copLightsAmount, true); // Red Flashing Lights
				injector::WriteMemory<float>(0x742b01, copLightsAmount, true); // Blue Flashing Lights
				injector::WriteMemory<float>(0x742b09, copLightsAmount, true); // White Flashing Lights
			}
			else // Disable cop lights
			{
				injector::WriteMemory<float>(0x742af9, 0, true); // Red Flashing Lights
				injector::WriteMemory<float>(0x742b01, 0, true); // Blue Flashing Lights
				injector::WriteMemory<float>(0x742b09, 0, true); // White Flashing Lights
			}

			while ((GetAsyncKeyState(hotkeyToggleCopLights) & 0x8000) > 0) { Sleep(0); }
		}

		// Headlights
		if ((GetAsyncKeyState(hotkeyToggleHeadLights) & 1)) // When pressed "Toggle Head Lights" key
		{
			headLightsMode = (headLightsMode + 1) % 3; // 0, 1 or 2
			CIniReader iniReader("NFSMWExtraOptionsSettings.ini");
			iniReader.WriteInteger("Gameplay", "HeadLightsMode", headLightsMode);

			switch (headLightsMode)
			{
				case 0: 
					injector::WriteMemory<float>(0x742b94, 0, true); // Left HeadLight
					injector::WriteMemory<float>(0x742bb3, 0, true); // Right HeadLight
					break;
				case 1: 
					injector::WriteMemory<float>(0x742b94, LowBeamAmount, true); // Left HeadLight
					injector::WriteMemory<float>(0x742bb3, LowBeamAmount, true); // Right HeadLight
					break;
				case 2: default:
					injector::WriteMemory<float>(0x742b94, HighBeamAmount, true); // Left HeadLight
					injector::WriteMemory<float>(0x742bb3, HighBeamAmount, true); // Right HeadLight
					break;
			}
		
			while ((GetAsyncKeyState(hotkeyToggleHeadLights) & 0x8000) > 0) { Sleep(0); }
		}


		// Car Hack
		if ((GetAsyncKeyState(hotkeyCarHack) & 1)) // When pressed "Toggle Freeze Car" key
		{
			carHackEnabled = !carHackEnabled;

			if (carHackEnabled)
			{
				raceType = *(unsigned char*)(raceOptions + 0x18); // Get the race type
				raceMode = *(unsigned char*)(raceOptions + 0x12C); // Get the mode. (1 = Career, 4 = Quick Race, 32 = My Cars)
				careerCar = *(DWORD*)(*(DWORD*)(raceOptions + 0x10) + 0xA8);

				switch (raceMode)
				{
					case 1: selectedCar = *(DWORD*)(*(DWORD*)(raceOptions + 0x10) + 0xA8); break; //Freeze career car
					case 4: selectedCar = *(DWORD*)(raceOptions + 0x2C + (raceType * 0x18)); break; // Freeze QR Car
					case 32: selectedCar = *(DWORD*)(raceOptions + 0x2C); break; //Freeze my car
					default: carHackEnabled=0; break; // Don't enable it while not in a car select screen
				}
				
			}
			else
			{
				// Fix Challenge Series behaviour
				injector::WriteMemory<unsigned char>(0x6f48e7, 0x74, true);

				// Fix Career Car
				injector::WriteMemory<DWORD>(*(DWORD*)(raceOptions + 0x10) + 0xA8, careerCar, true);
			}


			while ((GetAsyncKeyState(hotkeyCarHack) & 0x8000) > 0) { Sleep(0); }
		}

		if (carHackEnabled)
		{
			// Freeze values
			injector::WriteMemory<DWORD>(raceOptions + 0x2C, selectedCar, true); // Sprint (0)
			injector::WriteMemory<DWORD>(raceOptions + 0x2C + (0x18), selectedCar, true); // Circuit (1)
			injector::WriteMemory<DWORD>(raceOptions + 0x2C + (2 * 0x18), selectedCar, true); // Drag (2)
			injector::WriteMemory<DWORD>(raceOptions + 0x2C + (3 * 0x18), selectedCar, true); // Lap Knockout (3)
			injector::WriteMemory<DWORD>(raceOptions + 0x2C + (4 * 0x18), selectedCar, true); // Tollbooth (4)
			injector::WriteMemory<DWORD>(raceOptions + 0x2C + (5 * 0x18), selectedCar, true); // Speedtrap (5)
			injector::WriteMemory<DWORD>(raceOptions + 0x2C + (8 * 0x18), selectedCar, true); // Challenge (8)
			injector::WriteMemory<DWORD>(*(DWORD*)(raceOptions + 0x10) + 0xA8, selectedCar, true); // Career

			injector::WriteMemory<unsigned char>(0x6f48e7, 0xEB, true); // Use selected cars at Challenge Series
		}

		// Drunk Driver
		if ((GetAsyncKeyState(hotkeyDrunkDriver) & 1)) // When pressed "Drunk Driver" key
		{
			injector::WriteMemory<unsigned char>(0x90d5fa, 0x01, true);
			
			while ((GetAsyncKeyState(hotkeyDrunkDriver) & 0x8000) > 0) { Sleep(0); }
		}

		// Unlock All Tracks
		if ((GetAsyncKeyState(hotkeyUnlockAllTracks) & 1)) // When pressed "Unlock All Tracks" key
		{
			unlockAllTracks = !unlockAllTracks;
			CIniReader iniReader("NFSMWExtraOptionsSettings.ini");
			iniReader.WriteInteger("Gameplay", "UnlockAllTracks", unlockAllTracks);

			if (unlockAllTracks)
			{
				injector::WriteMemory<unsigned char>(0x7aad6a, 0xB1, true);
				injector::WriteMemory<unsigned char>(0x7aad6b, 0x00, true);
				injector::WriteMemory<unsigned char>(0x7aad6c, 0x90, true);

				// Read more bins (Adds hidden tracks to list if option is enabled)
				injector::WriteMemory<unsigned char>(0x7ba6e0, 18, true);
				injector::WriteMemory<unsigned char>(0x7ba6e4, 17, true);
				
			}
			else
			{
				injector::WriteMemory<unsigned char>(0x7aad6a, 0x0F, true);
				injector::WriteMemory<unsigned char>(0x7aad6b, 0x94, true);
				injector::WriteMemory<unsigned char>(0x7aad6c, 0xC1, true);

				injector::WriteMemory<unsigned char>(0x7ba6e0, 21, true);
				injector::WriteMemory<unsigned char>(0x7ba6e4, 16, true);
			}
			
			while ((GetAsyncKeyState(hotkeyUnlockAllTracks) & 0x8000) > 0) { Sleep(0); }
		}
		if (raceOptions && unlockAllTracks)
		{
			onQuickRaceMenu = *(unsigned char*)(raceOptions + 0x12D) == 0x04;
		}
		else onQuickRaceMenu = 0;

		// freeze cops option for challenge
		if (raceOptions && *(unsigned char*)(raceOptions + 0x18) == 0x08)
		{
			injector::WriteMemory<unsigned char>(0x7AC920, 0x00, true);
			injector::WriteMemory<unsigned char>(raceOptions + 0xE8, 0x01, true);
		}
		else // unfreeze cops option for circuit
		{
			injector::WriteMemory<unsigned char>(0x7AC920, 0x01, true);
		}

		// .hot Save And Load
		if ((GetAsyncKeyState(VK_LSHIFT) & 1)) // Save
		{
			while ((GetAsyncKeyState(VK_LSHIFT) & 0x8000) > 0)
			{ 
				Sleep(0);
				if (GetAsyncKeyState(49) & 1) { injector::WriteMemory<unsigned char>(0x9B0908, 0x01, true); while ((GetAsyncKeyState(49) & 0x8000) > 0) Sleep(0); }
				if (GetAsyncKeyState(50) & 1) { injector::WriteMemory<unsigned char>(0x9B0908, 0x02, true); while ((GetAsyncKeyState(50) & 0x8000) > 0) Sleep(0); }
				if (GetAsyncKeyState(51) & 1) { injector::WriteMemory<unsigned char>(0x9B0908, 0x03, true); while ((GetAsyncKeyState(51) & 0x8000) > 0) Sleep(0); }
				if (GetAsyncKeyState(52) & 1) { injector::WriteMemory<unsigned char>(0x9B0908, 0x04, true); while ((GetAsyncKeyState(52) & 0x8000) > 0) Sleep(0); }
				if (GetAsyncKeyState(53) & 1) { injector::WriteMemory<unsigned char>(0x9B0908, 0x05, true); while ((GetAsyncKeyState(53) & 0x8000) > 0) Sleep(0); }
			}
		}

		if ((GetAsyncKeyState(VK_LCONTROL) & 1)) // Load
		{
			while ((GetAsyncKeyState(VK_LCONTROL) & 0x8000) > 0)
			{
				Sleep(0);
				if (GetAsyncKeyState(49) & 1) { injector::WriteMemory<unsigned char>(0x9B090C, 0x01, true); while ((GetAsyncKeyState(49) & 0x8000) > 0) Sleep(0); }
				if (GetAsyncKeyState(50) & 1) { injector::WriteMemory<unsigned char>(0x9B090C, 0x02, true); while ((GetAsyncKeyState(50) & 0x8000) > 0) Sleep(0); }
				if (GetAsyncKeyState(51) & 1) { injector::WriteMemory<unsigned char>(0x9B090C, 0x03, true); while ((GetAsyncKeyState(51) & 0x8000) > 0) Sleep(0); }
				if (GetAsyncKeyState(52) & 1) { injector::WriteMemory<unsigned char>(0x9B090C, 0x04, true); while ((GetAsyncKeyState(52) & 0x8000) > 0) Sleep(0); }
				if (GetAsyncKeyState(53) & 1) { injector::WriteMemory<unsigned char>(0x9B090C, 0x05, true); while ((GetAsyncKeyState(53) & 0x8000) > 0) Sleep(0); }
			}
		}

	}
	return 0;
}

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD reason, LPVOID /*lpReserved*/)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);
		IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)(base);
		IMAGE_NT_HEADERS* nt = (IMAGE_NT_HEADERS*)(base + dos->e_lfanew);

		if ((base + nt->OptionalHeader.AddressOfEntryPoint + (0x400000 - base)) == 0x7C4040) // Check if .exe file is compatible - Thanks to thelink2012 and MWisBest
			Init();

		else
		{
			MessageBoxA(NULL, "This .exe is not supported.\nPlease use v1.3 English speed.exe (5,75 MB (6.029.312 bytes)).", "NFSMW Extra Options", MB_ICONERROR);
			return FALSE;
		}
	}
	return TRUE;
}

