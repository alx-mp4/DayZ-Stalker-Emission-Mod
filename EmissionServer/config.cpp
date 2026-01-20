class CfgPatches
{
	class EmissionServer
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Sounds_Effects",
			"Emission"
		};
	};
};

class CfgMods
{
	class EmissionServer
	{
		type = "mod";

		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] =
				{
					"EmissionServer/Scripts/3_Game"
				};
			};

			class worldScriptModule
			{
				value = "";
				files[] =
				{
					"EmissionServer/Scripts/4_World"
				};
			};

			class missionScriptModule
			{
				value = "";
				files[] =
				{
					"EmissionServer/Scripts/5_Mission"
				};
			};
		};
	};
};
