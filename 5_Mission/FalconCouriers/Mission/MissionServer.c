modded class MissionServer
{
	ref CourierMenuBack courierMenuBack;
	
	
	void MissionServer()
	{
		courierMenuBack = new CourierMenuBack();
	}
	
	override void OnInit()
	{
		super.OnInit();
		
		FalconCouriersUtils.initCouriers();
	}
	
	override void OnMissionLoaded()
	{
		super.OnMissionLoaded();
		
		// Stopped working don't know why, works when called in OnMissionLoaded() in FalconTraders. Moved to OnInit()
		//FalconCouriersUtils.initCouriers();
	}
}