class CfgPatches
{
	class Emission
	{
		units[] = {};
		weapons[] = {};
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};

class CfgMods
{
	class Emission
	{
		type = "mod";

		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] =
				{
					"Emission/Scripts/3_Game"
				};
			};

			class worldScriptModule
			{
				value = "";
				files[] =
				{
					"Emission/Scripts/4_World"
				};
			};

			class missionScriptModule
			{
				value = "";
				files[] =
				{
					"Emission/Scripts/5_Mission"
				};
			};
		};
	};
};

class CfgSoundSets
{
	class baseCharacter_SoundSet;

	class EmissionWarnSoundSet : baseCharacter_SoundSet
	{
		soundShaders[] = { "EmissionWarnSoundShader" };
	};

	class EmissionStartSoundSet : baseCharacter_SoundSet
	{
		soundShaders[] = { "EmissionStartSoundShader" };
	};

	class EmissionEndSoundSet : baseCharacter_SoundSet
	{
		soundShaders[] = { "EmissionEndSoundShader" };
	};

	class EmissionRumbleSoundSet : baseCharacter_SoundSet
	{
		soundShaders[] = { "EmissionRumbleSoundShader" };
	};
	
	class EmissionHitSoundSet : baseCharacter_SoundSet
	{
		soundShaders[] = { "EmissionHitSoundShader" };
	};
};

class CfgSoundShaders
{
	class EmissionWarnSoundShader
	{
		samples[] =
		{
			{ "Emission/Sounds/Warn.ogg", 1 }
		};
		volume = 1;
	};

	class EmissionStartSoundShader
	{
		samples[] =
		{
			{ "Emission/Sounds/Start.ogg", 1 }
		};
		volume = 1;
	};

	class EmissionEndSoundShader
	{
		samples[] =
		{
			{ "Emission/Sounds/End.ogg", 1 }
		};
		volume = 1;
	};

	class EmissionRumbleSoundShader
	{
		samples[] =
		{
			{ "Emission/Sounds/Rumble.ogg", 1 }
		};
		volume = 1;
	};
	
	class EmissionRumbleSoundShader
	{
		samples[] =
		{
			{ "Emission/Sounds/Hit.ogg", 1 }
		};
		volume = 1;
	};
};
