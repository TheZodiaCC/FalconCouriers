class FCHumanityHelpers
{
	const static string logsRoot = "$profile:/FH/";
	
	private static FC_HumanityData loadPlayerHumanityData(string playerID)
	{
		string playerJsonPath = logsRoot + playerID + ".json";
		
		if (FileExist(playerJsonPath))
		{
			FC_HumanityData playerHumanityData = new FC_HumanityData();
			
			JsonFileLoader<FC_HumanityData>.JsonLoadFile(playerJsonPath, playerHumanityData);
			
			return playerHumanityData;
		}	
		
		return null;
	}
	
	static bool checkIfPlayerHasEnoughtHumanity(string playerId, FalconCourier courier)
	{
		FC_HumanityData humanityData = loadPlayerHumanityData(playerId);
		
		if (humanityData)
		{
			int playerHumanity = humanityData.getHumanity();
			
			int courierMinHumanity = courier.getMinHumanity();
			int courierMaxHumanity = courier.getMaxHumanity();
			
			return playerHumanity.InRange(courierMinHumanity, courierMaxHumanity);
		}
		else
		{
			return false;
		}
	}
	
	static string getHumanityMessage(string playerId, FalconCourier courier)
	{
		FC_HumanityData humanityData = loadPlayerHumanityData(playerId);
		string message = "";
		
		if (humanityData)
		{
			int playerHumanity = humanityData.getHumanity();
			
			int courierMinHumanity = courier.getMinHumanity();
			int courierMaxHumanity = courier.getMaxHumanity();
			
			if (playerHumanity < courierMinHumanity)
			{
				message = "Your humanity is too low, courier requires at least: " + courierMinHumanity;
			}
			
			else if (playerHumanity > courierMaxHumanity)
			{
				message = "Your humanity is too high, courier requires at least: " + courierMaxHumanity;
			}
		}
		
		return message;
	}
}