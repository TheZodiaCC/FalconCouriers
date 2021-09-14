class FalconCourierCharacterData
{
	private int courierId;
	private string courierName;
	private string type;
	private string spawnPoint
	private string direction
	private int maxHumanity
	private int minHumanity
	private string head;
	private string body;
	private string pants;
	private string boots;
	private ref array<string> takesPackages = new array<string>();
	private ref array<string> givesPackages = new array<string>();
	
	int getCourierId()
	{
		return courierId;
	}
	
	string getCourierType()
	{
		return type;
	}
	
	string getCourierName()
	{
		return courierName;
	}
	
	string getCourierSpawnPoint()
	{
		return spawnPoint;
	}
	
	string getCourierDirection()
	{
		return direction;
	}
	
	string getCourierHead()
	{
		return head;
	}
	
	string getCourierBody()
	{
		return body;
	}
	
	string getCourierPants()
	{
		return pants;
	}
	string getCourierBoots()
	{
		return boots;
	}
	
	int getMaxHumanity()
	{
		return maxHumanity;
	}
	
	int getMinHumanity()
	{
		return minHumanity;
	}
	
	array<string> getTakesPackages()
	{
		return takesPackages;
	}
	
	array<string> getGivesPackages()
	{
		return givesPackages;
	}
}