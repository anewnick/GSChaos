#include "includes.h"

void CFeatureHighGravity::Init()
{
	CChaosFeature::Init();
}

void CFeatureHighGravity::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	sv_gravity = g_engfuncs->pfnCVarGetPointer("sv_gravity");

	if (!sv_gravity)
		return;

	m_flOldGravityValue = sv_gravity->value;
	m_bActivated = true;
}

void CFeatureHighGravity::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;

	if (!sv_gravity)
	{
		SERVER_COMMAND("sv_gravity 800\n");
		return;
	}

	sv_gravity->value = m_flOldGravityValue;
}

void CFeatureHighGravity::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	if (!sv_gravity)
		return;

	sv_gravity->value = 1600.0f;
}

const char* CFeatureHighGravity::GetFeatureName()
{
	return "X2 Gravity";
}