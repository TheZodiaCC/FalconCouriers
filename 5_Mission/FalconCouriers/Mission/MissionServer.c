modded class MissionServer
{
	ref CourierMenuBack courierMenuBack;
	
	
	void MissionServer()
	{
		courierMenuBack = new CourierMenuBack();
	}
	
	override void OnMissionLoaded()
	{
		super.OnMissionLoaded();
		
		FalconCouriersUtils.initCouriers();
	}
}