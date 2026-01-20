modded class PlayerBase
{
	protected bool m_IsInShelter;

	override void Init()
	{
		super.Init();
		RegisterNetSyncVariableBool("m_IsInShelter");
	}

	bool IsInShelterSync()
	{
		return m_IsInShelter;
	}

	void SetIsInShelter(bool value)
	{
		m_IsInShelter = value;

		if (GetGame().IsServer())
		{
			SetSynchDirty();
		}
	}
}