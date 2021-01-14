//search (long long CShop::Buy(LPCHARACTER ch, BYTE pos))
	else
	{
		if (item->IsDragonSoul())
			item->AddToCharacter(ch, TItemPos(DRAGON_SOUL_INVENTORY, iEmptyPos));
				item->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));

		ITEM_MANAGER::instance().FlushDelayedSave(item);

		if (item->GetVnum() >= 500219 && item->GetVnum() <= 500222)
			LogManager::instance().GoldLog(ch->GetPlayerID(), item->GetID(), PERSONAL_SHOP_BUY, "", ch->IsGM() ? "Yes" : "No");

		DBManager::instance().SendMoneyLog(MONEY_LOG_SHOP, item->GetVnum(), -dwPrice);
	}
	
//change
	else
	{
		if (item->IsDragonSoul())
			item->AddToCharacter(ch, TItemPos(DRAGON_SOUL_INVENTORY, iEmptyPos));
		else
		{
			WORD bCount = item->GetCount();
			
			if (IS_SET(item->GetFlag(), ITEM_FLAG_STACKABLE))
			{
				for (WORD i = 0; i < INVENTORY_MAX_NUM; ++i)
				{
					LPITEM item2 = ch->GetInventoryItem(i);

					if (!item2)
						continue;

					if (item2->GetVnum() == item->GetVnum())
					{
						int j;

						for (j = 0; j < ITEM_SOCKET_MAX_NUM; ++j)
							if (item2->GetSocket(j) != item->GetSocket(j))
								break;

						if (j != ITEM_SOCKET_MAX_NUM)
							continue;

						WORD bCount2 = MIN(ITEM_MAX_COUNT - item2->GetCount(), bCount);
						bCount -= bCount2;
						item2->SetCount(item2->GetCount() + bCount2);

						if (bCount == 0)
							break;
					}
				}

				item->SetCount(bCount);
			}
			
			if (bCount > 0)
				item->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
			else{
				M2_DESTROY_ITEM(item);
				return false;
			}
		}

		ITEM_MANAGER::instance().FlushDelayedSave(item);

		if (item->GetVnum() >= 500219 && item->GetVnum() <= 500222)
			LogManager::instance().GoldLog(ch->GetPlayerID(), item->GetID(), PERSONAL_SHOP_BUY, "", ch->IsGM() ? "Yes" : "No");

		DBManager::instance().SendMoneyLog(MONEY_LOG_SHOP, item->GetVnum(), -dwPrice);
	}
	
