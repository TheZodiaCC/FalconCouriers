class ActionCourier: ActionInteractBase
{		
	void ActionCourier()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINone;
	}

	override string GetText()
	{
		return "Courier";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		FalconCourier courier = FalconCourier.Cast(target.GetObject());
		
		if( courier && courier.IsAlive())
		{
			return true;
		}

		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		FalconCourier courier = FalconCourier.Cast( action_data.m_Target.GetObject() );
		PlayerBase player = action_data.m_Player;
		
		if (FCHumanityHelpers.checkIfPlayerHasEnoughtHumanity(player.GetIdentity().GetId(), courier))
		{
			GetRPCManager().SendRPC("FalconCouriers", "openCourierMenuC", new Param1<int>(courier.getCourierId()), true,  player.GetIdentity());
		}
		
		GetRPCManager().SendRPC("FalconCouriers", "FCmessagePlayerC", new Param1<string>(FCHumanityHelpers.getHumanityMessage(player.GetIdentity().GetId(), courier)), true,  player.GetIdentity());
	}
}