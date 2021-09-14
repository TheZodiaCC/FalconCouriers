class FalconCourier extends SurvivorBase
{
	private int courierId;
	private int maxHumanity;
	private int minHumanity;
	
	
	int getCourierId()
	{
		return courierId;
	}
	
	void setCourierId(int value)
	{
		courierId = value;
	}
	
	int getMaxHumanity()
	{
		return maxHumanity;
	}
	
	void setMaxHumanity(int value)
	{
		maxHumanity = value;
	}
	
	int getMinHumanity()
	{
		return minHumanity;
	}
	
	void setMinHumanity(int value)
	{
		minHumanity = value;
	}
	
	override void SetActionsRemoteTarget( out TInputActionMap InputActionMap)
	{		
		AddAction(ActionCourier, InputActionMap);
	}
	
	override bool CanBeRestrained()
	{
		return false;
	}
}