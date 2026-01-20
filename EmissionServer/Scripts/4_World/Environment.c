modded class Environment
{
	bool IsPlayerSheltered()
	{
		return IsInsideVehicle() || IsInsideBuilding() || IsUnderRoof();
	}

	override protected void CollectAndSetPlayerData()
	{
		super.CollectAndSetPlayerData();

		if (m_Player)
		{
			m_Player.SetIsInShelter(IsPlayerSheltered());
		}
	}
}
