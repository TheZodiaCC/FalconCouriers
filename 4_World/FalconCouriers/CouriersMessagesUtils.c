class CouriersMessagesUtils
{
	static void messageClient(string message, PlayerBase player)
	{
		GetRPCManager().SendRPC("FalconCouriers", "FCmessagePlayerC", new Param1<string>(message), true,  player.GetIdentity());
	}
}