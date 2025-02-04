#include "includes.h"

void CFeature20FPS::Init()
{
	CChaosFeature::Init();
}

void CFeature20FPS::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	fps_max = pEngfuncs->pfnGetCvarPointer("fps_max");
	fps_value = fps_max->value;
	m_bActivated = true;
}

void CFeature20FPS::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;

	fps_max->value = fps_value;
}

void CFeature20FPS::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	// TODO: change it after supporting WON/Pre-Steampipe builds
	fps_max->value = 19.5f;
}

const char* CFeature20FPS::GetFeatureName()
{
	return "Force 20 FPS";
}