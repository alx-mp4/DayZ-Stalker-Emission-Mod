class EmissionGlobalSettings
{
	// Interval between emissions in seconds (default: 2 hours/7200)
	static const float DEFAULT_EMISSION_INTERVAL = 600;

	// Duration of the warning before emission in seconds
	static const float DEFAULT_WARNING_DURATION = 120;

	// Emission duration in seconds (default: 3 minutes/180)
	static const float DEFAULT_EMISSION_DURATION = 180;

	// Duration of the recovery phase after emission in seconds (default: 2 minutes/120)
	static const float DEFAULT_ENDING_DURATION = 120;

	// Damage per second during emission without cover (default: 10.0)
	static const float DEFAULT_DAMAGE_PER_SECOND = 10.0;

	// Flag for toggling the emission system (default: true)
	static bool EnableEmissionSystem = true;
};
