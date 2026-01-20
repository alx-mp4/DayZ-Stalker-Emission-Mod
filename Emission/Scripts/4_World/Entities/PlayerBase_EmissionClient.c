modded class PlayerBase
{
	protected EffectSound Emissionrumble;
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

	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);

		switch (rpc_type)
		{
			case EmissionRPCHandler.RPC_EMISSION_WARNING:
				if (GetGame().IsClient())
				{
					EffectSound emissionWarn;
					PlaySoundSet(emissionWarn, "EmissionWarnSoundSet", 0, 0);
					emissionWarn.SetSoundAutodestroy(true);

					PlaySoundSetLoop(Emissionrumble, "EmissionRumbleSoundSet", 0.0, 1.0);
				}
				break;

			case EmissionRPCHandler.RPC_EMISSION_START:
				if (GetGame().IsClient())
				{
					// Audio only, no notifications
				}
				break;

			case EmissionRPCHandler.RPC_EMISSION_END:
				if (GetGame().IsClient())
				{
					StopSoundSet(Emissionrumble);
				}
				break;
		}
	}
}