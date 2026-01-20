modded class EmissionSymptom extends SymptomBase
{
	protected float damageTick = 0.0;
	protected float damageEmission = EmissionGlobalSettings.DEFAULT_DAMAGE_PER_SECOND;

	override void OnUpdateServer(PlayerBase player, float deltatime)
	{
		damageTick = damageTick + deltatime;

		if (damageTick >= 1.0)
		{
			if (!player.IsInShelterSync())
			{
				player.AddHealth("GlobalHealth", "Health", -damageEmission);
			}

			damageTick = 0.0;
		}
	}

	override void OnGetDeactivatedServer(PlayerBase player)
	{
		// Clean deactivation
	}
}