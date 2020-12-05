//search:
		if (item.pkItem)
		{
			item.vnum = pkItem->GetVnum();
			item.count = pkItem->GetCount();
			item.price = pTable->price;
			item.itemid	= pkItem->GetID();
		}
		else
		{
			item.vnum = pTable->vnum;
			item.count = pTable->count;

			if (IS_SET(item_table->dwFlags, ITEM_FLAG_COUNT_PER_1GOLD))
			{
				if (item_table->dwGold == 0)
					item.price = item.count;
				else
					item.price = item.count / item_table->dwGold;
			}
			else
				item.price = item_table->dwGold * item.count;
		}

//replace or adapt CShop::SetShopItems:
		if (item.pkItem)
		{
			item.vnum = pkItem->GetVnum();
			item.count = pkItem->GetCount();
			item.price = pTable->price;
			item.itemid	= pkItem->GetID();
		}
		else
		{
			item.vnum = pTable->vnum;
			item.count = pTable->count;
			item.multiple_buy = pTable->multiple_buy; // :D
				
			if (IS_SET(item_table->dwFlags, ITEM_FLAG_COUNT_PER_1GOLD))
			{
				if (item_table->dwGold == 0)
					item.price = item.count;
				else
					item.price = item.count / item_table->dwGold;
			}
			else
				item.price = item_table->dwGold * item.count;
		}
			
//search CShop::AddGuest:
		pack2.items[i].count = item.count;

//add:
		pack2.items[i].multiple_buy = item.multiple_buy;
		
//search CShop::BroadcastUpdateItem:
		pack2.item.vnum	= m_itemVector[pos].vnum;

//add:
		pack2.item.multiple_buy = m_itemVector[pos].multiple_buy;
		
//search CShop::Buy:
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
			else
				M2_DESTROY_ITEM(item);
//replace:
			if (r_item.multiple_buy == 1)
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
				else
					M2_DESTROY_ITEM(item);
			}
			else
				item->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
		
		