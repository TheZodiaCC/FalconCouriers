class FCHumanityHelpers
{	
	static bool checkIfPlayerHasEnoughtHumanity(string playerId, FalconCourier courier)
	{
		#ifdef FALCON_HEROES
			PlayerHumanityValues humanityData = FalconHeroesLogger.loadPlayerHumanityData(playerId);
			
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
		#else
			return true;
		#endif
	}
	
	static string getHumanityMessage(string playerId, FalconCourier courier)
	{
		string message = "";
		
		#ifdef FALCON_HEROES
			PlayerHumanityValues humanityData = FalconHeroesLogger.loadPlayerHumanityData(playerId);
			
			if (humanityData)
			{
				int playerHumanity = humanityData.getHumanity();
				
				int courierMinHumanity = courier.getMinHumanity();
				int courierMaxHumanity = courier.getMaxHumanity();
				
				if (playerHumanity < courierMinHumanity)
				{
					message = CouriersMessagesConsts.HUMANITY_TO_LOW + courierMinHumanity;
				}
				
				else if (playerHumanity > courierMaxHumanity)
				{
					message = CouriersMessagesConsts.HUMANITY_TO_HIGH + courierMaxHumanity;
				}
			}
		##endif
		
		return message;
	}
}