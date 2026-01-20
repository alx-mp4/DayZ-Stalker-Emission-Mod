class EmissionSystem
{
	private static ref EmissionSystem m_Instance;

	bool m_IsEmissionActive;
	bool m_IsWarningActive;
	private bool m_IsEndingActive;
	private float m_EmissionStartTime;
	private float m_LastEmissionTime;
	private float m_NextEmissionTime;

	private ref array<Man> m_PlayersInEmission;
	private Weather m_Weather;

	void EmissionSystem()
	{
		m_IsEmissionActive = false;
		m_IsWarningActive = false;
		m_IsEndingActive = false;
		m_LastEmissionTime = 0;
		m_NextEmissionTime = EmissionGlobalSettings.DEFAULT_EMISSION_INTERVAL;
		m_PlayersInEmission = new array<Man>;

		m_Weather = GetGame().GetWeather();

		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.Update, 1000, true);
	}

	static EmissionSystem GetInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new EmissionSystem();
		}

		return m_Instance;
	}

	bool IsEmissionActive()
	{
		return m_IsEmissionActive;
	}

	bool IsWarningActive()
	{
		return m_IsWarningActive;
	}

	void Update()
	{
		float currentTime = GetGame().GetTime() * 0.001;

		if (!m_IsWarningActive && !m_IsEmissionActive && !m_IsEndingActive && (currentTime - m_LastEmissionTime >= m_NextEmissionTime))
		{
			StartEmissionWarning();
		}

		if (m_IsWarningActive && (currentTime - m_EmissionStartTime >= EmissionGlobalSettings.DEFAULT_WARNING_DURATION))
		{
			m_IsWarningActive = false;
			StartEmission();
		}

		if (m_IsEmissionActive && !m_IsEndingActive && (currentTime - m_EmissionStartTime >= EmissionGlobalSettings.DEFAULT_WARNING_DURATION + EmissionGlobalSettings.DEFAULT_EMISSION_DURATION))
		{
			m_IsEmissionActive = false;
			StartEmissionEnding();
		}

		if (m_IsEndingActive && (currentTime - m_EmissionStartTime >= EmissionGlobalSettings.DEFAULT_WARNING_DURATION + EmissionGlobalSettings.DEFAULT_EMISSION_DURATION + EmissionGlobalSettings.DEFAULT_ENDING_DURATION))
		{
			EndEmission();
		}
	}

	void StartEmissionWarning()
	{
		m_IsWarningActive = true;
		m_EmissionStartTime = GetGame().GetTime() * 0.001;

		m_Weather.GetRain().Set(0.2, EmissionGlobalSettings.DEFAULT_WARNING_DURATION, 0);
		m_Weather.GetFog().Set(0.5, EmissionGlobalSettings.DEFAULT_WARNING_DURATION, 0);
		m_Weather.GetOvercast().Set(0.8, EmissionGlobalSettings.DEFAULT_WARNING_DURATION, 0);

		m_Weather.SetStorm(1.0, 0.4, 8);

		EmissionRPCHandler.SendEmissionWarningToAll();
	}

	void StartEmission()
	{
		m_IsEmissionActive = true;

		m_Weather.GetRain().Set(1.0, 180, 180);
		m_Weather.GetFog().Set(0.9, 180, 180);
		m_Weather.GetOvercast().Set(1.0, 180, 180);

		m_Weather.SetStorm(1, 0.4, 2);

		EmissionRPCHandler.SendEmissionStartToAll();

		array<Man> players = new array<Man>;
		GetGame().GetPlayers(players);

		foreach (Man man : players)
		{
			PlayerBase player = PlayerBase.Cast(man);
			if (player)
			{
				player.GetSymptomManager().QueueUpSecondarySymptom(EmissionSymptomsIDs.Emission);
			}
		}
	}

	void StartEmissionEnding()
	{
		m_IsEndingActive = true;

		EmissionRPCHandler.SendEmissionEndToAll();

		array<Man> players = new array<Man>;
		GetGame().GetPlayers(players);

		foreach (Man man : players)
		{
			PlayerBase player = PlayerBase.Cast(man);
			if (player)
			{
				player.GetSymptomManager().RemoveSecondarySymptom(EmissionSymptomsIDs.Emission);
			}
		}

		m_Weather.GetRain().Set(0.4, EmissionGlobalSettings.DEFAULT_ENDING_DURATION, 0);
		m_Weather.GetFog().Set(0.7, EmissionGlobalSettings.DEFAULT_ENDING_DURATION, 0);
		m_Weather.GetOvercast().Set(0.8, EmissionGlobalSettings.DEFAULT_ENDING_DURATION, 0);

		m_Weather.SetStorm(0.3, 0.7, 20);
	}

	void EndEmission()
	{
		m_IsEndingActive = false;
		m_LastEmissionTime = GetGame().GetTime() * 0.001;
		m_NextEmissionTime = EmissionGlobalSettings.DEFAULT_EMISSION_INTERVAL + Math.RandomFloat(-300, 300);

		m_Weather.GetRain().Set(0.1, 15, 0);
		m_Weather.GetFog().Set(0.5, 60, 0);
		m_Weather.GetOvercast().Set(0.6, 60, 0);

		m_Weather.SetStorm(0, 1.0, 60);
	}

	void OnClientConnected(PlayerBase player)
	{
		if (m_IsWarningActive)
		{
			EmissionRPCHandler.SendEmissionWarningToPlayer(player);
		}
		else if (m_IsEmissionActive)
		{
			EmissionRPCHandler.SendEmissionStartToPlayer(player);
			player.GetSymptomManager().QueueUpSecondarySymptom(EmissionSymptomsIDs.Emission);
		}
		else if (m_IsEndingActive)
		{
			EmissionRPCHandler.SendEmissionEndToPlayer(player);
		}
	}
}
