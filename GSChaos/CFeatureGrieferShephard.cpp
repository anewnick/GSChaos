#include "includes.h"

#define SHEPHARD_ROCKET_TIME 1.25

void CFeatureGrieferShephard::Init()
{
	CChaosFeature::Init();
	m_flRocketTime = 0.0;
}

void CFeatureGrieferShephard::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	m_bActivated = true;
	Spawn();
}

void CFeatureGrieferShephard::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;
}

const char* CFeatureGrieferShephard::GetFeatureName()
{
	return "Spawn Griefer Shephard";
}

void CFeatureGrieferShephard::OnFrame(double time)
{
	static bool bPaused;
	bPaused = CLWrapper::GetPausedState();

	if (bPaused)
		return;

	if (m_pShephard)
		Think();
}

void CFeatureGrieferShephard::Spawn()
{
	if (m_pShephard)
	{
		g_engfuncs->pfnRemoveEntity(m_pShephard);
		if (m_pShephard->pvPrivateData != NULL)
		{
			FREE_PRIVATE(m_pShephard);
		}

		m_pShephard = NULL;
	}

	m_pShephard = CREATE_NAMED_ENTITY(MAKE_STRING("monster_generic"));
	
	if (!m_pShephard)
		return;

	PRECACHE_MODEL("models/shephard.mdl");
	SET_MODEL(m_pShephard, "models/shephard.mdl");

	gEntityInterface->pfnSpawn(m_pShephard);
	Vector playerOrigin = (*sv_player)->v.origin;
	playerOrigin.z += 10.0f;

	m_pShephard->v.health = 1337;
	m_pShephard->v.origin = playerOrigin;
	m_pShephard->v.angles = (*sv_player)->v.angles;
	m_pShephard->v.movetype = MOVETYPE_NOCLIP;
	m_pShephard->v.solid = SOLID_NOT;
	m_pShephard->v.sequence = 11;
	m_pShephard->v.gaitsequence = 11;

	m_flRocketTime = gChaos.GetGlobalTime() + SHEPHARD_ROCKET_TIME;
	ma_engine_set_volume(&miniAudio, CVAR_GET_FLOAT("volume"));
	ma_engine_play_sound(&miniAudio, "valve/sound/hgrunt/c2a3_hg_laugh.wav", NULL);
}

void CFeatureGrieferShephard::Think()
{
	if (!m_pShephard)
		return;

	if (m_pShephard->free)
		return;

	if (!strstr(STRING(m_pShephard->v.classname), "monster_generic"))
		return;

	m_pShephard->v.sequence = 11;
	m_pShephard->v.gaitsequence = 11;
	m_pShephard->v.effects = 0;

	//DEBUG_PRINT("GetChaosTime(): %.01f | m_flRocketTime: %.01f\n", gChaos.GetGlobalTime(), m_flRocketTime);
	if (gChaos.GetGlobalTime() >= m_flRocketTime)
	{
		DEBUG_PRINT("CFeatureGrieferShephard::LaunchRocket\n");
		LaunchRocket();
		m_flRocketTime = gChaos.GetGlobalTime() + SHEPHARD_ROCKET_TIME;
	}
}

void CFeatureGrieferShephard::LaunchRocket()
{
	edict_t* pent = CREATE_NAMED_ENTITY(MAKE_STRING("rpg_rocket"));
	if (!pent)
		return;

	Vector vecTarget = gpGlobals->v_forward;
	Vector vecDir;
	float flDist, flMax, flDot;
	TraceResult tr;

	pent->v.origin = m_pShephard->v.origin + (m_pShephard->v.view_ofs * 96);
	pent->v.angles = m_pShephard->v.angles;
	pent->v.owner = m_pShephard;
	gEntityInterface->pfnSpawn(pent);

	UTIL_MakeAimVectors(pent->v.angles);

	vecTarget = gpGlobals->v_forward;
	flMax = 4096;
	//UTIL_TraceLine(pent->v.origin, (*sv_player)->v.origin, dont_ignore_monsters, pent, &tr);
	// ALERT( at_console, "%f\n", tr.flFraction );
	vecDir = (*sv_player)->v.origin - pent->v.origin;
	flDist = vecDir.Length();
	vecDir = vecDir.Normalize();
	flDot = DotProduct(gpGlobals->v_forward, vecDir);
	if ((flDot > 0) && (flDist * (1 - flDot) < flMax))
	{
		flMax = flDist * (1 - flDot);
		vecTarget = vecDir;
	}

	pent->v.angles = UTIL_VecToAngles(vecTarget);
	m_pShephard->v.angles = UTIL_VecToAngles(vecTarget);

	float flSpeed = pent->v.velocity.Length();
	pent->v.velocity = pent->v.velocity * 0.2 + vecTarget * (flSpeed * 0.8 + 400);

	EMIT_SOUND_DYN2(pent, CHAN_WEAPON, "weapons/rocketfire1.wav", 0.9, ATTN_NORM, 0, PITCH_NORM);
	EMIT_SOUND_DYN2(pent, CHAN_ITEM, "weapons/glauncher.wav", 0.7, ATTN_NORM, 0, PITCH_NORM);
}