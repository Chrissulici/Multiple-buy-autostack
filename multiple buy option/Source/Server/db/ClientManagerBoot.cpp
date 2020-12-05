//search:
	static const char * s_szQuery =
		"SELECT "
		"shop.vnum, "
		"shop.npc_vnum, "
		"shop_item.item_vnum, "
		"shop_item.count "
		"FROM shop LEFT JOIN shop_item "
		"ON shop.vnum = shop_item.shop_vnum ORDER BY shop.vnum, shop_item.item_vnum";

//replace or adapt CShop::SetShopItems:
	static const char * s_szQuery =
		"SELECT "
		"shop.vnum, "
		"shop.npc_vnum, "
		"shop_item.item_vnum, "
		"shop_item.count, "
		"shop_item.multiple_buy " // :D
		"FROM shop LEFT JOIN shop_item "
		"ON shop.vnum = shop_item.shop_vnum ORDER BY shop.vnum, shop_item.item_vnum";
			
//search:
		str_to_number(pItem->count, data[col++]);

//add:
		str_to_number(pItem->multiple_buy, data[col++]);
		
